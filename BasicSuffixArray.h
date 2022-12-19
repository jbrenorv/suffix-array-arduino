/*
 * Basic implementation of Suffix Array
 * Time Complexity: O(n*log^2(n))
 * Auxiliary Space: 10n -> O(n)
 * Font: https://codeforces.com/edu/course/2
 */

#ifndef BasicSuffixArray_H
#define BasicSuffixArray_H

  #include "IterativeQuickSort.h"
  #include "Pair.h"

  void buildSuffixArray(uint8_t *suffixArray, char *inputText, const uint8_t inputTextLength) {
    uint8_t c[inputTextLength];
    
    {
      // k = 0
      char charToReadInput;
      pair<char, uint8_t> a[inputTextLength];
      for (uint8_t i = 0; i < inputTextLength; i++) {
        charToReadInput = pgm_read_byte_near(inputText + i);
        a[i] = {charToReadInput, i};
      }
      
      quickSortIterative(a, 0, inputTextLength-1);

      for (uint8_t i = 0; i < inputTextLength; i++)
        suffixArray[i] = a[i].second;
      c[suffixArray[0]] = 0;
      for (uint8_t i = 1; i < inputTextLength; i++)
      {
        if (a[i].first == a[i - 1].first)
          c[suffixArray[i]] = c[suffixArray[i - 1]];
        else
          c[suffixArray[i]] = c[suffixArray[i - 1]] + 1;
      }
    }

    uint8_t k = 0;
    while ((1 << k) < inputTextLength)
    {
      // k -> k+1
      pair<pair<uint8_t, uint8_t>, uint8_t> a[inputTextLength];
      for (uint8_t i = 0; i < inputTextLength; i++)
          a[i] = {{c[i], c[(i + (1 << k)) % inputTextLength]}, i};
      quickSortIterative(a, 0, inputTextLength-1);
      for (uint8_t i = 0; i < inputTextLength; i++)
        suffixArray[i] = a[i].second;
      c[suffixArray[0]] = 0;
      for (uint8_t i = 1; i < inputTextLength; i++)
      {
        if (a[i].first == a[i - 1].first)
          c[suffixArray[i]] = c[suffixArray[i - 1]];
        else
          c[suffixArray[i]] = c[suffixArray[i - 1]] + 1;
      }
      k++;
    }
  }

#endif
