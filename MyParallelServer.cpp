
#include "MyParallelServer.h"
#include "MyParallelServer.h"
void MyParallelServer::open(int port, ClientHandler *client_handler) {
  int server_fd;
  struct sockaddr_in address;
  int opt = 1;
  // Creating socket file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // Forcefully attaching socket to the port 8080
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                 &opt, sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

  // Forcefully attaching socket to the port 8080
  if (bind(server_fd, (struct sockaddr *) &address,
           sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }
  thread t(start, server_fd, address, client_handler, &to_stop);
  t.join();
}

void MyParallelServer::start(int socketfd, sockaddr_in address, ClientHandler *client_handler, bool *to_stop) {
  cout << "Parallel server is up! waiting for clients.." << endl;
  while (!(*to_stop)) {
    int iResult;
    int client_socket = 0;
    struct timeval tv;
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(socketfd, &rfds);

    tv.tv_sec = 120.0;
    tv.tv_usec = 0;
    int addrlen = sizeof(address);
    iResult = select(socketfd + 1, &rfds, (fd_set *) 0, (fd_set *) 0, &tv);
    if (iResult > 0) {
      client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &addrlen);
      cout << "client connected, getting problem.." << endl;
    } else {
      cout << "timeout, server shut down." << endl;
      return;
    }
    if (client_socket == -1) {
      std::cerr << "can't accept client" << std::endl;
      return;
    }
    thread t(handleClient, client_handler, client_socket);
    t.detach();
  }
}
void MyParallelServer::stop() {
  to_stop = true;
}
void MyParallelServer::handleClient(ClientHandler *client_handler, int client_socket) {
  ClientHandler *ch = client_handler->getClone();
  ch->handleClient(client_socket);
  delete (ch);
}