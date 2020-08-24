
#ifndef EX4_5__MYPARALLELSERVER_H_
#define EX4_5__MYPARALLELSERVER_H_

#include <sys/socket.h>
#include <string>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include "ServerSide.h"
using namespace std;
class MyParallelServer : public server_side::Server {
  bool to_stop = false;
 public:
  void open(int, ClientHandler *);
  void stop();
  static void start(int, sockaddr_in, ClientHandler *, bool *to_close);
  static void handleClient(ClientHandler *client_handler, int client_socket);
};

#endif //EX4_5__MYPARALLELSERVER_H_
