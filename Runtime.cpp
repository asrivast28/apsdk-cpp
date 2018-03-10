/**
 * @file Runtime.cpp
 * @brief Implementation of different runtime functions.
 * @author Ankit Srivastava <asrivast@gatech.edu>
 *
 * Copyright 2018 Georgia Institute of Technology
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
  APCALL_CHECK(AP_QueryDeviceMetrics)(&deviceMetrics[0], deviceName.c_str());
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
 * @param deviceName  Name of the physical device to be queried.
 *
 * @return  Number of load regions.
 */
unsigned
queryDeviceConfig(
  const std::string& deviceName
)
{
  unsigned loadRegions;
  loadRegions = APCALL_CHECK(AP_QueryDeviceConfig)(deviceName.c_str(), static_cast<struct ap_device_config*>(0));
  return loadRegions;
}

} // namespace runtime
} // namespace ap
