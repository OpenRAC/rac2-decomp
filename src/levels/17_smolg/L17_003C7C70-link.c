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
void func_L17_0041F478(unsigned char *o)
{
    unsigned char *s=*(unsigned char **)(o+0x68),*target;
    Link *row=(Link *)(s+0x18),*r;
    int active,id,bits,half;
    float f;
    if(*(int *)(s+0x54)!=-1) {
        unsigned char *e=(unsigned char *)entity_base_abs[0]+(*(int *)(s+0x10)<<8);
        e[0x20]=2;
        if(!func_002B38B8(o)) {
            unsigned short flags=*(unsigned short *)(o+0x34);
            *(int *)(o+0x98)=0;
            o[0x31]=0;
            *(unsigned short *)(o+0x34)=flags|0x41;
            return;
        }
        *(int *)(s+0x54)=-1;
        func_L00_003294F0(o,0);
        e[0x20]=1;
    }
    active=0;
    target=0;
    if(*(int *)(s+0x10)!=-1)target=(unsigned char *)entity_base_abs[0]+(*(int *)(s+0x10)<<8);
    if((o[0xb0]==0xff || !(D_0019B2E8[o[0xb0]+(D_001A79F0<<4)]&0x80)) && o[0x20]!=0) {
        int i;
        r=row;
        for(i=0;i<5;++i,++r) {
            if(r->index==-1)goto next_row;
            {
                unsigned char *e=(unsigned char *)entity_base_gp+(r->index<<8);
                if(func_002B38B8(o))goto next_row;
                if(!e || *(short *)(e+0xaa)!=r->uid || e[0x20]==0xfe || e[0x20]==0xfd)goto clear_active;
                id=*(unsigned short *)(e+0xb2);
                half=(short)id;
                bits=D_0019B4A8[(half>>1)+(D_001A79F0<<10)];
                if(id&1)bits=(bits>>4)&7;else bits&=7;
                if(bits)goto clear_active;
                ++active;
                if(r->state==-1)goto next_row;
                if(e[0x20]!=r->state)goto next_row;
            }
clear_active:
            active=0;
next_row:;
        }
    }
    switch(o[0x20]) {
    case 0:
        if(target) {
            *(unsigned short *)(s+0x14)=*(unsigned short *)(target+0xaa);
            *(float *)(s+0x44)=func_00283CE0(target[0x23]);
            if(*(int *)(s+8)&0x10)qcopy(o+0x10,target+0x10);
            else if(*(int *)(s+8)&0x40)qcopy(target+0x10,o+0x10);
            if(*(int *)(s+8)&0x20)qcopy(o+0xf0,target+0xf0);
            else if(*(int *)(s+8)&0x80)qcopy(target+0xf0,o+0xf0);
        } else func_0026FEB8(D_L17_001B1FB8);
        { int i; unsigned char *diag;
        for(diag=(unsigned char *)row,i=0;i<5;++i,diag+=8) {
            if(*(int *)diag!=-1) {
                char *base=entity_base_abs[0];
                unsigned int offset=*(int *)diag<<8;
                unsigned char *e=(unsigned char *)(offset+(unsigned int)base);
                *(unsigned short *)(diag+4)=*(unsigned short *)(e+0xaa);
                func_0026FEB8(D_L17_001B1FE8,((char *)o-base)>>8,i,*(int *)diag,*(short *)(diag+4));
            } else func_0026FEB8(D_L17_001B2018,((char *)o-entity_base_abs[0])>>8,i);
        }
        }
        { float factor=*(float *)(*(char **)(o+0x24)+0x24);
        float width=*(float *)s,height=*(float *)(s+4);
        o[0x20]=1;
        *(float *)(o+0x2c)=(height>width?height:width)*factor; }
        break;
    case 1:
        if(!active) {
            if(target && *(signed char *)(s+0x16)!=-1)target[0x20]=s[0x16];
            *(int *)(s+0x40)=*(int *)(s+0xc);
            o[0x20]=2;
        }
        func_L17_0041F180(o,s);
        break;
    case 2:
        if(target && !(*(int *)(s+8)&2)) {
            f=func_00283CE0(*(int *)(s+0x40));
            f=*(float *)(s+0x44)*f/func_00283CE0(*(int *)(s+0xc));
            target[0x23]=func_00283CF0(f);
        }
        if(!(*(int *)(s+8)&4) && target && *(signed char *)(s+0x17)!=-1 && target[0x20]==*(signed char *)(s+0x17))o[0x20]=3;
        if(!(*(int *)(s+8)&8) && func_00282948(s+0x40))o[0x20]=3;
        func_L17_0041F180(o,s);
        break;
    case 3:
        if(target && !(*(int *)(s+8)&1))func_0029F338(target);
        func_0029F338(o);
        break;
    case 4:
        break;
    }
}
