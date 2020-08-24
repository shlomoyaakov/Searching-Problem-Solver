//
// Created by shlomo on 11/01/2020.
//

#ifndef EX4__CACHEMANAGER_H_
#define EX4__CACHEMANAGER_H_
#include <iostream>
using namespace std;
template<typename P,typename S>
class CacheManager {
 public:
  CacheManager<P,S>(){};
  virtual void saveSolution(P, S) = 0;
  virtual bool isThereSolution(P) = 0;
  virtual S getSolution(P) = 0;
  virtual ~CacheManager() {};
};

#endif //EX4__CACHEMANAGER_H_