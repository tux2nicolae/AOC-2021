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

int GetNextIndex(const vector<string> & image, AOC::Point currentPoint)
{
  string str;
  str += image[currentPoint.x - 1].substr(currentPoint.y - 1, 3);
  str += image[currentPoint.x].substr(currentPoint.y - 1, 3);
  str += image[currentPoint.x + 1].substr(currentPoint.y - 1, 3);

  for (auto & c : str)
    c = (c == '#') ? '1' : '0';

  return AOC::BinaryStringToInt(str);
}

int main()
{
  ifstream in("..\\src\\_input.in");
  ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);

  string imageEnhancementAlgorithm, _;
  getline(in, imageEnhancementAlgorithm);
  getline(in, _);

  auto image = reader.ReadLines();
  for (auto & line : image)
  {
    line = string(200, '.') + line + string(200, '.');
  }

  for (int i = 0; i < 200; i++)
  {
    image.insert(image.begin(), string(image[0].size(), '.'));
    image.push_back(string(image[0].size(), '.'));
  }

  int n = 50;
  while (n--)
  {
    vector<string> newImage = image;
    for (int i = 1; i < image.size() - 1; i++)
    {
      for (int j = 1; j < image[i].size() - 1; j++)
      {
        AOC::Point currentPoint{ i, j };
        newImage[i][j] = imageEnhancementAlgorithm[GetNextIndex(image, currentPoint)];
      }
    }

    image = newImage;

    for (auto & line : image)
      out << line << endl;

    out << endl;
    out << endl;
    out << endl;
    out << endl;
  }

  int s = 0;

  for (int i = 70; i < image.size() - 70; i++)
  {
    for (int j = 70; j < image[i].size() - 70; j++)
    {
      if (image[i][j] == '#')
        s++;
    }
  }

  out << s;

  // out
  // FStreamWriter writer(out);
  // writer.WriteVector(v);

  return 0;
}
