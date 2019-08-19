// stringdata.h

/*    Copyright 2010 10gen Inc.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#pragma once

#include <string>
#include <cstring>

namespace bson {

    using std::string;

    /* A StringData object wraps a 'const string&' or a 'const char*' without
     * copying its contents. The most common usage is as a function argument
     * that takes any of the two forms of strings above. Fundamentally, this
     * class tries go around the fact that string literals in C++ are char[N]'s.
     * Note that the object StringData wraps around must be alive while the
     * StringData is.
     */

    class StringData {
    public:
        /** Constructs an empty string data */
        StringData()
          : _data(NULL), _size(0) {}

        StringData(const StringData &s)
          : _data(s.data()), _size(s.size()) {}

        /** Construct a StringData, for the case where the length of
         * string is not known. 'c' must be a pointer to a null-terminated 
         * string.
         */
        StringData( const char* c )
            : _data(c), _size((unsigned) strlen(c)) {}

        /** Construct a StringData explicitly, for the case where the length of
         * the string is already known. 'c' must be a pointer to a null-
         * terminated string, and strlenOfc must be the length that 
         * std::strlen(c) would return, a.k.a the index of the terminator in c.
         */
        StringData( const char* c, unsigned len )
            : _data(c), _size(len) {}

        /** Construct a StringData, for the case of a std::string. */
        StringData( const string& s )
            : _data(s.c_str()), _size((unsigned) s.size()) {}

        // Construct a StringData explicitly, for the case of a literal whose
        // size is known at compile time.
        struct LiteralTag {};
        template<size_t N>
        StringData( const char (&val)[N], LiteralTag )
            : _data(&val[0]), _size(N-1) {}

        // accessors
        const char* const data() const { return _data; }
        const unsigned size() const { return _size; }
        inline int compare(const StringData& other) const {
            // Sizes might not have been computed yet.
            size();
            other.size();

            int res = memcmp(_data, other._data, std::min(_size, other._size));
            if (res != 0) {
                return res > 0 ? 1 : -1;
            }
            else if (_size == other._size) {
                return 0;
            }
            else {
                return _size > other._size ? 1 : -1;
            }
        }

        typedef const char* const_iterator;
        const_iterator begin() const { return data(); }
        const_iterator end() const { return data() + size(); }

        char operator[] (unsigned pos) const { return _data[pos]; }
        bool operator==(const StringData& rhs) { return compare(rhs) == 0;}
        bool operator!=(const StringData& rhs) { return compare(rhs) != 0;}
        bool operator<(const StringData& rhs) { return compare(rhs) < 0;}
        bool operator<=(const StringData& rhs) { return compare(rhs) <= 0;}
        bool operator>(const StringData& rhs) { return compare(rhs) > 0;}
        bool operator>=(const StringData& rhs) { return compare(rhs) >= 0;}
        StringData& operator=(const StringData& rhs) 
        {
            _data = rhs.data();
            _size = rhs.size();
            return *this;
        }

        StringData substr( size_t pos, size_t n) const {
            if ( pos > size() )
                throw std::out_of_range( "out of range" );

            // truncate to end of string
            if ( n > size() - pos )
                n = size() - pos;

            return StringData( _data + pos, n );
        }

        StringData substr( size_t pos) const {
            return substr(pos, size());
        }


        bool startsWith( const StringData& prefix ) const {
            // TODO: Investigate an optimized implementation.
            return substr(0, prefix.size()) == prefix;
        }

        bool endsWith( const StringData& suffix ) const {
            // TODO: Investigate an optimized implementation.
            const size_t thisSize = size();
            const size_t suffixSize = suffix.size();
            if (suffixSize > thisSize)
                return false;
            return substr(thisSize - suffixSize) == suffix;
        }

        size_t find( char c, size_t fromPos ) const {
            if ( fromPos >= size() )
                return std::string::npos;

            const void* x = memchr( _data + fromPos, c, _size - fromPos );
            if ( x == 0 )
                return std::string::npos;
            return static_cast<size_t>( static_cast<const char*>(x) - _data );
        }

        size_t find( const StringData& needle ) const {
            size_t mx = size();
            size_t needleSize = needle.size();

            if ( needleSize == 0 )
                return 0;
            else if ( needleSize > mx )
                return std::string::npos;

            mx -= needleSize;

            for ( size_t i = 0; i <= mx; i++ ) {
                if ( memcmp( _data + i, needle._data, needleSize ) == 0 )
                    return i;
            }
            return std::string::npos;
        }


    private:
        const char*    _data;  // is always null terminated
        mutable size_t _size;  // 'size' does not include the null terminator
    };

} // namespace bson
