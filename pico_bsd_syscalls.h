#ifndef PICO_BSD_SYSCALLS_H_
#define PICO_BSD_SYSCALLS_H_

#include "pico_bsd_sockets.h"

static inline int socket(int domain, int type, int proto)
{
    return pico_newsocket(domain, type, proto);
}

static inline int bind(int sd, struct sockaddr * local_addr, socklen_t socklen)
{
    return pico_bind(sd, local_addr, socklen);
}

static inline int listen(int sd, int backlog)
{
    return pico_listen(sd, backlog);
}

static inline int connect(int sd, struct sockaddr *_saddr, socklen_t socklen)
{
    return pico_connect(sd, _saddr, socklen);
}

static inline int accept(int sd, struct sockaddr *_orig, socklen_t *socklen)
{
    return pico_accept(sd, _orig, socklen);
}

static inline int sendto(int sd, void * buf, int len, int flags, struct sockaddr *_dst, socklen_t socklen)
{
    return pico_sendto(sd, buf, len, flags, _dst, socklen);
}

static inline int recvfrom(int sd, void * buf, int len, int flags, struct sockaddr *_addr, socklen_t *socklen)
{
    return pico_recvfrom(sd, buf, len, flags, _addr, socklen);
}

static inline int write(int sd, void * buf, int len)
{
    return pico_write(sd, buf, len);
}

static inline int send(int sd, void * buf, int len, int flags)
{
    return pico_send(sd, buf, len, flags);
}

static inline int read(int sd, void * buf, int len)
{
    return pico_read(sd, buf, len);
}

static inline int recv(int sd, void * buf, int len, int flags)
{
    return pico_recv(sd, buf, len, flags);
}

static inline int close(int sd)
{
    return pico_close(sd);
}

static inline int shutdown(int sd, int how)
{
    return pico_shutdown(sd, how);
}

static inline int getsockname(int sd, struct sockaddr * local_addr, socklen_t *socklen)
{
    return pico_getsockname(sd, local_addr, socklen);
}

static inline int getpeername(int sd, struct sockaddr * remote_addr, socklen_t *socklen)
{
    return pico_getpeername(sd, remote_addr, socklen);
}

static inline int fcntl(int sd, int cmd, int arg)
{
    return pico_fcntl(sd, cmd, arg);
}

#ifdef PICO_SUPPORT_DNS_CLIENT
static inline struct hostent *gethostbyname(const char *name)
{
    return pico_gethostbyname(name);
}
    
static inline int getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res)
{
    return pico_getaddrinfo(node, service, hints, res);
}

static inline void freeaddrinfo(struct addrinfo *res)
{
    return pico_freeaddrinfo(res);
}

#endif

static inline int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen)
{
    return pico_setsockopt(sockfd, level, optname, optval, optlen); 
}

static inline int getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen)
{
    return pico_getsockopt(sockfd, level, optname, optval, optlen);
}

static inline int select(int nfds, pico_fd_set *readfds, pico_fd_set *writefds, pico_fd_set *exceptfds, struct timeval *timeout)
{
    return pico_select(nfds, readfds, writefds, exceptfds, timeout);
}

static inline int pselect(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, const struct timespec *timeout, const sigset_t *sigmask)
{
    return pico_pselect(nfds, readfds, writefds, exceptfds, timeout, sigmask);
}

static inline int poll(struct pollfd *pfd, nfds_t npfd, int timeout)
{
    return pico_poll(pfd, npfd, timeout);
}

static inline int ppoll(struct pollfd *pfd, nfds_t npfd, const struct timespec *timeout_ts, const sigset_t *sigmask)
{
    return pico_ppoll(pfd, npfd, timeout_ts, sigmask);
}

#ifdef PICO_SUPPORT_SNTP_CLIENT
static int gettimeofday(struct timeval *tv, struct timezone *tz)
{
    return pico_gettimeofday(tv, tz);
}
#endif

static inline const char *inet_ntop(int af, const void *src, char *dst, socklen_t size)
{
    return pico_inet_ntop(af, src, dst, size);
}

static inline char *inet_ntoa(struct in_addr in)
{
    return pico_inet_ntoa(in);
}

static inline uint32_t htonl(uint32_t le) 
{
    return long_be(le);
}

static inline uint32_t ntohl(uint32_t le) 
{
    return long_be(le);
}

static inline uint16_t htons(uint16_t le) 
{
    return short_be(le);
}

static inline uint16_t ntohs(uint16_t le) 
{
    return short_be(le);
}

#endif /* PICO_BSD_SYSCALLS_H_ */
