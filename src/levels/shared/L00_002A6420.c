#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

extern void hero_play_footstep_sound_dust(int arg0, int arg1, int arg2, int arg3);

extern void func_002E6CF0(void *routine, void *state);

extern void func_00323270(void *a0, void *a1, void *a2, float f12, float f13, float f14);

extern void DrawHeroGlowQuads();

extern int func_L00_002B3998_1(float value);

#ifndef RAC2_T_RESIDENTSTATE_FD160FB9C
#define RAC2_T_RESIDENTSTATE_FD160FB9C
typedef struct {
    u8 pad000[0x1b8];
    int f1B8;
    u8 pad1bc[0x222 - 0x1bc];
    short s222;
    u8 pad224[0xc2c - 0x224];
    int fC2C;
    u8 padc30[0x149d - 0xc30];
    u8 b149D;
    u8 pad149e[0x2290 - 0x149e];
    u8 *p2290;
    int f2294;
    u8 pad2298[0x22b8 - 0x2298];
    u8 b22B8;
    u8 pad22b9[0x22bb - 0x22b9];
    u8 b22BB;
    u8 pad22bc[0x22bf - 0x22bc];
    u8 b22BF;
    u8 pad22c0[0x24ec - 0x22c0];
    short s24EC;
} ResidentState_Fd160fb9c;
#endif

extern ResidentState_Fd160fb9c D_00189E20_16;

extern int D_001A79F0_3 __attribute__((sda));

extern int func_L00_002D67A8_1(int);

extern char D_00189E20_2[];

extern float ApproachValue(float *p, float a, float b);

extern char D_00189E20_24[];

extern int func_00283CF0_6(float value);

extern float SplitFloatFraction(float *buffer, float value);

#ifndef RAC2_T_V4_FBFDC087A
#define RAC2_T_V4_FBFDC087A
typedef int V4_Fbfdc087a __attribute__((mode(TI)));
#endif

extern char D_00189EB0[];

extern void func_00283410_9(float *m, char *p);

extern void func_002830C0_8(float *dst, float *src, float *m);

extern void func_00283788_6(float *m, float *m2, float *e);

extern void func_00282CF0_14(float *c, float *a, float *b);

extern void func_00282CC0_29(char *a, char *b, float *c);

extern void func_002AB6D8_4(float *m, char *p);

extern void func_00282C88_2(void *);

extern void func_L00_002A9FE8_1(void *, float, float, float);

extern unsigned char D_0018C0D4[];

#ifndef RAC2_T_S36_F39E097FB
#define RAC2_T_S36_F39E097FB
typedef struct { int w[9]; } S36_F39e097fb;
#endif

extern int D_0018C0B0_1;

extern char D_0018AA70[];

extern S36_F39e097fb D_L00_001A7F68;

extern void func_L00_003116A8_1(int, int, S36_F39e097fb *, char *);

extern char D_00189E20_20[];

extern float func_002A7878_6(float a0, float a1);

extern void part_spawn_drifting(float *a0, float *a1, int a2, float a3, float a4);

extern int func_002A77E0_2(char *a0);

extern void hero_build_relative_offset(char *target, int mode, float value, float zero, float scale);

extern int func_002761F8_2(char *first, char *second, int mode, int flag, int extra);

extern float func_00282E48_4(char *source, short *table);

extern float fast_vec_dist(void *source, void *table);

extern int moby_is_in_special_class_range(void *object);

extern int hero_slot_item_id(int index);

extern void *D_L00_001BF218;

#ifndef RAC2_T_HEROBLOCK_2AB1D8
#define RAC2_T_HEROBLOCK_2AB1D8
typedef struct {
    u8 pad000[0x1e4];
    float f1E4;
} HeroBlock_2ab1d8;
#endif

extern HeroBlock_2ab1d8 g_hero_position;

extern short D_L00_001BF220_2[];

extern float D_0018A084;


typedef int s32;

