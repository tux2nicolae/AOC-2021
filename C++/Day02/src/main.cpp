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
#include "../../AOCLib/src/Parse.h"

int main()
{
  ifstream in("..\\src\\_input.in");
  // ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto   v = reader.ReadLines();

  int horisontal = 0;
  int depth = 0;

  // part 2
  int aim = 0;
  for (auto line : v)
  {
    string direction;
    int value;

    stringstream ss(line);
    ss >> direction >> value;

    if (direction == "forward") {
      horisontal += value;
      depth += value * aim;
    }
    else if (direction == "down")
      aim += value;
    else if (direction == "up")
      aim -= value;
  }

  cout << depth * horisontal;


  // out
  // FStreamWriter writer(out);
  // writer.WriteVector(v);

  return 0;
}
