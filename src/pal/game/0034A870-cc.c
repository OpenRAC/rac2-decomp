/* func_PAL_0034A870, the PAL copy of func_003486A8: the same C, where rename func_00348578 becomes func_PAL_0034A740; rename func_003369A8 becomes func_PAL_00338688; rename func_003489E8 becomes func_PAL_0034ABB0. */
/* Sets up the menu page's seven labels and its seven list rows. Its own unit: the labels' addresses
   are recomputed at each use and gcse numbers those pseudos in its hash table's order, which depends
   on the function's insn count. Retail's spill slots need the table of 93 buckets, which needs the
   string arguments unprecomputed (-fno-expensive-optimizations) and the row pointer walked. */
typedef unsigned char u8;
extern int func_00335E20(u8 *);
extern void *func_00336DA8(int, int);
extern int func_00336E40(void *);
extern void *func_PAL_00338688(void *, void *, void *);
extern void func_00336390(char *, char *, int);
extern void func_PAL_0034A740(u8 *, int);
extern void func_003361E0(void *, void *, void *);
extern void func_00336A38(void *, int);
extern void func_00335F88(void *, float, float, float, float);
extern void func_PAL_0034ABB0(void *, int);
extern char *D_001A8CFC[] __attribute__((sda));
extern char ref_003486A8_00[];
extern char ref_003486A8_01[];
extern char ref_003486A8_02[];
extern char ref_003486A8_03[];
extern char ref_003486A8_04[];
extern char ref_003486A8_05[];
extern char ref_003486A8_06[];
extern char ref_003486A8_07[];

void func_PAL_0034A870(char *o, void *data)
{
    int *v;

    *(int *)(o + 0x4ac) = 0;
    func_PAL_0034A740((u8 *)o, 0);
    *(void **)(o + 0x4a8) = data;
    if (data) {
        v = func_00336DA8(16, func_00336E40(data));
        *(int **)(o + 0x4a4) = v;
        v[1] = 0;
        v[2] = 0;
        v[3] = 0;
        v[0] = 0;
    }
    {
        float *position = *(float **)(o + 0x4a4);

        *(int *)(o + 0x4b0) = 1;
        position[0] = 250.0f;
    }
    (*(float **)(o + 0x4a4))[1] = 190.0f;
    func_003361E0(o + 0x0, ref_003486A8_00, data);
    func_003361E0(o + 0x130, ref_003486A8_01, data);
    func_003361E0(o + 0x4C, ref_003486A8_02, data);
    func_003361E0(o + 0x98, ref_003486A8_03, data);
    func_003361E0(o + 0xE4, ref_003486A8_04, data);
    func_003361E0(o + 0x17C, ref_003486A8_05, data);
    func_003361E0(o + 0x1C8, ref_003486A8_06, data);
    *(int *)(o + 0x480) = 0;
    *(int *)(o + 0x4b4) = 0;
    {
        int i;
        char *row = o + 0x218;

        for (i = 0; i < 7; i++) {
            func_PAL_00338688(row, ref_003486A8_07, data);
            func_00336A38(row, 0);
            func_00335F88(row, 1.0f, 0.0f, 0.0f, 0.0f);
            *(int *)func_00335E20((u8 *)row) = 0x80F0F0F0;
            *(int *)(o + 0x488 + i * 4) = 1;
            row += 88;
        }
    }
    *(int *)func_00335E20((u8 *)o + 0x0) = 0x60442D00;
    *(int *)func_00335E20((u8 *)o + 0x130) = 0x55F0C070;
    *(int *)func_00335E20((u8 *)o + 0x4C) = 0x55F0C070;
    *(int *)func_00335E20((u8 *)o + 0x98) = 0x80FFDE8D;
    *(int *)func_00335E20((u8 *)o + 0xE4) = 0x70FFFEED;
    *(int *)func_00335E20((u8 *)o + 0x17C) = 0x60442D00;
    *(int *)func_00335E20((u8 *)o + 0x1C8) = 0x55F0C070;
    func_00336390(o + 0x0, D_001A8CFC[0] + 0x8710, 28);
    func_00336390(o + 0x130, D_001A8CFC[0] + 0x8710, 29);
    func_00336390(o + 0x4C, D_001A8CFC[0] + 0x8710, 30);
    func_00336390(o + 0x98, D_001A8CFC[0] + 0x8710, 31);
    func_00336390(o + 0xE4, D_001A8CFC[0] + 0x8710, 32);
    func_00336390(o + 0x17C, D_001A8CFC[0] + 0x8710, 115);
    func_00336390(o + 0x1C8, D_001A8CFC[0] + 0x8710, 116);
    func_PAL_0034ABB0(o, 0);
}
