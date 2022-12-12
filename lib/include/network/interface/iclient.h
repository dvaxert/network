#ifndef NETWORK_LIB_INCLUDE_NETWORK_INTERFACE_ICLIENT_H_
#define NETWORK_LIB_INCLUDE_NETWORK_INTERFACE_ICLIENT_H_

#include <chrono>
#include <cstdint>
#include <string>
#include <vector>

#include "network/structs/endpoint.h"

using namespace std::chrono_literals;

namespace net {

class IClient {
 public:
  virtual ~IClient() = default;

  virtual void Connect(const std::string_view host, const std::string_view service) = 0;
  virtual void Connect(const std::string_view host, const uint16_t port) = 0;
  virtual void Connect(const std::string_view address, const uint16_t port) = 0;
  virtual void Connect(const Endpoint& endpoint) = 0;

  virtual void Disconnect() = 0;

  virtual bool IsConnected() const = 0;

  virtual void Send(const std::vector<uint8_t>& raw_data,
                    const std::chrono::milliseconds& timeout = 0ms) = 0;
  virtual void Send(const std::vector<uint8_t>& raw_data,
                    const std::chrono::system_clock::time_point& deadline) = 0;
  virtual void Send(const std::string& message, const std::chrono::milliseconds& timeout = 0ms) = 0;
  virtual void Send(const std::string& message,
                    const std::chrono::system_clock::time_point& deadline) = 0;

  virtual std::vector<uint8_t> Reseive(const std::chrono::milliseconds& timeout = 0ms) = 0;
  virtual std::vector<uint8_t> Reseive(const std::chrono::system_clock::time_point& deadline) = 0;
};

}  // namespace net

#endif  // NETWORK_LIB_INCLUDE_NETWORK_INTERFACE_ICLIENT_H_
