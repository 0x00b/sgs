#ifndef _SGS_INCLUDE_H_
#define _SGS_INCLUDE_H_

/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.9
Description : include some usage header that don't change
**************************************************/

/* system or c headers*/
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h> //getopt
#include <sys/resource.h>//rlimit

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

#include "app.h"

/* global variables*/

#endif // !_SGS_INCLUDE_H_
