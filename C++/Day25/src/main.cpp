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

bool AreTheSame(vector<string> a, vector<string> b)
{
  for (int i = 0; i < a.size(); i++)
  {
    for (int j = 0; j < a[i].size(); j++)
    {
      if (a[i][j] != b[i][j])
        return false;
    }
  }

  return true;
}

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  // FStreamWriter writer(out);
  // writer.WriteVector(v);

  FStreamReader reader(in);
  auto          inputLines = reader.ReadLines();

  auto lines    = inputLines;
  auto newLines = lines;

  int step = 0;

  while (true)
  {
    step++;

    // move east cucumbers
    for (int i = 0; i < lines.size(); i++)
    {
      for (int j = 0; j < lines[i].size(); j++)
      {
        if (lines[i][j] != '>')
          continue;

        int newI = i;
        int newJ = j + 1;

        if (newJ >= lines[i].size())
          newJ = 0;

        if (newLines[newI][newJ] == '.' && lines[newI][newJ] != '>')
        {
          newLines[i][j]       = '.';
          newLines[newI][newJ] = '>';
        }
      }
    }

    // move down
    for (int i = 0; i < lines.size(); i++)
    {
      for (int j = 0; j < lines[i].size(); j++)
      {
        if (lines[i][j] != 'v')
          continue;

        int newI = i + 1;
        int newJ = j;

        if (newI >= lines.size())
          newI = 0;

        if (newLines[newI][newJ] == '.' && lines[newI][newJ] != 'v')
        {
          newLines[i][j]       = '.';
          newLines[newI][newJ] = 'v';
        }
      }
    }

    if (AreTheSame(lines, newLines))
      break;

    out << step << endl;
    for (auto line : newLines)
    {
      out << line << endl;
    }

    out << endl;

    lines = newLines;
  }

  cout << step;

  return 0;
}
