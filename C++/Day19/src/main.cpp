/**
 * Advent of code 2021
 * @author : Nicolae Telechi
 */
#include <algorithm>
#include <array>
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
#include "../../AOCLib/src/Util.h"

struct Scanner
{
  int                  scannerID{};
  optional<AOC::Point> position;
  vector<AOC::Point>   beacons;
};

struct Metadata
{
  vector<int> orientation;
  vector<int> permutation;
};

map<AOC::Point, Metadata> GetScannersAround(const AOC::Point & beacon, const AOC::Point & distance)
{
  map<AOC::Point, Metadata> result;

  vector<long long> dimensions   = { distance.x, distance.y, distance.z };
  vector<int>       permutations = { 0, 1, 2 };

  for (auto signX : { -1, 1 })
  {
    for (auto signY : { -1, 1 })
    {
      for (auto signZ : { -1, 1 })
      {
        do
        {
          AOC::Point newDistance = distance;
          newDistance.x          = dimensions[permutations[0]] * signX;
          newDistance.y          = dimensions[permutations[1]] * signY;
          newDistance.z          = dimensions[permutations[2]] * signZ;

          result[beacon + newDistance] = { vector<int>{ signX, signY, signZ }, permutations };
        } while (next_permutation(permutations.begin(), permutations.end()));
      }
    }
  }

  //-----------------
  // front

  //{
  //  AOC::Point candidateFront = beacon + distance;

  //  candidateFront.RotateRight(beacon);
  //  result.insert(candidateFront);

  //  candidateFront.RotateRight(beacon);
  //  result.insert(candidateFront);

  //  candidateFront.RotateRight(beacon);
  //  result.insert(candidateFront);

  //  candidateFront.RotateRight(beacon);
  //  result.insert(candidateFront);
  //}

  ////-----------------
  //// back

  //{
  //  AOC::Point candidateBack = beacon - distance;

  //  candidateBack.RotateRight(beacon);
  //  result.insert(candidateBack);

  //  candidateBack.RotateRight(beacon);
  //  result.insert(candidateBack);

  //  candidateBack.RotateRight(beacon);
  //  result.insert(candidateBack);

  //  candidateBack.RotateRight(beacon);
  //  result.insert(candidateBack);
  //}

  ////-----------------
  //// left
  //{
  //  AOC::Point candidateLeft = beacon + distance;

  //  candidateLeft.RotateFront(beacon);
  //  result.insert(candidateLeft);

  //  candidateLeft.RotateFront(beacon);
  //  result.insert(candidateLeft);

  //  candidateLeft.RotateFront(beacon);
  //  result.insert(candidateLeft);

  //  candidateLeft.RotateFront(beacon);
  //  result.insert(candidateLeft);
  //}

  ////-----------------
  //// right
  //{
  //  AOC::Point candidateRight = beacon - distance;

  //  candidateRight.RotateFront(beacon);
  //  result.insert(candidateRight);

  //  candidateRight.RotateFront(beacon);
  //  result.insert(candidateRight);

  //  candidateRight.RotateFront(beacon);
  //  result.insert(candidateRight);

  //  candidateRight.RotateFront(beacon);
  //  result.insert(candidateRight);
  //}

  ////-----------------
  //// top
  //{
  //  AOC::Point candidateTop = beacon + distance;

  //  candidateTop.RotateTop(beacon);
  //  result.insert(candidateTop);

  //  candidateTop.RotateTop(beacon);
  //  result.insert(candidateTop);

  //  candidateTop.RotateTop(beacon);
  //  result.insert(candidateTop);

  //  candidateTop.RotateTop(beacon);
  //  result.insert(candidateTop);
  //}

  ////-----------------
  //// bottom
  //{
  //  AOC::Point candidateBottom = beacon - distance;

  //  candidateBottom.RotateTop(beacon);
  //  result.insert(candidateBottom);

  //  candidateBottom.RotateTop(beacon);
  //  result.insert(candidateBottom);

  //  candidateBottom.RotateTop(beacon);
  //  result.insert(candidateBottom);

  //  candidateBottom.RotateTop(beacon);
  //  result.insert(candidateBottom);
  //}

  return result;
}

map<AOC::Point, bool> allBeacons;

