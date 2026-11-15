#include "common.h"

/* Buffered tty write: bytes are staged in a 128-byte buffer and written
   through func_0011B1E8 (the Deci2 tty write) whenever it fills, or at once
   when FLUSH is 1. */
extern char D_0013C100[];

extern int D_00134668;

extern char *D_0013466C;

extern int tty_write_via_deci2(int fd, char *buf, int len);

/* Collects printed bytes in a small buffer and sends them out when it is full or on request. */
int BufferedWrite128(int fd, char *src, unsigned int len, int flush) {
    unsigned int i;
    int r;

    if (flush == 1) {
        r = tty_write_via_deci2(fd, D_0013C100, D_00134668);
        D_00134668 = 0;
        D_0013466C = D_0013C100;
        return r;
    }
    for (i = 0; i < len; i++) {
        *D_0013466C = src[i];
        D_0013466C++;
        D_00134668++;
        if (D_00134668 >= 0x80) {
            r = tty_write_via_deci2(fd, D_0013C100, D_00134668);
            D_0013466C = D_0013C100;
            D_00134668 = 0;
            if (r == 0)
                return 0;
        }
    }
    return i;
}
