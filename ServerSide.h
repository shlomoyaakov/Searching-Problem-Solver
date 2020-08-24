
#ifndef EX4_5__SERVERSIDE_H_
#define EX4_5__SERVERSIDE_H_
#include "ClientHandler.h"
namespace server_side {
class Server {
 public:
  virtual void open(int, ClientHandler *) = 0;
  virtual void stop() = 0;
  virtual ~Server()= default;
};
}

#endif //EX4_5__SERVERSIDE_H_
