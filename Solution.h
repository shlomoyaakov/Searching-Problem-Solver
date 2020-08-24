
#ifndef EX4_5__SOLUTION_H_
#define EX4_5__SOLUTION_H_
template<typename T>
class Solution{
 private:
  T solution_describe;
 public:
  T GetSolutionDescribe() const {
    return solution_describe;
  }
  void SetSolutionDescribe(T s) {
    Solution::solution_describe = s;
  }
};
#endif //EX4_5__SOLUTION_H_
