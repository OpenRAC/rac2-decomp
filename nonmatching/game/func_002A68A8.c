/* func_002A68A8 - 564 bytes.  Worker attempt, 27 October 2026 (draft below).

   Draft replaces the marker in src/game/002A0430.c (same flags). Size is
   within a few bytes (568 vs 564 before the last fixes); structure of all
   three loops matches (beql chains, exclusion sets {1F,3D,2D,4D} / {1F,3D} /
   {1F,3D,2D,4D}, pick/i registers once each loop has its own i/j/k).
   Remaining diffs:
   - the class-limit chain: retail `addu v0,a1,t6; lbu v1; mult v0,v1,t4; addu
   v1,v0,t7; lhu v0,0x8E(v1); beqz v0; ... (last exclusion beq with `daddu
   v1,v0,zero` in its delay slot, i.e. limit copied into $v1 just before `lw
   v0,0(a2); slt v0,v0,v1`)`; mine uses v1/v0 swapped and no copy. Separating
   `count` and `limit` locals was copy-propagated away.
   - tail: retail `addiu v1,zero,1; addiu a0,zero,2; movn a0,v1,v0; ... daddu
   v0,a0`; mine uses v1 as the result reg (`return f(5) ? 1 : 2` and `== 0 ? 2
   : 1` both give movn v1,a0,v0; an explicit `result` local made it worse, it
   took $s0).
   - loop 1 exclusion order: retail's last exclusion (0x4D) is a non-likely
   `beq` with the limit copy in its delay slot; mine is `beql`. */

/* replaces the INCLUDE_ASM marker in src/game/002A0430.c (default flags -O2 -G8) */
typedef struct {
    unsigned char pad0[0x8E];
    unsigned short count;
    unsigned char pad90[0x50];
} Class_2A68A8;

extern unsigned char D_001A7AF8[] __attribute__((sda));
extern unsigned char D_00139568[];
extern int D_00139688[];
extern Class_2A68A8 D_00239BA0[];
extern int func_002A77E0(int);

int func_002A68A8(int unused, int *out)
{
    int i;
    int j;
    int k;
    int sum = 0;
    int total = 0;
    int pick;

    for (i = 0; i < 0x38; i++) {
        unsigned short count;
        int limit;
        Class_2A68A8 *cls;

        if (D_001A7AF8[i] == 0)
            continue;
        cls = &D_00239BA0[D_00139568[i]];
        count = cls->count;
        if (count == 0)
            continue;
        if (i == 0x1F || i == 0x3D || i == 0x2D || i == 0x4D)
            continue;
        limit = count;
        total++;
        sum += D_00139688[i] < limit;
    }
    if (sum != 0) {
        pick = func_002A77E0(sum);
        for (j = 0; j < 0x38; j++) {
            unsigned short limit;
            Class_2A68A8 *cls;

            if (D_001A7AF8[j] == 0)
                continue;
            cls = &D_00239BA0[D_00139568[j]];
        limit = cls->count;
            if (limit == 0 || !(D_00139688[j] < limit))
                continue;
            if (j == 0x1F || j == 0x3D)
                continue;
            if (pick == 0) {
                *out = j;
                break;
            }
            pick--;
        }
    } else {
        pick = func_002A77E0(total);
        for (k = 0; k < 0x38; k++) {
            unsigned short limit;
            Class_2A68A8 *cls;

            if (D_001A7AF8[k] == 0)
                continue;
            cls = &D_00239BA0[D_00139568[k]];
        limit = cls->count;
            if (limit == 0)
                continue;
            if (k == 0x1F || k == 0x3D || k == 0x2D || k == 0x4D)
                continue;
            if (pick == 0) {
                *out = k;
                break;
            }
            pick--;
        }
    }
    return func_002A77E0(5) ? 1 : 2;
}