typedef float f32;

extern void hero_build_relative_point(f32, f32, f32, f32 *, s32);

typedef unsigned int u32;

extern u8 D_00189E20_1[];

typedef struct {
    u8 prefix[0x1220];
    u32 field1220;
    u8 gap[0x20];
    s32 field1244, field1248;
} NativeIndexedFieldsView;

typedef struct {
    u8 pad0000[0x2294];
    u32 kind;
    u32 unknown2298;
    u32 mode;
} ResidentFlags2294;

/* Reads a resident mode word and the kind byte of a pointer field, then for kind 3, 4 or 20 tests two float thresholds through a predicate and triggers a four-argument action with selector zero or one. */
void hero_check_targeting_triggers(void)
{
    int selector;

    if (D_00189E20_16.f2294 == 2) {
        if (D_00189E20_16.f1B8 < 15)
            return;
    }

    selector = D_00189E20_16.b149D;

    if (D_00189E20_16.f2294 == 2) {
        if (D_00189E20_16.f1B8 == 22)
            hero_play_footstep_sound_dust(selector, 0, 1, 30);
    }

    switch (D_00189E20_16.p2290[67]) {
    case 3:
        if (D_00189E20_16.fC2C != 0)
            return;
        if (func_L00_002B3998_1(49.5f) != 0)
            hero_play_footstep_sound_dust(selector, 0, 1, 30);
        if (func_L00_002B3998_1(17.0f) != 0)
            hero_play_footstep_sound_dust(selector, 1, 1, 30);
        return;
    case 4:
        if (D_00189E20_16.fC2C != 0)
            return;
        if (func_L00_002B3998_1(12.5f) != 0)
            hero_play_footstep_sound_dust(selector, 0, 1, 30);
        if (func_L00_002B3998_1(1.0f) != 0)
            hero_play_footstep_sound_dust(selector, 1, 1, 30);
        return;
    case 20:
        if (D_00189E20_16.fC2C != 0)
            return;
        if (func_L00_002B3998_1(8.0f) != 0)
            hero_play_footstep_sound_dust(selector, 0, 1, 30);
        if (func_L00_002B3998_1(21.0f) != 0)
            hero_play_footstep_sound_dust(selector, 1, 1, 30);
        return;
    }
}




/* reads a global mode value; for 8, 9 or 19 probes two engine queries and returns 1 if either reports true, else 0 */
int hero_is_in_swing_or_grind_mode(void)
{
    int v = D_001A79F0_3;
    int r = 0;
    if (v >= 8) {
        if (v < 10 || v == 19) {
            if (func_L00_002D67A8_1(1) != 0 || func_L00_002D67A8_1(2) != 0)
                r = 1;
        }
    }
    return r;
}

/* shared native body of family 0be97c76a107 */
/* Gives each of the seven weapon slot objects the same 8 bytes from the hero object. */
void hero_copy_color_to_slot_objects(void)
{
    char *hero = D_00189E20_2;
    int slot, part;

    for (slot = 0; slot < 7; slot++) {
        for (part = 0; part < 3; part++) {
            char *slotObject = *(char **)(hero + 4640 + slot * 80);

            if (part == 1)
                slotObject = *(char **)(hero + 4644 + slot * 80);
            else if (part == 2)
                slotObject = *(char **)(hero + 4648 + slot * 80);
            if (slotObject != 0)
                *(long long *)(slotObject + 56) = *(long long *)(*(char **)(hero + 8848) + 56);
        }
    }
}

/* Does nothing. */
void hero_empty_hook(void)
{
}

/* func_L00_002A70F8 is defined in L00_002A70F8-glow.c. */

/* func_L00_002A74A8 is defined in L00_002A74A8-tint.c. */


/* runs a three-float setup over two resident blocks when the mode is 124, then publishes a
   height once two resident flags are clear */
