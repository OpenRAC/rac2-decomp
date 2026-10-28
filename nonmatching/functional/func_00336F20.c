/* functional: medium. Written from the assembly; the two jump-table switches are folded into one predicate (kind is 0xC, 0xE, 0x11, 0x12 or 0x35); same reads, writes and calls in the same order. */
typedef unsigned char u8;
typedef struct { int w0; u8 b4; u8 pad[0x67]; int w6C; u8 pad2[0x70]; } Rec336F20; /* 0xE0 bytes */

extern u8 D_00139568[];
extern Rec336F20 D_00239BA0[];
extern int D_001ADAF8[] __attribute__((sda));
extern int func_00287F60(int);
extern int func_00288D58(void);

static int isKind(int k)
{
    switch (k) {
    case 0xC: case 0xE: case 0x11: case 0x12: case 0x35:
        return 1;
    default:
        return 0;
    }
}

void func_00336F20(int kind, int *o1, int *o2, int *o3)
{
    Rec336F20 *rec;
    int *tbl;
    int n;
    int cond;

    *o1 = 0x55F0C070;
    *o2 = 0x55F0C070;

    tbl = isKind(kind) ? D_001ADAF8 + 4 : D_001ADAF8;
    rec = &D_00239BA0[D_00139568[kind]];
    *o3 = tbl[rec->b4];
    if (kind == 0x10) {
        rec = &D_00239BA0[D_00139568[0x10]];
        if (rec->b4 >= 2)
            *o3 = D_001ADAF8[rec->b4 - 2];
    }

    if (D_00239BA0[D_00139568[kind]].w0 == 0)
        return;
    if (func_00287F60(kind) <= 0)
        return;

    if (func_00288D58() != 0) {
        cond = 0;
        if (D_00239BA0[D_00139568[kind]].w0 != 0) {
            n = func_00287F60(kind);
            if (n >= 2)
                cond = 1;
            else if (n == 1)
                cond = isKind(kind);
        }
        if (cond) {
            rec = &D_00239BA0[D_00139568[kind]];
            if (rec->w0 == 0)
                return;
            if (rec->b4 == 2 || (rec->b4 == 1 && isKind(kind))) {
                *o1 = 0x60664088;
                *o2 = 0x606600D8;
            }
            return;
        }
    }
    rec = &D_00239BA0[D_00139568[kind]];
    if (rec->b4 == 0 && rec->w6C > 0) {
        *o1 = 0x6049C1FF;
        *o2 = 0x60001EFF;
    }
}
