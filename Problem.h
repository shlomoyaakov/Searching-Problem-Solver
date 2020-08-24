//
// Created by shlomo on 13/01/2020.
//

#ifndef EX4__PROBLEM_H_
#define EX4__PROBLEM_H_
template<typename T>
class Problem {
 private:
  T problem_describe;
 public:
  Problem(T p) {
    this->problem_describe = p;
  }
  T GetProblemDescribe() const {
    return this->problem_describe;
  }
};

#endif //EX4__PROBLEM_H_
