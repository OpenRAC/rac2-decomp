#include "include_asm.h"

#include "common.h"
typedef struct CrateMoby CrateMoby;
typedef struct {
    char pad00[0x10];
    int collision;               
} CrateClass;
typedef struct {
    char pad00[0x24];
    int flags;                   
    char pad28[4];
    float f2C;                   
} CrateHit;
typedef struct {
    char pad00[0x1E];
    unsigned short flags;        
} CrateColl;
typedef struct {
    char pad00[0x20];
    CrateColl coll;              
    char pad40[0x90 - 0x40];
    float f90[4];                
    CrateMoby *above;            
    CrateMoby *below;            
    int fA8;                     
    int flags;                   
    char padB0[4];
    int frame;                   
    long long savedColor;        
    char padC0[6];
    short fC6;                   
    unsigned char respawns;      
    unsigned char respawnTimer;  
    unsigned char burstFrame;    
    char padCB;
    int fCC;                     
    char padD0[0xFC - 0xD0];
    void *linked;                
    int f100;                    
} CrateVars;
struct CrateMoby {
    char pad00[0x10];
    float position[4];           
    unsigned char state;         
    unsigned char group;         
    char pad22[2];
    CrateClass *pclass;          
    char pad28[0x31 - 0x28];
    unsigned char visible;       
    short drawDistance;          
    unsigned short flags;        
    char pad36[2];
    long long color;             
    char pad40[0x68 - 0x40];
    CrateVars *vars;             
    char pad6C[0x98 - 0x6C];
    int collision;               
    char pad9C[0xA8 - 0x9C];
    unsigned char hitSlot;       
    char padA9;
    short oClass;                
    char padAC[0xB4 - 0xAC];
    short fB4;                   
    char padB6[0xBC - 0xB6];
    unsigned char command;       
    char padBD[0xC0 - 0xBD];
    float forward[4];            
    char padD0[0x10];
    float up[4];                 
};
typedef struct {
    char pad000[0x26C];
    CrateMoby *collHitMoby;      
    CrateMoby *f270;             
    char pad274[0x33C - 0x274];
    CrateMoby *groundMoby;       
    char pad340[0x34E - 0x340];
    short airFrames;             
    char pad350[0x588 - 0x350];
    CrateMoby *ledgeMoby;        
    char pad58C[0x2290 - 0x58C];
    CrateMoby *moby;             
    char pad2294[0x229C - 0x2294];
    int f229C;                   
} CrateHero;
typedef struct {
    float position[4];           
    CrateMoby *moby;             
    int f14;                     
    char pad18[4];
    float f1C;                   
    int f20;                     
    char pad24[0xC];
} __attribute__((aligned(16))) CrateBurst;
extern int D_001B1688 MACRO_ADDR;
extern char D_00189E20[];
extern char D_001BF000[];
extern int D_0018C0BC;
#define HERO ((CrateHero *)D_00189E20)
extern void func_US2_003133F8(CrateMoby *);
extern CrateHit *func_002A9640(CrateMoby *, int, int);
extern int func_002ABB78(CrateMoby *);
extern void func_00282C88(void *);
extern void func_003116E8(CrateMoby *);
extern void *func_00312E20(CrateMoby *, int);
extern int func_002B3868(CrateMoby *);
extern void func_003120C8(CrateMoby *, int, CrateHit *);
extern void func_US2_00312D68(CrateMoby *);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283CE0(int);
extern int func_00277F48(void *, int, CrateMoby *, void *, float);
extern void func_002A9850(CrateMoby *, void *, void *, int, CrateMoby *, int, int, int, float, float, float);
extern int func_002A7820(int, int);
extern void func_0029F338(CrateMoby *);
extern int func_00283DB8(void *, float);
extern int func_002829A8(unsigned char *);
extern void func_002A7750(CrateMoby *, int, int);
extern int func_002A8600(CrateMoby **, int, int, int);
extern int func_002A86E8(CrateMoby **, CrateMoby *, int, int);
extern float func_00282E80(void *, void *);
extern float func_002A89A8(void *, int, float);
extern void func_002E5CF8(int, int, CrateMoby *);
extern void func_002A0488(CrateMoby *, int, int, int);

