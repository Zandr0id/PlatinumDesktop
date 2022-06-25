
#pragma once
#include <string>

enum class Error
{
    NO_ERROR,
    ERROR
};

template <typename T>
class ErrorOr
{
public:
    ErrorOr(T new_value)
    {
        value = new_value;
        is_error = false;
        error = Error::NO_ERROR;
    };
    ErrorOr(Error new_error)
    {
        is_error = true;
        error = new_error;
    };
    void SetMessage(std::string new_msg)
    {
        message = new_msg;
    }
    bool HasMessage() { return !message.empty(); };
    bool IsError() { return is_error; };
    T Value() { return value; };
    Error Error() { return error; };
    std::string Message() { return message; }

private:
    T value;
    bool is_error;
    enum Error error;
    std::string message;
};
