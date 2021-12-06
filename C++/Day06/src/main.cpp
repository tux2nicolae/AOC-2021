/**
 * Advent of code 2021
 * @author : Nicolae Telechi
 */
#include <algorithm>
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

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          input = reader.ReadDataSeparatedByCharAs<int>();

  list<pair<long long, long long>> ocean;
  for (auto & value : input)
  {
    ocean.push_back(make_pair(value, 1));
  }

  int iterations = 256;
  while (iterations--)
  {
    long long newLanternfish = 0;
    for (auto & [lanternfish, count] : ocean)
    {
      if (lanternfish == 0)
      {
        newLanternfish += count;
        lanternfish = 7;
      }

      lanternfish--;
    }

    ocean.insert(ocean.end(), make_pair(8, newLanternfish));
  }

  long long totalLanternfish = 0;
  for (auto & [_, count] : ocean)
  {
    totalLanternfish += count;
  }

  cout << totalLanternfish;
  return 0;
}
