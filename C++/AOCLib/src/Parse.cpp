/**
 * Advent of code 2021
 * @author : Nicolae Telechi
 */
#include "pch.h"
#include "Parse.h"

std::vector<std::string> AOC::Explode(const std::string & str, char separator)
{
  std::vector<std::string> result;

  std::istringstream stream(str);
  for (std::string token; std::getline(stream, token, separator);)
  {
    result.push_back(std::move(token));
  }

  return result;
}

std::vector<std::string> AOC::Explode(const std::string & str, const string & regexSeparator)
{
  regex reg(regexSeparator);

  sregex_token_iterator iter(str.begin(), str.end(), reg, -1);
  sregex_token_iterator end;

  return { iter, end };
}

int AOC::ExtractInt(const string & str, const string & regexStr)
{
  smatch match;
  regex_match(str, match, regex(regexStr));
  assert(match.size() == 1);

  // 0
  return stoi(match[0]);
}

vector<string> AOC::ExtractMatches(const string & str, const string & regexStr)
{
  smatch matches;
  regex_match(str, matches, regex(regexStr));

  return { matches.begin(), matches.end() };
}

int AOC::BinaryStringToInt(string_view binaryValue)
{
  return stoi(string(binaryValue), 0, 2);
}

int AOC::BinaryStringToInt(const string & binaryValue)
{
  return stoi(binaryValue, 0, 2);
}

long long AOC::BinaryStringToLongLong(string_view binaryValue)
{
  return stoll(string(binaryValue), 0, 2);
}

long long AOC::BinaryStringToLongLong(const string & binaryValue)
{
  return stoll(binaryValue, 0, 2);
}

string AOC::GetBinaryStringFromHexString(string hex)
{
  string result = "";
  for (auto c : hex)
  {
    switch (c)
    {
    case '0':
      result.append("0000");
      break;
    case '1':
      result.append("0001");
      break;
    case '2':
      result.append("0010");
      break;
    case '3':
      result.append("0011");
      break;
    case '4':
      result.append("0100");
      break;
    case '5':
      result.append("0101");
      break;
    case '6':
      result.append("0110");
      break;
    case '7':
      result.append("0111");
      break;
    case '8':
      result.append("1000");
      break;
    case '9':
      result.append("1001");
      break;
    case 'A':
      result.append("1010");
      break;
    case 'B':
      result.append("1011");
      break;
    case 'C':
      result.append("1100");
      break;
    case 'D':
      result.append("1101");
      break;
    case 'E':
      result.append("1110");
      break;
    case 'F':
      result.append("1111");
      break;
    }
  }

  return result;
}
