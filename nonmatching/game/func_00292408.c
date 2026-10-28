/* func_00292408 - 472 bytes.  Worker attempt, 27 October 2026 (draft below).

   func_00292408 468B vs 472B (sibling of func_002926B8, same GS-word build).
   Logic right. Left: (1) final 64-bit store: retail 'lui $at; sd
   a3,0x72C8($at)' BEFORE the last jal with 'addu a1' in the delay slot; mine
   (MACRO_ADDR long long) puts the sd in the jal delay slot, which turns it
   into the gp form (that is the 4 bytes). (2) 64-bit OR chain order/regs:
   retail loads D_001A72FC then D_001A72EC both before the shifts, mine loads
   them separately later. Reads use incomplete sda arrays (correct). Not
   tried: volatile (banned). */

/* src/game/00291758.c, replaces the INCLUDE_ASM */
typedef struct { long q[12]; } GsLoadImage292408 __attribute__((aligned(16)));
typedef struct { char pad[0x4F04]; int base; char pad2[0x4F98 - 0x4F08]; struct { int offset_b; int count_b; int offset_a; int count_a; } ent[1]; } Table292408;
extern void func_002FC3C0(int);
extern void func_002B7CE0(int);
extern int func_002B7C80(char *, int, int);
extern int func_00126288(GsLoadImage292408 *, short, short, short, short, short, short, short);
extern void func_0011AEA0(int);
extern int func_001265B0(GsLoadImage292408 *, void *);
extern int func_001244B8(int, int);
extern int func_00282A18(int);
extern Table292408 D_0014B540;
extern int *D_001BAF34;
extern int D_001A72EC[] __attribute__((sda));
extern int D_001A72FC[] __attribute__((sda));
#ifndef MACRO_ADDR
#define MACRO_ADDR __attribute__((section(".sdata")))
#endif
extern long long D_001A72C8 MACRO_ADDR;

void func_00292408(int a0)
{
    GsLoadImage292408 li;
    int *buf;
    int *hdr;
    int *src;
    int id;
    int w;
    long long result;

    func_002FC3C0(1);
    buf = D_001BAF34;
    func_002B7CE0(1);
    src = buf + 12;
    func_002B7C80((char *)buf, D_0014B540.ent[a0].offset_a + D_0014B540.base, D_0014B540.ent[a0].count_a);
    hdr = buf + 4;
    func_00126288(&li, D_001A72EC[0] >> 8, 1, 0, 0, 0, 16, 16);
    func_0011AEA0(0);
    func_001265B0(&li, src);
    func_001244B8(0, 0);
    id = func_00282A18(hdr[2]);
    w = hdr[2] >> 6;
    if (w <= 0)
        w = 1;
    func_00126288(&li, D_001A72FC[0] >> 8, w, 0x1B, 0, 0, (short)hdr[2], (short)hdr[3]);
    func_0011AEA0(0);
    func_001265B0(&li, buf + 0x10C);
    func_001244B8(0, 0);
    result = ((long long)(D_001A72FC[0] >> 8) | ((long long)w << 14) | ((long long)id << 26 | 0x1B00000)
              | ((long long)id << 30) | ((long long)(D_001A72EC[0] >> 8) << 37 | 0x400000000LL))
             | 0x8000000000000000ULL;
    D_001A72C8 = result;
    func_002B7C80((char *)buf, D_0014B540.ent[a0].offset_b + D_0014B540.base, D_0014B540.ent[a0].count_b);
}
