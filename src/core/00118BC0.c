#include "common.h"

/* Buffered tty write: bytes are staged in a 128-byte buffer and written
   through func_0011B1E8 (the Deci2 tty write) whenever it fills, or at once
   when FLUSH is 1. */
extern char g_tty_write_buffer_a[];

extern int g_stdout_buffer_len;

extern char *g_stdout_buffer_cursor;

extern int tty_write_via_deci2(int fd, char *buf, int len);

/* Collects printed bytes in a small buffer and sends them out when it is full or on request. */
int BufferedWrite128(int fd, char *src, unsigned int len, int flush) {
    unsigned int i;
    int r;

    if (flush == 1) {
        r = tty_write_via_deci2(fd, g_tty_write_buffer_a, g_stdout_buffer_len);
        g_stdout_buffer_len = 0;
        g_stdout_buffer_cursor = g_tty_write_buffer_a;
        return r;
    }
    for (i = 0; i < len; i++) {
        *g_stdout_buffer_cursor = src[i];
        g_stdout_buffer_cursor++;
        g_stdout_buffer_len++;
        if (g_stdout_buffer_len >= 0x80) {
            r = tty_write_via_deci2(fd, g_tty_write_buffer_a, g_stdout_buffer_len);
            g_stdout_buffer_cursor = g_tty_write_buffer_a;
            g_stdout_buffer_len = 0;
            if (r == 0)
                return 0;
        }
    }
    return i;
}
