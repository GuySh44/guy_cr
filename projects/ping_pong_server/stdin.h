#ifndef __STDIN_H__
#define __STDIN_H__

#include <stddef.h>

int StdinRecieve(void *buf, size_t buf_size);

int StdResponse(char *msg);

#endif /* __STDIN_H__ */
