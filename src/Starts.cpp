#include <math.h>
#include <stdint.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <limits>

#include "Starts.hpp"
#include "Match.hpp"
#include "week.hpp"
#include "NextPick.hpp"

// *****************************************************************************
// Private helper functions

// Fill a player at a specific position.
static void fillAtPosition(const Player_Ty& player,
			   const Position_Ty& position,
			   DailyPosition_Ty& dailyPosition)
{
  // Try to fill center spot
  if (position == posC)
    {
      if (teamLAST == dailyPosition.c1.m_team)
	{
	  dailyPosition.c1 = player;
	  return;
	}
      else if(teamLAST == dailyPosition.c2.m_team)
	{
	  dailyPosition.c2 = player;
	  return;
	}
    }
      
  // Try to fill lw spot
  if (position == posLW)
    {
      if (teamLAST == dailyPosition.lw1.m_team)
	{
	  dailyPosition.lw1 = player;
	  return;
	}
      else if(teamLAST == dailyPosition.lw2.m_team)
	{
	  dailyPosition.lw2 = player;
	  return;
	}

    }
      
  // Try to fill rw spot
  if (position == posRW)
    {
      if (teamLAST == dailyPosition.rw1.m_team)
	{
	  dailyPosition.rw1 = player;
	  return;
	}
      else if(teamLAST == dailyPosition.rw2.m_team)
	{
	  dailyPosition.rw2 = player;
	  return;
	}
    }

  // Try to fill F spot
  if ((position == posC) || (position == posLW) ||  (position == posRW))
    {
      if (teamLAST == dailyPosition.f1.m_team)
	{
	  dailyPosition.f1 = player;
	  return;
	}
      else if(teamLAST == dailyPosition.f2.m_team)
	{
	  dailyPosition.f2 = player;
	  return;
	}
    }

  // Try to fill the D spot
  if (position == posD)
    {
      if (teamLAST == dailyPosition.d1.m_team)
	{
	  dailyPosition.d1 = player;
	  return;
	}
      else if(teamLAST == dailyPosition.d2.m_team)
	{
	  dailyPosition.d2 = player;
	  return;
	}
      else if(teamLAST == dailyPosition.d3.m_team)
	{
	  dailyPosition.d3 = player;
	  return;
	}
      else if(teamLAST == dailyPosition.d4.m_team)
	{
	  dailyPosition.d4 = player;
	  return;
	}
    }
}


static void populateDailyPosition(Player_Ty::List_Ty::const_iterator currIter,
				 const Player_Ty::List_Ty::const_iterator& endIter,
				 const Match_Cl::Playing_Ty& playingToday,
				 DailyPosition_Ty& dailyPosition)
{
  
  // Tail of the recursion
  if (currIter == endIter)
    {
      return;
    }

  if (14 == dailyPosition.countPlayers())
    {
      return;
    }  

  // increment until we get to a player who is playing.
  while (0 == playingToday.count(currIter->m_team))
    {
      ++currIter;
      
      if (currIter == endIter)
	{
	  return;
	}      
    }


  if (currIter->m_position.size() > 1)
    {
      DailyPosition_Ty bestDailyPosition = dailyPosition;
      
      Player_Ty currPlayer = *currIter;
      
      ++currIter;
      
      for (set<Position_Ty>::const_iterator posIter = currPlayer.m_position.begin();
	   posIter != currPlayer.m_position.end();
	   ++posIter)
	{
	  DailyPosition_Ty currDailyPosition = dailyPosition;

	  fillAtPosition(currPlayer,
			 *posIter,
			 currDailyPosition);
	  
	  // Recurse
	  populateDailyPosition(currIter, 
				endIter,
				playingToday,
				currDailyPosition);
	  
	  if (currDailyPosition.countPlayers() > bestDailyPosition.countPlayers())
	    {
	      bestDailyPosition = currDailyPosition;
	    }	  
	}
      
      dailyPosition = bestDailyPosition;
      
    }
  else
    {
      
      fillAtPosition(*currIter,
		     *(currIter->m_position.begin()),
		     dailyPosition);
      
      // Increment to next.
      ++currIter;
      
      // Recurse
      populateDailyPosition(currIter, 
			    endIter,
			    playingToday,
			    dailyPosition);
    }
}


