/* func_US2_L17_004203E8, the USA v2.00 copy of func_L17_0041ED58: the same C, where rename func_002B0A18 becomes func_US2_002B1880; rename func_00288E18 becomes func_US2_00289840. */
#include "common.h"

extern s32 D_L17_001B2C1C __attribute__((sda));

/* func_L17_003C7C70 is defined in L17_003C7C70-tilt-g8.c. */

/* A 16-byte vector: the engine's helpers take and return these, and the copies between
   them are quadword moves. */
/* Turns the vector at a1 into the object's frame, then into the world with the matrix at
   a0 + 0xC0, and reports whether both of the first two coordinates stay below the two
   bounds. */
typedef struct {
    u8 pad00[0x80];
    f32 x;
    f32 y;
    f32 z;
    u8 pad8C[0x340 - 0x8C];
    s32 w340;
} L17Player;

extern L17Player D_00189E20;
extern f32 D_L17_001B04BC SDATA(D_L17_001B04BC);
/* `sda` on an array of unknown size: cc1 emits the one-instruction load, which the assembler
   expands absolute (`lui $r` / `lw $r,%lo($r)`), as retail has it in this -G0 unit; the limit
   word is loaded in a branch delay slot, so there it becomes the `$gp` form. The pool base is
   the word D_L17_001B2C1C declared above as an int, reached here as a pointer under a second
   name. */
extern u8 *D_L17_001B2C1C_base[] __asm__("D_L17_001B2C1C") __attribute__((sda));
/* The object's state record up to the group word and the word stored beside it. */
/* Walks the id list of the state's group and sets the state's mode word to 0x57 for every id
   that has an entity, stopping at the first that has none. */
/* Claims the shared slot at state+0x720 for this object (index into the object array):
   taken when free or when its holder is in state 0xFE/0xFD, then in mode 1 handed to the
   nearest candidate; returns 1 once this object holds it in mode 2. func_L17_003E6F20
   releases it. */
/* func_L17_00417DB0 is in L17_003C7C70-f7-g8.c. */

/* func_L17_0041E208 is defined in L17_0041E208-g8.c. */

/* func_L17_0041EAA8 is defined in L17_003C7C70-g8.c. */

typedef struct { unsigned char pad[0x464]; unsigned char flags[0]; } PickupFlags;
extern PickupFlags D_L17_0021EBB0;
extern unsigned char D_0019B4A8[], D_0013963C, D_001395B8[];
extern int D_001A79F0 SDATA(D_001A79F0);
typedef struct { unsigned char pad[0x20]; unsigned char state; unsigned char rest[0xDF]; } Entity;
extern Entity *entity_base_ptr __asm__("D_L17_001B2C1C") __attribute__((sda));
extern Entity *entity_base_gp SDATA(D_L17_001B2C1C);
extern char D_00189EA0[];
extern float func_00283B98(float,float), func_002A7878(float,float), func_002A7940(void), func_002A78D8(float,float);
extern int func_002A77E0(int);
extern void func_002AF000(void *,float,float,float);
extern void *func_002C2210(void *,int,unsigned,int,int,void *,float,float,float,int);
extern float func_00282E80(void *,void *);
extern void func_L00_003294F0(void *,int),func_002A7750(void *,int,int),func_0029F338(void *),func_US2_002B1880(int,int);
extern int func_US2_00289840(int,int);
/* Spins and sparkles an uncollected pickup; when the player comes within 1.5 units it bumps the
   pickup's saved count and triggers its linked entity, and when inactive it removes itself once
   that entity dies. */
void func_US2_L17_004203E8(unsigned char *o)
{
    int *s=*(int **)(o+0x68);
    unsigned short id;
    unsigned char *position;
    int n,sign,count;
    int bits;
    float size,ang,speed,scale;
    float vel[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    if(o[0x20]!=0) goto inactive;
    id=*(unsigned short *)(o+0xb2);
    if(D_L17_0021EBB0.flags[(short)id]!=0) goto remove_self;
    {
        bits=D_0019B4A8[((short)id>>1)+(D_001A79F0<<10)];
        if(id&1) bits=(bits>>4)&7; else bits=bits&7;
        if(bits) goto remove_self;
        position=o+0x10;
        {
            *(float *)(o+0xf8)=func_00283B98(*(float *)(o+0xf8),0.087266474f);
            n=1;
            do {
                size=func_002A7878(2.0f,5.0f);
                sign=func_002A77E0(2); if(sign==0)--sign;
                ang=func_002A7940();
                speed=func_002A7878(0.3490659f,1.5358899f);
                scale=func_002A7878(0.05f,0.1f);
                func_002AF000(vel,scale,ang,speed);
                qcopy(pos,position);
                pos[0]+=func_002A78D8(0.0f,0.15f);
                pos[1]+=func_002A78D8(0.0f,0.15f);
                pos[2]+=func_002A78D8(0.0f,0.15f);
                func_002C2210(pos,3,0x208020ff,0,sign,vel,size*0.1f,size,0.006f,0);
                func_002C2210(pos,3,0x20ffffff,1,-sign,vel,size*0.03f,size*0.3f,0.006f,0);
            } while(--n>=0);
            if(func_00282E80(position,D_00189EA0)<1.5f) {
                unsigned short pickupId;
                unsigned char *counter;
                D_0013963C=1;
                pickupId=*(unsigned short *)(o+0xb2);
                if(pickupId&1) {
                    counter=(((short)pickupId>>1)+(D_001A79F0<<10))+D_0019B4A8;
                    if(((*counter>>4)&7)!=7)*counter+=16;
                } else {
                    counter=(((short)pickupId>>1)+(D_001A79F0<<10))+D_0019B4A8;
                    if((*counter&7)!=7)++*counter;
                }
                if(*(int *)s!=-1) {
                    ((unsigned short *)o)[0x1a]|=1;
                    o[0x31]=0;
                    func_L00_003294F0(&entity_base_ptr[*s],1);
                    func_002A7750(o,1,-1);
                } else goto remove_self;
            }
            return;
        }
    }
remove_self:
    func_0029F338(o);
    return;
inactive:
    if(*(int *)s!=-1) {
        int state;
        state=entity_base_gp[*s].state;
        if(state==0xfe)goto dead;
        if(state!=0xfd)goto done;
    }
dead:
    {
        func_US2_002B1880(0x1292,0x78);
        count=D_001395B8[0x86]?1:2;
        if(D_001395B8[0x89])--count;
        if(count>0)func_US2_00289840(0xa0f,0x66);else func_US2_00289840(0xa10,0x67);
        func_0029F338(o);
    }
done:;
}

/* func_L17_0041F180 is defined in L17_collision.c. */

/* func_L17_0041F478 is defined in L17_003C7C70-link.c. */

/* func_L17_00420758 is defined in L17_collision.c. */

/* func_L17_00420A50 is defined in L17_00420A50-g8.c. */

/* func_L17_00420E08 is defined in L17_003C7C70-g8.c. */
