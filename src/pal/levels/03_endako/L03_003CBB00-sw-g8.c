#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void func_002A7750(char *,s32,s32);
extern void func_00282CF0(char *,char *,char *);
extern s32 D_001A79F0 MACRO_ADDR;
extern unsigned char D_0019B4A8[];
extern struct { char pad[0x464]; u8 flags[1]; } D_L03_0021EA30;
typedef struct {
    char pad00[0x30]; f32 position[4]; char pad40[0x40];
} Node7E20;
extern Node7E20 *D_L03_001B2B0C MACRO_ADDR;
extern s32 D_L03_001B2548 MACRO_ADDR;
typedef struct {
    char pad[0x26C]; char *object26C; char *object270;
    char pad274[0xC8]; char *object33C;
    char pad340[0x248]; char *object588;
} HeroContacts7E20;
extern HeroContacts7E20 D_00189E20;
extern s32 D_0018C0B4[];
extern char D_L03_001B9980[];
typedef struct {
    char pad[0x160]; f32 f160; char pad164[4]; s32 i168, i16C;
    char pad170[0x10]; f32 f180; char pad184[4]; s32 i188;
} EffectState7E20;
extern EffectState7E20 D_L03_001B9840;
extern f32 func_002A89A8(char *,s32,f32);
extern s32 func_002ACBC8(char *,s32);
extern f32 func_00282DF0(char *);
extern void func_002AAC80(f32 *,f32,f32,f32,f32);
extern void func_00282F20(char *,char *,f32);
extern void func_0029FCC0(s32,s32,void *);
extern void func_00282CC0(char *,char *,char *);
extern void func_002C9218(s32,char *,char *,f32);
extern s32 func_00278E78(void);
extern s32 func_002E5DA0(s32,s32,char *,s32);
extern void func_00282C88(char *);
extern void func_L03_003C8698(char *);
extern s32 func_002B3868(char *);
extern s32 func_00282978(void *);
extern void func_002A8C28(char *,char *,s32,s32,s32,s32,f32,f32,f32);
extern char *func_PAL_0032F3B8(char *,char *,char *,f32);
extern s32 func_00277258(char *,s32,char *,f32);
extern s32 func_L02_002EF388(char *,char *,char *,s32,s32);
extern s32 func_00282948(void *);
extern char *func_002A9640(char *,s32,s32);
typedef struct {
    char pad[0x5C]; s32 flags, effect, index; char pad68[8];
    f32 home[4], velocity[4], displacement[4];
    s32 node, unknownA4; f32 ground, damping; s32 pending, drawFlags;
    s16 delay, respawnDelay; s32 effectTimer;
} Private7E20;
typedef struct {
    char pad00[0x10]; f32 position[4]; u8 state; char pad21[3];
    char *classData; char pad28[0xC]; u16 flags; char pad36[0x32];
    Private7E20 *privateData; char pad6C[0xC]; s32 drawFlags;
    char pad7C[0x1C]; s32 collision; char pad9C[0xC];
    u8 alpha; char padA9; s16 type; char padAC[6]; s16 uid;
    char padB4[0x3C]; f32 rotation[4];
} Actor7E20;

/* Every state, and an out-of-range one, ends at the private block's effect timer, which keeps
   the private pointer live across the whole switch.
   &p->displacement and &p->velocity are written out each time: gcse keeps the first computation
   in a saved register. */