static void getDailyPosition(const Match_Cl::Playing_Ty& playingToday,
			   const Player_Ty::List_Ty& myTeam,
			   DailyPosition_Ty& dailyPosition)
{


  // Begin
  Player_Ty::List_Ty::const_iterator myTeamIterBegin = myTeam.begin();
  Player_Ty::List_Ty::const_iterator myTeamIterEnd = myTeam.end();


  populateDailyPosition(myTeamIterBegin, 
			myTeamIterEnd, 
			playingToday,
			dailyPosition);


  // Playing today
  // std::cout << " - playing today" << std::endl;
  
  // dailyPosition.printPlayers();  
}

  

static int countMatchStarts(const Match_Cl& match,
                            const Player_Ty::List_Ty& myTeam,
                            const bool& printStarts)
{
   int maxPossibleForwardsForMatch = 0;
   int maxPossibleDefenseForMatch = 0;

   const int cHOLD_OFF_FORWARDS_STARTS = match.m_offenseStarts - 1;

   const int cHOLD_OFF_DEFENSE_STARTS = match.m_defenseStarts - 1;

   for (Match_Cl::Week_Ty::const_iterator weekIter = match.m_week.begin();
        weekIter != match.m_week.end();
        ++weekIter)
   {
      // The 
      DailyPosition_Ty dailyPosition;

      // Playing this day
      getDailyPosition(*weekIter, myTeam, dailyPosition);

      {
         const int cSTARTS_THIS_DAY = dailyPosition.countForwards();

         const int cPREV_STARTS = min(maxPossibleForwardsForMatch, cHOLD_OFF_FORWARDS_STARTS);
	
         const int cSTARTS_UP_TO_THIS_DAY = cPREV_STARTS + cSTARTS_THIS_DAY;
	
         maxPossibleForwardsForMatch = max(maxPossibleForwardsForMatch, cSTARTS_UP_TO_THIS_DAY);
      }

      {
         const int cSTARTS_THIS_DAY = dailyPosition.countDefense();
	
         const int cPREV_STARTS = min(maxPossibleDefenseForMatch, cHOLD_OFF_DEFENSE_STARTS);
	
         const int cSTARTS_UP_TO_THIS_DAY = cPREV_STARTS + cSTARTS_THIS_DAY;
	
         maxPossibleDefenseForMatch = max(maxPossibleDefenseForMatch, cSTARTS_UP_TO_THIS_DAY);
      }
   }
   
   int maxPossibleForMatch = maxPossibleForwardsForMatch + maxPossibleDefenseForMatch;


   // If the playoffs multiply
   if (true == match.m_playoffs)
   {
      maxPossibleForMatch *= 2;
   }
   
   if (true == printStarts)
   {
      cout << maxPossibleForMatch << " starts for " << Match_Ns::timeToDate(match.m_startDate) << " - " << Match_Ns::timeToDate(match.m_endDate) << endl;
   }
   
   return maxPossibleForMatch;
}

static int countTotalStarts(const Match_Cl::Vector_Ty& matchSchedule,
                            const Player_Ty::List_Ty& myTeam,
                            const bool& printStarts)
{
  int maxTotalCount = 0;
  
  for (Match_Cl::Vector_Ty::const_iterator schIter = matchSchedule.begin();
       schIter != matchSchedule.end();
       ++schIter)
    {
       maxTotalCount += countMatchStarts(*schIter, myTeam, printStarts);
    }
     
  return (maxTotalCount);
}

// *****************************************************************************
// Starts_Ns

void Starts_Ns::maxStartsSingle()
{
  // The Match schedule
  const Match_Cl::Vector_Ty cMATCH_SCHEDULE = Match_Ns::buildMatchSchedule();

  const Player_Ty::List_Ty cMY_TEAM = Team_Ns::getMyTeam();

  const int cCURRENT_TOTAL = countTotalStarts(cMATCH_SCHEDULE, cMY_TEAM, false);

  std::cout << "Current Total: " << cCURRENT_TOTAL << endl;

  const Player_Ty::Vector_Ty cNEW_PLAYERS = Player_Ns::getNewOffensePlayers();
 
  // Pick a player from my team to remove
  for (Player_Ty::List_Ty::const_iterator firstPlayerIter = cMY_TEAM.begin();
       firstPlayerIter != cMY_TEAM.end();
       ++firstPlayerIter)
    {
      for (size_t i = 0; i < cNEW_PLAYERS.size(); ++i)
	{
	  // Copy the team
	  Player_Ty::List_Ty totalTeam(cMY_TEAM.begin(), cMY_TEAM.end());
	  
	  // Remove first two players
	  totalTeam.remove(*firstPlayerIter);
			  
	  // Add i and j.
	  totalTeam.push_front(cNEW_PLAYERS[i]);
	
	  // On this position

	  const int cNEW_TOTAL = countTotalStarts(cMATCH_SCHEDULE, totalTeam, false);

     // if (cNEW_TOTAL > cCURRENT_TOTAL)
	    {
	      std::cout << cNEW_TOTAL - cCURRENT_TOTAL << " drop " << firstPlayerIter->toString();
	      std::cout << " pickup " << cNEW_PLAYERS[i].toString() << std::endl;
	    }
	}
    }  
}


