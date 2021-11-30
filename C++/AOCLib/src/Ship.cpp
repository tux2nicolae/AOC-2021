/**
 * Advent of code 2021
 * @author : Nicolae Telechi
 */
#include "pch.h"
#include "Ship.h"

const char AOC::Ship::GetArrowDirection()
{
  return direction;
}

void AOC::Ship::SetArrowDirection(const char direction)
{
  assert(direction == '^' || direction == '>' || direction == 'v' || direction == '<');
  this->direction = direction;
}

AOC::Point AOC::Ship::GetPosition()
{
  return position;
}

void AOC::Ship::SetPosition(AOC::Point position)
{
  this->position = position;
}

void AOC::Ship::TurnLeft()
{
  switch (direction)
  {
  case '^':
    direction = '<';
    break;
  case '<':
    direction = 'v';
    break;
  case 'v':
    direction = '>';
    break;
  case '>':
    direction = '^';
    break;
  default:
    break;
  }
}

void AOC::Ship::TurnRight()
{
  switch (direction)
  {
  case '^':
    direction = '>';
    break;
  case '>':
    direction = 'v';
    break;
  case 'v':
    direction = '<';
    break;
  case '<':
    direction = '^';
    break;
  default:
    break;
  }
}

void AOC::Ship::GoForward(long long step)
{
  if (direction == '^')
  {
    position.y -= step;
  }
  else if (direction == '>')
  {
    position.x += step;
  }
  else if (direction == 'v')
  {
    position.y += step;
  }
  else if (direction == '<')
  {
    position.x -= step;
  }
}

void AOC::Ship::GoBackward(long long step)
{
  GoForward(-step);
}

void AOC::Ship::GoRight(long long step)
{
  TurnRight();
  GoForward(step);
}

void AOC::Ship::GoLeft(long long step)
{
  TurnLeft();
  GoForward(step);
}

void AOC::Ship::MoveNorth(long long step)
{
  position.y -= step;
}

void AOC::Ship::MoveSouth(long long step)
{
  position.y += step;
}

void AOC::Ship::MoveEast(long long step)
{
  position.x += step;
}

void AOC::Ship::MoveWest(long long step)
{
  position.x -= step;
}

AOC::Point AOC::Ship::GetFront(long long step)
{
  AOC::Ship front = *this;
  front.MoveForward(step);

  return front.GetPosition();
}

AOC::Point AOC::Ship::GetBack(long long step)
{
  return GetFront(-step);
}

AOC::Point AOC::Ship::GetRight(long long step)
{
  AOC::Ship right = *this;
  right.MoveRight(step);

  return right.GetPosition();
}

AOC::Point AOC::Ship::GetLeft(long long step)
{
  return GetRight(-step);
}

