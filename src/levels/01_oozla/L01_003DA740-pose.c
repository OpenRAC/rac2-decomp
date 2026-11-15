#include "common.h"

/* func_L01_00405300, in a unit of its own: retail reaches its globals with
   assembler macro loads (-mno-split-addresses), which keep its branches from
   taking the loads into their delay slots. The pose types are those of
   func_L01_003EC0C0 (L01_003DA740.c); struct (not cast) accesses matter there
   too, for the order of the table and index loads. */

typedef struct {
    unsigned char pad00[0x30];
    float position[4];              /* 0x30 */
    unsigned char pad40[0x30];
    float rotation[4];              /* 0x70 */
} PoseRecord;
typedef struct {
    unsigned char pad00[0x20];
    float track[4];                 /* 0x20 */
    unsigned char pad30[0x2C];
    int flags;                      /* 0x5C */
    float start_position[4];        /* 0x60 */
    float start_rotation[4];        /* 0x70 */
    int index;                      /* 0x80 */
    float duration;                 /* 0x84 */
    float t;                        /* 0x88 */
    int link;                       /* 0x8C */
    int sound;                      /* 0x90 */
} PoseMotion;
typedef struct {
    unsigned char pad00[0x10];
    float position[4];              /* 0x10 */
    unsigned char state;            /* 0x20 */
    unsigned char pad21[0x13];
    unsigned short flags;           /* 0x34 */
    unsigned char pad36[0x32];
    PoseMotion *vars;               /* 0x68 */
    unsigned char pad6C[0x3C];
    unsigned char hit_slot;         /* 0xA8 */
    unsigned char padA9[0x13];
    unsigned char command;          /* 0xBC */
    unsigned char padBD[0x33];
    float rotation[4];              /* 0xF0 */
} PoseMoby;
typedef struct { unsigned char data[256]; } AttachObject;

extern AttachObject *D_L01_001B255C __attribute__((sda));
extern PoseRecord *D_L01_001B264C MACRO_ADDR;
extern unsigned char D_001A7B0B[];
extern unsigned char D_001A7B2A[];
extern float func_00283180(float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002AA150(float, float, float);
extern void func_002A7750(void *, int, int);
extern void func_002AD6F0(void *, void *, void *, void *);

/* Eases into its table pose once its command byte is set, its linked moby is
   missing or dying (state 0xFE/0xFD), D_001A7B0B is clear or D_001A7B2A set;
   then sets bit 2 of its flags. */
void func_L01_00405300(PoseMoby *m)
{
    float position[4], rotation[4], delta[4];
    PoseMotion *p = m->vars;
    float blend;

    qcopy(position, m->position);
    qcopy(rotation, m->rotation);
    switch (m->state) {
    case 0:
        p->t = 0.0f;
        p->flags |= 1;
        qcopy(p->start_position, m->position);
        qcopy(p->start_rotation, m->rotation);
        func_002A7750(m, 1, -1);
        break;
    case 1:
        if (m->command || p->link == -1 ||
            D_L01_001B255C[p->link].data[0x20] == 0xfe ||
            D_L01_001B255C[p->link].data[0x20] == 0xfd ||
            !D_001A7B0B[0] || D_001A7B2A[0])
            func_002A7750(m, 2, -1);
        m->hit_slot = 255;
        break;
    case 2:
        p->t += 1.0f / p->duration;
        if (p->t > 1.0f) p->t = 1.0f;
        blend = (1.0f - func_00283180(p->t * 3.1415927f)) * 0.5f;
        FastVecSub(delta, D_L01_001B264C[p->index].position, p->start_position);
        FastVecScale(delta, delta, blend);
        FastVecAdd(m->position, p->start_position, delta);
        m->rotation[2] = func_002AA150(p->start_rotation[2], D_L01_001B264C[p->index].rotation[2], blend);
        m->rotation[1] = func_002AA150(p->start_rotation[1], D_L01_001B264C[p->index].rotation[1], blend);
        m->rotation[0] = func_002AA150(p->start_rotation[0], D_L01_001B264C[p->index].rotation[0], blend);
        if (p->t >= 1.0f) func_002A7750(m, 3, -1);
        break;
    case 3:
        m->flags |= 2;
        break;
    }
    if (m->state < 3) {
        FastVecSub(delta, m->position, position);
        func_002AD6F0(p->track, delta, rotation, m->rotation);
    }
}
