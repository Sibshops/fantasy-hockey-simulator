#ifndef STARTS_HPP
#define STARTS_HPP

#include <set>

using namespace std;

namespace Starts_Ns
{
   void printMyTeamStarts();

   void maxStartsSingle();

   void findUselessOffense();
   void findAdditionalOffense();

   void dropTwoAddOne();

   // Get the players index to try. Returns a set of random numbers between 0- (numPlayers - 1);
   multiset<int> getRandomPlayers(
      const int& numPlayers, 
      const int& maxPlayerIndex);

   // Use to just figure out forward defense ratio.
   void idealSchedule();

   void idealDefense();

   void idealForwards();

   // Best players to fill up the rest of the team. Picked randomly.
   void addMany(
      // The number of players to add.
      const int& additionalPlayers);

   // Exhaustive search to find players
   void addFew(
      // The number of players to add.
      const int& additionalPlayers);
      
}




#endif
