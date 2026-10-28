/* func_002C94C8 - 560 bytes.  Worker attempt, 27 October 2026 (draft below).

   func_002C94C8: draft 540 B vs 560; needs own file src/game/002C94C8.c "-O2
   -G0 -ffunction-sections -g" (nop pair before div.s) and common.h (qcopy).
   Structure and calls match; remaining differences are float/int register
   assignment: retail keeps 1.0f in f20 (m[2][2]=1.0, divide numerator) and
   best in f21 (mov.s f21,f20); mine swaps them. Retail saved regs:
   s1=idx(reused for the table pointer), s4=p0, s7=p1, fp=out, s6=found, s3=i,
   s2=byte offset, s5=prev ptr. Tried: best assigned before/after the length
   call, table pointer assigned late (matches). */

typedef struct {
    int count;
    int pad[3];
    float pts[1][4];
} Polyline;

extern Polyline *D_001F1700[];
extern void func_00282CF0(float *out, float *a, float *b);
extern float func_00282DF0(float *v);
extern void func_00282F20(float *out, float *v, float s);
extern void func_00282C88(float *v);
extern void func_00283098(float *out, float *in, float *m);
extern void func_00282D08(float *out, float *a, float *b, float t);

int func_002C94C8(int idx, float *p0, float *p1, float *out)
{
    float m[3][4] __attribute__((aligned(16)));
    float prev[4] __attribute__((aligned(16)));
    float cur[4] __attribute__((aligned(16)));
    Polyline **tab;
    float best;
    float t;
    float len;
    int found = 0;
    int i;

    func_00282CF0(m[0], p1, p0);
    m[0][2] = 0.0f;
    best = 1.0f;
    len = func_00282DF0(m[0]);
    func_00282F20(m[0], m[0], 1.0f / len);
    func_00282C88(m[1]);
    m[1][0] = m[0][1];
    m[1][1] = -m[0][0];
    func_00282C88(m[2]);
    m[2][2] = 1.0f;
    tab = &D_001F1700[idx];
    func_00282CF0(prev, (*tab)->pts[0], p0);
    func_00283098(prev, prev, m[0]);
    for (i = 1; i < (*tab)->count; i++) {
        func_00282CF0(cur, (*tab)->pts[i], p0);
        func_00283098(cur, cur, m[0]);
        if (!(prev[3] == 0.0f && cur[3] == 0.0f)) {
            if (cur[1] * prev[1] < 0.0f) {
                t = (prev[0] - cur[0]) / (prev[1] - cur[1]) * -cur[1] + cur[0];
                if (t > 0.0f && t < best) {
                    best = t;
                    found = 1;
                }
            }
        }
        qcopy(prev, cur);
    }
    func_00282D08(out, p0, p1, best);
    return found;
}
