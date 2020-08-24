
#ifndef EX4_5__MYSTRINGSOLVER_H_
#define EX4_5__MYSTRINGSOLVER_H_
#include "Solver.h"
#include <string>
using namespace std;
class StringReverser:public Solver<Solution<string>,Problem<string>>{
  string solve(string);
};
#endif //EX4_5__MYSTRINGSOLVER_H_
