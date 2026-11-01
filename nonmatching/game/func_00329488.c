/* Closer C3, 1 November 2026: this loop has 57 real insns against a threshold near 61; constants of life 1 move because
 * 61 * 1 >= 57. Over the threshold they stay in the body and only a long-lived 128.0f moves, which would explain retail with a
 * real for loop; the counter is still reversed though, so something else keeps its use. No real-loop form under 56 rows yet.
 */
/* Closer C2, 1 November 2026: 420/420, 3 rows, plain -O2 -G0. Retail's first loop has no loop.c work at all: up
 * counter kept, no reversal, no biv elimination, every constant left in the body (128.0f is a local set before it).
 * Written with labels it matches row for row: for/while/do forms hoist the constants and reverse the counter.
 * v[2] = v[1] = v[0] gives store order 8, 0, 4. Left: the 8-byte alignment nop before the first loop (a NOTE_INSN_LOOP_BEG
 * ahead of the label, so the source may be a real loop that loop.c rejects as invalid; no such form found) and an
 * addiu v0 / daddu s0,v0 copy where retail loads s0 directly in the second loop.
 */
typedef struct {
    float v[4];
    float f10;
    float f14;
    float f18;
    int f1C;
    int f20;
    int f24;
    int f28;
    int pad2C;
    int f30;
    int f34;
    void *owner;
    int pad3C;
} F328Tail;

typedef struct {
    float m[4];
    F328Tail t;
} F328Particle;

extern F328Particle D_0022C9A0[300];
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_00283180(float);
extern void func_002820A0(void);
extern void func_002820C8(void);
extern void func_002820D0(float, float, float, void *, int, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00329630(char *);

void func_00329488(void *obj) {
    F328Particle *base;
    F328Particle *p;
    float v[3];
    float scale, s, a, b;
    float full;
    int i, n;

    i = 0;
    func_002820A0();
    full = 128.0f;
    base = D_0022C9A0;
    p = base;
loop:
        if (p->t.owner != obj)
            goto next;
        if (p->t.f30 < (p->t.f34 >> 1))
            scale = func_00283CE0(p->t.f30) / func_00283CE0((p->t.f34 >> 1));
        else
            scale = 1.0f;
        n = func_00283CF0(scale * full);
        s = func_00283180(p->t.f14);
        a = (s + 1.0f) * 0.5f;
        b = a * (scale * -0.025f);
        v[2] = v[1] = v[0] = s * 0.05f;
        func_00282CC0(v, v, p);
        func_002820D0((p->t.f18 + p->t.f18) * a, b, 0.08f, v, n, 0);
next:
    i++;
    p++;
    if (i < 300)
        goto loop;
    func_002820C8();
    for (i = 0; i < 300; i++) {
        p = &D_0022C9A0[i];
        if (p->t.owner == obj)
            func_00329630((char *)p);
    }
}
