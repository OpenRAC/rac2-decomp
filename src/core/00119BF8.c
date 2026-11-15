#include "common.h"

/* Integer-only formatter reconstructed from retail control flow and the
 * public newlib 1999 implementation in RAC1 src/core/00116FA0.c.
 * The direct string/stream output replaces newlib's iovec PRINT macro.
 * realsz lives in the block that uses it: gcse numbers its PRE registers by
 * hash bucket, and a bucket sums the regnos, so its regno sets the spill slots
 * of flags & 4 (sp+0x6C) and width > realsz (sp+0x70).
 */
typedef struct {
    unsigned char *cursor;
    int read_count;
    int write_count;
    union {
        int word;
        struct { short flags; short file; } fields;
    } status;
} PrintFile;

extern void *D_00133E74;
extern int D_00133B80;
extern const char D_0013A730[];
extern const char D_0013A740[];
extern char D_0013A750[];
extern char D_0013A768[];
extern char D_0013A770[];
extern char D_0013A788[];
extern int func_00115FC0(void *, int *, const char *, unsigned int, int *);
extern int func_00119AC0(int, const char *, unsigned int, int);
extern void *memcpy(void *, const void *, unsigned int) __asm__("func_001153D4");
extern void *memchr(const void *, int, unsigned int) __asm__("func_00115250");
extern unsigned int strlen(const char *) __asm__("func_001157AC");

#define PRINT(ptr, len) { \
    if (fp->status.fields.flags & 0x200) { \
        __builtin_memcpy(fp->cursor, (ptr), (len)); \
        fp->cursor += (len); \
    } else { \
        if (fp->status.word == 0) fp->status.fields.file = 1; \
        BufferedWrite128Secondary(fp->status.fields.file, (ptr), (len), 0); \
    } \
}
#define PAD(howmany, with) { \
    if ((n = (howmany)) > 0) { \
        while (n > 16) { PRINT((with), 16); n -= 16; } \
        PRINT((with), n); \
    } \
}
#define GET(type) (*(type *)((ap += 8) - 8))
#define SARG() (flags & 0x20 ? GET(long long) : flags & 0x10 ? GET(long) : flags & 0x40 ? (long)(short)GET(int) : (long)GET(int))
#define UARG() (flags & 0x20 ? GET(unsigned long long) : flags & 0x10 ? GET(unsigned long) : flags & 0x40 ? (unsigned long)(unsigned short)GET(int) : (unsigned long)GET(unsigned int))

/* Formatted-output core without floating-point conversions: formats fmt with the arguments at
   ap into the stream fp. */
