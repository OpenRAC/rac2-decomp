#include "common.h"
extern void func_0029F338(void *);
extern int func_L00_00324120(void *);
extern int func_002ACBC8(void *,int);
extern int func_L13_002CEF00(int,int);
extern void func_002ACEC0(void *,void *,void *,float);
extern float func_00282E80(void *,void *);
extern struct { char pad[0x348]; short state; } D_00189E20;
extern char D_00189EA0[];
/* Gate that swings open when the player triggers it, stays open while the player is near, and closes again when the player leaves. */
void func_L13_003FE420(char *moby) {
    char *vars=*(char **)(moby+0x68);
    if (!vars) { MarkMobySpawned(moby); return; }
    switch (*(u8 *)(moby+0x20)) {
    case 0:
        *(int *)(vars+0xC)=0;
        *(int *)(vars+4)=0;
        *(u16 *)(moby+0x34)|=0x100;
        if (*(int *)vars) *(u8 *)(moby+0x20)=1;
        else *(u8 *)(moby+0x20)=4;
        break;
    case 1:
        if (IsCurrentSelectedId(moby)) {
            if (gHeroState.state==1 && IsPointInCuboid((char *)&gHeroState+0x80,*(int *)(vars+8))) {
                *(u16 *)(moby+0x96)=0;
                ChangeHeroAction(0x6F,1);
                *(u8 *)(moby+0x20)=2;
            }
            if (*(int *)(vars+8)!=-1 || !*(char **)(vars+0xC)) break;
            if (*(u8 *)(*(char **)(vars+0xC)+0x20)==0xFE) goto opened;
            if (*(u8 *)(*(char **)(vars+0xC)+0x20)!=0xFD) break;
opened:
            if (gHeroState.state==1) {
                *(u16 *)(moby+0x96)=0;
                *(u8 *)(moby+0x20)=2;
            }
        } else *(u16 *)(moby+0x96)=0;
        break;
    case 2:
        if (*(u16 *)(moby+0x96)<91) {
            ApplyAxisRotationToQuaternion(moby+0xC0,moby+0xC0,moby+0xD0,0.017453294f);
            ApplyAxisRotationToQuaternion(moby+0xE0,moby+0xE0,moby+0xD0,0.017453294f);
            (*(u16 *)(moby+0x96))++;
        } else {
            ChangeHeroAction(0,1);
            *(u8 *)(moby+0x20)=7;
        }
        break;
    case 3:
        if (*(u16 *)(moby+0x96)<91 && *(int *)(vars+4)==0) {
            ApplyAxisRotationToQuaternion(moby+0xC0,moby+0xC0,moby+0xD0,-0.034906588f);
            ApplyAxisRotationToQuaternion(moby+0xE0,moby+0xE0,moby+0xD0,-0.034906588f);
            *(u16 *)(moby+0x96)+=2;
        }
        if (*(u16 *)(moby+0x96)>=91 || *(int *)(vars+4)) {
            *(int *)(vars+4)=1;
            *(u8 *)(moby+0x20)=1;
            *(u16 *)(moby+0x96)=0;
        }
        break;
    case 5:
        ApplyAxisRotationToQuaternion(moby+0xC0,moby+0xC0,moby+0xD0,-0.017453294f);
        ApplyAxisRotationToQuaternion(moby+0xE0,moby+0xE0,moby+0xD0,-0.017453294f);
        if (--*(u16 *)(moby+0x96)==0) {
            *(u16 *)(moby+0x96)=0;
            *(u8 *)(moby+0x20)=1;
        }
        break;
    case 7:
        if (vec_distance_xy(moby+0x10,gHeroPosition)<4.0f) *(short *)(gHeroPosition+0x194)=2;
        else *(short *)(gHeroPosition+0x194)=0;
    case 6:
        if (gHeroState.state!=1) *(u8 *)(moby+0x20)=5;
        break;
    }
}
