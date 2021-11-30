#pragma once

/**
 * Advent of code 2021
 * @author : Nicolae Telechi
 */
namespace AOC
{
  struct Point;

  long long Cmmdc(long long n, long long m);
  long long Cmmmc(long long n, long long m);

  long long Fibonaci(long long n, long long modulo);

  /**
   * prime numbers
   */
  vector<bool> Eratosthenes(size_t n);

  /**
   * @returns length, begin index, end index
   */
  tuple<int, int, int> SubsequenceOfLargestSum(const vector<int> & sequence);
  vector<long long> GetPartialSums(const vector<long long>& sequence);

  long long ManhattenDistance(long long x1, long long y1, long long x2, long long y2);
  long long ManhattenDistance(const Point& a, const Point& b);

  /**
   * Lee algorithm
   */
  pair<vector<vector<int>>, set<int>> Lee(const vector<Point>& aCoordonates, vector<vector<int>>& aMap);
}
