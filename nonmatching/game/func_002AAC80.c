/* func_002AAC80 - 528 bytes.  Worker attempt, 27 October 2026 (draft below).

   draft is 516 B vs 528. Control flow is right (decoded block by block).
   Diffs: retail keeps *velocity in $f12 (mov.s f12,f0 after the lwc1, used by
   mul/else branch), mine uses $f1; retail has "nop" in bc1t delay slot and
   "mov.s f12,f21; nop; nop" before div.s (mine none) so +2-3 insns.
   Tried: float v=*velocity local (used in v*target, v*v, else branch),
   modifying v then storing: size got worse (492).
   Callees: func_00282C48 fabs, func_00282C10 sqrt, func_002AA2E8(float
   *value, float target, float step) approach. */

/* in src/game/002AA800.c (-ffast-math -g) replacing the INCLUDE_ASM; func_00282C48 is already declared there */
extern float func_002AA2E8(float *value, float target, float step);
extern float func_00282C10(float x);

void func_002AAC80(float *velocity, float target, float accel, float damping, float limit)
{
    float stop;
    float mag;
    float v;

    if (target == 0.0f && *velocity == 0.0f)
        return;
    v = *velocity;
    if (v * target >= 0.0f && target != 0.0f) {
        stop = v * v / damping * 0.5f;
        if (func_00282C48(target) < stop) {
            mag = func_00282C48(target) + func_00282C48(*velocity);
            if (stop < mag)
                func_002AA2E8(velocity, 0.0f, damping);
            else
                func_002AA2E8(velocity, 0.0f, damping * 1.1f);
        } else {
            mag = func_00282C10((damping + damping) * target);
            if (limit < mag)
                mag = limit;
            if (target < 0.0f)
                func_002AA2E8(velocity, -mag, accel);
            else
                func_002AA2E8(velocity, mag, accel);
        }
        if (func_00282C48(*velocity) < func_00282C48(target))
            return;
        *velocity = target;
    } else {
        if (*velocity >= 0.0f)
            *velocity -= damping;
        else
            *velocity += damping;
        if (target < 0.0f) {
            if (*velocity < target)
                *velocity = target;
        } else if (target > 0.0f) {
            if (target < *velocity)
                *velocity = target;
        }
    }
}
