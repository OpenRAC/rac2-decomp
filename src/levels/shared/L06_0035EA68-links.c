#include "common.h"
extern int math_fast_float_d(int *);
extern void moby_mark_spawned(void *);
extern void vec_scale_to_length(void *,void *,float);
extern char *D_L06_001B281C[] __attribute__((sda));
extern int g_current_map_index[] __attribute__((sda));
extern int D_001A79F0_gp SDATA(D_001A79F0);
extern unsigned char D_0019B2E8[], D_0019B4A8[];
extern char D_L06_001AF320[],D_L06_001AF350[],D_L06_001AF380[];
extern void STUB_printf(char *,...);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void moby_hit_inside_rectangle(void *,void *);
#define F14(p,o) (*(float *)((char *)(p)+(o)))
#define I14(p,o) (*(int *)((char *)(p)+(o)))
/* Updates moby class 794. It watches up to five linked mobies, and when all are in the right state it changes its target, counts down, then removes itself and the target. */
void link_watcher_update(unsigned char *moby) {
    int count=0,i;
    char *target=0;
    char *vars=*(char **)(moby+0x68);
    char *links=vars+0x18;
    char *link;
    if(I14(vars,0x10)!=-1) target=D_L06_001B281C[0]+I14(vars,0x10)*256;
    if((unsigned char)moby[0xb0]!=255 && (D_0019B2E8[(unsigned char)moby[0xb0]+D_001A79F0_gp*16]&128)) goto dispatch;
    if(!(unsigned char)moby[0x20]) goto dispatch;
    { int j; char *scan;
    for(j=0;j<5;j++){ scan=links+j*8;
        if(I14(scan,0)!=-1) {
            char *other=D_L06_001B281C[0]+I14(scan,0)*256;
            if(other && *(short *)(other+0xaa)==*(short *)(scan+4) && (unsigned char)other[0x20]!=254 && (unsigned char)other[0x20]!=253) {
                unsigned short bits=*(unsigned short *)(other+0xb2);
                int n=D_0019B4A8[((short)bits>>1)+g_current_map_index[0]*1024];
                if (bits & 1) { if ((n >> 4) & 7) continue; }
                else if (n & 7) continue;
                if(((signed char)scan[6]==-1 || (unsigned char)other[0x20]!=(signed char)scan[6])) count++;
            }
        }
    }
 }
 dispatch:
    switch((unsigned char)moby[0x20]) {
    case 0:
        if(target) {
            *(unsigned short *)(vars+0x14)=*(unsigned short *)(target+0xaa);
            F14(vars,0x44)=IntToFloat((unsigned char)target[0x23]);
            if(I14(vars,8)&0x10) qcopy(moby+0x10,target+0x10);
            else if(I14(vars,8)&0x40) qcopy(target+0x10,moby+0x10);
            if(I14(vars,8)&0x20) qcopy(moby+0xf0,target+0xf0);
            else if(I14(vars,8)&0x80) qcopy(target+0xf0,moby+0xf0);
        } else STUB_printf(D_L06_001AF320);
        for(i=0,link=links;i<5;i++,link+=8) {
            if(I14(link,0)!=-1){
                char *base = D_L06_001B281C[0];
                char *other=(char *)(I14(link,0)*256+(s32)base);
                unsigned short uid=*(unsigned short *)(other+0xaa);
                *(unsigned short *)(link+4)=uid;
                STUB_printf(D_L06_001AF350,((char *)moby-base)>>8,i,I14(link,0),(short)uid);
            } else STUB_printf(D_L06_001AF380,((char *)moby-D_L06_001B281C[0])>>8,i);
        }
        {
            float sizeA=F14(vars,0),sizeB=F14(vars,4);
            F14(moby,0x2c)=(sizeB>sizeA?sizeB:sizeA)*F14(*(char **)(moby+0x24),0x24);
        }
        moby[0x20]=1;
        *(unsigned short *)(moby+0x34)|=0x100;
        break;
    case 1:
        if(!count){
            if(target && (signed char)vars[0x16]!=-1) target[0x20]=vars[0x16];
            I14(vars,0x40)=I14(vars,0xc);
            moby[0x20]=2;
        }
        moby_hit_inside_rectangle(moby,vars);
        break;
    case 2:
        if(target && !(I14(vars,8)&2)) {
            float remaining=IntToFloat(I14(vars,0x40));
            float total=IntToFloat(I14(vars,0xc));
            target[0x23]=FloatToInt(F14(vars,0x44)*remaining/total);
        }
        if(!(I14(vars,8)&4) && target && (signed char)vars[0x17]!=-1 && (unsigned char)target[0x20]==(signed char)vars[0x17]) moby[0x20]=3;
        if(!(I14(vars,8)&8) && math_fast_float_d((int *)(vars+0x40))) moby[0x20]=3;
        moby_hit_inside_rectangle(moby,vars);
        break;
    case 3:
        if(target && !(I14(vars,8)&1)) moby_mark_spawned(target);
        moby_mark_spawned(moby);
        return;
    case 4:
        break;
    }
    if(g_current_map_index[0]==13) vec_scale_to_length(moby+0xc0,moby+0xc0,0.5f);
}
