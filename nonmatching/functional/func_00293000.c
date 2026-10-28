/* functional: high. Hand-written from the assembly: uploads the entries of a texture table through the GS image loader, twice (first the n entries of mixed type, then m entries of type 0x1B) and tracks the allocation pointers D_001A72D0/D_001A72D4; byte layout of the registers differs, behaviour is the same. */
typedef struct { long q[12]; } GsLoadImage293000 __attribute__((aligned(16)));
extern int D_001A72F4;
extern int D_001A72D4 __attribute__((sda));
extern int D_001A72D0 __attribute__((sda));
extern int D_001A7304;
extern int func_00126288(GsLoadImage293000 *, short, short, short, short, short, short, short);
extern void func_0011AEA0(int);
extern int func_001265B0(GsLoadImage293000 *, void *);
extern int func_001244B8(int, int);

void func_00293000(int base, int n, int m, int *tbl)
{
    GsLoadImage293000 li;
    int v = D_001A72F4;
    int w, h, type, area, alloc, dst;

    D_001A72D4 = v;
    D_001A72D0 = v;
    while (n > 0) {
        void *src = (void *)(base + tbl[3]);
        type = tbl[0];
        w = tbl[1] & 0xFFFF;
        h = tbl[1] >> 16;
        if (type == 0x13) {
            func_00126288(&li, D_001A72D0 >> 8, (w >> 6) != 0 ? (w >> 6) : 1, 0x13, 0, 0, w, h);
            area = w * h;
            D_001A72D0 = D_001A72D0 + (area > 0xFF ? area : 0x100);
        } else if (type == 2) {
            func_00126288(&li, D_001A72D0 >> 8, 1, 2, 0, 0, 0x10, 0x10);
            D_001A72D0 = D_001A72D0 + 0x200;
        } else if (type == 0) {
            func_00126288(&li, D_001A72D0 >> 8, 1, 0, 0, 0, 0x10, 0x10);
            D_001A72D0 = D_001A72D0 + 0x400;
        }
        func_0011AEA0(0);
        n--;
        tbl += 4;
        func_001265B0(&li, src);
        func_001244B8(0, 0);
    }
    alloc = D_001A7304;
    D_001A72D4 = D_001A72D0;
    while (m > 0) {
        void *src2 = (void *)(base + tbl[2]);
        w = tbl[1] & 0xFFFF;
        h = tbl[1] >> 16;
        func_00126288(&li, alloc >> 8, (w >> 6) != 0 ? (w >> 6) : 1, 0x1B, 0, 0, w, h);
        m--;
        tbl += 4;
        func_0011AEA0(0);
        alloc += (w * h) << 2;
        func_001265B0(&li, src2);
        func_001244B8(0, 0);
    }
}
