/* func_0031E3A8 - 380 bytes.  Worker attempt, 27 October 2026 (draft below).

   func_0031E3A8 376B vs 380B. Logic right (64 particles of 0x30 B at
   D_001B2754[0], id match, phase wrap, respawn). Left: scheduling only.
   Retail: bnel on the id test with i++ in its delay slot and the float
   constants (0.01f/0.075f, -8.0f, 8.0f, 1.0f) loaded AFTER the test and the
   phase store (swc1 f1,0x20 in the bc1f delay slot, add.s after); mine hoists
   the mtc1 constants above the id compare and keeps phase in a register (no
   early store). Tried continue vs if-body form; p->phase -= / += vs temp. */

/* src/game/003173B0.c, replaces the INCLUDE_ASM */
typedef struct {
    f32 dir[3];
    f32 pad0C;
    int id;
    f32 speed;
    int timer;
    int timerMax;
    f32 phase;
    int zero24;
    f32 side;
    f32 one;
} Particle_31E3A8;

extern Particle_31E3A8 *D_001B2754[] __attribute__((sda));
extern int func_00282948(void *);
extern int func_002A7820(int, int);
extern f32 func_002A7878(f32, f32);
extern char func_001163B0(void);
extern void func_00282F20(void *, void *, f32);

void func_0031E3A8(int id)
{
    int i;

    for (i = 0; i < 64; i++) {
        Particle_31E3A8 *p = &D_001B2754[0][i];
        if (p->id == id) {
            p->phase -= func_002A7878(0.01f, 0.075f);
            if (p->phase <= -8.0f)
                p->phase += 8.0f;
            if (func_00282948(&p->timer) != 0) {
                p->dir[0] = func_002A7878(-1.0f, 1.0f);
                p->dir[1] = func_002A7878(-1.0f, 1.0f);
                p->dir[2] = func_002A7878(-1.0f, 1.0f);
                p->zero24 = 0;
                p->timerMax = p->timer = func_002A7820(0x14, 0x32);
                p->side = (func_001163B0() & 1) ? 1.0f : -1.0f;
                p->one = 1.0f;
                func_00282F20(p, p, 1.0f);
                p->speed = func_002A7878(0.7f, 0.9f);
            }
        }
    }
}
