#include "include_asm.h"

#include "common.h"
extern void moby_transform_joint_to_world(void *,int,void *);
extern void moby_copy_joint_transform_to_object(void *,void *,int,int);
extern void func_PAL_002A0F68(void *);
extern void func_002A0F48(void *);
extern void euler_rotation_basis(void *,void *);
extern void func_002A10E8(void *);
extern void func_PAL_L18_004384D8(void *);
extern void DrawPairedBranchingRibbonEffects(void *);
extern void extermibot_update_linked_parts(void *);
extern void part_spawn_glow_flash(void *);
extern void gfx_add_draw_callback_third(void (*)(void *),void *);
extern int math_random_int_below(int);
extern int math_random_int_range(int,int);
extern void func_PAL_L18_0043A158(void *,int);
extern float fast_vec_dist(void *,void *);
extern float g_camera_l18_position[];
extern void moby_update_ground_check(void *);
extern void func_PAL_002B14F8(void *,float *,float,int,int);

void func_PAL_L18_00437388(unsigned char *object)
{
    float position[4] __attribute__((aligned(16)));
    unsigned char *state=*(unsigned char **)(object+0x68);
    if(*(unsigned short *)(object+0x96)<0xFFFF)
        ++*(unsigned short *)(object+0x96);
    if(*(short *)(state+0x804)<0x7FFF)
        ++*(unsigned short *)(state+0x804);
    if(*(void **)(state+0x7C0)) {
        moby_transform_joint_to_world(object,0,position);
        {
            unsigned char *child=*(unsigned char **)(state+0x7C0);
            qcopy(child+0x10,position);
            *(float *)(child+0x48)=*(float *)(object+0x48);
        }
        if(*(void **)(state+0x7C8))
            moby_copy_joint_transform_to_object(*(void **)(state+0x7C0),*(void **)(state+0x7C8),2,0);
        if(*(void **)(state+0x7C4)) {
            *(float *)(*(unsigned char **)(state+0x7C4)+0x48)=*(float *)(object+0x48);
            moby_transform_joint_to_world(*(void **)(state+0x7C0),0,position);
            {
                unsigned char *child=*(unsigned char **)(state+0x7C4);
                qcopy(child+0x10,position);
                qcopy(child+0xF0,*(unsigned char **)(state+0x7C0)+0xF0);
                func_PAL_002A0F68(child);
            }
            func_002A0F48(*(void **)(state+0x7C4));
            {
                unsigned char *child=*(unsigned char **)(state+0x7C4);
                euler_rotation_basis(child+0xC0,child+0xF0);
            }
            func_002A10E8(*(void **)(state+0x7C4));
        }
    }
    if(object && object[0x20]!=0xFE && object[0x20]!=0xFD && object[0x20]>=2) {
        if(*(short *)(state+0x7FC)==0 && *(void **)(state+0x7C8)) {
            func_PAL_L18_004384D8(object);
            gfx_add_draw_callback_third(DrawPairedBranchingRibbonEffects,object);
        }
        if(object[0x31])
            gfx_add_draw_callback_third(extermibot_update_linked_parts,object);
        if(!*(void **)(state+0x7C0)) {
            moby_transform_joint_to_world(object,0,position);
            if(math_random_int_below(20)==0)
                func_PAL_L18_0043A158(position,math_random_int_range(10,15));
            gfx_add_draw_callback_third(part_spawn_glow_flash,object);
        }
    }
    if(object[0x31] && fast_vec_dist(object+0x10,g_camera_l18_position)<24.0f) {
        moby_update_ground_check(object);
        object[0x6F]=22;
    }
    {
        void *child=*(void **)(state+0x7C4);
        *(short *)(state+0x808)=0;
        if(child)
            func_PAL_002B14F8(child,(float *)(state+0x810),2.5f,5,1);
    }
}
