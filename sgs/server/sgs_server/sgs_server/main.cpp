/**************************************************
* Author		: lijun
* Create Date	: 2018.1.9
* Function		: main
* Update		: 
* Update Date	:
**************************************************/

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
* Others		:
**************************************************/
int parse_args(int argc, char** argv)
{
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
* Return		:  -1/失败 0/成功
* Others		:
**************************************************/
int init_conf(std::string path)
{
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