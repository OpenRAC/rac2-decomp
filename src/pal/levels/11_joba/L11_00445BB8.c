#include "include_asm.h"




#include "common.h"
extern u8 g_moby_l11_script_data_2[];
extern u8 *g_group_id_lists[];
extern u8 *g_moby_l11_table __attribute__((section(".sdata")));
typedef struct {
    u8 pad0[0x10];
    float pos[4];
    u8 state;
    u8 pad21[0x89];
    short oclass;
    u8 padAC[0xC];
    void *owner;
    u8 padBC[4];
    float rot[12];
    float fF0;
    float fF4;
    float fF8;
} GroupMoby440B28;
typedef struct {
    u8 pad0[0xC0];
    int group;
} GroupVars440B28;
extern char *g_moby_group_entries __attribute__((sda));
extern unsigned short *g_fighter_target_lists[];
extern float mat_fast_helper_a(float, float);
extern void euler_rotation_basis(void *, void *);
extern void enemy_init_state_pal(void *, int, int);
extern u8 *g_group_id_lists[];
extern u8 *g_moby_l11_table;
extern u8 *D_L11_001B359C_base[] __asm__("D_L11_001B359C") __attribute__((sda));
extern u8 *g_arena_camera_table __attribute__((sda));
extern u8 g_hero_state[];
extern u8 g_music_state[];

int arena_launch_fighter_toward_target_pal(u8 *object, float *target)
{
    GroupMoby440B28 *member;
    unsigned short *list;
    unsigned short *p;
    int group;
    float dx;

    group = ((GroupVars440B28 *)*(u8 **)(object + 0x68))->group;
    if (group == 0xFF)
        return 0;
    list = g_fighter_target_lists[group];
    if (list == 0)
        return 0;
    p = list;
    do {
        member = (GroupMoby440B28 *)(g_moby_group_entries + (*p & 0x7FFF) * 0x100);
        if (member != 0 && member->state != 0xFE && member->state != 0xFD &&
            member->oclass == 0xD37 && member->state == 1) {
            member->owner = object;
            qcopy(member->pos, target);
            member->fF0 = 0.0f;
            member->fF4 = -1.5707965f;
            dx = target[0] - ((float *)arena_get_center_point(object))[0];
            member->fF8 = mat_fast_helper_a(dx, target[1] - ((float *)arena_get_center_point(object))[1]);
            euler_rotation_basis(member->rot, &member->fF0);
            enemy_init_state_pal(member, 0, 1);
            return 1;
        }
    } while ((short)*p++ >= 0);
    return 0;
}

