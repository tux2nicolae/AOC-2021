#pragma once

/**
 * Advent of code 2021
 * @author : Nicolae Telechi
 */
class FStreamReader
{
public:
  /**
   * Input stream
   */
  FStreamReader(ifstream & aIn);

  /**
   * @returns true if there is more data to read
   */
  bool IsValid();

  //-----------------------------------------------------------

  vector<int>    ReadLineAsNumbers();
  vector<int>    ReadLineAsDigits();
  vector<string> ReadLineAsWords();

  vector<string> ReadLines();

  vector<vector<int>>    ReadDataAsMatrixOfNumbers();
  vector<vector<int>>    ReadDataAsMatrixOfDigits();
  vector<vector<string>> ReadDataAsMatrixOfWords();

  //-----------------------------------------------------------

  template <typename T = int>
  vector<T> ReadDataAs()
  {
    vector<T> ret;

    T n = 0;
    while (mFileStream >> n)
      ret.push_back(n);

    return ret;
  }

  template <typename T = int>
  list<T> ReadDataAsListOf()
  {
    list<T> ret;

    T n = 0;
    while (mFileStream >> n)
      ret.push_back(n);

    return ret;
  }

  template <typename T = int>
  vector<T> ReadLineSeparatedByCharAs()
  {
    vector<T> ret;

    string line;
    if (!getline(mFileStream, line))
      return ret;

    std::istringstream ss(line);

    while (ss.good())
    {
      T    x{};
      char _{};

      ss >> x >> _;
      ret.push_back(x);
    }

    return ret;
  }

  template <typename T = int>
  vector<T> ReadDataSeparatedByCharAs()
  {
    vector<T> ret;
    while (mFileStream.good())
    {
      T    x{};
      char _{};

      mFileStream >> x >> _;
      ret.push_back(x);
    }

    return ret;
  }

private:
  ifstream & mFileStream;
};
