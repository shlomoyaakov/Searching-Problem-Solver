
#ifndef EX4_5_ASTAR_H
#define EX4_5_ASTAR_H
#include "Searcher.h"
#include "unordered_map"
#include "queue"
#include <cmath>
#include <set>
#include "Point.h"
template<typename T>
class AStar : public Searcher<T, vector<State<T>>> {
  int num_of_node_evaluated = 0;
  StatePriorityQueue<Point> open_list;
  set<State<T>> closed;
  unordered_map<T,double> realCost;

  void emptyOpenlist(){
    while (!(open_list.isEmpty()))
      open_list.poll();
  }

 public:
  int getSearcherID(){return 1;}
  Searcher<T, vector<State<T>>> *getClone() {
    return new AStar<T>();
  };

  int getNumberOfNodeEvaluated() {
    return num_of_node_evaluated;
  }

  Solution<vector<State<T>>> search(Searchable<T> &searchable) {
    num_of_node_evaluated = 0;
    emptyOpenlist();
    closed.clear();
    realCost.clear();
    double f_value;
    double gCost;
    unordered_map<T, bool> map;
    State<T>* initalState = searchable.getInitialState();
    // start node is the initialize node
    open_list.push(initalState);
    list<State<T>*> successors;
    realCost[initalState->getState()]=initalState->getCost();
    while(!open_list.isEmpty()){
      State<T> *n = open_list.poll();
      // count the number of nodes we open
      num_of_node_evaluated++;
      if (searchable.isGoalState(n))
        // if we find the goal, generate the path from start to it
        return reconstruct_path(*n);
      closed.insert(*n);
      map[n->getState()] = true;
      successors = searchable.getAllPossibleStates(n);
      for(State<T> * state: successors){
        gCost =realCost[n->getState()]+state->getCost()-n->getCost();
        f_value = gCost+getH(*state,searchable);
        state->setCost(f_value);
        if (map.find(state->getState()) == map.end() && !open_list.contain(*state)) {
          open_list.push(state);
          realCost[state->getState()]=gCost;
        } else if (open_list.contain(*state)) {
          if (state->getCost() < open_list.getStateCost(*state)) {
            open_list.remove(*state);
            open_list.push(state);
            realCost[state->getState()]=gCost;
          }
        }
      }
    }
    // open set in empty but goal never found
    throw "cant reach goal";
  }

  Solution<vector<State<T>>> reconstruct_path(State<T> current) {
    //create the path of solution
    vector<State<T>> total_path;
    current.setCost(realCost[current.getState()]);
    total_path.push_back(current);
    while (current.getCameFrom() != NULL) {
      current = *(current.getCameFrom());
      current.setCost(realCost[current.getState()]);
      total_path.push_back(current);
    }
    vector<State<T>> ret_vec;
    for (int i = total_path.size() - 1; i >= 0; i--) {
      ret_vec.push_back(total_path[i]);
    }
    Solution<vector<State<T>>> solution;
    solution.SetSolutionDescribe(ret_vec);
    return solution;
  }

  double getH(State<Point> node, Searchable<Point> &searchable) {
    //get the h distance between a node and the goal node
    State<Point> *goal = searchable.getGoalState();
    int dx = abs(node.getState().getX() - goal->getState().getX());
    int dy = abs(node.getState().getY() - goal->getState().getY());
    return (dx + dy);
  }

};

#endif //EX4_5_ASTAR_H