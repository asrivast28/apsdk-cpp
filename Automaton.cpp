/**
 * @file Automaton.cpp
 * @brief Implementation of Automaton functions.
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
#include "Automaton.hpp"

#include "APCall.hpp"

#include <iostream>

#include <micron/ap/sys/platform.h>
#if defined(LINUX32) || defined(LINUX64)
#include <fcntl.h>
#include <unistd.h>
#endif


namespace ap {

/**
 * @brief  Default constructor.
 */
Automaton::Automaton(
) : m_automaton(0)
{
}

/**
 * @brief  Constructor for creating the object with a given
 *         ap_automaton_t instance.
 */
Automaton::Automaton(
  const ap_automaton_t& automaton
) : m_automaton(automaton)
{
}

/**
 * @brief  Constructor for creating the object by reading automaton
 *         from the given file.
 *
 * @param fileName  Name of the file from which automaton is to be read.
 */
Automaton::Automaton(
  const std::string& fileName
) : m_automaton(0)
{
  file_descriptor_t fd;
#if defined(LINUX32) || defined(LINUX64)
	fd = open(fileName.c_str(),O_RDONLY, S_IRUSR);
#else
	//fd = CreateFileA(fileName.c_str(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
#endif
  APCALL_CHECK_ZERO(AP_Restore)(&m_automaton, fd);
#if defined(LINUX32) || defined(LINUX64)
  close(fd);
#else
  //CloseHandle(fd);
#endif
}

Automaton::Automaton(
  const Automaton& that
) : m_automaton(0)
{
  APCALL_CHECK_ZERO(AP_Duplicate)(that.m_automaton, &m_automaton, 0);
}

/**
 * @brief  Move constructor.
 */
Automaton::Automaton(
  Automaton&& that
) : m_automaton(that.m_automaton)
{
  that.m_automaton = 0;
}

Automaton&
Automaton::operator=(
  Automaton&& that
)
{
  m_automaton = that.m_automaton;
  that.m_automaton = 0;
  return *this;
}

/**
 * @brief  Substitutes symbols in the automaton.
 *
 * @param elementMap  Element map for the substitution.
 * @param changes     Array of all the changes.
 */
void
Automaton::setSymbol(
  ElementMap& elementMap,
  SymbolChange& changes
)
{
  //APCALL_CHECK(AP_SetSymbol)(m_automaton, *elementMap, *changes, changes.count());
  ap_element_map_t emap = *elementMap;
  struct ap_symbol_change* allChanges = *changes;
  size_t changeCount = changes.count();
  for (size_t idx = 0; idx < changeCount; ++idx) {
    APCALL_CHECK_ZERO(AP_SetSymbol)(m_automaton, emap, &allChanges[idx], 1);
  }
}

/**
 * @brief  Saves the automaton to the given file.
 *
 * @param fileName  Name of the file in which automaton is to be saved.
 */
void
Automaton::save(
  const std::string& fileName
) const
{
  file_descriptor_t fd;
#if defined(LINUX32) || defined(LINUX64)
	fd = open(fileName.c_str(),O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IRGRP|S_IROTH|S_IWUSR);
#else
	fd = CreateFileA(fileName.c_str(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
#endif
  APCALL_CHECK_ZERO(AP_Save)(m_automaton, fd);
#if defined(LINUX32) || defined(LINUX64)
  close(fd);
#else
  CloseHandle(fd);
#endif
}

/**
 * @brief  Prints information about the automaton.
 */
void
Automaton::printInfo(
) const
{
  struct ap_automaton_info info;
  APCALL_CHECK_ZERO(AP_GetInfo)(m_automaton, &info, 0);
  std::cout << "blocks_rect = " << info.blocks_rect<< std::endl;
  std::cout << "blocks_used = " << info.blocks_used<< std::endl;
  std::cout << "ste_count = " << info.ste_count<< std::endl;
  std::cout << "ste_grp_used = " << info.ste_grp_used << std::endl;
  std::cout << "counter_used = " << info.counter_used << std::endl;
  std::cout << "bool_used = " << info.bool_used << std::endl;
  std::cout << "match_res = " << info.match_res<< std::endl;
  std::cout << "clock_divisor = " << info.clock_divisor << std::endl;
}

/**
 * @brief  Overloaded indirection operator implementation.
 *
 * @return  Returns the underlying ap_automaton_t instance.
 */
ap_automaton_t
Automaton::operator*(
)
{
  return m_automaton;
}

/**
 * @brief  Default destructor.
 */
Automaton::~Automaton(
)
{
  // Destroy the automaton only if it points to a valid instance.
  if (m_automaton != 0) {
    try {
      APCALL_CHECK_ZERO(AP_Destroy)(m_automaton);
    }
    catch (const std::runtime_error& e) {
      std::cerr << "Unable to destroy the automaton because of errors." << std::endl;
      std::cerr << e.what() << std::endl;
    }
    m_automaton = 0;
  }
}

} // namespace ap
