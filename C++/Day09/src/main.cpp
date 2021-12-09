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
#include <queue>
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
  auto          input = reader.ReadDataAsMatrixOfDigits();

  int s = 0;

  vector<AOC::Point> lowPoints;

  for (int x = 0; x < input.size(); x++)
  {
    for (int y = 0; y < input[0].size(); y++)
    {
      auto point = AOC::Point{ x, y };

      int lowPoint = std::numeric_limits<int>::max();
      for (auto neighbour : point.GetDirectNeighbours())
      {
        if (neighbour.IsInBoundary({ 0, 0 }, { (int)input.size() - 1, (int)input[0].size() - 1 }))
        {
          lowPoint = min(lowPoint, input[neighbour.x][neighbour.y]);
        }
      }

      if (input[x][y] < lowPoint)
      {
        int risklevel = input[x][y] + 1;
        s += risklevel;

        lowPoints.push_back(AOC::Point{ x, y });
      }
    }
  }

  vector<int> results;

  for (const auto & lowPoint : lowPoints)
  {
    queue<AOC::Point> q;
    q.push(lowPoint);

    map<AOC::Point, bool> visited;
    int                   basinSize = 0;

    visited[lowPoint] = true;

    while (!q.empty())
    {
      auto from = q.front();
      q.pop();

      basinSize++;

      for (auto to : from.GetDirectNeighbours())
      {
        if (!to.IsInBoundary({ 0, 0 }, { (int)input.size() - 1, (int)input[0].size() - 1 }))
        {
          continue;
        }

        if (visited[to] || input[to.x][to.y] == 9)
        {
          continue;
        }

        visited[to] = true;
        q.push(to);
      }
    }

    results.push_back(basinSize);
  }

  sort(begin(results), end(results), greater<>());

  cout << s << endl;
  cout << results[0] * results[1] * results[2];
  // out
  // FStreamWriter writer(out);
  // writer.WriteVector(v);

  return 0;
}
