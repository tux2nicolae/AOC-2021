/**
 * Advent of code 2021
 * @author : Nicolae Telechi
 */
#include <algorithm>
#include <fstream>
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
#include "../../AOCLib/src/Time.h"

int main()
{
  ifstream in("..\\src\\_input.in");
  // ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  vector<int>   v = reader.ReadDataAs<int>();

  // part 1
  int part1 = 0;
  for (int i = 1; i < v.size(); i++)
  {
    if (v[i - 1] < v[i])
      part1++;
  }

  // part 2
  int part2 = 0;
  for (int i = 3; i < v.size(); i++)
  {
    if (v[i - 1] + v[i - 2] + v[i - 3] < v[i] + v[i - 1] + v[i - 2])
      part2++;
  }

  cout << part1 << " " << part2;

  // out
  // FStreamWriter writer(out);
  // writer.WriteVector(v);

  return 0;
}