void hero_update_model_wobble(void)
{
    char *hero = D_00189E20_2;

    if (*(int *)(hero + 0x2294) == 124)
        func_00323270(*(void **)(hero + 0x2290), hero + 0x7B0, hero + 0x7B4,
                      0.174532949924469f, 0.02617994323372841f, 0.03490659222006798f);
    if (*(short *)(hero + 0x6BC) == 0)
        return;
    if (*(int *)(hero + 0x660) != 0)
        return;
    *(float *)(*(char **)(hero + 0x2290) + 0xF4) = *(float *)(hero + 0x6B0);
}

/* func_L00_002A7748 is defined in L00_002A7748.c. */

/* func_L00_002A7958 is matched in its own unit, src/levels/shared/L00_002A7958-g8.c (-O2 -G8 -ffunction-sections). */

/* raises the pending flag once: registers an update routine with the resident pointer */
void hero_queue_glow_draw_routine(void)
{
    char *hero = D_00189E20_2;

    if (*(short *)(hero + 0x2162) == 0) {
        *(short *)(hero + 0x2162) = 1;
        func_002E6CF0(DrawHeroGlowQuads, *(void **)(hero + 0x2290));
    }
}

/* func_L00_002A7A50 is defined in L00_002A7A50-glow.c. */

/* func_L00_002A9460 is defined in L00_002A9460.c. */

/* func_L00_002A9600 uses the quadword-copy profile in L00_002A9600-qcopy.c. */

/* func_L00_002A9760 is defined in L00_002A9760-g8.c. */

/* Clamps two float fields of one object into [-1,1] through a repeated helper call and copies the clamped values into a second object. */
void pad_clamp_stick_to_unit_range(float *outValues, float *stick, float rate)
{
    char *base = D_00189E20_2;
    float target[2];

    target[0] = -*(float *)(base + 8112);
    target[1] = *(float *)(base + 8116);
    ApproachValue(stick + 2, target[0], rate);
    if (stick[2] > 1.0f) stick[2] = 1.0f;
    if (stick[2] < -1.0f) stick[2] = -1.0f;
    outValues[0] = stick[2];
    ApproachValue(stick + 1, target[1], rate);
    if (stick[1] > 1.0f) stick[1] = 1.0f;
    if (stick[1] < -1.0f) stick[1] = -1.0f;
    outValues[1] = stick[1];
}

/* func_L00_002A9E30 is defined in L00_002A9E30-retime.c. */

/* blends two table entries by the fractional part of a clock value: the integer part is the index, one step back is wrapped over a count unless a flag selects the last slot, and the result is frac*table[index] + (scale-frac)*table[previous] */
float math_blend_table_entries_by_clock(float *table, int count)
{
    char *hero = D_00189E20_24;
    float scratch[4];
    float fraction;
    int index;
    int last;
    int previous;
    index = func_00283CF0_6(*(float *)(hero + 3128));
    last = count - 1;
    previous = (index + last) % count;
    if (*(int *)(hero + 3112) & 2)
        previous = last;
    fraction = SplitFloatFraction(scratch, *(float *)(hero + 3128));
    return fraction * table[index] + (*(float *)(hero + 3132) - fraction) * table[previous];
}

/* Copies a 16-byte block pointed to by the first argument into a stack buffer, stores the three float arguments into a 16-byte stack vector, fills two 64-byte matrices through helper routines, applies copies of the buffer through them into two more 16-byte stack vectors, and finishes by passing the destination, the source and a composed vector to a closing routine. */
void hero_offset_pose_by_vector(V4_Fbfdc087a *src, float x, float y, float z)
{
    char *p = D_00189EB0;
    float q[4];
    float a[4];
    float b[4];
    float c[4];
    float m[16];
    float e[16];
    float v[4];

    *(V4_Fbfdc087a *)q = *src;
    func_00283410_9(m, p);
    func_002830C0_8(a, q, m);
    v[0] = x;
    v[1] = y;
    v[2] = z;
    func_00283410_9(e, v);
    func_00283788_6(m, m, e);
    func_002830C0_8(b, q, m);
    func_00282CF0_14(c, a, b);
    func_00282CC0_29(p - 16, p - 16, c);
    func_002AB6D8_4(m, p);
}

