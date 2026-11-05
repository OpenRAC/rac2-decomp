/* Short loops whose body holds a two-instruction 16-byte copy. */
typedef int TI128 __attribute__((mode(TI)));

static __inline__ void qcopy(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2", "memory");
}

/* lq, sq, addiu, addiu, slti, bnez, addiu: seven words, no pad (func_L00_0041CB80). */
void asm_copy_rows(char *dst, char *src)
{
    int i;

    for (i = 0; i < 3; i++) {
        qcopy(dst + 0xC0 + i * 16, src + 0xC0 + i * 16);
    }
}

/* The grouped pattern: lq, sq, two addiu, the branch and its slot are six words. */
void pattern_copy_rows(char *dst, char *src)
{
    int i;

    for (i = 0; i < 3; i++) {
        ((TI128 *)(dst + 0xC0))[i] = ((TI128 *)(src + 0xC0))[i];
    }
}

/* A scalar loop shorter than seven words is still padded. */
void scalar_rows(int *dst, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        dst[i] = 0;
    }
}

/* Two back edges to the same head must share the first edge's padding. */
unsigned skip_pair(unsigned value, unsigned first, unsigned second)
{
    while (value == first || value == second)
        value++;
    return value;
}

/* A later independent head still gets its own minimum span. */
unsigned skip_two_pairs(unsigned value, unsigned a, unsigned b, unsigned c, unsigned d)
{
    while (value == a || value == b)
        value++;
    while (value == c || value == d)
        value++;
    return value;
}

/* Volatile reads cannot be speculated into the other condition's delay slot. */
void poll_pair(volatile unsigned *a, volatile unsigned *b)
{
    while (*a || *b) {
        /* Both condition reads are the observable polling work. */
    }
}
