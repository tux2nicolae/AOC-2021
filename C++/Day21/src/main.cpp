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

unordered_map<long long, long long> sums;

pair<long long, long long> QuantumRoll(
  bool turn, long long player1, long long player2, long long score1, long long score2)
{
  pair<long long, long long> wins;

  if (score1 >= 21)
    return { 1ll, 0ll };

  if (score2 >= 21)
    return { 0ll, 1ll };

  for (auto [sum, times] : sums)
  {
    if (turn)
    {
      auto nextPlayer1 = 1ll + ((player1 + sum - 1ll) % 10);
      auto nextScore1  = score1 + nextPlayer1;

      auto nextWins = QuantumRoll(!turn, nextPlayer1, player2, nextScore1, score2);

      wins.first += nextWins.first * times;
      wins.second += nextWins.second * times;
    }
    else
    {
      auto nextPlayer2 = 1ll + ((player2 + sum - 1ll) % 10);
      auto nextScore2  = score2 + nextPlayer2;

      auto nextWins = QuantumRoll(!turn, player1, nextPlayer2, score1, nextScore2);

      wins.first += nextWins.first * times;
      wins.second += nextWins.second * times;
    }
  }

  return wins;
}

int main()
{
  ifstream in("..\\src\\_input.in");
  // ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          input = reader.ReadLines();

  long long player1{ 2 };
  long long player2{ 8 };

  long long score1 = 0;
  long long score2 = 0;

  bool turn = true;

  // part 1
  /*for (int n = 1;; n += 3)
  {
    int rols = n;
    rols += (n + 1);
    rols += (n + 2);

    if (turn)
    {
      player1 = 1 + ((player1 + rols - 1) % 10);
      score1 += player1;
    }
    else
    {
      player2 = 1 + ((player2 + rols - 1) % 10);
      score2 += player2;
    }

    if (score1 >= 1000)
    {
      cout << score2 * (n + 2);
      break;
    }

    if (score2 >= 1000)
    {
      cout << score1 * (n + 2);
      break;
    }

    turn = !turn;
  }*/

  // part 2

  for (int a = 1; a <= 3; a++)
  {
    for (int b = 1; b <= 3; b++)
    {
      for (int c = 1; c <= 3; c++)
      {
        sums[a + b + c] += 1;
      }
    }
  }

  auto result = QuantumRoll(true, player1, player2, 0, 0);
  cout << result.first << " " << result.second;

  return 0;
}
