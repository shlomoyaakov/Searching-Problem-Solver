
#ifndef EX4_5__CLIENTHANDLER_H_
#define EX4_5__CLIENTHANDLER_H_
class ClientHandler {
 public:
  virtual void handleClient(int) = 0;
  virtual ClientHandler* getClone() {return nullptr;};
  virtual ~ClientHandler()= default;
};
#endif //EX4_5__CLIENTHANDLER_H_
