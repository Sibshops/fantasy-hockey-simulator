#ifndef WEEK_HPP
#define WEEK_HPP

#include <set>
#include <vector>
#include <sstream>

#include "nameConversion.hpp"



// Position per day.
struct DailyPosition_Ty
{
  // The schedule for the week.
  typedef std::vector<DailyPosition_Ty> Vector_Ty;

  Player_Ty f1;
  Player_Ty f2;

  Player_Ty c1;
  Player_Ty c2;

  Player_Ty lw1;
  Player_Ty lw2;

  Player_Ty rw1;
  Player_Ty rw2;

  Player_Ty d1;
  Player_Ty d2;
  Player_Ty d3;
  Player_Ty d4;

   Player_Ty g1;
   Player_Ty g2;

  void printPlayers() const;

  int countPlayers() const;

  int countForwards() const;

  int countDefense() const;

  int countGoalie() const;
};

/*
struct WeeklyPosition_Ty
{
  WeeklyPosition_Ty() 
    : week()
  {
    week.resize(7);
  }

  DailyPosition_Ty::Vector_Ty week;  
};
*/

// *****************************************************************************
// Daily Position

inline void DailyPosition_Ty::printPlayers() const
{
  std::cout << "f1 " << f1.toString() << std::endl;
  std::cout << "f2 " << f2.toString() << std::endl;

  std::cout << "c1 " << c1.toString() << std::endl;
  std::cout << "c2 " << c2.toString() << std::endl;

  std::cout << "lw1 " << lw1.toString() << std::endl;
  std::cout << "lw2 " << lw2.toString() << std::endl;

  std::cout << "rw1 " << rw1.toString() << std::endl;
  std::cout << "rw2 " << rw2.toString() << std::endl;

  std::cout << "d1 " << d1.toString() << std::endl;
  std::cout << "d2 " << d2.toString() << std::endl;
  std::cout << "d3 " << d3.toString() << std::endl;
  std::cout << "d4 " << d4.toString() << std::endl;
}

inline int DailyPosition_Ty::countForwards() const
{
  int total = 0;

  if (teamLAST != f1.m_team)
    {
      ++total;
    }
  if (teamLAST != f2.m_team)
    {
      ++total;
    }

  if (teamLAST != c1.m_team)
    {
      ++total;
    }
  if (teamLAST != c2.m_team)
    {
      ++total;
    }

  if (teamLAST != lw1.m_team)
    {
      ++total;
    }
  if (teamLAST != lw2.m_team)
    {
      ++total;
    }

  if (teamLAST != rw1.m_team)
    {
      ++total;
    }
  if (teamLAST != rw2.m_team)
    {
      ++total;
    }

  return (total);
}


inline int DailyPosition_Ty::countDefense() const
{
  int total = 0;

  if (teamLAST != d1.m_team)
    {
      ++total;
    }
  if (teamLAST != d2.m_team)
    {
      ++total;
    }
  if (teamLAST != d3.m_team)
    {
      ++total;
    }
  if (teamLAST != d4.m_team)
    {
      ++total;
    }

  return (total);
}


inline int DailyPosition_Ty::countGoalie() const
{
  int total = 0;

  if (teamLAST != g1.m_team)
    {
      ++total;
    }
  if (teamLAST != g2.m_team)
    {
      ++total;
    }

  return (total);
}


inline int DailyPosition_Ty::countPlayers() const
{
   return (countForwards() + countDefense() + countGoalie());
}


#endif
