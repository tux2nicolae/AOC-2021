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

struct Board
{
  void MarkNumber(int number)
  {
    for (int i = 0; i < data.size(); i++)
    {
      for (int j = 0; j < data[i].size(); j++)
      {
        if (data[i][j] == number)
          seen[{ i, j }] = true;
      }
    }
  };

  int GetScore()
  {
    int score = 0;
    for (int i = 0; i < data.size(); i++)
    {
      for (int j = 0; j < data[i].size(); j++)
      {
        if (!seen[{ i, j }])
          score += data[i][j];
      }
    }

    return score;
  };

  bool HasWon()
  {
    // lines
    for (int i = 0; i < data.size(); i++)
    {
      bool allLine = true;
      for (int j = 0; j < data[i].size(); j++)
      {
        allLine = allLine && seen[{ i, j }];
      }

      if (allLine)
        return true;
    }

    // cols
    for (int i = 0; i < data[0].size(); i++)
    {
      bool allCols = true;
      for (int j = 0; j < data.size(); j++)
      {
        allCols = allCols && seen[{ j, i }];
      }

      if (allCols)
        return true;
    }

    return false;
  };

  bool Valid() { return valid; }
  void Invalidate() { valid = false; };

  bool                      valid{ true };
  vector<vector<int>>       data;
  map<pair<int, int>, bool> seen;
};

int main()
{
  ifstream in("..\\src\\_input.in");
  // ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);

  vector<int>   extracts = reader.ReadLineSeparatedByCharAs<int>();
  vector<Board> boards;

  int       iteration  = 0;
  const int kBoardSize = 5;

  vector<vector<int>> boardData;
  while (reader.IsValid())
  {
    auto dataLine = reader.ReadLineAsNumbers();
    if (dataLine.empty())
      continue;

    boardData.push_back(dataLine);

    if (++iteration % kBoardSize == 0)
    {
      Board board;
      board.data = boardData;

      boards.push_back(board);
      boardData.clear();
    }
  }

  optional<int> scorePart1;
  int           scorePart2 = 0;

  for (int extract : extracts)
  {
    for (auto & board : boards)
    {
      board.MarkNumber(extract);

      if (board.Valid() && board.HasWon())
      {
        if (!scorePart1)
          scorePart1 = extract * board.GetScore();

        scorePart2 = extract * board.GetScore();
        board.Invalidate();
      }
    }
  }

  cout << *scorePart1 << endl;
  cout << scorePart2;

  return 0;
}
