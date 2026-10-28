/* func_00329488 - 420 bytes.  Worker attempt, 27 October 2026 (draft below).

   Structure/semantics decoded and right (two loops, 300 x 0x50 particles at
   D_0022C9A0, callees
   2820A0/283CE0/283CF0/283180/282CC0/2820D0/2820C8/329630). Not exact:
   - With `f34 / 2`: 432 bytes vs 420 (srl/addu/sra for /2; retail has a plain
   sra). With `>> 1`: 448 bytes, gcc hoists ALL float constants out of the
   loop (retail hoists only 128.0f into $f23, others stay in loop).
   - Retail keeps an UP counter s3 (addiu at top, slti 0x12C at bottom); mine
   reverses to a down counter (bgez). Same loop-shape issue as func_00329328.
   - Retail dumps the stack vec in order sw 8,0,4 (mine 0,8,4).
   Update: func_00329328 matched with `F328Particle *base = D_0022C9A0; ... p
   = &base[i];` (indexed through a local base pointer, makes the prologue
   lui/addiu match) plus `float half = 0.5f;` (the hoisted constant). For this
   function the same base[i] form gives mult-based indexing (472 B); pointer
   p++ form hoists ALL constants (468 B, needs 5 callee-saved float regs).
   Retail has single pointer iv s1, up counter s3, only 128.0f hoisted into
   $f23. */

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
    F328Particle *p;
    float v[3];
    float scale, s, a, b;
    int i, n;

    func_002820A0();
    p = D_0022C9A0;
    for (i = 0; i < 300; i++, p++) {
        if (p->t.owner != obj)
            continue;
        if (p->t.f30 < (p->t.f34 >> 1))
            scale = func_00283CE0(p->t.f30) / func_00283CE0((p->t.f34 >> 1));
        else
            scale = 1.0f;
        n = func_00283CF0(scale * 128.0f);
        s = func_00283180(p->t.f14);
        a = (s + 1.0f) * 0.5f;
        b = a * (scale * -0.025f);
        v[0] = v[1] = v[2] = s * 0.05f;
        func_00282CC0(v, v, p);
        func_002820D0((p->t.f18 + p->t.f18) * a, b, 0.08f, v, n, 0);
    }
    func_002820C8();
    for (p = D_0022C9A0; p < D_0022C9A0 + 300; p++)
        if (p->t.owner == obj)
            func_00329630((char *)p);
}
