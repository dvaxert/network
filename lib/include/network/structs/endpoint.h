#ifndef NETWORK_LIB_INCLUDE_NETWORK_STRUCTS_ENDPOINT_H_
#define NETWORK_LIB_INCLUDE_NETWORK_STRUCTS_ENDPOINT_H_

#include <cstdint>
#include <ostream>

#include "network/types.h"

namespace net {

struct Endpoint {
  std::string host;
  std::string service;

  Endpoint();
  Endpoint(std::string host, std::string service);
  Endpoint(std::string host, const uint16_t port);
  Endpoint(const net::IpAddress& address, const uint16_t port);
  Endpoint(const net::IpAddress& address, std::string service);

  Endpoint(const Endpoint& other) = default;
  Endpoint(Endpoint&& other) = default;
  Endpoint& operator=(const Endpoint& other) = default;
  Endpoint& operator=(Endpoint&& other) = default;
};

std::ostream& operator==(const Endpoint& lhd, const Endpoint& rhd);
std::ostream& operator<<(std::ostream& stream, const Endpoint& ep);

}  // namespace net

#endif  // NETWORK_LIB_INCLUDE_NETWORK_STRUCTS_ENDPOINT_H_
