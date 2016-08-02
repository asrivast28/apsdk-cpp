#ifndef APSDK_APCALL_HPP_
#define APSDK_APCALL_HPP_

#include <iostream>
#include <stdexcept>
#include <string>

namespace ap {

template<typename Func, Func func>
class APCall {
public:
  APCall(const char* funcName, const char* fileName, const int lineNumber)
    : m_func(func), m_funcName(funcName), m_fileName(fileName), m_lineNumber(lineNumber)
  { }

  template <typename... Args>
  unsigned
  operator()(Args&&... args)
  {
    int error = m_func(std::forward<Args>(args)...);
    if (error < 0) {
      throw std::runtime_error("Error code " + std::to_string(error) + " returned during call to " + m_funcName +
                               " on line " + std::to_string(m_lineNumber) + " in file " + m_fileName + ".");
    }
    // The value of error is guaranteed to be greater than 0 at this point.
    return static_cast<unsigned>(error);
  }

private:
  const Func m_func;
  const std::string m_funcName;
  const std::string m_fileName;
  const int m_lineNumber;
}; // class APCall

} // namespace ap

#define APCALL_CHECK(FUNC) APCall<decltype(&FUNC), &FUNC>(#FUNC, __FILE__, __LINE__)

#endif // APSDK_APCALL_HPP_
