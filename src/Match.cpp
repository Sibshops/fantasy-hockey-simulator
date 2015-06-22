#include <sstream>
#include <fstream>

#include "Match.hpp"
#include "nameConversion.hpp"

Match_Cl::Match_Cl(const string& startDate,
                   const string& endDate,
                   const int& offenseStarts,
                   const int& defenseStarts,
                   const int& goalieStarts,
                   const bool& playoffs)
   : m_startDate(),
     m_endDate(),
     m_offenseStarts(offenseStarts),
     m_defenseStarts(defenseStarts),
     m_goalieStarts(m_goalieStarts),
     m_playoffs(playoffs)
     
{
  m_startDate = Match_Ns::dateToTime(startDate);
  m_endDate = Match_Ns::dateToTime(endDate);
}


std::string Match_Cl::toString() const
{
  std::stringstream ss;

  ss << "Start: " << Match_Ns::timeToDate(m_startDate)
     << ", End: " << Match_Ns::timeToDate(m_endDate) << ", Total: " << m_offenseStarts << "off - "      << m_defenseStarts << "def ";

  for (Week_Ty::const_iterator wiIter = m_week.begin(); 
       wiIter != m_week.end(); 
       ++wiIter)
    {
      ss << std::endl << " -";
      
      for (Playing_Ty::const_iterator playIter = wiIter->begin();
	   playIter != wiIter->end();
	   ++playIter)
	{
	  ss << " " << NameConversion_Ty::getName(*playIter);
	}
    }

  return (ss.str());
}

// Fill the match schedule with the daily teams.
static void fillMatches(Match_Cl::Vector_Ty& schedule)
{
  std::string line;
  
  //std::ifstream fileStream("data/2013_2014_NHL_Rest_Schedule.csv");
  //std::ifstream schedule ("2013_2014_NHL_One_Week_Schedule.csv");

  //std::ifstream fileStream("data/2013_2014_NHL_Schedule.csv");
  std::ifstream fileStream("data/2014_2015_NHL_Schedule.csv");

  
  Match_Cl::Vector_Ty::iterator schIter = schedule.begin();

  if (fileStream.is_open())
    {
      time_t previousDay = 0;

      Match_Cl::Playing_Ty playingToday;
            
      while (fileStream.good())
	{
	  getline(fileStream,line);
	  // std::cout << line << std::endl;

	  char *cLine = const_cast<char*>(line.c_str());
	  char *team1 = strtok(cLine, ",");
	  char *team2 = strtok(NULL, ","); 
	  char *date =  strtok(NULL, ",");

	  if (date != NULL)
	    {
	      time_t thisDay = Match_Ns::dateToTime(date);	  

	      // Continue to next match if date is before match
	      if (thisDay < schIter->m_startDate)
		{
		  continue;
		}
	      
	      // Increment if match is after the end date
	      while (schIter->m_endDate < thisDay)
		{
		  // push back current playing before incrementing
		  if (!playingToday.empty())
		    {
		      // Push back playing today to the week.
		      schIter->m_week.push_back(playingToday);
		      playingToday.clear();
		    }
		  
		  ++schIter;

		  if (schIter == schedule.end())
		    {
		      // No more to process.
		      return;
		    }
		}

	      if (thisDay == previousDay)
		{
		  // Add to existing match
		  playingToday.insert(NameConversion_Ty::getTeam(team1));
		  playingToday.insert(NameConversion_Ty::getTeam(team2));
		}
	      else 
		{		  
		  if (!playingToday.empty())
		    {
		      // Push back playing today to the week.
		      schIter->m_week.push_back(playingToday);
		      playingToday.clear();
		    }
		 
 
		  playingToday.insert(NameConversion_Ty::getTeam(team1));
		  playingToday.insert(NameConversion_Ty::getTeam(team2));
		  
		  previousDay = thisDay;
		}
	    }	 	 
	}
      
      // Push back playing today to the week.
      schIter->m_week.push_back(playingToday);
      
      fileStream.close();
   }
   else
   {
      std::cout << "Unable to open file" << std::endl << std::endl;
   }
}


