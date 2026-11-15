#include "names.h"
/* func_PAL_L07_003EF670, the PAL copy of func_L07_003EB2C0: the same C, where 0x7C becomes 0.008f
   and the two timers at 0x132 and 0x134 are word values scaled to 50 Hz. */
#include "common.h"
#define INT_AT(p,n) (*(int *)((p)+(n)))
#define U16_AT(p,n) (*(unsigned short *)((p)+(n)))
#define FLOAT_AT(p,n) (*(float *)((p)+(n)))
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern void moby_set_state(void *,int,int);
extern void func_PAL_002A7E68(void *,int,int,int);
extern float coll_get_ground_distance_below(void *,void *,void *);
extern float fast_vec_dist(void *,void *);
extern void moby_update_ground_check(void *);
extern char *part_find_owned_effect_slot(void *,int,int);
extern int CollLine(void *,void *,int,void *,void *);
extern int func_PAL_002B1A50(void *,void *,int);
extern int weapon_select_aim_target(void *,int,float,float,int,int);
extern void moby_mark_spawned(void *);
extern void entity_set_group_alert_c(void *);
extern void func_PAL_L07_003EFEA0(void *);
extern float D_L07_001B0BA8 __attribute__((sda));
extern int D_L07_001B0BB0 __attribute__((sda));
extern int D_L07_001B0BB4[] __attribute__((sda));
extern int D_L07_001C9780 NOT_SDA;
extern char *D_L07_001B1F40[] __attribute__((sda));
extern char D_L07_001B9200[];

/* Initialize the entity, handle nearby collision targets, and update its animation. */
void func_PAL_L07_003EF670(unsigned char *o)
{
    float from[4] __attribute__((aligned(16)));
    float to[4] __attribute__((aligned(16)));
    unsigned char *p=*(unsigned char **)(o+0x68);
    char *hit;
    float turn;
    if (!o[0x20]) {
        p[0x48]=FloatToInt(15.0f);
        p[0x4A]=FloatToInt(9.6f);

        if (math_random_int_below(2)) U16_AT(o,0x34)|=0x8000;
        else U16_AT(o,0x34)&=0x7FFF;
        p[0x150]=6;
        INT_AT(p,0x188)=3;
        FLOAT_AT(p,0x17C)=0.15f;
        FLOAT_AT(p,0x170)=1.0f;
        FLOAT_AT(p,0x174)=1.0f;
        turn=D_L07_001B0BA8;
        turn*=0.017453294f;
        FLOAT_AT(p,0x180)=FLOAT_AT(o,0x18)-3.0f;
        INT_AT(p,0x88)|=0x201;
        FLOAT_AT(p,0x54)=0.3f;
        FLOAT_AT(p,0x50)=1.0f;
        FLOAT_AT(p,0x60)=3.1415927f;
        if (math_random_int_below(2)) turn=-turn;
        FLOAT_AT(p,0x12C)=turn;
        U16_AT(p,0x132)=((s32)(D_L07_001B0BB0)*5+2)/6;
        U16_AT(p,0x134)=((s32)(D_L07_001B0BB4[0])*5+2)/6;
        FLOAT_AT(p,0x7C)=0.008f;
        if (INT_AT(p,0x2B0)!=-1) {
            char *entry=D_L07_001B1F40[0]+INT_AT(p,0x2B0)*0x30;
            if (*(short *)(entry+0x30)) INT_AT(p,0x8C)=**(int **)(entry+0x3C);
            else INT_AT(p,0x8C)=-1;
        }
        qcopy(p+0x2E0,o+0x10);
        if (FLOAT_AT(o,0x18)>FLOAT_AT((char *)&D_L07_001C9780,0x28)) {
            o[0x30]=255;
            INT_AT(p,0x320)=1;
        }
        FLOAT_AT(o,0x18)+=0.5f;
        coll_get_ground_distance_below(o+0x10,o,o+0x10);
        if (INT_AT(p,0x2B0)!=-1) {
            char *entry=D_L07_001B1F40[0]+INT_AT(p,0x2B0)*0x30;
            if (*(short *)(entry+0x30)) INT_AT(p,0x8C)=**(int **)(entry+0x3C);
            else INT_AT(p,0x8C)=-1;
        }
        if (!INT_AT(p,0x2BC)) {
            INT_AT(o,0x98)=0;
            U16_AT(o,0x34)=(U16_AT(o,0x34)|0x41)&0xEFFF;
            moby_set_state(o,11,4);
            if (o[0x43]) func_PAL_002A7E68(o,0,0,0);
        } else if (INT_AT(p,0x2B8)==-1) {
            moby_set_state(o,1,0);
            if (o[0x43]!=2) func_PAL_002A7E68(o,2,0,0);
        } else {
            moby_set_state(o,7,4);
            if (o[0x43]) func_PAL_002A7E68(o,0,0,0);
        }
    }
    if (o[0x31] && fast_vec_dist(o+0x10,D_L07_001B9200)<24.0f) {
        moby_update_ground_check(o);
        o[0x6F]=22;
    }
    hit=part_find_owned_effect_slot(o,0x10000,0);
    if (hit && *(char **)(hit+0x20)) {
        if (*(short *)(*(char **)(hit+0x20)+0xAA)==0xB7F) o[0xA8]=255;
        else if (fast_vec_dist(*(char **)(hit+0x20)+0x10,o+0x10)<32.0f) {
            qcopy(from,*(char **)(hit+0x20)+0x10);
            from[2]+=0.5f;
            qcopy(to,o+0x10);
            to[2]+=0.5f;
            if (CollLine(from,to,2,o,0)) o[0xA8]=255;
        }
    }
    if (func_PAL_002B1A50(o,p+0x140,0)) {
        entity_set_group_alert_c(o);
        if (FLOAT_AT(p,0x20)<=0) {
            func_PAL_L07_003EFEA0(o);
            moby_mark_spawned(o);
            return;
        }
    }
    INT_AT(p,0x2DC)=weapon_select_aim_target(o,INT_AT(p,0x2B0),FLOAT_AT(p,0x2B4),0,0,0);
}
