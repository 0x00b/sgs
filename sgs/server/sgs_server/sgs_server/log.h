/*************************************************
Copyright   : sgs
Author      : lijun
Date        : 2018.01.10
Description : log
**************************************************/
#ifndef _SGS_LOG_H_
#define _SGS_LOG_H_

#include "include.h"

typedef long long int64_t;

enum LEVEL {
    LEVEL_PANIC = 0,
    LEVEL_FATAL,
    LEVEL_ERROR,
    LEVEL_WARN,
    LEVEL_INFO,
    LEVEL_DEBUG,
};

enum CONSOLE {
	CONSOLE_OFF = 0,
	CONSOLE_ON,
};

enum ROTATE {
	ROTATE_OFF = 0,
	ROTATE_ON,
};

class Log {
public:
    Log();
    virtual ~Log();
    void start(std::string log_file, int level, int console, int rotate, int64_t max_size, int max_file);
    void stop();
    void panic(char *fmt, ...);
    void fatal(char *fmt, ...);
    void error(char *fmt, ...);
    void warn(char *fmt, ...);
    void info(char *fmt, ...);
    void debug(char *fmt, ...);
	
private:
    void output(char *buf, int cnt);
	void rotate();	
	bool check_day_changed();
	void rotate_day();

private:
	std::string				_log_file;
    int					_level;
    int					_fd;
    int					_console;
    int					_rotate;
    int64_t				_max_size;
    int64_t				_current_size;
	int					_max_file;
	struct tm       *_curr_day;
	int _year;
	int _month;
	int _day;
#ifdef POSIX_PTHREAD
	pthread_mutex_t		_mutex;
#endif
};

#endif
