/* functional: high. The size-exact draft (register choice for the base differs), unchanged: same reads, writes and calls. SAME on 4 calls (level 01) that all left at the first test; the rest (the unrun block) was read against retail: the id choice (entry's class, or `id` when not -1), the list at D_L01_001BD1C0+0x18C, the once-only byte, func_0029F978(p, arg1, D_L01_001B1E60) and the three stores of `value`. */
/* func_L01_003209F8 (240 bytes): the general form of func_L01_00394148: attaches effect `arg1` to the first listed moby of the class `id` (or the entry's class) once, and sets its three sizes to `value`. */
/*
 func_L01_003209F8 (240 bytes, 2 places) - same unit and flags as func_L01_00394148 (-O2 -G0 -ffunction-sections -mno-split-addresses).
 Size exact; 8 masked lines differ (w5, 2026-10-28). The `nor/movn` id replace and the loop are exact. Retail forms the
 base with `lui $v0,0x1C ; addiu $a0,$v0,-0x2E40` (result in the dead entry argument's register a0) and reads the count
 with `lh $v0,0x44($a0)`; this cc1 forms it tied in v0 and puts the count in a0.
 Reopen: the base temporary landing in a0 (after the entry id is read).
 */
extern int D_L01_001A8F40;
extern unsigned char D_001A7A40[];
extern char *D_L01_001BD1C0[];
extern unsigned char D_L01_001B1E61[];
extern char D_L01_001B1E60[];
extern float D_L01_001B1E80[];
extern float D_L01_001B1E84[];
extern float D_L01_001B1E88[];
extern void func_0029F978(char *p, int a1, char *a2);

void func_L01_003209F8(char *entry, int arg1, int id, float value)
{
    char *base;
    char **table;
    char *p;
    int wanted;
    int i;

    if (D_L01_001A8F40 != 2)
        return;
    if (D_001A7A40[0] == 0)
        return;
    wanted = *(short *)(entry + 0xAA);
    if (id != -1)
        wanted = id;
    base = (char *)D_L01_001BD1C0;
    for (i = 0; i < *(short *)(base + 0x44); i++) {
        base = (char *)D_L01_001BD1C0;
        table = (char **)(base + 0x18C);
        p = table[i];
        if (*(short *)(p + 0xAA) == wanted) {
            if (D_L01_001B1E61[0] != 0)
                continue;
            func_0029F978(p, arg1, D_L01_001B1E60);
            D_L01_001B1E80[0] = value;
            D_L01_001B1E84[0] = value;
            D_L01_001B1E88[0] = value;
        }
    }
}
