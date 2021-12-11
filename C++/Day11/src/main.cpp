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

void Flash(vector<vector<int>> & input, map<AOC::Point, bool> & alreadyFlashed, AOC::Point octopus)
{
  for (auto & neighbour : octopus.GetAll2DNeighbours())
  {
    if (!neighbour.IsInBoundary({ 0, 0 }, { (int)input.size() - 1, (int)input.size() - 1 }))
      continue;

    if (alreadyFlashed[neighbour])
      continue;

    if (++input[neighbour.x][neighbour.y] > 9)
    {
      input[neighbour.x][neighbour.y] = 0;

      alreadyFlashed[neighbour] = true;
      Flash(input, alreadyFlashed, neighbour);
    }
  }
}

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          input = reader.ReadDataAsMatrixOfDigits();

  int steps = 0;
  while (++steps)
  {
    int totalFlashes = 0;

    vector<AOC::Point>    shouldFlashes;
    map<AOC::Point, bool> alreadyFlashed;

    for (int x = 0; x < input.size(); x++)
    {
      for (int y = 0; y < input[0].size(); y++)
      {
        AOC::Point octopus{ x, y };
        if (++input[octopus.x][octopus.y] > 9)
        {
          input[octopus.x][octopus.y] = 0;

          alreadyFlashed[octopus] = true;
          shouldFlashes.push_back(octopus);
        }
      }
    }

    for (auto & shouldFlash : shouldFlashes)
    {
      Flash(input, alreadyFlashed, shouldFlash);
    }

    FStreamWriter writer(out);
    writer.WriteMatrix(input);

    out << endl;

    for (int x = 0; x < input.size(); x++)
    {
      for (int y = 0; y < input[0].size(); y++)
      {
        if (input[x][y] == 0)
          totalFlashes++;
      }
    }

    if (totalFlashes == 100)
    {
      break;
    }
  }

  cout << steps;

  // out
  // FStreamWriter writer(out);
  // writer.WriteVector(v);

  return 0;
}
