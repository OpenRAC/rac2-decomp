#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits;float f[4]; } Vector4;
#define FIELD(type,p,off) (*(type *)((char *)(p)+(off)))
extern u8 *CreateMoby(s32);
extern void moby_init_child_from_parent(void *,void *),moby_set_state(u8 *,s32,s32);
/* Creates a small copy of the owner's object type that flies off with the given velocity. */
void door_spawn_debris_piece(u8 *owner,void *unused,Vector4 *velocity,s32 index)
{
    u8 *object=CreateMoby(FIELD(s16,owner,0xAA));
    char *work;
    if(!object)return;
    moby_init_child_from_parent(object,owner);
    object[0x31]=0;FIELD(u16,object,0x34)|=1;
    FIELD(u32,object,0x98)=FIELD(u32,FIELD(char *,object,0x24),0x10);
    work=FIELD(char *,object,0x68);FIELD(Quadword,work,0)=velocity->bits;FIELD(s32,work,0x10)=index;
    moby_set_state(object,5,-1);
}
