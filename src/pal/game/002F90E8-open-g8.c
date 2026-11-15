#include "common.h"

/* func_PAL_002F90E8, the PAL copy of func_002F8178: the same C, where 0x112A880 becomes 0xE4E1C0
   and func_0026F720 becomes func_0026F728. */

/* Opens the vendor menu (RAC1 open_vendor_menu). It calls the boot-only
   func_PAL_002FA6F8, so it has a unit of its own and the call stays extern. */

typedef struct { int id, kind; char pad[0x10]; } ShopSlot_002F8178;
typedef struct {
    int state, unused4, field8, fieldC;
    int base10, base14, unused18, base1C;
    char pad20[8];
    char *moby;
    char pad2C[0xC];
    int field38;
    char pad3C[8];
    int field44;
    int unused48, field4C, mode;
    char pad54[0xC];
    int restore, field64, field68, field6C;
    char pad70[8];
    int field78, field7C, index, field84, field88, field8C;
    char pad90[0x10];
    int fieldA0, fieldA4;
    char padA8[0xC];
    int fieldB4, fieldB8;
    float fieldBC;
    char padC0[0x10];
    float position[4], rotation[4];
    char padF0[0x50];
    ShopSlot_002F8178 slots[64];
    int count, field744;
    char pad748[0x18];
} Shop_002F8178;
extern Shop_002F8178 g_vendor_menu_state;
typedef struct { char pad[0xC]; int baseC, base10; } Resources_002F8178;
extern Resources_002F8178 D_001BAEC0;
typedef struct { char pad[0x20]; short level; } Settings_002F8178;
extern Settings_002F8178 g_player_bolts MACRO_ADDR;
typedef struct {
    char pad[0x1248];
    int mode;
    char pad124C[0x1069];
    char flag22B5;
    char pad22B6[6];
    char flag22BC;
} Hero_002F8178;
extern Hero_002F8178 g_hero_state;
extern char g_camera_eye_state[];
extern unsigned char D_001A7BB4[] __attribute__((sda));
extern unsigned char D_001A7BB1;
extern int g_is_pal_video;
extern int g_equipment_bits MACRO_ADDR;
extern int D_001AD1C0;
extern int D_001AD1C4 __attribute__((sda)), D_001AD230 __attribute__((sda));
extern char D_001AD1E0[] SDATA(D_001AD1E0), D_001AD1F0[] SDATA(D_001AD1F0);
extern char D_001AD210[] SDATA(D_001AD210), D_001AD220[] SDATA(D_001AD220);
extern float D_001AD234 SDATA(D_001AD234), D_001AD238 SDATA(D_001AD238);
extern float D_001B2280, g_screen_fade;
extern int D_001B15A4;
extern int D_001B2238, D_001B2244, D_001B2248;
extern int D_001B2284, D_001B2288, D_001B228C, D_001B2290, D_001B2294, D_001B2298;
extern int g_current_game_mode;
extern struct { int w, h; } g_screen_width;
extern char D_00152CE4[], D_001C2AC0[];
extern void mem_clear(void *, int, int);
extern char *CreateMoby(int);
extern void FastVecAdd(void *, void *, void *);
extern void vec_clear_128(void *);
extern void func_002A0F48(void *);
extern void func_PAL_002FA6F8(void);
extern void shop_build_vendor_weapon_list(int);
extern void shop_rebuild_unlocked_slot_list(void);
extern void BuildShopChannelList(void);
extern void shop_build_vendor_list_by_flags(void);
extern void snd_send_cmd22(int);
extern void music_Pause(int);
extern void snd_Pump(void);
extern void weapon_menu_reset(void);
extern void level_forward_value(int);
extern void level_forward_pair(int, int);
extern int PlayMobySound(int, int, void *);
extern void subtitle_clear_state(void);
extern unsigned int func_PAL_0026F5B8(int, int);
extern void stub_empty_4(void);
extern void matrix_mul_vec3(void *, void *, void *);
extern float FastAddRotations(float, float);
extern void SetCamera5Pose(void *, void *, int, int, int);
extern void object_copy_vector_to_selected(void *);
extern void cam_set_state_rotation(void *);
extern void func_PAL_00272208(void);

