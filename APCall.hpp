/**
 * @file APCall.hpp
 * @brief Functionality for error checking calls to C API.
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
#ifndef APSDK_APCALL_HPP_
#define APSDK_APCALL_HPP_

#include <iostream>
#include <stdexcept>
#include <string>

namespace ap {

template<typename Func, Func func>
class APCall {
public:
  APCall(const char* funcName, const char* fileName, const int lineNumber, const bool isZero)
    : m_func(func), m_funcName(funcName), m_fileName(fileName), m_lineNumber(lineNumber), m_isZero(isZero)
  { }

  template <typename... Args>
  unsigned
  operator()(Args&&... args)
  {
    int error = m_func(std::forward<Args>(args)...);
    if ((!m_isZero && (error < 0)) || (m_isZero && (error != 0))) {
      throw std::runtime_error("Error code " + std::to_string(error) + " returned during call to " + m_funcName +
                               " on line " + std::to_string(m_lineNumber) + " in file " + m_fileName + ".");
    }
    // The value of error is guaranteed to be non-negative at this point.
    return static_cast<unsigned>(error);
  }

private:
  const Func m_func;
  const std::string m_funcName;
  const std::string m_fileName;
  const int m_lineNumber;
  const bool m_isZero;
}; // class APCall

} // namespace ap

// This macro should be used when the acceptable return values are non-negative.
#define APCALL_CHECK(FUNC) APCall<decltype(&FUNC), &FUNC>(#FUNC, __FILE__, __LINE__, false)
// This macro should be used when zero is the only acceptable return value.
#define APCALL_CHECK_ZERO(FUNC) APCall<decltype(&FUNC), &FUNC>(#FUNC, __FILE__, __LINE__, true)

#endif // APSDK_APCALL_HPP_
