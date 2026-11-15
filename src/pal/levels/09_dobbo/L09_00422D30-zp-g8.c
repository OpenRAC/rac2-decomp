#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef int Quadword __attribute__((mode(TI)));
typedef union EffectVector { Quadword bits; float value[4]; } EffectVector;
extern void moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern void moby_mark_spawned(void *);
extern void *part_spawn_object_following_effect(float *, u8 *, int, int, int, int, int, int, float, float);
extern void func_PAL_L00_002ED7E8(u8 *, float *, float *, int, int, float, float, float, float, float);
extern void func_PAL_L00_0032C328(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern char *moby_l00_spawn_child(u8 *, int, int);
extern float D_L09_001B1CA0 __attribute__((sda));
extern float D_L09_001B1CA8 __attribute__((sda));
extern float D_L09_001B1CB0 __attribute__((sda));

/* Three-state effect object: spawns its first effect, waits for the hit, then fires the closing effects and retires itself. */
void func_PAL_L09_00427350(u8 *self)
{
    EffectVector a;
    EffectVector b;
    u8 *state = *(u8 **)(self + 0x68);

    a.bits = 0;
    a.value[1] = -0.14f;
    a.value[2] = 0.14f;
    switch (self[0x20]) {
    case 0:
        part_spawn_object_following_effect(a.value, self, 0x50088030, -1, 1, -1, 0, -1, 136500.0f, 0.75f);
        moby_set_state(self, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(self, 0x4010000, 0)) {
            if (*(int *)state == 0)
                moby_set_state(self, 2, -1);
        }
        self[0xA8] = 0xFF;
        break;
    case 2:
        b.bits = 0;
        b.value[1] = -0.060000002f;
        b.value[2] = 0.020000001f;
        func_PAL_L00_002ED7E8(self, a.value, b.value, 25, 2, 0.2f, 0.10000001f, 1.5f, 6.0f, 0.8f);
        func_PAL_L00_0032C328(self, &D_L09_001B1CB0, &D_L09_001B1CA8, &D_L09_001B1CA0,
                          0xFFFF, 0, -1, 0, 0xFFFF, 0xFF, 0);
        moby_l00_spawn_child(self, 0x1299, 0);
        moby_mark_spawned(self);
        break;
    }
}
