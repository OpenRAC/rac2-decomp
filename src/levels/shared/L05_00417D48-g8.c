#include "common.h"

extern void func_L05_00418200(void *);
extern void func_00282C88(char *);
extern unsigned int D_001A7AF0 MACRO_ADDR;
/* A pointer table whose slot 0 holds the active object (L30_003B3F70-g8.c also reads it as an array). */
extern void *D_0018B650[] __attribute__((nosda));
extern char D_L05_001B34F0[] MACRO_ADDR;
extern char D_L05_001B3510[] MACRO_ADDR;
extern float D_L05_001B3500;
/* Model ids per equipment selector, one 4-entry table per D_001A7AF0 bit field. */
extern short D_L05_001A8F70[] MACRO_ADDR;
extern short D_L05_001A8F78[] MACRO_ADDR;
extern short D_L05_001A8F80[] MACRO_ADDR;
extern short D_L05_001A8F88[] MACRO_ADDR;
extern short D_L05_001A8F90[] MACRO_ADDR;
extern short D_L05_001A8F98[] MACRO_ADDR;
extern short D_L05_001A8FA0[] MACRO_ADDR;
extern char *func_L05_0041C708(void *, float, int, int);
extern char *func_L05_00432080(void *, float);
extern int func_002ED8A0(int);
extern int func_L05_0037AC00(void);
extern int func_L05_0037AC40(void);
extern int func_00282948(char *);
extern int func_002E59B0(void *, int);
extern int func_002E5CF8(int, int, void *);
extern void func_L05_00418288(void *);
extern void func_L00_004450C0(void *);

typedef struct {
    int f0;
    int f4;
    short f8;
    short fA;
    char padC[0x8];
    int f14;
    int f18;
    int f1C;
    char pad20[0x10];
    int f30;
    int f34;
    int f38;
    int f3C;
    char * f40;
    char * f44;
    char * f48;
    char * f4C;
    char * f50;
    int f54;
    int f58;
    int f5C;
    char pad60[0x40];
    int fA0;
    char padA4[0x8];
    char * fAC;
    char padB0[0x140];
    char * f1F0;
    char * f1F4;
    char * f1F8;
    char * f1FC;
    char * f200;
    char * f204;
    char * f208;
    int f20C;
    int f210;
    char pad214[0x4C];
    int f260;
    int f264;
    int f268;
    int f26C;
    int f270;
    char * f274;
    char * f278;
    int f27C;
} State_L05_00417D48;

typedef struct {
    char pad0[0x10];
    char pos[0x10];
    unsigned char state;
    char pad21[0x13];
    unsigned short modeBits;
    char pad36[0x32];
    State_L05_00417D48 *pVar;
} Obj_L05_00417D48;

/* State 0 spawns the equipment parts chosen by the D_001A7AF0 selector bits; state 1 updates timers and the
 * position copy. */
