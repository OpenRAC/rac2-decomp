/* func_PAL_003292E8, the PAL copy of func_00327B40: the same C, where rename func_0032D758 becomes func_PAL_0032F0B8; wrap ref_L00_00327B40_00 - 20 (((int)({e}) * 5 + 2) / 6). */
#include "common.h"

/* The thresholds live in small data, so this unit is built with -G8 (and -ffast-math for the
   min.s); they differ from program to program, so they carry no level. */
typedef unsigned int B40Quad __attribute__((mode(TI)));
extern int ref_L00_00327B40_00 __attribute__((sda));
extern float ref_L00_00327B40_01 __attribute__((sda));
extern int D_001BF000[];
typedef struct { unsigned char pad[0x20]; unsigned char selection; } SettingsB40;
extern SettingsB40 D_00139568;
typedef struct { char pad[0x70]; float damage; char tail[0x6C]; } B40Class;
extern B40Class D_00239BA0[];
typedef struct { char pad[0x2290]; char *object; } ContextB40;
extern ContextB40 D_00189E20;
extern int func_00277F48(void *, int, void *, int, float);
extern int func_002AB1F0(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002A8C00(void *, void *, int, void *, float);
extern void func_002A8E20(void *, void *);
extern void func_PAL_0032F0B8(void *, int, int);

typedef struct {
    char pad0[0x10];
    float pos[4];
    char pad20[0x48];
    char *state;
    char pad6C[0x4C];
    int id;
} ObjectB40;

/* Pushes every object within range (the smaller of the state's radius and a global one) away
   from this object, unless it is the hero's current object or neither pushable nor flagged
   0x4000. */
void func_PAL_003292E8(ObjectB40 *self)
{
    float direction[4];
    struct {
        float direction[4];
        char pad10[8];
        unsigned char kind, mode;
        short classid;
        int pad1C;
        int enabled;
        char tail[12];
    } hit;
    char *state = self->state;
    int count, remaining;
    int *list;
    char *obj;
    float radius;

    if (*(int *)(state + 0x20) < (((int)(ref_L00_00327B40_00 - 20) * 5 + 2) / 6))
        return;
    radius = *(float *)(state + 0x24) < ref_L00_00327B40_01 ? *(float *)(state + 0x24) : ref_L00_00327B40_01;
    count = func_00277F48(self->pos, 0, self, 0, radius);
    if (count > 0) {
        list = D_001BF000;
        remaining = count;
        do {
            obj = (char *)*list;
            if ((func_002AB1F0(obj) || (*(unsigned short *)(obj + 0x34) & 0x4000))
                && obj != D_00189E20.object) {
                func_00282CF0(direction, obj + 0x10, self->pos);
                func_00282F20(direction, direction, 1.0f);
                func_00282F20(&hit, &hit, 1.0f);
                func_002A8C00(&hit, self, 0x830000, direction,
                              ((B40Class *)((int)D_00239BA0 + D_00139568.selection * sizeof(B40Class)))->damage);
                *(B40Quad *)hit.direction = *(B40Quad *)direction;
                hit.enabled = 1;
                hit.direction[3] = 5627.925f;
                hit.kind = 5;
                hit.mode = 3;
                hit.classid = *(short *)(obj + 0xAA);
                func_002A8E20(obj, &hit);
                func_PAL_0032F0B8(obj, 32, self->id);
            }
            list++;
        } while (--remaining);
    }
}
