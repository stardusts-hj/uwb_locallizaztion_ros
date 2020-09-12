#ifndef __READSERIAL_H__
#define __READSERIAL_h__



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
#include <fcntl.h>
#include <unistd.h>
 
#include <termios.h> //set baud rate
 
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>

//#define rec_buf_wait_2s 2
#define buffLen 1024
#define rcvTimeOut 2
 
 int read_data_tty(int fd, char *rec_buf, int rec_wait);
 int device_485_receive(int fd);




#endif