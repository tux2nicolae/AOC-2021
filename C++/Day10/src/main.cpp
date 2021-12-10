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

int GetPoints(char c)
{
  switch (c)
  {
  case ')':
    return 3;
  case ']':
    return 57;
  case '}':
    return 1197;
  case '>':
    return 25137;
  }

  assert(false);
  return 0;
}

int GetPointsPart2(char c)
{
  switch (c)
  {
  case '(':
    return 1;
  case '[':
    return 2;
  case '{':
    return 3;
  case '<':
    return 4;
  }

  assert(false);
  return 0;
}

char GetMatchChar(char c)
{
  switch (c)
  {
  case ')':
    return '(';
  case '}':
    return '{';
  case ']':
    return '[';
  case '>':
    return '<';
  }

  assert(false);
  return 0;
}

int main()
{
  ifstream in("..\\src\\_input.in");
  // ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          input = reader.ReadLines();

  int               s = 0;
  vector<long long> part2Scores;

  for (auto line : input)
  {
    stack<char> st;
    bool        corupted = false;
    for (char c : line)
    {
      if (c == '(' || c == '[' || c == '<' || c == '{')
      {
        st.push(c);
      }
      else
      {
        if (st.empty() || st.top() != GetMatchChar(c))
        {
          corupted = true;
          s += GetPoints(c);
          break;
        }

        st.pop();
      }
    }

    if (!corupted)
    {
      long long score = 0;

      while (!st.empty())
      {
        score = score * 5 + GetPointsPart2(st.top());
        st.pop();
      }

      part2Scores.push_back(score);
    }
  }

  cout << s << endl;

  sort(begin(part2Scores), end(part2Scores));
  cout << part2Scores[part2Scores.size() / 2];

  // out
  // FStreamWriter writer(out);
  // writer.WriteVector(v);

  return 0;
}
