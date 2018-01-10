/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.9
Description : include some usage header that don't change
**************************************************/

#ifndef _SGS_INCLUDE_H_
#define _SGS_INCLUDE_H_

/* system or c headers*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <errno.h>
#include <unistd.h> //getopt
#include <sys/resource.h>//rlimit
#include <stdarg.h> //va_start
#ifdef POSIX_PTHREAD
#include <pthread.h>
#endif


/* c++ headers*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <list>

/* other headers*/
#include "zlib/zlib.h"
#include "include/libev/ev++.h"
#include "libs/base64.h"
#include "libs/json/json.h"

/* global variables*/

#define log g_app.m_iLog

#endif // !_SGS_INCLUDE_H_
