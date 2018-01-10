/**************************************************
* Author		: lijun
* Create Date	: 2018.1.9
* Function		: main
* Update		: 
* Update Date	:
**************************************************/

//http://www.cplusplus.com/

#include "include.h"

/* some function for init or config*/

/*************************************************
* Function		: parse_args
* Description	: 解析来自启动时传入的参数
* Author		: lijun
* Create Date	: 2018.1.9
* Calls			: 
* Called by		: 
* Inputs		: argc 参数的数量
*				: argv 参数数组

* Output		: 
* Return		: -1/失败 0/成功
* Others		:  
**************************************************/
int parse_args(int argc, char** argv);

/*************************************************
* Function		: init_conf
* Description	: 初始化配置，从配置文件中读取配置项
* Author		: lijun
* Create Date	: 2018.1.9
* Calls			:
* Called by		:
* Inputs		: path 配置文件路径

* Output		: 配置项
* Return		:  -1/失败 0/成功
* Others		:
**************************************************/
int init_conf(std::string path);

/*************************************************
* Function		: set_rlimit
* Description	: 设置打开的文件描述符的最大限制
* Author		: lijun
* Create Date	: 2018.1.9
* Calls			:
* Called by		:
* Inputs		: n 文件描述符的最大数量

* Output		: 
* Return		: -1/设置失败 other/成功
* Others		:
**************************************************/
int set_rlimit(int n);

/*************************************************
* Function		: single_instance_running
* Description	: 保证程序单例运行
* Author		: lijun
* Create Date	: 2018.1.9
* Calls			:
* Called by		:
* Inputs		: 

* Output		: 
* Return		: -1/已经运行 0/没有运行
* Others		:
**************************************************/
int single_instance_running();

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
	/* 获取初始化参数*/
	int nRet = 0;
	if (parse_args(argc, argv) < 0)
	{
		exit(1);
	}

	return 0;
}

/*************************************************
* Function		: parse_args
* Description	: 解析来自启动时传入的参数
* Author		: lijun
* Create Date	: 2018.1.9
* Calls			:
* Called by		:
* Inputs		: argc 参数的数量
*				: argv 参数数组

* Output		:
* Return		: -1/失败 0/成功
* Others		: getopt说明/https://www.ibm.com/developerworks/cn/aix/library/au-unix-getopt.html
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
			printf("invalid opt:%d\n", optopt);
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
* Description	: 初始化配置，从配置文件中读取配置项
* Author		: lijun
* Create Date	: 2018.1.9
* Calls			:
* Called by		:
* Inputs		: path 配置文件路径

* Output		: 配置项
* Return		: -2/打开文件失败 -1/解析失败 0/成功
* Others		:
**************************************************/
int init_conf(std::string path)
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
* Description	: 设置打开的文件描述符的最大限制
* Author		: lijun
* Create Date	: 2018.1.9
* Calls			:
* Called by		:
* Inputs		: n 文件描述符的最大数量

* Output		:
* Return		: -1/设置失败 other/成功
* Others		:
**************************************************/
int set_rlimit(int n)
{
	struct rlimit rt;
	
}

/*************************************************
* Function		: single_instance_running
* Description	: 保证程序单例运行
* Author		: lijun
* Create Date	: 2018.1.9
* Calls			:
* Called by		:
* Inputs		:

* Output		:
* Return		: -1/已经运行 0/没有运行
* Others		:
**************************************************/
int single_instance_running()
{

}