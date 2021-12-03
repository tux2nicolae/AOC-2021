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
#include "../../AOCLib/src/Time.h"

pair<vector<int>, vector<int>> ComputeFrequencies(const vector<string> & numbers)
{
  vector<int> frequency0;
  vector<int> frequency1;

  frequency0.resize(numbers[0].size());
  frequency1.resize(numbers[0].size());

  for (auto bit : numbers)
  {
    for (int i = 0; i < bit.size(); i++)
    {
      if (bit[i] == '0')
        frequency0[i]++;
      else
        frequency1[i]++;
    }
  }

  return make_pair(frequency0, frequency1);
}

int Find(vector<string> numbers, function<bool(int, int)> excludeCriteria)
{
  for (int i = 0; i < numbers[0].size(); i++)
  {
    auto [frequency0, frequency1] = ComputeFrequencies(numbers);

    auto exclude = excludeCriteria(frequency0[i], frequency1[i]);

    numbers.erase(std::remove_if(numbers.begin(), numbers.end(),
                                 [=](const string & number)
                                 {
                                   return number[i] == (exclude ? '1' : '0');
                                 }),
                  numbers.end());

    if (numbers.size() == 1)
      return AOC::BinaryStringToInt(numbers[0]);
  }

  return -1;
}

int FindGenerator(const vector<string> & numbers)
{
  return Find(numbers,
              [](int frequency0, int frequency1)
              {
                return frequency0 > frequency1;
              });
}

int FindScrubber(const vector<string> & numbers)
{
  return Find(numbers,
              [](int frequency0, int frequency1)
              {
                return frequency0 <= frequency1;
              });
}

int main()
{
  ifstream in("..\\src\\_input.in");
  // ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          input = reader.ReadLines();

  // part 1
  {
    auto [frequency0, frequency1] = ComputeFrequencies(input);

    int gama    = 0;
    int epsilon = 0;

    for (int i = 0; i < frequency0.size(); i++)
    {
      gama    = (gama << 1) | (frequency1[i] > frequency0[i]);
      epsilon = (epsilon << 1) | (frequency1[i] <= frequency0[i]);
    }

    cout << gama * epsilon << endl;
  }

  // part 2
  {
    int generator = FindGenerator(input);
    int scrubber  = FindScrubber(input);

    cout << generator * scrubber;
  }

  return 0;
}
