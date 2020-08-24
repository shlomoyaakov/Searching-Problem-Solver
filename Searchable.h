//
// Created by shlomo on 12/01/2020.
//

#ifndef EX4__SEARCHABLE_H_
#define EX4__SEARCHABLE_H_
#include "State.h"
#include "list"
using namespace std;
template<typename T>
class Searchable {
 public:
  virtual State<T> *getInitialState() = 0;
  virtual bool isGoalState(State<T> *s) = 0;
  virtual list<State<T> *> getAllPossibleStates(State<T> *s) = 0;
  virtual State<T> *getGoalState() { return nullptr; };
  virtual ~Searchable() = default;
};

#endif //EX4__SEARCHABLE_H_
