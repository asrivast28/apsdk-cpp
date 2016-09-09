#ifndef APSDK_RUNTIME_HPP_
#define APSDK_RUNTIME_HPP_

#include "Automaton.hpp"

#include <functional>
#include <vector>

namespace ap {
namespace runtime {

std::vector<unsigned>
calcLoadSize(const std::vector<std::reference_wrapper<Automaton> >&);

unsigned
queryDeviceCount();

std::vector<struct ap_device_metrics>
queryDeviceMetrics(const std::string& = "");

void
configureDevice(const std::string&);

#if (APSDKVERSION == 17)
struct ap_device_config
#else
unsigned
#endif
queryDeviceConfig(const std::string&);

} // namespace runtime
} // namespace ap

#endif // APSDK_RUNTIME_HPP_
