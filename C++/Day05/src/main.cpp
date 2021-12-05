/**
 * Advent of code 2021
 * @author : Nicolae Telechi
 */
#include <algorithm>
#include <fstream>
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
#include "../../AOCLib/src/Time.h"

int main()
{
  ifstream in("..\\src\\_input.in");
  // ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          v = reader.ReadLines();

  map<AOC::Point, int> count;

  for (auto & line : v)
  {
    auto data = AOC::ExtractMatches(line, "(.*),(.*) -> (.*),(.*)");

    AOC::Point from{
      atoi(data[1].c_str()),
      atoi(data[2].c_str()),
    };

    AOC::Point to{
      atoi(data[3].c_str()),
      atoi(data[4].c_str()),
    };

    // part 1
    if (from.x == to.x || from.y == to.y)
    {
      for (int i = min(from.x, to.x); i <= max(from.x, to.x); i++)
      {
        for (int j = min(from.y, to.y); j <= max(from.y, to.y); j++)
        {
          count[AOC::Point{ i, j }]++;
        }
      }
    }
    // part 2
    else
    {
      AOC::Point step{ 0, 0 };

      if (from.x < to.x)
        step.x = 1;
      else
        step.x = -1;

      if (from.y < to.y)
        step.y = 1;
      else
        step.y = -1;

      for (int i = from.x, j = from.y; i != to.x && j != to.y; i += step.x, j += step.y)
      {
        count[AOC::Point{ i, j }]++;
      }

      count[to]++;
    }
  }

  int overlappedValues = 0;
  for (auto & [_, val] : count)
  {
    if (val >= 2)
      overlappedValues++;
  }

  cout << overlappedValues;

  // out
  // FStreamWriter writer(out);
  // writer.WriteVector(v);

  return 0;
}
