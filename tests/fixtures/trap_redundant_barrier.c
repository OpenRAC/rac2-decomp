/* Fixture for tests/test_trap_redundant_barrier.py: authored, not game code. */
extern int ticks;
extern void every_third(void);
extern void every_fifth(void);
extern void prepare(void);

/* The branch over the first call still holds `ticks', read above the division guard;
   the call in front keeps the prologue's stores out of the way. */
void guarded(void)
{
    prepare();
    if (ticks % 3 == 0)
        every_third();
    if (ticks % 5 == 0)
        every_fifth();
}

/* Control: no division, so no guard; the reload is redundant on the branch's path and is
   dropped. */
void plain(void)
{
    prepare();
    if (ticks == 3)
        every_third();
    if (ticks == 5)
        every_fifth();
}

extern float measure(float *);
extern void mark(float *);

/* A volatile asm between the `bc1f' that holds the restore of $16 in its slot and the `b' to the
   epilogue: the restore at the epilogue is not redundant across it. */
void copied(float *dst, float *src, float *state, int mode, float *probe)
{
    if (mode == 0) {
        if (measure(probe) > 0.0f) {
            __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)" : : "r"(dst), "r"(src) : "$2", "memory");
            *state = 0.0f;
        } else {
            mark(probe);
            mark(probe);
            if (measure(probe) > 0.0f) {
                __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)" : : "r"(dst), "r"(src) : "$2", "memory");
                *state = 0.0f;
            }
        }
    } else {
        prepare();
    }
}

/* Control: a plain store in the asm's place; the `b' skips the redundant restore. */
void stored(float *dst, float *src, float *state, int mode, float *probe)
{
    if (mode == 0) {
        if (measure(probe) > 0.0f) {
            src[0] = 0.0f;
            *state = 0.0f;
        } else {
            mark(probe);
            mark(probe);
            if (measure(probe) > 0.0f) {
                dst[0] = 0.0f;
                *state = 0.0f;
            }
        }
    } else {
        prepare();
    }
}