void func_PAL_L03_003CBE60(char *a0)
{
    char buf[0x10] __attribute__((aligned(16)));
    char direction[0x10] __attribute__((aligned(16)));
    char hit[0x10] __attribute__((aligned(16)));
    Actor7E20 *actor=(Actor7E20 *)a0;
    Private7E20 *p = actor->privateData;
    switch (actor->state) {
    case 0: {
        u16 id;
        p->drawFlags=actor->drawFlags;
        p->ground=actor->position[2];
        qcopy((char *)&p->home,(char *)actor->position);
        p->flags|=1;
        if (actor->type==0xB85) {
            id=(u16)actor->uid;
            if (D_L03_0021EA30.flags[(s16)id] ||
                ((D_0019B4A8[((s16)id>>1)+(D_001A79F0<<10)] >> ((id&1)?4:0))&7)) {
                qcopy((char *)actor->position,D_L03_001B2B0C[p->index].position);
            }
        }
        func_002A7750(a0,1,-1);
        break;
    }
    case 1: {
        u16 id;
        if (!(D_L03_001B2548&7)) {
            if (func_002A89A8((char *)actor->position,0,0.5f)+0.05f<=actor->position[2])
                func_002A7750(a0,3,-1);
        }
        if (actor->type==0xCFC) {
            char *v=func_002A9640(a0,0x10001,0);
            if (v) {
                func_002A7750(a0,4,-1);
                if (*(char **)(v+0x20) && *(s16 *)(*(char **)(v+0x20)+0xAA)==0xB85)
                    p->delay=1;
                else p->delay=8;
            }
            if (D_00189E20.object26C==a0 || D_00189E20.object33C==a0 ||
                D_00189E20.object270==a0 || D_00189E20.object588==a0)
                func_002A7750(a0,4,-1);
        } else if (p->pending && D_0018C0B4[0]!=0x31) {
            p->pending=0;
            if (func_002ACBC8((char *)actor->position,p->index)) {
                qcopy((char *)actor->position,D_L03_001B2B0C[p->index].position);
                id=(u16)actor->uid;
                if (id&1) {
                    u8 *b=&D_0019B4A8[((s16)id>>1)+(D_001A79F0<<10)];
                    if (((*b>>4)&7)!=7) *b+=16;
                } else {
                    u8 *b=&D_0019B4A8[((s16)id>>1)+(D_001A79F0<<10)];
                    if ((*b&7)!=7) *b+=1;
                }
            } else func_002C9218(p->effect,(char *)actor->position,(char *)actor->position,2.5f);
        }
        break;
    }
    case 2: {
        f32 length;
        f32 offset=2.3f;
        p->displacement[2]+=offset;
        length=func_00282DF0((char *)&p->displacement);
        if (length!=0.0f) {
            func_002AAC80(&p->damping,length,0.00040000002f,0.00040000002f,0.020000001f);
            length-=p->damping;
            if (length<0.0f) length=0.0f;
            func_00282F20((char *)&p->displacement,(char *)&p->displacement,length);
        }
        p->displacement[2]-=offset;
        func_0029FCC0(p->node,2,buf);
        func_00282CC0((char *)actor->position,buf,(char *)&p->displacement);
        break;
    }
    case 3: {
        p->velocity[2]-=0.012f;
        func_00282CC0((char *)actor->position,(char *)actor->position,(char *)&p->velocity);
        func_002C9218(p->effect,(char *)actor->position,(char *)actor->position,1.25f);
        p->ground=func_002A89A8((char *)actor->position,0,0.5f);
        if (actor->position[2]<=p->ground) {
            if (actor->type==0xCFC) {
                if (func_00278E78()==1) func_002A7750(a0,5,-1);
                else func_002A7750(a0,4,-1);
            } else func_002A7750(a0,1,-1);
            func_002E5DA0(3,0,a0,0x94A);
            p->effectTimer=2;
            func_00282C88((char *)&p->velocity);
            actor->position[2]=p->ground;
            p->pending=1;
        }
        func_L03_003C8698(a0);
        break;
    }
    case 4:
        if (func_002B3868(a0) && !p->delay) p->delay=108;
        if (func_00282978((char *)&p->delay)) func_002A7750(a0,5,-1);
        if (p->delay%50<8) {
            func_002E5DA0(0,0,a0,0xCFC);
            actor->drawFlags=0x800000C0;
        } else actor->drawFlags=p->drawFlags;
        break;
    case 5: {
        char *position=(char *)actor->position;
        qcopy(buf,position);
        *(f32 *)(buf+8)+=1.0f;
        func_002E5DA0(1,0,a0,0xCFC);
        func_00282CF0(direction,D_L03_001B9980,buf);
        func_00282F20(direction,direction,1.0f);
        *(TI128 *)(hit)=0;
        *(f32 *)(hit+8)=1.0f;
        func_00282CC0(hit,hit,position);
        func_002A8C28(a0,hit,0x10001,0,1,0,4.0f,4.0f,1.0f);
        func_PAL_0032F3B8(a0,buf,direction,0.0f);
        actor->collision=0;
        actor->flags=(actor->flags|0x41)&~0x1000;
        func_002A7750(a0,6,-1);
        break;
    }
    case 6:
        if (func_002B3868(a0)) p->respawnDelay=50;
        if (func_00282978((char *)&p->respawnDelay)) {
            qcopy((char *)actor->position,(char *)&p->home);
            qcopy(buf,(char *)actor->position);
            *(f32 *)(buf+8)+=1.3f;
            if (!func_00277258(buf,0,a0,1.2f) &&
                (*(f32 *)(buf+8)+=1.0f,!func_00277258(buf,0,a0,1.2f))) {
                func_002A7750(a0,1,-1);
                actor->drawFlags=p->drawFlags;
                actor->flags=(actor->flags&~0x41)|0x1000;
                actor->collision=*(s32 *)(*(char **)(a0+0x24)+0x10);
                func_L02_002EF388(a0,(char *)&p->home,(char *)actor->rotation,0,0);
                actor->alpha=255;
            } else p->respawnDelay=25;
        }
        break;
    }
    if (func_00282948((char *)&p->effectTimer)==2) {
        D_L03_001B9840.f180=0.1f;
        D_L03_001B9840.i188=50;
        D_L03_001B9840.f160=0.1f;
        D_L03_001B9840.i168=25;
        D_L03_001B9840.i16C=0;
    }
}
