#include "include_asm.h"
#include "names.h"
/* func_L04_003EE7C0: the level-04 copy of func_L00_003C2FC8 (aim-assist target query),
 * over level 04's tuning block and tables. Same -g unit reasons as the twin. */
typedef int AimWord128 __attribute__((mode(TI)));
typedef union { AimWord128 word; float f[4]; } AimVector;
typedef struct { unsigned int words[5]; } AimQueryConfig;
typedef struct { char prefix[0x54]; float cooldown; char suffix[0xE0-0x58]; } AimTuning;
typedef union { unsigned char b[0x2600]; short h[0x1300]; int i[0x980]; unsigned int u[0x980]; float f[0x980]; unsigned char *ptr[0x980]; } Hero;
#define H ((Hero *)D_00189E20)
#define PAD ((Hero *)D_00138180)
struct Rac2Native_5f824a0e369ccf7b_src_record {
    unsigned char b0,b1,b2,b3;
    unsigned short s4,s6,s8,s10,s12;
    unsigned char e,f;
};
extern AimQueryConfig D_L04_001B01B0;
extern AimTuning D_L04_0027B470[];
extern struct Rac2Native_5f824a0e369ccf7b_src_record D_L04_002BA6C0[];
extern unsigned char D_00189E20[];
extern unsigned char D_00138180[];
extern unsigned char D_00139592[];
extern float D_L04_001B01A0 __attribute__((sda));
extern float D_L04_001B01A4 __attribute__((sda));
extern float D_L04_001B01A8 __attribute__((sda));
extern float D_L04_001B01AC __attribute__((sda));
extern int D_L04_001B2F38;
extern void func_0029FCC0(char *, int, char *);
extern void func_002A75E0(void *, int, int, int, int);
extern int func_002AB1F0(unsigned char *);
extern int func_00282948(void *);
extern unsigned char *func_002AF580(void *, void *, void *, float, float, int, int, int, float, float, float, int, AimQueryConfig *);
extern void func_002FDF40(void *, void *, void *, int, float, float, float, float);
extern int func_002FE5A0(void *, void *, void *, void *, void *, int, int, float);
extern void func_L00_002AF7D0(void);
extern int func_L00_002D3F30(int, int);
extern void func_L00_002AF568(void);
extern int func_L00_002D6998(struct Rac2Native_5f824a0e369ccf7b_src_record *);
extern int func_002E5CF8(int, int, char *);
extern char *func_L00_003E7650(int, char *, char *);
extern int func_L00_002D4040(int);
extern void func_L00_002D6B70(int);
extern int func_002829D8(void *);
extern void func_L00_003C33E0(void *);
extern void func_L00_002E6EF8(void (*)(void *), void *);

/* Updates the player's Mini-Nuke: finds an aim target and, when the fire button is pressed, launches the shot and starts its sound. */
void func_L04_003EE7C0(unsigned char *moby) {
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    unsigned char *aimTarget;
    char *targetInfo;
    AimVector position;
    AimQueryConfig config;
    AimVector scratch;
    int allowed;
    TransformMobyJointToWorld((char *)moby, 0, (char *)&position);
    if (moby[0x42] == moby[0x43] && (moby[0x60] & 2))
        StartAnimationBlendedWithFlags(moby, 1, 0, 2, 0);
    aimTarget = 0;
    if (H->ptr[0x1450 / 4] && H->ptr[0x1450 / 4][0x20] != 0xFE && H->ptr[0x1450 / 4][0x20] != 0xFD) {
        targetInfo = (char *)GetMobyPrivateValue0(H->ptr[0x1450 / 4]);
        if (targetInfo && *(float *)targetInfo > 0.0f)
            aimTarget = H->ptr[0x1450 / 4];
    }
    allowed = 1;
    if (H->i[0x2294 / 4] == 0x1D || H->i[0x2294 / 4] == 1) {
        if (FastFloatHelperD(&H->i[0x2534 / 4]) == 0)
            allowed = 0;
    } else {
        H->i[0x2534 / 4] = 0x28;
        if (!aimTarget) {
            config = D_L04_001B01B0;
            aimTarget = SelectBestTargetInCone(&position, &H->b[0x760], &scratch, 0.392699093f, 0.785398185f,
                                  0, 0, 0, 11.1f, 0.0f, 0.0f, 0, &config);
        }
    }
    CalculateAimedLaunchVelocity(&config, &position, aimTarget, 0, D_L04_001B01A4, D_L04_001B01A0,
                   D_L04_001B01AC * 0.016666668f, D_L04_001B01A8 * 0.00027777778f);
    *(int *)(vars + 0x24) = TraceProjectileToImpact(&position, &config, vars, vars + 0x10, moby, 0, 0,
                                          D_L04_001B01A8 * 0.00027777778f);
    switch (moby[0x20]) {
    case 0:
        moby[0x20] = 1;
        *(int *)(vars + 0x2C) = -1;
        *(float *)(vars + 0x20) = 0.0f;
        *(int *)(vars + 0x28) = 0;
    case 1:
        if (H->i[0x1D8 / 4] >= 21)
            cancel_hero_item_animation();
        if (allowed && *(float *)(vars + 0x20) == 0.0f && !H->b[0x22BC] && (PAD->u[0x1A0 / 4] & H->u[0x1230 / 4]) && H->i[0x1240 / 4] >= 23) {
            if (SpendWeaponAmmo(-1, 1)) {
                D_L04_001B2F38 = 1;
                start_equipped_item_animation();
                *(int *)(vars + 0x2C) = CopyRecordsToFreeSlots(D_L04_002BA6C0);
                StartAnimationBlendedWithFlags(moby, 2, 0, 2, 0);
                SpawnMiniNukeProjectile((int)moby, (char *)&position, (char *)&config);
                PlayMobySound(0, 0, (char *)moby);
                {
                AimTuning *tuning = &D_L04_0027B470[D_00139592[0]];
                *(float *)(vars + 0x20) = 1.0f / tuning->cooldown;
            }
            } else if ((PAD->u[0x1A4 / 4] & H->u[0x1230 / 4]) || D_L04_001B2F38 == 1) {
                PlayMobySound(1, 0, (char *)moby);
                D_L04_001B2F38 = 0;
            }
            if (!(PAD->u[0x1A0 / 4] & H->u[0x1230 / 4]) || !get_ammo(-1) || !H->b[0x22B8]) {
                if (*(int *)(vars + 0x2C) >= 0) {
                    ResetActiveSlots(*(int *)(vars + 0x2C));
                    *(int *)(vars + 0x2C) = -1;
                }
            }
        }
    }
    FastVectorHelperB(vars + 0x20);
    AddDrawCallbackToList3(ApplyActiveEffect, moby);
}