/* runs a setup routine on a 16-byte stack buffer, selects 0.35f or 0.6f into buffer slot 2 from a flag byte in fixed data, then forwards the buffer with three float arguments */
void hero_start_pose_offset(float a, float b, float c)
{
    float buf[4];

    func_00282C88_2(buf);

    if (D_0018C0D4[0] == 1)
        buf[2] = 0.35f;
    else
        buf[2] = 0.6f;

    func_L00_002A9FE8_1(buf, a, b, c);
}

/* Copies a 36-byte global record onto the stack, substitutes a default id when the argument is zero, and calls one helper with the id, the count 9 and two fixed global addresses. */
void part_spawn_effect_from_record(int id)
{
    S36_F39e097fb buf;

    if (id == 0)
        id = D_0018C0B0_1;
    buf = D_L00_001A7F68;
    func_L00_003116A8_1(id, 9, &buf, D_0018AA70);
}

/* func_L00_002AA200 is defined in L00_002AA200-pose.c. */

/* Bumps a 16-bit counter in a fixed data block and, when the new value exceeds the caller's threshold, builds a three-float jittered position from two globals plus three random calls, hands it to a spawn helper and stores the helper's return value back into the counter. */
void part_spawn_jittered_after_delay(char *owner, int threshold)
{
    float position[3];
    int count;
    char *hero;
    float speed;

    hero = D_00189E20_20;
    count = *(unsigned short *)(hero + 2628) + 1;
    *(unsigned short *)(hero + 2628) = count;
    if (threshold < (short)count) {
        position[0] = *(float *)(hero + 128) + func_002A7878_6(-0.05f, 0.05f);
        position[1] = *(float *)(hero + 132) + func_002A7878_6(-0.05f, 0.05f);
        position[2] = *(float *)(hero + 816);
        speed = func_002A7878_6(0.4f, 0.6f);
        part_spawn_drifting(position, (float *)(hero + 816), -1, speed, 5250.0f);
        *(unsigned short *)(hero + 2628) = func_002A77E0_2(owner);
    }
}

/* Near miss: nonmatching/levels/func_L00_002AA570.c - 472/480 bytes; retail
   keeps the base's %hi in $s5 and re-materialises it inside the loop. */
/* func_L00_002AA570 is defined in L00_002AA570-effects.c. */

/* func_L00_002AA750 is defined in L00_002AA750.c. */

/* func_L00_002AA938 is defined in L00_002AA938-effects.c. */

/* func_L00_002AABE0 is defined in L00_002AABE0.c. */

/* func_L00_002AAE00 is defined in L00_002AAE00-effects.c. */

typedef struct {
    char reserved00[0xA4];
    float first;
    float second;
    int reservedAC;
} FloatPairRow;
extern FloatPairRow D_L00_0025BE10[4];

#ifndef RAC2_T_FLOATBLOCK_2AB1D8
#define RAC2_T_FLOATBLOCK_2AB1D8
typedef struct {
    u8 pad000[0x5e0];
    float f5E0;
    float f5E4;
    u8 pad5e8[0x624 - 0x5e8];
    float f624;
    float f628;
    u8 pad62c[0x690 - 0x62c];
    float f690;
    float f694;
    u8 pad698[0x6d4 - 0x698];
    float f6D4;
    float f6D8;
} FloatBlock_2ab1d8;
#endif

extern FloatBlock_2ab1d8 D_L00_0025BE10_1;

/* Stores two values in the first entry of a small table. */
void cam_set_limits_first(float first, float second) {
    D_L00_0025BE10[0].first = first;
    D_L00_0025BE10[0].second = second;
}

