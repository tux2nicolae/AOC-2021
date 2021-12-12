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

struct Cave
{
  vector<string> neighbours;
};

int totalPaths = 0;

bool                       smallTwice = false;
unordered_map<string, int> visited;

unordered_map<string, Cave> graph;

bool dfs(unordered_map<string, Cave> & graph, string node)
{
  if (node == "end")
  {
    totalPaths++;
    return true;
  }

  for (auto neigbour : graph[node].neighbours)
  {
    if (neigbour == "start")
      continue;

    if (visited[neigbour] && smallTwice)
      continue;

    if (neigbour[0] <= 'z' && neigbour[0] >= 'a')
    {
      if (++visited[neigbour] >= 2)
        smallTwice = true;

      assert(visited[neigbour] <= 2);
    }

    dfs(graph, neigbour);

    if (neigbour[0] <= 'z' && neigbour[0] >= 'a')
    {
      if (visited[neigbour]-- == 2)
        smallTwice = false;
    }
  }

  return true;
}

int main()
{
  ifstream in("..\\src\\_input.in");
  // ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          input = reader.ReadLines();

  for (auto line : input)
  {
    auto matches = AOC::ExtractMatches(line, "(.*)-(.*)");

    graph[matches[1]].neighbours.push_back(matches[2]);
    graph[matches[2]].neighbours.push_back(matches[1]);
  }

  visited["start"] = true;
  dfs(graph, "start");

  cout << totalPaths;

  // out
  // FStreamWriter writer(out);
  // writer.WriteVector(v);

  return 0;
}
