/**
 * Advent of code 2021
 * @author : Nicolae Telechi
 */
#include <algorithm>
#include <assert.h>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#include "../../AOCLib/src/Algorithm.h"
#include "../../AOCLib/src/FStreamReader.h"
#include "../../AOCLib/src/FStreamWriter.h"
#include "../../AOCLib/src/Math.h"
#include "../../AOCLib/src/Parse.h"
#include "../../AOCLib/src/Point.h"
#include "../../AOCLib/src/Ship.h"
#include "../../AOCLib/src/Time.h"

void GetNext(AOC::Point & probe, AOC::Point & velocity)
{
  probe += velocity;

  if (velocity.x > 0)
  {
    velocity.x -= 1;
  }
  else if (velocity.x < 0)
  {
    velocity.x += 1;
  }

  velocity.y -= 1;

  // assert(velocity.y >= 0);
}

optional<long long> Shut(AOC::Point point,
                         AOC::Point velocity,
                         AOC::Point minTarget,
                         AOC::Point maxTarget)
{
  long long currentMaxHeight = 0;
  while (point.y >= minTarget.y)
  {
    currentMaxHeight = max(currentMaxHeight, point.y);

    if (point.IsInBoundary(minTarget, maxTarget))
    {
      return currentMaxHeight;
    }

    GetNext(point, velocity);
  }

  return nullopt;
}

long long Solve(AOC::Point minTarget, AOC::Point maxTarget)
{
  long long maxHeight = 0;

  for (int i = 1; i <= 100; i++)
  {
    for (int j = 1; j <= 100; j++)
    {
      AOC::Point point{ 0, 0 };
      AOC::Point velocity{ i, j };

      auto localMax = Shut({ 0, 0 }, { i, j }, minTarget, maxTarget);
      if (localMax)
      {
        maxHeight = max(maxHeight, *localMax);
      }
    }
  }

  return maxHeight;
}

long long Part2(AOC::Point minTarget, AOC::Point maxTarget)
{
  long long totalSum = 0;

  for (int i = 0; i <= 400; i++)
  {
    for (int j = -100; j <= 500; j++)
    {
      AOC::Point point{ 0, 0 };
      AOC::Point velocity{ i, j };

      if (Shut({ 0, 0 }, { i, j }, minTarget, maxTarget))
        totalSum++;
    }
  }

  return totalSum;
}

int main()
{
  ifstream in("..\\src\\_input.in");
  // ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);

  string input;
  getline(in, input);

  auto matches = AOC::ExtractMatches(input, "target area: x=(.*)\\.\\.(.*), y=(.*)\\.\\.(.*)");
  assert(matches.size() == 5);

  auto x1 = stoi(matches[1]);
  auto x2 = stoi(matches[2]);

  auto y1 = stoi(matches[3]);
  auto y2 = stoi(matches[4]);

  AOC::Point minTarget{ min(x1, x2), min(y1, y2) };
  AOC::Point maxTarget{ max(x1, x2), max(y1, y2) };

  // auto result = Shut({ 0, 0 }, { 6, 9 }, minTarget, maxTarget);
  auto result  = Solve(minTarget, maxTarget);
  auto result2 = Part2(minTarget, maxTarget);

  return 0;
}