void Starts_Ns::findUselessOffense()
{
  // Get teams by weeks
  const Match_Cl::Vector_Ty cMATCH_SCHEDULE = Match_Ns::buildMatchSchedule();

  const Player_Ty::List_Ty cMY_TEAM = Team_Ns::getMyTeam();

  const int cCURRENT_TOTAL = countTotalStarts(cMATCH_SCHEDULE, cMY_TEAM, false);

  std::cout <<  __func__ << "max starts " << cCURRENT_TOTAL << std::endl;

  // Pick a player from my team to remove
  for (Player_Ty::List_Ty::const_iterator firstPlayerIter = cMY_TEAM.begin();
       firstPlayerIter != cMY_TEAM.end();
       ++firstPlayerIter)
    {
      // Copy the team
      Player_Ty::List_Ty totalTeam(cMY_TEAM.begin(), cMY_TEAM.end());

      // Player name
      const string cPLAYER_NAME = firstPlayerIter->toString();     
      
      totalTeam.remove(*firstPlayerIter);

      const int cNEW_TOTAL = countTotalStarts(cMATCH_SCHEDULE, totalTeam, false);
      
      std::cout << cCURRENT_TOTAL - cNEW_TOTAL << " less starts without " << cPLAYER_NAME << std::endl;
    }

}

void Starts_Ns::findAdditionalOffense()
{
  // The Match schedule
  const Match_Cl::Vector_Ty cMATCH_SCHEDULE = Match_Ns::buildMatchSchedule();

  const Player_Ty::List_Ty cMY_TEAM = Team_Ns::getMyTeam();

  const int cCURRENT_TOTAL = countTotalStarts(cMATCH_SCHEDULE, cMY_TEAM, false);

  std::cout << "Current Total: " << cCURRENT_TOTAL << endl;

  const Player_Ty::Vector_Ty cNEW_PLAYERS = Player_Ns::getNewOffensePlayers();
 

  for (size_t i = 0; i < cNEW_PLAYERS.size(); ++i)
    {
      // Copy the team
      Player_Ty::List_Ty totalTeam(cMY_TEAM.begin(), cMY_TEAM.end());
	  		  
      // Add i and j.
      totalTeam.push_front(cNEW_PLAYERS[i]);
	
      // On this position

      const int cNEW_TOTAL = countTotalStarts(cMATCH_SCHEDULE, totalTeam, false);

      if (cNEW_TOTAL > cCURRENT_TOTAL)
      {
         std::cout << cNEW_TOTAL - cCURRENT_TOTAL << " pickup " << cNEW_PLAYERS[i].toString() << std::endl;
      }
    }
}

void Starts_Ns::printMyTeamStarts()
{
  // The Match schedule
  const Match_Cl::Vector_Ty cMATCH_SCHEDULE = Match_Ns::buildMatchSchedule();

  const Player_Ty::List_Ty cMY_TEAM = Team_Ns::getMyTeam();

  const int cCURRENT_TOTAL = countTotalStarts(cMATCH_SCHEDULE, cMY_TEAM, true);

  std::cout << "Current Total: " << cCURRENT_TOTAL << endl;
}


