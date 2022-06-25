
#pragma once
#include <string>

class Error
{
public:
    // make sure to add a String representation
    // below when adding a new entry, and in the same
    // order.
    typedef enum
    {
        NO_ERROR,
        ERROR,
        ANOTHER
    } ErrorType;
    Error(ErrorType new_val = ErrorType::NO_ERROR)
    {
        val = new_val;
    }
    std::string ToString() { return string_reps[val]; };

    bool operator==(Error &b)
    {
        return this->val == b.val;
    }

private:
    ErrorType val;
    inline static std::string string_reps[] =
        {
            "NO_ERROR",
            "ERROR",
            "ANOTHER"};
};

template <typename T>
class ErrorOr
{
public:
    ErrorOr()
    {
        is_error = false;
        error = Error::NO_ERROR;
    }
    void MakeError(Error new_error)
    {
        if (false == has_been_set)
        {
            has_been_set = true;
            is_error = true;
            error = new_error;
        }
    };
    void MakeValue(T new_value)
    {
        if (false == has_been_set)
        {
            has_been_set = true;
            value = new_value;
        }
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

    void operator=(ErrorOr<T> &b)
    {
        this->Error = b.Error;
        this->is_error = b.is_error;
        this->value = b.value;
        this->message = b.message;
    }

private:
    T value;
    bool is_error;
    bool has_been_set;
    class Error error;
    std::string message;
};
