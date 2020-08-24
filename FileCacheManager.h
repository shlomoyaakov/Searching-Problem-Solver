//
// Created by shlomo on 11/01/2020.
//

#ifndef EX4__FILECACHEMANAGER_H_
#define EX4__FILECACHEMANAGER_H_
#include "CacheManager.h"
#include "unordered_map"
#include "list"
#include <iostream>
#include <map>
#include <string>
using namespace std;
class FileCacheManager : public CacheManager<string, string> {
  int currentSize;
  int capacity;
  list<pair<string, string>> doublyList;
  unordered_map<string, typename list<pair<string, string>>::iterator> cacheMap;
  unordered_map<string, bool> boolMap;
  void delFromCache(string);
  void checkCache();
  bool printToFile(string key, string obj);
  string readFromFile(string);
 public:
  FileCacheManager();
  void saveSolution(string, string);
  bool isThereSolution(string);
  string getSolution(string);
};

#endif //EX4__FILECACHEMANAGER_H_