#include "team.hpp"
#include <iostream>


Player_Ty::List_Ty Team_Ns::getMyTeam()
{
   // A list of players who can't be kept.
   Player_Ty::List_Ty team;
     
   team.push_back(Player_Ty("Abdelkader", teamDETROIT, posLW));
   team.push_back(Player_Ty("Atkinson", teamCOLUMBUS, posRW));
   // team.push_back(Player_Ty("Beleskey", teamANAHEIM, posLW));
   team.push_back(Player_Ty("Gionta", teamBUFFALO, posLW));
   team.push_back(Player_Ty("D. Sedin", teamVANCOUVER, posLW));   
   team.push_back(Player_Ty("Downie", teamPITTSBURGH, posLW, posRW));
   team.push_back(Player_Ty("St. Louis", teamNY_RANGERS, posRW, posC));
   team.push_back(Player_Ty("McLeod", teamCOLORADO, posLW));
   team.push_back(Player_Ty("Sharp", teamCHICAGO, posLW));
   team.push_back(Player_Ty("Silfverberg", teamANAHEIM, posRW));
   team.push_back(Player_Ty("Spezza", teamDALLAS, posC));
   team.push_back(Player_Ty("Toews", teamCHICAGO, posC));
   team.push_back(Player_Ty("Williams", teamLOS_ANGLES, posRW));
   team.push_back(Player_Ty("Zuccarello", teamNY_RANGERS, posRW));
   
   // team.push_back(Player_Ty("Hedman", teamTAMPA_BAY, posD));
   team.push_back(Player_Ty("Hjalmarsson,", teamCHICAGO, posD));
   team.push_back(Player_Ty("McDonagh", teamNY_RANGERS, posD));
   team.push_back(Player_Ty("Lindholm", teamANAHEIM , posD));
   team.push_back(Player_Ty("Phaneuf", teamTORONTO, posD));
   team.push_back(Player_Ty("Edler", teamVANCOUVER , posD));
   
   
// IR
   
   
   if (team.size() != 19)
   {
      cout << "Not right number of players, has " << team.size() << endl;
   }

   return team;   
}

Player_Ty::List_Ty Team_Ns::getDefenseKeepers()
{
  Player_Ty::List_Ty team;

  return team;
}


Player_Ty::List_Ty Team_Ns::getOffenseKeepers()
{
  Player_Ty::List_Ty team;

  
  return team;
}


