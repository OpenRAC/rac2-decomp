#include "include_asm.h"

#include "common.h"
extern void func_PAL_L00_002AF6C0(void);
extern void func_00283098(void *, void *, void *);
extern char D_L01_002637A0[];
extern float func_00283B98(float f12, float f13);
typedef int HeroQuad __attribute__((mode(TI)));
extern char D_00189E20[];
extern unsigned char D_00139568[];
extern char D_L01_001B7B00[];
extern int func_L00_002D4040(int);
extern int func_L00_002ADEA0(int);
extern void func_L00_00311080(void *, void *, int, int, int, int);
extern void func_L00_00310D30(void *, void *);
extern void func_002AA2E8(void *, float, float);
extern void func_L00_00310C88(void *, void *);
extern void func_00282C88(void *);
extern void func_00283098(void *, void *, void *);
extern float func_00283B98(float, float);
typedef struct MobyModel {
    char pad00[0x10];
    int f10;
    char pad14[0x32];
    short kind;                  
} MobyModel;
typedef struct Moby {
    char pad00[5];
    unsigned char flags;
    char pad06[2];
    float fade;                  
    char pad0C[0x17];
    unsigned char animation;     
    MobyModel *model;            
    int f28;
    char pad2C[5];
    unsigned char f31;
    char pad32[2];
    unsigned short state;        
    char pad36[2];
    char *buffer0;               
    char *buffer1;               
    char pad40[0x58];
    int f98;
    char pad9C[0x24];
    HeroQuad matrix[3];          
    char padF0[0x10];
} Moby;
typedef struct WeaponInfo {
    char pad00[0x2C];
    int animation;               
    int altAnimation;            
    char pad34[0xAC];
} WeaponInfo;
typedef struct HeroState {
    char pad00[0x90];
    HeroQuad position;           
    char padA0[0x730 - 0xA0];
    HeroQuad matrix[3];          
    float f760;
    char pad764[0xC];
    union {
        HeroQuad quad;
        float v[4];
    } f770;                      
    char pad780[0xE98 - 0x780];
    Moby *attached[2];           
    char padEA0[4];
    int attachedMode;            
    char padEA8[0x2290 - 0xEA8];
    Moby *moby;                  
    char pad2294[8];
    int state;                   
    char pad22A0[0x22B8 - 0x22A0];
    unsigned char f22B8;
    char pad22B9;
    unsigned char f22BA;
    char pad22BB[8];
    unsigned char f22C3;
    char pad22C4[0x24B0 - 0x22C4];
    int animation;               
    int weaponId;                
} HeroState;
extern void func_PAL_L00_002AF6C0(void);
extern char D_00189E20[];

/* For the hero's two attached mobys: point them at their buffers, start the animation the
   current item's table entry names, fade them in or out (removing one that has faded out),
   then copy the hero moby's matrix to hero + 0x730 and ease hero + 0x778 to 0. */
void func_PAL_L01_002B0208(void)
{
    HeroState *hero;
    HeroState *state;
    HeroQuad *matrix;
    WeaponInfo *weapon;
    int weaponId, animation;
    int i;

    hero = (HeroState *)D_00189E20;
    if (hero->f22B8 && hero->f22BA && !func_L00_002D4040(-1))
        func_PAL_L00_002AF6C0();
    for (i = 0; i < 2; i++) {
        HeroState *player = (HeroState *)D_00189E20;
        Moby **slot = &player->attached[i];

        if (*slot) {
            (*slot)->buffer0 = D_L01_001B7B00 + i * 0xC00;
            (*slot)->buffer1 = D_L01_001B7B00 + 0x600 + i * 0xC00;
            weaponId = func_L00_002ADEA0(0);
            if (weaponId == player->weaponId) {
                weapon = &((WeaponInfo *)D_L01_002637A0)[D_00139568[weaponId]];
                animation = weapon->animation;
                if (player->state == 12)
                    animation = weapon->altAnimation;
                if (animation != -1 && (*slot)->animation != animation) {
                    player->animation = animation;
                    func_L00_00311080(player->moby, *slot, animation, 0, 7, 1);
                }
            }
            {
                HeroState *owner = (HeroState *)D_00189E20;

                func_L00_00310D30(owner->moby, *slot);
                if (owner->attachedMode) {
                    if (owner->attachedMode == 2)
                        func_002AA2E8(&(*slot)->fade, 0.0f, 0.3f);
                    else
                        func_002AA2E8(&(*slot)->fade, 0.0f, 0.08400001f);
                    hero = (HeroState *)D_00189E20;
                    if ((*slot)->fade == 0.0f) {
                        func_L00_00310C88(hero->moby, slot);
                        return;
                    }
                } else {
                    func_002AA2E8(&(*slot)->fade, 1.0f, 0.24000001f);
                    if (((*slot)->flags & 2) && !owner->f22BA) {
                        owner->attachedMode = 1;
                        (*slot)->f28 = 0;
                        owner->f22B8 = 0;
                        return;
                    }
                }
            }
        }
    }
    matrix = ((HeroState *)D_00189E20)->matrix;
    state = (HeroState *)D_00189E20;
    {
        Moby *moby = state->moby;

        matrix[0] = moby->matrix[0];
        matrix[1] = moby->matrix[1];
        matrix[2] = moby->matrix[2];
        func_00282C88(&state->f760);
    }
    state->f760 = 1.0f;
    func_00283098(&state->f760, &state->f760, matrix);
    state->f770.quad = state->position;
    if (!state->f22C3)
        state->f770.v[2] = func_00283B98(state->f770.v[2], 0.0f);
}
