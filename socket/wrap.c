#include<stdlib.h>
#include<errno.h>
#include<sys/socket.h>

void perror_exit(const char *s)
{
    perror(s);
    exit(1);
}

int Accept(int fd, struct sockaddr * sa, socklen_t *salenptr)
{
    int n;
again:
    if (n=accept(fd, sa, salenptr) < 0)
    {
        if ((errno==ECONNABORTED) || (errno==EINTR))
            goto again;
        else
            perror_exit("accept error");
    }
    return n;
}

void Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if (bind(fd, sa, salen) < 0)
    {
        perror_exit("bind error");
    }
}

void Connect(int fd, const struct sockaddr * sa, socklen_t salen)
{
    if (connect(fd, sa, salen) < 0)
    {
        perror_exit("connect error");
    }
}

void Listen(int fd, int backlog)
{
    if (listen(fd, backlog) < 0)
    {
        perror_exit("listen error");
    }
}

int Socket(int family, int type, int protocol)
{
    int n;
    if ((n=socket(family, type, protocol)) < 0)
    {
        perror_exit("socket error");
    }
    return n;
}

ssize_t Read(int fd, void *prt, size_t nbytes)
{
    ssize_t n;

again:
    if (n=read(fd, ptr, nbytes)==-1)
    {
        if (errno==EINTR)
            goto again;
        else
            return -1;
    }
    return n;
}

ssize_t Write(int fd, const void *ptr, size_t nbytes)
{
    ssize_t n;

again:
    if ((n=Write(fd, ptr, nbytes))==-1)
    {
        if (errno==EINTR)
            goto again;
        else 
            return -1;
    }
    return n;
}

void Close(int fd)
{
    if (close(fd)== -1)
    {
        perror_exit("close error");
    }
}

ssize_t Readn(int fd, void *vptr, size_t n)
{
    size_t nleft;
    ssize_t nread;
    char *ptr;

    ptr = vptr;
    nleft = n;
    
    while(nleft>0)
    {
        if ((nread = read(fd, ptr, nleft)) < 0)
        {
            if(errno==EINTR)
                nread = 0;
            else 
                return -1;
        } 
        else if (nread==0)
        {
            break;
        }
        nleft -=nread;
        ptr += nread;
    }
    return n-nleft;
}

ssize_t Writen(int fd, const char *vptr, size_t n)
{
    size_t nleft;
    ssize_t nwritten;
    const char *ptr;

    ptr = vptr;
    nleft = n;
    while(nleft > 0)
    {
        if ((nwritten = Write(fd, ptr, nleft)) <= 0)
        {
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0;
            else
                return -1;
        }
        nleft -= nwritten;
        ptr += nwritten;
    }
    return n;
}

static ssize_t my_read(int fd, char *ptr)
{
    static int read_cnt;
    static char * read_ptr;
    static char * read_buf[100];

    if (read_cnt <= 0)
    {
    again:
        if ((read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0)
        {
            if (errno==EINTR)
                goto again;
            return -1;
        }
        else if (read_cnt==0)
        {
            return 0;
        }
        read_ptr = read_buf;
    }
    read_cnt--;
    *ptr = *read_ptr++;
    return 1;
}

ssize_t Readline(int fd, void * vptr, size_t maxlen)
{
    ssize_t n, rc;
    char c, *ptr;

    ptr = vptr;
    for (n = 1; n < maxlen; n++)
    {
        if ((rc=my_read(fd, &c)) == 1)
        {
            *ptr++=c;
            if (c=='\n')
                break;
        }
        else if (rc == 0)
        {
            *ptr = 0;
            return n-1;
        }
        else 
            return -1;
    }
    *ptr = 0;
    return n;
}
