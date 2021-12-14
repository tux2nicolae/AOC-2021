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

  auto input = reader.ReadLines();

  map<string, int> prevInsertionsCount;

  int n = 20;
  while (n--)
  {
    map<string, int> insertionsCount;
    map<int, string> insertions;
    for (auto line : input)
    {
      auto matches = AOC::ExtractMatches(line, "(.*) -> (.*)");
      assert(matches.size() == 3);

      auto from = matches[1];
      auto to   = matches[2];

      auto pos = polymer.find(from, 0);
      while (pos != string::npos)
      {
        insertions[pos] = to;
        insertionsCount[to]++;

        pos = polymer.find(from, pos + 1);
      }
    }

    out << "Total :" << insertions.size() << endl;
    for (auto [_, freqency] : insertionsCount)
    {
      out << prevInsertionsCount[_] * 2 - freqency << " ";
    }

    prevInsertionsCount = insertionsCount;
    out << endl;

    for (auto it = insertions.rbegin(); it != insertions.rend(); it++)
    {
      auto & [pos, to] = *it;
      polymer.insert(pos + 1, to);
    }

    out << polymer << endl;

    map<char, int> freq;
    for (auto c : polymer)
      freq[c]++;

    // FC

    vector<int> frequencies;
    // for (auto [_, freqency] : freq)
    //{
    //   out << _ << "(" << freqency << ") ";
    //   frequencies.push_back(freqency);
    // }

    sort(begin(frequencies), end(frequencies));

    FStreamWriter writer(out);
    // writer.WriteVector(frequencies);
    out << endl;

    // auto [minElement, maxElement] = minmax_element(begin(frequencies), end(frequencies));
    // out << *minElement << " " << *maxElement << endl;
  }

  return 0;
}
