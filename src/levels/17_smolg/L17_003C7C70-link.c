#include "common.h"

/* func_L17_0041F478 has a unit of its own: retail's max.s needs -ffast-math, and its jump table
   is this unit's only .rodata. */

/* A linked-entity row: entity index, the UID it had when linked, and an optional state that
   breaks the link. */
typedef struct { int index; short uid; signed char state; unsigned char pad; } Link;
extern char *entity_base_abs[] __asm__("D_L17_001B2C1C") __attribute__((sda));
extern int D_001A79F0 SDATA(D_001A79F0);
extern char *entity_base_gp SDATA(D_L17_001B2C1C);
extern unsigned char D_0019B2E8[],D_0019B4A8[];
extern char D_L17_001B1FB8[],D_L17_001B1FE8[],D_L17_001B2018[];
extern int func_002B38B8(void *),func_00282948(void *),func_00283CF0(float);
extern void func_L00_003294F0(void *,int),func_0029F338(void *),func_L17_0041F180(void *,void *);
extern float func_00283CE0(int);
extern void func_0026FEB8(char *,...);
/* Tracks up to five linked entities, syncs the target's position/rotation, and steps the
   target's timed state. */
void func_L17_0041F478(unsigned char *moby)
{
    unsigned char *vars=*(unsigned char **)(moby+0x68),*target;
    Link *row=(Link *)(vars+0x18),*link;
    int active,id,bits,half;
    float factor;
    if(*(int *)(vars+0x54)!=-1) {
        unsigned char *linked=(unsigned char *)entity_base_abs[0]+(*(int *)(vars+0x10)<<8);
        linked[0x20]=2;
        if(!IsThirdPendingFlagSet(moby)) {
            unsigned short flags=*(unsigned short *)(moby+0x34);
            *(int *)(moby+0x98)=0;
            moby[0x31]=0;
            *(unsigned short *)(moby+0x34)=flags|0x41;
            return;
        }
        *(int *)(vars+0x54)=-1;
        SetObjectFlagBit(moby,0);
        linked[0x20]=1;
    }
    active=0;
    target=0;
    if(*(int *)(vars+0x10)!=-1)target=(unsigned char *)entity_base_abs[0]+(*(int *)(vars+0x10)<<8);
    if((moby[0xb0]==0xff || !(D_0019B2E8[moby[0xb0]+(gCurrentMapIndex<<4)]&0x80)) && moby[0x20]!=0) {
        int i;
        link=row;
        for(i=0;i<5;++i,++link) {
            if(link->index==-1)goto next_row;
            {
                unsigned char *linked=(unsigned char *)entity_base_gp+(link->index<<8);
                if(IsThirdPendingFlagSet(moby))goto next_row;
                if(!linked || *(short *)(linked+0xaa)!=link->uid || linked[0x20]==0xfe || linked[0x20]==0xfd)goto clear_active;
                id=*(unsigned short *)(linked+0xb2);
                half=(short)id;
                bits=D_0019B4A8[(half>>1)+(gCurrentMapIndex<<10)];
                if(id&1)bits=(bits>>4)&7;else bits&=7;
                if(bits)goto clear_active;
                ++active;
                if(link->state==-1)goto next_row;
                if(linked[0x20]!=link->state)goto next_row;
            }
clear_active:
            active=0;
next_row:;
        }
    }
    switch(moby[0x20]) {
    case 0:
        if(target) {
            *(unsigned short *)(vars+0x14)=*(unsigned short *)(target+0xaa);
            *(float *)(vars+0x44)=IntToFloat(target[0x23]);
            if(*(int *)(vars+8)&0x10)qcopy(moby+0x10,target+0x10);
            else if(*(int *)(vars+8)&0x40)qcopy(target+0x10,moby+0x10);
            if(*(int *)(vars+8)&0x20)qcopy(moby+0xf0,target+0xf0);
            else if(*(int *)(vars+8)&0x80)qcopy(target+0xf0,moby+0xf0);
        } else STUB_printf(D_L17_001B1FB8);
        { int i; unsigned char *diag;
        for(diag=(unsigned char *)row,i=0;i<5;++i,diag+=8) {
            if(*(int *)diag!=-1) {
                char *base=entity_base_abs[0];
                unsigned int offset=*(int *)diag<<8;
                unsigned char *linked=(unsigned char *)(offset+(unsigned int)base);
                *(unsigned short *)(diag+4)=*(unsigned short *)(linked+0xaa);
                STUB_printf(D_L17_001B1FE8,((char *)moby-base)>>8,i,*(int *)diag,*(short *)(diag+4));
            } else STUB_printf(D_L17_001B2018,((char *)moby-entity_base_abs[0])>>8,i);
        }
        }
        { float factor=*(float *)(*(char **)(moby+0x24)+0x24);
        float width=*(float *)vars,height=*(float *)(vars+4);
        moby[0x20]=1;
        *(float *)(moby+0x2c)=(height>width?height:width)*factor; }
        break;
    case 1:
        if(!active) {
            if(target && *(signed char *)(vars+0x16)!=-1)target[0x20]=vars[0x16];
            *(int *)(vars+0x40)=*(int *)(vars+0xc);
            moby[0x20]=2;
        }
        HitMobysInsideBox(moby,vars);
        break;
    case 2:
        if(target && !(*(int *)(vars+8)&2)) {
            factor=IntToFloat(*(int *)(vars+0x40));
            factor=*(float *)(vars+0x44)*factor/IntToFloat(*(int *)(vars+0xc));
            target[0x23]=FloatToInt(factor);
        }
        if(!(*(int *)(vars+8)&4) && target && *(signed char *)(vars+0x17)!=-1 && target[0x20]==*(signed char *)(vars+0x17))moby[0x20]=3;
        if(!(*(int *)(vars+8)&8) && FastFloatHelperD(vars+0x40))moby[0x20]=3;
        HitMobysInsideBox(moby,vars);
        break;
    case 3:
        if(target && !(*(int *)(vars+8)&1))MarkMobySpawned(target);
        MarkMobySpawned(moby);
        break;
    case 4:
        break;
    }
}
