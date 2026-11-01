#include "common.h"






extern float D_L11_001BA8C0[];

extern float func_002A7878(float, float);

extern void func_0029FCC0(void *, int, void *);

extern void func_00282CF0(float *, const float *, const float *);

extern void func_00282F20(char *, char *, float);

extern void func_00282CC0(char *, char *, char *);



extern int D_L18_001C9D40;


extern s32 func_002E59B0(void *, s32);

extern s32 func_002E5CF8(s32, s32, void *);






extern int func_00283CF0(float);
extern void func_002E59F8(int);
extern char D_00188660[], D_00189EA0[];
extern int func_002A77E0(int);
extern float func_002A78D8(float, float);
extern int func_001163B0(void);
extern void func_00282D30(void *, void *, float);
extern void func_002ACEC0(void *, void *, void *, float);
extern u8 *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);

typedef int TI128 __attribute__((mode(TI)));

extern void func_0029FCC0(void *, int, void *);
extern void func_00282CF0(float *, const float *, const float *);
extern void func_00282CC0(char *, char *, char *);
extern void func_00282F20(char *, char *, float);
extern char D_00188660[];

#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define I(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define H(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define P(p,o) (*(u8 **)((u8 *)(p)+(o)))
extern int func_002E59B0(void *,int),func_002E5CF8(int,int,void *);
extern void func_002E59F8(int);

extern void func_L11_003F4A58(char *,int);

extern struct { u8 pad[24];u8 *object;u8 pad1[4];float position[4] __attribute__((aligned(16))); } D_L18_001BFC00;
extern int D_L18_001B2348 __attribute__((sda));
typedef struct {
 u8 pad[0x7e4]; u8 *attached; u8 gap[0x1c]; s16 timer, mode;
} DamoselBeamState;

#undef F
#undef I
#undef H
#undef P

/* func_L18_00433B70 lives in L18_00433B70.c. */

extern float D_L11_001B0654 __attribute__((sda));
extern float D_L11_001B0658 __attribute__((sda));
extern float D_L11_001B065C __attribute__((sda));
extern float D_L11_001B0660 __attribute__((sda));
extern float D_L11_001B0664 __attribute__((sda));
extern float D_L11_001B0668 __attribute__((sda));
extern float D_L11_001B066C __attribute__((sda));

void func_L11_003F4A58(char *pos, int count) {
    float velocity[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));
    int i, sign;
    float size, angle, speed;
    u8 *particle;

    *(TI128 *)axis = 0;
    axis[2] = 1.0f;
    func_00282CF0(direction, D_L11_001BA8C0, (float *)pos);
    direction[2] = 0.0f;
    for (i = 0; i < count; i++) {
        size = func_002A7878(D_L11_001B0668, D_L11_001B066C);
        sign = func_002A77E0(2);
        if (sign == 0)
            sign--;
        angle = func_002A7878(-1.0471977f, 1.0471977f);
        func_002ACEC0(velocity, direction, axis, angle);
        speed = func_002A7878(D_L11_001B0654, D_L11_001B0658) * (1.0f / 60.0f);
        func_00282F20((char *)velocity, (char *)velocity, speed);
        velocity[2] = func_002A7878(D_L11_001B065C, D_L11_001B0660) * (1.0f / 60.0f);
        qcopy(point, pos);
        point[0] += func_002A78D8(0.0f, 0.15f);
        point[1] += func_002A78D8(0.0f, 0.15f);
        point[2] += func_002A78D8(0.0f, 0.15f);
        if (!(func_001163B0() & 1)) {
            func_00282D30(velocity, velocity, 1.5f);
            particle = func_002C2210(point, 60, size * 0.35f, size, 0x7F800000, 0, sign, velocity, 0, D_L11_001B0664);
            if (particle)
                particle[9] = func_00283CF0(4.0f) + 0x70;
            particle = func_002C2210(point, 60, size * 0.245f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, D_L11_001B0664);
        } else {
            func_00282CF0(extra, D_L11_001BA8C0, point);
            func_00282F20((char *)extra, (char *)extra, speed);
            func_00282CC0((char *)velocity, (char *)velocity, (char *)extra);
            particle = func_002C2210(point, 40, size * 2.05f, size, 0x7F800000, 0, sign, velocity, 0, D_L11_001B0664);
            if (particle)
                particle[9] = func_00283CF0(4.0f) + 0x70;
            particle = func_002C2210(point, 40, size * 1.43500006f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, D_L11_001B0664);
        }
        if (particle)
            particle[9] = func_00283CF0(4.0f) + 0x70;
    }
}

