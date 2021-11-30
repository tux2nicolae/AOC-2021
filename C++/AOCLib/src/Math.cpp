/**
 * Advent of code 2021
 * @author : Nicolae Telechi
 */
#include "pch.h"
#include "Math.h"
#include "Point.h"

long long AOC::Abs(long long number)
{
  return number > 0 ? number : -number;
}

long long AOC::InvModulo(long long n, long long modulo)
{
  n = n % modulo;
  for (long long x = 1; x < modulo; x++)
    if (MultiplyModulo(n, x, modulo) == 1)
      return x;

  return 0;
}

long long AOC::PowModulo(long long a, long long b, long long modulo)
{
  if (a == 0)
    return 0;

  if (b == 0)
    return 1;

  if (b % 2 == 0)
  {
    long long half = PowModulo(a, b / 2, modulo);
    return AOC::MultiplyModulo(half, half, modulo);
  }
  else
  {
    long long previousPower = PowModulo(a, b - 1, modulo);
    return AOC::MultiplyModulo(previousPower, a, modulo);
  }
}

long long AOC::MultiplyModulo(long long a, long long b, long long modulo)
{
  long long res = 0;

  a %= modulo;

  while (b)
  {
    if (b % 2 == 1)
      res = (res + a) % modulo;

    a = (2 * a) % modulo;
    b = b / 2;
  }

  return res;
}
