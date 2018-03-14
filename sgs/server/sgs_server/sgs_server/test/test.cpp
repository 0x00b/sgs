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

void *func(void *)
{
    while (1)
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
    MyClass(int n) : data(n)
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
    bool operator==(const MyClass &mc)
    {
        return data == mc.data;
    }
};

//jump
void jump(int N, int n, int step, int a[])
{
    for (int i = 1; i <= 2; ++i)
    {
        step += i;
        a[n] = i;
        if (step < N)
        {
            jump(N, n + 1, step, a);
        }
        else if (step == N)
        {
            //find
            for (int j = 0; j <= n; ++j)
            {
                printf("%d ", a[j]);
            }
            printf("\n");
        }
        step -= i;
    }
}

#include <string>
#include <stdlib.h>

#define MAX 10
class GDS
{
  public:
    std::string name;
    int B[MAX];
};

std::vector<std::string> &split(std::vector<std::string> &v, std::string str, std::string del)
{
    std::string::size_type spos = 0;
    std::string::size_type epos = str.find(del);
    v.clear();
    while (epos != std::string::npos)
    {
        v.push_back(str.substr(spos, epos - spos));
        spos = epos + 1;
        epos = str.find(del, spos);
    }
    v.push_back(str.substr(spos));
    return v;
}

void arrAdd(int a[], int b[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        a[i] += b[i];
    }
}

void arrSub(int a[], int b[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        a[i] -= b[i];
    }
}

bool arrLe(int a[], int b[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        if (a[i] > b[i])
        {
            return false;
        }
    }
    return true;
}

bool gdsbest(int A[], int tgds[], int bgds[], int tbest[], int best[], int N, int M)
{
    int remain_tgds_kinds = 0;
    int remain_bgds_kinds = 0;

    for (int i = 0; i < N; ++i)
    {
        if ((A[i] - tgds[i]) > 0)
        {
            ++remain_tgds_kinds;
        }
        if ((A[i] - bgds[i]) > 0)
        {
            ++remain_bgds_kinds;
        }
    }

    if (remain_tgds_kinds < remain_bgds_kinds)
    {
        return true;
    }
    else if (remain_tgds_kinds == remain_tgds_kinds)
    {
        int tgds_group = 0;
        int bgds_group = 0;
        for (int i = 0; i < M; ++i)
        {
            if (tbest[i] > 0)
            {
                tgds_group++;
            }
            if (best[i] > 0)
            {
                bgds_group++;
            }
        }
        if (tgds_group < bgds_group)
        {
            return true;
        }
    }

    return false;
}

//A     存放所有商品的个数，共有N个商品
//gds   存放商品组合数，和每个组合中各商品的个数
//tgds  临时存放当前组合中所有商品，和各商品个数
//bgds  存放最好组合中所有商品，和各商品个数
//tbest 存放当前组合中所有组合用了多少次
//best  存放最好组合中所有组合使用的次数
//N     所有商品的个数
//M     所有组合的个数
void dp_find(int A[], GDS *gds, int tgds[], int bgds[], int tbest[], int best[], int N, int M)
{
    for (int i = 0; i < M; ++i)
    {
        arrAdd(tgds, gds[i].B, N);
        tbest[i]++;
        if (arrLe(tgds, A, N))
        {
            if (gdsbest(A, tgds, bgds, tbest, best, N, M))
            {
                memcpy(best, tbest, sizeof(int) * N);
            }
            dp_find(A, gds, tgds, bgds, tbest, best, N, M);
        }
        tbest[i]--;
        arrSub(tgds, gds[i].B, N);
    }
}

int main()
{
    char buf[128];
    scanf("%s", buf); //n,m
    std::vector<std::string> v;
    split(v, buf, ",");

    int N = atoi(v[0].c_str());
    int M = atoi(v[1].c_str());
    GDS *gds = new GDS[M];
    int A[MAX];

    scanf("%s", buf); //a1,a2,a3...
    v = split(v, buf, ",");
    for (int i = 0; i < N && i < MAX; ++i)
    {
        A[i] = atoi(v[i].c_str());
    }

    //boom1,1,...
    //boom2,1,...
    for (int i = 0; i < M; ++i)
    {
        scanf("%s", buf);
        v = split(v, buf, ",");
        gds[i].name = v[0];
        for (int j = 0; j < MAX && j < N; ++j)
        {
            gds[i].B[j] = atoi(v[j + 1].c_str());
        }
    }

    int *tgds = new int[N];
    int *bgds = new int[N];
    int *tbest = new int[M];
    int *best = new int[M];
    memset(tgds, 0x00, sizeof(int) * N);
    memset(tbest, 0x00, sizeof(int) * M);
    memset(best, 0x00, sizeof(int) * M);

    memcpy(bgds, gds[0].B, sizeof(int) * N);
    best[0] = 1;

    dp_find(A, gds, tgds, bgds, tbest, best, N, M);

    bool flag = true;
    for (int i = 0; i < M; ++i)
    {
        if (best[i] > 0)
        {
            flag ? (flag = false) : printf(",");
            printf("%s*%d", gds[i].name.c_str(), best[i]);
        }
    }

    delete[] tgds;
    delete[] bgds;
    delete[] best;
    delete[] tbest;
    delete[] gds;

    return 0;

    //std::vector<std::string> v = split("231231,sfsf,3432", ",");

    for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it)
    {
        printf("%s \n", it->c_str());
    }

    return 0;

    int a[10];

    jump(10, 0, 0, a);

    return 0;

    int i;
    int j;

    int *p = &i;
    int *pj = &j;

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