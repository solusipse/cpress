/*
cpress - C library for simulating keypress.

Requirements:
- Linux
- running uinput (modprobe uinput)
- root privileges

There are Python and Go bindings for this library.

-------------------------------------------------------------------------------

License: MIT (http://www.opensource.org/licenses/mit-license.php)
Repository: https://github.com/solusipse/cpress

-------------------------------------------------------------------------------
*/

#ifndef CPRESS_H
#define CPRESS_H

#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <termios.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <linux/input.h>
#include <linux/uinput.h>

int uinput = -1;

int open_uinput();
int fd_initialize();

void finish();
void initialize();
void press_key(int key);
void ask_for_password();
void check_permissions();
void error(char *error_code);
void ci_write(int type, int code, int value);

#endif