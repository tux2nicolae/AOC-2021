#pragma once

/**
 * Advent of code 2021
 * @author : Nicolae Telechi
 */
namespace AOC
{
  struct Point;

  long long Abs(long long number);

  /**
   * Only coprime numbers (numbers that share no prime factors)
   */
  long long InvModulo(long long n, long long modulo);

  long long PowModulo(long long a, long long b, long long modulo);
  long long MultiplyModulo(long long a, long long b, long long modulo);

  vector<vector<long long>> MultiplyMatrix(const vector<vector<long long>>& first,
      const vector<vector<long long>>& second, long long modulo);
}
