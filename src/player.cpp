#include <sstream>

#include "player.hpp"
#include "nameConversion.hpp"


static char cPOS_NAME[20][20] =
  {
    "C",
    "LW",
    "RW",
    "D",
    "Out of range"
  };
  
std::string Player_Ty::toString() const
{

  std::stringstream ss;
  
  ss << m_name << " " << NameConversion_Ty::getName(m_team);

  for (std::set<Position_Ty>::const_iterator posIter = m_position.begin();
       posIter != m_position.end();
       ++posIter)
    {
      ss << " " << cPOS_NAME[*posIter];
    }
  
  return (ss.str());
}



Player_Ty::Vector_Ty Player_Ns::getNewOffensePlayers()
{
  Player_Ty::Vector_Ty newPlayers;

  for (int posIndex = 0; posIndex < posLAST; ++posIndex)
  {
     for (int teamIndex = 0; teamIndex < teamLAST; ++teamIndex)
     {      
        // Add player from this team
        Player_Ty newPlayer;
        newPlayer.m_name = "";
        newPlayer.m_team = static_cast<Team_Ty>(teamIndex);
        newPlayer.m_position.insert(static_cast<Position_Ty>(posIndex));

        newPlayers.push_back(newPlayer); 
     }
  }
  
  return (newPlayers);
}


Player_Ty::Vector_Ty Player_Ns::getNewForwardPlayers()
{
   Player_Ty::Vector_Ty newPlayers;

   for (int teamIndex = 0; teamIndex < teamLAST; ++teamIndex)
   {
      for (int posIndex = 0; posIndex < posD; ++posIndex)
      {

         // Add player from this team
         Player_Ty newPlayer;
         newPlayer.m_name = "";
         newPlayer.m_team = static_cast<Team_Ty>(teamIndex);
         newPlayer.m_position.insert(static_cast<Position_Ty>(posIndex));

	     newPlayers.push_back(newPlayer); 
      }
   }
  
   return (newPlayers);
}


Player_Ty::Vector_Ty Player_Ns::getNewDefensePlayers()
{
   Player_Ty::Vector_Ty newPlayers;

   for (int teamIndex = 0; teamIndex < teamLAST; ++teamIndex)
   {
      // Add player from this team
      Player_Ty newPlayer;
      newPlayer.m_name = "";
      newPlayer.m_team = static_cast<Team_Ty>(teamIndex);
      newPlayer.m_position.insert(posD);

      newPlayers.push_back(newPlayer); 
   }

   return (newPlayers);
}
