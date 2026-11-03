/* func_0029B910 - nonmatching draft, opus-1 (Claude Opus 5.5, xhigh), 2026-11-03.
 * Best result: 316/328 bytes, 0/28 places (USA v1.01), 64 of 82 rows differ.
 * Profile: own unit with -O2 -G32 -ffunction-sections -Wa,-G32 (like
 * 0029AE78-menu-g8.c); this is needed for retail's $gp form of the sized
 * D_001A9AC8[4] (at -G8/-G0 it becomes lui/addiu). The incomplete
 * D_001A8CFC[] gives retail's lui/lw macro load.
 * The record side matches: an int `level` at +0x20 (narrowed by the short
 * `id` store into lhu) gives retail's sum-form addressing and the
 * rematerialised sym+0x24.
 * Still different: sym+0x20 is hoisted into fp instead of being
 * rematerialised; the output side uses two givs (s2 = &id with second at
 * -0xC, s4 = &color) where retail has one giv s1 = D_00256418+8 (color 0,
 * id 8) plus an unreduced `s5 (i*24, init 0) + fp (D_00256418+4)` for
 * second, which costs retail the ninth saved register. Store order
 * second, color, id combines all three on one base (worse).
 * Declarations needed are the ones below.
 */

extern char *D_001A8CFC[] __attribute__((sda));
extern int D_001A9AC8[4] __attribute__((sda));
extern int func_002ED8A0(int);

typedef struct {
    unsigned short id;           /* +0x00 */
    short pad02;
    int next;                    /* +0x04 */
    int pad08[4];
    int state;                   /* +0x18 */
    short count;                 /* +0x1C */
    short pad1E;
    int level;                   /* +0x20 */
    int flag;                    /* +0x24 */
} MissionRec;

typedef struct {
    int first;                   /* +0x00 */
    int second;                  /* +0x04 */
    int color;                   /* +0x08 */
    float angle;                 /* +0x0C */
    short id;                    /* +0x10 */
    short pad12;
    int text;                    /* +0x14 */
} ListEntry;

extern MissionRec D_00262940[];
extern ListEntry D_00256418[];
extern void func_0033A9D0(char *, int, int);

void func_0029B910(void) {
    int i;
    if (D_001A8CFC[0] != 0) {
        for (i = 0; i < 4; i++) {
            int idx = func_002ED8A0(D_001A9AC8[i]);
            if (idx >= 0) {
                D_00256418[i].second = D_00262940[idx].count;
                D_00256418[i].id = D_00262940[idx].level;
                D_00256418[i].color = D_00262940[idx].flag >= 1 ? 0x6029A1FF : 0x60F0F0B0;
                func_0033A9D0(D_001A8CFC[0] + 0x3F138, i, 0);
            } else {
                func_0033A9D0(D_001A8CFC[0] + 0x3F138, i, 2);
            }
        }
    }
}
