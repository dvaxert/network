#ifndef NETWORK_LIB_INCLUDE_WORMHOLE_NETWORK_STRUCTS_ENDPOINT_H_
#define NETWORK_LIB_INCLUDE_WORMHOLE_NETWORK_STRUCTS_ENDPOINT_H_

#include <cstdint>
#include <ostream>

#include "wormhole/network/types.h"

namespace wh {
namespace net {

struct Endpoint {
  std::string host;
  std::string service;

  Endpoint();
  Endpoint(std::string host, std::string service);
  Endpoint(std::string host, const uint16_t port);
  Endpoint(const IpAddress& address, const uint16_t port);
  Endpoint(const IpAddress& address, std::string service);

  Endpoint(const Endpoint& other) = default;
  Endpoint(Endpoint&& other) = default;
  Endpoint& operator=(const Endpoint& other) = default;
  Endpoint& operator=(Endpoint&& other) = default;
};

std::ostream& operator==(const Endpoint& lhd, const Endpoint& rhd);
std::ostream& operator<<(std::ostream& stream, const Endpoint& ep);

}  // namespace net
}  // namespace wh

#endif  // NETWORK_LIB_INCLUDE_WORMHOLE_NETWORK_STRUCTS_ENDPOINT_H_
