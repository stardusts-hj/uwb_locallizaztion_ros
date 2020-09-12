#ifndef READ10_H
#define READ10_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>   /* File Control Definitions           */
#include <termios.h> /* POSIX Terminal Control Definitions */
#include <unistd.h>  /* UNIX Standard Definitions 	   */ 
#include <errno.h>   /* ERROR Number Definitions           */
#include "trilateration.h"	

int read_range(int *Range_deca);
int read_mesg(char *read_buffer, int *Range_deca);


#endif