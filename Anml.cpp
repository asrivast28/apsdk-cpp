/**
 * @file Anml.cpp
 * @brief Implementation of Anml functions.
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
#include "Anml.hpp"

#include "AnmlMacro.hpp"
#include "AnmlNetwork.hpp"
#include "APCall.hpp"


namespace ap {

/**
 * @brief  Initializes the instance with an ANML workspace.
 */
Anml::Anml(
) : m_anml(AP_CreateAnml())
{
}

/**
 * @brief  Move constructor.
 */
Anml::Anml(
  Anml&& that
) : m_anml(that.m_anml)
{
  // Ensure that the other instance doesn't destroy the workspace.
  that.m_anml = 0;
}

/**
 * @brief  Loads macro from the given ANML file.
 *
 * @param fileName  Name of the ANML file from which macro is to be loaded.
 *
 * @return  Returns AnmlMacro instance for the loaded macro.
 */
AnmlMacro
Anml::loadMacro(
  const std::string& fileName
)
{
  ap_macro_def_t macro;
  int lineNumber = 0;
  try {
    APCALL_CHECK_ZERO(AP_LoadAnmlMacro)(m_anml, &macro, &lineNumber, fileName.c_str(), static_cast<ap_cbinfo_t*>(0), AP_OPT_DEFAULT, static_cast<const char*>(0));
  }
  catch(std::runtime_error& e) {
    throw std::runtime_error(std::string(e.what()) + " In " + fileName + " on line " + std::to_string(lineNumber) + ".");
  }

  return AnmlMacro(macro);
}


/**
 * @brief  Creates an ANML network in this workspace.
 *
 * @param anmlId  ANML id of the network to be created.
 *
 * @return  Returns AnmlNetwork instance for the created network.
 */
AnmlNetwork
Anml::createNetwork(
  const std::string& anmlId
)
{
  ap_anml_network_t network;
  APCALL_CHECK_ZERO(AP_CreateAutomataNetwork)(m_anml, &network, anmlId.c_str());
  return AnmlNetwork(network);
}

/**
 * @brief  Precompiles all the loaded macros.
 */
void
Anml::compileMacros(
) const
{
  APCALL_CHECK_ZERO(AP_CompileMacros)(m_anml, static_cast<ap_macro_def_t*>(0), static_cast<ap_anml_element_ref_t*>(0), static_cast<ap_cbinfo_t*>(0), AP_OPT_DEFAULT, 0);
}

/**
 * @brief  Compiles the ANML workspace.
 *
 * @return  Returns Automaton and ElementMap instances generated as a result of the compilation.
 */
std::pair<Automaton, ElementMap>
Anml::compileAnml(
) const
{
  ap_automaton_t automaton;
  ap_element_map_t elementMap;
  APCALL_CHECK_ZERO(AP_CompileAnml)(m_anml, &automaton, &elementMap, static_cast<ap_anml_element_ref_t*>(0), static_cast<ap_cbinfo_t*>(0), AP_OPT_DEFAULT, 0);
  return std::pair<Automaton, ElementMap>(Automaton(automaton), ElementMap(elementMap));
}

/**
 * @brief  Destuctor for destroying the associated ANML workspace.
 */
Anml::~Anml(
)
{
  if (m_anml != 0) {
    try {
      APCALL_CHECK_ZERO(AP_DestroyAnml)(m_anml);
    }
    catch (const std::runtime_error& e) {
      std::cerr << "Unable to destroy the ANML workspace because of errors." << std::endl;
      std::cerr << e.what() << std::endl;
    }
    m_anml = 0;
  }
}

} // namespace ap
