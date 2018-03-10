/**
 * @file Device.hpp
 * @brief Declaration of Device functions.
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
#ifndef APSDK_DEVICE_HPP_
#define APSDK_DEVICE_HPP_

#include "Automaton.hpp"

#include <limits>
#include <string>

#include <micron/ap/ap_anml.h>

namespace ap {

/**
 * @brief  Wrapper class for ap_device_t and ap_rto_t functionality.
 */
class Device {
public:
  Device();

  Device(const std::string&, const int = -1);

  // Do NOT allow copying of this object.
  // The underlying instance is not "shareable".
  Device(const Device&) = delete;

  Device&
  operator=(Device&&);

  void
  load(Automaton&&, const unsigned = 0);

  std::vector<std::pair<size_t, ElementRef> >
  search(std::vector<unsigned char>&, const size_t = std::numeric_limits<size_t>::max());

  void
  unload();

  ~Device();

private:
  static const size_t MAX_MATCHES = 512;

private:
  // ap_device_t instance that this object refers to.
  ap_device_t m_device;
  // ap_rto_t instance that this object refers to.
  ap_rto_t m_runtimeObject;
}; // class Device

} // namespace ap

#endif // APSDK_DEVICE_HPP_
