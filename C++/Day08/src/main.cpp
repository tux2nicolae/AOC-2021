/**
 * Advent of code 2021
 * @author : Nicolae Telechi
 */
#include <algorithm>
#include <assert.h>
#include <bitset>
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

struct Note
{
  vector<string> signalPatterns;
  vector<string> outputValue;  // 4 digit
};

optional<int> GetUniqueDigit(string & signal)
{
  if (signal.size() == 2)
    return 1;
  else if (signal.size() == 4)
    return 4;
  else if (signal.size() == 3)
    return 7;
  else if (signal.size() == 7)
    return 8;

  return nullopt;
}

int CommonCharacters(const string a, const string & b)
{
  int s = 0;
  for (auto c : a)
    if (b.find(c) != string::npos)
      s++;

  return s;
}

int MapSignal(unordered_map<string, optional<int>> & mappings, string & signal)
{
  auto findDigit = [&](int digit)
  {
    return std::find_if(begin(mappings), end(mappings),
                        [=](auto & entry)
                        {
                          return entry.second && entry.second == digit;
                        });
  };

  if (signal.size() == 6)
  {
    auto it1 = findDigit(1);
    assert(it1 != mappings.end());

    if (CommonCharacters(signal, it1->first) == 1)
    {
      return 6;
    }
    else
    {
      auto it4 = findDigit(4);
      assert(it4 != mappings.end());

      if (CommonCharacters(signal, it4->first) == 4)
        return 9;
      else
        return 0;
    }
  }
  else if (signal.size() == 5)
  {
    auto it4 = findDigit(4);
    assert(it4 != mappings.end());

    if (CommonCharacters(signal, it4->first) == 2)
    {
      return 2;
    }
    else
    {
      auto it1 = findDigit(1);
      assert(it1 != mappings.end());

      if (CommonCharacters(signal, it1->first) == 2)
        return 3;
      else
        return 5;
    }
  }
}

bool CanMapSignal(unordered_map<string, optional<int>> & mappings, string & signal, int digit)
{
  auto findDigit = [&](int digit)
  {
    return std::find_if(begin(mappings), end(mappings),
                        [](auto & entry)
                        {
                          return entry.second && entry.second == 8;
                        });
  };

  if (signal.size() == 6)
  {
    auto it1 = findDigit(1);
    assert(it1 != mappings.end());

    if (CommonCharacters(signal, it1->first) == 1)
    {
      return digit == 6;
    }
    else
    {
      auto it4 = findDigit(4);
      assert(it4 != mappings.end());

      if (CommonCharacters(signal, it4->first) == 4)
        return digit == 9;
      else
        return digit == 0;
    }
  }
  else if (signal.size() == 5)
  {
    auto it4 = findDigit(4);
    assert(it4 != mappings.end());

    if (CommonCharacters(signal, it4->first) == 2)
    {
      return digit == 2;
    }
    else
    {
      auto it1 = findDigit(1);
      assert(it1 != mappings.end());

      if (CommonCharacters(signal, it1->first) == 2)
        return digit == 3;
      else
        return digit == 2;
    }
  }
}

bool BackTraking(unordered_map<string, optional<int>> & mappings,
                 vector<bool> &                         foundDigits,
                 vector<string> &                       signals)
{
  if (accumulate(begin(foundDigits), end(foundDigits), 0) == 10)
    return true;

  for (auto signal : signals)
  {
    if (mappings[signal])
      continue;

    for (int digit = 0; digit <= 9; digit++)
    {
      if (foundDigits[digit])
        continue;

      if (!CanMapSignal(mappings, signal, digit))
        continue;

      mappings[signal]   = digit;
      foundDigits[digit] = true;

      if (BackTraking(mappings, foundDigits, signals))
        return true;

      mappings[signal]   = nullopt;
      foundDigits[digit] = false;
    }
  }

  return false;
}

unordered_map<string, optional<int>> MapStringsToDigits(vector<string> & signals)
{
  // vector<bool>                         foundDigits(10);
  unordered_map<string, optional<int>> mappings;

  // unique signals
  for (auto signal : signals)
  {
    auto uniqueDigit = GetUniqueDigit(signal);
    if (uniqueDigit)
    {
      mappings[signal] = uniqueDigit;
    }
  }

  for (auto signal : signals)
  {
    if (!mappings[signal])
      mappings[signal] = MapSignal(mappings, signal);
  }

  return mappings;
  // BackTraking(mappings, foundDigits, signals);
}

int SolvePart2(vector<Note> & notes)
{
  int sum = 0;

  for (auto & note : notes)
  {
    // sort
    for (auto & signal : note.signalPatterns)
    {
      sort(begin(signal), end(signal));
    }

    // solve
    auto stringToDigits = MapStringsToDigits(note.signalPatterns);

    int number = 0;
    for (auto & outputDigit : note.outputValue)
    {
      sort(begin(outputDigit), end(outputDigit));
      number = number * 10 + *stringToDigits[outputDigit];
    }

    sum += number;
  }

  return sum;
}

int main()
{
  ifstream in("..\\src\\_input.in");
  // ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          input = reader.ReadLines();

  vector<Note> notes;
  for (int i = 0; i < input.size(); i += 1)
  {
    auto flatInput = AOC::Explode(input[i], '|');

    Note note;
    note.signalPatterns = AOC::Explode(flatInput[0], " ");
    note.outputValue    = AOC::Explode(flatInput[1], " ");

    // |
    // note.signalPatterns.pop_back();
    note.outputValue.erase(note.outputValue.begin());

    notes.push_back(note);
  }

  int part1 = 0;
  int part2 = SolvePart2(notes);

  for (auto & note : notes)
  {
    for (auto & outputDigit : note.outputValue)
    {
      if (outputDigit.size() == 2 || outputDigit.size() == 4 || outputDigit.size() == 3 ||
          outputDigit.size() == 7)
      {
        part1++;
      }
    }
  }

  cout << part1 << endl;
  cout << part2;

  return 0;
}