void Starts_Ns::dropTwoAddOne()
{
  // The Match schedule
  const Match_Cl::Vector_Ty cMATCH_SCHEDULE = Match_Ns::buildMatchSchedule();

  const Player_Ty::List_Ty cMY_TEAM = Team_Ns::getMyTeam();

  const int cCURRENT_TOTAL = countTotalStarts(cMATCH_SCHEDULE, cMY_TEAM, false);

  std::cout << "Current Total: " << cCURRENT_TOTAL << endl;

  const Player_Ty::Vector_Ty cNEW_PLAYERS = Player_Ns::getNewOffensePlayers();
 
  // Pick a player from my team to remove
  for (Player_Ty::List_Ty::const_iterator firstPlayerIter = cMY_TEAM.begin();
       firstPlayerIter != cMY_TEAM.end();
       ++firstPlayerIter)
  {
     Player_Ty::List_Ty::const_iterator secondPlayerIter = firstPlayerIter;
     ++secondPlayerIter;
      
      // Pick second player from my team to remove.
     for (;
          secondPlayerIter != cMY_TEAM.end();
          ++secondPlayerIter)
     {
        for (size_t i = 0; i < cNEW_PLAYERS.size(); ++i)
        {
           // Copy the team
           Player_Ty::List_Ty totalTeam(cMY_TEAM.begin(), cMY_TEAM.end());
	  
           // Remove first two players
           totalTeam.remove(*firstPlayerIter);
           totalTeam.remove(*secondPlayerIter);
			  
           // Add i and j.
           totalTeam.push_front(cNEW_PLAYERS[i]);
	
           // On this position

           const int cNEW_TOTAL = countTotalStarts(cMATCH_SCHEDULE, totalTeam, false);

           // if (cNEW_TOTAL > cCURRENT_TOTAL + 3)
           {
              std::cout << cNEW_TOTAL - cCURRENT_TOTAL << " drop " << firstPlayerIter->toString()
                        << " and " << secondPlayerIter->toString();
              std::cout << " pickup " << cNEW_PLAYERS[i].toString() << std::endl;
           }
        }
     }  
  }
}

multiset<int> Starts_Ns::getRandomPlayers(
   const int& numPlayers, 
   const int& maxPlayerIndex)
{
   multiset<int> players;

   for (int i = 0; i < numPlayers; ++i)
   {
      // The max possible player index.
      const int cPLAYER_INDEX = rand() % maxPlayerIndex;

      players.insert(cPLAYER_INDEX);
   }
   
   return (players);
}


void Starts_Ns::idealSchedule()
{
  // The Match schedule
  const Match_Cl::Vector_Ty cMATCH_SCHEDULE = Match_Ns::buildMatchSchedule();

  const Player_Ty::Vector_Ty cNEW_PLAYERS = Player_Ns::getNewOffensePlayers();

  // Best possible number of starts for seanon is 1519
  
  const int cTOTAL_ROSTER_SIZE = 20;

  // Seed the generator
  srand (time(NULL));

  int runningMax = 0;
  
  for (int i = 0; i < numeric_limits<int>::max(); ++i)
  //while (true)
  {
     // Copy the team
     Player_Ty::List_Ty totalTeam;

     const multiset<int> cPLAYER_INDEX_SET = Starts_Ns::getRandomPlayers(cTOTAL_ROSTER_SIZE, 
                                                                         cNEW_PLAYERS.size());


     // The stream of players added
     stringstream ss;

     // ss << " num: " << remainingPlayers;

     for (multiset<int>::const_iterator stIter = cPLAYER_INDEX_SET.begin(); 
          stIter != cPLAYER_INDEX_SET.end();
          ++stIter)
     {
        // The player to add.
        const int cPLAYER_INDEX = *stIter;

        const Player_Ty& cNEW_PLAYER = cNEW_PLAYERS[cPLAYER_INDEX];

        totalTeam.push_back(cNEW_PLAYER);
        
        // ss << "(" << cPLAYER_INDEX << ") ";
        ss << cNEW_PLAYER.toString() << " ";
     }

     // On this position
     const int cNEW_TOTAL = countTotalStarts(cMATCH_SCHEDULE, totalTeam, false);
     
     // Number is from the max
     if (cNEW_TOTAL + 20 > runningMax)
     {
        std::cout << cNEW_TOTAL << " pickup " << ss.str() << std::endl;

        runningMax = max(runningMax, cNEW_TOTAL);
     }  
  }
}


