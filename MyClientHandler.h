

#ifndef EX4_5__MYTESTCLIENTHANDLER_H_
#define EX4_5__MYTESTCLIENTHANDLER_H_
#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "MatrixProblem.h"
#include "Solution.h"
#include "State.h"
#include <chrono>
#include <thread>
#include <mutex>
class MyClientHandler : public ClientHandler {
  CacheManager<string, string> *cache_manager;
  Solver<Problem<MatrixProblem>, Solution<string>> *solver;
  mutex locker;
 public:
  MyClientHandler(CacheManager<string, string> *c, Solver<Problem<MatrixProblem>, Solution<string>> *s);
  void handleClient(int);
  int getNumberOfCols(string);
  ClientHandler *getClone() {
    return new MyClientHandler(cache_manager, solver->getClone());
  }
  bool checkProblemValidation(Point, Point, int, int, int);
};

#endif //EX4_5__MYTESTCLIENTHANDLER_H_
