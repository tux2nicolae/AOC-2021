#pragma once

/**
 * Advent of code 2021
 * @author : Nicolae Telechi
 */
namespace AOC
{
  struct Point;

  long long Fibonaci(long long n, long long modulo);
  vector<bool> Eratosthenes(size_t n);

  /**
   * @returns length, begin index, end index
   */
  tuple<int, int, int> SubsequenceOfLargestSum(const vector<int> & sequence);
  vector<long long> GetPartialSums(const vector<long long>& sequence);

  /**
   * Huge numbers multiplication
   */
  long long MultiplyModulo(long long a, long long b, long long modulo);
  vector<vector<long long>> MultiplyMatrix(const vector<vector<long long>>& first,
    const vector<vector<long long>>& second, long long modulo);

  long long PowModulo(long long a, long long b, long long modulo);

  /**
   * Only coprime numbers (numbers that share no prime factors)
   */
  long long InvMod(long long n, long long modulo);

  /**
   * Lee algorithm
   */
  pair<vector<vector<int>>, set<int>> Lee(const vector<Point>& aCoordonates, vector<vector<int>>& aMap);
}
