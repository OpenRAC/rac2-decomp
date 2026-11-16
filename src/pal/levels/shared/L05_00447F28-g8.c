#include "names.h"
/* func_PAL_L05_00447F28, the PAL copy of func_L05_00441D40: the same C, where 0.016666668f becomes
   0.020000001f. */
#include "include_asm.h"
#include "common.h"

extern int g_ship_state __attribute__((sda));

extern char *g_path_l05_entry_table MACRO_ADDR;
extern char *g_feltzin_target_mobys MACRO_ADDR;
extern float g_cam_pitch_param_first __attribute__((sda));
extern float g_cam_pitch_param_second __attribute__((sda));
extern float g_cam_pitch_param_third __attribute__((sda));
extern float g_cam_yaw_param_first __attribute__((sda));
extern float g_cam_yaw_param_second __attribute__((sda));
extern float g_cam_yaw_param_third __attribute__((sda));
extern float g_cam_param_c_default __attribute__((sda));
extern float g_cam_param_d_default __attribute__((sda));

typedef struct ListMoby_0042C928 {
    char pad0[0x28];
    struct ListMoby_0042C928 *next;
    char pad2C[0x7E];
    short oclass;
} ListMoby_0042C928;

extern float g_cam_init_pos_x __attribute__((sda));
extern float g_cam_init_pos_y __attribute__((sda));
extern float g_cam_init_pos_z __attribute__((sda));
extern float g_cam_chase_goal_rate __attribute__((sda));
extern int g_ship_horizontal_input_ramp __attribute__((sda));
extern int g_ship_vertical_input_ramp __attribute__((sda));
extern void vec_clear_128(void *a0);
extern void cam_load_entry_vectors(void *a0);
extern void gfx_set_clamped_view_distance(float a0);
extern void func_L05_003D1E20(void);
extern void ship_save_settings(void);

typedef struct Block_00441D40 {
    float f00, f04, f08, f0C, f10, f14;
    int f18;
    short f1C;
    u8 f1E, f1F;
    int pad20;
    int f24;
    char pad28[0x28];
    char v50[0x10];
    char v60[0x10];
    int f70;
    float f74;
    float f78;
} Block_00441D40;

typedef struct Tail_00441D40 {
    char pad0[4];
    short f04;
    short f06;
    char pad8[4];
    short f0C;
    char padE[2];
    short f10;
} Tail_00441D40;

typedef struct State_00441D40 {
    float pos[3];
    int pad0C;
    char v10[0x30];
    int f40;
    int f44;
    char pad48[8];
    Block_00441D40 blk;
    char padCC[8];
    Tail_00441D40 tail;
} State_00441D40;

typedef struct Entry_00441D40 {
    char pad0[0x20];
    int index;
    char pad24[0x34];
    int f58;
} Entry_00441D40;

typedef struct Slot_00441D40 {
    char pad0[0x1C];
    Entry_00441D40 *entry;
} Slot_00441D40;

typedef struct ActorVars_00441D40 {
    char pad0[0x38];
    float rate;
    char pad3C[0x1D8];
    int f214;
} ActorVars_00441D40;

typedef struct Actor_00441D40 {
    char pad0[0x68];
    ActorVars_00441D40 *vars;
    char pad6C[0x94];
} Actor_00441D40;

typedef struct Object_00441D40 {
    char pad0[0x70];
    State_00441D40 *state;
    char pad74[0xA];
    short f7E;
    char pad80[4];
    short f84;
} Object_00441D40;

void cam_init_state_pal(Object_00441D40 *object)
{
    State_00441D40 *state;
    State_00441D40 *state2;
    Block_00441D40 *blk;
    Tail_00441D40 *tail;
    Entry_00441D40 *entry;
    ActorVars_00441D40 *vars;
    Slot_00441D40 *table;
    char *actors;
    float rate;

    state = object->state;
    state->pos[0] = g_cam_init_pos_x;
    state->pos[1] = g_cam_init_pos_y;
    state->pos[2] = g_cam_init_pos_z;
    vec_clear_128(state->v10);
    state->f40 = 0;
    state->f44 = 0;

    state2 = object->state;
    blk = &state2->blk;
    blk->f00 = g_cam_yaw_param_first;
    blk->f04 = g_cam_yaw_param_second;
    blk->f08 = g_cam_yaw_param_third;
    blk->f74 = g_cam_param_c_default;
    blk->f78 = g_cam_param_d_default;
    blk->f0C = g_cam_pitch_param_first;
    blk->f10 = g_cam_pitch_param_second;
    blk->f14 = g_cam_pitch_param_third;
    blk->f70 = 0;
    blk->f1C = 0;
    blk->f18 = 0;
    blk->f24 = 0;
    blk->f1E = 0;
    blk->f1F = 0;
    vec_clear_128(state2->blk.v50);
    vec_clear_128(state2->blk.v60);
    cam_load_entry_vectors(object);
    gfx_set_clamped_view_distance(4096.0f);

    table = (Slot_00441D40 *)g_path_l05_entry_table;
    actors = g_feltzin_target_mobys;
    tail = &object->state->tail;
    tail->f06 = 0;
    tail->f0C = 0;
    tail->f10 = 0;
    tail->f04 = 0;
    rate = g_cam_chase_goal_rate * 0.020000001f;
    entry = table[object->f84].entry;
    entry->f58 = 0;
    vars = ((Actor_00441D40 *)(actors + (entry->index << 8)))->vars;
    vars->rate = rate;
    vars->f214 = -1;
    object->f7E = 0;
    g_ship_state = 0;
    func_L05_003D1E20();
    g_ship_horizontal_input_ramp = 0;
    g_ship_vertical_input_ramp = 0;
    ship_save_settings();
}
