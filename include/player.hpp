#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <set>
#include <list>
#include <vector>
#include <string>


using namespace std;

enum Team_Ty
{
   teamANAHEIM,
   teamFIRST = teamANAHEIM,
   teamBOSTON,
   teamBUFFALO,
   teamCALGARY,
   teamCAROLINA,
   teamCHICAGO,
   teamCOLORADO,
   teamCOLUMBUS,
   teamDALLAS,
   teamDETROIT,
   teamEDMONTON,
   teamFLORIDA,
   teamLOS_ANGLES,
   teamMINNESOTA,
   teamMONTREAL,
   teamNASHVILLE,
   teamNEW_JERSEY,
   teamNY_ISLANDERS,
   teamNY_RANGERS,
   teamOTTAWA,
   teamPHILADELPHIA,
   teamPHOENIX,
   teamPITTSBURGH,
   teamSAN_JOSE,
   teamST_LOUIS,
   teamTAMPA_BAY,
   teamTORONTO,
   teamVANCOUVER,
   teamWASHINGTON,
   teamWINNIPEG,
   teamLAST,
   teamCOUNT = (teamLAST - teamFIRST)
};



enum Position_Ty
  {
    posC,
    posFIRST = posC,
    posLW,
    posRW,
    posD,
    posLAST,
    posCOUNT = (posLAST - posFIRST)
  };




// Create a player struct
struct Player_Ty
{

  Player_Ty()
    : m_name(),
      m_team(teamLAST),
      m_position()
  {}

  Player_Ty(const std::string& name,
	    const Team_Ty& team,  
	    const Position_Ty& position)
    : m_name(name),
      m_team(team),
      m_position()
  {
    m_position.insert(position);
  }

  Player_Ty(const std::string& name,
	    const Team_Ty& team,
	    const Position_Ty& position1,
	    const Position_Ty& position2)
    : m_name(name),
      m_team(team),
      m_position()
  {
    m_position.insert(position1);
    m_position.insert(position2);
  }


  const bool operator==(const Player_Ty& rh)
  {
    return ((m_name == rh.m_name) && (m_team == rh.m_team) && (m_position.size() == rh.m_position.size()));
  }
  
   const bool operator<(const Player_Ty& rh) const
   {
      bool lessThan = false;
      
      if (m_team < rh.m_team)
      {
         lessThan = true;
      }
      else if (m_team == rh.m_team)
      {
         if (m_position.size() < rh.m_position.size())
         {
            lessThan = true;
         }
         else if (m_position.size() == rh.m_position.size())
         {
            if (*m_position.begin() < *rh.m_position.begin())
            {
               lessThan = true;
            }
         }
      }

      return lessThan;
   }

  typedef std::vector<Player_Ty> Vector_Ty;
  
  typedef std::list<Player_Ty> List_Ty;

  std::string m_name;

  Team_Ty m_team;  

  std::set<Position_Ty> m_position;  

  std::string toString() const;
};


namespace Player_Ns
{
  Player_Ty::Vector_Ty getNewOffensePlayers();

  Player_Ty::Vector_Ty getNewForwardPlayers();

  Player_Ty::Vector_Ty getNewDefensePlayers();
};


#endif
