#include "include_asm.h"

typedef int L04_FBD80Quad __attribute__((mode(TI)));
typedef struct {
    float jitter[28];
    float scale;
    unsigned char *owner;
    int timer;
    float age;
} L04_FBD80Vars;
extern unsigned char *ref_L04_003FBD80_00(int kind);
extern int ref_L04_003FBD80_01(int a0, int a1, void *owner);
extern float ref_L04_003FBD80_02(float low, float high);
extern void func_PAL_L04_003FFB98(unsigned char *object, L04_FBD80Vars *vars);
extern int D_L04_001B0488 __attribute__((sda));

/* Spawns a kind-0xABE object for an entity of kind 0xBBC: it takes the entity's 8-byte
   word at +0x38, the given position raised by 0.2 and the entity's quadword at +0xF0 (with
   +0xF4 replaced by the entity state's +0x284 when its +0x274 is set), and its state
   points back at the entity with a 0.5 scale and a jitter table of 28 random floats in
   [-10, 10] / 75, the first and last zero. Returns the object, or 0. */
unsigned char *func_PAL_L04_003FFF88(unsigned char *entity, L04_FBD80Quad *position)
{
    float pos[4] __attribute__((aligned(16)));
    unsigned char *object;
    unsigned char *state;
    L04_FBD80Vars *vars;
    int result;
    long word;
    int i;

    *(L04_FBD80Quad *)pos = *position;
    if (entity == 0 || *(short *)(entity + 0xAA) != 0xBBC)
        return 0;
    object = ref_L04_003FBD80_00(0xABE);
    if (object != 0) {
        state = *(unsigned char **)(entity + 0x68);
        object[0x30] = 0x7F;
        *(short *)(object + 0x32) = 0x7F;
        object[0x31] = 1;
        vars = *(L04_FBD80Vars **)(object + 0x68);
        result = ref_L04_003FBD80_01(9, 0, entity);
        word = *(long *)(entity + 0x38);
        D_L04_001B0488 = result;
        *(long *)(object + 0x38) = word;
        *(L04_FBD80Quad *)(object + 0x10) = *(L04_FBD80Quad *)pos;
        *(float *)(object + 0x18) += 0.2f;
        *(L04_FBD80Quad *)(object + 0xF0) = *(L04_FBD80Quad *)(entity + 0xF0);
        if (*(short *)(state + 0x274) != 0)
            *(float *)(object + 0xF4) = *(float *)(state + 0x284);
        vars->owner = entity;
        vars->scale = 0.6f;
        vars->timer = 0;
        vars->age = 0;
        for (i = 0; i < 28; i++) {
            vars->jitter[i] = ref_L04_003FBD80_02(-10.0f, 10.0f) * 0.018897636f;
            if (i == 0 || i == 27)
                vars->jitter[i] = 0;
        }
        func_PAL_L04_003FFB98(object, vars);
    }
    return object;
}
