
#ifndef EX4_5__MYTESTCLIENTHANDLER_H_
#define EX4_5__MYTESTCLIENTHANDLER_H_
#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"
class MyTestClientHandler : public ClientHandler {
  CacheManager<string,string> *cache_manager;
  Solver<string,string> *solver;
 public:
  MyTestClientHandler(CacheManager<string,string> *, Solver<string,string> *);
  void handleClient(int);
};

#endif //EX4_5__MYTESTCLIENTHANDLER_H_