/* Stores two values in the second entry of a small table. */
void cam_set_limits_second(float first, float second) {
    D_L00_0025BE10[1].first = first;
    D_L00_0025BE10[1].second = second;
}

/* Stores two values in the third entry of a small table. */
void cam_set_limits_third(float first, float second) {
    D_L00_0025BE10[2].first = first;
    D_L00_0025BE10[2].second = second;
}

/* Stores two values in the fourth entry of a small table. */
void cam_set_limits_fourth(float first, float second) {
    D_L00_0025BE10[3].first = first;
    D_L00_0025BE10[3].second = second;
}

/* scales and blends two 16-byte samples through a helper, and on a successful comparison writes a table-derived value to the caller's output */
int hero_test_reach_blend(float *out, float scale, float amount)
{
    char buffer[32];

    hero_build_relative_offset(buffer, 1, D_0018A084 - 0.02f, 0.0f, scale);
    hero_build_relative_offset(buffer + 16, 1, amount, 0.0f, scale);
    if (func_002761F8_2(buffer, buffer + 16, 2, 0, 0)) {
        if (out)
            *out = func_00282E48_4(buffer, D_L00_001BF220_2);
        return 1;
    }
    return 0;
}

/* Publishes the level's camera blend: clears the pending flag at 0x24EC, drops out on the
   three resident gates (the 0x22BB byte, the 0x222 halfword, the 0x22BF byte), asks the
   blend helper for the frame scale, and writes the clamped angle pair into the level's
   float block at 0x25BE10. */

void cam_update_blend_angles(void)
{
    float blendValue;
    float range, pitchAngle, yawAngle, scale;
    int itemId;

    D_00189E20_16.s24EC = 0;

    if (D_00189E20_16.b22BB == 0)
        return;

    if (D_00189E20_16.s222 != 0)
        return;

    if (D_00189E20_16.b22BF != 0)
        return;

    if (hero_test_reach_blend(0, D_00189E20_16.b22B8 != 0 ? 0.7f : 0.57f, 1.3f) == 0)
        return;

    if (D_00189E20_16.b22B8 != 0 && D_L00_001BF218 != 0) {
        if (moby_is_in_special_class_range(D_L00_001BF218) != 0)
            return;
    }

    D_L00_0025BE10_1.f6D4 = 0.05f;
    D_L00_0025BE10_1.f6D8 = 0.3f;

    blendValue = fast_vec_dist(&g_hero_position, D_L00_001BF220_2);
    range = 1.3f - (blendValue - g_hero_position.f1E4);
    scale = range * 0.9615385f;
    pitchAngle = scale * (-70.0f * 0.017453294f);
    if (-30.0f * 0.017453294f < pitchAngle)
        pitchAngle = -30.0f * 0.017453294f;
    if (pitchAngle < (-70.0f * 0.017453294f))
        pitchAngle = -70.0f * 0.017453294f;

    yawAngle = 0.0f;
    itemId = hero_slot_item_id(0);
    if (itemId == 27 || itemId == 44) {
        float maxYaw = 40.0f * 0.017453294f;

        yawAngle = scale * maxYaw;
        if (maxYaw < yawAngle)
            yawAngle = maxYaw;
    }

    D_L00_0025BE10_1.f694 = pitchAngle;
    D_L00_0025BE10_1.f690 = yawAngle;

    if (D_00189E20_16.b22BB == 2) {
        D_L00_0025BE10_1.f624 = D_L00_0025BE10_1.f6D4;
        D_L00_0025BE10_1.f628 = D_L00_0025BE10_1.f6D8;
        D_L00_0025BE10_1.f5E4 = pitchAngle;
        D_L00_0025BE10_1.f5E0 = yawAngle;
    }

    D_00189E20_16.s24EC = 1;
}

