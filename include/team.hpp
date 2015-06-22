#ifndef TEAM_HPP
#define TEAM_HPP


#include "player.hpp"

namespace Team_Ns
{

   // The whole team.
   Player_Ty::List_Ty getMyTeam();
   
   // // A list of players who can't be kept.
   // Player_Ty::List_Ty getMustDropPlayers();   
   
   // // A list of players who are able to be kept next year.
   // Player_Ty::List_Ty getKeepablePlayers();      

   // // A list of probable keepers no more than 10.
   // Player_Ty::List_Ty getProbableKeepablePlayers();

   // A list of defense to keep
   Player_Ty::List_Ty getDefenseKeepers();

   // A list of offense to keep
   Player_Ty::List_Ty getOffenseKeepers();

}
#endif
