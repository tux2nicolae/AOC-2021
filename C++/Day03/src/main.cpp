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
#include "../../AOCLib/src/Time.h"

int BinaryStringToInt(const string & binaryValue)
{
  return stoi(binaryValue, 0, 2);
};

pair<vector<int>, vector<int>> ComputeFrequencies(vector<string> & numbers)
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

int FindGenerator(vector<string> numbers)
{
  for (int i = 0; i < numbers[0].size(); i++)
  {
    auto [frequency0, frequency1] = ComputeFrequencies(numbers);

    auto mostFrequent = (frequency1[i] >= frequency0[i]) ? '1' : '0';

    numbers.erase(std::remove_if(numbers.begin(), numbers.end(),
                                 [=](const string & number)
                                 {
                                   return number[i] != mostFrequent;
                                 }),
                  numbers.end());

    if (numbers.size() == 1)
      return BinaryStringToInt(numbers[0]);
  }

  return -1;
}

int FindScrubber(vector<string> numbers)
{
  int scrubber = 0;
  for (int i = 0; i < numbers[0].size(); i++)
  {
    auto [frequency0, frequency1] = ComputeFrequencies(numbers);

    auto lessFrequent = (frequency1[i] < frequency0[i]) ? '1' : '0';

    numbers.erase(std::remove_if(numbers.begin(), numbers.end(),
                                 [=](const string & number)
                                 {
                                   return number[i] != lessFrequent;
                                 }),
                  numbers.end());

    if (numbers.size() == 1)
      return BinaryStringToInt(numbers[0]);
  }

  return -1;
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
