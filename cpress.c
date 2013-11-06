#include <stdio.h>
#include <ctype.h>
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

static int uinput = -1;

int open_uinput();
int fd_initialize();

void finish();
void initialize();
void press_key(int key);
void error(char *error_code);
void ci_write(int type, int code, int value);


void initialize()
{
    uinput = fd_initialize();
    if(uinput == -1)
        error("pemissions");
}


void finish()
{
    close(uinput);
}


void press_key(int key)
{
    ci_write(EV_KEY, key, 1);
    ci_write(EV_SYN, SYN_REPORT, 0);
}


void ci_write(int type, int code, int value)
{
    usleep(5000);
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
                error("permissions");

    return fd;
}


int fd_initialize(){
    int fd, key;
    struct uinput_user_dev dev;

    fd = open_uinput();

    memset(&dev, 0, sizeof(dev));
    strncpy(dev.name, "c2h2_spi_kbd", sizeof(dev.name));
    dev.name[sizeof(dev.name) - 1] = 0;

    if(write(fd, &dev, sizeof(dev)) != sizeof(dev))
        error("write");

    if(ioctl(fd, UI_SET_EVBIT, EV_KEY) != 0)
        error("write");

    if(ioctl(fd, UI_SET_EVBIT, EV_REP) != 0)
        error("write");

    for (key = KEY_RESERVED; key <= KEY_UNKNOWN; key++)
        if (ioctl(fd, UI_SET_KEYBIT, key) != 0)
            error("write");

    if (ioctl(fd, UI_DEV_CREATE) != 0)
        error("write");

    return fd;

}


void error(char *error_code)
{
    perror(error_code);
    exit(1);
}