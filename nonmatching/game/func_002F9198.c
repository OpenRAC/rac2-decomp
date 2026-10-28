/* func_002F9198 - 528 bytes.  Worker attempt, 27 October 2026 (draft below).

   func_002F9198: draft 564B vs 528B in 002F5220.c (default profile).
   Structure, branches, all gp/abs global forms (sda scalar names + incomplete
   sda arrays), the 21-byte ldl/ldr table copy (__builtin_memcpy) and the
   calls already match.
   Left: (1) retail copies 48 bytes D_001B2250 -> D_001B5570 as grouped
   lq,lq,lq,sq,sq,sq from one base (needs the -frac2-qcopy file flag, i.e. a
   new file + cflags line, with a 48-byte struct assignment); my three qcopy()
   calls give interleaved lq/sq with extra addiu. (2) retail keeps `lui
   $s0,0x22` (hi of D_0021F240) in $s1 across func_002FC138 and stores mode
   via -0xDC0($s1); mine builds a separate base. (3) retail's func_002FC138
   result is unused; check it is void. */

/* goes in a NEW file with -O2 -G8 -ffunction-sections -frac2-qcopy (grouped 48-byte lq/sq copy); #include "common.h" first */
typedef struct { int mode; char pad04[0x28 - 4]; char *obj; char pad2C[0x50 - 0x2C]; int f50; char pad54[0x60 - 0x54]; int f60; char padE0[0xE0 - 0x64]; f32 camPos[4]; } Enter2F9198;
typedef struct { u8 pad[0x34]; u16 flags; } Obj2F9198;
typedef struct { void *cur; char pad04[0x14]; int f18; char pad1C[0x30 - 0x1C]; int f30; } Sel2F9198;
typedef struct { u8 pad[0x24 - 0]; } Dummy2F9198;
extern Enter2F9198 D_0021F240;
extern Sel2F9198 D_00152C00;
extern f32 D_001B5350[4];
extern char D_001B5570[0x30];
extern char D_001B2250[0x30];
extern f32 D_001AD234 __attribute__((sda));
extern f32 D_001AD238 __attribute__((sda));
extern int D_001AD230 __attribute__((sda));
extern int D_001B2284 __attribute__((sda));
extern int D_001B2288[] __attribute__((sda));
extern int D_001AD1B8 __attribute__((sda));
extern u16 D_001AD1BC __attribute__((sda));
extern u16 D_001AD1C0 __attribute__((sda));
extern short D_001A7A18[] __attribute__((sda));
extern int D_001A7AF0[] __attribute__((sda));
extern u16 D_001A7AF2[] __attribute__((sda));
extern u8 D_001AD308[21];
extern void func_002FC138(void);
extern void func_002E5CF8(int, int, char *);
extern void func_002923C0(int);
extern int func_00288FB8(int);
extern void func_0029CC98(int, int);
extern void func_002925F0(int);
extern void func_002926B8(int);
extern void func_002E6178(int);

void func_002F9198(void)
{
    u8 tbl[21];
    int *list = (int *)tbl;

    func_002FC138();
    func_002E5CF8(5, 0x11, D_0021F240.obj);
    if (D_0021F240.f60 != 0) {
        qcopy(D_001B5350, D_0021F240.camPos);
        qcopy(D_001B5570, D_001B2250);
        qcopy(D_001B5570 + 16, D_001B2250 + 16);
        qcopy(D_001B5570 + 32, D_001B2250 + 32);
    }
    ((Obj2F9198 *)D_0021F240.obj)->flags |= 0x100;
    D_0021F240.mode = 2;
    D_001AD234 = 1.0f;
    D_001AD238 = 1.1f;
    D_001B2288[0] = 0x60;
    D_001B2288[1] = 0x55;
    D_001AD230 = 0;
    D_001B2288[2] = 0;
    D_001B2288[3] = 0;
    D_001B2288[4] = 0;
    D_001B2284 = 0x60;
    if (D_0021F240.f50 == 3) {
        D_001A7A18[0] = D_001AD1B8 != 0 ? D_001AD1BC : D_001AD1C0;
        func_002923C0(D_001A7A18[0]);
        __builtin_memcpy(tbl, D_001AD308, 21);
        if (D_001AD1B8 != 0)
            func_0029CC98(func_00288FB8(list[D_001A7A18[0]]), -1);
    }
    if (D_0021F240.f50 == 2) {
        int a = D_001A7AF0[0];
        if (D_00152C00.f18 != a)
            func_002925F0(a & 3);
        if (D_00152C00.cur != 0) {
            int *c = (int *)D_00152C00.cur;
            if (c[0x98 / 4] != 0)
                c[0x98 / 4] = *(int *)(*(int *)((char *)c + 0x24) + 0x10);
        }
        {
            int s = D_001A7AF2[0] & 0x1F;
            if (D_00152C00.f30 != s)
                func_002926B8(s);
        }
        func_002E6178(0);
    }
}
