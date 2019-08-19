﻿//---------------------------------------------------------------------
// <copyright file="asyncrt_utils.cpp" company="Microsoft">
//      Copyright (C) Microsoft Corporation. All rights reserved. See License.txt in the project root for license information.
// </copyright>
//---------------------------------------------------------------------

#include "odata/common/platform.h"
#include "odata/common/basic_types.h"
#include "odata/common/asyncrt_utils.h"
#include <algorithm>

#if defined(__cplusplus_winrt)
using namespace Platform;
using namespace Windows::Storage::Streams;
#endif // #if !defined(__cplusplus_winrt)

#ifndef _MS_WINDOWS
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
using namespace boost::locale::conv;
#endif

// using namespace odata::web;
using namespace odata::utility;
using namespace odata::utility::conversions;

namespace odata { namespace utility
{

#pragma region error categories

namespace details
{

const std::error_category & __cdecl platform_category()
{
#ifdef _MS_WINDOWS
    return windows_category();
#else
    return linux_category();
#endif
}

#ifdef _MS_WINDOWS

const std::error_category & __cdecl windows_category()
{
    static details::windows_category_impl instance;
    return instance;
}

std::string windows_category_impl::message(int errorCode) const
{
    const size_t buffer_size = 4096;
    DWORD dwFlags = FORMAT_MESSAGE_FROM_SYSTEM;
    LPCVOID lpSource = NULL;

#if !defined(__cplusplus_winrt)
    if (errorCode >= 12000)
    {
        dwFlags = FORMAT_MESSAGE_FROM_HMODULE;
        lpSource = GetModuleHandleA("winhttp.dll"); // this handle DOES NOT need to be freed
    }
#endif

    std::wstring buffer;
    buffer.resize(buffer_size);
    
    const auto result = ::FormatMessageW(
        dwFlags,
        lpSource,
        errorCode,
        0,
        &buffer[0],
        buffer_size,
        NULL);

    if (result == 0)
    {
        std::ostringstream os;
        os << "Unable to get an error message for error code: " << errorCode << ".";
        return os.str();
    }

    return utility::conversions::to_utf8string(buffer);
}

std::error_condition windows_category_impl::default_error_condition(int errorCode) const
{
    // First see if the STL implementation can handle the mapping for common cases.
    const std::error_condition errCondition = std::system_category().default_error_condition(errorCode);
    const std::string errConditionMsg = errCondition.message();
    if(_stricmp(errConditionMsg.c_str(), "unknown error") != 0)
    {
        return errCondition;
    }

    switch(errorCode)  
    {  
#ifndef __cplusplus_winrt
    case ERROR_WINHTTP_TIMEOUT:
        return std::errc::timed_out;
    case ERROR_WINHTTP_CANNOT_CONNECT:
        return std::errc::host_unreachable;
    case ERROR_WINHTTP_CONNECTION_ERROR:
        return std::errc::connection_aborted;
#endif
    case INET_E_RESOURCE_NOT_FOUND:
    case INET_E_CANNOT_CONNECT:
        return std::errc::host_unreachable;
    case INET_E_CONNECTION_TIMEOUT:
        return std::errc::timed_out;
    case INET_E_DOWNLOAD_FAILURE:
        return std::errc::connection_aborted;
    default:    
        break;
    }

    return std::error_condition(errorCode, *this);
}

#else

const std::error_category & __cdecl linux_category()
{
    // On Linux we are using boost error codes which have the exact same
    // mapping and are equivalent with std::generic_category error codes.
    return std::generic_category();
}

#endif

}

#pragma endregion

#pragma region conversions

utf16string __cdecl conversions::utf8_to_utf16(const std::string &s)
{
    if(s.empty())
    {
        return utf16string();
    }

#ifdef _MS_WINDOWS
    // first find the size
    int size = ::MultiByteToWideChar(
        CP_UTF8, // convert to utf-8
        MB_ERR_INVALID_CHARS, // fail if any characters can't be translated
        s.c_str(),
        (int)s.size(),
        nullptr, 0); // must be null for utf8

    if (size == 0)
    {
        throw utility::details::create_system_error(GetLastError());
    }
        
    utf16string buffer;
    buffer.resize(size);

    // now call again to format the string
    const int result = ::MultiByteToWideChar(
        CP_UTF8, // convert to utf-8
        MB_ERR_INVALID_CHARS, // fail if any characters can't be translated
        s.c_str(),
        (int)s.size(),
        &buffer[0], size); // must be null for utf8
        
    if (result != size)
    {
        throw utility::details::create_system_error(GetLastError());
    }

    return buffer;
#else
    return utf_to_utf<utf16char>(s, stop);
#endif
}

std::string __cdecl conversions::utf16_to_utf8(const utf16string &w)
{
    if(w.empty())
    {
        return std::string();
    }

#ifdef _MS_WINDOWS
    // first find the size
    const int size = ::WideCharToMultiByte(
        CP_UTF8, // convert to utf-8
#if _WIN32_WINNT >= _WIN32_WINNT_VISTA
        WC_ERR_INVALID_CHARS, // fail if any characters can't be translated
#else
        0, // ERROR_INVALID_FLAGS is not supported in XP, set this dwFlags to 0
#endif // _WIN32_WINNT >= _WIN32_WINNT_VISTA
        w.c_str(),
        (int)w.size(),
        nullptr, 0, // find the size required
        nullptr, nullptr); // must be null for utf8  

    if (size == 0)
    {
        throw utility::details::create_system_error(GetLastError());
    }

    std::string buffer;
    buffer.resize(size);
    
    // now call again to format the string
    const int result = ::WideCharToMultiByte(
        CP_UTF8, // convert to utf-8
#if _WIN32_WINNT >= _WIN32_WINNT_VISTA
        WC_ERR_INVALID_CHARS, // fail if any characters can't be translated
#else
        0, // ERROR_INVALID_FLAGS is not supported in XP, set this dwFlags to 0
#endif // _WIN32_WINNT >= _WIN32_WINNT_VISTA
        w.c_str(),
        (int)w.size(),
        &buffer[0], size,
        nullptr, nullptr); // must be null for utf8 
        
    if (result != size)
    {
        throw utility::details::create_system_error(GetLastError());
    }

    return buffer;
#else
    return utf_to_utf<char>(w, stop);
#endif
}

utf16string __cdecl conversions::usascii_to_utf16(const std::string &s)
{
    if(s.empty())
    {
        return utf16string();
    }

#ifdef _MS_WINDOWS
    int size = ::MultiByteToWideChar(
        20127, // convert from us-ascii
        MB_ERR_INVALID_CHARS, // fail if any characters can't be translated
        s.c_str(),
        (int)s.size(),
        nullptr, 0);

    if (size == 0)
    {
        throw utility::details::create_system_error(GetLastError());
    }

    // this length includes the terminating null
    std::wstring buffer;
    buffer.resize(size);
    
    // now call again to format the string
    int result = ::MultiByteToWideChar(
        20127, // convert from us-ascii
        MB_ERR_INVALID_CHARS, // fail if any characters can't be translated
        s.c_str(),
        (int)s.size(),
        &buffer[0], size);

    if (result != size)
    {
        throw utility::details::create_system_error(GetLastError());
    }

    return buffer;
#else
    return utf_to_utf<utf16char>(to_utf<char>(s, "ascii", stop));
#endif
}

utf16string __cdecl conversions::latin1_to_utf16(const std::string &s)
{
    if(s.empty())
    {
        return utf16string();
    }

#ifdef _MS_WINDOWS
    int size = ::MultiByteToWideChar(
        28591, // convert from Latin1
        MB_ERR_INVALID_CHARS, // fail if any characters can't be translated
        s.c_str(),
        (int)s.size(),
        nullptr, 0);

    if (size == 0)
    {
        throw utility::details::create_system_error(GetLastError());
    }

    // this length includes the terminating null
    std::wstring buffer;
    buffer.resize(size);

    // now call again to format the string
    int result = ::MultiByteToWideChar(
        28591, // convert from Latin1
        MB_ERR_INVALID_CHARS, // fail if any characters can't be translated
        s.c_str(),
        (int)s.size(),
        &buffer[0], size);

    if (result != size)
    {
        throw utility::details::create_system_error(GetLastError());
    }

    return buffer;
#else
    return utf_to_utf<utf16char>(to_utf<char>(s, "Latin1", stop));
#endif
}

utf16string __cdecl conversions::default_code_page_to_utf16(const std::string &s)
{
    if(s.empty())
    {
        return utf16string();
    }

#ifdef _MS_WINDOWS
    // First have to convert to UTF-16.
    int size = ::MultiByteToWideChar(
        CP_ACP, // convert from Windows system default
        MB_ERR_INVALID_CHARS, // fail if any characters can't be translated
        s.c_str(),
        (int)s.size(),
        nullptr, 0); 
    if (size == 0)
    {
        throw utility::details::create_system_error(GetLastError());
    }

    // this length includes the terminating null
    std::wstring buffer;
    buffer.resize(size);

    // now call again to format the string
    int result = ::MultiByteToWideChar(
        CP_ACP, // convert from Windows system default
        MB_ERR_INVALID_CHARS, // fail if any characters can't be translated
        s.c_str(),
        (int)s.size(), 
        &buffer[0], size);
    if(result == size)
    {
        return buffer;
    }
    else
    {
        throw utility::details::create_system_error(GetLastError());
    }
#else // LINUX
    return utf_to_utf<utf16char>(to_utf<char>(s, std::locale(""), stop));
#endif
}

utility::string_t __cdecl conversions::to_string_t(utf16string &&s)
{
#ifdef _UTF16_STRINGS
    return std::move(s);
#else
    return utf16_to_utf8(std::move(s));
#endif
}

utility::string_t __cdecl conversions::to_string_t(std::string &&s)
{
#ifdef _UTF16_STRINGS
    return utf8_to_utf16(std::move(s));
#else
    return std::move(s);
#endif
}

utility::string_t __cdecl conversions::to_string_t(const utf16string &s)
{
#ifdef _UTF16_STRINGS
    return s;
#else
    return utf16_to_utf8(s);
#endif
}

utility::string_t __cdecl conversions::to_string_t(const std::string &s)
{
#ifdef _UTF16_STRINGS
    return utf8_to_utf16(s);
#else
    return s;
#endif
}

std::string __cdecl conversions::to_utf8string(std::string value) { return std::move(value); }

std::string __cdecl conversions::to_utf8string(const utf16string &value) { return utf16_to_utf8(value); }

utf16string __cdecl conversions::to_utf16string(const std::string &value) { return utf8_to_utf16(value); }

utf16string __cdecl conversions::to_utf16string(utf16string value) { return std::move(value); }


#pragma endregion

#pragma region datetime

#ifndef WIN32
datetime datetime::timeval_to_datetime(struct timeval time)
{
    const uint64_t epoch_offset = 11644473600LL; // diff between windows and unix epochs (seconds)
    uint64_t result = epoch_offset + time.tv_sec;
    result *= _secondTicks; // convert to 10e-7
    result += time.tv_usec; //add microseconds (in 10e-7)
    return datetime(result);
}
#endif

static bool is_digit(utility::char_t c) { return c >= _XPLATSTR('0') && c <= _XPLATSTR('9'); }

/// <summary>
/// Returns the current UTC date and time.
/// </summary>
datetime __cdecl datetime::utc_now()
{
#ifdef _MS_WINDOWS
    ULARGE_INTEGER largeInt;
    FILETIME fileTime;
    GetSystemTimeAsFileTime(&fileTime);

    largeInt.LowPart = fileTime.dwLowDateTime;
    largeInt.HighPart = fileTime.dwHighDateTime;

    return datetime(largeInt.QuadPart);    
#else //LINUX
    struct timeval time;
    gettimeofday(&time, nullptr);
    return timeval_to_datetime(time);
#endif
}

/// <summary>
/// Returns a string representation of the datetime. The string is formatted based on RFC 1123 or ISO 8601
/// </summary>
utility::string_t datetime::to_string(date_format format) const
{
#ifdef _MS_WINDOWS
    int status;

    ULARGE_INTEGER largeInt;
    largeInt.QuadPart = m_interval;

    FILETIME ft;
    ft.dwHighDateTime = largeInt.HighPart;
    ft.dwLowDateTime = largeInt.LowPart;

    SYSTEMTIME systemTime;
    if (!FileTimeToSystemTime((const FILETIME *)&ft, &systemTime))
    {
        throw utility::details::create_system_error(GetLastError());
    }

    std::wostringstream outStream;

    if ( format == RFC_1123 )
    {
#if _WIN32_WINNT < _WIN32_WINNT_VISTA 
        TCHAR dateStr[18] = {0};
        status = GetDateFormat(LOCALE_INVARIANT, 0, &systemTime, __TEXT("ddd',' dd MMM yyyy"), dateStr, sizeof(dateStr) / sizeof(TCHAR));
#else
        wchar_t dateStr[18] = {0};
        status = GetDateFormatEx(LOCALE_NAME_INVARIANT, 0, &systemTime, L"ddd',' dd MMM yyyy", dateStr, sizeof(dateStr) / sizeof(wchar_t), NULL);
#endif // _WIN32_WINNT < _WIN32_WINNT_VISTA 
        if (status == 0)
        {
            throw utility::details::create_system_error(GetLastError());
        }

#if _WIN32_WINNT < _WIN32_WINNT_VISTA 
        TCHAR timeStr[10] = {0};
        status = GetTimeFormat(LOCALE_INVARIANT, TIME_NOTIMEMARKER | TIME_FORCE24HOURFORMAT, &systemTime, "HH':'mm':'ss", timeStr, sizeof(timeStr) / sizeof(TCHAR));
#else
        wchar_t timeStr[10] = {0};
        status = GetTimeFormatEx(LOCALE_NAME_INVARIANT, TIME_NOTIMEMARKER | TIME_FORCE24HOURFORMAT, &systemTime, L"HH':'mm':'ss", timeStr, sizeof(timeStr) / sizeof(wchar_t));
#endif // _WIN32_WINNT < _WIN32_WINNT_VISTA 
        if (status == 0)
        {
            throw utility::details::create_system_error(GetLastError());
        }

        outStream << dateStr << " " << timeStr << " " << "GMT";
    }
    else if ( format == ISO_8601 )
    {
        const size_t buffSize = 64;
#if _WIN32_WINNT < _WIN32_WINNT_VISTA 
        TCHAR dateStr[buffSize] = {0};
        status = GetDateFormat(LOCALE_INVARIANT, 0, &systemTime, "yyyy-MM-dd", dateStr, buffSize);
#else
        wchar_t dateStr[buffSize] = {0};
        status = GetDateFormatEx(LOCALE_NAME_INVARIANT, 0, &systemTime, L"yyyy-MM-dd", dateStr, buffSize, NULL);
#endif // _WIN32_WINNT < _WIN32_WINNT_VISTA 
        if (status == 0)
        {
            throw utility::details::create_system_error(GetLastError());
        }

#if _WIN32_WINNT < _WIN32_WINNT_VISTA 
        TCHAR timeStr[buffSize] = {0};
        status = GetTimeFormat(LOCALE_INVARIANT, TIME_NOTIMEMARKER | TIME_FORCE24HOURFORMAT, &systemTime, "HH':'mm':'ss", timeStr, buffSize);
#else
        wchar_t timeStr[buffSize] = {0};
        status = GetTimeFormatEx(LOCALE_NAME_INVARIANT, TIME_NOTIMEMARKER | TIME_FORCE24HOURFORMAT, &systemTime, L"HH':'mm':'ss", timeStr, buffSize);
#endif // _WIN32_WINNT < _WIN32_WINNT_VISTA 
        if (status == 0)
        {
            throw utility::details::create_system_error(GetLastError());
        }

        outStream << dateStr << "T" << timeStr;
        uint64_t frac_sec = largeInt.QuadPart % _secondTicks;
        if (frac_sec > 0)
        {
            // Append fractional second, which is a 7-digit value with no trailing zeros
            // This way, '1200' becomes '00012'
            char buf[9] = { 0 };
            sprintf_s(buf, sizeof(buf), ".%07ld", (long int)frac_sec);
            // trim trailing zeros
            for (int i = 7; buf[i] == '0'; i--) buf[i] = '\0';
            outStream << buf;
        }
        outStream << "Z";
    }

    return outStream.str();
#else //LINUX
    uint64_t input = m_interval; 
    uint64_t frac_sec = input % _secondTicks;
    input /= _secondTicks; // convert to seconds
    time_t time = (time_t)input - (time_t)11644473600LL;// diff between windows and unix epochs (seconds)

    struct tm datetime;
    gmtime_r(&time, &datetime);

    const int max_dt_length = 64;
    char output[max_dt_length+1] = {0};
    
    if (format != RFC_1123 && frac_sec > 0)
    {
        // Append fractional second, which is a 7-digit value with no trailing zeros
        // This way, '1200' becomes '00012'
        char buf[9] = { 0 };
        snprintf(buf, sizeof(buf), ".%07ld", (long int)frac_sec);
        // trim trailing zeros
        for (int i = 7; buf[i] == '0'; i--) buf[i] = '\0';
        // format the datetime into a separate buffer
        char datetime_str[max_dt_length+1] = {0};
        strftime(datetime_str, sizeof(datetime_str), "%Y-%m-%dT%H:%M:%S", &datetime);
        // now print this buffer into the output buffer
        snprintf(output, sizeof(output), "%s%sZ", datetime_str, buf);
    }
    else
    {
        strftime(output, sizeof(output), 
            format == RFC_1123 ? "%a, %d %b %Y %H:%M:%S GMT" : "%Y-%m-%dT%H:%M:%SZ",
            &datetime);
    }

    return std::string(output);
#endif
}

#ifdef _MS_WINDOWS
bool __cdecl datetime::system_type_to_datetime(void* pvsysTime, uint64_t seconds, datetime * pdt)
{
    SYSTEMTIME* psysTime = (SYSTEMTIME*)pvsysTime;
    FILETIME fileTime;

    if (SystemTimeToFileTime(psysTime, &fileTime))
    {
        ULARGE_INTEGER largeInt;
        largeInt.LowPart = fileTime.dwLowDateTime;
        largeInt.HighPart = fileTime.dwHighDateTime;

        // Add hundredths of nanoseconds
        largeInt.QuadPart += seconds;

        *pdt = datetime(largeInt.QuadPart);
        return true;
    }
    return false;
}
#endif

// Take a string that represents a fractional second and return the number of ticks
// This is equivalent to doing atof on the string and multiplying by 10000000,
// but does not lose precision
template<typename StringIterator>
uint64_t timeticks_from_second(StringIterator begin, StringIterator end)
{
    int size = (int)(end - begin);
    _ASSERTE(begin[0] == U('.'));
    uint64_t ufrac_second = 0;
    for (int i = 1; i <= 7; ++i)
    {
        ufrac_second *= 10;
        int add = i < size ? begin[i] - U('0') : 0;
        ufrac_second += add;
    }
    return ufrac_second;
}

void extract_fractional_second(const utility::string_t& dateString, utility::string_t& resultString, uint64_t& ufrac_second)
{
    resultString = dateString;
    // First, the string must be strictly longer than 2 characters, and the trailing character must be 'Z'
    if (resultString.size() > 2 && resultString[resultString.size() - 1] == U('Z'))
    {
        // Second, find the last non-digit by scanning the string backwards
        auto last_non_digit = std::find_if_not(resultString.rbegin() + 1, resultString.rend(), is_digit);
        if (last_non_digit < resultString.rend() - 1)
        {
            // Finally, make sure the last non-digit is a dot:
            auto last_dot = last_non_digit.base() - 1;
            if (*last_dot == U('.'))
            {
                // Got it! Now extract the fractional second
                auto last_before_Z = std::end(resultString) - 1;
                ufrac_second = timeticks_from_second(last_dot, last_before_Z);
                // And erase it from the string
                resultString.erase(last_dot, last_before_Z);
            }
        }
    }
}

/// <summary>
/// Returns a string representation of the datetime. The string is formatted based on RFC 1123 or ISO 8601
/// </summary>
datetime __cdecl datetime::from_string(const utility::string_t& dateString, date_format format)
{
    // avoid floating point math to preserve precision
    uint64_t ufrac_second = 0;

#ifdef _MS_WINDOWS
    datetime result;
    if ( format == RFC_1123 )
    {
        SYSTEMTIME sysTime = {0};
    
        std::wstring month(3, L'\0');
        std::wstring unused(3, L'\0');

        const wchar_t * formatString = L"%3c, %2d %3c %4d %2d:%2d:%2d %3c";
        auto n = swscanf_s(dateString.c_str(), formatString, 
            unused.data(), unused.size(), 
            &sysTime.wDay, 
            month.data(), month.size(), 
            &sysTime.wYear,  
            &sysTime.wHour, 
            &sysTime.wMinute, 
            &sysTime.wSecond, 
            unused.data(), unused.size());
    
        if (n == 8)
        {
            std::wstring monthnames[12] = {L"Jan", L"Feb", L"Mar", L"Apr", L"May", L"Jun", L"Jul", L"Aug", L"Sep", L"Oct", L"Nov", L"Dec"};
            auto loc = std::find_if(monthnames, monthnames+12, [&month](const std::wstring& m) { return m == month;});

            if (loc != monthnames+12)
            {
                sysTime.wMonth = (short) ((loc - monthnames) + 1);
                if (system_type_to_datetime(&sysTime, ufrac_second, &result))
                {
                    return result;
                }
            }
        }
    }
    else if ( format == ISO_8601 )
    {
        // Unlike FILETIME, SYSTEMTIME does not have enough precision to hold seconds in 100 nanosecond
        // increments. Therefore, start with seconds and milliseconds set to 0, then add them separately

        // Try to extract the fractional second from the timestamp
        utility::string_t input;
        extract_fractional_second(dateString, input, ufrac_second);
        {
            SYSTEMTIME sysTime = { 0 };
            const wchar_t * formatString = L"%4d-%2d-%2dT%2d:%2d:%2dZ";
            auto n = swscanf_s(input.c_str(), formatString,
                &sysTime.wYear,  
                &sysTime.wMonth,  
                &sysTime.wDay, 
                &sysTime.wHour, 
                &sysTime.wMinute, 
                &sysTime.wSecond);

            if (n == 3 || n == 6)
            {
                if (system_type_to_datetime(&sysTime, ufrac_second, &result))
                {
                    return result;
                }
            }
        }
        {
            SYSTEMTIME sysTime = {0};
            DWORD date = 0;

            const wchar_t * formatString = L"%8dT%2d:%2d:%2dZ";
            auto n = swscanf_s(input.c_str(), formatString,
                &date, 
                &sysTime.wHour, 
                &sysTime.wMinute, 
                &sysTime.wSecond);

            if (n == 1 || n == 4)
            {
                sysTime.wDay = date % 100;
                date /= 100;
                sysTime.wMonth = date % 100;
                date /= 100;
                sysTime.wYear = (WORD)date;

                if (system_type_to_datetime(&sysTime, ufrac_second, &result))
                {
                    return result;
                }
            }
        }
        {
            SYSTEMTIME sysTime = {0};
            GetSystemTime(&sysTime);    // Fill date portion with today's information
            sysTime.wSecond = 0;
            sysTime.wMilliseconds = 0;
    
            const wchar_t * formatString = L"%2d:%2d:%2dZ";
            auto n = swscanf_s(input.c_str(), formatString,
                &sysTime.wHour, 
                &sysTime.wMinute, 
                &sysTime.wSecond);

            if (n == 3)
            {
                if (system_type_to_datetime(&sysTime, ufrac_second, &result))
                {
                    return result;
                }
            }
        }
    }

    return datetime();
#else
    std::string input(dateString);

    struct tm output = tm();

    if ( format == RFC_1123 )
    {
        strptime(input.data(), "%a, %d %b %Y %H:%M:%S GMT", &output);
    } 
    else
    {
        // Try to extract the fractional second from the timestamp
        utility::string_t input;
        extract_fractional_second(dateString, input, ufrac_second);

        auto result = strptime(input.data(), "%Y-%m-%dT%H:%M:%SZ", &output);

        if ( result == nullptr )
        {
            result = strptime(input.data(), "%Y%m%dT%H:%M:%SZ", &output);
        }
        if ( result == nullptr )
        {
            // Fill the date portion with the epoch,
            // strptime will do the rest
            memset(&output, 0, sizeof(struct tm));
            output.tm_year = 70;
            output.tm_mon = 1;
            output.tm_mday = 1;
            result = strptime(input.data(), "%H:%M:%SZ", &output);
        }
        if ( result == nullptr )
        {
            result = strptime(input.data(), "%Y-%m-%d", &output);
        }
        if ( result == nullptr )
        {
            result = strptime(input.data(), "%Y%m%d", &output);
        }
        if ( result == nullptr )
        {
            return datetime();
        }
    } 

    time_t time = timegm(&output);

    struct timeval tv = timeval();
    tv.tv_sec = time;
    tv.tv_usec = (unsigned int)ufrac_second;
    return timeval_to_datetime(tv);
#endif
}
#pragma endregion

#pragma region "timespan"

/// <summary>
/// Converts a timespan/interval in seconds to xml duration string as specified by
/// http://www.w3.org/TR/xmlschema-2/#duration
/// </summary>
utility::string_t __cdecl timespan::seconds_to_xml_duration(utility::seconds durationSecs)
{
    auto numSecs = durationSecs.count();

    // Find the number of minutes
    auto numMins =  numSecs / 60;
    if (numMins > 0)
    {
        numSecs = numSecs % 60;
    }

    // Hours
    auto numHours = numMins / 60;
    if (numHours > 0)
    {
        numMins = numMins % 60;
    }

    // Days
    auto numDays = numHours / 24;
    if (numDays > 0)
    {
        numHours = numHours % 24;
    }

    // The format is:
    // PdaysDThoursHminutesMsecondsS
    utility::ostringstream_t oss;

    oss << _XPLATSTR("P");
    if (numDays > 0)
    {
        oss << numDays << _XPLATSTR("D");
    }
    
    oss << _XPLATSTR("T");

    if (numHours > 0)
    {
        oss << numHours << _XPLATSTR("H");
    }

    if (numMins > 0)
    {
        oss << numMins << _XPLATSTR("M");
    }

    if (numSecs > 0)
    {
        oss << numSecs << _XPLATSTR("S");
    }

    return oss.str();
}

/// <summary>
/// Converts an xml duration to timespan/interval in seconds
/// http://www.w3.org/TR/xmlschema-2/#duration
/// </summary>
utility::seconds __cdecl timespan::xml_duration_to_seconds(utility::string_t timespanString)
{
    // The format is:
    // PnDTnHnMnS
    // if n == 0 then the field could be omitted
    // The final S could be omitted

    int64_t numSecs = 0;

    utility::istringstream_t is(timespanString);
    auto eof = std::char_traits<utility::char_t>::eof();

    std::basic_istream<utility::char_t>::int_type c;
    c = is.get(); // P

    while (c != eof)
    {
        int val = 0;
        c = is.get();

        while (is_digit((utility::char_t)c))
        {
            val = val * 10 + (c - L'0');
            c = is.get();

            if (c == '.')
            {
                // decimal point is not handled
                do { c = is.get(); } while(is_digit((utility::char_t)c));
            }
        }

        if (c == L'D') numSecs += val * 24 * 3600; // days
        if (c == L'H') numSecs += val * 3600; // Hours
        if (c == L'M') numSecs += val * 60; // Minutes
        if (c == L'S' || c == eof)
        {
            numSecs += val; // seconds
            break;
        }
    }

    return utility::seconds(numSecs);
}

#pragma endregion

}
}
