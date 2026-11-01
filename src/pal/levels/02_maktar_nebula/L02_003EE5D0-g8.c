#include "include_asm.h"

#include "common.h"
extern float func_002A7940(void);
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern int func_00283CF0(float);
extern void func_002A7750(char *, int, int);
extern void func_L00_0033E220(void *, char *, int, float, int, int, float, int, int, int);
extern int func_002B38B8(char *);
extern int func_002E5CF8(int, int, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern char *D_0018A15C[3] __attribute__((sda));
typedef struct { unsigned short value; } FlagA180;
extern FlagA180 D_0018CA54 NOT_SDA;
extern float D_L02_001B0D40 __attribute__((sda));
extern float D_L02_001B0D44 __attribute__((sda));
extern float D_L02_001B0D48 __attribute__((sda));
extern float D_L02_001B0D4C __attribute__((sda));
typedef struct { char pad[0x78]; int color; } ActorA180;
typedef int QuadA180 __attribute__((mode(TI)));
typedef struct { float origin[4]; float position, velocity, angle; } StateA180;

void func_PAL_L02_003EE5D0(char *actor) {
    StateA180 *s = *(StateA180 **)(actor + 0x68);
    QuadA180 vector;
    int color;
    float direction;

    switch (*(u8 *)(actor + 0x20)) {
    case 0:
        s->angle = func_002A7940();
        qcopy(s, actor + 0x10);
        func_002A7750(actor, 1, -1);
        break;
    case 1:
        vector = 0;
        ((float *)&vector)[1] = -1.25f;
        ((float *)&vector)[2] = -2.0f;
        s->angle = func_00283B98(s->angle, 0.062831864f);
        color = func_00283CF0((func_00283198(s->angle) * 4.0f - 3.0f) * 208.0f);
        if (color > 208) color = 208;
        else if (color < 80) color = 80;
        if (D_0018A15C[0] != 0 && *(short *)(D_0018A15C[0] + 0xAA) == 0xA61 && color >= 101) {
            func_L00_0033E220(&vector, actor, 0x20000012, 3.15e+05f, -1, 0, 0.0f, 12, 0, -1);
            func_L00_0033E220(&vector, actor, 0x20000012, 3.15e+05f, -1, 1, 0.0f, 12, 0, -1);
        }
        ((ActorA180 *)actor)->color = color | 0x800C0C00;
        if (func_002B38B8(actor)) {
            func_002E5CF8(0, 0, actor);
            func_002A7750(actor, 2, -1);
        }
        break;
    case 2: {
        float force, spring;
        ((ActorA180 *)actor)->color = 0xFF0CFF0C;
        force = D_L02_001B0D44 * 0.00040000002f;
        spring = s->position * 0.00040000002f * D_L02_001B0D48;
        force += spring;
        s->velocity += force;
        s->position += s->velocity;
        D_0018CA54.value = -1;
        if (s->position > D_L02_001B0D40) {
            s->position = D_L02_001B0D40;
            if (s->velocity > 0.020000001f) {
                s->velocity *= D_L02_001B0D4C;
            } else {
                s->velocity = 0;
                func_002A7750(actor, 3, -1);
            }
        }
        direction = -1.0f;
        if (*(short *)(actor + 0xAA) == 0xAAC) direction = 1.0f;
        func_00282F20(actor + 0x10, actor + 0xC0, direction * s->position);
        func_00282CC0(actor + 0x10, actor + 0x10, s);
        break;
    }
    }
    return;
}
