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
  // ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          input = reader.ReadDataSeparatedByCharAs<int>();

  int minFuel = numeric_limits<int>::max();

  for (int target = 0; target <= *max_element(begin(input), end(input)); target++)
  {
    int s = 0;
    for (auto crab : input)
    {
      long long distance = abs(crab - target);
      long long fuel     = (distance * (distance + 1)) / 2;

      s += fuel;
    }

    minFuel = min(minFuel, s);
  }

  cout << minFuel;

  // out
  // FStreamWriter writer(out);
  // writer.WriteVector(v);

  return 0;
}
