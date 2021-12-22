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

struct Interval
{
  bool on;

  AOC::Point from;
  AOC::Point to;
};

vector<Interval> DifferenceOnAxis(const Interval & onInterval,
                                  const Interval & offInterval,
                                  size_t           axe)
{
  vector<Interval> resultIntervals;

  if ((onInterval.from[axe] <= offInterval.from[axe] &&
       offInterval.from[axe] <= onInterval.to[axe]) ||
      (onInterval.from[axe] <= offInterval.to[axe] && offInterval.to[axe] <= onInterval.to[axe]))
  {
    // two resulting intervals
    if (onInterval.from[axe] < offInterval.from[axe] && offInterval.to[axe] < onInterval.to[axe])
    {
      auto beforeInterval    = onInterval;
      beforeInterval.to[axe] = offInterval.from[axe] - 1;

      resultIntervals.push_back(beforeInterval);

      auto afterInterval      = onInterval;
      afterInterval.from[axe] = offInterval.to[axe] + 1;

      resultIntervals.push_back(afterInterval);
    }
    // one resulting interval
    else
    {
      if (onInterval.from[axe] < offInterval.from[axe])
      {
        auto beforeInterval    = onInterval;
        beforeInterval.to[axe] = offInterval.from[axe] - 1;

        resultIntervals.push_back(beforeInterval);
      }
      else if (offInterval.to[axe] < onInterval.to[axe])
      {
        auto afterInterval      = onInterval;
        afterInterval.from[axe] = offInterval.to[axe] + 1;

        resultIntervals.push_back(afterInterval);
      }
      else
      {
        // equal
      }
    }
  }
  else if (offInterval.from[axe] <= onInterval.from[axe] &&
           onInterval.to[axe] <= offInterval.to[axe])
  {
    // zero resulting intervals
  }
  else
  {
    resultIntervals.push_back(onInterval);
  }

  return resultIntervals;
}

vector<Interval> TurnOffInterval(const vector<Interval> & intervals, const Interval & offInterval)
{
  vector<Interval> resultIntervals;

  for (const auto & onInterval : intervals)
  {
    vector<Interval> newIntervals;

    for (size_t axe = 0; axe < 3; axe++)
    {
      const auto & diff = DifferenceOnAxis(onInterval, offInterval, axe);
      for (const auto & newInterval : diff)
      {
        newIntervals = TurnOffInterval(newIntervals, newInterval);
        newIntervals.push_back(newInterval);
      }
    }

    resultIntervals.insert(resultIntervals.end(), newIntervals.begin(), newIntervals.end());
  }

  return resultIntervals;
}

int main()
{
  ifstream in("..\\src\\_input.in");
  // ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          input = reader.ReadLines();

  vector<Interval> allIntervals;

  for (auto line : input)
  {
    auto matches =
      AOC::ExtractMatches(line, "(.*) x=(.*)\\.\\.(.*),y=(.*)\\.\\.(.*),z=(.*)\\.\\.(.*)");

    assert(matches.size() == 8);

    AOC::Point from{ stoi(matches[2]), stoi(matches[4]), stoi(matches[6]) };
    AOC::Point to{ stoi(matches[3]), stoi(matches[5]), stoi(matches[7]) };

    allIntervals.push_back({ matches[1] == "on", from, to });
  }

  vector<Interval> resultIntervals;
  for (auto & interval : allIntervals)
  {
    if (interval.on)
    {
      // turn off then turn on again
      resultIntervals = TurnOffInterval(resultIntervals, interval);
      resultIntervals.push_back(interval);
    }
    else
    {
      // turn them all off
      resultIntervals = TurnOffInterval(resultIntervals, interval);
    }
  }

  auto cubeSize = [](const Interval & interval) -> long long
  {
    long long n = AOC::Abs(interval.from.x - interval.to.x) + 1;
    long long m = AOC::Abs(interval.from.y - interval.to.y) + 1;
    long long h = AOC::Abs(interval.from.z - interval.to.z) + 1;

    return n * m * h;
  };

  long long sum = 0;
  for (const auto & interval : resultIntervals)
  {
    sum += cubeSize(interval);
  }

  cout << sum;

  return 0;
}
