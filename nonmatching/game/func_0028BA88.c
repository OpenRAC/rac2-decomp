/* func_0028BA88 - 460 bytes.  Worker attempt, 27 October 2026 (draft below).

   func_0028BA88: draft 456 B vs 460, rest of the function matches in
   structure (first ~25 and last ~40 instructions identical).
   Differences: (1) abs: retail does `subu v0,a1,a0; bgez v0,L; move s0,v0
   (delay); negu s0,s0` (branch), the compiler makes `movz/movn` for every abs
   spelling tried (if/neg, ternary, separate diff var). (2) max(v, d/5):
   retail `slt a0,v0,a1; movz a1,v0,a0`, mine `slt v0,a1,a0; movn a1,a0,v0`.
   (3) after the abs the rest is shifted by these. Draft is in place-ready
   form (functions already declared in 00288D88.c: func_00283CE0,
   func_00283CF0). */

extern float func_00283CE0(int);
extern float func_00282C10(float);
extern int func_00283CF0(float);
extern void func_0028DF80(char *);

void func_0028BA88(char *o)
{
    int *c = *(int **)(o + 0xC);
    unsigned char *acc = (unsigned char *)(o + 0x70);
    int v;
    int d;
    int diff;
    int m;
    int step;
    int k;

    if (c != 0) {
        v = *c;
        if (v < 0)
            v = 0;
        *(int *)(o + 0x78) = v;
        if (*(int *)(o + 8) < v)
            *(int *)(o + 0x78) = *(int *)(o + 8);
    }
    if (*(int *)(o + 0x74) != *(int *)(o + 0x78)) {
        *(int *)(o + 0x7C) = 0xB4;
        if (*(int *)(o + 0x6C) >= 0x18) {
            diff = *(int *)(o + 0x74) - *(int *)(o + 0x78);
            d = diff;
            if (diff < 0)
                d = -d;
            if (d != 0) {
                v = func_00283CF0(func_00282C10(func_00283CE0(d) * 0.04f) * 5.0f);
                m = d / 5;
                step = v >= m ? v : m;
                if (step < 0x7A) {
                    if (step <= 0)
                        step = 1;
                } else {
                    step = 0x79;
                }
                acc[3] += step;
                if (acc[3] >= 3) {
                    k = acc[3] >> 1;
                    if (*(int *)(o + 0x78) < *(int *)(o + 0x74))
                        *(int *)(o + 0x74) -= k;
                    else
                        *(int *)(o + 0x74) += k;
                    acc[3] -= k * 2;
                }
            }
        }
    }
    if (*(int *)(o + 0x7C) < 5) {
        if (acc[1] != 0 || acc[0] != 0)
            *(int *)(o + 0x6C) = 1;
        if (acc[1] != 0)
            acc[1]--;
        else if (acc[0] != 0)
            acc[0]--;
    } else if (acc[0] < 8) {
        acc[0]++;
    } else if (acc[1] < 8) {
        acc[1]++;
    }
    func_0028DF80(o + 0x40);
}
