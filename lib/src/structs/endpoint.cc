#include "wormhole/network/structs/endpoint.h"

namespace wormhole {
namespace network {

Endpoint::Endpoint() : host(), service() {}

//------------------------------------------------------------------------------

Endpoint::Endpoint(std::string host_, std::string service_) : host(std::move(host_)), service(std::move(service_)) {}

//------------------------------------------------------------------------------

Endpoint::Endpoint(std::string host_, const uint16_t port) : host(std::move(host_)), service(std::to_string(port)) {}

//------------------------------------------------------------------------------

Endpoint::Endpoint(const IpAddress& address, const uint16_t port)
    : host(address.to_string()), service(std::to_string(port)) {}

//------------------------------------------------------------------------------

Endpoint::Endpoint(const IpAddress& address, std::string service_)
    : host(address.to_string()), service(std::move(service_)) {}

//------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& stream, const Endpoint& ep) { return stream << ep.host << ':' << ep.service; }

}  // namespace network
}  // namespace wormhole
