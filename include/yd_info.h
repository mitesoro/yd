#ifndef YD_EXAMPLE_H
#define YD_EXAMPLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef WINDOWS
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "ydApi.h"
#include "ydError.h"

void startExample5(const char *configFilename,const char *username,const char *password,const char *instrumentID);

#endif
