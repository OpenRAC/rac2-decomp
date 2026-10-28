/* func_002926B8 - 460 bytes.  Worker attempt, 27 October 2026 (draft below).

   func_002926B8: size should be 460B (run check.py). Logic right. Left: (1)
   register swap: retail buf=s1, src(buf+8)=s2, id=s2; mine buf=s2, src=s1.
   (2) retail v1=lui table base, v0=v1+a0*8; mine swapped v0/v1. (3) tail
   64-bit OR order: retail loads D_001A7300 and D_001A72F0 early (both before
   the shifts) and ors (A|w<<14), |(id<<26|0x1B00000), |id<<30,
   |(B<<37|0x400000000), |1<<63; mine loads/ors in a different order. Tried:
   incomplete sda arrays for the absolute reads (good), local src before/after
   the call, one-expression and stepwise ors. */

/* src/game/00291758.c, replaces the INCLUDE_ASM */
typedef struct { long q[12]; } GsLoadImage292688 __attribute__((aligned(16)));
typedef struct { char pad[0x3E24]; int base; char pad2[0x48F0 - 0x3E28]; struct { int offset; int count; } ent[1]; } Table2926B8;
typedef struct { char pad[0x30]; int mode; char pad4[4]; long long word; } State2926B8;
extern State2926B8 D_00152C00;
extern int D_001B22A0[];
extern int D_001B22B4[] __attribute__((sda));
extern Table2926B8 D_0014B540;
extern int D_001A72F0[] __attribute__((sda));
extern int D_001A7300[] __attribute__((sda));
extern void func_002FC3C0(int);
extern void func_002B7CE0(int);
extern int func_002B7C80(char *, int, int);
extern int func_00126288(GsLoadImage292688 *, short, short, short, short, short, short, short);
extern void func_0011AEA0(int);
extern int func_001265B0(GsLoadImage292688 *, void *);
extern int func_001244B8(int, int);
extern int func_00282A18(int);

void func_002926B8(int a0)
{
    GsLoadImage292688 li;
    int *src;
    int *buf;
    int id;
    int w;
    long long result;

    D_00152C00.mode = a0;
    func_002FC3C0(1);
    buf = (int *)D_001B22A0[1 - D_001B22B4[0]];
    src = buf + 8;
    func_002B7CE0(1);
    func_002B7C80((char *)buf, D_0014B540.ent[a0].offset + D_0014B540.base, D_0014B540.ent[a0].count);
    func_00126288(&li, D_001A72F0[0] >> 8, 1, 0, 0, 0, 16, 16);
    func_0011AEA0(0);
    func_001265B0(&li, src);
    func_001244B8(0, 0);
    id = func_00282A18(buf[2]);
    w = buf[2] >> 6;
    if (w <= 0)
        w = 1;
    func_00126288(&li, D_001A7300[0] >> 8, w, 0x1B, 0, 0, (short)buf[2], (short)buf[3]);
    func_0011AEA0(0);
    func_001265B0(&li, buf + 0x108);
    func_001244B8(0, 0);
    result = ((long long)(D_001A7300[0] >> 8) | ((long long)w << 14) | ((long long)id << 26 | 0x1B00000)
              | ((long long)id << 30) | ((long long)(D_001A72F0[0] >> 8) << 37 | 0x400000000LL))
             | 0x8000000000000000ULL;
    D_00152C00.word = result;
}
