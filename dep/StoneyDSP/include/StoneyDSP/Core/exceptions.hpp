#pragma once

#define STONEYDSP_EXCEPTIONS_HPP_INCLUDED 1

#include <stdexcept>

namespace StoneyDSP {

/**
 * All exceptions thrown by components of the C++ Standard library throw
 * exceptions derived from this exception class. These are:
 *
 * <exception>          <description>
 * bad_alloc
 * bad_cast
 * bad_exception
 * bad_typeid
 * bad_function_call
 * bad_weak_ptr
 *
 * Also deriving from exception, header <exception> defines two generic
 * exception types that can be inherited by custom exceptions to report
 * errors:
 *
 * <exception>          <description>
 * logic_error
 * runtime_error
 */
typedef enum Status {
    status_ok,
    bad_alloc, // thrown by new on allocation failure
    bad_cast, // thrown by dynamic_cast when it fails in a dynamic cast
    bad_exception, // thrown by certain dynamic exception specifiers
    bad_typeid, // thrown by typeid
    bad_function_call, // thrown by empty function objects
    bad_weak_ptr, // thrown by shared_ptr when passed a bad weak_ptr
    logic_error, // error related to the internal logic of the program
    runtime_error // error detected during runtime
} stoneydsp_status;

//==============================================================================

  /// @} group StoneyDSP
} // namespace StoneyDSP

// If C++ exceptions are not explicitly enabled or disabled, enable them
// if exceptions were enabled in the compiler settings.
#if !defined(STONEYDSP_CPP_EXCEPTIONS) && !defined(STONEYDSP_DISABLE_CPP_EXCEPTIONS)
#if defined(_CPPUNWIND) || defined(__EXCEPTIONS)
#define STONEYDSP_CPP_EXCEPTIONS
#else
#error Exception support not detected. \
      Define either STONEYDSP_CPP_EXCEPTIONS or STONEYDSP_DISABLE_CPP_EXCEPTIONS.
#endif
#endif

// If C++ STONEYDSP_CPP_EXCEPTIONS are enabled, STONEYDSP_ENABLE_MAYBE should
// not be set
#if defined(STONEYDSP_CPP_EXCEPTIONS) && defined(STONEYDSP_ENABLE_MAYBE)
#error STONEYDSP_ENABLE_MAYBE should not be set when \
    STONEYDSP_CPP_EXCEPTIONS is defined.
#endif

#ifdef _NOEXCEPT
#define STONEYDSP_NOEXCEPT _NOEXCEPT
#else
#define STONEYDSP_NOEXCEPT noexcept
#endif

#ifdef STONEYDSP_CPP_EXCEPTIONS

#define STONEYDSP_THROW(e, ...) throw e
#define STONEYDSP_THROW_VOID(e) throw e

#define STONEYDSP_THROW_IF_FAILED(result, exception, ...)                      \
  if ((result) != ::StoneyDSP::Status::status_ok) throw std::exception(__VA_ARGS__)

#define STONEYDSP_THROW_IF_FAILED_VOID(result, exception)                      \
  if ((result) != ::StoneyDSP::Status::status_ok) throw std::exception()


// void test() {
//         int a = 1;
//     STONEYDSP_THROW_IF_FAILED(a, exception);

//     int bad_alloc = 1;
//     STONEYDSP_THROW_IF_FAILED_VOID(bad_alloc < 1, bad_alloc);
// }


#else  // STONEYDSP_CPP_EXCEPTIONS

#define STONEYDSP_THROW(e, ...)                                                \
  do {                                                                         \
    /** (e).ThrowAsJavaScriptException(); */                                   \
    return __VA_ARGS__;                                                        \
  } while (0)

#define NAPI_THROW_VOID(e)                                                     \
  do {                                                                         \
    /** (e).ThrowAsJavaScriptException(); */                                   \
    return;                                                                    \
  } while (0)

#define NAPI_THROW_IF_FAILED(env, status, ...)                                 \
    if ((status) != stoneydsp_success) {                                       \
        /** Napi::Error::New(env).ThrowAsJavaScriptException(); */             \
        return __VA_ARGS__;                                                    \
    }

#define NAPI_THROW_IF_FAILED_VOID(env, status)                                 \
    if ((status) != stoneydsp_success) {                                       \
        /** Napi::Error::New(env).ThrowAsJavaScriptException(); */             \
        return;                                                                \
    }

#endif  // NAPI_CPP_EXCEPTIONS
