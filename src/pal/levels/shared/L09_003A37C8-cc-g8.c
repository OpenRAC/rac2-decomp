/* func_PAL_L09_003A37C8, the PAL copy of func_L09_003A01D8: the same C, where rename func_002C16C0 becomes func_PAL_002C23B8; rename func_002ABBB8 becomes func_PAL_002AC718. */
#include "common.h"

/* The level's resident spawn counters, in small data. */
/* Small data the run's step needs: the resident mode word (0x001A79F0), the level's
   release word (0x001A9040) and the level's record table (0x001B285C). */
extern void func_00282F20(void *dst, void *src, float scale);
extern float func_002A7878(float lo, float hi);
/* Small data: the query range, drop and radius are read $gp-relative; the two level weights
   and the toggle word are plain absolute loads (a weight load the scheduler moves into a delay
   slot comes out $gp-relative). */
extern float D_L09_001B2390 MACRO_ADDR;
extern float D_L09_001B238C MACRO_ADDR;
extern int D_L09_001B2388 MACRO_ADDR;

/* For joints 5 to 7: queries near D_00189EA0 when close enough, then spawns falling particles
   (two colours by the toggle word, then a third). While neither level weight is above 0.95
   and +0x31 is set, joints 3 and 4 also spawn particles along the +0xC0 vector. */
/* Steps the run: refreshes the object's frame, drops the record it still points at when
   the resident mode word says 9, and rebuilds the effect. */
/* The walks below read the group count through $gp; the group table of id lists is absolute
   and the entity base (the level's record table, D_L09_001B285C above through $gp) is the bare
   `lui`/`lw` pair here, a second name sized over 8 bytes with `sda` in this -G8 unit. */
/* Counts the class-0xD0F entities of the object's group whose private state has bit 0 of its
   byte at +0x302 clear and the word a1 at +0x420; -1 when a1 is 0. */
/* The largest word at +0x420 (0 at least) in the private states, whose byte at +0x302 is 0, of
   the class-0xD0F entities of the object's group. */
/* Re-arms the frame's four spawn slots, bumps the object's counter and re-runs the stage. */
/* func_PAL_L09_003A37C8: a 16-byte vector with a whole-quadword view, and the 0x28-byte impact
   request func_002A8C00 fills (attacker 0x10, flags 0x14, damage 0x1C, enabled 0x20 and the
   direction copied from its last argument). */
typedef int Quad_L09_003A01D8 __attribute__((mode(TI)));
typedef union {
    Quad_L09_003A01D8 q;
    float f[4];
} Vector_L09_003A01D8;

typedef struct {
    float direction[4];
    void *attacker;
    int flags;
    u8 kind;
    u8 mode;
    u16 object_class;
    float damage;
    int enabled;
    float unused24;
} Impact_L09_003A01D8;

#define I(p, o) (*(int *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))
#define P(p, o) (*(u8 **)((p) + (o)))

extern u8 *D_L09_001BFE58 NOT_SDA;
extern float D_L09_001A8F20[] MACRO_ADDR;
extern float func_00283B98(float angle, float step);
extern float func_00282DF0(void *v);
extern float func_002A7940(void);
extern int func_001163B0(void);
extern int func_00282948(void *a0);
extern void func_00282CC0(void *dst, void *a, void *b);
extern void func_00282CF0(void *dst, void *a, void *b);
extern void func_00283098(void *dst, void *src, void *matrix);
extern void func_00282D30(void *dst, void *src, float scale);
extern void func_002ACEC0(void *dst, void *src, void *matrix, float angle);
extern void *func_PAL_002C23B8(void *position, void *velocity, int a2, int a3, int color, int t1,
                           float f12, float f13, float f14, float f15, float f16);
extern void *func_002BD8B0(void *a0, void *a1, int a2, int a3, int a4, int a5, float f12);
extern void func_002A8C00(void *impact, int attacker, int flags, float damage, void *direction);
extern int func_002761F8(void *from, void *to, int a2, void *object, Impact_L09_003A01D8 *impact);
extern int func_00277258(void *position, int a1, void *object, float radius);
extern int func_00277F48(void *position, int a1, void *target, Impact_L09_003A01D8 *impact,
                         float scale);
extern void func_PAL_002AC718(void *owner, void *direction, void *position, float radius, float damage,
                          int sparks, int flashes, int smoke, float glow, float white, float cutoff,
                          float scale, int sound, float blast, int shake, int debris, int quality,
                          int channels, int flags);
extern int func_002E5CF8(int a0, int a1, void *object);
extern void func_0029F338(void *object);

/* Moves a projectile along its velocity (state = object +0x68, velocity at state +0x00),
   spinning +0xF0. Unless the level is busy on an odd frame it leaves a drifting trail particle
   and, on odd random draws, a spark. It then asks for an impact towards the owner
   (state +0x3C); on a hit against anything but the owner it explodes and deletes itself,
   otherwise it commits the predicted position. The trail vectors and the impact request share
   one stack area. */
