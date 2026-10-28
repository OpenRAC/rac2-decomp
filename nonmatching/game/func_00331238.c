/* func_00331238 - 424 bytes.  Worker attempt, 27 October 2026 (draft below).

   Append draft to src/game/0032EB28-qcopy.c (flags already -frac2-qcopy
   -frac2-qcopy-barrier); remove marker in src/game/0032EB28.c. 428 B vs 424
   B, frame 0x80 vs 0x70.
   Everything matches except one thing: mine hoists the 61300.0f (0x470B7400)
   argument into a third callee-saved float ($f20/$f22) for the whole loop;
   retail only keeps 0.005f ($f21) and 0.035f ($f20) and rebuilds 61300.0f
   with lui/ori/mtc1 $f12 + mov.s $f13,$f12 before each of the two
   func_002C65A0 calls.
   Found: struct {TI128 pos; TI128 v; float p[4];} L for retail stack layout;
   `L.pos = *center` (not qcopy, which is not declared in this file);
   D_001A8BD0 needs section(".sdata") attribute (MACRO_ADDR) or its address is
   hoisted into $s4. */

/* append to src/game/0032EB28-qcopy.c (uses its TI128 typedef); remove marker from src/game/0032EB28.c */
typedef struct {
    unsigned char pad0[2];
    unsigned char b2;
} Spark_331238;

extern struct {
    unsigned char pad0[0xD4];
    unsigned char *p_d4;
    unsigned char pad_d8[0x94];
    unsigned char *p_16c;
} D_001F2540;
extern char D_001A8BD0[] __attribute__((section(".sdata")));

extern void func_00282D30(void *out, float scale);
extern void func_00282CC0(void *out, void *a, void *b);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int);
extern Spark_331238 *func_002C65A0(void *, void *, int, int, int, int, int, int, float, float, float);

void func_00331238(TI128 *center)
{
    struct {
        TI128 pos;
        TI128 v;
        float p[4];
    } L;
    int i;
    int color;
    Spark_331238 *s;

    L.pos = *center;
    func_00282D30(&L.v, 0.5f);
    func_00282CC0(&L.pos, &L.pos, &L.v);
    for (i = 8; i >= 0; i--) {
        L.p[0] = ((float *)&L.pos)[0] + func_002A78D8(0.005f, 0.035f);
        L.p[1] = ((float *)&L.pos)[1] + func_002A78D8(0.005f, 0.035f);
        L.p[2] = ((float *)&L.pos)[2] + func_002A78D8(0.005f, 0.035f);
        color = func_002A77E0(255);
        s = func_002C65A0(L.p, D_001A8BD0, 4, 0x808080, color, 0x7F, 0x3F, 1, 35700.0f, 35700.0f, 0.0f);
        if (s)
            s->b2 = D_001F2540.p_16c[1];
        s = func_002C65A0(L.p, D_001A8BD0, 4, 0x406080, color, 0x10, 8, 1, 35700.0f, 35700.0f, 0.0f);
        if (s)
            s->b2 = D_001F2540.p_d4[0];
    }
}
