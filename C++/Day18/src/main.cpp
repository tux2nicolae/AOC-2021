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

struct Node
{
  optional<int> val;

  shared_ptr<Node> left;
  shared_ptr<Node> right;
};

shared_ptr<Node> ParseSnailfish(string_view & snailfish)
{
  auto node = make_shared<Node>();

  if (snailfish[0] != '[')
  {
    node->val = stoi(string(snailfish.substr(0, 1)));
    snailfish.remove_prefix(1);

    return node;
  }

  assert(snailfish[0] == '[');
  snailfish.remove_prefix(1);

  node->left = ParseSnailfish(snailfish);

  assert(snailfish[0] == ',');
  snailfish.remove_prefix(1);

  node->right = ParseSnailfish(snailfish);

  assert(snailfish[0] == ']');
  snailfish.remove_prefix(1);

  return node;
}

shared_ptr<Node> AddSnailfishes(shared_ptr<Node> left, shared_ptr<Node> right)
{
  auto result   = make_shared<Node>();
  result->left  = left;
  result->right = right;

  return result;
}

void ExplodeSnailfishHelper(shared_ptr<Node> &         node,
                            shared_ptr<Node> &         firstLeftVal,
                            shared_ptr<Node> &         nextRigthVal,
                            optional<pair<int, int>> & exploded,
                            int                        deep)
{
  if (node->val)
  {
    if (!exploded)
      firstLeftVal = node;

    if (exploded && !nextRigthVal)
      nextRigthVal = node;

    return;
  }

  if (deep == 4 && !exploded)
  {
    exploded = make_pair(*node->left->val, *node->right->val);

    node->left  = nullptr;
    node->right = nullptr;
    node->val   = 0;
    return;
  }

  ExplodeSnailfishHelper(node->left, firstLeftVal, nextRigthVal, exploded, deep + 1);
  ExplodeSnailfishHelper(node->right, firstLeftVal, nextRigthVal, exploded, deep + 1);
}

bool ExplodeSnailfish(shared_ptr<Node> & node)
{
  shared_ptr<Node>         firstLeftVal;
  shared_ptr<Node>         nextRigthVal;
  optional<pair<int, int>> exploded;

  ExplodeSnailfishHelper(node, firstLeftVal, nextRigthVal, exploded, 0);

  if (exploded)
  {
    if (firstLeftVal)
      *firstLeftVal->val += exploded->first;

    if (nextRigthVal)
      *nextRigthVal->val += exploded->second;

    return true;
  }

  return false;
}

bool SplitSnailfish(shared_ptr<Node> & node)
{
  assert(node != nullptr);

  if (node->val && node->val >= 10)
  {
    node->left      = make_shared<Node>();
    node->left->val = *node->val / 2;

    node->right      = make_shared<Node>();
    node->right->val = (*node->val / 2) + (*node->val % 2);

    node->val = nullopt;
    return true;
  }

  if (node->val)
    return false;

  if (SplitSnailfish(node->left))
    return true;

  if (SplitSnailfish(node->right))
    return true;

  return false;
}

void Print(shared_ptr<Node> & node)
{
  if (node->val)
  {
    cout << *node->val;
    return;
  }

  cout << "[";
  Print(node->left);
  cout << ",";
  Print(node->right);
  cout << "]";
}

void ReduceSnailfish(shared_ptr<Node> node)
{
  while (ExplodeSnailfish(node) || SplitSnailfish(node))
  {
  };
}

long long ComputeMagnitude(shared_ptr<Node> node)
{
  if (node->val)
  {
    return *node->val;
  }

  return 3 * ComputeMagnitude(node->left) + 2 * ComputeMagnitude(node->right);
}

int main()
{
  ifstream in("..\\src\\_input.in");
  // ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  auto          input = reader.ReadLines();

  string_view firstSnailfish = input[0];
  auto        result         = ParseSnailfish(firstSnailfish);

  for (int i = 1; i < input.size(); i++)
  {
    string_view snailfish = input[i];

    result = AddSnailfishes(result, ParseSnailfish(snailfish));
    ReduceSnailfish(result);

    Print(result);
    cout << endl;
  }

  cout << ComputeMagnitude(result) << endl;

  // part 2
  {
    long long maxMagnitude = 0;
    for (int i = 0; i < input.size(); i++)
    {
      for (int j = 0; j < input.size(); j++)
      {
        if (i == j)
          continue;

        string_view firstSnailfish  = input[i];
        string_view secondSnailfish = input[j];

        auto result =
          AddSnailfishes(ParseSnailfish(firstSnailfish), ParseSnailfish(secondSnailfish));

        ReduceSnailfish(result);

        maxMagnitude = max(maxMagnitude, ComputeMagnitude(result));
      }
    }

    cout << maxMagnitude << endl;
  }

  // out
  // FStreamWriter writer(out);
  // writer.WriteVector(v);

  return 0;
}
