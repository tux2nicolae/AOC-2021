/**
 * Advent of code 2021
 * @author : Nicolae Telechi
 */
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <set>
#include <unordered_map>
#include <optional>
#include <numeric>

using namespace std;

#include "../../AOCLib/src/Algorithm.h"
#include "../../AOCLib/src/FStreamReader.h"
#include "../../AOCLib/src/FStreamWriter.h"
#include "../../AOCLib/src/Math.h"
#include "../../AOCLib/src/Time.h"

void ComputeFrequencies(vector<vector<int>> & v, vector<int> & frequency0, vector<int> & frequency1)
{
  frequency0.clear();
  frequency1.clear();

  frequency0.resize(v[0].size());
  frequency1.resize(v[0].size());

  for (auto number : v)
  {
    for (int i = 0; i < number.size(); i++)
    {
      if (number[i] == 0)
        frequency0[i]++;
      else
        frequency1[i]++;
    }
  }
}

int main()
{
  ifstream in("..\\src\\_input.in");
  // ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto v = reader.ReadDataAsMatrixOfDigits();

  const int kLength = v[0].size();

  vector<int> frequency0;
  vector<int> frequency1;

  ComputeFrequencies(v, frequency0, frequency1);

  int gama = 0;
  int epsilon = 0;
  for (int i = 0; i < kLength; i++)
  {
    if (frequency1[i] > frequency0[i])
    {
      gama = (gama << 1) | 1;
      epsilon <<= 1;
    }
    else
    {
      epsilon = (epsilon << 1) | 1;
      gama <<= 1;
    }
  }

  cout << gama * epsilon << endl;

  // part 2
  {
    auto allGenerators = v;

    auto toDecimal = [=](const vector<int>& binaryValue)
    {
      int decimalValue = 0;
      for (int i = 0; i < kLength; i++)
      {
        decimalValue = (decimalValue << 1) | binaryValue[i];
      }

      return decimalValue;
    };

    // xxx
    int generator = 0;
    for (int i = 0; i < kLength; i++)
    {
      int mostFrequent = (frequency1[i] >= frequency0[i]) ? 1 : 0;

      allGenerators.erase(std::remove_if(allGenerators.begin(), allGenerators.end(), [=](vector<int>& x)
      {
        return x[i] != mostFrequent;
      }), allGenerators.end());

      ComputeFrequencies(allGenerators, frequency0, frequency1);

      // found
      if (allGenerators.size() == 1)
      {
        generator = toDecimal(allGenerators[0]);
        break;
      }
    }

    allGenerators = v;

    int scrubber = 0;
    for (int i = 0; i < kLength; i++)
    {
      int lessFrequent = (frequency1[i] < frequency0[i]) ? 1 : 0;

      allGenerators.erase(std::remove_if(allGenerators.begin(), allGenerators.end(), [=](vector<int>& x)
      {
        return x[i] != lessFrequent;
      }), allGenerators.end());

      ComputeFrequencies(allGenerators, frequency0, frequency1);

      // found
      if (allGenerators.size() == 1)
      {
        scrubber = toDecimal(allGenerators[0]);
        break;
      }
    }

    cout << generator * scrubber;
  }

  // out
  // FStreamWriter writer(out);
  // writer.WriteVector(v);

  return 0;
}
