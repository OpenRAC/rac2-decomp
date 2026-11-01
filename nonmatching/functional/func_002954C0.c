/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* GPT-6.1 Sol (high effort), v0742, USA v1.01.
 * Best: 444 bytes, 0/28 places. Default -O2 -G0 -ffunction-sections.
 * Delaying arena setup until after the initial calls matches the prologue.
 * Distinct first/second-path size locals remove the extra callee-saved size.
 * Source store order now reproduces the arena updates and the entire first
 * path tail. Remaining: arena value registers/cache store order, table pointer
 * materialization and load order, and second-path map pointer allocation.
 * Struct fields for the map state did not change the bytes. Next investigate
 * the file-table layout and the map base's lifetime across the two paths.
 * Required declarations are included below. Not linked.
 */
extern void func_00298170(void);
extern int D_001C4FA0[];
extern int D_001F2840[];
extern char D_0014B540_1[];
extern unsigned char D_001A7AFD __attribute__((section(".sdata")));
extern int D_001A79F0_3 __attribute__((section(".sdata")));

extern void func_0029DEA8(int, int);
extern void func_002B7C80(unsigned long, int, unsigned long);
extern void func_002B7CE0(int);
extern void func_002EEE50(int, int, int, int);
extern void func_002EEED0(int, int, int, int, int);
extern void func_002E5E58(int, int, int);

/* resets the map's cache slots and reloads the current level's entry */
void func_002954C0(void)
{
    int *arena;
    int a;
    int b;
    int c;
    int e;
    int filebase;
    int fileoff;
    int *map;

    func_00298170();
    func_0029DEA8(D_001C4FA0[0x230 / 4], 1);
    arena = D_001F2840;
    a = arena[0x10C / 4];
    b = arena[0x110 / 4];
    c = a + 0x9A800;
    arena[0x10C / 4] = c + 0x48000;
    arena[0x110 / 4] = b + 0x48000;
    D_001C4FA0[0x248 / 4] = a;
    D_001C4FA0[0x288 / 4] = 0;
    D_001C4FA0[0x28C / 4] = c;
    D_001C4FA0[0x290 / 4] = b;
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
        int *sizes;
        int *offsets;
        filebase = *(int *)((char *)D_0014B540_1 + 0x36C);
        offsets = (int *)(D_0014B540_1 + D_001C4FA0[0x230 / 4] * 8);
        sizes = offsets;
        fileoff = *(int *)((char *)offsets + 0x15D0) + filebase;
        e = *(int *)((char *)sizes + 0x15D4);
        func_002B7C80(c, fileoff, e);
        e <<= 7;
        func_002B7CE0(1);
        D_001C4FA0[0x23C / 4] = 1;
        D_001C4FA0[0x240 / 4] = e;
        func_002EEE50(D_001C4FA0[0x28C / 4], D_001C4FA0[0x238 / 4], 0, e);
        D_001C4FA0[0x234 / 4] = -2;
        D_001C4FA0[0x24 / 4] = 1;
        D_001C4FA0[0x2A0 / 4] = D_001A79F0_3 + 0x100;
    } else {
        int size;
        map = D_001C4FA0;
        if (map[0x238 / 4] == -1) goto done;
        size = map[0x240 / 4];
        map[0x2B8 / 4] = size;
        func_002EEED0(map[0x28C / 4], map[0x238 / 4], 0, size, 0);
        map[0x234 / 4] = -2;
        map[0x24 / 4] = 1;
        map[0x2A0 / 4] = D_001A79F0_3 + (D_001A7AFD ? 0x100 : 0);
    }
    goto done;
empty:
    D_001C4FA0[0x24 / 4] = 0;
done:
    func_002E5E58(0x11, 0, 0);
}
