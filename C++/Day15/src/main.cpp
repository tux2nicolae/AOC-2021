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

vector<vector<int>> GetPart2Input(const vector<vector<int>> & input)
{
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

      auto inputNumber = input[i % input.size()][j % input.size()];
      auto tileNumber  = (i / input.size()) + (j / input.size());

      part2Input[i][j] = inputNumber + tileNumber;
      if (part2Input[i][j] > 9)
        part2Input[i][j] %= 9;
    }
  }

  return part2Input;
}

vector<vector<int>> Run(vector<vector<int>> & aMap, AOC::Point startPoint, AOC::Point endPoint)
{
  vector<vector<int>> costs(aMap.size(), vector<int>(aMap[0].size(), numeric_limits<int>::max()));
  costs[startPoint.x][startPoint.y] = 0;

  auto heapComparator = [&](AOC::Point left, AOC::Point right)
  {
    return costs[left.x][left.y] > costs[left.x][left.y];
  };

  set<AOC::Point> exists;
  exists.insert(startPoint);

  priority_queue<AOC::Point, vector<AOC::Point>, decltype(heapComparator)> heap(heapComparator);
  heap.push(startPoint);

  // run
  while (!heap.empty())
  {
    auto from = heap.top();
    heap.pop();

    for (auto to : from.GetAll2DNeighbours())
    {
      if (!to.IsInBoundary(startPoint, endPoint))
        continue;

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

  auto input      = reader.ReadDataAsMatrixOfDigits();
  auto part2Input = GetPart2Input(input);

  auto resultPart2 = Run(part2Input, AOC::Point{ 0, 0 },
                         AOC::Point{ (int)part2Input.size() - 1, (int)part2Input.size() - 1 });

  // out
  FStreamWriter writer(out);
  writer.WriteMatrix(resultPart2);

  return 0;
}
