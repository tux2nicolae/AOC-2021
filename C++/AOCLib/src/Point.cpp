/**
 * Advent of code 2021
 * @author : Nicolae Telechi
 */
#include "pch.h"
#include "Point.h"

bool AOC::Point::operator==(const Point & second) const
{
  return tie(x, y, z, w) == tie(second.x, second.y, second.z, second.w);
}

bool AOC::Point::operator!=(const Point & second) const
{
  return !operator==(second);
}

bool AOC::Point::operator<(const Point & second) const
{
  return tie(x, y, z, w) < tie(second.x, second.y, second.z, second.w);
}

AOC::Point AOC::Point::operator+(const AOC::Point & second) const
{
  AOC::Point newPosition = *this;

  newPosition.x += second.x;
  newPosition.y += second.y;
  newPosition.z += second.z;
  newPosition.w += second.w;

  return newPosition;
}

AOC::Point AOC::Point::operator-(const AOC::Point & second) const
{
  AOC::Point newPosition = *this;

  newPosition.x -= second.x;
  newPosition.y -= second.y;
  newPosition.z -= second.z;
  newPosition.w -= second.w;

  return newPosition;
}

AOC::Point & AOC::Point::operator-=(const AOC::Point & second)
{
  x -= second.x;
  y -= second.y;
  z -= second.z;
  w -= second.w;

  return *this;
}

long long & AOC::Point::operator[](size_t pos)
{
  assert(pos >= 0 && pos <= 3);

  if (pos == 0)
    return x;
  else if (pos == 1)
    return y;
  else if (pos == 2)
    return z;
  else if (pos == 3)
    return w;

  static long long kInvalid;
  return kInvalid;
}

const long long & AOC::Point::operator[](size_t pos) const
{
  assert(pos >= 0 && pos <= 3);

  if (pos == 0)
    return x;
  else if (pos == 1)
    return y;
  else if (pos == 2)
    return z;
  else if (pos == 3)
    return w;

  static long long kInvalid;
  return kInvalid;
}

bool AOC::Point::IsInBoundary(const Point & from, const Point & to)
{
  return (x >= from.x && y >= from.y && z >= from.z && w >= from.w && x <= to.x && y <= to.y &&
          z <= to.z && w <= to.w);
}

AOC::Point AOC::Point::GetLeft()
{
  return { x - 1, y, z, w };
}

AOC::Point AOC::Point::GetRight()
{
  return { x + 1, y, z, w };
}

AOC::Point AOC::Point::GetTop()
{
  return { x, y - 1, z, w };
}

AOC::Point AOC::Point::GetBottom()
{
  return { x, y + 1, z, w };
}

AOC::Point AOC::Point::GetTopLeft()
{
  return GetTop().GetLeft();
}

AOC::Point AOC::Point::GetTopRight()
{
  return GetTop().GetRight();
}

AOC::Point AOC::Point::GetBottomLeft()
{
  return GetBottom().GetLeft();
}

AOC::Point AOC::Point::GetBottomRight()
{
  return GetBottom().GetRight();
}

AOC::Point AOC::Point::GetNeighbour(const char direction)
{
  switch (direction)
  {
  case '<':
  case 'L':
  case 'l':
  case 'W':
  case 'w':
    return GetLeft();
  case '>':
  case 'R':
  case 'r':
  case 'E':
  case 'e':
    return GetRight();
  case '^':
  case 'T':
  case 't':
  case 'N':
  case 'n':
  case 'U':
  case 'u':
    return GetTop();
  case 'v':
  case 'B':
  case 'b':
  case 'S':
  case 's':
  case 'D':
  case 'd':
    return GetBottom();
  default:
    assert("Invalid direction");
    return {};
  }
}

AOC::Point AOC::Point::GetNeighbour(const string & direction)
{
  auto neighbour = *this;
  for (auto to : direction)
    neighbour = neighbour.GetNeighbour(to);

  return neighbour;
}

vector<AOC::Point> AOC::Point::GetDirectNeighbours()
{
  return { GetTop(), GetRight(), GetBottom(), GetLeft() };
}

vector<AOC::Point> AOC::Point::GetAll2DNeighbours()
{
  return { GetTopLeft(), GetTop(),        GetTopRight(), GetLeft(),
           GetRight(),   GetBottomLeft(), GetBottom(),   GetBottomRight() };
}

vector<AOC::Point> AOC::Point::GetAll3DNeighbours() const
{
  vector<AOC::Point> neighbours;
  neighbours.reserve(26);

  AOC::Point nextSlice = *this;
  for (long long nextZ : { z - 1, z - 0, z + 1 })
  {
    nextSlice.z = nextZ;

    auto currentNeighbours = nextSlice.GetAll2DNeighbours();
    copy(begin(currentNeighbours), end(currentNeighbours), back_inserter(neighbours));
  }

  // neighbours
  nextSlice   = *this;
  nextSlice.z = z - 1;

  neighbours.push_back(nextSlice);

  nextSlice   = *this;
  nextSlice.z = z + 1;

  neighbours.push_back(nextSlice);

  return neighbours;
}

vector<AOC::Point> AOC::Point::GetAll4DNeighbours() const
{
  vector<AOC::Point> neighbours;
  neighbours.reserve(80);

  AOC::Point nextSlice = *this;
  for (long long nextW : { w - 1, w - 0, w + 1 })
  {
    nextSlice.w = nextW;

    auto currentNeighbours = nextSlice.GetAll3DNeighbours();
    copy(begin(currentNeighbours), end(currentNeighbours), back_inserter(neighbours));
  }

  // neighbours
  nextSlice   = *this;
  nextSlice.w = w - 1;

  neighbours.push_back(nextSlice);

  nextSlice   = *this;
  nextSlice.w = w + 1;

  neighbours.push_back(nextSlice);

  return neighbours;
}

void AOC::Point::RotateRight(const Point & origin)
{
  AOC::Point newPosition = *this;

  // translate to OXY
  newPosition.x -= origin.x;
  newPosition.y -= origin.y;
  newPosition.z -= origin.z;

  // rotate
  newPosition = { -1 * newPosition.y, newPosition.x, newPosition.z };

  // translate back
  newPosition.x += origin.x;
  newPosition.y += origin.y;
  newPosition.z += origin.z;

  *this = newPosition;
}

void AOC::Point::RotateLeft(const Point & origin)
{
  // 270 degree right rotation
  RotateRight(origin);
  RotateRight(origin);
  RotateRight(origin);
}

void AOC::Point::FlipX()
{
  x *= -1;
}

void AOC::Point::FlipY()
{
  y *= -1;
}

void AOC::Point::FlipZ()
{
  z *= -1;
}

//------------------------------------------------------------
