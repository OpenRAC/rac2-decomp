/* func_US2_003493E0, the USA v2.00 copy of func_003486A8: the same C, with the moved fields, 88-byte
   rows and the row store at +0x54. Its own unit for the template's flags.

   As in the template, the labels' addresses are recomputed at each use and the spill slots follow
   gcse's hash order, (14029 + base regno + offset) % 95 here. v2.00's order needs a base pseudo of
   145 to 163, which `o` gets from `&o`: put_var_into_stack gives an address-taken variable a fresh
   pseudo only when the address is first taken, and purge_addressof makes it a register again before
   gcse. All other uses go through `self`, the copy in the first block, which cprop rewrites to that
   pseudo in the later blocks. position_of() brings the pseudo count to 145 at `*&o`. */
typedef unsigned char u8;
extern int func_00335E20(u8 *);
extern void *func_00336DA8(int, int);
extern int func_00336E40(void *);
extern void *func_US2_003377B0(void *, void *, void *);
extern void func_00336390(char *, char *, int);
extern void func_US2_003492B0(u8 *, int);
extern void func_003361E0(void *, void *, void *);
extern void func_00336A38(void *, int);
extern void func_00335F88(void *, float, float, float, float);
extern void func_US2_00349728(void *, int);
extern char *D_001A8CFC[] __attribute__((sda));
extern char ref_003486A8_00[];
extern char ref_003486A8_01[];
extern char ref_003486A8_02[];
extern char ref_003486A8_03[];
extern char ref_003486A8_04[];
extern char ref_003486A8_05[];
extern char ref_003486A8_06[];
extern char ref_003486A8_07[];

static inline float *position_of(char *o)
{
    return *(float **)(o + 0x4a4);
}

void func_US2_003493E0(char *o, void *data)
{
    int *v;
    char *self = o;

    *(int *)(self + 0x4ac) = 0;
    func_US2_003492B0((u8 *)self, 0);
    *(void **)(self + 0x4a8) = data;
    if (data) {
        v = func_00336DA8(16, func_00336E40(data));
        *(int **)(self + 0x4a4) = v;
        v[1] = 0;
        v[2] = 0;
        v[3] = 0;
        v[0] = 0;
    }
    {
        float *position = position_of(self);

        *(int *)(self + 0x4b0) = 1;
        position[0] = 250.0f;
    }
    position_of(self)[1] = 190.0f;
    func_003361E0(self + 0x0, ref_003486A8_00, data);
    func_003361E0(self + 0x130, ref_003486A8_01, data);
    func_003361E0(self + 0x4C, ref_003486A8_02, data);
    func_003361E0(self + 0x98, ref_003486A8_03, data);
    func_003361E0(self + 0xE4, ref_003486A8_04, data);
    func_003361E0(self + 0x17C, ref_003486A8_05, data);
    func_003361E0(self + 0x1C8, ref_003486A8_06, data);
    *(int *)(self + 0x480) = 0;
    *(int *)(self + 0x4b4) = 0;
    {
        int i;
        char *row = self + 0x218;

        for (i = 0; i < 7; i++) {
            func_US2_003377B0(row, ref_003486A8_07, data);
            func_00336A38(row, 0);
            func_00335F88(row, 1.0f, 0.0f, 0.0f, 0.0f);
            *(int *)(row + 0x54) = 0;
            *(int *)func_00335E20((u8 *)row) = 0x80F0F0F0;
            *(int *)(self + 0x488 + i * 4) = 1;
            row += 88;
        }
    }
    *(int *)func_00335E20((u8 *)self + 0x0) = 0x60442D00;
    *(int *)func_00335E20((u8 *)self + 0x130) = 0x55F0C070;
    *(int *)func_00335E20((u8 *)self + 0x4C) = 0x55F0C070;
    *(int *)func_00335E20((u8 *)self + 0x98) = 0x80FFDE8D;
    *(int *)func_00335E20((u8 *)self + 0xE4) = 0x70FFFEED;
    *(int *)func_00335E20((u8 *)self + 0x17C) = 0x60442D00;
    *(int *)func_00335E20((u8 *)self + 0x1C8) = 0x55F0C070;
    func_00336390(*&o, D_001A8CFC[0] + 0x8710, 28);
    func_00336390(self + 0x130, D_001A8CFC[0] + 0x8710, 29);
    func_00336390(self + 0x4C, D_001A8CFC[0] + 0x8710, 30);
    func_00336390(self + 0x98, D_001A8CFC[0] + 0x8710, 31);
    func_00336390(self + 0xE4, D_001A8CFC[0] + 0x8710, 32);
    func_00336390(self + 0x17C, D_001A8CFC[0] + 0x8710, 115);
    func_00336390(self + 0x1C8, D_001A8CFC[0] + 0x8710, 116);
    func_US2_00349728(self, 0);
}
