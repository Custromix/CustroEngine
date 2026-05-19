#include "String.h"

namespace Engine
{
    String::String(const char* str)
    {
        if (!str)
        {
            length = 0;
            data = new char[1];
            data[0] = '\0';
        }else
        {
            length = strlen(str);
            data = new char[length + 1];
            strcpy(data, str);
        }
    }

    String::String(const String& other)
    {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
    }

    String::~String()
    {
        delete[] data;
    }

    String& String::operator=(const String& other)
    {
        if (this != &other)
        {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            strcpy(data, other.data);
        }
        return *this;
    }

    String String::operator+(const String& other) const
    {
        String result;
        result.length = length + other.length;
        delete[] result.data;
        result.data = new char[result.length + 1];
        strcpy(result.data, data);
        strcat(result.data, other.data);
        return result;
    }

    bool String::operator==(const String& other) const
    {
        return strcmp(data, other.data) == 0;
    }

    bool String::operator!=(const String& other) const
    {
        return !(*this == other);
    }

    char& String::operator[](size_t index)
    {
        return data[index];
    }
    
    bool String::operator<(const String& other) const
    {
        return strcmp(data, other.data) < 0;
    }
    

    size_t String::Length() const
    {
        return length;
    }

    const char* String::CStr() const
    {
        return data;
    }

    bool String::IsEmpty() const
    {
        return length == 0;
    }

    String String::Substring(size_t start, size_t count) const
    {
        char* buffer = new char[count + 1];
        strncpy(buffer, data + start, count);
        buffer[count] = '\0';
        String result(buffer);
        delete[] buffer;
        return result;
    }

    bool String::Contains(const String& other) const
    {
        return strstr(data, other.data) != nullptr;
    }

    void String::Append(const String& other)
    {
        char* newData = new char[length + other.length + 1];
        strcpy(newData, data);
        strcat(newData, other.data);
        delete[] data;
        data = newData;
        length += other.length;
    }

    std::ostream& operator<<(std::ostream& os, const String& str)
    {
        os << str.data;
        return os;
    }
}