Match_Cl::Vector_Ty Match_Ns::buildMatchSchedule()
{
  Match_Cl::Vector_Ty schedule;

  // schedule.push_back(Match_Cl("10/8/2014","10/12/2014", 23, 11, 7,  0));
  // schedule.push_back(Match_Cl("10/13/2014","10/19/2014", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("10/20/2014","10/26/2014", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("10/27/2014","11/2/2014", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("10/3/2014","11/9/2014", 32, 16, 10, 0));  
  // schedule.push_back(Match_Cl("11/10/2014","11/16/2014", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("11/17/2014","11/23/2014", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("11/24/2014","11/30/2014", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("12/1/2014","12/7/2014", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("12/8/2014","12/14/2014", 32, 16, 10, 0)); 
  // schedule.push_back(Match_Cl("12/15/2014","12/21/2014", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("12/22/2014","12/28/2014", 32, 16, 10, 0));
  
  // schedule.push_back(Match_Cl("12/29/2014","1/4/2015", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("1/5/2014","1/11/2015", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("1/12/2015","1/25/2015", 64, 32, 10, 0));
  // schedule.push_back(Match_Cl("1/26/2015","2/1/2015", 32, 16, 10, 0));  
  // schedule.push_back(Match_Cl("2/2/2015","2/8/2015", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("2/9/2015","2/15/2015", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("2/16/2015","2/22/2015", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("2/23/2015","3/1/2015", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("3/2/2015","3/8/2015", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("3/9/2015","3/15/2015", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("3/16/2015","3/22/2015", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("3/23/2015","3/29/2015", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("3/30/2015","4/5/2015", 32, 16, 10, 0));
  schedule.push_back(Match_Cl("4/6/2015","4/11/2015", 32, 16, 10, 0));


  
  // Need to figure out matchups.
  // schedule.push_back(Match_Cl("10/1/2013","10/6/2013", 27, 14, 9, 0));
  // schedule.push_back(Match_Cl("10/7/2013","10/13/2013", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("10/14/2013","10/20/2013", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("10/21/2013","10/27/2013", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("10/28/2013","11/3/2013", 32, 16, 10, 0));  
  // schedule.push_back(Match_Cl("11/4/2013","11/10/2013", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("11/11/2013","11/17/2013", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("11/18/2013","11/24/2013", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("11/25/2013","12/1/2013", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("12/2/2013","12/8/2013", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("12/9/2013","12/15/2013", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("12/16/2013","12/22/2013", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("12/23/2013","12/29/2013", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("12/30/2013","1/5/2014", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("1/6/2014","1/12/2014", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("1/13/2014","1/19/2014", 32, 16, 10, 0));  
  // schedule.push_back(Match_Cl("1/20/2014","1/26/2014", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("1/27/2014","2/2/2014", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("2/3/2014","2/9/2014", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("2/10/2014","3/9/2014", 128, 64, 40, 0));
  // schedule.push_back(Match_Cl("3/10/2014","3/16/2014", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("3/17/2014","3/23/2014", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("3/24/2014","3/30/2014", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("3/31/2014","4/6/2014", 32, 16, 10, 0));
  // schedule.push_back(Match_Cl("3/7/2014","4/13/2014", 32, 16, 10, 0));

  // Fill matches
  fillMatches(schedule);
  

  return schedule;
}


string Match_Ns::timeToDate(const time_t& time)
{
  struct tm * timeinfo;

  timeinfo = localtime (&time);
  
  char buf[255];

  strftime(buf, sizeof(buf), "%m/%d/%Y", timeinfo);
  
  return (buf);
}


time_t Match_Ns::dateToTime(const string& date)
{
  // Fill in time_t value
  struct tm timeinfo;
  memset(&timeinfo, 0, sizeof(struct tm));	   
  strptime(date.c_str(), "%m/%d/%Y",&timeinfo);
  return (mktime(&timeinfo));
}