/* Updates the equipment holder object (moby class 4031). On its first frame it creates the player's equipment parts; after that it keeps its sound, timers and light going. */
void func_L05_00417D48(Obj_L05_00417D48 *object)
{
    State_L05_00417D48 *vars = object->pVar;
    int phase = object->state;
    int partClass;
    unsigned int selector;

    switch (phase) {
    case 0:
        vars->f30 = -1;
        vars->f270 = -1;
        vars->f260 = 1;
        vars->f264 = 0x3840;
        vars->f0 = 0;
        vars->f4 = 0;
        vars->f8 = 0;
        vars->fA = 0;
        vars->f20C = 0;
        vars->f210 = 0;
        vars->f14 = 0;
        vars->f18 = 0;
        vars->f1C = 0;
        vars->f34 = 0;
        vars->f38 = 0;
        vars->f3C = 0;
        vars->f268 = 0;
        vars->f26C = 0;
        vars->f27C = 0;
        object->state = 1;
        object->modeBits |= 0x100;
        func_L05_00418200(object);
        ClearVector128(gLightSpotSum);
        D_0018B650[0] = object;
        selector = gEquipmentBits & 3;
        gLightSpotCount = 0;
        object->modeBits |= 0x41;
        vars->f40 = SpawnEquipmentPartMoby(object, 0.05f, 0, D_L05_001A8F70[selector]);
        if (vars->f40) *(int *)(vars->f40 + 0x98) = 0;
        selector = (gEquipmentBits >> 2) & 3;
        partClass = D_L05_001A8F78[selector];
        vars->f44 = SpawnEquipmentPartMoby(object, 0.05f, 0, partClass);
        vars->f48 = SpawnEquipmentPartMoby(object, 0.05f, 1, partClass);
        if (vars->f44) *(int *)(vars->f44 + 0x98) = 0;
        if (vars->f48) *(int *)(vars->f48 + 0x98) = 0;
        selector = (gEquipmentBits >> 4) & 3;
        vars->f4C = SpawnEquipmentPartMoby(object, 0.05f, 0, D_L05_001A8F80[selector]);
        if (vars->f4C) *(int *)(vars->f4C + 0x98) = 0;
        vars->f50 = CreateTransformClone(object, 0.05f);
        selector = (gEquipmentBits >> 6) & 1;
        partClass = D_L05_001A8F88[selector];
        vars->fAC = SpawnEquipmentPartMoby(object, 0.05f, 0, partClass);
        vars->f1F0 = SpawnEquipmentPartMoby(object, 0.05f, 1, partClass);
        if (vars->fAC) *(int *)(vars->fAC + 0x98) = 0;
        if (vars->f1F0) *(int *)(vars->f1F0 + 0x98) = 0;
        selector = (gEquipmentBits >> 9) & 1;
        partClass = D_L05_001A8F98[selector];
        vars->f1F4 = SpawnEquipmentPartMoby(object, 0.05f, 0, partClass);
        vars->f1F8 = SpawnEquipmentPartMoby(object, 0.05f, 1, partClass);
        if (vars->f1F4) *(int *)(vars->f1F4 + 0x98) = 0;
        if (vars->f1F8) *(int *)(vars->f1F8 + 0x98) = 0;
        if (FindLastUsedChainEntry(3)) {
            selector = (gEquipmentBits >> 7) & 3;
            partClass = D_L05_001A8F90[selector];
            if (partClass) {
                vars->f1FC = SpawnEquipmentPartMoby(object, 0.05f, 0, partClass);
                vars->f200 = SpawnEquipmentPartMoby(object, 0.05f, 1, partClass);
                if (vars->f1FC) *(int *)(vars->f1FC + 0x98) = 0;
                if (vars->f200) *(int *)(vars->f200 + 0x98) = 0;
            }
        }
        selector = (gEquipmentBits >> 10) & 3;
        partClass = D_L05_001A8FA0[selector];
        vars->f204 = SpawnEquipmentPartMoby(object, 0.05f, 0, partClass);
        vars->f208 = SpawnEquipmentPartMoby(object, 0.05f, 1, partClass);
        if (vars->f204) *(int *)(vars->f204 + 0x98) = 0;
        if (vars->f208) *(int *)(vars->f208 + 0x98) = 0;
        if (FindLastUsedChainEntry(4) != -1) {
            vars->f274 = SpawnEquipmentPartMoby(object, 0.05f, 0, 0x10E2 /* moby class 4322 */);
            if (vars->f274) *(int *)(vars->f274 + 0x98) = 0;
        }
        if (FindLastUsedChainEntry(5) != -1) {
            vars->f278 = SpawnEquipmentPartMoby(object, 0.05f, 0, 0x10E4 /* moby class 4324 */);
            if (vars->f278) *(int *)(vars->f278 + 0x98) = 0;
        }
        vars->f58 = 70;
        vars->f54 = 60;
        vars->f5C = 0;
        vars->fA0 = 0;
        break;
    case 1:
        if (GetShieldSlotValue() < GetShieldSlotLimit()) vars->f260 = phase;
        if (vars->f260) {
            if (FastFloatHelperD((char *)&vars->f264)) vars->f268 = phase;
        }
        if (!IsVoicePlayingForOwner(object, vars->f30)) vars->f30 = PlayMobySound(0, 4, object);
        UpdateWobblingLight(object);
        qcopy(D_L05_001B3510, object->pos);
        ForwardResidentAddress(object);
        break;
    }
}
