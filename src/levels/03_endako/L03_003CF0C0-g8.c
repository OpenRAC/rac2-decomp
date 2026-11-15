#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef struct {
    char position[16];
    char pad10[0x25C];
    char *attached;
    char pad270[0x2024];
    int state;
} PlayerState;
extern PlayerState D_00189E20;
typedef struct {
    u8 header[0x464];
    u8 entries[0];
} TriggerTable;
extern TriggerTable D_L03_0021EA30;
extern u8 D_0019B4A8[];
extern char D_L03_001A8F20[] __attribute__((sda));
extern float D_L03_001B0460 __attribute__((sda));
extern float D_L03_001B0464 __attribute__((sda));
extern float D_L03_001B0468 __attribute__((sda));
extern char D_L03_001B0470[] SDATA(D_L03_001B0470);
extern int D_001A79F0 MACRO_ADDR;
extern int D_L03_001B2548;
extern char *func_002A9640(char *, int, int);
extern void func_002A7750(char *, int, int);
extern void func_002B0A18(int, int);
extern int func_002E5CF8(int, int, char *);
extern void func_00282C98(void *);
extern void func_00282F70(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_002ACE78(void *, void *, float);
extern void func_00273978(char *, int, int, void *, void *, u8, float);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002AB6D8(void *, void *);
extern void func_002B0A68(char *, int, void *, u8, float, float, float, float);
extern void func_002A7A00(void *, float, float);
extern void func_L03_003D0300(char *);
extern int func_002A77E0(int), func_00273B70(char *);
extern char *func_00273730(char *, int, int, int, void *, void *, void *, u8, float, float);
extern float func_00283198(float), func_00282DB0(void *, void *), func_00282DF0(void *);
extern float func_002A78D8(float, float), func_002A7878(float, float), func_002A7940(void);
/* Initializes the triggered motion, sheds debris while moving, and emits the
 * final twenty-object burst when the collision magnitude reaches its threshold. */
/* Per-frame update of moby class 2481 (Trash Can). */
void func_L03_003CF0C0(char *obj)
{
    float target[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float temporary[4] __attribute__((aligned(16)));
    float angles[4] __attribute__((aligned(16)));
    char *vars = *(char **)(obj + 0x68);
    char *collision = FindOwnedEffectSlot(obj, 0x10000, 0);
    int i, dialogue;
    float value;

    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        SetMobyState(obj, 1, -1);
        break;
    case 1:
        if (!collision && !(gHeroState.state == 0x10 && gHeroState.attached == obj))
            break;
        dialogue = *(int *)(vars + 0x84);
        if (dialogue >= 0) {
            u16 id = *(u16 *)(obj + 0xB2);
            if (!D_L03_0021EA30.entries[(s16)id]) {
                int count = D_0019B4A8[((s16)id >> 1) + (gCurrentMapIndex << 10)];
                if (!((id & 1) ? ((count >> 4) & 7) : (count & 7)))
                    SetEntryValueByIndex(dialogue + 0x2F52, 0xB4);
            }
        }
        if (*(u16 *)(obj + 0xB2) & 1) {
            u8 *cell = D_0019B4A8 +
                (((short)*(u16 *)(obj + 0xB2) >> 1) + (gCurrentMapIndex << 10));
            if (((*cell >> 4) & 7) != 7)
                *cell += 16;
        } else {
            u8 *cell = D_0019B4A8 +
                (((short)*(u16 *)(obj + 0xB2) >> 1) + (gCurrentMapIndex << 10));
            if ((*cell & 7) != 7)
                ++*cell;
        }
        PlayMobySound(0, 0, obj);
        VectorCopyHelperA(velocity);
        if (collision)
            FastVectorNormalizeHelper(target, collision + 0x10, D_L03_001B0460 * 0.0166666675f);
        else
            FastVectorNormalizeHelper(target, gHeroState.position, D_L03_001B0460 * 0.0166666675f);
        target[2] = D_L03_001B0464 * 0.0166666675f;
        FastVecCross(position, velocity, target);
        value = FastSinOrCosB(D_L03_001B0468 * 0.000290888245f);
        SetDirectionWithComplement(position, position, value * 0.5f);
        InitCameraTracking(obj, 0, -1, target, position, 255, 15.0f);
        *(int *)(obj + 0x98) = *(int *)(*(char **)(obj + 0x24) + 0x10);
        SetMobyState(obj, 2, -1);
        break;
    case 2:
        VectorCopyHelperA(target);
        value = FastVecDot(obj + 0xE0, target);
        if ((gFrameCounter_L03 & 3) == (((int)obj >> 8) & 3) && value < 0.9f && value > 0.1f) {
            int kind;
            char *child;

            i = RandomIntBelow(4);
            matrix_mul_vec3(position, D_L03_001B0470 + (i << 4), obj + 0xC0);
            FastVecAdd(position, position, obj + 0x10);
            kind = 0x9D7;
            if (RandomIntBelow(2))
                kind = 0x9D4;
            *(Quad *)temporary = 0;
            temporary[0] = RandomSignedFloatRange(0, 2);
            temporary[1] = RandomSignedFloatRange(0, 2);
            temporary[2] = RandomFloatRange(4, 8);
            *(Quad *)velocity = *(Quad *)temporary;
            value = FastVecLength(velocity);
            vec_scale_to_length(velocity, velocity, value * 0.0166666675f);
            matrix_mul_vec3(velocity, velocity, obj + 0xC0);
            *(Quad *)angles = 0;
            angles[0] = RandomAngle();
            angles[1] = RandomAngle();
            angles[2] = RandomAngle();
            *(Quad *)temporary = *(Quad *)angles;
            child = CreateCameraMoby(obj, 0, kind, -1, position, temporary, velocity, 255,
                RandomSignedFloatRange(45, 180) * 0.000290888245f, 20.0f);
            if (child) {
                *(void (**)(char *))(child + 0x64) = UpdateTrashCanDebrisMoby;
                PlayMobySound(1, 0, obj);
            }
        }
        if (UpdateCameraMoby(obj))
            SetMobyState(obj, 3, -1);
        break;
    case 3:
        break;
    case 4:
        return;
    }
    if (collision && *(float *)(collision + 0x2C) >= 3.0f) {
        SetMobyState(obj, 4, -1);
        *(int *)(obj + 0x98) = 0;
        *(u16 *)(obj + 0x34) = (*(u16 *)(obj + 0x34) | 0x41) & ~0x1000;
        GetEulerAnglesFromMatrix(obj + 0xC0, obj + 0xF0);
        SpawnDebrisForMaskedParts(obj, 0x1FF, D_L03_001A8F20, 255, 3.0f, 5.0f, 5.0f, 10.0f);
        *(Quad *)target = 0;
        target[2] = 0.5f;
        matrix_mul_vec3(target, target, obj + 0xC0);
        FastVecAdd(target, target, obj + 0x10);
        for (i = 0x13; i >= 0; --i) {
            int kind;
            char *child;

            RandomDirectionVector(position, 0, 0.5f);
            FastVecAdd(position, position, target);
            *(Quad *)temporary = 0;
            temporary[0] = RandomSignedFloatRange(0, 2);
            temporary[1] = RandomSignedFloatRange(0, 2);
            temporary[2] = RandomFloatRange(5, 12);
            *(Quad *)velocity = *(Quad *)temporary;
            value = FastVecLength(velocity);
            vec_scale_to_length(velocity, velocity, value * 0.0166666675f);
            kind = 0x9D7;
            if (RandomIntBelow(2))
                kind = 0x9D4;
            *(Quad *)angles = 0;
            angles[0] = RandomAngle();
            angles[1] = RandomAngle();
            angles[2] = RandomAngle();
            *(Quad *)temporary = *(Quad *)angles;
            child = CreateCameraMoby(obj, 0, kind, -1, position, temporary, velocity, 255,
                RandomSignedFloatRange(45, 180) * 0.000290888245f, 20.0f);
            if (child)
                *(void (**)(char *))(child + 0x64) = UpdateTrashCanDebrisMoby;
        }
    }
}
