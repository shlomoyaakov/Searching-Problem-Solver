//
// Created by shlomo on 14/01/2020.
//

#include "MatrixSearchable.h"
MatrixSearchable::MatrixSearchable(MatrixProblem *m) {
  matrix_problem = m;
  Point start_point = m->GetStart();
  init_state = new State<Point>(start_point);
  init_state->setCameFrom(NULL);
  init_state->setCost(m->getValuebyIndex(start_point.getX(), start_point.getY()));
  goal_state = new State<Point>(m->GetFinish());
  total_states.push_front(init_state);
  total_states.push_front(goal_state);
}
bool MatrixSearchable::isGoalState(State<Point> *s) {
  return (this->matrix_problem->GetFinish() == s->getState());
}
State<Point> *MatrixSearchable::getInitialState() {
  return init_state;
}
State<Point> *MatrixSearchable::getGoalState() {
  return goal_state;
}

list<State<Point> *> MatrixSearchable::getAllPossibleStates(State<Point> *s) {
  // check and return all the possible states we can generate from the state s according the walls and the matrix limits
  list<State<Point> *> list;
  int x = s->getState().getX();
  int y = s->getState().getY();
  if (x < (matrix_problem->GetRowsNum() - 1)) {
    Point p{x + 1, y};
    int value = this->matrix_problem->getValuebyIndex(x + 1, y);
    if (value != -1) {
      State<Point> *newState = new State<Point>(p);
      newState->setCameFrom(s);
      newState->setCost(s->getCost() + value);
      list.push_front(newState);
      total_states.push_front(newState);
    }
  }
  if (y < (matrix_problem->GetColsNum() - 1)) {
    Point p{x, y + 1};
    int value = this->matrix_problem->getValuebyIndex(x, y + 1);
    if (value != -1) {
      State<Point> *newState = new State<Point>(p);
      newState->setCameFrom(s);
      newState->setCost(s->getCost() + value);
      list.push_front(newState);
      total_states.push_front(newState);
    }
  }
  if (x > 0) {
    Point p{x - 1, y};
    int value = this->matrix_problem->getValuebyIndex(x - 1, y);
    if (value != -1) {
      State<Point> *newState = new State<Point>(p);
      newState->setCameFrom(s);
      newState->setCost(s->getCost() + value);
      list.push_front(newState);
      total_states.push_front(newState);
    }
  }
  if (y > 0) {
    Point p{x, y - 1};
    int value = this->matrix_problem->getValuebyIndex(x, y - 1);
    if (value != -1) {
      State<Point> *newState = new State<Point>(p);
      newState->setCameFrom(s);
      newState->setCost(s->getCost() + value);
      list.push_front(newState);
      total_states.push_front(newState);
    }
  }
  return list;
}
MatrixSearchable::~MatrixSearchable() {
  // free all the states we have created
  for (State<Point> *s : total_states)
    if (s != nullptr)
      delete (s);
}
