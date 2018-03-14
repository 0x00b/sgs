#include "../include.h"
#include "../ppacket.cpp"
#include <pthread.h>


class Test
{
    public:
    Test(int x)
    {
        a = x;
    }
        int a;

};

void* func(void* )
{
   while(1)
   {   

   } 
   return NULL;
}

#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <algorithm>

class MyClass
{
public:
    int data;
    MyClass(int n):data(n)
    {
        printf("con");
    }
    ~MyClass()
    {
        printf("de");
    }

    bool operator==(int n)
    {
        return data == n;
    }
    bool operator==(const MyClass&  mc)
    {
        return data == mc.data;
    }
};

int main()
{

    //signal(SIGSEGV, SIG_DFL);

    int i ;
    int j;

    int* p = &i;
    int* pj = &j;

    sembuf s;

    std::list<MyClass> lll;

    lll.emplace_back(111);

    //lll.remove(111);
    lll.erase(lll.end());

    int llll = lll.size();

    std::vector<MyClass> vvv;

    vvv.push_back(1111);
    vvv.push_back(2222);
    vvv.push_back(1111);
    vvv.push_back(2222);
    vvv.push_back(2222);

    std::remove(vvv.begin(), vvv.end(), 1111);
    vvv.erase(vvv.end());

    llll = vvv.size();
    //    semget(,);

    srand(time(NULL));
    
    printf("%u\n", sizeof(long));
/*

    pthread_t p;
    pthread_create(&p,NULL,func,NULL);
    pthread_create(&p, NULL, func, NULL);
    pthread_create(&p, NULL, func, NULL);

    while (1)
    {
    }
    
    std::list<std::shared_ptr<Test>> l;
    l.emplace_front(new Test(1));

    printf("%d",l.front()->a);
     */
/*
    std::map<int, std::shared_ptr<Test>> m;
    if(m.find(0) == m.end()){
        //
        printf("no find");
    }
    m[0]->a = 0;

    int* pn = NULL;
    *pn = 10;

    for (int i = 0; i < 100; i++)
    {
        printf("%d\n", rand());
    }

    
    int ret = 0;
    sockaddr_in sa;
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(37373);
    ret = inet_pton(AF_INET, "0.0.0.0", &sa.sin_addr.s_addr);

    ret = connect(fd, (sockaddr *)&sa, sizeof(sa));
    if(ret == -1)
    {
        std::cout<<strerror(errno)<<std::endl;
    }
    PPacket p;
    p.body = "hello world!";
    p.pack(1);

    ret = send(fd, p.data.c_str(), p.data.length(), 0);

    close(fd);*/
}