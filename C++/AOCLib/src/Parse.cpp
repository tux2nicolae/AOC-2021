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

int AOC::BinaryStringToInt(const string& binaryValue)
{
    return stoi(binaryValue, 0, 2);
}
