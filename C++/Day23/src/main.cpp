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

  assert(false);
  return 0;
}

struct Amphenoid
{
  char       id;
  AOC::Point position;
};

struct Room
{
  char              roomTarget;
  vector<Amphenoid> roomMates;

  optional<int> roomStartingRow{};
  int           roomCol{};
  int           maxSize{};
};

bool CanGoToHallway(const map<AOC::Point, char> & hallways,
                    AOC::Point                    hallway,
                    Amphenoid &                   amphipod)
{
  assert(hallways.count(hallway));

  if (hallways.at(hallway) != '.')
    return false;

  auto nextHallway = hallway;
  int  stepY       = 0;

  if (amphipod.position.y < hallway.y)
  {
    nextHallway.y = amphipod.position.y + 1;
    stepY         = 1;
  }
  else
  {
    nextHallway.y = amphipod.position.y - 1;
    stepY         = -1;
  }

  for (; nextHallway != hallway; nextHallway.y += stepY)
  {
    if (!hallways.count(nextHallway))
      continue;

    if (hallways.at(nextHallway) != '.')
      return false;
  }

  return true;
}

bool CanGoToTargetRoom(map<AOC::Point, char> & hallways, AOC::Point hallway, Room & room)
{
  if (hallways[hallway] != room.roomTarget)
    return false;

  assert(room.roomMates.size() <= 4);

  for (auto roomMate : room.roomMates)
  {
    if (roomMate.id != room.roomTarget)
      return false;
  }

  AOC::Point targetRoomPoint{ *room.roomStartingRow + (room.maxSize - room.roomMates.size() - 1),
                              room.roomCol };

  auto nextHallway = hallway;
  int  stepY       = 0;

  if (targetRoomPoint.y < hallway.y)
  {
    nextHallway.y = hallway.y - 1;
    stepY         = -1;
  }
  else if (targetRoomPoint.y > hallway.y)
  {
    nextHallway.y = hallway.y + 1;
    stepY         = 1;
  }

  for (; nextHallway.y != targetRoomPoint.y; nextHallway.y += stepY)
  {
    if (!hallways.count(nextHallway))
      continue;

    if (hallways[nextHallway] != '.')
      return false;
  }

  return true;
}

int GetTargetRoomFor(const Amphenoid & amphipod)
{
  return amphipod.id - 'A';
};

vector<AOC::Point> GetAvailableHallwaysFor(const map<AOC::Point, char> & hallways,
                                           Amphenoid &                   amphipod)
{
  vector<AOC::Point> availableHallways;
  for (auto [hallway, _] : hallways)
    if (CanGoToHallway(hallways, hallway, amphipod))
      availableHallways.push_back(hallway);

  return availableHallways;
}

int GoToHallway(map<AOC::Point, char> & hallways, AOC::Point hallway, Amphenoid & amphipod)
{
  hallways[hallway] = amphipod.id;
  return AOC::ManhattenDistance(amphipod.position, hallway) * GetEnergy(amphipod.id);
}

int GoToTargetRoom(map<AOC::Point, char> & hallways,
                   Room &                  room,
                   AOC::Point              hallway,
                   Amphenoid &             amphipod)
{
  assert(room.roomMates.size() <= 3);

  AOC::Point targetRoomPoint{ *room.roomStartingRow + (room.maxSize - room.roomMates.size() - 1),
                              room.roomCol };

  return AOC::ManhattenDistance(targetRoomPoint, hallway) * GetEnergy(amphipod.id);
}

bool AreOrganized(const vector<Room> & rooms)
{
  bool found = true;
  for (auto & room : rooms)
  {
    if (room.roomMates.size() != room.maxSize)
    {
      found = false;
    }

    bool allOff = true;
    for (auto & roomMate : room.roomMates)
    {
      allOff = allOff && roomMate.id == room.roomTarget;
    }

    found = found && allOff;
  }

  return found;
}

bool HasImpostors(const Room & room)
{
  for (const auto & roomMate : room.roomMates)
  {
    if (roomMate.id != room.roomTarget)
      return true;
  }

  return false;
}

optional<int> Solve(ofstream & out, map<AOC::Point, char> hallways, vector<Room> rooms)
{
  int initialCost = 0;

  // move from hallway to rooms
  int n = 5;
  while (n--)
  {
    for (const auto & [hallway, amphenoidId] : hallways)
    {
      if (amphenoidId == '.')
        continue;

      auto   amphenoid  = Amphenoid{ amphenoidId, hallway };
      auto & targetRoom = rooms[GetTargetRoomFor(amphenoid)];

      if (CanGoToTargetRoom(hallways, hallway, targetRoom))
      {
        initialCost += GoToTargetRoom(hallways, targetRoom, hallway, amphenoid);

        hallways[hallway] = '.';
        targetRoom.roomMates.push_back(amphenoid);
      }
    }
  }

  if (AreOrganized(rooms))
    return initialCost;

  //-------------------------------------------------------------------------

  optional<int> minCost;
  for (auto & room : rooms)
  {
    if (!HasImpostors(room))
      continue;

    Amphenoid amphenoid = room.roomMates.back();
    for (const auto & hallway : GetAvailableHallwaysFor(hallways, amphenoid))
    {
      // move to hallways
      int cost = GoToHallway(hallways, hallway, amphenoid);
      room.roomMates.pop_back();

      // solve the subproblem
      auto subproblemCost = Solve(out, hallways, rooms);
      if (subproblemCost)
      {
        minCost =
          min(minCost.value_or(numeric_limits<int>::max()), initialCost + cost + *subproblemCost);
      }

      // revert back
      hallways[hallway] = '.';
      room.roomMates.push_back(amphenoid);
    }
  }

  return minCost;
}

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          lines = reader.ReadLines();

  map<AOC::Point, char> hallways;

  vector<Room> rooms;
  rooms.resize(4);

  vector<char> targets{ 'A', 'B', 'C', 'D' };

  for (int i = lines.size() - 1; i >= 0; i--)
  {
    int roomId = 0;

    for (int j = 0; j < lines[i].size(); j++)
    {
      AOC::Point point{ i, j };
      if (lines[i][j] == '.' && lines[i + 1][j] == '#')
      {
        hallways[point] = '.';
      }
      else if (lines[i][j] >= 'A' && lines[i][j] <= 'D')
      {
        auto roomMate = Amphenoid{ lines[i][j], point };

        rooms[roomId].roomTarget = targets[roomId];
        rooms[roomId].roomCol    = j;

        rooms[roomId].roomMates.push_back(roomMate);
        rooms[roomId++].maxSize =
          max((size_t)rooms[roomId].maxSize, rooms[roomId].roomMates.size());
      }
    }
  }

  // set room starting row
  for (int i = 0; i < lines.size(); i++)
  {
    int roomId = 0;
    for (int j = 0; j < lines[i].size(); j++)
    {
      if (lines[i][j] >= 'A' && lines[i][j] <= 'D')
      {
        if (!rooms[roomId].roomStartingRow)
          rooms[roomId++].roomStartingRow = i;
      }
    }
  }

  auto totalCost = Solve(out, hallways, rooms);
  cout << *totalCost;

  return 0;
}
