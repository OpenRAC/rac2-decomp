/* functional: medium. The one captured call takes the D_001A7BB8 branch with the argument checked only as given; the other two display modes and the buffer-clear loop were read from the assembly but not exercised. Hand-written from the assembly: picks the display mode (three variants by D_001A7B90/D_001A7BB8), publishes the framebuffer addresses and size globals, writes the GS register packet at D_00139120 and, when the argument is set, clears the frame buffers by uploading blocks of the 0x1BB000 area; same reads, writes and calls in retail order, 64-bit values are computed in `long`. */
typedef struct { long q[12]; } GsLoadImage27B440 __attribute__((aligned(16)));
extern int D_001A7B90;
extern int D_001A7BB8;
extern int D_001A72E4;
extern int D_001A72E0;
extern int D_001A72DC;
extern int D_001A72D8;
extern int D_001A72EC;
extern int D_001A72F0;
extern int D_001A72F4;
extern int D_001A7358;
extern int D_001A735C;
extern int D_001A72E8;
extern int D_001A7340;
extern int D_001A7344;
extern int D_001A7348;
extern int D_001A734C;
extern int D_001A7350;
extern int D_001A7354;
extern int D_001A72D4;
extern int D_001A72D0;
extern unsigned char D_001A6480[];
extern long D_00139120[];
extern long D_00139310;
extern long D_00139380;
extern void func_0011AEA0(int);
extern void func_00284268(int, int, int, int, int, int);
extern void func_00284EA8(void);
extern void func_00284F40(int);
extern void func_00284E80(void);
extern void func_00282A60(void *, int, int);
extern int func_00126288(GsLoadImage27B440 *, short, short, short, short, short, short, short);
extern int func_001265B0(GsLoadImage27B440 *, void *);
extern int func_001244B8(int, int);

void func_0027B440(int a0)
{
    GsLoadImage27B440 li;
    long t0, t3, t6, s0v, top;
    int e0, w152, w150, s2, s3, t2, t1, a2, t8, s0, s1, v0;

    func_0011AEA0(0);
    if (D_001A7B90 != 0) {
        D_001A72E4 = 0x2C0000;
        D_001A72E0 = 0x100000;
        D_001A72DC = 0x1E0000;
        D_001A72D8 = 0;
        func_00284268(0x200, 0x1C0, 0x200, 0x200, 4, 0);
    } else if (D_001A7BB8 != 0) {
        D_001A72E4 = 0x2C0000;
        D_001A72E0 = 0x118000;
        D_001A72DC = 0x1E8000;
        D_001A72D8 = 0;
        func_00284268(0x200, 0x1A0, 0x280, 0x1C0, 0, 0);
    } else {
        D_001A72E4 = 0x2C0000;
        D_001A72E0 = 0x118000;
        D_001A72DC = 0x1E8000;
        D_001A72D8 = 0;
        func_00284268(0x200, 0x1A0, 0x200, 0x1C0, 0, 0);
    }

    e0 = D_001A72E0 >> 13;
    w152 = *(unsigned short *)(D_001A6480 + 0x152);
    w150 = *(unsigned short *)(D_001A6480 + 0x150);
    s0 = D_001A72DC;
    s3 = (int)(w152 << 16) >> 17;
    s2 = (int)(w150 << 16) >> 17;
    D_001A7354 = (0x800 - s3) << 4;
    D_001A7350 = (0x800 - s2) << 4;
    v0 = (int)(w150 << 16) >> 22;
    t2 = D_001A7354;
    a2 = (int)(w150 << 16) >> 16;
    t1 = (int)(w152 << 16) >> 16;
    top = D_001A7350;
    t8 = D_001A72E4;
    t0 = e0 | 0x1000000;
    t3 = ((long)(a2 - 1) << 16) | ((long)(t1 - 1) << 48);
    s0v = ((long)s0 >> 13) | ((long)v0 << 16);
    t6 = top | ((long)t2 << 32);
    D_00139120[0x80 / 8] = t3;
    D_00139380 = t0 | 0x100000000L;
    D_001A72EC = t8 + 0x1000;
    D_001A72F0 = t8 + 0x1400;
    D_001A72F4 = t8 + 0x1800;
    D_001A7358 = (s2 + 0x800) << 4;
    D_001A735C = (s3 + 0x800) << 4;
    D_00139120[0x20 / 8] = s0v;
    D_00139120[0x50 / 8] = t6;
    D_00139120[0x60 / 8] = t6;
    D_00139310 = t0;
    D_001A72E8 = t8;
    D_001A7340 = a2;
    D_001A7344 = t1;
    D_001A7348 = s2;
    D_001A734C = s3;
    D_00139120[0x10 / 8] = s0v;
    D_00139120[0x30 / 8] = t0;
    D_00139120[0x40 / 8] = t0;
    D_00139120[0x70 / 8] = t3;

    if (a0 != 0) {
        D_001A72D4 = t8;
        D_001A72D0 = t8;
        func_0011AEA0(0);
        func_001244B8(0, 0);
        s1 = 0;
        func_0011AEA0(0);
        func_00284EA8();
        func_00284F40(0);
        func_0011AEA0(0);
        func_001244B8(0, 0);
        func_00284E80();
        func_00282A60((void *)(0x1C0000 - 0x5000), 0, 0x1000);
        s0 = (*(short *)(D_001A6480 + 0x158) * *(short *)(D_001A6480 + 0x15A)) >> 10;
        if (s0 > 0) {
            do {
                func_00126288(&li, s1 << 4, 1, 0, 0, 0, 0x20, 0x20);
                s1++;
                func_0011AEA0(0);
                func_001265B0(&li, (void *)(0x1C0000 - 0x5000));
                func_001244B8(0, 0);
            } while (s1 < s0);
        }
    }
}
