/* func_PAL_00295DD0, the PAL copy of func_002954C0: the same C, where rename func_002B7C80 becomes func_PAL_002B8838; rename func_002B7CE0 becomes func_PAL_002B8898. */
/* Map cache reset: calls the boot-only stub func_00298170, which is defined
 * in 00294BC8.c, so this level-placed body lives in a unit of its own. */
extern unsigned char D_001A7AFD __attribute__((section(".sdata")));
extern int D_001A79F0_3 __attribute__((sda));
extern int D_001C4FA0[];

extern void func_00298170(void);
extern int D_001F2840[];
extern void func_0029DEA8(int, int);
extern int func_PAL_002B8838(void *, int, int);
extern short func_PAL_002B8898(int);
extern int func_002EEE50(int, int, int, int);
extern int func_002EEED0(int, int, int, int, int);
extern int func_002E5E58(int, unsigned int, void *);

/* resets the map's cache slots and reloads the current level's entry */
typedef struct { int sector, size; } MapFile;
typedef struct {
    char pad0[0x36C];
    int base;           /* 0x36C */
    char pad370[0x14F0 - 0x370];
    MapFile files0[28]; /* 0x14F0 */
    MapFile files1[28]; /* 0x15D0 */
} MapToc;
extern MapToc D_0014B540;

void func_PAL_00295DD0(void)
{
    int *arena;
    int a, b, c;
    int e;
    int *map;

    func_00298170();
    func_0029DEA8(D_001C4FA0[0x230 / 4], 1);
    arena = D_001F2840;
    a = arena[0x10C / 4];
    b = arena[0x110 / 4];
    D_001C4FA0[0x248 / 4] = a;
    c = a + 0x9A800;
    D_001C4FA0[0x288 / 4] = 0;
    D_001C4FA0[0x28C / 4] = c;
    arena[0x10C / 4] = c + 0x48000;
    D_001C4FA0[0x290 / 4] = b;
    arena[0x110 / 4] = b + 0x48000;
    D_001C4FA0[0x294 / 4] = 0;
    D_001C4FA0[0x298 / 4] = 0;
    D_001C4FA0[0x29C / 4] = -1;
    D_001C4FA0[0x2A0 / 4] = -1;
    D_001C4FA0[0x2A4 / 4] = -1;
    D_001C4FA0[0x2A8 / 4] = -1;
    D_001C4FA0[0x2AC / 4] = -1;
    D_001C4FA0[0x2B0 / 4] = -1;
    if (D_001C4FA0[0x238 / 4] == -1) goto empty;
    if (D_001C4FA0[0x23C / 4] == 0 && D_001A7AFD != 0) {
        MapToc *toc = &D_0014B540;
        int size = toc->files1[D_001C4FA0[0x230 / 4]].size;
        e = size << 7;
        func_PAL_002B8838((void *)c, toc->files1[D_001C4FA0[0x230 / 4]].sector + toc->base, size);
        func_PAL_002B8898(1);
        D_001C4FA0[0x23C / 4] = 1;
        D_001C4FA0[0x240 / 4] = e;
        func_002EEE50(D_001C4FA0[0x28C / 4], D_001C4FA0[0x238 / 4], 0, e);
        D_001C4FA0[0x234 / 4] = -2;
        D_001C4FA0[0x24 / 4] = 1;
        D_001C4FA0[0x2A0 / 4] = D_001A79F0_3 + 0x100;
    } else {
        int size;
        map = D_001C4FA0;
        if (map[0x238 / 4] == -1) goto empty;
        size = map[0x240 / 4];
        map[0x2B8 / 4] = size;
        func_002EEED0(map[0x28C / 4], map[0x238 / 4], 0, size, 0);
        map[0x24 / 4] = 1;
        map[0x2A0 / 4] = D_001A79F0_3 + (D_001A7AFD ? 0x100 : 0);
        map[0x234 / 4] = -2;
    }
    goto done;
empty:
    D_001C4FA0[0x24 / 4] = 0;
done:
    func_002E5E58(0x11, 0, 0);
}
