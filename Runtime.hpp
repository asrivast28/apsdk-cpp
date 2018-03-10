/**
 * @file Runtime.hpp
 * @brief Declaration of different runtime functions.
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

unsigned
queryDeviceConfig(const std::string&);

} // namespace runtime
} // namespace ap

#endif // APSDK_RUNTIME_HPP_
