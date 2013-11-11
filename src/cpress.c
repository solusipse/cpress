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

#include "cpress.h"

void initialize()
{
    /* This function is used for initializing everything. */

    check_permissions();

    uinput = fd_initialize();
    if(uinput == -1)
        error("initialization");

    usleep(10000); /* That is required because /dev/input
    needs some time for creating new input. */
}


void finish()
{
    /* Use this function at the end to clean up. */
    ioctl(uinput, UI_DEV_DESTROY);
    close(uinput);
}


void press_key(int key)
{
    /* This function is used for simulating single
    press and release action. */
    ci_write(EV_KEY, key, 1);
    ci_write(EV_KEY, key, 0);
    ci_write(EV_SYN, SYN_REPORT, 0);
}


void hold_key(int key)
{
    /* Use this to add modifiers, for example KEY_LEFTSHIFT */
    ci_write(EV_KEY, key, 1);
    ci_write(EV_SYN, SYN_REPORT, 0);
}


void release_key(int key)
{
    /* Used to release keys triggered by hold_key() */
    ci_write(EV_KEY, key, 0);
    ci_write(EV_SYN, SYN_REPORT, 0);
}


void press_combination(int num_args, ...)
{
    /* This function is used for simulating multiple
    keys pressed in one moment. */
    va_list keylist;
    int i;

    va_start(keylist, num_args);
        for(i = 0; i < num_args + 1; i++)
        {
            ci_write(EV_KEY, va_arg(keylist, int), 1);
        }
    va_end(keylist);

    ci_write(EV_SYN, SYN_REPORT, 0);
    
    va_start(keylist, num_args);
        for(i = 0; i < num_args + 1; i++)
        {
            ci_write(EV_KEY, va_arg(keylist, int), 0);
        }
    va_end(keylist);

    ci_write(EV_SYN, SYN_REPORT, 0);
}


void ci_write(int type, int code, int value)
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
                printf("No enough permissions to write to uinput.\n");
                exit(1);
            }

    return fd;
}


