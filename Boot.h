
#ifndef EX4_5__BOOT_H_
#define EX4_5__BOOT_H_
#include "MyClientHandler.h"
#include "MyTestClientHandler.h"
#include "FileCacheManager.h"
#include "StringReverser.h"
#include "State.h"
#include "StatePriorityQueue.h"
#include "Point.h"
#include "ObjectAdapter.h"
#include "MyParallelServer.h"
#include "BreadthFirstSearch.h"
#include "BestFirstSearch.h"
#include "DepthFirstSearch.h"
#include "AStar.h"
namespace boot {
class Main;
}

class boot :: Main{

 public:
  Main(){};
  ~Main(){};
  int main() {
    // allocate all the necessary object to get and solve a problem and run the parallel server -
    MyParallelServer server;
    Searcher<Point, vector<State<Point>>> *s = new DepthFirstSearch<Point>();
    ObjectAdapter sr(s);
    FileCacheManager fcm;
    MyClientHandler ch(&fcm, &sr);
    server.open(5600, &ch);
    delete (s);
    return 0;
  };
};
#endif //EX4_5__BOOT_H_
