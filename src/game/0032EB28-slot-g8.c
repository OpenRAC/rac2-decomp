#include "common.h"

/* func_00334160: retail keeps the owned-flag mask 2 in a register from the first block and
   reuses it for the weapon type==2 test; the type tests are one || whose true arm jumps to a
   shared return, and D_001A7A80 is reached by an unsplit lui/addiu pair. */
typedef int Quad341 __attribute__((mode(TI)));
typedef struct {
    float vector[4];
    char pad10[8];
    unsigned char type;
    unsigned char source;
    short oclass;
    char pad1C[4];
    int flag;
    char pad24[0xC];
} Hit334160;
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
typedef struct { int active; unsigned char type; char pad[0x47]; short map; char pad2[0x92]; } Weapon1271;
typedef struct { float cost,a; int frames; float b; } Effect1271;
typedef struct { int timer,color,alpha; float zero,a,b; char *object; int state,owner,active; char pad[8]; } Slot1271;
extern Weapon1271 g_weapon_table[];
extern unsigned char D_001A7A80[] MACRO_ADDR;
extern unsigned char g_item_slot_to_record[];
extern Effect1271 D_00237DA0[2][119];
extern Slot1271 g_health_drain_slots[30];
typedef struct { char pad[0xb8]; int owner; } Attacker341;
extern Attacker341 *D_001B1000 __attribute__((sda));
extern float *moby_get_private_value_0(void *);
extern int moby_find_entry_index_by_id(int);
extern void get_moby_color(void *,int *,int *,int *);
extern void FastVecScale(void *,void *,float),vec_scale_to_length(void *,void *,float);
extern void make_hit_descriptor(void *,void *,int,void *,float),QueueMobyImpact(void *,void *);
/* Tells if a weapon number is one of the special ones. */
static __inline__ int IsSpecial1271(int id)
{
    int special=0;
    switch(id) {
    case 12:case 14:case 17:case 18:case 53:special=1;break;
    }
    return special;
}
/* Tells if a weapon can cause the first kind of drain effect. */
static __inline__ int IsEffect1271(int id)
{
    Weapon1271 *weapon=&g_weapon_table[g_item_slot_to_record[id]];
    if(weapon->active) {
        int type=weapon->type;
        if(type==2 || (type==1 && IsSpecial1271(id))) return 1;
    }
    return 0;
}
/* Tells if a weapon can cause the second kind of drain effect. */
static __inline__ int IsEffect3_1271(int id)
{
    Weapon1271 *weapon=&g_weapon_table[g_item_slot_to_record[id]];
    int active=0;
    if(weapon->active) active=weapon->type==3;
    return active;
}
/* Starts a slow health drain on a target hit by a weapon. If the target runs out of health, it deals the final hit to it. */
int weapon_start_health_drain(char *object,int id,int owner)
{
    float backwards[4] __attribute__((aligned(16)));
    Hit334160 damage __attribute__((aligned(16)));
    int r,g,b;
    int mapped=g_weapon_table[id].map;
    int mode,result=1,i;
    int mask=2;
    if(!mapped) mapped=id;
    if(!(D_001A7A80[mapped]&mask)) return 1;
    mode=IsEffect1271(mapped) || IsEffect3_1271(mapped);
    {
        if(H(P(object,0x24),0x46)!=5) return 1;
        if(!(*(unsigned short *)(object+0x34)&0x1000)) return 1;
        if(*(signed char *)(object+0x20)<0) return 1;
        if(!I(object,0x98)) return 1;
        {
            float *health=moby_get_private_value_0(object);
            if(!health || *health<=0.0f) return 1;
        }
        if(moby_find_entry_index_by_id((int)object)!=-1) return 1;
        {
            for(i=0;i<30;i++) {
                if(!g_health_drain_slots[i].object) {
                    Slot1271 *slot=&g_health_drain_slots[i];
                    float *health;
                    slot->timer=D_00237DA0[mode][id].frames*60;
                    slot->a=D_00237DA0[mode][id].a; slot->b=D_00237DA0[mode][id].b;
                    slot->object=object;slot->owner=owner;slot->state=0;
                    health=moby_get_private_value_0(object);
                    *health-=D_00237DA0[mode][id].cost;
                    {
                    int colored=0;
                    if(*(unsigned short *)(slot->object+0x34)&0x20) {
                        char *p=P(P(slot->object,0x68),0x10);
                        if(p && H(p,0)) {r=B(p,4);g=B(p,5);b=B(p,6);colored=1;}
                    }
                    if(!colored) get_moby_color(slot->object,&r,&g,&b);
                    }
                    slot->color=(b<<16)+(g<<8)+r;
                    slot->alpha=0xff0000;slot->zero=0.0f;slot->active=1;
                    result=0;
                    if(*health<=slot->zero && D_001B1000) {
                        FastVecScale(backwards,slot->object+0xc0,-1.0f);
                        vec_scale_to_length(damage.vector,damage.vector,0.0016666668234393f);
                        D_001B1000->owner=slot->owner;
                        make_hit_descriptor(damage.vector,D_001B1000,0x810000,backwards,0.001f);
                        *(Quad341 *)damage.vector=*(Quad341 *)backwards;
                        damage.vector[3]=5627.9248046875f;
                        damage.flag=1;
                        damage.type=5;
                        damage.source=1;
                        damage.oclass=*(unsigned short *)(slot->object+0xaa);
                        QueueMobyImpact(slot->object,&damage);
                        slot->object=0;
                    }
                    break;
                }
            }
        }
    }
    return result;
}
