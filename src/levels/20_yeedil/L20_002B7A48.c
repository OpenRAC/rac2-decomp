#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern char D_00189E20[];

typedef int V4_F6a70b950 __attribute__((mode(TI)));
typedef struct { float x,y,z,w; } Vec4;
typedef struct {
    unsigned char pad0[0x270]; int contact;
    unsigned char pad274[0x2290-0x274]; void *object;
    unsigned char pad2294[8]; int activity;
    unsigned char pad22a0[0x14]; unsigned char state;
} MotionView;
typedef struct {
    unsigned char pad0[0x18]; int contact; int count;
    unsigned char pad20[0x20]; Vec4 normal;
} ContactView;
#define VELOCITY ((char *)(D_00189E20 + 0xf0))
extern unsigned char D_L20_001C0400[];
#define PLAYER ((MotionView *)D_00189E20)
#define CONTACT ((ContactView *)D_L20_001C0400)
extern float func_L00_002D3A58(char *);
/* EE integer and FP argument banks retain their original order. */
extern void func_L00_002D36E0(float *, float, float, int, float);
extern float func_00282E20(void *);
extern void func_00282F20(void *, void *, float);
extern void func_L00_002D3B58(V4_F6a70b950 *, V4_F6a70b950 *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00278E78(void);
extern float func_L00_002D3EA8(char *);
extern float func_00282DB0(void *, void *);


extern u8 D_00139568[];

extern char D_L20_0026D970[];

extern s32 func_L00_002ADEA0(s32 index);

extern void func_0028CC98(void);
extern void func_0028CCE0(void);
extern void func_0028D1E8(void);
extern s32 func_0028B3D0(s32, s32, void *, void *, void *, s32, s32);
extern void func_L00_002AF7D0(void);
extern void func_L00_002B1F90(void);
extern void func_L00_00322EC8(char *);
extern void func_L00_002D2E68(void);
extern void func_L00_002A6708(void);
extern void func_L00_002A53B8(void);
extern void func_L00_002F6B90(s32);
extern void func_L00_002D24B8(void);
extern void func_002A677C(s32);
extern s32 func_L20_002D7730(s32, s32);
extern void func_L00_002D2168(f32, s32, s32);
extern s32 D_00138320[];
extern void func_L20_002C63F0(void);

typedef struct {
    unsigned char pad0[440];
    int state_timer;
    unsigned char pad1bc[148];
    float capsule_top;
    float capsule_bottom;
    float top_target;
    float bottom_target;
    float radius_target;
    float radius;
    float radius_velocity;
    unsigned char pad26c[27];
    unsigned char wall_hit;
    unsigned char pad288[184];
    int field340;
    unsigned char pad344[346];
    unsigned char past_jump_apex;
    unsigned char pad49f[13];
    short takeoff_frame;
    unsigned char pad4ae[10];
    float field4b8;
    unsigned char pad4bc[4054];
    unsigned char field1492;
    unsigned char pad1493[1];
    unsigned char base_condition;
    unsigned char pad1495[3583];
    int move_state;
    unsigned char pad2298[4];
    int control_mode;
    unsigned char pad22a0[4];
    int previous_control_mode;
    unsigned char pad22a8[8];
    int field22b0;
    unsigned char vehicle_mode;
} HeroCapsuleState;
#define CAPSULE (*(HeroCapsuleState *)D_00189E20)
extern float func_002AA2E8(float *, float, float);
extern float func_00282E80(char *, char *);
extern float func_002AA3A8(float *, float *, float, float, float, float);


/* func_L20_002B7A48 is defined in L20_002B7A48-selector.c. */

/*W23E*/

/* func_L20_002B93E0 is defined in L20_002B7A48-g8.c (it reaches data through $gp). */

void func_L20_002C57D0(s32 a0, s32 a1, char *a2)
{
    char *D = D_00189E20;
    s32 p0 = a0;
    char *p2 = a2;
    s32 p1 = a1;
    char *block;

    func_L00_002AF7D0();
    *(u8 *)(D + 0x22B6) = 1;
    func_L00_002B1F90();
    *(s32 *)(D + 0x2290) = *(s32 *)(D + 0xC18);
    func_L00_00322EC8(D + 0x18E0);
    func_L00_00322EC8(D + 0x1A30);
    *(s32 *)(*(s32 *)(D + 0x2290) + 0x9C) = -1;
    if (p0 != 4 || *(u8 *)(D + 0x22B4) != p0)
        func_L00_002D2E68();
    func_L00_002A6708();
    func_L00_002A53B8();
    block = D_00189E20;
    *(u8 *)(block + 0x22B4) = p0;
    *(s32 *)(block + 0xC14) = (s32)p2;
    *(s32 *)(block + 0x2290) = (s32)p2;
    if ((p0 & 0xFF) == 1) {
        if (D_00138320[0] & 0x10) {
            func_0028B3D0(0x23, 0, (void *)func_0028CC98, (void *)func_0028CCE0,
                          (void *)func_0028D1E8, 0, 0);
            func_L00_002F6B90(3);
        }
    }
    func_L20_002C63F0();
    D = D_00189E20;
    *(f32 *)(D + 0x250) = *(f32 *)(D + 0x258);
    *(f32 *)(D + 0x254) = *(f32 *)(D + 0x25C);
    *(u16 *)(*(s32 *)(D + 0x2290) + 0x34) |= 6;
    *(f32 *)(D + 0xC20) = 1.0f;
    *(f32 *)(D + 0xC24) = 1.0f;
    func_L00_002D24B8();
    func_002A677C(*(s32 *)(D + 0x2290));
    *(u16 *)(D + 0x24F2) = p1;
    switch (p0) {
    case 1:
        *(u16 *)(D + 0x24D4) = *(u16 *)(D + 0x24CC);
        *(s32 *)(D + 0x24CC) = *(s32 *)(D + 0x24D0);
        if (*(s32 *)(D + 0x24CC) >= 5)
            *(s32 *)(D + 0x24CC) = 4;
        break;
    case 4:
        qcopy(D + 0x80, p2 + 0x10);
        qcopy(D + 0x90, p2 + 0xF0);
        *(u16 *)(D + 0x24D4) = *(u16 *)(D + 0x24CC);
        *(s32 *)(D + 0x24CC) = 3;
    }
    func_L20_002D7730(p1, 2);
    if (p0 == 4)
        func_L00_002D2168(5.0f, 0xF, 0);
}


/* func_L20_002C5A48 is defined in L20_002C5A48-qcopy.c (its copies need the grouped-copy profile). */

/* func_L20_002C5D00 is defined in L20_002B7A48-g8.c (it reaches data through $gp). */

void func_L20_002C63F0(void)
{
    HeroCapsuleState *initial = (HeroCapsuleState *)D_00189E20;
    switch (initial->vehicle_mode) {
    case 1:
        initial->top_target = 0.5999999642372131f;
        initial->bottom_target = 0.45000001788139343f;
        initial->radius_target = 0.3f;
        break;
    case 0:
    case 4:
        initial->top_target = 0.8f;
        initial->bottom_target = 0.7f;
        initial->radius_target = 0.44999998807907104f;
        break;
    }
    if (CAPSULE.control_mode == 4) {
        if (CAPSULE.takeoff_frame < CAPSULE.state_timer && !CAPSULE.past_jump_apex)
            CAPSULE.bottom_target = CAPSULE.field4b8;
    } else if (CAPSULE.move_state == 6) {
        CAPSULE.bottom_target = 0.5f;
    } else if (CAPSULE.move_state == 4) {
        CAPSULE.top_target = 0.3500000238418579f;
    } else if ((unsigned)(CAPSULE.control_mode - 17) < 2) {
        CAPSULE.top_target = 0.0f;
        CAPSULE.bottom_target = 0.0f;
    } else if (CAPSULE.field1492 && CAPSULE.field340) {
        CAPSULE.top_target = 0.8f;
        CAPSULE.bottom_target = 0.9f;
    } else if (CAPSULE.move_state == 124) {
        CAPSULE.radius_target = 0.8f;
    }
    if (!CAPSULE.wall_hit || CAPSULE.previous_control_mode == 18 ||
        CAPSULE.field22b0 == 18 ||
        (CAPSULE.vehicle_mode == 0 && CAPSULE.capsule_bottom < 0.53f) ||
        CAPSULE.control_mode == 17 || CAPSULE.base_condition ||
        func_00282E80((char *)&CAPSULE + 0x240, (char *)&CAPSULE + 0x80) >
            CAPSULE.radius * 0.5f) {
        func_002AA2E8(&CAPSULE.capsule_top, CAPSULE.top_target, 0.02f);
        func_002AA2E8(&CAPSULE.capsule_bottom, CAPSULE.bottom_target, 0.02f);
        func_002AA3A8(&CAPSULE.radius, &CAPSULE.radius_velocity,
                     CAPSULE.radius_target, 0.02f, 0.3f, 0.0666666701f);
    }
}

void func_L20_002C7588(int force)
{
    Vec4 offset, start, lowerOffset, lowerStart;
    float height, radius, angle;
    float lowerHeight;
    int kind;
    if (func_L00_002D3A58(VELOCITY) < 0.0016666668f) return;
    height = 0.37f;
    radius = 0.5f;
    if ((unsigned int)(PLAYER->activity - 0x11) < 2) {
        height = 0.0f;
        radius = 0.7f;
    } else if (PLAYER->state == 1) {
        height = 0.35f;
        radius = 0.27f;
    } else if (PLAYER->state == 4) height = 0.35f;
    func_L00_002D36E0(&offset.x, 0.0f, 0.0f, 1, height);
    lowerHeight = height * 0.3f;
    func_L00_002D36E0(&lowerOffset.x, 0.0f, 0.0f, 1, lowerHeight);
    if (force || func_00282E20(VELOCITY) < 0.01f) {
        func_00282F20(&start, D_00189E20, radius);
        func_00282F20(&lowerStart, D_00189E20, radius * 1.4f);
    } else {
        func_L00_002D3B58((V4_F6a70b950 *)&start, (V4_F6a70b950 *)VELOCITY, 0.0f);
        func_00282F20(&start, &start, radius);
        func_00282D30(&lowerStart, &start, 1.4f);
    }
    kind = -1;
    func_00282CC0(&start, &start, &offset);
    func_00282CC0(&lowerStart, &lowerStart, &lowerOffset);
    if (func_002761F8(&lowerOffset, &lowerStart, 2, PLAYER->object, 0) && CONTACT->count > 0)
        kind = func_00278E78();
    angle = 0.0f;
    if (func_002761F8(&offset, &start, 2, PLAYER->object, 0) && CONTACT->count > 0)
        angle = func_L00_002D3EA8((char *)&CONTACT->normal);
    if (angle >= 0.8726647f || kind == 8 || kind == 12) {
        float dot;
        PLAYER->contact = CONTACT->contact;
        func_L00_002D3B58((V4_F6a70b950 *)&CONTACT->normal, (V4_F6a70b950 *)&CONTACT->normal, 0.0f);
        func_00282F20(&CONTACT->normal, &CONTACT->normal, 1.0f);
        dot = func_00282DB0(&CONTACT->normal, VELOCITY);
        if (dot < 0.0f) {
            func_00282D30(&CONTACT->normal, &CONTACT->normal, -dot);
            func_00282CC0(VELOCITY, VELOCITY, &CONTACT->normal);
        }
    }
}
