/* func_L09_002F8BA0 - 464 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   func_L09_002F8BA0 (464 B). Needs L09_002F8BA0-g8.c (gp float
   D_L09_001A93E0). Decoded fully (draft.c): game-state 9 gate, id = 0x47 or
   -1 from (D_L09_001BD700.f34-2)<=0x3E6, rot vec {0,0,gp float}, 4 table
   vectors transformed, alpha pulse sin(2*pi*(t%120)/120).
   Not matching, ~95 masked lines: sizes 456-460 vs 464 (retail has the
   `beql/break` zero check for `% 120`, so the divisor is a variable at expand
   time; keeping `int period=120` puts it in $s4 for the whole function),
   retail zeroes rot with `addiu $v0,$sp,0x30; sq $zero,0($v0)` (no por; mine
   por+sq), saved-register numbering differs ($s4 id, $s7 hi of D_L09_001BD700
   in retail).
   Tried: period local (kept in $s4), literal 120, incomplete-sda
   D_001A79F0[0] for the absolute lui/lw, m[12] (fixes frame layout). */

typedef int TI128 __attribute__((mode(TI)));
typedef struct { unsigned char pad[0x34]; int f34; } G_L09_001BD700;
extern G_L09_001BD700 D_L09_001BD700;
extern f32 D_L09_001A93E0 __attribute__((sda));
extern f32 D_L09_001B9420[];
extern int D_001A79F0[] __attribute__((sda));
extern void func_00282F20(void *, void *, f32);
extern void func_002833F0(void *, void *);
extern f32 func_00283198(f32);
extern f32 func_00283CE0(int);
extern int func_00283CF0(f32);
extern void func_L01_002E2608(void *, int, int, int, int);

void func_L09_002F8BA0(void *a0) {
    f32 m[12] __attribute__((aligned(16)));
    f32 rot[4] __attribute__((aligned(16)));
    f32 pts[4][4] __attribute__((aligned(16)));
    f32 off[4] __attribute__((aligned(16)));
    f32 *tbl;
    f32 *out;
    int id = -1;
    int period = 120;
    int i;
    int t;
    f32 a;

    if (D_001A79F0[0] != 9) {
        return;
    }
    if ((unsigned)(D_L09_001BD700.f34 - 2) <= 0x3E6) {
        id = 0x47;
    }
    if (id == -1) {
        return;
    }
    *(TI128 *)rot = 0;
    rot[2] = D_L09_001A93E0;
    func_002833F0(m, rot);
    tbl = D_L09_001B9420;
    func_00282F20(off, m, 0.05f);
    out = pts[0];
    for (i = 3; i >= 0; i--) {
        func_00283098(out, tbl, m);
        tbl -= 4;
        func_00282CC0((char *)out, (char *)out, (char *)a0 + 0x10);
        func_00282CC0((char *)out, (char *)out, (char *)off);
        out += 4;
    }
    t = D_L09_001BD700.f34 % period;
    a = func_00283198((f32)t * 6.2831855f / func_00283CE0(120));
    func_L01_002E2608(pts, id, 0, ((func_00283CF0((a * 0.5f + 0.5f) * 48.0f) + 0x50) << 24) | 0x808080, 0);
}
