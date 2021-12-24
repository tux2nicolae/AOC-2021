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

unordered_map<string, int> variables;

int         dataIt = 0;
vector<int> inputData1{ 4, 5, 3, 1, 1, 1, 9, 1, 5, 1, 6, 1, 1, 1 };
vector<int> inputData2{ 9, 9, 9, 9, 9, 7, 9, 5, 9, 1, 9, 4, 5, 6 };

int readNextData()
{
  return inputData1[dataIt++];
}

void RunOperation(string operation, string a, string b)
{
  if (operation == "inp")
  {
    variables[a] = readNextData();
    cout << "-----------------------inp [" << a << "=" << variables[a] << "]-----------------"
         << endl;
  }
  else
  {
    int var = 0;
    if (b.size() == 1 && b[0] >= 'a' && b[0] <= 'z')
    {
      var = variables[b];
    }
    else
      var = stoi(b);

    if (operation == "add")
    {
      cout << a << "+=" << b << " (" << var << ")";

      variables[a] = variables[a] + var;
    }
    else if (operation == "mul")
    {
      cout << a << "*=" << b << " (" << var << ")";

      variables[a] = variables[a] * var;
    }
    else if (operation == "div")
    {
      cout << a << "/=" << b << " (" << var << ")";

      assert(var != 0);
      variables[a] = variables[a] / var;
    }
    else if (operation == "mod")
    {
      cout << a << "%=" << b << " (" << var << ")";

      assert(var != 0);
      variables[a] = variables[a] % var;
    }
    else if (operation == "eql")
    {
      cout << a << "=" << a << "==" << b << " (" << var << ")  ================ ";
      variables[a] = variables[a] == var;
    }

    cout << "  -> " << variables[a] << endl;
  }
}

int main()
{
  ifstream in("..\\src\\_input.in");
  // ofstream out("..\\src\\_output.out");

  FStreamReader reader(in);
  while (in.good())
  {
    string operation, from, to;
    in >> operation >> from;

    if (operation != "inp")
    {
      in >> to;
    }

    RunOperation(operation, from, to);
  }

  cout << "VALID : " << variables["z"];

  // for (int i = 0; i < lines.size(); i++)
  // {
  //   for (int j = 0; j < lines[i].size(); j++)
  //   {
  //   }
  // }

  return 0;
}
