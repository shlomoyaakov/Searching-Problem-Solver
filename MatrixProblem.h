
#ifndef EX4_5__MATRIXPROBLEM_H_
#define EX4_5__MATRIXPROBLEM_H_
#include "Point.h"
#include <cstring>

using namespace std;
class MatrixProblem {
  int **matrix;
  int rows_num;
  int cols_num;
  Point start;
 public:
  int **GetMatrix() const {
    return matrix;
  }
  int GetRowsNum() const {
    return rows_num;
  }
  int GetColsNum() const {
    return cols_num;
  }
  const Point &GetStart() const {
    return start;
  }
  const Point &GetFinish() const {
    return finish;
  }
 private:
  Point finish;
 public:
  MatrixProblem(){}
  MatrixProblem(int **m, Point s, Point f, int r, int c) {
    this->matrix = m;
    this->start = s;
    this->finish = f;
    this->rows_num = r;
    this->cols_num = c;
  }
  int getValuebyIndex(int x,int y){
    return this->matrix[x][y];
  }
  string toString() {
    // make a string that contains all the problem (matrix + start point + end point)
    // its necessary for hashing the problem
    string str="";
    str+= to_string(start.getX())+to_string(start.getY());
    str+=to_string(finish.getX())+to_string(finish.getY());
    for (int i = 0; i < rows_num; i++){
      for (int j = 0; j < cols_num; j++){
        str+=to_string(matrix[i][j]);
      }
    }
    return str;
  }

};
#endif //EX4_5__MATRIXPROBLEM_H_
