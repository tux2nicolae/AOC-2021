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

struct Packet
{
  long long version;  // 3bits
  long long type;     // 3bits {4 - literal value }

  // literal value
  long long number;

  // subpackets
  vector<Packet> nestedPackets;
};

long long CountVersionSum(const Packet & packet)
{
  long long subPacketsSum = 0;
  for (auto subPacket : packet.nestedPackets)
    subPacketsSum += CountVersionSum(subPacket);

  return packet.version + subPacketsSum;
}

long long DecodeTransmition(const Packet & packet)
{
  if (packet.type == 4)
    return packet.number;

  if (packet.type == 0)
  {
    long long subPacketsSum = 0;
    for (auto subPacket : packet.nestedPackets)
    {
      subPacketsSum += DecodeTransmition(subPacket);
    }

    return subPacketsSum;
  }
  else if (packet.type == 1)
  {
    long long product = 1;
    for (auto subPacket : packet.nestedPackets)
    {
      product *= DecodeTransmition(subPacket);
    }

    return product;
  }
  else if (packet.type == 2)
  {
    long long minValue = numeric_limits<long long>::max();
    for (auto subPacket : packet.nestedPackets)
    {
      minValue = min(minValue, DecodeTransmition(subPacket));
    }

    return minValue;
  }
  else if (packet.type == 3)
  {
    long long maxValue = 0;
    for (auto subPacket : packet.nestedPackets)
    {
      maxValue = max(maxValue, DecodeTransmition(subPacket));
    }

    return maxValue;
  }
  else if (packet.type == 5)
  {
    return DecodeTransmition(packet.nestedPackets[0]) > DecodeTransmition(packet.nestedPackets[1]);
  }
  else if (packet.type == 6)
  {
    return DecodeTransmition(packet.nestedPackets[0]) < DecodeTransmition(packet.nestedPackets[1]);
  }
  else if (packet.type == 7)
  {
    return DecodeTransmition(packet.nestedPackets[0]) == DecodeTransmition(packet.nestedPackets[1]);
  }

  assert(false);
  return 0;
}

Packet ParsePacket(string_view & binaryData)
{
  Packet result;

  result.version = AOC::BinaryStringToLongLong(binaryData.substr(0, 3));
  binaryData.remove_prefix(3);

  result.type = AOC::BinaryStringToLongLong(binaryData.substr(0, 3));
  binaryData.remove_prefix(3);

  // literal value
  if (result.type == 4)
  {
    string number;

    long long totalBits = 6;
    string    flag;

    do
    {
      flag = binaryData.substr(0, 1);
      binaryData.remove_prefix(1);

      number += binaryData.substr(0, 4);
      binaryData.remove_prefix(4);

      totalBits += 5;
    } while (flag == "1");

    result.number = AOC::BinaryStringToLongLong(number);

    // padding
    // binaryData.remove_prefix(4 - totalBits % 4);
  }
  else
  {
    auto lengthTypeId = binaryData.substr(0, 1);
    binaryData.remove_prefix(1);

    if (lengthTypeId == "0")
    {
      auto totalLength = binaryData.substr(0, 15);
      binaryData.remove_prefix(15);

      auto nextPackets = binaryData.substr(0, AOC::BinaryStringToLongLong(totalLength));
      binaryData.remove_prefix(AOC::BinaryStringToLongLong(totalLength));

      while (!nextPackets.empty())
      {
        result.nestedPackets.push_back(ParsePacket(nextPackets));
      }
    }
    else
    {
      auto subPacketsCount = binaryData.substr(0, 11);
      binaryData.remove_prefix(11);

      auto n = AOC::BinaryStringToLongLong(subPacketsCount);
      while (n--)
      {
        result.nestedPackets.push_back(ParsePacket(binaryData));
      }
    }
  }

  return result;
}

int main()
{
  ifstream in("..\\src\\_input.in");
  // ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  string        input;

  in >> input;
  auto binaryString = AOC::GetBinaryStringFromHexString(input);

  string_view binaryStringView(binaryString);
  auto        packet = ParsePacket(binaryStringView);

  auto sum              = CountVersionSum(packet);
  auto transmitionValue = DecodeTransmition(packet);
  // out
  // FStreamWriter writer(out);
  // writer.WriteVector(v);

  return 0;
}