void func_PAL_L09_003A37C8(u8 *object)
{
    struct {
        float predicted[4];
        union {
            struct {
                Vector_L09_003A01D8 point, velocity, axis;
            } effects;
            Impact_L09_003A01D8 impact;
        } payload;
    } f;
    u8 *state = P(object, 0x68), *hit;
    float length;
    int collision;
    int busy;

    if (object[0x20])
        return;
    F(object, 0xF0) = func_00283B98(F(object, 0xF0), 0.12566373f);
    func_00282CC0(f.predicted, object + 0x10, state);
    busy = D_L09_001B238C > 0.9f || D_L09_001B2390 > 0.9f;
    if (!busy || !(D_L09_001B2388 & 1)) {
        length = func_00282DF0(state);
        f.payload.effects.axis.q = 0;
        f.payload.effects.axis.f[0] = func_002A7878(-1.0f, 1.0f);
        f.payload.effects.axis.f[1] = func_002A7878(-1.0f, 1.0f);
        f.payload.effects.axis.f[2] = func_002A7878(-1.0f, 1.0f);
        f.payload.effects.velocity.q = f.payload.effects.axis.q;
        func_00282F20(f.payload.effects.velocity.f, f.payload.effects.velocity.f,
                      func_002A7878(0.04f, 0.08f) * 0.020000001f);
        func_00282D30(f.payload.effects.point.f, state, func_002A7878(0.2f, 0.99f));
        func_00282CC0(f.payload.effects.velocity.f, f.payload.effects.velocity.f,
                      f.payload.effects.point.f);
        func_00282F20(f.payload.effects.point.f, state, func_002A7878(0.0f, 1.0f) * length);
        func_00282CC0(f.payload.effects.point.f, f.payload.effects.point.f, object + 0x10);
        func_PAL_002C23B8(object + 0x10, f.payload.effects.velocity.f, 6, 127, 0xB0B0B0, 3,
                      40000.0f, 1000.0f, 1.0f, -0.00039999998989515007f, 0.0f);
        f.payload.effects.axis.q = 0;
        f.payload.effects.axis.f[2] = 0.01f;
        func_00283098(f.payload.effects.axis.f, f.payload.effects.axis.f, object + 0xC0);
        func_002ACEC0(f.payload.effects.axis.f, f.payload.effects.axis.f, object + 0xC0,
                      func_002A7940());
        if (func_001163B0() & 1)
            func_002BD8B0(f.payload.effects.point.f, f.payload.effects.axis.f, 0x4F007FFF,
                          0x1FFFFFFF, 11, 1, 25000.0f);
    }
    func_002A8C00(&f.payload.impact, I(state, 0x3C), 0x10001, F(state, 0x40), state);
    f.payload.impact.object_class = *(u16 *)(object + 0xAA);
    func_00282CF0(f.payload.impact.direction, object + 0x10, P(state, 0x3C) + 0x10);
    f.payload.impact.direction[2] = 0.0f;
    func_00282F20(f.payload.impact.direction, f.payload.impact.direction, 2.0000002f);
    f.payload.impact.direction[3] = 5627.9248046875f;
    f.payload.impact.enabled |= 1;
    f.payload.impact.kind = 4;
    collision = func_002761F8(object + 0x10, f.predicted, 0, object, &f.payload.impact);
    if (collision || func_00277258(object + 0x10, 1, object, 0.3f)
        || func_00282948(state + 0x38)) {
        hit = D_L09_001BFE58;
        if (hit) {
            if (hit == P(state, 0x3C)) {
                qcopy(object + 0x10, f.predicted);
                return;
            }
            if (*(short *)(hit + 0xAA) != 0x4E)
                func_00277F48(object + 0x10, 0, P(state, 0x3C), &f.payload.impact, 0.5f);
            /* The calls are written out per arm: a call ending a block that falls into a label
               gets a (use 0) from flow, which stops jump2 from cross-jumping the tails. */
            func_PAL_002AC718(object, D_L09_001A8F20, 0, 0.0f, 0.0f, 0, 2, 10, 0.0f, 0.0f, 9.0f,
                          0.666f, -1, 0.0f, 0, 1, -1, 0, 0x810001);
            func_002E5CF8(0, 0, object);
            func_0029F338(object);
        } else {
            func_PAL_002AC718(object, D_L09_001A8F20, 0, 0.0f, 0.0f, 0, 2, 8, 0.0f, 0.0f, 9.0f,
                          0.5f, -1, 0.0f, 0, 1, -1, 0, 0x810001);
            func_002E5CF8(0, 0, object);
            func_0029F338(object);
        }
    } else
        qcopy(object + 0x10, f.predicted);
}

#undef I
#undef F
#undef P
