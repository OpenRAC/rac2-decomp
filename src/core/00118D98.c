#include "common.h"

/* Float-capable formatter reconstructed from retail control flow and the
 * public newlib 1999 implementation in RAC1 src/core/00116FA0.c.
 * The direct string/stream output replaces newlib's iovec PRINT macro.
 *
 * The last five spill slots follow PRE's reaching registers, numbered in hash
 * bucket order, bucket = hash % ((insns at gcse / 2) | 1): dprec - size,
 * realsz < width, flags & 4, &wc, &state. The per-conversion block raises the
 * regnos of the first two, RAC1's unused locals place that block's regnos, and
 * the done test's cast sets the table size to 427.
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

extern void func_00115228(void);
extern double func_001182B8(double);
extern char *func_001185E8(double, int, char, int);

extern void *D_00133E74 NOT_SDA;
extern int D_00133B80 NOT_SDA;
extern const char D_0013A540[];
extern const char D_0013A550[];
extern char D_0013A560[];
extern char D_0013A578[];
extern char D_0013A580[];
extern char D_0013A598[];
extern int func_00115FC0(void *, int *, const char *, unsigned int, int *);
extern int func_00118BC0(int, const char *, unsigned int, int);
extern void *memcpy(void *, const void *, unsigned int) __asm__("func_001153D4");
extern void *memchr(const void *, int, unsigned int) __asm__("func_00115250");
extern unsigned int strlen(const char *) __asm__("func_001157AC");

#define PRINT(ptr, len) { \
    if (fp->status.fields.flags & 0x200) { \
        __builtin_memcpy(fp->cursor, (ptr), (len)); \
        fp->cursor += (len); \
    } else { \
        if (fp->status.word == 0) fp->status.fields.file = 1; \
        BufferedWrite128(fp->status.fields.file, (ptr), (len), 0); \
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

/* Prints text from a format string, including decimal numbers. */
int func_00118D98(void *data, PrintFile *fp, const char *fmt0, char *ap)
{
    register char *fmt;
    register int ch;
    register int n, m;
    register char *cp;
    register int flags;
    int ret;
    int prec;
    char sign;
    int wc;
    char *decimal_point; /* unused, as RAC1 */
    char softsign;       /* unused, as RAC1 */
    double fvalue;
    double exponent;
    int dot;
    int expt;            /* unused, as RAC1 */
    int expsize;         /* unused, as RAC1 */
    int ndig;            /* unused, as RAC1 */
    char expstr[7];      /* unused, as RAC1: places buf at sp+0x10 */
    u64 value;
    enum { OCT, DEC, HEX } base;
    char buf[348];
    char ox[2];
    int state;

    InitLibraryStdioState();
    state = 0;
    fmt = (char *)fmt0;
    ret = 0;
    for (;;) {
        cp = fmt;
        while ((n = MultibyteToWideCharReentrant(D_00133E74, &wc, fmt, D_00133B80, &state)) > 0) {
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
        {
            int width;
            int realsz;
            int dprec;
            int size;
            char *xdigs;
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
            case 'L':
                flags |= 0x008;
                goto rflag;
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
            case 'E': case 'G': case 'e': case 'f': case 'g': {
                dot = 0;
                if (prec == -1) prec = 6;
                fvalue = GET(double);
                if (ch == 'g' || ch == 'G') {
                    if (fvalue != 0.0) {
                        double magnitude = fvalue;
                        if (fvalue < 0.0) magnitude = -fvalue;
                        exponent = __ieee754_log10(magnitude);
                    } else exponent = 1.0;
                    if (exponent < -4.0 || exponent >= prec)
                        ch = ch == 'g' ? 'e' : 'E';
                    else ch = 'f';
                    dot = 1;
                }
                if (flags & 1) {
                    dot = 0;
                    if (prec == 0) prec = 1;
                }
                cp = FormatFloatDigits(fvalue, prec, ch, dot);
                size = strlen(cp);
                break;
            }
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
                xdigs = D_0013A560;
                flags |= 0x002;
                ch = 'x';
                goto nosign;
            case 's':
                if ((cp = GET(char *)) == 0) cp = D_0013A578;
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
                xdigs = D_0013A580;
                goto hex;
            case 'x':
                xdigs = D_0013A560;
            hex:
                value = UARG();
                base = HEX;
                if (flags & 0x001 && value != 0) flags |= 0x002;
            nosign:
                sign = '\0';
            number:
                if ((dprec = prec) >= 0) flags &= ~0x080;
                cp = buf + 348;
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
                        cp = D_0013A598;
                        size = strlen(cp);
                        goto skipsize;
                    }
                }
                size = buf + 348 - cp;
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
            realsz = dprec > size ? dprec : size;
            if (sign) realsz++;
            else if (flags & 0x002) realsz += 2;
            if ((flags & 0x084) == 0) PAD(width - realsz, D_0013A540);
            if (sign) {
                PRINT(&sign, 1);
            } else if (flags & 0x002) {
                ox[0] = '0';
                ox[1] = ch;
                PRINT(ox, 2);
            }
            if ((flags & 0x084) == 0x080) PAD(width - realsz, D_0013A550);
            PAD(dprec - size, D_0013A550);
            PRINT(cp, size);
            if (flags & 0x004) PAD(width - realsz, D_0013A540);
            ret += width > realsz ? width : realsz;
        }
    }
 done:
    if (!((unsigned short)fp->status.fields.flags & 0x200))
        BufferedWrite128(fp->status.fields.file, 0, 0, 1);
    return ret;
}
