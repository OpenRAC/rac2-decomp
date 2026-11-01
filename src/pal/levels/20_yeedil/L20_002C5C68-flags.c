#include "include_asm.h"

#include "common.h"
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

void func_PAL_L20_002C7500(int force)
{
    Vec4 offset, start, lowerOffset, lowerStart;
    float height, radius, angle;
    float lowerHeight;
    int kind;
    if (func_L00_002D3A58(VELOCITY) < 0.002f) return;
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
