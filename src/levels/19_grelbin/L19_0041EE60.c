#include "common.h"

extern u16 *D_L19_001FB5A0[];
extern u8 *D_L19_001B2A1C[] __attribute__((sda));
extern s32 D_L19_001B2A38[] __attribute__((sda));
extern s32 D_001A79F0 __attribute__((sda));
extern char D_0019B4A8[];

extern void func_0029F338(u8 *);

extern struct { u8 header[0x464]; u8 entries[0]; } D_L19_0021EA30;
extern s32 D_L19_001B1D20 __attribute__((sda));
extern s32 D_L19_001B1D24 __attribute__((sda));

extern s32 func_002ACD38(void *);
extern float func_002A89A8(void *, s32, f32);
extern float func_002A7878(f32, f32);
extern s32 func_002B3BA8(u8 *, s32, f32, f32, s32, s32);
extern void func_002B0A68(u8 *, s32, void *, s32, f32, f32, f32, f32);
extern s32 func_002E5CF8(s32, s32, u8 *);
extern void func_002A7750(u8 *, s32, s32);
extern s32 func_00282948(void *);

#define GROUP(off) (*(s32 *)(state + (off)))
#define FOR_EACH_ID(p, off) \
    for (p = D_L19_001FB5A0[GROUP(off)]; \
         (GROUP(off) & 0xFF) != 0xFF && GROUP(off) <= D_L19_001B2A38[0] && p != 0 && \
         ((p != 0 && (s16)p[-1] >= 0) || p == D_L19_001FB5A0[GROUP(off)]); \
         p++)

/* Controls a group of Y.E.T.I.s kept at this spot. It lets them out one at a time while fewer than the allowed number are active. */
void func_L19_0041EE60(u8 *moby)
{
    u8 *state;
    s32 savedCount;

    if (IsObjectInSelectedZone(moby + 0x10) == 0)
        return;
    state = *(u8 **)(moby + 0x68);
    if (GROUP(0x120) == -1 ||
        (moby[0xB0] != 0xFF &&
         (D_L19_0021EA30.entries[(s16)*(u16 *)(moby + 0xB2)] != 0 ||
          ((savedCount = *(u8 *)(D_0019B4A8 + (((s16) * (u16 *)(moby + 0xB2) >> 1) + (gCurrentMapIndex << 10)))),
           (*(u16 *)(moby + 0xB2) & 1) ? ((savedCount >> 4) & 7) != 0 : (savedCount & 7) != 0)))) {
        MarkMobySpawned(moby);
        return;
    }
    switch (moby[0x20]) {
    case 0: {
        u16 *p;
        u8 *otherMoby;
        u8 *otherVars;
        f32 groundHeight;

        groundHeight = ProbeGroundHeightBelow(moby + 0x10, 0, 0.5f);
        groundHeight -= RandomFloatRange(0.1f, 0.3f);
        *(s16 *)(moby + 0x7C) = 0x1F;
        *(s32 *)(moby + 0x48) = 0;
        *(f32 *)(moby + 0x18) = groundHeight;
        FOR_EACH_ID(p, 0x120) {
            otherMoby = gMobyArray_L19[0] + ((*p & 0x7FFF) << 8);
            if (otherMoby == 0)
                break;
            if (*(s16 *)(otherMoby + 0xAA) == 0x10D0 /* Y.E.T.I. */) {
                otherVars = *(u8 **)(otherMoby + 0x68);
                *(f32 *)(otherVars + 0x22C) = *(f32 *)(state + 0x128) + 10.0f;
                *(s32 *)(otherVars + 0x26C) = 1;
                *(s32 *)(otherVars + 0x274) = 1;
            }
        }
        SetMobyState(moby, 1, -1);
        break;
    }
    case 1: {
        u8 *otherMoby;
        f32 burstVec[4];
        s32 gone;

        SelectAimTarget_002B3BA8(moby, -1, *(f32 *)(state + 0x128), *(f32 *)(state + 0x128), 0, 0);
        gone = 0;
        if (GROUP(0x138) == -1) {
            gone = 1;
        } else {
            otherMoby = gMobyArray_L19[0] + (GROUP(0x138) << 8);
            if (otherMoby == 0 || otherMoby[0x20] == 0xFE || otherMoby[0x20] == 0xFD)
                gone = 1;
        }
        if (GROUP(0x64) == 1 && gone) {
            qzero(burstVec);
            burstVec[2] = 0.15f;
            *(s16 *)(moby + 0x7C) = 0;
            SpawnDebrisForMaskedParts(moby, 0x1F, burstVec, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
            PlayMobySound(0, 0, moby);
            SetMobyState(moby, 3, -1);
        }
        break;
    }
    case 3: {
        u16 *p;
        u8 *otherMoby;
        u8 *otherVars;
        s32 found = 0;

        FOR_EACH_ID(p, 0x120) {
            otherMoby = gMobyArray_L19[0] + ((*p & 0x7FFF) << 8);
            if (otherMoby == 0)
                break;
            if (*(s16 *)(otherMoby + 0xAA) == 0x10D0 /* Y.E.T.I. */) {
                otherVars = *(u8 **)(otherMoby + 0x68);
                if (*(s32 *)(otherVars + 0x26C) == 1) {
                    qcopy(otherMoby + 0x10, moby + 0x10);
                    qcopy(otherVars + 0x210, moby + 0x10);
                    *(f32 *)(otherMoby + 0x18) = ProbeGroundHeightBelow(otherMoby + 0x10, 0, 1.0f);
                    found = 1;
                    *(s32 *)(otherVars + 0x26C) = 0;
                    *(u16 *)(otherMoby + 0x34) &= 0xFF7F;
                    break;
                }
            }
        }
        if (!found) {
            SetMobyState(moby, 4, -1);
        } else {
            GROUP(0x13C) = 200;
            SetMobyState(moby, 2, -1);
        }
        break;
    }
    case 2: {
        u16 *p;
        u8 *otherMoby;
        u8 *otherVars;
        s32 idleCount;

        SelectAimTarget_002B3BA8(moby, -1, *(f32 *)(state + 0x128) + 10.0f, *(f32 *)(state + 0x128), 0, 0);
        if (GROUP(0x64) == 1) {
            idleCount = 0;
            FOR_EACH_ID(p, 0x120) {
                otherMoby = gMobyArray_L19[0] + ((*p & 0x7FFF) << 8);
                if (otherMoby == 0)
                    break;
                if (*(s16 *)(otherMoby + 0xAA) == 0x10D0 /* Y.E.T.I. */) {
                    otherVars = *(u8 **)(otherMoby + 0x68);
                    if (*(s32 *)(otherVars + 0x26C) == 0) {
                        if (otherMoby[0x20] != 0xFE) {
                            if (otherMoby[0x20] != 0xFD)
                                idleCount++;
                        }
                    }
                }
            }
            if (gActiveYetiCount < gMaxActiveYetis) {
                if (idleCount < 3) {
                    if (FastFloatHelperD(state + 0x13C))
                        SetMobyState(moby, 3, -1);
                }
            }
        }
        break;
    }
    }
}
