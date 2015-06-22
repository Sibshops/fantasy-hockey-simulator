#ifndef NEXT_PICK_HPP
#define NEXT_PICK_HPP

#include <string>
#include <vector>
#include <set>
#include <map>

#include "team.hpp"

using namespace std;


class NextPick_Cl
{  

public:
   
   typedef map<Player_Ty, int> PlayerMap_Ty;

   typedef multimap<int, Player_Ty> ReversePlayerMap_Ty;

   NextPick_Cl();

   // Add players who would be good additions for the team.
   void addPlayers(
      const Player_Ty::List_Ty& players);

   // Print the next picks. 
   void printNextPicks(
      const int minPercentage);

   // Return if the result didn't change between next picks
   bool isResultSettled() const
   {
      return m_settled;
   }

private:

   PlayerMap_Ty m_playerMap;

   string m_lastString;
   
   bool m_settled;

   int m_listAddedCount;
};


namespace NextPick_Ns
{


};
#endif
