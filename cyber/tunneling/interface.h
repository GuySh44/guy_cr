#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <stddef.h> /**/

int InterfaceCreate();

int InterfaceSet(char* addr, int mtu);

int InterfaceRecieve(int tunfd, void *buf, size_t len);

#endif /*__INTERFACE_H__*/
