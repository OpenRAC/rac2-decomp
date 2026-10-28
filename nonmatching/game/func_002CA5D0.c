/* func_002CA5D0 - 444 bytes.  Worker attempt, 27 October 2026 (draft below).

   func_002CA5D0: draft ~444 B but 94 diff lines; needs own file 002CA5D0-g8.c
   "-O2 -G8 -ffunction-sections" ($gp store D_001A72D4 = S.stash).
   Retail details not reproduced: dest array is D_00189E20 + 0x22C8 (a struct
   at D_00189E20, as in src/game/002B7E28.c SlotRec), src is &D_001F2840 +
   0x40, hi of D_001F2840 kept in s2 and the 0x1BAF80 struct hi in s3; the
   copy loop uses movn for `v ? v : 0x77`; D_001B1888 pointer loaded tied (lui
   v0/lw v0). Mine uses one extra saved reg (s4). */

typedef struct {
    int mode;
    int zero04;
    char pad08[0xC];
    char *owner;
    char pad18[0xC];
    int state;
    int stash;
    char pad2C[0x14];
    int cur[4];
    char pad50[0xD0];
    int count;
} MenuCtl;

typedef struct { char pad[0xC]; void (*update)(char *, int); } Widget;

extern MenuCtl D_001F2840;
extern int D_001A7398[];
extern int D_0018C0E8[];
extern char *D_001B1888 MACRO_ADDR;
extern int D_001A72D4 __attribute__((sda));
extern unsigned int D_001BAF90 MACRO_ADDR;
extern void func_002FC3C0(int);
extern void func_002FC1D8(void);
extern void func_0028B160(int, int, int);
extern void func_0028AFE8(int);
extern void func_0029B720(int);
extern void func_0029B698(int);
extern void func_002FC280(void);

void func_002CA5D0(void)
{
    int i;
    int *dst;
    int *prev;
    int *src;
    int v;

    if (D_001F2840.count >= 10) {
        func_002FC3C0(1);
        func_002FC1D8();
        if (D_001F2840.owner != 0) {
            for (i = 0; i < 14; i++) {
                char *w = *(char **)(D_001F2840.owner + i * 4 + 0xEC);
                if (w != 0 && *(void (**)(char *, int))(w + 0xC) != 0)
                    (*(void (**)(char *, int))(w + 0xC))(w, 0);
            }
        }
        D_001F2840.owner = 0;
        dst = D_0018C0E8;
        prev = D_001A7398;
        src = D_001F2840.cur;
        for (i = 3; i >= 0; i--) {
            v = *src;
            *dst = *prev == v ? 0x77 : (v ? v : 0x77);
            dst++;
            src++;
            prev++;
        }
        D_001A72D4 = D_001F2840.stash;
        func_0028B160(0, *(int *)(D_001B1888 + 0x74), 0);
        func_0028AFE8(2);
        if (*(int *)(D_001B1888 + 0x80) != 0)
            func_0028AFE8(3);
        if (*(int *)(D_001B1888 + 0x84) != 0)
            func_0028AFE8(4);
        func_0029B720(0x168);
        func_0029B698(0xB4);
        D_001BAF90 &= 0x7FFFFFFF;
        D_001F2840.mode = 5;
        D_001F2840.state = 2;
        D_001F2840.zero04 = 0;
        func_002FC280();
        func_002FC3C0(1);
    }
}
