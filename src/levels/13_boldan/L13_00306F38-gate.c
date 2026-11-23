#include "common.h"
extern void moby_mark_spawned(void *);
extern int hero_is_current_selected_id(void *);
extern int IsPointInCuboid(void *,int);
extern int hero_l13_set_move_state(int,int);
extern void math_apply_axis_rotation_to_quat(void *,void *,void *,float);
extern float vec_distance_xy(void *,void *);
extern struct { char pad[0x348]; short state; } g_hero_state;
extern char g_hero_position[];
/* Gate that swings open when the player triggers it, stays open while the player is near, and closes again when the player leaves. */
void gate_l13_update(char *moby) {
    char *vars=*(char **)(moby+0x68);
    if (!vars) { moby_mark_spawned(moby); return; }
    switch (*(u8 *)(moby+0x20)) {
    case 0:
        *(int *)(vars+0xC)=0;
        *(int *)(vars+4)=0;
        *(u16 *)(moby+0x34)|=0x100;
        if (*(int *)vars) *(u8 *)(moby+0x20)=1;
        else *(u8 *)(moby+0x20)=4;
        break;
    case 1:
        if (hero_is_current_selected_id(moby)) {
            if (g_hero_state.state==1 && IsPointInCuboid((char *)&g_hero_state+0x80,*(int *)(vars+8))) {
                *(u16 *)(moby+0x96)=0;
                hero_l13_set_move_state(0x6F,1);
                *(u8 *)(moby+0x20)=2;
            }
            if (*(int *)(vars+8)!=-1 || !*(char **)(vars+0xC)) break;
            if (*(u8 *)(*(char **)(vars+0xC)+0x20)==0xFE) goto opened;
            if (*(u8 *)(*(char **)(vars+0xC)+0x20)!=0xFD) break;
opened:
            if (g_hero_state.state==1) {
                *(u16 *)(moby+0x96)=0;
                *(u8 *)(moby+0x20)=2;
            }
        } else *(u16 *)(moby+0x96)=0;
        break;
    case 2:
        if (*(u16 *)(moby+0x96)<91) {
            math_apply_axis_rotation_to_quat(moby+0xC0,moby+0xC0,moby+0xD0,0.017453294f);
            math_apply_axis_rotation_to_quat(moby+0xE0,moby+0xE0,moby+0xD0,0.017453294f);
            (*(u16 *)(moby+0x96))++;
        } else {
            hero_l13_set_move_state(0,1);
            *(u8 *)(moby+0x20)=7;
        }
        break;
    case 3:
        if (*(u16 *)(moby+0x96)<91 && *(int *)(vars+4)==0) {
            math_apply_axis_rotation_to_quat(moby+0xC0,moby+0xC0,moby+0xD0,-0.034906588f);
            math_apply_axis_rotation_to_quat(moby+0xE0,moby+0xE0,moby+0xD0,-0.034906588f);
            *(u16 *)(moby+0x96)+=2;
        }
        if (*(u16 *)(moby+0x96)>=91 || *(int *)(vars+4)) {
            *(int *)(vars+4)=1;
            *(u8 *)(moby+0x20)=1;
            *(u16 *)(moby+0x96)=0;
        }
        break;
    case 5:
        math_apply_axis_rotation_to_quat(moby+0xC0,moby+0xC0,moby+0xD0,-0.017453294f);
        math_apply_axis_rotation_to_quat(moby+0xE0,moby+0xE0,moby+0xD0,-0.017453294f);
        if (--*(u16 *)(moby+0x96)==0) {
            *(u16 *)(moby+0x96)=0;
            *(u8 *)(moby+0x20)=1;
        }
        break;
    case 7:
        if (vec_distance_xy(moby+0x10,g_hero_position)<4.0f) *(short *)(g_hero_position+0x194)=2;
        else *(short *)(g_hero_position+0x194)=0;
    case 6:
        if (g_hero_state.state!=1) *(u8 *)(moby+0x20)=5;
        break;
    }
}
