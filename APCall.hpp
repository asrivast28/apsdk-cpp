#ifndef APSDK_APCALL_HPP_
#define APSDK_APCALL_HPP_

#include <iostream>
#include <stdexcept>
#include <string>

namespace ap {

template<typename Func, Func func>
class APCall {
public:
  APCall(const char* funcName)
    : m_func(func), m_funcName(funcName)
  { }

  template <typename... Args>
  unsigned 
  operator()(Args&&... args)
  {
    int error = m_func(std::forward<Args>(args)...);
    if (error < 0) {
      throw std::runtime_error("Error code " + std::to_string(error) + " returned during call to " + m_funcName + ".");
    }
    // The value of error is guaranteed to be greater than 0 at this point.
    return static_cast<unsigned>(error);
  }

private:
  Func m_func;
  std::string m_funcName;
}; // class APCall

} // namespace ap

#define APCALL_CHECK(FUNC) APCall<decltype(&FUNC), &FUNC>(#FUNC)

#endif // APSDK_APCALL_HPP_
