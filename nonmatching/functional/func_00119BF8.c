/* functional: medium. vfprintf (integer-only newlib engine, ap in 8-byte slots): flags - + # 0 space, width and precision (also from '*'), h l ll q, conversions c d i D u U o O x X p s n and the literal fallback; output goes to the stream buffer (memcpy when fp->_flags has 0x200) or through func_00119AC0 on fp->_file. Reconstructed from the assembly and the jump table at 0x13A7B0; no floating-point cases exist in retail. */
extern int D_00133E74;
extern int D_00133B80;
extern char D_0013A730[];
extern char D_0013A740[];
extern char D_0013A750[];
extern char D_0013A768[];
extern char D_0013A770[];
extern char D_0013A788[];

extern int func_00115FC0(int reent, int *wc, char *s, int n, int *state);
extern void func_001153D4(char *dst, char *src, int n);
extern void func_00119AC0(int fd, char *buf, int n, int flag);
extern char *func_00115250(char *s, int c, int n);
extern int func_001157AC(char *s);
extern unsigned long long func_001220F0(unsigned long long a, unsigned long long b);
extern unsigned long long func_00121B20(unsigned long long a, unsigned long long b);

#define FP_P(fp)     (*(char **)(fp))
#define FP_FLAGS(fp) (*(unsigned short *)((fp) + 0xC))
#define FP_WORD(fp)  (*(int *)((fp) + 0xC))
#define FP_FILE(fp)  (*(short *)((fp) + 0xE))

#define PRINT(src, len)                                         \
    do {                                                        \
        if (FP_FLAGS(fp) & 0x200) {                             \
            func_001153D4(FP_P(fp), (src), (len));              \
            FP_P(fp) = FP_P(fp) + (len);                        \
        } else {                                                \
            if (FP_WORD(fp) == 0)                               \
                FP_FILE(fp) = 1;                                \
            func_00119AC0(FP_FILE(fp), (src), (len), 0);        \
        }                                                       \
    } while (0)

#define PAD(count, with)                                        \
    do {                                                        \
        int pn_ = (count);                                      \
        if (pn_ > 0) {                                          \
            while (pn_ > 16) {                                  \
                PRINT((with), 16);                              \
                pn_ -= 16;                                      \
            }                                                   \
            PRINT((with), pn_);                                 \
        }                                                       \
    } while (0)

