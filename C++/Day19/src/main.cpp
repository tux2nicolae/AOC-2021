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
  return result;
}

bool AlignScannersPositions(Scanner & scanner1, Scanner & scanner2)
{
  if (!scanner1.position || scanner2.position)
    return false;

  optional<AOC::Point> scannerPosition;
  optional<Metadata>   metadata;

  map<AOC::Point, int> candidatesCount;

  for (const auto & beacon1 : scanner1.beacons)
  {
    if (scannerPosition)
      break;

    for (const auto & beacon2 : scanner2.beacons)
    {
      if (scannerPosition)
        break;

      const auto & scannersAround = GetScannersAround(beacon1, beacon2);
      for (const auto & [candidateScannerPosition, candidateMetadata] : scannersAround)
      {
        if (++candidatesCount[candidateScannerPosition] >= 12)
        {
          scannerPosition = candidateScannerPosition;
          metadata        = candidateMetadata;
          break;
        }
      }
    }
  }

  if (scannerPosition)
  {
    // align position
    scanner2.position = *scannerPosition - *scanner1.position;

    // align beacons
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

    return true;
  }

  return false;
}

set<AOC::Point> DetectBeaconPositions(vector<Scanner> & scanners)
{
  std::set<int> q;
  q.insert(0);

  while (!q.empty())
  {
    auto & detectedScanner = scanners[*q.begin()];
    q.erase(q.begin());

    for (int i = 0; i < scanners.size(); ++i)
    {
      if (detectedScanner.scannerID == i)
        continue;

      if (AlignScannersPositions(detectedScanner, scanners[i]))
      {
        q.insert(i);
      }
    }
  }

  set<AOC::Point> allBeacons;
  for (auto & scanner : scanners)
  {
    for (auto & beacon : scanner.beacons)
    {
      allBeacons.insert(beacon - *scanner.position);
    }
  }

  return allBeacons;
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

  // parse input
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

  // put first scanner position as { 0, 0, 0 }
  scanners[0].position = { 0, 0, 0 };

  auto allBeacons = DetectBeaconPositions(scanners);
  cout << "All beacons:" << allBeacons.size() << endl;

  // debug output
  for (auto & beacon : allBeacons)
  {
    out << beacon.x << "," << beacon.y << "," << beacon.z << endl;
  }

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

  cout << "MAX DISTANCE:" << maxDistance << endl;
  return 0;
}
