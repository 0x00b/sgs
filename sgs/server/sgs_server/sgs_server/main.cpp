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

int parse_args(int argc, char** argv);
int init_conf();
int set_rlimit(int n);
int single_instance_running();
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
	/* ��ȡ��ʼ������*/
	int nRet = 0;
	do{
		if ((nRet = parse_args(argc, argv)) < 0)
		{
			printf("parse args err!\n");
			break;
		}
		//todo
		if ((nRet = init_conf()) < 0)
		{
			printf("init_conf err!\n");
			break;
		}
		//todo
		if ((nRet = set_rlimit(1024)) < 0)
		{
			printf("set_rlimit err!\n");
			break;
		}
		if ((nRet = single_instance_running()) < 0)
		{
			printf("single_instance_running err!\n");
			break;
		}

		if(g_app.m_bDaemonize && daemonize() < 0)
		{
			printf("daemonize err!\n");
			break;
		}

		//todo
	}while(0);

	if (nRet < 0)
	{
		exit(1);
	}



	return 0;
}

/*************************************************
* Function		: parse_args
* Description	: ����������ʱ����Ĳ���
* Author		: lijun
* Create Date	: 2018.1.9
* Calls			:
* Called by		:
* Inputs		: argc ����������
*				: argv ��������

* Output		:
* Return		: -1/ʧ�� 0/�ɹ�
* Others		: getopt˵��/https://www.ibm.com/developerworks/cn/aix/library/au-unix-getopt.html
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
* Description	: ��ʼ�����ã��������ļ��ж�ȡ������
* Author		: lijun
* Create Date	: 2018.1.9
* Calls			:
* Called by		:
* Inputs		: 

* Output		: ������
* Return		: -2/���ļ�ʧ�� -1/����ʧ�� 0/�ɹ�
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
* Description	: ���ô򿪵��ļ����������������
* Author		: lijun
* Create Date	: 2018.1.9
* Calls			:
* Called by		:
* Inputs		: n �ļ����������������

* Output		:
* Return		: -1/����ʧ�� other/�ɹ�
* Others		:
**************************************************/
int set_rlimit(int n)
{
	struct rlimit rt;
	rt.rlim_cur = rt.rlim_max = n;

	if(setrlimit(RLIMIT_NOFILE, &rt) == -1)
	{
		printf("setrlimit err!\n");
		return -1;
	}
	
	return 0;
}

/*************************************************
* Function		: single_instance_running
* Description	: ��֤����������
* Author		: lijun
* Create Date	: 2018.1.9
* Calls			:
* Called by		:
* Inputs		:

* Output		:
* Return		: -1/�Ѿ����� 0/û������
* Others		:
**************************************************/
int single_instance_running()
{

	return 0;
}


/*************************************************
* Function		: daemonize
* Description	: backend
* Author		: lijun
* Create Date	: 2018.1.9
* Calls			:
* Called by		:
* Inputs		:

* Output		:
* Return		: -1/failure 0/succ
* Others		:
**************************************************/
int daemonize()
{
	
	return 0;
}