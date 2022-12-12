#ifndef NETWORK_LIB_INCLUDE_NETWORK_INTERFACE_ISERVER_H_
#define NETWORK_LIB_INCLUDE_NETWORK_INTERFACE_ISERVER_H_

namespace wormhole {
namespace network {

class IServer {
 public:
  virtual ~IServer() = default;

  virtual void Run() = 0;
  virtual void Restart() = 0;
  virtual void Stop() = 0;
};

}  // namespace network
}  // namespace wormhole

#endif  // NETWORK_LIB_INCLUDE_NETWORK_INTERFACE_ISERVER_H_
