#include "include_asm.h"


#include "common.h"
typedef int TI_0032ABC0 __attribute__((mode(TI)));
typedef union { char b[0x2600]; char *ptr[0x980]; } Hero_0032ABC0;
typedef struct { float dir[4]; float spin; float speed; int life; void *owner; float scale; char pad24[0xC]; } Debris0032ABC0;
extern Debris0032ABC0 D_00232760[];
extern char D_00189E20[];
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern void func_002FE8D8(void *, float *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(float *, float *, float);

/* Takes the first free debris slot for owner: a random spin and speed, a 37-frame life, and a
   direction pointing away from the hero's target. */
void func_PAL_0032C3B0(void *owner)
{
    Debris0032ABC0 *debris;
    int i;
    float out[4];
    TI_0032ABC0 delta;
    TI_0032ABC0 pos;

    for (i = 0; i < 12; i++) {
        debris = &D_00232760[i];
        if (debris->owner == 0) {
            debris->owner = owner;
            debris->spin = func_002A7940();
            debris->speed = func_002A78D8(1200.0f, 1400.0f) * 0.0003490659f;
            debris->life = 0x1F;
            debris->scale = func_002A7878(0.3f, 0.4f);
            func_002FE8D8(((Hero_0032ABC0 *)D_00189E20)->ptr[0x2290 / 4] + 0x10, out);
            qcopy(&pos, ((Hero_0032ABC0 *)D_00189E20)->ptr[0x2290 / 4] + 0x10);
            func_00282CC0(&delta, &pos, out);
            func_00282DD8(&pos, &pos, &delta);
            func_00282F20(debris->dir, (float *)&pos, debris->scale);
            return;
        }
    }
}

