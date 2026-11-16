#include "common.h"

/* func_L17_00420A50 has a unit of its own: it needs -ffast-math (config/cflags.txt),
 * and its state switch brings a jump table. The link scan counts with an upward
 * index: loop.c turns links[j] into a pointer giv and reverses j into a countdown
 * whose init follows the hoisted -1/0xFE/0xFD constants, as in retail; that order
 * gives the state value a3 and the shared -1 t0. */
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
#define H(p,o) (*(short *)((u8 *)(p)+(o)))
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
extern u8 *g_moby_l17_pool;
extern int g_current_map_index __attribute__((sda));
extern u8 g_moby_group_flags[];
extern u8 g_str_linked_group_debug_a[],g_str_linked_group_debug_b[],g_str_linked_group_debug_c[];
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void STUB_printf(void *,...);
extern int math_fast_float_d(void *);
extern void coll_hit_mobys_inside_box_copy(void *,void *);
extern void moby_mark_spawned(void *);
typedef struct {int index;short uid;signed char state;u8 pad;} Link;
/* Counts the linked objects that are still alive, copies position and turn from its
   target, and removes itself when it is finished (moby class 4869). */
void linked_moby_group_update(u8 *obj)
{
    int count=0,i;
    u8 *target=0,*other,*vars=*(u8 **)(obj+0x68);
    Link *links=(Link *)(vars+0x18),*link;
    if(I(vars,0x10)!=-1) target=g_moby_l17_pool+I(vars,0x10)*256;
    if(obj[0xB0]!=255 && (g_moby_group_flags[obj[0xB0]+g_current_map_index*16]&0x80)) goto dispatch;
    if(obj[0x20]!=0) {
        int j;
        for(j=0;j<5;j++) {
            if(links[j].index!=-1) {
                other=g_moby_l17_pool+links[j].index*256;
                if(other && H(other,0xAA)==links[j].uid && other[0x20]!=254 && other[0x20]!=253) {
                    if(links[j].state==-1 || other[0x20]!=links[j].state) count++;
                }
            }
        }
    }
dispatch:
    switch(obj[0x20]) {
    case 0:
        if(target) {
            H(vars,0x14)=H(target,0xAA);
            F(vars,0x44)=IntToFloat(target[0x23]);
            if(I(vars,8)&0x10) qcopy_nc(obj+0x10,target+0x10);
            else if(I(vars,8)&0x40) qcopy_nc(target+0x10,obj+0x10);
            if(I(vars,8)&0x20) qcopy_nc(obj+0xF0,target+0xF0);
            else if(I(vars,8)&0x80) qcopy_nc(target+0xF0,obj+0xF0);
        } else STUB_printf(g_str_linked_group_debug_a);
        for(i=0,link=links;i<5;i++,link++) {
            if(link->index!=-1) {
                link->uid=H(g_moby_l17_pool+link->index*256,0xAA);
                STUB_printf(g_str_linked_group_debug_b,(obj-g_moby_l17_pool)>>8,i,link->index,(int)link->uid);
            } else STUB_printf(g_str_linked_group_debug_c,(obj-g_moby_l17_pool)>>8,i);
        }
        F(obj,0x2C)=(F(vars,0)<F(vars,4)?F(vars,4):F(vars,0))*F(*(u8 **)(obj+0x24),0x24);
        obj[0x20]=1;
        break;
    case 1:
        if(!count) {
            if(target && *(signed char *)(vars+0x16)!=-1) target[0x20]=vars[0x16];
            I(vars,0x40)=I(vars,0xC);
            obj[0x20]=2;
        }
        coll_hit_mobys_inside_box_copy(obj,vars);
        break;
    case 2:
        if(target && !(I(vars,8)&2)) {
            float timer=IntToFloat(I(vars,0x40));
            float total=IntToFloat(I(vars,0xC));
            target[0x23]=FloatToInt((F(vars,0x44)*timer)/total);
        }
        if(!(I(vars,8)&4)) {
            if(target && *(signed char *)(vars+0x17)!=-1 && target[0x20]==*(signed char *)(vars+0x17)) obj[0x20]=3;
        }
        if(!(I(vars,8)&8) && math_fast_float_d(vars+0x40)) obj[0x20]=3;
        coll_hit_mobys_inside_box_copy(obj,vars);
        break;
    case 3:
        if(target && !(I(vars,8)&1)) moby_mark_spawned(target);
        moby_mark_spawned(obj);
        break;
    case 4:
        break;
    }
}
