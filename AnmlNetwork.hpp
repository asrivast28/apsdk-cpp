/**
 * @file AnmlNetwork.hpp
 * @brief Declaration of AnmlNetwork functions.
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
#ifndef APSDK_ANMLNETWORK_HPP_
#define APSDK_ANMLNETWORK_HPP_

#include "AnmlMacro.hpp"

#include <string>

#include <micron/ap/ap_anml.h>

namespace ap {

/**
 * @brief  Wrapper class for ap_anml_network_t functionality.
 */
class AnmlNetwork {
public:
  AnmlNetwork(const ap_anml_network_t&);

  AnmlNetwork(const AnmlNetwork&);

  void
  addMacroRef(const AnmlMacro&, const std::string&);

  void
  exportAnml(const std::string&) const;

  ~AnmlNetwork();

private:
  // ap_anml_network_t instance that this object refers to.
  ap_anml_network_t m_network;
}; // class AnmlNetwork

} // namespace ap

#endif // APSDK_ANMLNETWORK_HPP_