void Starts_Ns::idealDefense()
{
  // The Match schedule
  const Match_Cl::Vector_Ty cMATCH_SCHEDULE = Match_Ns::buildMatchSchedule();

  const Player_Ty::Vector_Ty cNEW_PLAYERS = Player_Ns::getNewDefensePlayers();

  const Player_Ty::List_Ty cDEFENSE_KEEPERS =  Team_Ns::getDefenseKeepers();

  NextPick_Cl nextPick;
  
  // Number of Defensemen to add.
  const int cTOTAL_ROSTER_SIZE = 6 - cDEFENSE_KEEPERS.size();

  // Seed the generator
  srand (time(NULL));

  int runningMax = 0;
  
  // for (int i = 0; (false == nextPick.isResultSettled()) && (i < numeric_limits<int>::max()); ++i)
  //for (int i = 0; i < 10000; ++i)
  //while (true)
  while (false == nextPick.isResultSettled())
  {
     // Copy the team
     Player_Ty::List_Ty totalTeam(cDEFENSE_KEEPERS.begin(), cDEFENSE_KEEPERS.end());

     Player_Ty::List_Ty newPlayers;

     const multiset<int> cPLAYER_INDEX_SET = Starts_Ns::getRandomPlayers(cTOTAL_ROSTER_SIZE, 
                                                                         cNEW_PLAYERS.size());


     // The stream of players added
     stringstream ss;

     // ss << " num: " << remainingPlayers;

     for (multiset<int>::const_iterator stIter = cPLAYER_INDEX_SET.begin(); 
          stIter != cPLAYER_INDEX_SET.end();
          ++stIter)
     {
        // The player to add.
        const int cPLAYER_INDEX = *stIter;

        const Player_Ty& cNEW_PLAYER = cNEW_PLAYERS[cPLAYER_INDEX];

        totalTeam.push_back(cNEW_PLAYER);

        newPlayers.push_back(cNEW_PLAYER);
        // ss << "(" << cPLAYER_INDEX << ") ";
        ss << cNEW_PLAYER.toString() << " ";
     }

     // On this position
     const int cNEW_TOTAL = countTotalStarts(cMATCH_SCHEDULE, totalTeam, false);
     
     // Number is from the max
     if (cNEW_TOTAL + 10 > runningMax)
     {
        // std::cout << cNEW_TOTAL << " pickup " << ss.str() << std::endl;

        nextPick.addPlayers(newPlayers);

        runningMax = max(runningMax, cNEW_TOTAL);

        static int interval = 0;
        ++interval;
        
        if (0 == interval % 500)
        {
           nextPick.printNextPicks(0);
           return;
        }
     }  
  }
}


void Starts_Ns::idealForwards()
{
  // The Match schedule
  const Match_Cl::Vector_Ty cMATCH_SCHEDULE = Match_Ns::buildMatchSchedule();

  const Player_Ty::Vector_Ty cNEW_PLAYERS = Player_Ns::getNewForwardPlayers();

  const Player_Ty::List_Ty cOFFENSE_KEEPERS =  Team_Ns::getOffenseKeepers();

  NextPick_Cl nextPick;
    
  // Number of Defensemen
  const int cTOTAL_ROSTER_SIZE = 13 - cOFFENSE_KEEPERS.size();

  // Seed the generator
  srand (time(NULL));

  int runningMax = 0;

  // for (int i = 0; i < numeric_limits<int>::max(); ++i)
  //while (true)
  while (false == nextPick.isResultSettled())
  {
     // Copy the team
     Player_Ty::List_Ty totalTeam(cOFFENSE_KEEPERS.begin(), cOFFENSE_KEEPERS.end());

     Player_Ty::List_Ty newPlayers;

     const multiset<int> cPLAYER_INDEX_SET = Starts_Ns::getRandomPlayers(cTOTAL_ROSTER_SIZE, 
                                                                         cNEW_PLAYERS.size());

     // The stream of players added
     stringstream ss;

     //ss << " num: " << remainingPlayers;

     for (multiset<int>::const_iterator stIter = cPLAYER_INDEX_SET.begin(); 
          stIter != cPLAYER_INDEX_SET.end();
          ++stIter)
     {
        // The player to add.
        const int cPLAYER_INDEX = *stIter;

        const Player_Ty& cNEW_PLAYER = cNEW_PLAYERS[cPLAYER_INDEX];

        totalTeam.push_back(cNEW_PLAYER);
        newPlayers.push_back(cNEW_PLAYER);
        
        // ss << "(" << cPLAYER_INDEX << ") ";
        // ss << cNEW_PLAYER.toString() << " ";
     }

     // On this position
     const int cNEW_TOTAL = countTotalStarts(cMATCH_SCHEDULE, totalTeam, false);
     
     // Number is from the max
     if (cNEW_TOTAL + 15 > runningMax)
     {
        // std::cout << cNEW_TOTAL << " pickup " << ss.str() << std::endl;

        nextPick.addPlayers(newPlayers);

        runningMax = max(runningMax, cNEW_TOTAL);

        static int interval = 0;
        ++interval;
        
        if (0 == interval % 500)
        {
           nextPick.printNextPicks(0);
           return;
        }
     }  
  }
}



