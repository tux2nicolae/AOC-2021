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
#include <stack>
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

auto GetEnergy(char amphipod)
{
  switch (amphipod)
  {
  case 'A':
    return 1;
  case 'B':
    return 10;
  case 'C':
    return 100;
  case 'D':
    return 1000;
  }
}

struct Room
{
  vector<pair<AOC::Point, char>> roomMates;
};

bool CanGo(map<AOC::Point, char> & hallways, AOC::Point hallway, AOC::Point from)
{
  if (hallways[hallway] != '.')
    return false;

  auto nextHallway = hallway;
  int  stepX       = 0;
  if (from.x < hallway.x)
  {
    nextHallway.x = from.x + 1;
    stepX         = 2;
  }
  else
  {
    nextHallway.x = from.x - 1;
    stepX -= 2;
  }

  while (nextHallway != hallway)
  {
    if (hallways[nextHallway] != '.')
      return false;

    nextHallway.x += stepX;
  }

  return true;
}

void Solve(map<AOC::Point, char> & hallways, vector<Room> & rooms)
{
  for (auto room : rooms)
  {
    for (auto roomMate : room.roomMates)
    {
    }
  }
}

int main()
{
  ifstream in("..\\src\\_input.in");
  // ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          lines = reader.ReadLines();

  map<AOC::Point, char> hallways;

  vector<Room> rooms;
  rooms.resize(4);

  for (int i = lines.size() - 1; i >= 0; i--)
  {
    int roomId = 0;

    for (int j = 0; j < lines[0].size(); j++)
    {
      AOC::Point point{ i, j };
      if (lines[i][j] == '.' && lines[i + 1][j] == '#')
      {
        hallways[point] = '.';
      }
      else if (lines[i][j] >= 'A' && lines[i][j] <= 'D')
      {
        auto roomMate = make_pair(point, lines[i][j]);
        rooms[roomId++].roomMates.push_back(roomMate);
      }
    }
  }

  // out
  // FStreamWriter writer(out);
  // writer.WriteVector(v);

  return 0;
}