int func_00119BF8(void *data, PrintFile *fp, const char *fmt0, char *ap)
{
    register char *fmt;
    register int ch;
    register int n, m;
    register char *cp;
    register int flags;
    int ret;
    int width;
    int prec;
    char sign;
    int wc;
    u64 value;
    enum { OCT, DEC, HEX } base;
    int dprec;
    int size;
    char *xdigs;
    int *wide_char;
    int *mbstate;
    char buf[40];
    char ox[2];
    int state = 0;

    fmt = (char *)fmt0;
    ret = 0;
    wide_char = &wc;
    mbstate = &state;
    for (;;) {
        cp = fmt;
        while ((n = MultibyteToWideCharReentrant(D_00133E74, wide_char, fmt, D_00133B80, mbstate)) > 0) {
            fmt += n;
            if (wc == '%') {
                fmt--;
                break;
            }
        }
        if ((m = fmt - cp) != 0) {
            PRINT(cp, m);
            ret += m;
        }
        if (n <= 0)
            goto done;
        fmt++;
        flags = 0;
        dprec = 0;
        width = 0;
        prec = -1;
        sign = '\0';
    rflag:
        ch = *fmt++;
    reswitch:
        switch (ch) {
        case ' ':
            if (!sign) sign = ' ';
            goto rflag;
        case '#':
            flags |= 0x001;
            goto rflag;
        case '*':
            if ((width = GET(int)) >= 0) goto rflag;
            width = -width;
        case '-':
            flags |= 0x004;
            goto rflag;
        case '+':
            sign = '+';
            goto rflag;
        case '.':
            if ((ch = *fmt++) == '*') {
                n = GET(int);
                prec = n < 0 ? -1 : n;
                goto rflag;
            }
            n = 0;
            while ((unsigned)(ch - '0') <= 9) {
                n = 10 * n + (ch - '0');
                ch = *fmt++;
            }
            prec = n < 0 ? -1 : n;
            goto reswitch;
        case '0':
            flags |= 0x080;
            goto rflag;
        case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9':
            n = 0;
            do {
                n = 10 * n + (ch - '0');
                ch = *fmt++;
            } while ((unsigned)(ch - '0') <= 9);
            width = n;
            goto reswitch;
        case 'h':
            flags |= 0x040;
            goto rflag;
        case 'l':
            if (*fmt == 'l') {
                fmt++;
                flags |= 0x020;
            } else {
                flags |= 0x010;
            }
            goto rflag;
        case 'q':
            flags |= 0x020;
            goto rflag;
        case 'c':
            *(cp = buf) = GET(int);
            size = 1;
            sign = '\0';
            break;
        case 'D':
            flags |= 0x010;
        case 'd': case 'i':
            value = SARG();
            if ((s64)value < 0) {
                value = -value;
                sign = '-';
            }
            base = DEC;
            goto number;
        case 'n':
            if (flags & 0x020) *GET(long long *) = ret;
            else if (flags & 0x010) *GET(long *) = ret;
            else if (flags & 0x040) *GET(short *) = ret;
            else *GET(int *) = ret;
            continue;
        case 'O':
            flags |= 0x010;
        case 'o':
            value = UARG();
            base = OCT;
            goto nosign;
        case 'p':
            value = (s64)(int)GET(void *);
            base = HEX;
            xdigs = D_0013A750;
            flags |= 0x002;
            ch = 'x';
            goto nosign;
        case 's':
            if ((cp = GET(char *)) == 0) cp = D_0013A768;
            if (prec >= 0) {
                char *p = memchr(cp, 0, prec);
                if (p != 0) {
                    size = p - cp;
                    if (size > prec) size = prec;
                } else size = prec;
            } else size = strlen(cp);
            sign = '\0';
            break;
        case 'U':
            flags |= 0x010;
        case 'u':
            value = UARG();
            base = DEC;
            goto nosign;
        case 'X':
            xdigs = D_0013A770;
            goto hex;
        case 'x':
            xdigs = D_0013A750;
        hex:
            value = UARG();
            base = HEX;
            if (flags & 0x001 && value != 0) flags |= 0x002;
        nosign:
            sign = '\0';
        number:
            if ((dprec = prec) >= 0) flags &= ~0x080;
            cp = buf + 40;
            if (value != 0 || prec != 0) {
                switch (base) {
                case OCT:
                    do {
                        *--cp = (value & 7) + '0';
                        value >>= 3;
                    } while (value);
                    if (flags & 0x001 && *cp != '0') *--cp = '0';
                    break;
                case DEC:
                    while (value >= 10) {
                        *--cp = (value % 10) + '0';
                        value /= 10;
                    }
                    *--cp = value + '0';
                    break;
                case HEX:
                    do {
                        *--cp = xdigs[value & 15];
                        value >>= 4;
                    } while (value);
                    break;
                default:
                    cp = D_0013A788;
                    size = strlen(cp);
                    goto skipsize;
                }
            }
            size = buf + 40 - cp;
        skipsize:
            break;
        default:
            if (ch == '\0') goto done;
            cp = buf;
            *cp = ch;
            size = 1;
            sign = '\0';
            break;
        }
        {
            int realsz = dprec > size ? dprec : size;
            if (sign) realsz++;
            else if (flags & 0x002) realsz += 2;
            if ((flags & 0x084) == 0) PAD(width - realsz, D_0013A730);
            if (sign) {
                PRINT(&sign, 1);
            } else if (flags & 0x002) {
                ox[0] = '0';
                ox[1] = ch;
                PRINT(ox, 2);
            }
            if ((flags & 0x084) == 0x080) PAD(width - realsz, D_0013A740);
            PAD(dprec - size, D_0013A740);
            PRINT(cp, size);
            if (flags & 0x004) PAD(width - realsz, D_0013A730);
            ret += width > realsz ? width : realsz;
        }
    }
 done:
    if (!(fp->status.fields.flags & 0x200))
        BufferedWrite128Secondary(fp->status.fields.file, 0, 0, 1);
    return ret;
}
