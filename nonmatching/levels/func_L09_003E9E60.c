/* func_L09_003E9E60 - 504 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   003E9EF0  addiu       $a1, $s1, 0x104              | mov.s       $f12, $f21
     003E9EF8  daddu       $a2, $zero, $zero            | addiu       $a1,
   $s1, 0x104
     003E9F00  mov.s       $f12, $f21                   | daddu       $a2,
   $zero, $zero
     003E9FD4  swc1        $f0, 0x10($sp)               | lwc1        $f13,
   0x70($s1)
     003E9FDC  mov.s       $f12, $f22                   | lwc1        $f14,
   0x74($s1)
     003E9FE0  lwc1        $f13, 0x70($s1)              | mov.s       $f12,
   $f22
     003E9FE4  lwc1        $f14, 0x74($s1)              | lwc1        $f15,
   0x78($s1)
     003E9FEC  lwc1        $f15, 0x78($s1)              | swc1        $f0,
   0x10($sp)
   func_L09_003E9E60: 0 of 2 places match (src/levels/shared/L09_003E9E60-g.c)
   masked diff lines: 8
   Size 504 ok in -g unit (new file flags: -O2 -G0 -ffunction-sections -g,
   needed for the nop pair before div.s). Remaining 8 masked lines are
   scheduling only: (1) mov.s f12,f21 vs addiu a1 order in the first
   func_002AAA00 call, (2) retail has swc1 f0,0x10(sp) (len) in the delay slot
   of the func_002AAC80 call after the arg loads; with -g mine stores it
   before the loads (line note between `len = ...` and the call). Without -g
   that region matches but the nop pair is missing (500 vs 504). Tried same-
   line statements, no effect. */

extern void func_00282CC0(char *first, char *second, char *third);
extern void func_00282F20(char *dst, char *src, float x);
extern float func_00283248(float x, float y);

extern void func_00282CF0(char *dst, char *a, char *b);
extern void func_00282FB8(char *dst, char *src, float x);
extern float func_002AAA00(char *a, char *b, int c, float d, float e, float f, float g);
extern float func_00283C80(float a, float b);
extern float func_002A7798(float x);
extern float func_00283B98(float a, float b);
extern float func_00282DF0(char *v);
extern void func_002AAC80(float *v, float a, float b, float c, float d);
typedef struct {
    char pad[0x80];
    float f80;
    float f84;
} D00189E20_View;

extern D00189E20_View D_00189E20;

int func_L09_003E9E60(char *object, void *buf, float f) {
    char *state = *(char **)(object + 0x68);
    int result = 1;

    if (*(short *)(state + 0x118) != -1) {
        float vec[4];
        float len;
        float dist;
        float t = 1.0f;
        char *dir;

        func_00282CF0((char *)vec, buf, object + 0x10);
        func_00282FB8((char *)vec, (char *)vec, *(float *)(state + 0x78));
        dist = func_00283248(vec[0], vec[1]);
        if (*(unsigned char *)(object + 0x20) < 4) {
            func_002AAA00(object + 0xF8, state + 0x104, 0, dist, *(float *)(state + 0x64),
                          *(float *)(state + 0x68), *(float *)(state + 0x6C));
            t = func_00283C80(dist, *(float *)(object + 0xF8)) / *(float *)(state + 0x80);
            if (t > 1.0f) {
                t = 1.0f;
            } else if (t < 0.0f) {
                t = 0.0f;
            }
            t = func_002A7798(1.0f - t);
        } else {
            char *q = object + 0xF8;

            dist = func_00283B98(func_00283248(D_00189E20.f80 - *(float *)(object + 0x10),
                                               D_00189E20.f84 - *(float *)(object + 0x14)),
                                 1.5707964f);
            func_002AAA00(q, state + 0x104, 0, dist, *(float *)(state + 0x64),
                          *(float *)(state + 0x68), *(float *)(state + 0x6C));
        }
        dir = state + 0xF0;
        len = func_00282DF0(dir); func_002AAC80(&len, f, *(float *)(state + 0x70), *(float *)(state + 0x74), *(float *)(state + 0x78));
        len = len * t;
        func_00282F20(dir, (char *)vec, len);
        func_00282CC0(object + 0x10, object + 0x10, dir);
        if (*(short *)(state + 0x118) != *(short *)(state + 0x11A))
            result = 0;
    }
    return result;
}
