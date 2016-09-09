/**
 * @file Runtime.cpp
 * @brief Implementation of different runtime functions.
 * @author Ankit Srivastava <asrivast@gatech.edu>
 * @version 1.0
 * @date 2016-09-09
 */
#include "Runtime.hpp"

#include "APCall.hpp"

#include <micron/ap/ap_load.h>

namespace ap {
namespace runtime {

/**
 * @brief  Calculate size of load region for given automaton.
 *
 * @return  Returns the estimated load region size. 
 */
std::vector<unsigned>
calcLoadSize(
  const std::vector<std::reference_wrapper<Automaton> >& automataRefs
)
{
  std::vector<unsigned> loadSize(automataRefs.size());
  std::vector<ap_automaton_t> automata(automataRefs.size());
  for ( const std::reference_wrapper<Automaton>& automaton : automataRefs ) {
    automata.push_back(*(automaton.get()));
  }
  APCALL_CHECK(AP_CalcLoadSize)(&loadSize[0], &automata[0], automata.size());
  return loadSize;
}

/**
 * @brief  Returns the number of physical devices on the system. 
 *
 * @return  Number of physical devices.
 */
unsigned
queryDeviceCount(
)
{
  unsigned numDevices = 0;
  APCALL_CHECK(AP_QueryDeviceCount)(&numDevices);
  return numDevices;
}

/**
 * @brief  Returns the metrics for all the physical devices on the system. 
 *
 * @param deviceName  Name of the physical device for which metrics are required.
 *
 * @return  Metrics for all the devices or the given device.
 */
std::vector<struct ap_device_metrics>
queryDeviceMetrics(
  const std::string& deviceName
)
{
  std::vector<struct ap_device_metrics> deviceMetrics(queryDeviceCount());
#if (APSDKVERSION == 17)
  APCALL_CHECK(AP_QueryDeviceMetrics)(&deviceMetrics[0], deviceName.c_str());
#else
  APCALL_CHECK(AP_QueryDeviceMetrics)(&deviceMetrics[0]);
#endif
  return deviceMetrics;
}

/**
 * @brief  Configure the physical device with default configuration.
 *
 * @param deviceName  Name of the physical device to be configured.
 */
void
configureDevice(
  const std::string& deviceName
)
{
  APCALL_CHECK(AP_ConfigureDevice)(deviceName.c_str(), static_cast<struct ap_device_config*>(0));
}

/**
 * @brief  Returns the number of load regions for the given device. 
 *
 * @param deviceName  Name of the device to be queried.
 *
 * @return  Number of load regions.
 */
#if (APSDKVERSION == 17)
struct ap_device_config
#else
unsigned
#endif
queryDeviceConfig(
  const std::string& deviceName
)
{
#if (APSDKVERSION == 17)
  struct ap_device_config config;
  APCALL_CHECK(AP_QueryDeviceConfig)(deviceName.c_str(), &config);
  return config;
#else
  unsigned loadRegions = APCALL_CHECK(AP_QueryDeviceConfig)(deviceName.c_str());
  return loadRegions;
#endif
}

} // namespace runtime
} // namespace ap
