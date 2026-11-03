#include "common.h"

extern void func_002AB8C0(u8 *a0, void *a1);

extern void func_00282978(void *a0);

extern void func_002A7470(u8 *a0, u32 a1, u32 a2, u32 a3);

extern void func_002AEC48(u8 *a0, void *a1, f32 f12, f32 f13, s32 a2);

extern void func_002B0990(u8 *a0, void *a1, f32 f12, s32 a2, s32 a3);

extern void *D_L11_001FC420[];

extern u8 *D_L11_001B359C[] __attribute__((sda));

extern void func_0029FCC0(u32 a0, s32 a1, f32 *a2);

extern f32 func_00283180(f32 a0);

extern f32 func_00283198(f32 a0);

extern void func_00282CC0(f32 *a0, f32 *a1, f32 *a2);

extern void func_L11_00431EE8(u8 *a0, f32 *a1);

extern void func_L11_004320F8(u8 *a0, f32 *a1);



/* func_L11_00425F10 lives in L11_00425F10-g-g8.c (-G8 -g: it reaches level globals
   through $gp and needs the -g line labels before its divisions). */

/* func_L11_004295A0 lives in L11_00425F10-g8.c (it reaches level globals through $gp). */

extern float func_00282DF0(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_L02_0032E998(void *, void *, void *, void *, int, void *, void *, f32, f32);
extern void func_002AAA00(void *, f32, f32, f32, f32, void *, int);
extern f32 func_00283C80(f32, f32);
extern void func_002AA548(void *, void *, f32, f32, f32, f32);
extern f32 func_002AA2E8(f32 *, f32, f32);
extern void func_00282F20(void *, void *, f32);
extern int func_002A7EA0(void *, void *, void *, f32, f32, f32, f32, int);

/* Same body as func_L04_00450D50, with this function's own callees. */
int func_L11_0042A158(u8 *object, void *target, f32 desiredHeading, f32 speed, f32 stopDistance, f32 margin) {
    f32 delta[4], displacement[4], destination[4];
    f32 angle, frameSpeed = 0.0f;
    u8 *data = *(u8 **)(object + 0x68);
    int done = 0;
    f32 distance, acceleration;
    func_00282CF0(delta, target, object + 0x10);
    delta[2] = 0.0f;
    distance = func_00282DF0(delta);
    acceleration = speed * 0.0008333333535119891f;
    if (stopDistance < distance) {
        int collision = *(int *)(data + 0x520);
        angle = 0.0f;
        func_L02_0032E998(object + 0x10, target, &angle, data + 0x320, collision, data + 0x530, data + 0x534, margin, 0.4f);
        func_002AAA00(object + 0xF8, angle, 0.006981317885220051f, 0.0034906589426100254f, 0.20943954586982727f, data + 0x27C, 0);
        if (func_00283C80(*(f32 *)(object + 0xF8), angle) < 0.523598849773407f) {
            func_002AA548(&frameSpeed, data + 0x538, distance, acceleration, acceleration, speed * 0.01666666753590107f);
        } else {
            *(f32 *)(data + 0x538) = 0.0f;
        }
    } else {
        func_002AAA00(object + 0xF8, desiredHeading, 0.006981317885220051f, 0.2f, 0.20943954586982727f, data + 0x27C, 0);
        func_002AA2E8((f32 *)(data + 0x538), 0.0f, acceleration);
        if (*(f32 *)(data + 0x538) == 0.0f && func_00283C80(*(f32 *)(object + 0xF8), desiredHeading) < 0.0872664749622345f) {
            *(f32 *)(data + 0x27C) = 0.0f;
            done = 1;
        }
    }
    func_00282F20(displacement, object + 0xC0, *(f32 *)(data + 0x538));
    func_00282CC0(destination, displacement, object + 0x10);
    if (!func_002A7EA0(object, object + 0x10, destination, 0.75f, 0.75f, 0.4f, 0.523598849773407f, 0))
        *(int *)(data + 0x53C) += 1;
    if (*(int *)(data + 0x53C) >= 30) {
        *(int *)(data + 0x53C) = 0;
        done = 1;
    }
    return done;
}

/* Same preparation as func_L11_00431D50 with the class setup on 0x260 and a two-stage
   animation seeded on 0x2A0. */
void func_L11_0042A420(u8 *arg0) {
    u8 *s0 = *(u8 **)(arg0 + 0x68);

    func_002AB8C0(arg0, s0 + 0x50);
    func_00282978(s0 + 0x260);
    func_00282978(s0 + 0x26);
    if (*(u16 *)(arg0 + 0x96) <= 0xFFFE)
        (*(u16 *)(arg0 + 0x96))++;
    func_002AEC48(arg0, s0 + 0x2A0, 0.03f, 0.3f, 4);
    func_002B0990(arg0, s0 + 0x2A0, 3.5f, 4, 1);
}

void func_L11_0042A4C8(u8 *arg0) {
    void *list;
    u16 *p;
    u8 *rec;
    u8 *owner;
    u8 *base;

    if (arg0[0x21] == 0xFF)
        return;
    list = D_L11_001FC420[arg0[0x21]];
    arg0 = *(u8 **)(arg0 + 0x68);
    if (list == 0)
        return;
    base = D_L11_001B359C[0];
    p = list;
    do {
        rec = base + ((*p & 0x7FFF) << 8);
        if (*(s8 *)(rec + 0x20) >= 0 && *(s16 *)(rec + 0xAA) == 0xCF6) {
            owner = *(u8 **)(rec + 0x68);
            *(u16 *)(owner + 0x266) = 1;
            (*(u32 *)(owner + 0x560))++;
        }
        if (*(s8 *)(rec + 0x20) >= 0 && *(s16 *)(rec + 0xAA) == 0xCF5) {
            owner = *(u8 **)(rec + 0x68);
            *(u16 *)(owner + 0x266) = 1;
            (*(u32 *)(owner + 0x560))++;
            if (*(f32 *)(arg0 + 0x20) <= 0.0f)
                (*(u32 *)(owner + 0x584))++;
        }
    } while (*(s16 *)p++ >= 0);
}

extern char D_L11_001BA8C0[];
extern float func_002A7878_range(float, float) __asm__("func_002A7878");
extern int func_002A77E0(int);
extern float func_002A78D8(float, float);
extern void func_002ACEC0(void *, void *, void *, float);
extern char *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern int func_00283CF0(float);

/* Emits paired particles with opposite spin and randomized velocities. */
void func_L11_0042A5B0(float *pos, int count) {
    float velocity[4], origin[4], direction[4], axis[4], offset[4];
    float size, angle;
    int i;
    int sign;
    char *particle;
    func_00282CF0(direction, (float *)D_L11_001BA8C0, pos);
    func_00282F20((char *)offset, (char *)direction, 0.3f);
    direction[2] = 0;
    axis[0] = 0;
    axis[1] = 0;
    axis[2] = 1.0f;
    axis[3] = 1.0f;
    for (i = 0; i < count; i++) {
        size = func_002A7878_range(0.5f, 2.0f);
        sign = func_002A77E0(2);
        if (!sign) sign--;
        angle = func_002A7878_range(-1.0471977f, 1.0471977f);
        func_002ACEC0(velocity, direction, axis, angle);
        func_00282F20((char *)velocity, (char *)velocity, func_002A7878_range(0.05f, 3.0f) * 0.0166666675f);
        velocity[2] = func_002A7878_range(1.0f, 5.0f) * 0.0166666675f;
        func_00282CC0(origin, pos, offset);
        pos[0] += func_002A78D8(0, 0.15f);
        pos[1] += func_002A78D8(0, 0.15f);
        pos[2] += func_002A78D8(0, 0.15f);
        particle = func_002C2210(origin, 60, size * 0.1f, size, 0x7F207F7F, 0, sign, velocity, 0, 0.002f);
        if (particle) particle[9] = func_00283CF0(4.0f) + 0x70;
        particle = func_002C2210(origin, 60, size * 0.07f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        if (particle) particle[9] = func_00283CF0(4.0f) + 0x70;
    }
}


/* Applies the class setup to this object and its owner, or to this object alone when they
   are the same. */
void func_L11_0042EF90(u8 *arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4) {
    u8 *s2 = *(u8 **)(arg0 + 0x68);

    if (*(u32 *)(s2 + 0x27C) != 0) {
        func_002A7470(arg0, arg1, arg3, arg4);
        func_002A7470(*(u8 **)(s2 + 0x27C), arg2, arg3, arg4);
    } else if (arg0[0x43] != arg1) {
        func_002A7470(arg0, arg1, arg3, arg4);
    }
}


/* func_L11_00431860 lives in L11_00431860-g8.c. */

/* Runs the class setup on the sub-record, unmarks two state halfwords and steps the timer. */
void func_L11_00431D50(u8 *arg0) {
    u8 *s0 = *(u8 **)(arg0 + 0x68);

    func_002AB8C0(arg0, s0 + 0x50);
    func_00282978(s0 + 0x270);
    func_00282978(s0 + 0x272);
    if (*(u16 *)(arg0 + 0x96) <= 0xFFFE)
        (*(u16 *)(arg0 + 0x96))++;
}

/* func_L11_00431DB0 lives in L11_00425F10-g8.c (it reaches D_L11_001B359C
   through $gp). */

/* Builds the object's follow vector from the renderer's position, offsets its height and
   hands it to the two transform helpers. */
void func_L11_00431E30(u8 *arg0) {
    u8 *s0 = arg0;
    u8 *s1 = *(u8 **)(s0 + 0x68);
    u8 *p = *(u8 **)(s1 + 0x27C);
    u8 *q;
    f32 v[3];
    f32 w[3];

    if (p == 0)
        return;
    q = *(u8 **)(p + 0x68);
    func_0029FCC0(*(u32 *)(q + 0x278), 0, v);
    w[0] = func_00283180(*(f32 *)(s0 + 0xF8)) * 0.1f;
    w[1] = func_00283198(*(f32 *)(s0 + 0xF8)) * 0.1f;
    w[2] = 0.0f;
    func_00282CC0(v, v, w);
    v[2] = v[2] - 0.05f;
    func_L11_00431EE8(s0, v);
    func_L11_004320F8(s0, v);
}

