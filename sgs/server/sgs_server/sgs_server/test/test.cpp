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

int main()
{

    //signal(SIGSEGV, SIG_DFL);

    srand(time(NULL));

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