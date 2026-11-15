#include "include_asm.h"
#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
typedef struct { char pad[0x50]; float speed; char tail[0x8C]; } WeaponEntry;
typedef struct {
    char pad00[0x10];
    short frames, mode;
    float rate;
    short slot, handle;
    char *target;
    VectorBits velocity, origin;
} BeamState;
extern WeaponEntry D_L00_00262570[];
extern unsigned char D_0013957F[];
extern unsigned int D_L00_001AF6D4 __attribute__((sda));
extern char D_L00_001B8DC0[];
extern int func_002B4038(int, int);
extern char *func_0029EFD0(int);
extern void func_003001E0(void *, void *, void *);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern char *func_L00_0032A088(int, int);
extern void func_002AFFD8(char *, char *, int);
extern void func_00282D30(void *, void *, float);
extern void func_L00_003A8060(char *, char *);
extern void func_L00_003A8E28(void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_L00_003A80F8(char *, void *);

/* Spawn and configure one moving beam effect. */
char *func_L00_003A7C30(void *position, void *velocity, int handle, int mode)
{
    float normal[4], previous[4];
    char *moby;
    BeamState *state;
    float speed;
    if (handle == -1 || !IsSavedRecordValue(0x5CB /* Pulse Rifle */, handle))
        return 0;
    moby = CreateMoby(0x5D6 /* moby class 1494 */);
    if (moby != 0) {
        *(unsigned char *)(moby + 0x30) = 0xFF;
        *(unsigned short *)(moby + 0x32) = 0xFF;
        *(unsigned char *)(moby + 0x31) = 1;
        state = *(BeamState **)(moby + 0x68);
        qcopy(moby + 0x10, position);
        *(unsigned char *)(moby + 0x20) = 0;
        state->mode = mode;
        AddTransformedVectorOrCopy(state, velocity, position);
        speed = (gWeaponTable_L00 + D_0013957F[0])->speed * (1.0f / 60.0f);
        state->frames = FloatToInt(128.0f / speed);
        state->rate = 1.0f / IntToFloat(state->frames);
        state->handle = handle;
        state->target = GetSlotBody(0x5CB /* Pulse Rifle */, handle);
        ComputeViewDirection(moby + 0x10, (char *)normal, 1);
        FastVecScale(normal, normal, -1.0f);
        BuildMobyAxisVectors(moby, (char *)normal);
        if (D_L00_001AF6D4 >= 4)
            D_L00_001AF6D4 = 0;
        state->slot = D_L00_001AF6D4;
        D_L00_001AF6D4 = (int)(D_L00_001AF6D4 + 1) % 3;
        StoreTrailSample(moby);
        if (mode == 1) {
            qcopy(&state->origin, gCameraPosition_L00);
            vec_scale_to_length(&state->velocity, gCameraPosition_L00 + 0x230, FastVecLength(velocity));
        }
        if (mode == 2) {
            qcopy(previous, position);
            FastVecAdd(moby + 0x10, position, velocity);
            if (TestBeamSegmentHit(moby, previous))
                *(unsigned char *)(moby + 0x20) = 2;
        }
    }
    return moby;
}
