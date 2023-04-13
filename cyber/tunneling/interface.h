#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <stddef.h> /**/

int InterfaceCreate();

int InterfaceSet(char* addr, int mtu);

int InterfaceRecieve(int tunfd, void *buf, size_t len);

int InterfaceRespond(int tunfd, void *msg, size_t msg_len);

int InterfaceSetServerRouting();

int InterfaceCleanServerRouting();

#endif /*__INTERFACE_H__*/
