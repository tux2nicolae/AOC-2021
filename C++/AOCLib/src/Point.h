#pragma once

/**
 * Advent of code 2021
 * @author : Nicolae Telechi
 */
namespace AOC
{
struct Point
{
  bool operator==(const Point & second) const;
  bool operator!=(const Point & second) const;
  bool operator<(const Point & second) const;

  Point   operator+(const Point & second);
  Point & operator+=(const Point & second);

  bool IsInBoundary(const Point & from, const Point & to);

  Point GetLeft();
  Point GetRight();
  Point GetTop();
  Point GetBottom();

  Point GetTopLeft();
  Point GetTopRight();
  Point GetBottomLeft();
  Point GetBottomRight();

  Point GetNeighbour(const char direction);
  Point GetNeighbour(const string & direction);

  vector<Point> GetDirectNeighbours();
  vector<Point> GetAll2DNeighbours();
  vector<Point> GetAll3DNeighbours() const;
  vector<Point> GetAll4DNeighbours() const;

  void RotateRight(const Point & origin = { 0, 0 });
  void RotateLeft(const Point & origin = { 0, 0 });

  long long x{ 0 };
  long long y{ 0 };
  long long z{ 0 };
  long long w{ 0 };
};

template <typename T = long long, typename... Args>
Point MakePoint(Args... args)
{
  return Point{ static_cast<T>(args)... };
};
}  // namespace AOC
