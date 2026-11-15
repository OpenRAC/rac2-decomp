#include "include_asm.h"
#include "names.h"

typedef unsigned int Quad __attribute__((mode(TI)));
extern char g_item_slot_to_record[];
extern char g_weapon_l00_table[];
extern char g_area_hit_targets[];
extern float IntToFloat(int);
extern float math_lerp_float(float,float,float);
extern int coll_process_hit(float, void *, int, void *, int);
extern void moby_queue_knockback_for_nodes(void *,void *,void *,int,int,int,int,int,float,float,float);
extern void moby_mark_spawned(void *);

void func_PAL_L00_003920F8(unsigned char *object)
{
    Quad local;
    unsigned char *globals=(unsigned char *)g_item_slot_to_record;
    unsigned char *table=(unsigned char *)g_weapon_l00_table;
    float limit, amount;
    int effect;
    *(unsigned short *)(object+0x34)|=0x41;
    limit=(IntToFloat(table[globals[12]*0xE0+4]!=0)+1.0f)*3.0f-0.5f;
    amount=IntToFloat(object[0xBC]);
    amount=math_lerp_float(0.5f,limit,amount*0.083333336f);
    effect=coll_process_hit(amount, object+0x10, 0x10, object, 0);
    local=*(Quad *)(object+0x10);
    moby_queue_knockback_for_nodes(object,&local,g_area_hit_targets,effect,0,0x830000,2,1,*(float *)(table+globals[12]*0xE0+0x70),1.0f,1.0f);
    object[0xBC]++;
    if(object[0xBC]>12) moby_mark_spawned(object);
}