void AlignScannersPositions(Scanner & scanner1, Scanner & scanner2)
{
  if (!scanner1.position)
    return;

  optional<AOC::Point> position;
  optional<Metadata>   metadata;

  map<AOC::Point, int> candidatesCount;

  for (const auto & beacon1 : scanner1.beacons)
  {
    if (position)
      break;

    for (const auto & beacon2 : scanner2.beacons)
    {
      if (position)
        break;

      const auto & scannersAround = GetScannersAround(beacon1, beacon2);
      for (const auto & [candidateScannerPosition, candidateMetadata] : scannersAround)
      {
        if (++candidatesCount[candidateScannerPosition] >= 12)
        {
          // calculate orientation when beacon1 == beacon2

          auto test  = beacon2 - beacon1;
          auto test1 = candidateScannerPosition - test;

          position = candidateScannerPosition;
          metadata = candidateMetadata;
          break;
        }
      }
    }
  }

  if (position)
  {
    if (scanner2.position)
    {
      // assert(*scanner2.position == *position - *scanner1.position);
    }
    else
    {
      // align position
      scanner2.position = *position - *scanner1.position;

      for (auto & beacon2 : scanner2.beacons)
      {
        vector<long long> dimensions = { beacon2.x, beacon2.y, beacon2.z };

        beacon2.x = dimensions[(*metadata).permutation[0]] * (*metadata).orientation[0];
        beacon2.y = dimensions[(*metadata).permutation[1]] * (*metadata).orientation[1];
        beacon2.z = dimensions[(*metadata).permutation[2]] * (*metadata).orientation[2];

        beacon2.RotateLeft(*scanner2.position);
        beacon2.RotateLeft(*scanner2.position);

        beacon2.z += 2 * (scanner2.position->z - beacon2.z);
      }

      cout << "--- scanner " << scanner2.scannerID << " --- (" << (*scanner2.position).x << ","
           << (*scanner2.position).y << "," << (*scanner2.position).z << ")" << endl;

      vector<AOC::Point> debug;
      for (auto & beacon2 : scanner2.beacons)
      {
        debug.push_back(beacon2 - *scanner2.position);

        AOC::Point test = debug.back();
        cout << test.x << "," << test.y << "," << test.z << endl;

        allBeacons[test] = true;
      }

      cout << endl;
    }
  }
}

map<int, vector<pair<int, AOC::Point>>> FindMatches(vector<Scanner> & scanners, ofstream & out)
{
  int total = accumulate(begin(scanners), end(scanners), 0,
                         [](long long acc, Scanner & scanner)
                         {
                           return acc + scanner.beacons.size();
                         });

  map<int, vector<pair<int, AOC::Point>>> matches;

  int n = 3;
  while (n--)
  {
    for (int i = 0; i < scanners.size(); i++)
    {
      for (int j = 0; j < scanners.size(); j++)
      {
        if (i == j)
          continue;

        AlignScannersPositions(scanners[i], scanners[j]);
      }
    }

    cout << "All beacons:" << allBeacons.size() << endl;
  }

  for (auto & [id, edges] : matches)
  {
    cout << id << ": ";
    for (auto & edge : edges)
    {
      cout << edge.first << " ";
    }

    cout << endl;
  }

  return matches;
}

void Solve(vector<Scanner> & scanners, map<int, vector<pair<int, AOC::Point>>> & graph)
{
  for (auto & [id, edges] : graph)
  {
    for (auto & [nextNodeId, position] : edges)
    {
      auto nextPosition = position;

      assert(scanners[id].position);

      nextPosition.x += nextPosition.x + scanners[id].position->x;
      nextPosition.y += scanners[id].position->y;
      nextPosition.z += scanners[id].position->z;

      scanners[nextNodeId].position = nextPosition;
    }
  }
}

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          input = reader.ReadLines();

  vector<Scanner> scanners;

  int                scannerId = 0;
  vector<AOC::Point> beacons;

  for (auto line : input)
  {
    if (line.empty())
      continue;

    auto matches = AOC::ExtractMatches(line, "--- scanner (.*) ---");
    if (matches.size())
    {
      if (!beacons.empty())
        scanners.push_back({ scannerId, nullopt, beacons });

      // collect data for new scanner
      scannerId = stoi(matches[1]);
      beacons.clear();
      continue;
    }

    matches = AOC::ExtractMatches(line, "(.*),(.*),(.*)");
    assert(matches.size() == 4);

    AOC::Point point{ stoi(matches[1]), stoi(matches[2]), stoi(matches[3]) };
    beacons.push_back(point);
  }

  // push last scanner
  scanners.push_back({ scannerId, nullopt, beacons });

  // put first scanner position as { 0, 0, 0}
  scanners[0].position = { 0, 0, 0 };

  for (auto beacon : scanners[0].beacons)
    allBeacons[beacon] = true;

  auto graph = FindMatches(scanners, out);
  Solve(scanners, graph);

  // part 2
  long long maxDistance = 0;
  for (auto scanner1 : scanners)
  {
    for (auto scanner2 : scanners)
    {
      maxDistance =
        max(maxDistance, AOC::ManhattenDistance(*scanner1.position, *scanner2.position));
    }
  }

  for (auto & [beacon2, _] : allBeacons)
  {
    AOC::Point test = beacon2;
    out << test.x << "," << test.y << "," << test.z << endl;
  }

  cout << "MAX DISTANCE:" << endl;
  cout << maxDistance;

  // out
  // FStreamWriter writer(out);
  // writer.WriteVector(v);

  return 0;
}
