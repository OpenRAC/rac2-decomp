/* Seven-state controller of a Dobbo level object.  It has a unit of its own for its switch
 * table.  It reads the entity table in both of retail's forms: $gp through the sda name, and
 * the tied absolute macro load (lui $r; lw $r) through the MACRO_ADDR alias. */
#include "common.h"
extern char *D_L09_001B285C __attribute__((sda));
extern char *D_L09_001B285C_1 MACRO_ADDR;
extern char *D_L09_001B294C __attribute__((sda));
extern s32 D_L09_001B2388;
extern s16 D_001A63F0[] __attribute__((nosda));
extern s32 D_001A79F0 MACRO_ADDR;
extern u8 D_001395B8[];
extern s32 D_001397C4 __attribute__((nosda));
extern s32 D_0018A160 __attribute__((nosda));
extern s32 D_0018C0B4 __attribute__((nosda));
extern char D_00189EA0[];
typedef struct { u8 pad[0x464]; u8 active[0]; } DobboFlags;
extern DobboFlags D_L09_0021E9F0;
extern u8 D_0019B4A8[][0x400];
extern s32 func_L09_00406BF8(s32, s32);
extern void func_L09_00406BA0(s32, u8);
extern void func_L09_00406C68(s32, s32, s32, s32);
extern void func_L09_00406C90(char *);
extern s32 func_L09_00406CC0(char *);
extern void func_L09_00406E78(char *);
extern void func_0029F338(char *);
extern void func_L00_003672F8(void);
extern void func_L00_002B9D60(char *, char *, s32, s32);
extern void func_L08_00328B80(s32, s32, s32, s32);
extern void func_0029B3E0(s32, s32);
extern void func_002A7750(char *, s32, s32);
extern s32 func_002B3868(char *);
extern void func_L01_00323310(s32, s32);
extern s32 func_L00_00329520(char *, s32);
#define FIELD(p,o) (*(s32 *)((p)+(o)))
/* Per-frame update of the Dobbo switch controller (moby class 3485): it turns linked lights, doors and lifts on and off as the hero uses it. */
void func_L09_00406FC8(u8 *obj)
{
    char *data = *(char **)(obj + 0x68);
    s32 mode, bits;
    u32 id;
    s32 index2;
    s32 index4;
    s32 index5;
    s32 index6;
    s32 index7;
    s32 index8;
    s32 index10;
    s32 index11;
    s32 index12;
    obj[0x30] = 0xFF;
    switch ((u8)obj[0x20]) {
    case 0:
        if (D_L09_001B2388 == 0) {
            index2 = FIELD(data,0x58);
            if (index2 != -1) {
                mode = (u8)D_L09_001B285C[(index2 << 8)+0x20];
                if (mode != 254) {
                    if (mode == 253) goto skip58;
                    if (CheckHeroTriggerResult(FIELD(data,0xC),-1)) {
                        MarkMobySpawned(D_L09_001B285C + (FIELD(data,0x58) << 8));
                        FIELD(data,0x58) = -1;
                    }
                }
            }
skip58:
            if ((u8)D_001395B8[0x2D] && FIELD(data,0x60) != -1) {
                char *other;
                SetFlagToOne();
                other = D_L09_001B285C_1;
                other += FIELD(data,0x60) << 8;
                ResetHeroPositionAndDirection(other+0x10,other+0xF0,0,1);
                D_001395B8[0x2D] = 0;
            }
            if ((u8)D_001395B8[0x1E]) {
                index4 = FIELD(data,0x40);
                if (index4 != -1 && FIELD(data,0x48) != -1)
                    FIELD(*(char **)(D_L09_001B285C+(index4<<8)+0x68),0) = FIELD(data,0x48);
            }
            index5 = FIELD(data,0x50);
            if (index5 == -1) goto inactive;
            {
                id = *(u16 *)((index5<<8) + (u32)D_L09_001B285C + 0xB2);
                if (D_L09_0021E9F0.active[(s16)id]) goto active;
                bits = D_0019B4A8[gCurrentMapIndex][(s16)id>>1];
                if (!((id & 1) ? ((bits>>4)&7) : (bits&7))) goto inactive;
active:
    SetMobyFlagsByIndex(FIELD(data,0x4C),1,1,1);
                ReleaseLinkedMoby(obj);
                goto after_active;
inactive:
    SetMobyFlagsByIndex(FIELD(data,0x4C),0,0,0);
after_active:
                ReleaseLinkedObjectsIfReady(obj);
            }
            if (!(u8)D_001395B8[0xA3]) {
                D_001395B8[0xA3] = 1;
                MemcardSave(0,-1);
            }
        }
        if (D_L09_001B2388 < 6) break;
        ActivateLinkedMobyIfValid(FIELD(data,0x30),0,0,-1);
        ActivateLinkedMobyIfValid(FIELD(data,0x34),0,0,-1);
        ActivateLinkedMobyIfValid(FIELD(data,0x38),0,-1,-1);
        ActivateLinkedMobyIfValid(FIELD(data,0x3C),0,0,0);
        SetMobyFlagsByIndex(FIELD(data,0x50),0,0,0);
        SetMobyFlagsByIndex(FIELD(data,0x54),0,0,-1);
        SetMobyFlagsByIndex(FIELD(data,0x58),0,0,0);
        SetMobyFlagsByIndex(FIELD(data,0x5C),0,0,-1);
        SetMobyFlagsByIndex(FIELD(data,0x68),0,0,0);
        SetMobyFlagsByIndex(FIELD(data,0x64),0,0,-1);
        if (CheckHeroTriggerResult(FIELD(data,0),FIELD(data,0x20))) {
            SetLinkedMobyState(FIELD(data,0x24),2);
            SetMobyFlagsByIndex(FIELD(data,0x50),0,0,0);
            SetMobyFlagsByIndex(FIELD(data,0x54),0,0,-1);
            SetMobyFlagsByIndex(FIELD(data,0x58),0,0,0);
            SetMobyFlagsByIndex(FIELD(data,0x5C),0,0,-1);
            SetMobyFlagsByIndex(FIELD(data,0x4C),0,0,0);
            SetMobyState(obj,1,-1);
        } else if (CheckHeroTriggerResult(FIELD(data,4),FIELD(data,0x24))) {
            SetLinkedMobyState(FIELD(data,0x20),2);
            SetMobyFlagsByIndex(FIELD(data,0x50),1,1,1);
            SetMobyFlagsByIndex(FIELD(data,0x54),1,1,-1);
            SetMobyFlagsByIndex(FIELD(data,0x58),1,1,1);
            index6 = FIELD(data,0x54);
            if (index6 != -1 && (u8)D_L09_001B285C[(index6<<8)+0x20] >= 3) {
                SetMobyFlagsByIndex(FIELD(data,0x5C),1,1,-1);
            } else {
                SetMobyFlagsByIndex(FIELD(data,0x5C),0,0,-1);
            }
            if (!ReleaseLinkedObjectsIfReady(obj) && D_001397C4 < 0) {
                SetMobyFlagsByIndex(FIELD(data,0x68),1,1,1);
                SetMobyFlagsByIndex(FIELD(data,0x64),1,-1,-1);
            }
            SetMobyState(obj,2,-1);
        } else if (IsPointInsideRegion(gHeroPosition,FIELD(data,0x10))) {
            SetLinkedMobyState(FIELD(data,0x20),2);
            SetMobyFlagsByIndex(FIELD(data,0x50),1,1,1);
            SetMobyFlagsByIndex(FIELD(data,0x54),1,1,-1);
            SetMobyFlagsByIndex(FIELD(data,0x58),1,1,1);
            SetMobyFlagsByIndex(FIELD(data,0x5C),1,1,-1);
            if (!ReleaseLinkedObjectsIfReady(obj) && D_001397C4 < 0) {
                SetMobyFlagsByIndex(FIELD(data,0x68),1,1,1);
                SetMobyFlagsByIndex(FIELD(data,0x64),1,-1,-1);
            }
            SetMobyState(obj,4,-1);
        }
        UpdateCollectedItemIndicator(obj);
        break;
    case 1:
        if (SetFirstPendingFlag(obj) && D_001A63F0[0] != FIELD(data,0x78))
            QueueKeyedRequest(FIELD(data,0x78),FIELD(data,0x74));
        if (!CheckHeroTriggerResult(FIELD(data,4),FIELD(data,0x24))) break;
        SetLinkedMobyState(FIELD(data,0x20),2);
        SetMobyFlagsByIndex(FIELD(data,0x50),1,1,1);
        SetMobyFlagsByIndex(FIELD(data,0x54),1,1,-1);
        SetMobyFlagsByIndex(FIELD(data,0x58),1,1,1);
        SetMobyFlagsByIndex(FIELD(data,0x5C),0,0,-1);
        index7 = FIELD(data,0x58);
        if (index7 == -1 || (u8)D_L09_001B285C[(index7<<8)+0x20] == 254 ||
            (u8)D_L09_001B285C[(index7<<8)+0x20] == 253) {
            ActivateLinkedMobyIfValid(FIELD(data,0x3C),1,1,1);
            FIELD(data,0x58) = -1;
        }
        SetMobyState(obj,2,-1);
        break;
    case 2:
        if (SetFirstPendingFlag(obj) && D_001A63F0[0] != FIELD(data,0x70))
            QueueKeyedRequest(FIELD(data,0x70),FIELD(data,0x74));
        index8 = FIELD(data,0x58);
        if (index8 == -1) goto after_release;
        mode = (u8)D_L09_001B285C[(index8<<8)+0x20];
        if (mode == 254) goto release;
        if (mode != 253) goto after_release;
release:
        ActivateLinkedMobyIfValid(FIELD(data,0x3C),1,1,1);
        FIELD(data,0x58) = -1;
after_release:
        if (CheckHeroTriggerResult(FIELD(data,0),FIELD(data,0x20))) {
            SetLinkedMobyState(FIELD(data,0x24),2);
            SetMobyFlagsByIndex(FIELD(data,0x50),0,0,0);
            SetMobyFlagsByIndex(FIELD(data,0x54),0,0,-1);
            SetMobyFlagsByIndex(FIELD(data,0x58),0,0,0);
            SetMobyFlagsByIndex(FIELD(data,0x5C),0,0,-1);
            SetMobyFlagsByIndex(FIELD(data,0x4C),0,0,0);
            SetMobyState(obj,1,-1);
        } else if (D_0018A160 && CheckHeroTriggerResult(FIELD(data,0xC),-1)) {
            ActivateLinkedMobyIfValid(FIELD(data,0x30),1,1,-1);
            D_001395B8[0x1E] = 1;
            index10 = FIELD(data,0x40);
            if (index10 != -1 && FIELD(data,0x48) != -1)
                FIELD(*(char **)(D_L09_001B285C+(index10<<8)+0x68),0) = FIELD(data,0x48);
            UpdateCollectedItemIndicator(obj);
            SetMobyState(obj,3,-1);
        }
        if ((u32)((u8)obj[0x20] - 1) < 2) break;
        /* State 3's common follow-up is also reached after the transition. */
    case 3:
        index11 = FIELD(data,0x54);
        if (index11 != -1 && (u8)D_L09_001B285C[(index11<<8)+0x20] >= 3)
            SetMobyFlagsByIndex(FIELD(data,0x5C),1,1,-1);
        if (!ReleaseLinkedObjectsIfReady(obj) && D_001397C4 < 0) {
            SetMobyFlagsByIndex(FIELD(data,0x68),1,1,1);
            SetMobyFlagsByIndex(FIELD(data,0x64),1,-1,-1);
        }
        if (!CheckHeroTriggerResult(FIELD(data,0xC),-1)) goto reset_to_2;
        if (D_0018C0B4 == 0x31) {
            UpdateCollectedItemIndicator(obj);
            SetLinkedMobyState(FIELD(data,0x24),2);
            ActivateLinkedMobyIfValid(FIELD(data,0x3C),0,0,0);
            SetMobyState(obj,4,-1);
        }
        break;
    case 4:
        if (CheckHeroTriggerResult(FIELD(data,0x10),-1)) {
            ActivateLinkedMobyIfValid(FIELD(data,0x30),0,0,-1);
            ReleaseLinkedObjectsIfReady(obj);
            SetMobyState(obj,5,-1);
        }
        break;
    case 5:
        UpdateCollectedItemIndicator(obj);
        if (!CheckHeroTriggerResult(FIELD(data,0xC),-1)) break;
        ReleaseLinkedMoby(obj);
        SetLinkedMobyState(FIELD(data,0x24),0);
        index12 = FIELD(data,0x6C);
        if (index12 != -1) {
            char *other = D_L09_001B294C + (index12<<7);
            ResetHeroPositionAndDirection(other+0x30,other+0x70,0,0);
        }
        ReleaseLinkedObjectsIfReady(obj);
        SetMobyState(obj,6,-1);
        break;
    case 6:
        ReleaseLinkedObjectsIfReady(obj);
        if (CheckHeroTriggerResult(FIELD(data,0),FIELD(data,0x20))) {
            SetMobyFlagsByIndex(FIELD(data,0x50),0,0,0);
            SetMobyFlagsByIndex(FIELD(data,0x54),0,0,-1);
            SetMobyFlagsByIndex(FIELD(data,0x58),0,0,0);
            SetMobyFlagsByIndex(FIELD(data,0x5C),0,0,-1);
            SetLinkedMobyState(FIELD(data,0x24),2);
            SetMobyState(obj,1,-1);
        } else if (!CheckHeroTriggerResult(FIELD(data,0xC),-1)) {
reset_to_2:
            SetLinkedMobyState(FIELD(data,0x24),0);
            SetMobyState(obj,2,-1);
        } else if (D_0018C0B4 == 0x31) {
            UpdateCollectedItemIndicator(obj);
            SetLinkedMobyState(FIELD(data,0x24),2);
            ActivateLinkedMobyIfValid(FIELD(data,0x3C),0,0,0);
            SetMobyState(obj,4,-1);
        }
        break;
    }
}
