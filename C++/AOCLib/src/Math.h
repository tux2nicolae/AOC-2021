#pragma once

/**
 * Advent of code 2021
 * @author : Nicolae Telechi
 */
namespace AOC
{
  struct Point;

  long long Abs(long long number);

  long long ManhattenDistance(long long x1, long long y1, long long x2, long long y2);
  long long ManhattenDistance(const Point & a, const Point& b);

  long long Cmmdc(long long n, long long m);
  long long Cmmmc(long long n, long long m);
}