int func_00119BF8(int reent, unsigned char *fp, char *fmt, long *ap)
{
    struct { int wc; int state; int ret; } st;
    char buf[0x28];
    char ox[2];
    char sign;
    char *cp, *start;
    char *xdigs = 0;
    int ch, n, m, flags, width, prec, dprec, size, realsz, base, fld, pn;
    int ladj, zp;
    unsigned long long u;

    st.state = 0;
    st.ret = 0;
    for (;;) {
        start = fmt;
        while ((n = func_00115FC0(D_00133E74, &st.wc, fmt, D_00133B80, &st.state)) > 0) {
            fmt += n;
            if (st.wc == '%') {
                fmt -= 1;
                break;
            }
        }
        m = fmt - start;
        if (m != 0) {
            PRINT(start, m);
            st.ret += m;
        }
        if (n <= 0)
            goto done;
        fmt++;

        sign = 0;
        dprec = 0;
        flags = 0;
        width = 0;
        prec = -1;
    rflag:
        ch = *fmt++;
    reswitch:
        if ((unsigned)(ch - 0x20) >= 0x59)
            goto dflt;
        switch (ch) {
        case ' ':
            if (sign == 0)
                sign = ' ';
            goto rflag;
        case '#':
            flags |= 1;
            goto rflag;
        case '*':
            ap++;
            width = (int)ap[-1];
            if (width >= 0)
                goto rflag;
            width = -width;
            flags |= 4;
            goto rflag;
        case '+':
            sign = '+';
            goto rflag;
        case '-':
            flags |= 4;
            goto rflag;
        case '.':
            ch = *fmt++;
            if (ch == '*') {
                ap++;
                n = (int)ap[-1];
                prec = (n > -2) ? n : -1;
                goto rflag;
            }
            n = 0;
            while ((unsigned)(ch - '0') < 10) {
                n = n * 10 + ch - '0';
                ch = *fmt++;
            }
            prec = (n > -2) ? n : -1;
            goto reswitch;
        case '0':
            flags |= 0x80;
            goto rflag;
        case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9':
            n = 0;
            do {
                n = n * 10 + ch - '0';
                ch = *fmt++;
            } while ((unsigned)(ch - '0') < 10);
            width = n;
            goto reswitch;
        case 'h':
            flags |= 0x40;
            goto rflag;
        case 'l':
            if (*fmt == 'l') {
                fmt++;
                flags |= 0x20;
            } else {
                flags |= 0x10;
            }
            goto rflag;
        case 'q':
            flags |= 0x20;
            goto rflag;
        case 'c':
            ap++;
            buf[0] = (char)ap[-1];
            cp = buf;
            size = 1;
            sign = 0;
            goto have_string;
        case 'D':
            flags |= 0x10;
            /* fall through */
        case 'd':
        case 'i':
            ap++;
            if (flags & 0x20)
                u = (unsigned long long)*(long long *)(ap - 1);
            else if (flags & 0x10)
                u = (unsigned long long)*(long long *)(ap - 1);
            else if (flags & 0x40)
                u = (unsigned long long)(long long)*(short *)(ap - 1);
            else
                u = (unsigned long long)(long long)*(int *)(ap - 1);
            if ((long long)u < 0) {
                u = -(long long)u;
                sign = '-';
            }
            base = 1;
            goto number;
        case 'n':
            ap++;
            if (flags & 0x20)
                *(long long *)(int)ap[-1] = st.ret;
            else if (flags & 0x10)
                *(long long *)(int)ap[-1] = st.ret;
            else if (flags & 0x40)
                *(short *)(int)ap[-1] = st.ret;
            else
                *(int *)(int)ap[-1] = st.ret;
            continue;
        case 'O':
            flags |= 0x10;
            /* fall through */
        case 'o':
            ap++;
            if (flags & 0x20)
                u = *(unsigned long long *)(ap - 1);
            else if (flags & 0x10)
                u = *(unsigned long long *)(ap - 1);
            else if (flags & 0x40)
                u = *(unsigned short *)(ap - 1);
            else
                u = *(unsigned int *)(ap - 1);
            base = 0;
            goto nosign;
        case 'p':
            ap++;
            xdigs = D_0013A750;
            base = 2;
            flags |= 2;
            ch = 'x';
            u = (unsigned long long)(long long)*(int *)(ap - 1);
            goto nosign;
        case 's':
            ap++;
            cp = (char *)(int)ap[-1];
            if (cp == 0)
                cp = D_0013A768;
            if (prec >= 0) {
                char *e = func_00115250(cp, 0, prec);
                if (e != 0) {
                    size = e - cp;
                    if (prec < size)
                        size = prec;
                } else {
                    size = prec;
                }
            } else {
                size = func_001157AC(cp);
            }
            sign = 0;
            goto have_string;
        case 'U':
            flags |= 0x10;
            /* fall through */
        case 'u':
            ap++;
            if (flags & 0x20)
                u = *(unsigned long long *)(ap - 1);
            else if (flags & 0x10)
                u = *(unsigned long long *)(ap - 1);
            else if (flags & 0x40)
                u = *(unsigned short *)(ap - 1);
            else
                u = *(unsigned int *)(ap - 1);
            base = 1;
            goto nosign;
        case 'X':
            xdigs = D_0013A770;
            goto hex;
        case 'x':
            xdigs = D_0013A750;
        hex:
            ap++;
            if (flags & 0x20)
                u = *(unsigned long long *)(ap - 1);
            else if (flags & 0x10)
                u = *(unsigned long long *)(ap - 1);
            else if (flags & 0x40)
                u = *(unsigned short *)(ap - 1);
            else
                u = *(unsigned int *)(ap - 1);
            if ((flags & 1) && u != 0)
                flags |= 2;
            base = 2;
            goto nosign;
        default:
        dflt:
            if (ch == 0)
                goto done;
            buf[0] = (char)ch;
            cp = buf;
            sign = 0;
            size = 1;
            goto have_string;
        }

    nosign:
        sign = 0;
    number:
        dprec = prec;
        if (prec >= 0)
            flags &= ~0x80;
        cp = buf + 0x28;
        if (u == 0 && prec == 0) {
            size = (buf + 0x28) - cp;
            goto have_size;
        }
        if (base == 1) {
            if (u < 10) {
                *--cp = (char)(u + '0');
            } else {
                do {
                    *--cp = (char)(func_001220F0(u, 10) + '0');
                    u = func_00121B20(u, 10);
                } while (u >= 10);
                *--cp = (char)(u + '0');
            }
            size = (buf + 0x28) - cp;
            goto have_size;
        }
        if (base == 0) {
            char last;
            do {
                last = (char)((u & 7) + '0');
                *--cp = last;
                u >>= 3;
            } while (u != 0);
            if ((flags & 1) && last != '0')
                *--cp = '0';
            size = (buf + 0x28) - cp;
            goto have_size;
        }
        if (base == 2) {
            do {
                *--cp = xdigs[(int)(u & 0xF)];
                u >>= 4;
            } while (u != 0);
            size = (buf + 0x28) - cp;
            goto have_size;
        }
        cp = D_0013A788;
        size = func_001157AC(cp);
        goto have_size;

    have_string:
    have_size:
        realsz = (size < dprec) ? dprec : size;
        if (sign != 0)
            realsz++;
        else
            realsz += (flags & 2);
        ladj = flags & 4;
        zp = flags & 0x84;
        pn = dprec - size;
        if (zp == 0)
            PAD(width - realsz, D_0013A730);
        if (sign != 0) {
            PRINT(&sign, 1);
        } else if (flags & 2) {
            ox[0] = '0';
            ox[1] = (char)ch;
            PRINT(ox, 2);
        }
        if (zp == 0x80)
            PAD(width - realsz, D_0013A740);
        PAD(pn, D_0013A740);
        PRINT(cp, size);
        if (ladj)
            PAD(width - realsz, D_0013A730);
        st.ret += (realsz < width) ? width : realsz;
    }
done:
    if (!(FP_FLAGS(fp) & 0x200))
        func_00119AC0(FP_FILE(fp), 0, 0, 1);
    return st.ret;
}
