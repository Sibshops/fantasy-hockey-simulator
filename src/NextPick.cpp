#include <sstream>
#include <fstream>

#include "NextPick.hpp"
#include "nameConversion.hpp"

NextPick_Cl::NextPick_Cl()
   : m_playerMap(),
     m_lastString(),
     m_settled(false),
     m_listAddedCount(0)
{
}


void NextPick_Cl::addPlayers(
   const Player_Ty::List_Ty& players)
{
   // cout << "Adding ";

   for (Player_Ty::List_Ty::const_iterator plIter = players.begin();
        plIter != players.end();
        ++plIter)
   {
      //cout << plIter->toString() << " ";

      // increment the player
      m_playerMap[*plIter]++;
   }


   ++m_listAddedCount;

   // // Print map.
   // for (PlayerMap_Ty::const_iterator plIter = m_playerMap.begin();
   //      plIter != m_playerMap.end();
   //      ++plIter)
   // {
   //    cout << plIter->first.toString() << " ";
   // }
   //cout << endl;
}


void NextPick_Cl::printNextPicks(const int minPercentage)
{
   ReversePlayerMap_Ty reversePlayerMap;

   int total = 0;

   stringstream ss;

   // Iterate through the playermap to build a reverse player map.
   for (PlayerMap_Ty::const_iterator plIter = m_playerMap.begin();
        plIter != m_playerMap.end();
        ++plIter)
   {
      pair<int, Player_Ty> entry(plIter->second, plIter->first);
      
      reversePlayerMap.insert(entry);

      // Increment total to get normalized
      total += plIter->second;
   }

   // cout << "total = " << total << endl;
   
   for (ReversePlayerMap_Ty::const_reverse_iterator revPlIter = reversePlayerMap.rbegin();
        revPlIter != reversePlayerMap.rend();
        ++revPlIter)
   {
      const int cAVERAGE_APPEARANCES = revPlIter->first * 100 / m_listAddedCount;

      if (cAVERAGE_APPEARANCES > minPercentage)
      {
         ss << cAVERAGE_APPEARANCES << revPlIter->second.toString() << ", ";
      }
   }

   if (ss.str() == m_lastString)
   {
      if (false == m_lastString.empty())
      {
         m_settled = true;
         cout << "Settled: ";
      }
   }

   cout << ss.str() << endl;

   m_lastString = ss.str();
}
