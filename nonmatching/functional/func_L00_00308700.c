/* functional: high. Same cache lookup, least-recent replacement and entry swap as retail; address arithmetic differs. */
/* GPT-6.1 Sol high, v0801: 296/288 bytes, 0/27 USA v1.01 places.
 * Default -O2 -G0 -ffunction-sections. Compared with the prior 272-byte draft,
 * the age-origin view plus grouping the data-word offset recovers the five
 * saved registers and the complete scan loop. The byte offset now survives
 * the call, but cc1 builds D+0x38 separately, costing two extra instructions.
 * The quadword swap still has pointer/value registers permuted. Grouped byte,
 * unsigned-address and word-index forms give identical 296-byte code.
 * Next: keep the original D base while preventing full selected-pointer CSE;
 * then resolve the swap's local allocator roles. No linked build was run.
 * Declarations below.
 */
typedef int Q128 __attribute__((mode(TI)));

typedef union {
    struct {
        int key;
        int age;
        unsigned char *data;
        int pad;
    } s;
    Q128 q;
} Ent_308700;

typedef struct {
    unsigned char *base;
    short *info;
    char pad8[0x28 - 8];
    int active;
    int pad2C;
    Ent_308700 e[8];
} Cache_308700;

extern Cache_308700 D_L00_001C93A0;
extern Ent_308700 D_L00_001C93D0[8];
extern int D_L00_001B18D8;
extern void func_00297550(unsigned char *, int, unsigned char *, short *);

int func_L00_00308700(int key)
{
    int found;
    int best;
    int i;

    if (D_L00_001C93A0.active == 0)
        return 0;
    found = 0;
    best = 0;
    for (i = 0; i < 8; i++) {
        if (D_L00_001C93A0.e[i].s.key == key)
            break;
        if (D_L00_001C93A0.e[i].s.age < (&D_L00_001C93A0.e[0].s.age)[best * 4])
            best = i;
    }
    if (i == 8) {
        func_00297550(((unsigned char **)&D_L00_001C93A0)[best * 4 + 14], key, D_L00_001C93A0.base, D_L00_001C93A0.info);
        D_L00_001C93A0.e[best].s.key = key;
        i = best;
        found = 1;
    }
    if (i != 0) {
        Q128 tmp = D_L00_001C93D0[0].q;
        Q128 other = D_L00_001C93D0[i].q;
        D_L00_001C93D0[i].q = tmp;
        D_L00_001C93D0[0].q = other;
    }
    D_L00_001C93A0.e[0].s.age = D_L00_001B18D8;
    return found;
}
