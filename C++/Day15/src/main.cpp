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

vector<vector<int>> Run(AOC::Point startPoint, vector<vector<int>> & aMap)
{
  vector<vector<int>> costs(aMap.size(), vector<int>(aMap[0].size(), numeric_limits<int>::max()));
  costs[0][0] = 0;

  auto heapComparator = [&](AOC::Point left, AOC::Point right)
  {
    return costs[left.x][left.y] > costs[left.x][left.y];
  };

  priority_queue<AOC::Point, vector<AOC::Point>, decltype(heapComparator)> heap(heapComparator);
  heap.push(startPoint);

  auto isInBoundary = [&](const AOC::Point & to) -> bool
  {
    return !(to.x < 0 || to.y < 0 || to.x >= static_cast<int>(aMap.size()) ||
             to.y >= static_cast<int>(aMap[0].size()));
  };

  // run
  while (!heap.empty())
  {
    auto from = heap.top();
    heap.pop();

    static const int directionX[4] = { -1, 0, 1, 0 };
    static const int directionY[4] = { 0, 1, 0, -1 };

    for (int i = 0; i < 4; ++i)
    {
      AOC::Point to;
      to.x = from.x + directionX[i];
      to.y = from.y + directionY[i];

      if (!isInBoundary(to))
      {
        continue;
      }

      if (costs[from.x][from.y] + aMap[to.x][to.y] < costs[to.x][to.y])
      {
        costs[to.x][to.y] = min(costs[from.x][from.y] + aMap[to.x][to.y], costs[to.x][to.y]);
        heap.push(to);
      }
    }
  }

  return costs;
}

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          input = reader.ReadDataAsMatrixOfDigits();

  vector<vector<int>> part2Input(input.size() * 5, vector<int>(input[0].size() * 5));

  for (int i = 0; i < part2Input.size(); i++)
  {
    for (int j = 0; j < part2Input[0].size(); j++)
    {
      if (i < input.size() && j < input.size())
      {
        part2Input[i][j] = input[i][j];
        continue;
      }

      auto tileNumber = (i / input.size()) + (j / input.size());

      part2Input[i][j] = (input[i % input.size()][j % input.size()] + tileNumber);
      if (part2Input[i][j] > 9)
      {
        part2Input[i][j] %= 9;
      }
    }
  }

  auto result = Run({ AOC::Point{ 0, 0 } }, part2Input);

  // out
  FStreamWriter writer(out);
  writer.WriteMatrix(result);

  return 0;
}
