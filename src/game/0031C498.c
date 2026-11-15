#include "common.h"

extern float func_00283B98(float, float);
extern float func_00282C48(float);
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);
extern int func_002A77E0(int);
extern int D_001AFAFC SDATA(D_001AFAFC);
extern void func_0031D070(void *, int);
extern int func_002E59B0(void *, int);
extern int func_002E5CF8(int, int, void *);
extern void func_002E59F8(int);
extern void func_002AB8C0(void *, void *);
extern int func_00282978(void *);
extern char D_00188660[];

/* Turns the three attached parts toward the target and throws sparks from them while active. It keeps a looping sound going, and stops it when the object is not active. */
void func_0031C498(char *object)
{
    float axis[4];
    char *state = *(char **)(object + 0x68);
    if (*(unsigned char *)(object + 0x95) != 0 &&
        *(unsigned char *)(object + 0x20) != 3 &&
        *(unsigned char *)(object + 0x95) != 5 &&
        *(int *)(state + 0x294) == 0) {
        *(float *)(state + 0x27C) = FastAddRotations(*(float *)(state + 0x27C), 0.3141593039035797f);
        if (0.00001f <= FloatAbs(*(float *)(state + 0x27C))) {
            char *target;
            target = *(char **)(state + 0x270);
            BuildAxisAngleQuaternion(axis, target + 0xE0, *(float *)(state + 0x27C));
            { char *row = *(char **)(state + 0x270) + 0xC0;
                RotateVectorByQuaternion(row, row, axis); }
            { char *row = *(char **)(state + 0x270) + 0xD0;
                RotateVectorByQuaternion(row, row, axis); }
            target = *(char **)(state + 0x274);
            BuildAxisAngleQuaternion(axis, target + 0xE0, *(float *)(state + 0x27C));
            { char *row = *(char **)(state + 0x274) + 0xC0;
                RotateVectorByQuaternion(row, row, axis); }
            { char *row = *(char **)(state + 0x274) + 0xD0;
                RotateVectorByQuaternion(row, row, axis); }
            target = *(char **)(state + 0x278);
            BuildAxisAngleQuaternion(axis, target + 0xE0, *(float *)(state + 0x27C));
            { char *row = *(char **)(state + 0x278) + 0xC0;
                RotateVectorByQuaternion(row, row, axis); }
            { char *row = *(char **)(state + 0x278) + 0xD0;
                RotateVectorByQuaternion(row, row, axis); }
        }
        /* Each snapshot is consumed by the immediately following opaque call;
         * no C memory access crosses the non-clobbering transfer. */
        if (RandomIntBelow(D_001AFAFC) == 1) {
            qcopy_nc(axis, *(char **)(state + 0x270) + 0x10);
            SpawnSparkPairs_0031D070(axis, 1);
        }
        if (RandomIntBelow(D_001AFAFC) == 1) {
            qcopy_nc(axis, *(char **)(state + 0x274) + 0x10);
            SpawnSparkPairs_0031D070(axis, 1);
        }
        if (RandomIntBelow(D_001AFAFC) == 1) {
            qcopy_nc(axis, *(char **)(state + 0x278) + 0x10);
            SpawnSparkPairs_0031D070(axis, 1);
        }
        if (!IsVoicePlayingForOwner(*(void **)(state + 0x278), *(int *)(state + 0x290)))
            *(int *)(state + 0x290) = PlayMobySound(0, 4, *(void **)(state + 0x278));
    } else {
        int handle = *(int *)(state + 0x290);
        if (handle != -1) {
            char *sound = gSoundState + handle * 112;
            if (*(char **)(sound + 0x88) == *(char **)(state + 0x278) &&
                *(unsigned char *)(sound + 0x74) != 0)
                StopSoundVoice(handle);
        }
        *(int *)(state + 0x290) = -1;
    }
    UpdateColorFade(object, state + 0x50);
    FastDecTimer(state + 0x240);
    FastDecTimer(state + 0x242);
    if (*(unsigned short *)(object + 0x96) < 0xFFFF)
        *(unsigned short *)(object + 0x96) += 1;
}
