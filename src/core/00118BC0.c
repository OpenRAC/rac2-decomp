#include "common.h"

/* Buffered tty write: bytes are staged in a 128-byte buffer and written
   through func_0011B1E8 (the Deci2 tty write) whenever it fills, or at once
   when FLUSH is 1. */
extern char D_0013C100[];

extern int D_00134668;

extern char *D_0013466C;

extern int func_0011B1E8(int fd, char *buf, int len);

/* Appends len bytes of src to a 128-byte staging buffer and writes it to fd with func_0011B1E8
   whenever it fills; flush == 1 writes out what is pending. */
int func_00118BC0(int fd, char *src, unsigned int len, int flush) {
    unsigned int i;
    int r;

    if (flush == 1) {
        r = func_0011B1E8(fd, D_0013C100, D_00134668);
        D_00134668 = 0;
        D_0013466C = D_0013C100;
        return r;
    }
    for (i = 0; i < len; i++) {
        *D_0013466C = src[i];
        D_0013466C++;
        D_00134668++;
        if (D_00134668 >= 0x80) {
            r = func_0011B1E8(fd, D_0013C100, D_00134668);
            D_0013466C = D_0013C100;
            D_00134668 = 0;
            if (r == 0)
                return 0;
        }
    }
    return i;
}