void func_PAL_002F90E8(char *moby)
{
    int mode, v, visible, count;
    float vec[4];

    mem_clear(&g_vendor_menu_state, 0, 0x760);
    if (g_is_pal_video) D_001B2280 = 1.076923f;
    else D_001B2280 = 1.0f;
    g_vendor_menu_state.restore = 0;
    D_001AD1C0 = g_player_bolts.level;
    mode = (int)moby;
    if ((unsigned)moby < 4) {
        g_vendor_menu_state.restore = 1;
        moby = CreateMoby(11);
        *(short *)(moby + 0x32) = 64;
        if (D_001A7BB1) qcopy(vec, D_001AD1F0);
        else qcopy(vec, D_001AD1E0);
        vec[2] = -vec[2];
        FastVecAdd(moby + 0x10, g_camera_eye_state, vec);
        vec_clear_128(moby + 0xF0);
        *(float *)(moby + 0xF8) = 3.1415927f;
        func_002A0F48(moby);
        g_vendor_menu_state.restore = 1;
        g_vendor_menu_state.field744 = 0;
        moby[0x20] = 3;
        if (mode == 0) {
            g_vendor_menu_state.field744 = 0;
            g_vendor_menu_state.mode = 0;
        } else if (mode == 1) {
            g_vendor_menu_state.mode = 1;
        } else if (mode == 2) {
            g_vendor_menu_state.mode = 2;
            g_vendor_menu_state.fieldBC = -1.5707964f;
            g_vendor_menu_state.fieldB4 = 0;
            g_vendor_menu_state.fieldB8 = 0;
            g_vendor_menu_state.fieldA4 = 0;
        } else {
            g_vendor_menu_state.mode = 3;
        }
    } else if (*(short *)(moby + 0xAA) == 11) {
        g_vendor_menu_state.field744 = 0;
        v = *(int *)(*(char **)(moby + 0x68) + 0x94);
        if (v == 0) {
            g_vendor_menu_state.mode = 0;
        } else if (v == 1) {
            g_vendor_menu_state.mode = 1;
            func_PAL_002FA6F8();
        } else if (v == 4) {
            g_vendor_menu_state.mode = 2;
        } else if (v == 2) {
            g_vendor_menu_state.mode = 3;
        } else if (v == 3) {
            g_vendor_menu_state.field744 = 1;
            g_vendor_menu_state.mode = 0;
        }
    } else if (*(short *)(moby + 0xAA) == 0x1309) {
        g_vendor_menu_state.moby = moby;
        g_vendor_menu_state.mode = 2;
    } else if (*(short *)(moby + 0xAA) == 0xDDC) {
        g_vendor_menu_state.moby = moby;
        g_vendor_menu_state.mode = 1;
        func_PAL_002FA6F8();
    }
    if (D_001AD1C4 != -1) g_vendor_menu_state.mode = D_001AD1C4;
    g_vendor_menu_state.field88 = 0;
    g_vendor_menu_state.field8C = 0;
    g_vendor_menu_state.field38 = 0;
    g_vendor_menu_state.field44 = D_001A7BB4[0] - 1;
    if (g_vendor_menu_state.field44 < 0) g_vendor_menu_state.field44 = 0;
    g_vendor_menu_state.field78 = -1;
    g_vendor_menu_state.field7C = -1;
    g_vendor_menu_state.field64 = 0;
    g_vendor_menu_state.index = 0;
    D_001B2244 = 0;
    g_vendor_menu_state.field84 = 0;
    g_vendor_menu_state.field68 = -1;
    D_001AD234 = 0.8f;
    D_001AD238 = 1.0f;
    D_001B2290 = 96;
    D_001B2248 = 0;
    D_001B2238 = 0;
    D_001B2294 = 96;
    D_001AD230 = 0;
    D_001B2284 = 0;
    D_001B2288 = 0;
    D_001B2298 = 85;
    D_001B228C = 0;
    snd_send_cmd22(93);
    music_Pause(0);
    snd_Pump();
    if (g_vendor_menu_state.mode == 0) shop_build_vendor_weapon_list(0);
    else if (g_vendor_menu_state.mode == 3) shop_rebuild_unlocked_slot_list();
    else if (g_vendor_menu_state.mode == 1) BuildShopChannelList();
    else if (g_vendor_menu_state.mode == 2) shop_build_vendor_list_by_flags();
    count = g_vendor_menu_state.count;
    visible = count / 2;
    if (count < 3) visible = 1;
    g_vendor_menu_state.index = count / 2;
    g_vendor_menu_state.field6C = (visible - count / 2) * 40;
    weapon_menu_reset();
    if (g_vendor_menu_state.mode != 2) level_forward_value(0xE4E1C0);
    if (g_vendor_menu_state.mode == 0 && g_vendor_menu_state.slots[g_vendor_menu_state.index].kind == 1 && g_hero_state.mode != 10)
        level_forward_pair(g_vendor_menu_state.slots[g_vendor_menu_state.index].id, 0xE4E1C0);
    g_vendor_menu_state.state = 0;
    g_vendor_menu_state.base10 = D_001BAEC0.base10 + 0x60000;
    g_vendor_menu_state.base1C = g_vendor_menu_state.base10 + g_screen_width.w * g_screen_width.h * 4;
    g_vendor_menu_state.field8 = 0;
    g_vendor_menu_state.fieldC = 1;
    g_vendor_menu_state.moby = moby;
    g_vendor_menu_state.base14 = D_001BAEC0.baseC + 0x60000;
    PlayMobySound(3, 17, moby);
    g_vendor_menu_state.field4C = g_equipment_bits;
    g_vendor_menu_state.fieldA0 = *(short *)D_00152CE4;
    subtitle_clear_state();
    g_current_game_mode = 5;
    g_screen_fade = 0.0f;
    D_001B15A4 = 0;
    func_PAL_0026F5B8(97, 1);
    g_hero_state.flag22BC = 1;
    g_hero_state.flag22B5 = 1;
    stub_empty_4();
    if (!g_vendor_menu_state.restore) {
        if (D_001A7BB1) matrix_mul_vec3(g_vendor_menu_state.position, D_001AD1F0, g_vendor_menu_state.moby + 0xC0);
        else matrix_mul_vec3(g_vendor_menu_state.position, D_001AD1E0, g_vendor_menu_state.moby + 0xC0);
        FastVecAdd(g_vendor_menu_state.position, g_vendor_menu_state.position, g_vendor_menu_state.moby + 0x10);
        g_vendor_menu_state.rotation[2] = FastAddRotations(*(float *)(g_vendor_menu_state.moby + 0xF8), 3.1415927f);
        SetCamera5Pose(g_vendor_menu_state.position, g_vendor_menu_state.rotation, 1, 0, 0);
        qcopy(vec, g_vendor_menu_state.position);
        if (g_vendor_menu_state.mode == 2) vec[1] += 5.0f;
        object_copy_vector_to_selected(vec);
        cam_set_state_rotation(g_vendor_menu_state.rotation);
        func_PAL_00272208();
    }
    matrix_mul_vec3(D_001C2AC0 + 0x10, D_001AD210, g_vendor_menu_state.moby + 0xC0);
    qcopy(D_001C2AC0, D_001AD220);
    qzero_nc(D_001C2AC0 + 0x30);
    qzero_nc(D_001C2AC0 + 0x20);
}
