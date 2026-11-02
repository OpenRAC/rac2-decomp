/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* GPT-6.1 Sol high tier, USA v1.01, -O2 -G8 -ffunction-sections.
 * Best: 1008/1008 bytes, 0/28 places; first difference +0x38.
 * The saved-register allocation now agrees with retail. Move the color flag's
 * initialization AFTER the health call so it does not cross that call; test
 * D_00237800[i].object before constructing the success-path slot pointer; set
 * result=0 before the death check. These changes recover size and allocation.
 * Corrects the earlier draft's flag semantics: beqz at 0x3341C4 branches to
 * 0x3342B0, an unconditional return-1 path. A clear bit gates the whole body.
 * Typed attacker.owner at +0xB8 avoids an extra global pointer reload, and a
 * native TImode stack transfer recovers the retail sq at sp+0x10.
 * Remaining: predicate startup scheduling/type-2 comparison, two effect-table
 * address registers, and the final damage-field stores/argument scheduling.
 * A type switch, explicit boolean predicates, -g, a typed damage record, and
 * moving the b-field store earlier did not close these differences. The last
 * two changes are not retained. Next useful experiment: the first predicate's
 * allocation and block shape; avoid redoing color-flag lifetime variants.
 * All required declarations are below. No unmatched C belongs in src/.
 */
#include "common.h"
typedef int Quad341 __attribute__((mode(TI)));
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
typedef struct { int active; unsigned char type; char pad[0x47]; short map; char pad2[0x92]; } Weapon1271;
typedef struct { float cost,a; int frames; float b; } Effect1271;
typedef struct { int timer,color,alpha; float zero,a,b; char *object; int state,owner,active; char pad[8]; } Slot1271;
extern Weapon1271 D_00239BA0[];
extern unsigned char D_001A7A80[],D_00139568[];
extern Effect1271 D_00237DA0[2][119];
extern Slot1271 D_00237800[30];
typedef struct { char pad[0xb8]; int owner; } Attacker341;
extern Attacker341 *D_001B1000 __attribute__((sda));
extern float *func_002AB1F0(void *);
extern int func_00334100(int);
extern void func_002A04B8(void *,int *,int *,int *);
extern void func_00282D30(void *,void *,float),func_00282F20(void *,void *,float);
extern void func_002A8C00(void *,void *,int,void *,float),func_002A8E20(void *,void *);
static __inline__ int IsEffect1271(int id)
{
    Weapon1271 *weapon=&D_00239BA0[D_00139568[id]];
    if(weapon->active) {
        int type=weapon->type;
        if(type==2) return 1;
        if(type==1) {
            int special=0;
            switch(id) {
            case 12:case 14:case 17:case 18:case 53:special=1;break;
            }
            if(special) return 1;
        }
    }
    return 0;
}
static __inline__ int IsEffect3_1271(int id)
{
    Weapon1271 *weapon=&D_00239BA0[D_00139568[id]];
    int active=0;
    if(weapon->active) active=weapon->type==3;
    return active;
}
int func_00334160(char *object,int id,int owner)
{
    float backwards[4] __attribute__((aligned(16)));
    unsigned char damage[0x30] __attribute__((aligned(16)));
    int r,g,b;
    int mapped=D_00239BA0[id].map;
    int mode,result=1,i;
    if(!mapped) mapped=id;
    if(!(D_001A7A80[mapped]&2)) return 1;
    mode=IsEffect1271(mapped) || IsEffect3_1271(mapped);
    {
        if(H(P(object,0x24),0x46)!=5) return 1;
        if(!(*(unsigned short *)(object+0x34)&0x1000)) return 1;
        if(*(signed char *)(object+0x20)<0) return 1;
        if(!I(object,0x98)) return 1;
        {
            float *health=func_002AB1F0(object);
            if(!health || *health<=0.0f) return 1;
        }
        if(func_00334100((int)object)!=-1) return 1;
        {
            
            for(i=0;i<30;i++) {
                if(!D_00237800[i].object) {
                    Slot1271 *slot=&D_00237800[i];
                    float *health;
                    slot->timer=D_00237DA0[mode][id].frames*60;
                    slot->a=D_00237DA0[mode][id].a; slot->b=D_00237DA0[mode][id].b;
                    slot->object=object;slot->owner=owner;slot->state=0;
                    health=func_002AB1F0(object);
                    *health-=D_00237DA0[mode][id].cost;
                    {
                    int colored=0;
                    if(*(unsigned short *)(slot->object+0x34)&0x20) {
                        char *p=P(P(slot->object,0x68),0x10);
                        if(p && H(p,0)) {r=B(p,4);g=B(p,5);b=B(p,6);colored=1;}
                    }
                    if(!colored) func_002A04B8(slot->object,&r,&g,&b);
                    }
                    slot->color=(b<<16)+(g<<8)+r;
                    slot->alpha=0xff0000;slot->zero=0.0f;slot->active=1;
                    result=0;
                    if(*health<=slot->zero && D_001B1000) {
                        func_00282D30(backwards,slot->object+0xc0,-1.0f);
                        func_00282F20(damage,damage,0.0016666668234393f);
                        D_001B1000->owner=slot->owner;
                        func_002A8C00(damage,D_001B1000,0x810000,backwards,0.001f);
                        *(Quad341 *)damage=*(Quad341 *)backwards;
                        F(damage,0xc)=5627.9248046875f;
                        B(damage,0x19)=1;B(damage,0x18)=5;
                        H(damage,0x1a)=*(unsigned short *)(slot->object+0xaa);
                        I(damage,0x20)=1;
                        func_002A8E20(slot->object,damage);
                        slot->object=0;
                    }
                    break;
                }
            }
        }
    }
    return result;
}
