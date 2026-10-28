/* func_002BC508 - 596 bytes.  Worker attempt, 27 October 2026 (draft below).

   func_002BC508: draft 592 B vs 596. Needs own file src/game/002BC508-g8.c
   "-O2 -G8 -ffunction-sections -g" (gp floats D_001AA348/34C/33C/338/31C/318
   are sda floats; nop pair before div.s).
   Difference: float register allocation of the lerp: retail loads lo/hi into
   f0/f1 in each branch and keeps t in f12 (passed straight on to
   func_00283D38(t, s18, s14)); mine puts lo in f20 and t in f2 then `mov.s
   f12,f2`; also the D_001AA348 load is hoisted before `neg.s`. Rest of the
   control flow (bounds checks, func_00282978 test, h-- at the end) is as
   retail. */

extern void func_00282CC0(char *, char *, char *);
extern float func_00282DF0(char *);
extern void func_002AA548(char *out, float *res, float a, float b, float c, float d);
extern void func_00282F20(char *, char *, float);
extern float func_00283CE0(int);
extern int func_00283D38(float, int, int);
extern int func_00282978(short *);
extern void func_002B9180(char *);
extern float D_001AA348 __attribute__((sda));
extern float D_001AA34C __attribute__((sda));
extern float D_001AA33C __attribute__((sda));
extern float D_001AA338 __attribute__((sda));
extern float D_001AA31C __attribute__((sda));
extern float D_001AA318 __attribute__((sda));

void func_002BC508(char *o)
{
    char *s = o + 0x20;
    float len;
    float res[4];
    float t;
    float lo;
    float hi;
    float u;

    o[8] += s[0x1E];
    func_00282CC0(o + 0x10, o + 0x10, s);
    len = func_00282DF0(s);
    func_002AA548(o + 0x30, res, 0.0f, 0.0f, D_001AA348 * 0.00027777778f, -len);
    func_00282F20(s, s, -res[0]);
    *(float *)(o + 0x18) += D_001AA34C * 0.016666668f;
    t = func_00283CE0(*(short *)(o + 0xA)) / func_00283CE0((unsigned char)s[0x1D]);
    if (s[0x1F] & 1) {
        lo = D_001AA33C;
        hi = D_001AA338;
    } else {
        lo = D_001AA31C;
        hi = D_001AA318;
    }
    *(float *)(o + 0xC) = ((hi - lo) * t + lo) * 210000.0f;
    *(int *)(o + 4) = func_00283D38(t, *(int *)(s + 0x18), *(int *)(s + 0x14));
    if (*(short *)(o + 0xA) < 0xF) {
        u = func_00283CE0(*(short *)(o + 0xA)) / func_00283CE0(10);
        *(int *)(o + 4) = func_00283D38(u, *(int *)(o + 4) & 0xFFFFFF, *(int *)(o + 4));
    }
    if (*(float *)(o + 0x10) < 2.0f || *(float *)(o + 0x10) > 1021.0f ||
        *(float *)(o + 0x14) < 2.0f || *(float *)(o + 0x14) > 1021.0f ||
        *(float *)(o + 0x18) < 2.0f || *(float *)(o + 0x18) > 1021.0f) {
        func_002B9180(o);
        return;
    }
    if (func_00282978((short *)(o + 0xA)) != 0) {
        func_002B9180(o);
        return;
    }
    if (*(float *)(s + 0x10) < 0.01f)
        *(unsigned short *)(o + 0xA) -= 1;
}
