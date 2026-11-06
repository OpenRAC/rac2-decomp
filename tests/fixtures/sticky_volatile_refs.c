/* Authored controls for the optional sticky volatile reference; no game code. */
extern void one(void);
extern void two(int);
extern void three(int, int);

static __inline__ void copy(void *dst, const void *src)
{
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)" : : "r"(dst), "r"(src) : "$2", "memory");
}

/* A volatile asm, a call and ordinary loads follow one(): with the option the search for
   one()'s delay slot stops at the asm, so `b = a * 3` is not taken from beyond it. */
void after_asm(int *p, int a)
{
    int b;

    copy(p + 8, p + 12);
    one();
    copy(p, p + 4);
    two(*p);
    b = a * 3;
    two(p[1]);
    three(b, p[2]);
}

/* Control: an ordinary copy instead of the second asm, so the option changes nothing. */
void no_asm(int *p, int a)
{
    int b;

    copy(p + 8, p + 12);
    one();
    p[0] = p[4];
    two(*p);
    b = a * 3;
    two(p[1]);
    three(b, p[2]);
}
