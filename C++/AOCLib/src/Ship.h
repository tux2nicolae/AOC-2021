#pragma once

#include "Point.h"

/**
 * Advent of code 2021
 * @author : Nicolae Telechi
 */
namespace AOC
{
struct Ship
{
  const char GetArrowDirection();
  void       SetArrowDirection(const char direction = '^');

  AOC::Point GetPosition();
  void       SetPosition(AOC::Point position);

  void TurnLeft();
  void TurnRight();

  // changes the direction
  void GoForward(long long step = 1);
  void GoBackward(long long step = 1);
  void GoRight(long long step = 1);
  void GoLeft(long long step = 1);

  // without changing direction
  void MoveNorth(long long step = 1);
  void MoveSouth(long long step = 1);
  void MoveEast(long long step = 1);
  void MoveWest(long long step = 1);

  AOC::Point GetFront(long long step = 1);
  AOC::Point GetBack(long long step = 1);
  AOC::Point GetRight(long long step = 1);
  AOC::Point GetLeft(long long step = 1);

  //----------------------------------------------

  char       direction{ '^' };
  AOC::Point position{ 0, 0 };
};
}  // namespace AOC
