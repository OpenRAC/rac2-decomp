#include "common.h"

/* Buffered tty write: bytes are staged in a 128-byte buffer and written
   through func_0011B1E8 (the Deci2 tty write) whenever it fills, or at once
   when FLUSH is 1. */
extern char D_0013C180[];

extern int D_00134670;

extern char *D_00134674;

extern int func_0011B1E8(int fd, char *buf, int len);

/* Collects printed bytes in a second small buffer and sends them out when it is full or on request. */
int func_00119AC0(int fd, char *src, unsigned int len, int flush) {
    unsigned int i;
    int r;

    if (flush == 1) {
        r = WriteTtyViaDeci2(fd, D_0013C180, D_00134670);
        D_00134670 = 0;
        D_00134674 = D_0013C180;
        return r;
    }
    for (i = 0; i < len; i++) {
        *D_00134674 = src[i];
        D_00134674++;
        D_00134670++;
        if (D_00134670 >= 0x80) {
            r = WriteTtyViaDeci2(fd, D_0013C180, D_00134670);
            D_00134674 = D_0013C180;
            D_00134670 = 0;
            if (r == 0)
                return 0;
        }
    }
    return i;
}