int fd_initialize()
{
    /* This function is used for initialization, it is called internally
    by initialization() */
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

void ask_for_password()
{
    /* This function asks for root password and changes
    mode of uinput */
    if (access("/dev/input/uinput", F_OK) == 0)
        system("su -c \"chmod +0666 /dev/input/uinput\"");
    if (access("/dev/uinput", F_OK) == 0)
        system("su -c \"chmod +0666 /dev/uinput\"");
    if (access("/dev/misc/uinput", F_OK) == 0)
        system("su -c \"chmod +0666 /dev/misc/uinput\"");
}

void check_permissions()
{
    /* If there are not enough permissions to write to uinput,
    this function calls ask_for_password() */
    if (access("/dev/input/uinput", W_OK) == -1)
        if (access("/dev/uinput", W_OK) == -1)
            if (access("/dev/misc/uinput", W_OK) == -1)
                ask_for_password();
}


void error(char *error_code)
{
    perror(error_code);
    exit(1);
}

/* keylist from linux/uinput.h

#define KEY_RESERVED                    0
#define KEY_ESC                         1
#define KEY_1                           2
#define KEY_2                           3
#define KEY_3                           4
#define KEY_4                           5
#define KEY_5                           6
#define KEY_6                           7
#define KEY_7                           8
#define KEY_8                           9
#define KEY_9                           10
#define KEY_0                           11
#define KEY_MINUS                       12
#define KEY_EQUAL                       13
#define KEY_BACKSPACE                   14
#define KEY_TAB                         15
#define KEY_Q                           16
#define KEY_W                           17
#define KEY_E                           18
#define KEY_R                           19
#define KEY_T                           20
#define KEY_Y                           21
#define KEY_U                           22
#define KEY_I                           23
#define KEY_O                           24
#define KEY_P                           25
#define KEY_LEFTBRACE                   26
#define KEY_RIGHTBRACE                  27
#define KEY_ENTER                       28
#define KEY_LEFTCTRL                    29
#define KEY_A                           30
#define KEY_S                           31
#define KEY_D                           32
#define KEY_F                           33
#define KEY_G                           34
#define KEY_H                           35
#define KEY_J                           36
#define KEY_K                           37
#define KEY_L                           38
#define KEY_SEMICOLON                   39
#define KEY_APOSTROPHE                  40
#define KEY_GRAVE                       41
#define KEY_LEFTSHIFT                   42
#define KEY_BACKSLASH                   43
#define KEY_Z                           44
#define KEY_X                           45
#define KEY_C                           46
#define KEY_V                           47
#define KEY_B                           48
#define KEY_N                           49
#define KEY_M                           50
#define KEY_COMMA                       51
#define KEY_DOT                         52
#define KEY_SLASH                       53
#define KEY_RIGHTSHIFT                  54
#define KEY_KPASTERISK                  55
#define KEY_LEFTALT                     56
#define KEY_SPACE                       57
#define KEY_CAPSLOCK                    58
#define KEY_F1                          59
#define KEY_F2                          60
#define KEY_F3                          61
#define KEY_F4                          62
#define KEY_F5                          63
#define KEY_F6                          64
#define KEY_F7                          65
#define KEY_F8                          66
#define KEY_F9                          67
#define KEY_F10                         68
#define KEY_NUMLOCK                     69
#define KEY_SCROLLLOCK                  70
#define KEY_KP7                         71
#define KEY_KP8                         72
#define KEY_KP9                         73
#define KEY_KPMINUS                     74
#define KEY_KP4                         75
#define KEY_KP5                         76
#define KEY_KP6                         77
#define KEY_KPPLUS                      78
#define KEY_KP1                         79
#define KEY_KP2                         80
#define KEY_KP3                         81
#define KEY_KP0                         82
#define KEY_KPDOT                       83
#define KEY_ZENKAKUHANKAKU              85
#define KEY_102ND                       86
#define KEY_F11                         87
#define KEY_F12                         88
#define KEY_RO                          89
#define KEY_KATAKANA                    90
#define KEY_HIRAGANA                    91
#define KEY_HENKAN                      92
#define KEY_KATAKANAHIRAGANA            93
#define KEY_MUHENKAN                    94
#define KEY_KPJPCOMMA                   95
#define KEY_KPENTER                     96
#define KEY_RIGHTCTRL                   97
#define KEY_KPSLASH                     98
#define KEY_SYSRQ                       99
#define KEY_RIGHTALT                    100
#define KEY_LINEFEED                    101
#define KEY_HOME                        102
#define KEY_UP                          103
#define KEY_PAGEUP                      104
#define KEY_LEFT                        105
#define KEY_RIGHT                       106
#define KEY_END                         107
#define KEY_DOWN                        108
#define KEY_PAGEDOWN                    109
#define KEY_INSERT                      110
#define KEY_DELETE                      111
#define KEY_MACRO                       112
#define KEY_MUTE                        113
#define KEY_VOLUMEDOWN                  114
#define KEY_VOLUMEUP                    115
#define KEY_POWER                       116
#define KEY_KPEQUAL                     117
#define KEY_KPPLUSMINUS                 118
#define KEY_PAUSE                       119
#define KEY_SCALE                       120
#define KEY_KPCOMMA                     121
#define KEY_HANGEUL                     122
#define KEY_HANGUEL                     KEY_HANGEUL
#define KEY_HANJA                       123
#define KEY_YEN                         124
#define KEY_LEFTMETA                    125
#define KEY_RIGHTMETA                   126
#define KEY_COMPOSE                     127
#define KEY_STOP                        128
#define KEY_AGAIN                       129
#define KEY_PROPS                       130       
#define KEY_UNDO                        131        
#define KEY_FRONT                       132
#define KEY_COPY                        133      
#define KEY_OPEN                        134 
#define KEY_PASTE                       135 
#define KEY_FIND                        136  
#define KEY_CUT                         137    
#define KEY_HELP                        138 
#define KEY_MENU                        139      
#define KEY_CALC                        140 
#define KEY_SETUP                       141
#define KEY_SLEEP                       142     
#define KEY_WAKEUP                      143 
#define KEY_FILE                        144
#define KEY_SENDFILE                    145
#define KEY_DELETEFILE                  146
#define KEY_XFER                        147
#define KEY_PROG1                       148
#define KEY_PROG2                       149
#define KEY_WWW                         150
#define KEY_MSDOS                       151
#define KEY_COFFEE                      152
#define KEY_SCREENLOCK                  KEY_COFFEE
#define KEY_DIRECTION                   153
#define KEY_CYCLEWINDOWS                154
#define KEY_MAIL                        155
#define KEY_BOOKMARKS                   156 
#define KEY_COMPUTER                    157
#define KEY_BACK                        158
#define KEY_FORWARD                     159
#define KEY_CLOSECD                     160
#define KEY_EJECTCD                     161
#define KEY_EJECTCLOSECD                162
#define KEY_NEXTSONG                    163
#define KEY_PLAYPAUSE                   164
#define KEY_PREVIOUSSONG                165
#define KEY_STOPCD                      166
#define KEY_RECORD                      167
#define KEY_REWIND                      168
#define KEY_PHONE                       169
#define KEY_ISO                         170
#define KEY_CONFIG                      171
#define KEY_HOMEPAGE                    172
#define KEY_REFRESH                     173
#define KEY_EXIT                        174
#define KEY_MOVE                        175
#define KEY_EDIT                        176
#define KEY_SCROLLUP                    177
#define KEY_SCROLLDOWN                  178
#define KEY_KPLEFTPAREN                 179
#define KEY_KPRIGHTPAREN                180
#define KEY_NEW                         181
#define KEY_REDO                        182
#define KEY_F13                         183
#define KEY_F14                         184
#define KEY_F15                         185
#define KEY_F16                         186
#define KEY_F17                         187
#define KEY_F18                         188
#define KEY_F19                         189
#define KEY_F20                         190
#define KEY_F21                         191
#define KEY_F22                         192
#define KEY_F23                         193
#define KEY_F24                         194
#define KEY_PLAYCD                      200
#define KEY_PAUSECD                     201
#define KEY_PROG3                       202
#define KEY_PROG4                       203
#define KEY_DASHBOARD                   204 
#define KEY_SUSPEND                     205
#define KEY_CLOSE                       206       
#define KEY_PLAY                        207
#define KEY_FASTFORWARD                 208
#define KEY_BASSBOOST                   209
#define KEY_PRINT                       210 
#define KEY_HP                          211
#define KEY_CAMERA                      212
#define KEY_SOUND                       213
#define KEY_QUESTION                    214
#define KEY_EMAIL                       215
#define KEY_CHAT                        216
#define KEY_SEARCH                      217
#define KEY_CONNECT                     218
#define KEY_FINANCE                     219
#define KEY_SPORT                       220
#define KEY_SHOP                        221
#define KEY_ALTERASE                    222
#define KEY_CANCEL                      223 
#define KEY_BRIGHTNESSDOWN              224
#define KEY_BRIGHTNESSUP                225
#define KEY_MEDIA                       226
#define KEY_SWITCHVIDEOMODE             227 
#define KEY_KBDILLUMTOGGLE              228
#define KEY_KBDILLUMDOWN                229
#define KEY_KBDILLUMUP                  230
#define KEY_SEND                        231
#define KEY_REPLY                       232
#define KEY_FORWARDMAIL                 233
#define KEY_SAVE                        234
#define KEY_DOCUMENTS                   235
#define KEY_BATTERY                     236
#define KEY_BLUETOOTH                   237
#define KEY_WLAN                        238
#define KEY_UWB                         239
#define KEY_UNKNOWN                     240
#define KEY_VIDEO_NEXT                  241
#define KEY_VIDEO_PREV                  242
#define KEY_BRIGHTNESS_CYCLE            243
#define KEY_BRIGHTNESS_ZERO             244
#define KEY_DISPLAY_OFF                 245
#define KEY_WIMAX                       246
#define KEY_RFKILL                      247
#define KEY_MICMUTE                     248
*/