void Starts_Ns::addMany(const int& additionalPlayers)
{
  // The Match schedule
  const Match_Cl::Vector_Ty cMATCH_SCHEDULE = Match_Ns::buildMatchSchedule();

  const Player_Ty::Vector_Ty cNEW_PLAYERS = Player_Ns::getNewOffensePlayers();

  const Player_Ty::List_Ty cMY_TEAM = Team_Ns::getMyTeam();

  // Seed the generator
  srand (time(NULL));

  int runningMax = 0;
  
  for (int i = 0; i < 1000000; ++i)
  //while (true)
  {
     // Copy the team
     Player_Ty::List_Ty totalTeam(cMY_TEAM.begin(), cMY_TEAM.end());

     const multiset<int> cPLAYER_INDEX_SET = Starts_Ns::getRandomPlayers(additionalPlayers, 
                                                                         cNEW_PLAYERS.size());

     // The stream of players added
     stringstream ss;

     // ss << " num: " << remainingPlayers;

     for (multiset<int>::const_iterator stIter = cPLAYER_INDEX_SET.begin(); 
          stIter != cPLAYER_INDEX_SET.end();
          ++stIter)
     {
        // The player to add.
        const int cPLAYER_INDEX = *stIter;

        const Player_Ty& cNEW_PLAYER = cNEW_PLAYERS[cPLAYER_INDEX];

        totalTeam.push_back(cNEW_PLAYER);
        
        // ss << "(" << cPLAYER_INDEX << ") ";
        ss << cNEW_PLAYER.toString() << " ";
     }

     // On this position
     const int cNEW_TOTAL = countTotalStarts(cMATCH_SCHEDULE, totalTeam, false);
     
     // Number is from the max
     if (cNEW_TOTAL + 6 > runningMax)
     {
        std::cout << cNEW_TOTAL << " pickup " << ss.str() << std::endl;

        runningMax = max(runningMax, cNEW_TOTAL);
     }  
  }
}


void Starts_Ns::addFew(
   const int& additionalPlayers)
{
   // The Match schedule
   const Match_Cl::Vector_Ty cMATCH_SCHEDULE = Match_Ns::buildMatchSchedule();

   const Player_Ty::List_Ty cMY_TEAM =  Team_Ns::getMyTeam();;

   const uint64_t cCURRENT_TOTAL = countTotalStarts(cMATCH_SCHEDULE, cMY_TEAM, false);

   std::cout << "Current Total: " << cCURRENT_TOTAL << endl;

   // const Player_Ty::Vector_Ty cNEW_PLAYERS = Player_Ns::getNewOffensePlayers();
   const Player_Ty::Vector_Ty cNEW_PLAYERS = Player_Ns::getNewForwardPlayers();

   const uint64_t cINT_COUNTER_TOTAL = pow(cNEW_PLAYERS.size(), additionalPlayers);

   // cout << "debug: " << cINT_COUNTER_TOTAL << endl;

   // Seed the generator
   srand (time(NULL));

   cout << "Rand max" << RAND_MAX << endl;

   uint64_t runningMax = 0;

   for (uint64_t combinedIndex = 0; combinedIndex < cINT_COUNTER_TOTAL; ++combinedIndex)
   {
      // Copy the team
      Player_Ty::List_Ty totalTeam(cMY_TEAM.begin(), cMY_TEAM.end());

      // The remaining players to add in an index format.
      uint64_t remainingPlayers = combinedIndex;

      // The stream of players added
      stringstream ss;


      // ss << " num: " << remainingPlayers;

      for (uint64_t playerIndex = 0; playerIndex < additionalPlayers; ++playerIndex)
      {
         // The player to add.
         const uint64_t cPLAYER_INDEX = remainingPlayers % cNEW_PLAYERS.size();

         const Player_Ty& cNEW_PLAYER = cNEW_PLAYERS[cPLAYER_INDEX];

         totalTeam.push_back(cNEW_PLAYER);

         ss << cNEW_PLAYER.toString() << " ";

         remainingPlayers = remainingPlayers / cNEW_PLAYERS.size();
      }

      // On this position
      const uint64_t cNEW_TOTAL = countTotalStarts(cMATCH_SCHEDULE, totalTeam, false);

      // Number is from the max
      if (cNEW_TOTAL + 4 > runningMax)
      {
         const int64_t cMORE_STARTS = cNEW_TOTAL - cCURRENT_TOTAL;
         
         std::cout <<  cMORE_STARTS << " pickup " << ss.str() << std::endl;

         runningMax = max(runningMax, cNEW_TOTAL);
      }
   }
}
