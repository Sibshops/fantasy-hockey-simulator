#ifndef MATCH_HPP
#define MATCH_HPP

#include <string>
#include <vector>
#include <set>

#include "team.hpp"

using namespace std;

// This class defines a match between two teams.
class Match_Cl
{  

public:

  typedef vector<Match_Cl> Vector_Ty;

  // A set of the teams playing on a day.
  typedef std::set<Team_Ty> Playing_Ty;
  
  // The match "week"
  typedef std::vector<Playing_Ty> Week_Ty;

  Match_Cl(const string& startDate,
           const string& endDate,
           const int& offenseStarts,
           const int& defenseStarts,
           const int& goalieStarts,
           const bool& playoffs);

  std::string toString() const;
   
   time_t m_startDate;
   
   time_t m_endDate;

   int m_offenseStarts;
   
   int m_defenseStarts;
   
   int m_goalieStarts;
   
   bool m_playoffs;

   // The schedule of the teams playing for the week.
   Week_Ty m_week;
   
};


namespace Match_Ns
{
  Match_Cl::Vector_Ty buildMatchSchedule();

  string timeToDate(const time_t& time);
  time_t dateToTime(const string& time);
};
#endif
