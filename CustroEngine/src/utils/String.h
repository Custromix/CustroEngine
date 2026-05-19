#pragma once
#include <cstring>
#include <iostream>

namespace Engine
{
    class String
    {
    private:
        char* data;
        size_t length;

    public:
        String(const char* str = "");
        String(const String& other);
        ~String();

        String& operator=(const String& other);
        String  operator+(const String& other) const;
        bool    operator==(const String& other) const;
        bool    operator!=(const String& other) const;
        char&   operator[](size_t index);
        bool operator<(const String& other) const;

        size_t      Length() const;
        const char* CStr()   const;

        bool IsEmpty() const;
        
        String Substring(size_t start, size_t count) const;
        bool   Contains(const String& other) const;
        void   Append(const String& other);

        friend std::ostream& operator<<(std::ostream& os, const String& str);
    };
    
       
}
