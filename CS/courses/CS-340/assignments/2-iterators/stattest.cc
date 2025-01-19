#include <iostream>
#include <iterator>
#include <vector>
#include <deque>
#include <list>
#include <string>
#include <unistd.h> // for getopt

#include "assign2-algos.h"

template <class T>
std::string to_string(const T &val) {
  std::stringstream ss;
  ss << val;
  return ss.str();
}

template <typename CONTAINER, bool PRINT_RANGE=false> 
void run_test(CONTAINER &c, const char *label) {
  using std::cout, std::endl;
  cout << "TEST: " << label << "\n";
  //cout << "    size() of container passed in: " << c.size() << endl;
  
  auto begin = c.begin();
  auto end = c.end();

  std::ostream_iterator <typename CONTAINER::value_type > oi(std::cout, " "); 
  cout << "    "; std::copy(c.begin(), c.end(), oi); cout << "\n";
  cout << "    range_count: " << range_count(begin, end) << "\t";
  cout << "    range_sum: " << range_sum(begin, end) << "\t";
  cout << "    range_avg: " << range_avg(begin, end) << endl;
  cout << "    range_maxval: " << range_maxval(begin, end) << "\t";
  cout << "    range_minval: " << range_minval(begin, end) << endl;

  std::cout << "\n";
}

template <typename T, class CONTAINER, bool PRINT_RANGE=false>
void test_set(const char * container_type, const char * element_type, int length, T startval, T stride) {
  char labelbuf[255];

  CONTAINER ivec;

  // Test with a vector of `veclength` items with constant value `constval`
  ivec.clear();
  for(int i = 0; i < length; ++i) ivec.push_back(startval);

  snprintf(labelbuf, 255, "%s of %d %s with constant value %s", container_type, length, element_type, to_string(startval).data());
  run_test<CONTAINER, PRINT_RANGE>(ivec, labelbuf); 

  // Test with a vector of `veclength` items with constant value `constval`
  ivec.clear();
  T val = startval;
  for(int i = 0; i < length; ++i) {
    ivec.push_back(val); 
    val += stride;
  }


  snprintf(labelbuf, 255, "%s of %d %s starting at %s, incrementing by %s",
            container_type, length, element_type, to_string(startval).data(), to_string(stride).data());
  run_test<CONTAINER, PRINT_RANGE>(ivec, labelbuf); 

   


}


int main(int argc, char *argv[]) {
  using std::cout, std::endl;
  cout << "// stattest: Test your algorithms calculating statistics from a range.\n";
  cout << "/////////////////////////////////////////////////////////////////////////\n";

  int length = 10; // default
  int startval = 10;
  int stride = 10;

  bool vflag = false; // do vector tests (default if none passed)
  bool dflag = false; // do deque tests
  bool lflag = false; // do list tests
  bool sflag = false; // use standard input to get values

  const char * optstring = "vdl";
  int opt;
  while( (opt = getopt(argc, argv, optstring)) != -1) {
    switch(opt) {
      case 'v':
        vflag = true; break;
      case 'd':
        dflag = true; break;
      case 'l':
        lflag = true; break;
    }
  }

  if(sflag) { // get the values


  }
  else { // use default values
    if(vflag || (!vflag && !dflag && !lflag)) { // vector is the default if nothing else is used
      test_set<int,   std::vector<int>,   true>("vector", "integer(s)", length, startval, stride);
      test_set<float, std::vector<float>, true>("vector", "float(s)",   length, (float) startval + .5, (float) stride);
    }
    if(dflag) { // use deque
      test_set<int,   std::deque<int>,   true>("deque", "integer(s)", length, startval, stride);
      test_set<float, std::deque<float>, true>("deque", "float(s)",   length, (float) startval + .5, (float) stride);
    }
    if(lflag) { // use deque
      test_set<int,   std::list<int>,   true>("list", "integer(s)", length, startval, stride);
      test_set<float, std::list<float>, true>("list", "float(s)",   length, (float) startval + .5, (float) stride);
    }
  }
};


