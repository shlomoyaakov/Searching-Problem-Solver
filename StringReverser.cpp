

#include <algorithm>
#include "StringReverser.h"
string StringReverser::solve(string str) {
  //reverse the string
  string reverse_str = str;
  reverse(reverse_str.begin(), reverse_str.end());
  return reverse_str;
}