void func_US2_00311C90(CrateMoby *moby)
{
    CrateBurst burst;
    float position[4] __attribute__((aligned(16)));
    CrateMoby *found;
    CrateVars *vars = moby->vars;
    CrateHit *hit;
    int touched;
    CrateColl *coll = &vars->coll;

    if (vars->flags & 0xC) {
        if (vars->frame != D_001B1688) {
            func_US2_003133F8(moby);
        }
    }
    if (vars->above == 0) {
        coll->flags |= 1;
    }
    hit = func_002A9640(moby, 0x5830001, 0);
    touched = 0;
    if (hit != 0 && hit->flags == 0x1000000) {
        hit = 0;
        touched = 1;
    }
    switch (moby->state) {
    case 0:
        if (vars->above != 0 && !func_002ABB78(vars->above)) {
            vars->above = 0;
        }
        if (vars->below != 0 && !func_002ABB78(vars->below)) {
            vars->below = 0;
        }
        func_00282C88(vars->f90);
        moby->state = 1;
        vars->fA8 = 0;
        if (moby->oClass == 0x1FF) {
            vars->frame++;
        }
        if (vars->fCC == 0) {
            vars->flags |= 0x14;
            if ((vars->flags ^ 1) & 1) {
                func_003116E8(moby);
            }
        }
        vars->linked = 0;
        if (moby->oClass == 0x1FF) {
            vars->fC6 = 100;
        } else if (moby->oClass == 0x1F5) {
            vars->linked = func_00312E20(moby, 0);
        } else if (moby->oClass == 0x200) {
            vars->linked = func_00312E20(moby, 1);
        }
        break;
    case 1:
        if (func_002B3868(moby)) {
            vars->f100 = 0;
        }
        if (moby->oClass == 0x1F9 &&
            (HERO->f270 == moby || HERO->collHitMoby == moby ||
             (HERO->groundMoby == moby && HERO->airFrames == 0) ||
             HERO->ledgeMoby == moby || touched)) {
            if (HERO->f229C == 15) {
                func_003120C8(moby, 1, 0);
                func_US2_00312D68(moby);
                break;
            }
            moby->command = 0;
            moby->state = 5;
            break;
        }
        if (hit != 0 && hit->f2C > 0.0f) {
            int doHit = 1;

            if (moby->oClass == 0x1F6 && !(hit->flags & 0x20000)) {
                doHit = 0;
            }
            if (moby->oClass == 0x1F9) {
                moby->state = 5;
                if (hit->flags & 0x20000) {
                    moby->command = 1;
                } else {
                    moby->command = func_00283CF0(func_002A7878(5.0f, 15.0f));
                }
                vars->savedColor = moby->color;
                doHit = 0;
            }
            if (doHit) {
                func_003120C8(moby, moby->oClass == 0x1F9, hit);
                func_US2_00312D68(moby);
            }
            moby->hitSlot = 255;
        }
        break;
    case 2:
        if (--moby->command == 255) {
            moby->hitSlot = 255;
            moby->state = 1;
        }
        break;
    case 3:
        if (moby->oClass == 0x1F9 && vars->burstFrame < 21) {
            float radius;
            int target;

            burst.moby = moby;
            burst.f1C = 2.0f;
            qcopy(&burst, moby->forward);
            burst.f20 = 0;
            func_00282F20(position, moby->up, 0.5f);
            func_00282CC0(position, position, moby->position);
            radius = func_00283CE0(vars->burstFrame) * 0.05f;
            burst.f14 = 1;
            func_00277F48(position, 16, moby, &burst, radius + radius);
            burst.f14 = 0x30000;
            target = func_00277F48(position, 16, HERO->moby, 0, radius * 3.0f);
            if (target != 0) {
                func_002A9850(moby, position, D_001BF000, target, HERO->moby, 0x10000, 0, 0x30000, 4.0f, 1.0f, 1.0f);
            }
            vars->burstFrame++;
        } else if (vars->respawns != 0) {
            moby->flags = (moby->flags | 0x41) & 0xEFFF;
            moby->collision = 0;
            if (moby->fB4 >= 2) {
                moby->fB4 = 1;
            }
            moby->state = 6;
            if (vars->respawnTimer != 255) {
                vars->respawnTimer = func_002A7820(30, 60);
            }
        } else {
            func_0029F338(moby);
            break;
        }
        moby->hitSlot = 255;
        break;
    case 6:
        vars->f100++;
        if (vars->respawnTimer == 255) {
            break;
        }
        qcopy(&burst, moby->position);
        burst.position[2] += 0.5f;
        burst.position[3] = 1.0f;
        if (func_00283DB8(&burst, (float)moby->drawDistance) != -1 || !func_002829A8(&vars->respawnTimer)) {
            goto done;
        }
        if (moby->group == 255) {
            func_002A7750(moby, 1, -1);
            moby->flags = (moby->flags & 0xFFBE) | 0x1000;
            moby->collision = moby->pclass->collision;
            break;
        }
        func_002A8600(&found, moby->group, 0, 0);
        while (found != 0) {
            if (moby != found && !(func_00282E80(moby->position, found->position) > 0.1f) && found->state == 1) {
                CrateVars *other = found->vars;

                if (other->above == 0) {
                    qcopy(moby->position, found->position);
                    moby->position[2] += 1.0f;
                    other->above = moby;
                    vars->below = found;
                    vars->above = 0;
                    moby->state = 1;
                    moby->visible = 1;
                    moby->flags &= 0xFFFE;
                    moby->collision = moby->pclass->collision;
                    moby->flags |= 0x1000;
                    break;
                }
            }
            func_002A86E8(&found, found, 0, 0);
        }
        if (moby->state != 1) {
            moby->position[2] = func_002A89A8(moby->position, 0, 0.5f);
            moby->state = 1;
            vars->above = 0;
            vars->below = 0;
            moby->visible = 1;
            moby->flags &= 0xFFFE;
            moby->collision = moby->pclass->collision;
        }
        goto done;
    case 5:
        if (moby->command == 0) {
            moby->command = 179;
            vars->savedColor = moby->color;
        } else if (moby->command >= 16 && hit != 0) {
            moby->command = func_00283CF0(func_002A7878(5.0f, 15.0f));
        }
        if (moby->command % 60 == 57 || moby->command == 13) {
            func_002E5CF8(1, 32, moby);
        }
        if (moby->command % 60 > 40 || moby->command < 15) {
            func_002A0488(moby, 200, 64, 64);
        } else {
            moby->color = vars->savedColor;
        }
        if (moby->command == 1 || D_0018C0BC == 22) {
            moby->color = vars->savedColor;
            func_003120C8(moby, 1, 0);
            func_US2_00312D68(moby);
        }
        moby->hitSlot = 255;
        moby->command--;
        break;
    case 4:
        if (func_002829A8(&moby->command)) {
            moby->state = 1;
            moby->flags &= 0xFFFE;
        }
done:
        moby->hitSlot = 255;
        break;
    }
}
