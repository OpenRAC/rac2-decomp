#include "include_asm.h"

#include "common.h"
typedef struct {
    float vel[4];
    char pad10[4];
    int arg;
    char pad18[4];
    int timer;
    char pad20[8];
    int index;
} CloudWork;
typedef struct Actor {
    char pad0[0x10];
    float pos[4];
    unsigned char state;
    char pad21[3];
    char *classData;
    struct Actor *next;
    float scale;
    unsigned char alpha, active;
    unsigned short flags;
    char pad34[0x34];
    CloudWork *work;
    char pad6c[0x3E];
    short kind;
    char padac[0x44];
    float rx, ry, rz;
} Actor;
extern int func_002A77E0(int);
extern Actor *func_0029EFD0(int);
extern void func_002A0488(Actor *, int, int, int);
extern char D_L10_002BABF0[];
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern Actor *D_L10_001B1780 __attribute__((sda));
extern Actor *D_L10_001B2528;

/* Spawns one of three cloud classes (0x1315, 0x1328, 0x1327) at a random start point
   from D_L10_002BABF0, jittered by +-5 on each axis, with a random orientation and
   timer. The first call also caches the last class-0xFBF object of the list in
   D_L10_001B1780. Classes 0x1315 and 0x1327 get 1.5 times their class scale. */
Actor *func_PAL_L10_00433CD0(int arg)
{
    Actor *p;
    CloudWork *st;
    int index;
    int kind = func_002A77E0(5);

    if (kind == 0) p = func_0029EFD0(0x1315);
    else if (kind == 1) p = func_0029EFD0(0x1328);
    else p = func_0029EFD0(0x1327);
    if (p) {
        p->state = 0;
        p->alpha = 255;
        p->flags = 255;
        p->active = 1;
        st = p->work;
        func_002A0488(p, 20, 20, 20);
        index = func_002A77E0(5);
        st->index = index;
        qcopy(&p->pos, D_L10_002BABF0 + index * 16);
        p->pos[0] += func_002A7878(5.0f, -5.0f);
        p->pos[1] += func_002A7878(5.0f, -5.0f);
        p->pos[2] += func_002A7878(5.0f, -5.0f);
        p->rx = func_002A7940();
        p->ry = func_002A7940();
        p->rz = func_002A7940();
        st->timer = ((s32)(func_002A77E0(3600)) * 5 + 2) / 6;
        st->arg = arg;
        if (!D_L10_001B1780) {
            Actor *cur = D_L10_001B2528;
            while (cur) {
                if (cur->kind == 0xFBF) D_L10_001B1780 = cur;
                cur = cur->next;
            }
        }
        if (p->kind == 0x1315)
            p->scale = *(float *)(p->classData + 0x24) * 1.5f;
        else if (p->kind == 0x1328)
            p->scale = *(float *)(p->classData + 0x24);
        else if (p->kind == 0x1327)
            p->scale = *(float *)(p->classData + 0x24) * 1.5f;
        return p;
    }
    return 0;
}
