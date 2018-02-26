#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <stdlib.h>
#include <cstring>
#include <errno.h>
#include <stdexcept>

namespace TrieTree {

class Exception : public std::runtime_error {
public:
    Exception(const std::string& message) :
        std::runtime_error(message) {}

    Exception(const unsigned int errorcode, const std::string& message) :
        std::runtime_error(message) {}

    virtual ~Exception() throw() {}

    static std::string strerrno() {
        return strerror(errno);
    }
};

class KeyNotFoundException : public Exception {
public:
    KeyNotFoundException(const std::string& message) : Exception(message) {}
};

class DuplicateRecordException : public Exception {
public:
    DuplicateRecordException(const std::string& message) : Exception(message) {}
};

} // namespace

#endif
