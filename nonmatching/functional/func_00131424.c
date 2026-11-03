/* functional: medium. newlib's sqrt() wrapper (fdlibm w_sqrt.c, double, soft-float), written from the assembly at 0x131430 (the catalogue's func_00131424 starts 12 bytes early on padding: 0xCDCDCDCD fill and a stray word). Same calls and stores as retail; the x < 0 test is retail's libgcc compare (func_00123028) written as C; fixes against the near miss: func_001310C0 is passed x (retail leaves it in $a0), and _POSIX_ (2) sets errno directly instead of skipping it. */
typedef struct {
    int type;                      /* 1: DOMAIN */
    char *name;
    double arg1;
    double arg2;
    double retval;
    int err;
} MathException_00131424;

extern double func_001310C0(double);      /* __ieee754_sqrt */
extern int func_001313C8(double);         /* isnan */
extern int func_00131400(void *);         /* matherr */
extern int *func_00115200(void);          /* __errno */
extern int D_0013BF10;                    /* _LIB_VERSION: -1 IEEE, 0 SVID, 1 XOPEN, 2 POSIX */
extern char D_0013BF28[];                 /* "sqrt" */
extern double D_0013BF30;                 /* the domain error's result (0.0/0.0) */

double func_00131424(double x)
{
    MathException_00131424 exc;
    double z = func_001310C0(x);
    int version = D_0013BF10;

    if (version == -1 || func_001313C8(x) != 0)
        return z;
    if (!(x < 0.0))
        return z;
    exc.type = 1;
    exc.name = D_0013BF28;
    exc.arg1 = x;
    exc.err = 0;
    exc.arg2 = x;
    if (version == 0)
        exc.retval = 0.0;
    else
        exc.retval = D_0013BF30;
    if (D_0013BF10 == 2 || func_00131400(&exc) == 0)
        *func_00115200() = 33;         /* EDOM */
    if (exc.err != 0)
        *func_00115200() = exc.err;
    return exc.retval;
}
