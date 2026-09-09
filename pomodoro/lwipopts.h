#ifndef _LWIPOPTS_H
#define _LWIPOPTS_H

// Standardinställningar för Pico W utan operativsystem (NO_SYS = 1)
#define NO_SYS                      1
#define LWIP_SOCKET                 0
#define LWIP_COMPAT_SOCKETS         0
#define LWIP_CORE_LOCKING           0
#define LWIP_NETCONN                0
#define LWIP_IPV4                   1
#define LWIP_IPV6                   0
#define LWIP_DHCP                   1
#define LWIP_ICMP                   1
#define LWIP_UDP                    1
#define LWIP_TCP                    1
#define MEM_LIBC_MALLOC             0
#define MEM_ALIGNMENT               4
#define MEM_SIZE                    4000
#define MEMP_NUM_TCP_SEG            32
#define MEMP_NUM_ARP_QUEUE          10
#define PBUF_POOL_SIZE              24
#define LWIP_ARP                    1
#define LWIP_ETHERNET               1
#define LWIP_IGMP                   0
#define LWIP_DNS                    1

#endif /* _LWIPOPTS_H */
