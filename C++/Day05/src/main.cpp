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

  map<AOC::Point, int> values;

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

    AOC::Point step{ 0, 0 };

    if (from.x < to.x)
      step.x = 1;
    else if (from.x > to.x)
      step.x = -1;

    if (from.y < to.y)
      step.y = 1;
    else if (from.y > to.y)
      step.y = -1;

    for (; from != to; from += step)
    {
      values[from]++;
    }

    values[to]++;
  }

  int overlappedValues = count_if(begin(values), end(values),
                                  [](auto & val)
                                  {
                                    return val.second >= 2;
                                  });

  cout << overlappedValues;

  // out
  // FStreamWriter writer(out);
  // writer.WriteVector(v);

  return 0;
}
