#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef float f32;
typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    char pad[0xAA];
    short key;
} Obj_389848;

extern void func_L13_00389848(Obj_389848 *);

extern void func_002AB8C0(char *, char *);

extern void *func_002A9640(char *, int, int);

extern int func_00282978(void *);

extern f32 func_002A96A0(char *, char *);

extern void func_002B3380(char *, char *, char *);

extern void func_00282F20(f32 *, char *, f32);

extern void func_00282CC0(f32 *, f32 *, f32 *);

extern void func_0029F338(char *);

extern void func_0032C700(void *, int, int, int, int, int, int, int, int, int, int, int,
                          f32, f32);

/* Updates an enemy that loses health over time, and makes a small explosion and removes it when its health runs out. */
void func_L13_003ECEA8(char *a0)
{
    char *self = a0;
    char *ctl;
    unsigned char state;
    char *child;
    char *obj;
    f32 vec[4];
    f32 tmp1[4];
    f32 tmp2[4];
    f32 scale;

    ctl = *(char **)(self + 0x68);
    state = *(unsigned char *)(self + 0x20);
    switch (state) {
    case 0:
        AddKeyToLevelList((Obj_389848 *)self);
        *(unsigned char *)(self + 0x20) = 1;
    case 1:
        UpdateColorFade(self, ctl + 0x50);
        child = (char *)FindOwnedEffectSlot(self, 1, 0);
        if (FastDecTimer(ctl + 0x26) == 0)
            child = 0;
        if (child != 0) {
            scale = *(f32 *)(child + 0x2C);
            if (*(f32 *)(ctl + 0xF8) != 0.0f) {
                obj = *(char **)(child + 0x20);
                if (obj != 0 && *(short *)(self + 0xAA) == *(short *)(obj + 0xAA))
                    *(f32 *)(child + 0x2C) = scale * *(f32 *)(ctl + 0xF8);
            }
        } else {
            child = (char *)FindOwnedEffectSlot(self, 0x10000, 0);
            if (child != 0) {
                scale = *(f32 *)(child + 0x2C);
                scale *= 0.5f;
                *(f32 *)(child + 0x2C) = scale;
                if (*(f32 *)(ctl + 0xF8) != 0.0f) {
                    obj = *(char **)(child + 0x20);
                    if (obj != 0 && *(short *)(self + 0xAA) == *(short *)(obj + 0xAA))
                        *(f32 *)(child + 0x2C) = scale * *(f32 *)(ctl + 0xF8);
                }
            }
        }
        scale = UpdateAimTargetStrength(self, child);
        *(unsigned char *)(self + 0xA8) = 0xFF;
        *(f32 *)(ctl + 0x20) -= scale;
        SpawnDamageDebrisOnHealthLoss(self, ctl + 0x100, ctl + 0x20);
        if (*(f32 *)(ctl + 0x20) <= 0.0f) {
            {
            f32 *v = vec;
            *(TI128 *)v = *(TI128 *)(self + 0x10);
            }
            vec_scale_to_length(tmp2, self + 0xD0, -2.0f);
            FastVecAdd(vec, tmp2, vec);
            vec_scale_to_length(tmp1, self + 0xC0, 1.5f);
            FastVecAdd(vec, tmp1, vec);
            SpawnExplosion(vec, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1, 0, 0, 0,
                          0.75f, 20.0f);
            MarkMobySpawned(self);
        }
    }
}
