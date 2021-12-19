/**
 * Advent of code 2021
 * @author : Nicolae Telechi
 */
#include "pch.h"
#include "Algorithm.h"
#include "Math.h"
#include "Point.h"

//--------------------------------------------------------------------------
// implementation details

namespace AOC::detail
{
vector<vector<long long>> FibonaciMatrix(long long n, long long modulo);
}

//--------------------------------------------------------------------------

long long AOC::Cmmdc(long long n, long long m)
{
  if (n == 0)
    return m;

  return Cmmdc(m % n, n);
}

long long AOC::Cmmmc(long long n, long long m)
{
  return (n * m) / Cmmdc(n, m);
}

long long AOC::Fibonaci(long long n, long long modulo)
{
  if (n == 0)
    return 0;

  auto fibonaciMatrix = detail::FibonaciMatrix(n - 1, modulo);
  return fibonaciMatrix[1][1];
}

std::vector<bool> AOC::Eratosthenes(size_t n)
{
  vector<bool> sieve;
  sieve.resize(n + 1);  // + 1 for n

  for (int i = 2; i <= sqrt(n); i++)
  {
    while (sieve[i])
      i++;

    for (int j = i * i; j <= n; j += i)
      sieve[j] = true;
  }

  return sieve;
}

tuple<int, int, int> AOC::SubsequenceOfLargestSum(const vector<int> & sequence)
{
  assert(sequence.size() > 1);

  // reserve +1 for a dummy element 0 witch will make our live easier, this will make
  // begin and end to point on the correct positions
  vector<int> sums;
  sums.reserve(sequence.size() + 1);
  sums.push_back(0);

  std::partial_sum(sequence.begin(), sequence.end(), back_inserter(sums));

  int smax      = std::numeric_limits<int>::min();
  int smaxbegin = 0, smaxend = 0;

  for (int beg = 0, end = 1; end < sums.size(); ++end)
  {
    if (sums[end] - sums[beg] > smax)
    {
      smax      = sums[end] - sums[beg];
      smaxbegin = beg;
      smaxend   = end;
    }

    // longest or shortest <=
    if (sums[end] < sums[beg])
      beg = end;
  }

  return make_tuple(smax, smaxbegin, smaxend);
}

vector<long long> AOC::GetPartialSums(const vector<long long> & sequence)
{
  vector<long long> sums;
  sums.reserve(sequence.size());

  std::partial_sum(sequence.begin(), sequence.end(), back_inserter(sums));

  return sums;
}

long long AOC::ManhattenDistance(long long x1, long long y1, long long x2, long long y2)
{
  return Abs(x1 - x2) + Abs(y1 - y2);
}

long long AOC::ManhattenDistance(const Point & a, const Point & b)
{
  return Abs(a.x - b.x) + Abs(a.y - b.y) + Abs(a.z - b.z) + Abs(a.w - b.w);
}

vector<vector<long long>> AOC::MultiplyMatrix(const vector<vector<long long>> & first,
                                              const vector<vector<long long>> & second,
                                              long long                         modulo)
{
  assert(first.size() != 0);
  assert(first.size() == second.size());
  assert(first[0].size() == second[0].size());

  for (int i = 0; i < first.size(); ++i)
  {
    assert(first[i].size() == first[0].size());
    assert(second[i].size() == first[0].size());
  }

  //------------------------------------------------------------------------

  size_t                    matrixSize = first.size();
  vector<vector<long long>> temp;

  temp.resize(matrixSize);
  for (auto & row : temp)
    row.resize(matrixSize);

  for (int i = 0; i < matrixSize; i++)
  {
    for (int j = 0; j < matrixSize; j++)
    {
      for (int k = 0; k < matrixSize; k++)
      {
        temp[i][j] = (MultiplyModulo(first[i][k], second[k][j], modulo) + temp[i][j]) % modulo;
      }
    }
  }

  return temp;
}

pair<vector<vector<int>>, set<int>> AOC::Lee(const vector<Point> & aCoordonates,
                                             vector<vector<int>> & aMap)
{
  set<int> infinitePoints;

  vector<vector<int>> distances;
  distances.resize(aMap.size());
  for (auto & line : distances)
    line.resize(aMap[0].size());

  queue<Point> unvisited;
  for (const auto & startingPoint : aCoordonates)
    unvisited.push(startingPoint);

  auto isInBoundary = [&](const Point & to) -> bool
  {
    return !(to.x < 0 || to.y < 0 || to.x >= static_cast<int>(aMap.size()) ||
             to.y >= static_cast<int>(aMap[0].size()));
  };

  // run
  while (!unvisited.empty())
  {
    auto from = unvisited.front();
    unvisited.pop();

    if (aMap[from.x][from.y] == -1)
      continue;

    static const int directionX[4] = { -1, 0, 1, 0 };
    static const int directionY[4] = { 0, 1, 0, -1 };

    for (int i = 0; i < 4; ++i)
    {
      Point to;
      to.x = from.x + directionX[i];
      to.y = from.y + directionY[i];

      if (!isInBoundary(to))
      {
        infinitePoints.insert(aMap[from.x][from.y]);
        continue;
      }

      if (aMap[to.x][to.y])
      {
        if (distances[to.x][to.y] == distances[from.x][from.y] + 1 &&
            aMap[from.x][from.y] != aMap[to.x][to.y])
          aMap[to.x][to.y] = -1;

        continue;
      }

      aMap[to.x][to.y]      = aMap[from.x][from.y];
      distances[to.x][to.y] = distances[from.x][from.y] + 1;

      unvisited.push(to);
    }
  }

  return { distances, infinitePoints };
}

//--------------------------------------------------------------------------------
// implementation details

namespace AOC::detail
{
vector<vector<long long>> FibonaciMatrix(long long n, long long modulo)
{
  static const vector<vector<long long>> kFibonaci{ { 0, 1 }, { 1, 1 } };

  if (n == 0)
  {
    return { { 1, 0 }, { 0, 1 } };
  }
  else if (n == 1)
  {
    return kFibonaci;
  }

  auto result = FibonaciMatrix(n / 2, modulo);
  if (n % 2 == 0)
  {
    return AOC::MultiplyMatrix(result, result, modulo);
  }
  else
  {
    return AOC::MultiplyMatrix(AOC::MultiplyMatrix(result, result, modulo), kFibonaci, modulo);
  }
}
}  // namespace AOC::detail
