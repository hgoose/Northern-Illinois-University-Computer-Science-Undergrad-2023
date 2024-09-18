#ifndef NIUCSCI340ASSIGN2_ALGOS_H
#define NIUCSCI340ASSIGN2_ALGOS_H

//***************************************************************************
//
//  assign2-algos.h
//  CSCI 340 Assignment  (2)
//
//  Created by Nate Warner z2004109
//
//***************************************************************************


#include <iomanip>
#include "assign2-algos.decl.h"

// Implement your algorithms for assignment 2 here.

#include <iostream>
#include <string>

using std::setw;

/**
 * Get token based on passed begin and end (strict), counts consecutive delimiters as tokens
 *
 * @param begin beginning of range
 * @param end end of range
 * @param delim the specified delimiter
 *
 * @return token_info struct (info about the collected token)
 *
 */
template <typename ITERATOR, typename T>
token_info<ITERATOR> get_next_token_strict(ITERATOR begin, ITERATOR end, T delim) {
  token_info<ITERATOR> just_stop;
  just_stop.t_begin = begin;
  just_stop.t_end = end;
  just_stop.t_next = end;

  // Find delim
  while (begin != end && *begin != delim) {
      ++begin;
  }

  // Found delim, mark stop
  just_stop.t_end = begin;

  // If we are at the end, set t_next to the end, if not, 
  // advance t_next one position from the end we marked above
  if (begin != end) {
      just_stop.t_next = ++begin;
  } else {
      just_stop.t_next = end;
  }

  return just_stop;
}

/**
 * Get token based on passed begin and end (greedy), doesn't care about consecutive delimiters, just skip them.
 *
 * @param begin beginning of range
 * @param end end of range
 * @param delim the specified delimiter
 *
 * @return token_info struct (info about the collected token)
 *
 */
template <typename ITERATOR, typename T>
token_info<ITERATOR> get_next_token_greedy(ITERATOR begin, ITERATOR end, T delim) {
  token_info<ITERATOR> just_stop;
  just_stop.t_begin = end;
  just_stop.t_end = end;
  just_stop.t_next = end;

  // While we are at delimiters, we just skip past all those. Don't really care too much about them.
  while (begin != end && *begin == delim) {
      ++begin;
  }

  // Found the first non-delim, set that as the beginning
  just_stop.t_begin = begin;

  // Find the end of the token (One past the end).
  while (begin != end && *begin != delim) {
      ++begin;
  }

  // Set the end
  just_stop.t_end = begin;

  // Eat any consecutive other delimiters after t_end is found
  while (begin != end && *begin == delim) {
      ++begin;
  }

  // Stop point found after eating the consecutive delimiters after t_end (if any)
  just_stop.t_next = begin;

  // Return info
  return just_stop;
}

/**
 * Function to get frequency of elements in a container, throw them in some histogram classes (bins)
 *
 * @param begin iterator to beginning of container
 * @param end iterator to one past end of container
 * @param bin_counts random access iterator to contain the counts of each bin
 * @param n number of bins
 * @param width width of each bin
 */
template<typename ITERATOR, typename RANDOM_ACCESS>
void histogram(ITERATOR begin, ITERATOR end, RANDOM_ACCESS & bin_counts, int N, double width) {
    // Set the counts to zeros
    for (int i=0; i<N; ++i) 
        bin_counts[i] = 0;

    // Iterate through the container
    int count = 0;
    for (ITERATOR it = begin; it != end; ++it, ++count) {
        // Find which bin we are in
        int bin = *it/width;

        // Check if the bin is valid. If it is, update the count in bin_counts
        if (bin >= 0 && bin <= N-1) {
            ++bin_counts[bin];
        }
    }
}

/**
 * Output container elements given a range
 *
 * @param ost ostream reference 
 * @param begin iterator to beginning of container 
 * @param end iterator to end of container
 * @param pre string to output before we output the container elements
 * @param sep element separator
 * @param post string to output after we output the container elements
 * @param width width of each element output
 */
template <typename ITERATOR>
void print_range(std::ostream & ost, ITERATOR begin, ITERATOR end, const std::string &pre, const std::string &sep, const std::string &post, int width) {
    // Get the size of the range (so we can not print a separator after the last output)
    int size = range_count(begin, end);

    // Also need to keep track of the count so we know if we are at size-1
    int count = 0;

    ost << pre;  // Output the pre message
    
    // Output the whole container (with specified width)
    for (ITERATOR it = begin; it!=end; ++it, ++count) {
        ost << setw(width)<< *it << (count < size-1 ? sep : "");
    }
    ost << post;  // Output the post message
};


/**
 * Function to get the sum of elements in a container
 *
 * @param begin iterator to beginning of container range
 * @param end iterator to end of container range
 *
 * @return double the sum of a range of a container
 *
 */
template <typename ITERATOR>
double range_sum(ITERATOR begin, ITERATOR end) {
    // Initialize sum to zero
    double sum = 0.0f;

    // Iterate through the container, get the sum of each element
    for (ITERATOR it=begin; it!=end; ++it)
        sum+=*it;

    // Return the result
    return sum;
}


/**
 * Get the average of elements in a container
 *
 * @param begin iterator to beginning of container range
 * @param end iterator to end of container range
 *
 * @return double for average of elements
 */
template <typename ITERATOR>
double range_avg(ITERATOR begin, ITERATOR end) {
  int n=0; // size
  double sum = 0.0f; // sum

  // \bar{x} = \frac{1}{n}\sum_{i=1}^{n}x_i, this reflects that.
  for (ITERATOR it=begin; it!=end; ++it, ++n)
      sum+=*it;
  return sum / n;
}


/**
 * Procure max element in container range
 *
 * @param begin iterator to beginning of container range
 * @param end iterator to end of container range
 *
 * @return auto for the max element, whatever type the container elements are
 */
template <typename ITERATOR>
auto range_maxval(ITERATOR begin, ITERATOR end) {
    // Assume the container max is the very first element
    auto max = *begin; 
    
    // Iterate through the container to see if our assumption is false
    for (ITERATOR it = begin; it!=end; ++it) {
        if (*it > max) { // Compare current element to current max
            max = *it; // Found a new max, update
        }
    }
    return max;
}


/**
 * Procure min element in container range
 *
 * @param begin iterator to beginning of container range
 * @param end iterator to end of container range
 *
 * @return auto for the min element, whatever type the container elements are
 */
template <typename ITERATOR>
auto range_minval(ITERATOR begin, ITERATOR end) {
    // Assume the container min is the very first element
    auto min = *begin;

    // Iterate through
    for (ITERATOR it = begin; it!=end; ++it) {
        // Check if current element is less than the current min
        if (*it < min) {
            min = *it; // Found a new min;
        }
    }
    return min;
}


/**
 * get the number of elements in container range
 *
 * @param begin iterator to beginning of container range
 * @param end iterator to end of container range
 *
 * @return int the number of elements in range
 */
template <typename ITERATOR>
int range_count(ITERATOR begin, ITERATOR end) {
  int count = 0;

  // Iterate through only to count how many times we do it.
  for (ITERATOR it = begin; it!=end; ++it, ++count);

  return count;
}


#endif /*NIUCSCI340ASSIGN2_ALGOS_H*/
