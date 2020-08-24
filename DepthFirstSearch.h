
#ifndef EX4_5__DEPTHFIRSTSEARCH_H_
#define EX4_5__DEPTHFIRSTSEARCH_H_
//
// Created by daniels on 12/01/2020.

#include <stack>
#include "Searcher.h"
#include "unordered_map"
#include "queue"
#include "Stack.h"
template<typename T>
class DepthFirstSearch : public Searcher<T, vector<State<T>>> {
  int num_of_node_evaluated = 0;
 public:
  Searcher<T, vector<State<T>>> *getClone() {
    return new DepthFirstSearch<T>();
  };
  int getNumberOfNodeEvaluated() { return num_of_node_evaluated; }
  Solution<vector<State<T>>> search(Searchable<T> &searchable) {
    Stack<State<T> *> stack;
    State<T> *v;
    list<State<T> *> list;
    unordered_map<T, bool> discovered_map;
    // push stack the start node
    stack.push(searchable.getInitialState());
    while (!stack.empty()) {
      // count the nodes we get in
      num_of_node_evaluated++;
      v = stack.top();
      stack.pop();
      if (searchable.isGoalState(v)) {
        // if we reach the goal state, make the path and return it
        return backTrace(*v);
      }
      if (discovered_map.find(v->getState()) == discovered_map.end()) {
        discovered_map[v->getState()] = true;
        list = searchable.getAllPossibleStates(v);
        for (State<T> *s : list) {
          if (discovered_map.find(s->getState()) == discovered_map.end()) {
            stack.push(s);
          }
        }
      }
    }
    throw "cant reach goal";
  }
  Solution<vector<State<T>>> backTrace(State<T> s) {
    // make the path from goal to the start point
    vector<State<T>> vec;
    vec.push_back(s);
    while (s.getCameFrom() != NULL) {
      s = *(s.getCameFrom());
      vec.push_back(s);
    }
    vector<State<T>> ret_vec;
    for (int i = vec.size() - 1; i >= 0; i--) {
      ret_vec.push_back(vec[i]);
    }
    Solution<vector<State<T>>> solution;
    solution.SetSolutionDescribe(ret_vec);
    return solution;
  }
  int getSearcherID(){return 4;}
};

#endif //EX4_5__DEPTHFIRSTSEARCH_H_
