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

set<AOC::Point> HorizontalFold(set<AOC::Point> & points, int val)
{
  set<AOC::Point> newPoints;

  for (auto point : points)
  {
    // fold
    if (point.y > val)
    {
      AOC::Point rotationPoint{ point.x, val };

      point.RotateLeft(rotationPoint);
      point.RotateLeft(rotationPoint);
    }

    newPoints.insert(point);
  }

  return newPoints;
}

set<AOC::Point> VerticalFold(set<AOC::Point> & points, int val)
{
  set<AOC::Point> newPoints;

  for (auto point : points)
  {
    if (point.x > val)
    {
      AOC::Point rotationPoint{ val, point.y };

      point.RotateLeft(rotationPoint);
      point.RotateLeft(rotationPoint);
    }

    assert(point.x >= 0);
    newPoints.insert(point);
  }

  return newPoints;
}

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          input = reader.ReadLines();

  set<AOC::Point> points;

  for (auto line : input)
  {
    if (line.empty())
      break;

    auto tokens = AOC::Explode(line, ',');
    assert(tokens.size() == 2);

    points.insert(AOC::Point{ atoi(tokens[0].c_str()), atoi(tokens[1].c_str()) });
  }

  // string line;
  auto foldedPoints = points;
  for (int i = 853; i < input.size(); i++)
  {
    string line = input[i];
    if (line.empty())
      break;

    auto matches = AOC::ExtractMatches(line, "fold along (.*)=(.*)");
    assert(matches.size() == 3);

    int position = atoi(matches[2].c_str());

    if (matches[1] == "x")
    {
      foldedPoints = VerticalFold(foldedPoints, position);
    }
    else
    {
      foldedPoints = HorizontalFold(foldedPoints, position);
    }
  }

  // out
  FStreamWriter writer(out);

  for (int i = 0; i < 100; i++)
  {
    for (int j = 0; j < 100; j++)
    {
      if (foldedPoints.count(AOC::Point{ j, i }))
        out << "#";
      else
        out << ".";
    }

    out << endl;
  }

  return 0;
}
