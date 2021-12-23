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

struct Amphenoid
{
  auto GetEnergy() const
  {
    switch (id)
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

  char       id;
  AOC::Point position;
};

struct Room
{
  bool HasImpostors()
  {
    for (const auto & roomMate : roomMates)
    {
      if (roomMate.id != roomTarget)
        return true;
    }

    return false;
  }

  char              roomTarget{};
  vector<Amphenoid> roomMates;
  AOC::Point        roomPosition{};
};

struct Space
{
  Space() { rooms.resize(4); }

  bool IsOrganized()
  {
    for (const auto & room : rooms)
    {
      if (room.roomMates.size() != roomSize)
        return false;

      for (const auto & roomMate : room.roomMates)
      {
        if (roomMate.id != room.roomTarget)
          return false;
      }
    }

    return true;
  }

  Room & GetTargetRoomFor(const Amphenoid & amphipod)
  {
    assert(amphipod.id - 'A' < rooms.size());
    return rooms[amphipod.id - 'A'];
  };

  vector<AOC::Point> GetAvailableHallwaysFor(const Amphenoid & amphipod)
  {
    vector<AOC::Point> availableHallways;
    for (const auto & [hallway, _] : hallways)
      if (CanGoToHallway(hallway, amphipod))
        availableHallways.push_back(hallway);

    return availableHallways;
  }

  bool CanGoToHallway(const AOC::Point & hallway, const Amphenoid & amphipod)
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

  bool CanGoToTargetRoom(AOC::Point hallway, Room & room)
  {
    assert(hallways.count(hallway));
    if (hallways.at(hallway) != room.roomTarget)
      return false;

    assert(room.roomMates.size() <= 4);
    for (const auto & roomMate : room.roomMates)
    {
      if (roomMate.id != room.roomTarget)
        return false;
    }

    AOC::Point targetRoomPoint{ room.roomPosition.x + (roomSize - room.roomMates.size() - 1),
                                room.roomPosition.y };

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

      if (hallways.at(nextHallway) != '.')
        return false;
    }

    return true;
  }

  int CostToHallway(const AOC::Point & hallway, const Amphenoid & amphipod)
  {
    return AOC::ManhattenDistance(amphipod.position, hallway) * amphipod.GetEnergy();
  }

  int CostToTargetRoom(const Room & toRoom, const AOC::Point & fromHallway, Amphenoid & amphipod)
  {
    assert(toRoom.roomMates.size() <= 3);
    AOC::Point targetRoomPoint{ toRoom.roomPosition.x + (roomSize - toRoom.roomMates.size() - 1),
                                toRoom.roomPosition.y };

    return AOC::ManhattenDistance(targetRoomPoint, fromHallway) * amphipod.GetEnergy();
  }

  //-------------------------------------------------------------------------

  map<AOC::Point, char> hallways;

  size_t       roomSize{};
  vector<Room> rooms;
};

optional<int> Solve(Space space)
{
  int initialCost = 0;

  // move from hallway to rooms
  int n = space.hallways.size();
  while (n--)
  {
    for (const auto & [hallway, amphenoidId] : space.hallways)
    {
      if (amphenoidId == '.')
        continue;

      auto   amphenoid  = Amphenoid{ amphenoidId, hallway };
      auto & targetRoom = space.GetTargetRoomFor(amphenoid);

      if (space.CanGoToTargetRoom(hallway, targetRoom))
      {
        initialCost += space.CostToTargetRoom(targetRoom, hallway, amphenoid);

        space.hallways[hallway] = '.';
        targetRoom.roomMates.push_back(amphenoid);
      }
    }
  }

  if (space.IsOrganized())
    return initialCost;

  optional<int> minCost;
  for (auto & room : space.rooms)
  {
    if (!room.HasImpostors())
      continue;

    Amphenoid amphenoid = room.roomMates.back();
    for (const auto & hallway : space.GetAvailableHallwaysFor(amphenoid))
    {
      // move to hallways
      space.hallways[hallway] = amphenoid.id;
      room.roomMates.pop_back();

      int cost = space.CostToHallway(hallway, amphenoid);

      // solve the subproblem
      auto subproblemCost = Solve(space);
      if (subproblemCost)
      {
        minCost =
          min(minCost.value_or(numeric_limits<int>::max()), initialCost + cost + *subproblemCost);
      }

      // revert back
      space.hallways[hallway] = '.';
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

  Space space;

  // parse space data
  const vector<char> kTargets{ 'A', 'B', 'C', 'D' };
  for (int x = lines.size() - 1; x >= 0; x--)
  {
    for (int roomNumber = 0, y = 0; y < lines[x].size(); y++)
    {
      char       id = lines[x][y];
      AOC::Point point{ x, y };

      if (id == '.' && lines[x + 1][y] == '#')
      {
        space.hallways[point] = '.';
      }
      else if (id >= 'A' && id <= 'D')
      {
        Amphenoid roomMate{ id, point };
        space.rooms[roomNumber].roomMates.push_back(roomMate);
        space.rooms[roomNumber].roomTarget = kTargets[roomNumber];

        space.roomSize = max(space.roomSize, space.rooms[roomNumber].roomMates.size());

        roomNumber++;
      }
    }
  }

  // parse room starting position
  for (int roomNumber = 0, y = 0; y < lines[2].size(); y++)
  {
    if (lines[2][y] >= 'A' && lines[2][y] <= 'D')
      space.rooms[roomNumber++].roomPosition = { 2, y };
  }

  auto totalCost = Solve(space);
  cout << *totalCost;

  return 0;
}
