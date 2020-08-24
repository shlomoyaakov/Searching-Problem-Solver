
#ifndef EX4_5_STATEPRIORITYQUEUE_H
#define EX4_5_STATEPRIORITYQUEUE_H
#include "State.h"
#include <bits/stdc++.h>
#include "queue"
#include "vector"
using namespace std;
template<typename T>
class StatePriorityQueue {
  unordered_map<T, bool> contains_map;
  vector<State<T> *> pq;
  map<State<T>, double> costOfState;
  int binarySearch(double cost, int size, int location) {
    // search a var
    if (size == 0) {
      return location;
    }
    if (size == 1) {
      if (cost < pq[location]->getCost()) {
        return location;
      } else {
        return location + 1;
      }
    }
    int newSize = size / 2;
    if (cost < pq[location + newSize]->getCost()) {
      return binarySearch(cost, newSize, location);
    } else {
      return binarySearch(cost, size - newSize, location + newSize);
    }
  }
  int findState(T s) {
    // return that var index in pq
    int i, size = pq.size();
    for (i = 0; i < size; i++) {
      if (pq[i]->getState() == s) {
        return i;
      }
    }
    return i;
  }
 public:
  bool contain(State<T> s) {
    // check if a var inside the pq
    if (contains_map.find(s.getState()) == contains_map.end()) return false;
    return (contains_map[s.getState()]);
  }
  void remove(State<T> s) {
    // delete a var from pq
    if (!contain(s)) {
      throw "The state does not exist";
    }
    contains_map.erase(s.getState());
    int i = findState(s.getState());
    pq.erase(pq.begin() + i);
    this->costOfState.erase(s.getState());
  }
  double getStateCost(State<T> s) {
    // get the cosr of a var in pq
    if (!contain(s)) {
      throw "The state does not exist";
    }
    return this->costOfState[s];
  }
  State<T> *poll() {
    // get the smallest element in pq
    if (pq.size() == 0) {
      throw "The queue is empty";
    }
    State<T> *s = pq[0];
    this->costOfState.erase(s->getState());
    pq.erase(pq.begin());
    contains_map.erase(s->getState());
    return s;
  }
  void push(State<T> *s) {
    // push element to pq
    int i = binarySearch(s->getCost(), pq.size(), 0);
    if (contain(*s)) {
      remove(*s);
    }
    contains_map[s->getState()] = true;
    this->costOfState[*s] = s->getCost();
    pq.insert(pq.begin() + i, s);
  }
  int GetCount() const {
    return pq.size();
  }
  bool isEmpty() {
    return pq.size() == 0;
  }
  void printQueue() {
    for (State<T> *s : pq) {
      cout << s->getState() << ": " << s->getCost() << endl;
    }
  }
};
#endif //EX4_5_STATEPRIORITYQUEUE_H