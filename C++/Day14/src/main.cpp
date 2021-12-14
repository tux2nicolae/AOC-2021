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

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);

  string polymer, _;
  getline(in, polymer);
  getline(in, _);

  unordered_map<string, string>         toChar;
  unordered_map<string, vector<string>> toPairs;

  for (auto line : reader.ReadLines())
  {
    assert(!line.empty());

    auto matches = AOC::ExtractMatches(line, "(.*) -> (.*)");
    assert(matches.size() == 3);

    auto from = matches[1];
    auto to   = matches[2];

    auto toFirst  = string(1, from[0]) + to;
    auto toSecond = to + string(1, from[1]);

    toPairs[from].push_back(toFirst);
    toPairs[from].push_back(toSecond);

    toChar[from] = to;
  }

  unordered_map<string, long long> pairs;
  for (int i = 0; i < polymer.size() - 1; i++)
  {
    pairs[string(1, polymer[i]) + string(1, polymer[i + 1])]++;
  }

  map<string, long long> totalCount;
  for (auto c : polymer)
  {
    totalCount[string(1, c)]++;
  }

  for (int i = 0; i < 40; i++)
  {
    unordered_map<string, long long> newPairs;
    for (auto [from, count] : pairs)
    {
      for (auto to : toPairs[from])
      {
        newPairs[to] += count;
      }

      totalCount[toChar[from]] += count;
    }

    pairs = newPairs;
  }

  auto [minElement, maxElement] = minmax_element(begin(totalCount), end(totalCount),
                                                 [](auto a, auto b)
                                                 {
                                                   return a.second < b.second;
                                                 });

  cout << maxElement->second - minElement->second;

  return 0;
}