/* Clears the hero's saved values for the first slot and four more small records. */
void hero_clear_slot_records(void)
{
    char *hero = D_00189E20_2;
    int i;

    char *entry;

    *(int *)(hero + 0x1194) = 0;
    *(int *)(hero + 0x1198) = 0;
    entry = hero;
    for (i = 3; i >= 0; i--) {
        *(int *)(entry + 0x11B4) = 0;
        *(int *)(entry + 0x11B8) = 0;
        entry += 0x10;
    }
}


/* func_L00_002AB420 is defined in L00_002AB420-g8.c. */

/* func_L00_002AB948 is defined in L00_002AB948.c. */

/* func_L00_002ABBA0 is defined in L00_002A6420-target-g8.c. */

/* func_L00_002AC1A0 is defined in L00_002AC1A0.c. */

/* func_L00_002AC578 is defined in L00_002AC578.c. */

/* func_L00_002ACA08 is defined in L00_002ACA08-flags.c. */


/* func_L00_002AD868 is defined in L00_002AD868-rail.c. */

/* func_L00_002ADB40 is defined in L00_002ADB40.c. */

/* forwards an output pointer, three pinned floating constants and selector one to the typed helper */
void hero_get_offset_vector(f32 *output) {
 hero_build_relative_point(0.3f,0.0f,1.34f,output,1);
}

/* func_L00_002ADD30 is matched in its own unit, L00_002ADD30.c. */

/* returns indexed resident word 0x1220 when field 0x1244 equals two, otherwise zero */
u32 hero_get_slot_object(s32 index) {
 NativeIndexedFieldsView *p=(NativeIndexedFieldsView *)((u8 *)&D_00189E20_1+index*0x50);
 if(p->field1244==2) return p->field1220;
 return 0;
}

/* returns indexed resident word 0x1248 when field 0x1244 equals two, otherwise minus one */
s32 hero_slot_item_id(s32 index) {
 NativeIndexedFieldsView *p=(NativeIndexedFieldsView *)((u8 *)&D_00189E20_1+index*0x50);
 if(p->field1244==2) return p->field1248;
 return -1;
}

/* tests whether the indexed resident status equals 12 or 17 */
s32 hero_is_slot_item_wrench(s32 index) {
 s32 value=hero_slot_item_id(index);
 if(value==12 || value==17) return 1;
 return 0;
}

/* tests whether the indexed resident status equals 47 */
s32 hero_is_slot_item_special(s32 index) {
 return hero_slot_item_id(index)==47;
}

/* the indexed resident status is one of four measured values */
s32 hero_is_slot_item_one_of_four(s32 index)
{
    s32 value = hero_slot_item_id(index);

    if (value == 19 || value == 52 || value == 54 || value == 20)
        return 1;
    return 0;
}


/* tests the measured unsigned resident kind and mode alternatives */
s32 hero_is_in_special_kind_or_mode(void)
{
    ResidentFlags2294 *root = (ResidentFlags2294 *)D_00189E20_1;

    if (root->mode == 17 || root->mode == 18
        || root->kind == 0x67 || root->kind == 0x7f
        || root->kind == 0x73 || root->kind == 0x72) {
        return 1;
    }
    return 0;
}

/* returns the provided value, or object byte 0xa9 when the value is 255 */
u32 hero_get_value_or_default(u8 *object,u32 value) {
    if(value==255) value=object[0xa9];
    return value;
}



/* Returns a saved value from a ring of the last 32 float values, going back by the given number of steps. */
float hero_get_recent_float(int count)
{
    char *hero = D_00189E20_2;
    char *ring;
    int back;
    int start;

    if (count >= 32)
        back = 31;
    else
        back = count;
    if (*(int *)(hero + 0x23C0) < back)
        back = *(int *)(hero + 0x23C0);
    start = *(int *)(hero + 0x23BC) - back;
    ring = hero + 0x233C;
    return *(float *)(ring + ((start + 31) % 32) * 4);
}



/* func_L00_002AE0C8 is defined in L00_002AE0C8-regions.c. */
