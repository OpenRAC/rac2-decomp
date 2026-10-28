/* func_00294420 - 456 bytes.  Worker attempt, 27 October 2026 (draft below).

   func_00294420 460B vs 456B, logic matches (all 3 loops, movz chains,
   tables). Diffs: register allocation of the locals (retail t1/t2 marks,
   a2/t6/t7 bases); the while (j==m1||j==m2) j++ loop: retail has one aligned
   head (5 nops) and the 2nd beql jumps back to the j++ at the top, mine emits
   a second aligned head (3 more nops). Tried plain while, swapped order,
   nested while(j==m1) inside. */

/* src/game/00291758.c, replaces the INCLUDE_ASM */
typedef struct { char pad[0x14]; int id; char rest[0xE0 - 0x18]; } SlotRec;
extern char D_00189E20[];
extern short D_001A63AC;
extern int D_001A7398;
extern int D_001A7A04;
extern unsigned char D_00139568[];
extern SlotRec D_00239BA0[];
extern int D_00152D04[];
extern struct { int id; char pad[0x10]; } D_00150080[];
extern int func_00294630(int);
extern void func_00294398(int, int);

void func_00294420(int v)
{
    int a, b, j, mark1, mark2, cur;
    if (func_00294630(v) != 0)
        return;
    if (D_001A63AC != 0)
        return;
    a = D_00239BA0[D_00139568[*(int *)(D_00189E20 + 0x22E4)]].id;
    b = D_00239BA0[D_00139568[D_001A7398]].id;
    if (b == a)
        b = D_00239BA0[D_00139568[D_001A7A04]].id;
    if (a == v)
        a = -1;
    if (b == v)
        b = -1;
    mark1 = -1;
    mark2 = -1;
    for (j = 0; j < 3; j++) {
        int id = D_00150080[D_00152D04[j]].id;
        if (b == id)
            mark2 = j;
        if (a == id)
            mark1 = j;
    }
    j = 0;
    while (j == mark1 || j == mark2) {
        j++;
        while (j == mark1)
            j++;
    }
    cur = *(int *)(D_00189E20 + 0x22C8);
    if (cur != 0) {
        int k = D_00152D04[j];
        if (k != -1) {
            if (D_00239BA0[D_00139568[cur]].id == D_00150080[k].id)
                *(int *)(D_00189E20 + 0x22C8) = 0;
        }
    }
    func_00294398(v, j);
}
