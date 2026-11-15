#include "include_asm.h"
#include "names.h"
typedef struct { char pad0[0x80]; char position[0x2BC]; char *active; int enabled; char pad1[0x244]; char *other; char pad2[0x1D10]; int mode; } Globals;
extern Globals D_00189E20;
extern char *D_L08_001B29DC;
extern float D_L08_001B01E0 __attribute__((sda)), D_L08_001B01E4 __attribute__((sda)), D_L08_001B01E8 __attribute__((sda));
extern float D_L08_001B01EC __attribute__((sda)), D_L08_001B01F0 __attribute__((sda)), D_L08_001B01F4 __attribute__((sda)), D_L08_001B01F8 __attribute__((sda));
extern int func_L08_003D0098(int);
extern float func_00283180(float);
extern float func_00282E80(void *, void *);
extern float func_00283B98(float, float);
extern float func_00282C48(float);
extern void func_002E5CF8(int, int, void *);
extern void func_L08_003D0040(void *);

/* Seesaw beam: tilts when the hero stands on either end and rocks back toward level, playing a creak sound as it moves. */
void func_L08_003D00C8(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    float tiltAccel, previousTilt, tiltScale;
    float dampFactor;
    int linkedOn;
    switch ((unsigned char)moby[0x20]) {
    case 0:
        *(float *)(vars + 8) = 0;
        if (*(int *)(vars + 0x14) != -1) {
            char *beamEnd = (char *)((*(unsigned int *)(vars + 0x14) << 8) + (unsigned int)D_L08_001B29DC);
            int partState = (unsigned char)beamEnd[0x20];
            if (partState == 0xFE) goto first_done;
            if (partState == 0xFD) goto first_done;
            *(char **)vars = beamEnd;
        }
    first_done:
        if (*(int *)(vars + 0x18) != -1) {
            char *beamEnd = (char *)((*(unsigned int *)(vars + 0x18) << 8) + (unsigned int)D_L08_001B29DC);
            int partState = (unsigned char)beamEnd[0x20];
            if (partState == 0xFE) goto second_done;
            if (partState == 0xFD) goto second_done;
            *(char **)(vars + 4) = beamEnd;
        }
    second_done:
        *(int *)(vars + 0x10) = IsLinkedMobySwitchedOnSeesaw(*(int *)(vars + 0xC));
        moby[0x20] = 1;
        break;
    case 1:
        tiltAccel = 0;
        if (gHeroState.enabled) {
            if (gHeroState.active == *(char **)vars) {
                float tiltRate = FastSinOrCosA(*(float *)(moby + 0xF4));
                float heroDistance = vec_distance_xy(gHeroState.position, moby + 0x10);
                float weightFactor = D_L08_001B01E0;
                tiltRate *= 0.000004848137450608192f;
                tiltAccel = weightFactor * tiltRate * heroDistance / D_L08_001B01F0;
            }
            if (gHeroState.active == *(char **)(vars + 4)) {
                tiltScale = FastSinOrCosA(*(float *)(moby + 0xF4));
                tiltAccel = -(D_L08_001B01E0 * 0.000004848137450608192f) * tiltScale * vec_distance_xy(gHeroState.position, moby + 0x10) / D_L08_001B01F0;
            }
        }
        if (gHeroState.mode == 3) {
            if (gHeroState.other == *(char **)vars) {
                float tiltRate = FastSinOrCosA(*(float *)(moby + 0xF4));
                float heroDistance = vec_distance_xy(gHeroState.position, moby + 0x10);
                float weightFactor = D_L08_001B01E0;
                tiltRate *= 0.000004848137450608192f;
                tiltAccel = weightFactor * tiltRate * heroDistance / D_L08_001B01F0;
            }
            if (gHeroState.other == *(char **)(vars + 4)) {
                tiltScale = FastSinOrCosA(*(float *)(moby + 0xF4));
                tiltAccel = -(D_L08_001B01E0 * 0.000004848137450608192f) * tiltScale * vec_distance_xy(gHeroState.position, moby + 0x10) / D_L08_001B01F0;
            }
        }
        if (*(float *)(moby + 0xF4) > D_L08_001B01E4 * 0.01745329424738884f)
            {
            float overTilt = *(float *)(moby + 0xF4) - D_L08_001B01E4 * 0.01745329424738884f;
            float tiltRange = D_L08_001B01E8 * 0.01745329424738884f;
            overTilt /= tiltRange;
            tiltAccel -= D_L08_001B01EC * (overTilt * 0.000004848137450608192f);
        }
        else if (*(float *)(moby + 0xF4) < -D_L08_001B01E4 * 0.01745329424738884f)
            {
            float overTilt = D_L08_001B01E4 * 0.01745329424738884f + *(float *)(moby + 0xF4);
            float tiltRange = D_L08_001B01E8 * 0.01745329424738884f;
            overTilt /= tiltRange;
            tiltAccel -= D_L08_001B01EC * (overTilt * 0.000004848137450608192f);
        }
        previousTilt = *(float *)(vars + 8);
        *(float *)(vars + 8) += tiltAccel;
        *(float *)(moby + 0xF4) = FastAddRotations(*(float *)(moby + 0xF4), *(float *)(vars + 8));
        if ((FloatAbs(previousTilt) < 0.0002908882452175021f && FloatAbs(*(float *)(vars + 8)) > 0.0002908882452175021f) ||
            (FloatAbs(previousTilt) < 0.0014544413425028324f && FloatAbs(*(float *)(vars + 8)) > 0.0014544413425028324f) ||
            (FloatAbs(previousTilt) < 0.002908882685005665f && FloatAbs(*(float *)(vars + 8)) > 0.002908882685005665f))
            PlayMobySound(0, 0, moby);
        linkedOn = IsLinkedMobySwitchedOnSeesaw(*(int *)(vars + 0xC));
        if (FloatAbs(*(float *)(moby + 0xF4)) > D_L08_001B01F4 * 0.01745329424738884f && linkedOn) {
            *(float *)(vars + 8) = 0;
            moby[0x20] = 2;
        }
        dampFactor = D_L08_001B01F8;
        *(int *)(vars + 0x10) = linkedOn;
        *(float *)(vars + 8) *= dampFactor;
        AttachPartsToMoby(moby);
        break;
    case 2:
        if (!IsLinkedMobySwitchedOnSeesaw(*(int *)(vars + 0xC))) moby[0x20] = 1;
        break;
    }
}
