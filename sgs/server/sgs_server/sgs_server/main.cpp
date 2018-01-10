/**************************************************
* Author		: lijun
* Create Date	: 2018.1.9
* Function		: main
* Update		: 
* Update Date	:
**************************************************/

//http://www.cplusplus.com/

#include "include.h"
#include "app.h"

/* some function for init or config*/

int parse_args(int argc, char** argv);
int init_conf();
int set_rlimit(int n);
int single_instance_running(const char* pid_file);
int daemonize();

App g_app;

/*************************************************
* Function		: main
* Description	: 
* Author		: lijun
* Create Date	: 2018.1.9
* Calls			: 
* Calledby		: 
* Inputs		: void
* Output		: 
* Return		: exit code
* Others		:  
**************************************************/
int main(int argc, char** argv)
{
	int nRet = 0;
	do{
		if ((nRet = parse_args(argc, argv)) < 0)
		{
			log.fatal("parse args err!\n");
			break;
		}
		//todo
		if ((nRet = init_conf()) < 0)
		{
			log.fatal("init_conf err!\n");
			break;
		}
		//todo
		if ((nRet = set_rlimit(1024)) < 0)
		{
			log.fatal("set_rlimit err!\n");
			break;
		}
		if ((nRet = single_instance_running(g_app.m_iConf["app"]["pid_file"].asCString())) < 0)
		{
			log.fatal("single_instance_running err!\n");
			break;
		}

		if(g_app.m_bDaemonize && daemonize() < 0)
		{
			log.fatal("daemonize err!\n");
			break;
		}

		log.start(g_app.m_iConf["log"].get("log_file", "log/sgs_server.log").asString(),
			g_app.m_iConf["log"].get("level", 4).asInt(),
			g_app.m_iConf["log"].get("console", 0).asInt(),
			g_app.m_iConf["log"].get("rotate", 1).asInt(),
			g_app.m_iConf["log"].get("max_size", 1073741824).asInt(),
			g_app.m_iConf["log"].get("max_file", 50).asInt());

		//todo
	}while(0);

	if (nRet < 0)
	{
		exit(1);
	}

	struct ev_loop *loop = ev_default_loop(0);
	g_app.m_iLoop = loop;

	g_app.m_iGame = new (std::nothrow) Game();
	//g_app.m_iGame->start();

	ev_loop(loop, 0);

	return 0;
}

/*************************************************
* Function		: parse_args
* Description	: 
* Author		: lijun
* Create Date	: 2018.1.9
* Calls			:
* Called by		:
* Inputs		: argc 
*				: argv  

* Output		:
* Return		: -1/f 0/s
* Others		: getopt/https://www.ibm.com/developerworks/cn/aix/library/au-unix-getopt.html
**************************************************/
int parse_args(int argc, char** argv)
{
	char ch;
	while ((ch = getopt(argc, argv, "Df:")) != -1)
	{
		switch (ch)
		{
		case 'D':
			g_app.m_bDaemonize = true;
			break;
		case 'f':
			g_app.m_stConf_File = std::string(optarg);
			break;
		case '?':
			//invalid opt
			log.info("invalid opt:%d\n", optopt);
			break;
		case ':':
			//lack of 
			break;
		default:
			break;
		}
	}
	return 0;
}

/*************************************************
* Function		: init_conf
* Description	: 
* Author		: lijun
* Create Date	: 2018.1.9
* Calls			:
* Called by		:
* Inputs		: 

* Output		: 
* Return		: -2/  -1/  0/s
* Others		:
**************************************************/																																																																																																																																																																																																																																																																																																	
int init_conf()
{
	std::ifstream in(g_app.m_stConf_File.c_str(), std::ifstream::binary);

	if (!in)
	{
		std::cout << "open file:" << g_app.m_stConf_File.c_str() << "failed!\n";
		return -2;
	}

	Json::Reader reader;																																																																																																																																																																																																																																																																																																																																																																																																																																																										
	bool bRet = reader.parse(in, g_app.m_iConf);
	in.close();
	if (bRet)
	{
		return 0;
	}
	std::cout << "parse:" << g_app.m_stConf_File.c_str() << "failed!\n";
	return -1;
}

/*************************************************
* Function		: set_rlimit
* Description	: 
* Author		: lijun
* Create Date	: 2018.1.9
* Calls			:
* Called by		:
* Inputs		: n

* Output		:
* Return		: -1/  other/
* Others		:
**************************************************/
int set_rlimit(int n)
{
	struct rlimit rt;
	rt.rlim_cur = rt.rlim_max = n;

	if(setrlimit(RLIMIT_NOFILE, &rt) == -1)
	{
		log.fatal("setrlimit err!\n");
		return -1;
	}
	
	return 0;
}

/*************************************************
* Function		: lock_file
* Description	:
* Author		: lijun
* Create Date	: 2018.1.10
* Calls			:
* Called by		:
* Inputs		:

* Output		:
* Return		: -1/failure 0/succ
* Others		:
**************************************************/
static int lock_file(int fd)
{
	struct flock fl;

	fl.l_type = F_WRLCK;
	fl.l_start = 0;
	fl.l_whence = SEEK_SET;
	fl.l_len = 0;
	return (fcntl(fd, F_SETLK, &fl));
}



/*************************************************
* Function		: single_instance_running
* Description	: 
* Author		: lijun
* Create Date	: 2018.1.9
* Calls			:
* Called by		:
* Inputs		:

* Output		:
* Return		: -1/  0/s
* Others		:
**************************************************/
#define LOCKMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
int single_instance_running(const char* pid_file)
{
	int     fd;
	char    buf[16];

	fd = open(pid_file, O_RDWR | O_CREAT, LOCKMODE);
	if (fd < 0) {
		return -1;
	}

	if (lock_file(fd) < 0) {
		if (errno == EACCES || errno == EAGAIN) {
			close(fd);
			return -1;
		}
		close(fd);
		return -1;
	}
	ftruncate(fd, 0);
	snprintf(buf, sizeof(buf), "%ld", (long)getpid());
	write(fd, buf, strlen(buf) + 1);

	return 0;
}


/*************************************************
* Function		: daemonize
* Description	: backend
* Author		: lijun
* Create Date	: 2018.1.10
* Calls			:
* Called by		:
* Inputs		:

* Output		:
* Return		: -1/failure 0/succ
* Others		:
**************************************************/
int daemonize()
{
	pid_t pid;
	int fd = -1;

	/* already a daemon */
	if (getppid() == 1)
		exit(1);

	pid = fork();
	if (pid < 0)
		exit(1);
	else if (pid != 0)
		exit(0);

	/* Cancel certain signals */
	signal(SIGCHLD, SIG_DFL); /* A child process dies */
	signal(SIGTSTP, SIG_IGN); /* Various TTY signals */
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGHUP, SIG_IGN); /* Ignore hangup signal */
	signal(SIGTERM, SIG_DFL); /* Die on SIGTERM */
	signal(SIGPIPE, SIG_IGN);

	/* become session leader https://www.ibm.com/developerworks/cn/linux/l-cn-nohup/*/
	if (setsid() < 0)
		exit(1);

	/* change working directory */
	//if (chdir("/") < 0)
	//    exit(1);

	/* clear our file mode creation mask */
	umask(0);

	for (fd = getdtablesize(); fd >= 0; fd--)
		close(fd);

	/* handle standart I/O */
	fd = open("/dev/null", O_RDWR);
	fd = dup(0);
	fd = dup(0);

	return 0;
}
