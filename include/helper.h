// Helper functions
#ifndef STRING_HELPER_H
#define STRING_HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>

#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif
#ifndef STRCASECMP
#define STRCASECMP  _stricmp
#endif
#ifndef STRNCASECMP
#define STRNCASECMP _strnicmp
#endif
#ifndef STRCPY
#define STRCPY(sFilePath, nLength, sPath) strcpy_s(sFilePath, nLength, sPath)
#endif

#ifndef FOPEN
#define FOPEN(fHandle,filename,mode) fopen_s(&fHandle, filename, mode)
#endif
#ifndef FOPEN_FAIL
#define FOPEN_FAIL(result) (result != 0)
#endif
#ifndef SSCANF
#define SSCANF sscanf_s
#endif
#ifndef SPRINTF
#define SPRINTF sprintf_s
#endif
#else // Linux Includes
#include <string.h>
#include <strings.h>

#ifndef STRCASECMP
#define STRCASECMP  strcasecmp
#endif
#ifndef STRNCASECMP
#define STRNCASECMP strncasecmp
#endif
#ifndef STRCPY
#define STRCPY(sFilePath, nLength, sPath) strcpy(sFilePath, sPath)
#endif

#ifndef FOPEN
#define FOPEN(fHandle,filename,mode) (fHandle = fopen(filename, mode))
#endif
#ifndef FOPEN_FAIL
#define FOPEN_FAIL(result) (result == NULL)
#endif
#ifndef SSCANF
#define SSCANF sscanf
#endif
#ifndef SPRINTF
#define SPRINTF sprintf
#endif
#endif

#ifndef EXIT_WAIVED
#define EXIT_WAIVED 2
#endif

inline bool checkCmdLineFlag(const int argc, const char **argv, const char *string_ref)
{
    bool bFound = false;

    if (argc >= 1)
    {
        for (int i=1; i < argc; i++)
        {
            int string_start = stringRemoveDelimiter('-', argv[i]);
            const char *string_argv = &argv[i][string_start];

            const char *equal_pos = strchr(string_argv, '=');
            int argv_length = (int)(equal_pos == 0 ? strlen(string_argv) : equal_pos - string_argv);

            int length = (int)strlen(string_ref);

            if (length == argv_length && !STRNCASECMP(string_argv, string_ref, length))
            {
                bFound = true;
                continue;
            }
        }
    }

    return bFound;
}

template <class T>
inline bool getCmdLineArgumentValue(const int argc, const char **argv, const char *string_ref, T *value)
{
    bool bFound = false;

    if (argc >= 1)
    {
        for (int i=1; i < argc; i++)
        {
            int string_start = stringRemoveDelimiter('-', argv[i]);
            const char *string_argv = &argv[i][string_start];
            int length = (int)strlen(string_ref);

            if (!STRNCASECMP(string_argv, string_ref, length))
            {
                if (length+1 <= (int)strlen(string_argv))
                {
                    int auto_inc = (string_argv[length] == '=') ? 1 : 0;
                    *value = (T)atoi(&string_argv[length + auto_inc]);
                }

                bFound = true;
                i=argc;
            }
        }
    }

    return bFound;
}

inline int getCmdLineArgumentInt(const int argc, const char **argv, const char *string_ref)
{
    bool bFound = false;
    int value = -1;

    if (argc >= 1)
    {
        for (int i=1; i < argc; i++)
        {
            int string_start = stringRemoveDelimiter('-', argv[i]);
            const char *string_argv = &argv[i][string_start];
            int length = (int)strlen(string_ref);

            if (!STRNCASECMP(string_argv, string_ref, length))
            {
                if (length+1 <= (int)strlen(string_argv))
                {
                    int auto_inc = (string_argv[length] == '=') ? 1 : 0;
                    value = atoi(&string_argv[length + auto_inc]);
                }
                else
                {
                    value = 0;
                }

                bFound = true;
                continue;
            }
        }
    }

    if (bFound)
    {
        return value;
    }
    else
    {
        return 0;
    }
}

inline float getCmdLineArgumentFloat(const int argc, const char **argv, const char *string_ref)
{
    bool bFound = false;
    float value = -1;

    if (argc >= 1)
    {
        for (int i=1; i < argc; i++)
        {
            int string_start = stringRemoveDelimiter('-', argv[i]);
            const char *string_argv = &argv[i][string_start];
            int length = (int)strlen(string_ref);

            if (!STRNCASECMP(string_argv, string_ref, length))
            {
                if (length+1 <= (int)strlen(string_argv))
                {
                    int auto_inc = (string_argv[length] == '=') ? 1 : 0;
                    value = (float)atof(&string_argv[length + auto_inc]);
                }
                else
                {
                    value = 0.f;
                }

                bFound = true;
                continue;
            }
        }
    }

    if (bFound)
    {
        return value;
    }
    else
    {
        return 0;
    }
}

inline bool getCmdLineArgumentString(const int argc, const char **argv,
                                     const char *string_ref, char **string_retval)
{
    bool bFound = false;

    if (argc >= 1)
    {
        for (int i=1; i < argc; i++)
        {
            int string_start = stringRemoveDelimiter('-', argv[i]);
            char *string_argv = (char *)&argv[i][string_start];
            int length = (int)strlen(string_ref);

            if (!STRNCASECMP(string_argv, string_ref, length))
            {
                *string_retval = &string_argv[length+1];
                bFound = true;
                continue;
            }
        }
    }

    if (!bFound)
    {
        *string_retval = NULL;
    }

    return bFound;
}

#endif