/* functional: high. Same calls, arguments, reads and writes as retail; the 16-byte lq/sq copy of the old angles (+0x30) is four word copies on the stack. The clamp compares the value just stored, as retail does. */

/* Per-frame orientation update of a vehicle/camera owner: when its state (func_002EE6A8) is 8 or 9, the
 * owner's basis rows (+0xC0, +0xE0, +0xD0) come from the camera matrix D_001B5390 (the first scaled by the
 * object's +0x140, the others negated). Otherwise it recomputes pitch (+0x34) and yaw (+0x38) from the
 * direction at +0x90, then in states 2 and 12 eases the matrix at +0x40 toward the new rotation (0.0125) and
 * uses it; in the others it banks the roll (+0x30: 0.98 decay plus the yaw change times D_001AC244, clamped to
 * +-1.4137167) and builds the basis from the angles. */

extern char *func_002ED688(unsigned char *);
extern int func_002EE6A8(unsigned char *);
extern float func_00282E20(void *);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern float func_00283C80(float, float);
extern void func_002A91F0(void *, void *);
extern void func_00283810(void *, void *, void *, float);
extern void func_00283958(void *, void *);
extern void func_00282F20(void *, void *, float);
extern float D_001AC244;
extern char *D_001B5390;

void func_002EE000(unsigned char *owner)
{
    char *o = func_002ED688(owner);
    float old[4] __attribute__((aligned(16)));
    float temp[4] __attribute__((aligned(16)));
    float sign, a, b, roll;
    int i;

    if (o == 0)
        return;
    if (func_002EE6A8(owner) == 8 || func_002EE6A8(owner) == 9) {
        char *p = D_001B5390;
        func_00282F20(owner + 0xC0, p + 0x10, *(float *)(o + 0x140));
        func_00282F20(owner + 0xE0, p, -1.0f);
        func_00282F20(owner + 0xD0, p + 0x20, -1.0f);
        return;
    }
    for (i = 0; i < 4; i++)
        old[i] = ((float *)(o + 0x30))[i];
    a = func_00282E20(o + 0x90);
    sign = 1.0f;
    *(float *)(o + 0x34) = -func_00283248(a, *(float *)(o + 0x98));
    *(float *)(o + 0x38) = func_00283248(*(float *)(o + 0x90), *(float *)(o + 0x94));
    if (func_00283BE0(*(float *)(o + 0x38), old[2]) < 0.0f)
        sign = -1.0f;
    b = func_00283C80(old[2], *(float *)(o + 0x38));
    if (func_002EE6A8(owner) != 2 && func_002EE6A8(owner) != 12) {
        roll = *(float *)(o + 0x30) * 0.98f + ((b * -sign) * (D_001AC244 * 1.4137166738510132f)) * 8.0f;
        *(float *)(o + 0x30) = roll;
        if (1.4137166738510132f < roll)
            *(float *)(o + 0x30) = 1.4137166738510132f;
        else if (roll < -1.4137166738510132f)
            *(float *)(o + 0x30) = -1.4137166738510132f;
        func_002A91F0(temp, o + 0x30);
        func_00283958(temp, owner + 0xC0);
    } else {
        func_002A91F0(temp, o + 0x30);
        func_00283810(o + 0x40, o + 0x40, temp, 0.0125f);
        func_00283958(o + 0x40, owner + 0xC0);
    }
}
