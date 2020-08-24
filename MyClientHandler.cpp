

#include "MyClientHandler.h"
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "MatrixProblem.h"
#include "Solution.h"
#include "State.h"
using namespace std;
MyClientHandler::MyClientHandler(CacheManager<string, string> *c, Solver<Problem<MatrixProblem>, Solution<string>> *s) {
  this->cache_manager = c;
  this->solver = s;
}

int MyClientHandler::getNumberOfCols(string line) {
  int c = 1;
  for (char ch:line) {
    if (ch == ',')
      c++;
  }
  return c;
}
void MyClientHandler::handleClient(int client_socket) {
  string all_matrix = "";
  char buffer[2048] = {0};
  vector<string> from_client;
  string str;
  string solve_str;
  // read from client first line
  read(client_socket, buffer, 2048);
  str = buffer;
  if (str != "\n")
    all_matrix += str;
  string end = "end";
  // read until its reach the "end" word
  while (str.find(end) == string::npos) {
    char buffer2[2048] = {0};
    read(client_socket, buffer2, 2048);
    str = buffer2;
    if (str != "\n")
      all_matrix += str;
  }
  int i = 0;
  // split it to lines and enter to a from_client vector
  while (all_matrix[i] != 'e') {
    string temp = "";
    while (all_matrix[i] != '\n') {
      temp += all_matrix[i];
      i++;
    }
    i++;
    from_client.insert(from_client.end(), temp);
  }
  // convert it to int[][] form
  string number, line;
  int r = (int) from_client.size() - 2;
  int c = getNumberOfCols(from_client[0]);
  int **matrix = (int **) malloc(r * sizeof(int *));
  for (i = 0; i < r; i++)
    matrix[i] = (int *) malloc(c * sizeof(int));

  for (i = 0; i < r; i++) {
    int j = 0;
    line = from_client[i];
    size_t pos = 0;
    while ((pos = line.find(",")) != std::string::npos) {
      number = line.substr(0, pos);
      line.erase(0, pos + 1);
      matrix[i][j] = stoi(number);
      j++;
    }
    pos = line.length();
    number = line.substr(0, pos);
    line.erase(0, pos + 1);
    matrix[i][j] = stoi(number);
  }
  // extract the start and finish point
  Point start, finish;
  line = from_client[from_client.size() - 2];
  size_t pos = 0;
  pos = line.find(",");
  number = line.substr(0, pos);
  line.erase(0, pos + 1);
  start.setX(stoi(number));
  pos = line.length();
  number = line.substr(0, pos);
  line.erase(0, pos + 1);
  start.setY(stoi(number));
  line = from_client[from_client.size() - 1];
  pos = line.find(",");
  number = line.substr(0, pos);
  line.erase(0, pos + 1);
  finish.setX(stoi(number));
  pos = line.length();
  number = line.substr(0, pos);
  line.erase(0, pos + 1);
  finish.setY(stoi(number));
  // check if the start and finish points is inside the matrix
  if (!checkProblemValidation(start, finish, r, c, client_socket)) {
    return;
  }
  // generate the problem and make a uniq hash for it
  MatrixProblem matrix_problem(matrix, start, finish, r, c);
  hash < string > hasher;
  auto hashed = hasher(matrix_problem.toString());
  string key = to_string(hashed);
  key += ("_" + to_string(solver->getSolverID()));
  // check if there is a solved solution for the problem
  if (cache_manager->isThereSolution(key)) {
    locker.lock();
    solve_str = cache_manager->getSolution(key);
    locker.unlock();
    cout << "problem " << key << " exists in file system, sending solution to client.." << endl;
  } else {
    cout << "problem " << key << " do not exists in file system, solving.." << endl;
    auto *problem = new Problem<MatrixProblem>(matrix_problem);
    try {
      // try to solve the problem, if there is no solution send an appropriate message to client
      solve_str = (solver->solve(*problem)).GetSolutionDescribe();
    }catch (...){
      solve_str = "invalid problem, no path found between start point to finish point";
      char *temp = (char *) malloc((solve_str.length() + 1) * sizeof(char));
      strcpy(temp, solve_str.c_str());
      int is_sent = send(client_socket, temp, strlen(temp), 0);
      free(temp);
      if (is_sent == -1) {
        std::cout << "Error sending message" << std::endl;
      }
      delete (problem);
      close(client_socket);
      cout << "cant solve problem, disconnect client.." << endl;
      return;
    }
    cout << "problem solved! sending solution to client.." << endl;
    delete (problem);
    locker.lock();
    cache_manager->saveSolution(key, solve_str);
    locker.unlock();
  }
  // send solution to client
  char *temp = (char *) malloc((solve_str.length() + 1) * sizeof(char));
  strcpy(temp, solve_str.c_str());
  int is_sent = send(client_socket, temp, strlen(temp), 0);
  free(temp);
  if (is_sent == -1) {
    std::cout << "Error sending message" << std::endl;
  }
  close(client_socket);
  cout << "client disconnected" << endl;
}
bool MyClientHandler::checkProblemValidation(Point start, Point finish, int rows, int cols, int client_socket) {
  // check if the point inside the matrix
  if (!(start.getX() >= 0 && start.getX() < rows && start.getY() >= 0 && start.getY() < cols &&
      finish.getX() >= 0 && finish.getX() < rows && finish.getY() >= 0 && finish.getY() < cols)) {
    string solve_str = "invalid problem, start or finish point are out of matrix";
    char *temp = (char *) malloc((solve_str.length() + 1) * sizeof(char));
    strcpy(temp, solve_str.c_str());
    int is_sent = send(client_socket, temp, strlen(temp), 0);
    free(temp);
    if (is_sent == -1) {
      std::cout << "Error sending message" << std::endl;
    }
    close(client_socket);
    cout << "cant solve problem, disconnect client.." << endl;
    return false;
  }
  return true;
}

