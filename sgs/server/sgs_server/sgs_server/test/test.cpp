#include "../include.h"
#include "../ppacket.cpp"

int main()
{
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

    close(fd);
}