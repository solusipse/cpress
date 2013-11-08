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


#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <linux/input.h>
#include <linux/uinput.h>


int open_uinput();
int fd_initialize();

void finish();
int initialize();
void press_key(int key);
void error(char *error_code);
void ci_write(int uinput, int type, int code, int value);


int initialize()
{
    int uinput = fd_initialize();
    if(uinput == -1)
        error("initialization");
    usleep(3000);

    return uinput;
}


void finish(int uinput)
{
    close(uinput);
}


void press_key(int key)
{
    int uinput = initialize();
    ci_write(uinput, EV_KEY, key, 1);
    ci_write(uinput, EV_SYN, SYN_REPORT, 0);
    finish(uinput);
}


void press_combination(int num_args, ...)
{

    int i, uinput = initialize();
    va_list keylist;

    va_start(keylist, num_args);
    for(i = 0; i < num_args; i++)
    {
        ci_write(uinput, EV_KEY, va_arg(keylist, int), 1);
    }
    va_end(keylist);

    ci_write(uinput, EV_SYN, SYN_REPORT, 0);
    finish(uinput);
}


void ci_write(int uinput, int type, int code, int value)
{
    struct input_event ie;

    memset(&ie, 0, sizeof(ie));
    ie.type = type;
    ie.code = code;
    ie.value = value;

    if(write(uinput, &ie, sizeof(ie)) != sizeof(ie))
        error("write");
}


int open_uinput()
{
    int fd;

    if ((fd = open("/dev/input/uinput", O_WRONLY | O_NONBLOCK)) == -1)
        if ((fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK)) == -1)
            if ((fd = open("/dev/misc/uinput", O_WRONLY | O_NONBLOCK)) == -1)
            {
                printf("Please, run as root.\n");
                exit(1);
            }

    return fd;
}


int fd_initialize()
{
    int fd, key;
    struct uinput_user_dev dev;

    fd = open_uinput();
    memset(&dev, 0, sizeof(dev));
    strncpy(dev.name, "c2h2_spi_kbd", UINPUT_MAX_NAME_SIZE);

    if(write(fd, &dev, sizeof(dev)) != sizeof(dev))
        return -1;

    for (key = 0; key < 256; key++)
        if (ioctl(fd, UI_SET_KEYBIT, key) != 0)
            return -1;

    if(ioctl(fd, UI_SET_EVBIT, EV_KEY) != 0)
        return -1;

    if(ioctl(fd, UI_SET_EVBIT, EV_REP) != 0)
        return -1;

    if (ioctl(fd, UI_DEV_CREATE) != 0)
        return -1;

    return fd;
}


void error(char *error_code)
{
    perror(error_code);
    exit(1);
}