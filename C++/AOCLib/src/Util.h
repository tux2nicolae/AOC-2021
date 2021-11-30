#pragma once

/**
 * Advent of code 2021
 * @author : Nicolae Telechi
 */
namespace AOC
{
  namespace detail
  {
    template<size_t k>
    void GenerateCombinationsRecursive(vector<array<size_t, k>>& combinations,
      array<size_t, k>& temp,
      size_t n,
      size_t from,
      size_t depth)
    {
      if (depth == k) {
        combinations.push_back(temp);
        return;
      }

      for (size_t i = from; i < n; ++i) {
        temp[depth] = i;
        GenerateCombinationsRecursive(combinations, temp, n, i + 1, depth + 1);
      }
    }
  }

  template<size_t k = 1>
  vector<std::array<size_t, k>> GenerateIndexCombinations(size_t n)
  {
    vector<std::array<size_t, k>> combinations;

    array<size_t, k> temp;
    detail::GenerateCombinationsRecursive<k>(combinations, temp, n, 0, 0);

    return combinations;
  }
}
