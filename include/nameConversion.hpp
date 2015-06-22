
#include <string.h>
#include <iostream>

#ifndef NAMECONVERSION_HPP
#define NAMECONVERSION_HPP

#include "player.hpp"


const char cTEAM_NAMES[50][50] =
  {
    "Anaheim",
    "Boston",
    "Buffalo",
    "Calgary",
    "Carolina",
    "Chicago",
    "Colorado",
    "Columbus",
    "Dallas",
    "Detroit",
    "Edmonton",
    "Florida",
    "Los Angeles",
    "Minnesota",
    "Montreal",
    "Nashville",
    "New Jersey",
    "Ny Islanders",
    "Ny Rangers",
    "Ottawa",
    "Philadelphia",
    //"Phoenix",
    "Arizona",
    "Pittsburgh",
    "San Jose",
    "St. Louis",
    "Tampa Bay",
    "Toronto",
    "Vancouver",
    "Washington",
    "Winnipeg",
  };


namespace NameConversion_Ty
{
  static Team_Ty getTeam(const char* teamName) 
  {
    // The return team.
    Team_Ty team = teamLAST;
  
    for (int i = teamFIRST; i < teamLAST; ++i)
      {
	if(0 == strcasecmp(teamName, cTEAM_NAMES[i]))
	  {
	    team = static_cast<Team_Ty>(i);
	  }
      }

    if (teamLAST == team)
      {
	std::cout << "No match for team" << teamName << std::endl;
      }

    return (team);
  }


  static const char* getName(const Team_Ty team)
  {
    return (cTEAM_NAMES[team]);
  }

}
#endif
