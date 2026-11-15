#include "common.h"

/* Partial layouts measured from the menu, controller and resource accesses. */
typedef struct {
    int f00;
    int f04;
    int f08;
    int f0c;
    int f10;
    int f14;
    int f18;
    int f1c;
    int f20;
    int f24;
    int f28;
    int f2c;
    int f30;
    int f34;
    int f38;
    int f3c;
    int f40;
    int f44;
    int f48;
    int f4c;
    int f50;
    int f54;
    int f58;
    int f5c;
    int f60;
    int f64;
    int f68;
    int f6c;
    int f70;
    int f74;
    int f78;
    int f7c;
    int f80;
    int f84;
    int f88;
    int f8c;
    int f90;
    int f94;
    float f98;
    int f9c;
    int fa0;
    int fa4;
    float fa8;
    float fac;
    float fb0;
    float fb4;
    float fb8;
    float fbc;
    char rest[0x684];
} PurchaseMenuState;
extern PurchaseMenuState g_purchase_menu_model[];
#define MENU ((char *)D_L00_0022F7C0)
extern float D_L00_001AD570 __attribute__((sda));
extern int D_L00_001B259C, D_L00_001B25A0, D_L00_001B25A4;
typedef struct {
    int pad[0x140 / 4];
    float x, y;
    char pad148[0x78];
    int held, pressed;
} PurchaseMenuInput;
extern PurchaseMenuInput g_pad_state[];
typedef struct {
    int pad[0x4B40 / 4];
    struct { int value; char pad[16]; } entries[0];
} MenuResourceTable;
extern MenuResourceTable g_copy_setup_data[];
extern short D_00152CE4 NOT_SDA;
extern unsigned char g_item_slot_to_record[];
typedef struct {
    char prefix[0x3C];
    unsigned short value;
    char tail[0xE0 - 0x3E];
} MenuShopClass;
extern char g_weapon_l00_table[];
extern void module_l00_call_handler_with_arg_2(int);
extern s16 snd_pump_music_and_disc_read(int);
extern void LoadClassIntoFreeCacheSlot(int);
extern void SwitchCachedDiscAsset(int);
extern void game_reset_frame_counters(void),moby_update_visible_objects(void),snd_run_callbacks(void);
extern void hero_l00_update_frame_2(void);
extern void part_update_all(void),UpdateLightingEnvironment(void),game_update_idle_frame_counters(void);
extern int request_end_slot(int,int);
extern int hud_update_record_timers(int);
extern void object_copy_vector_to_selected(void *),cam_set_state_rotation(void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern float func_L00_002EDCF0(float);
extern float FastAddRotations(float,float);
extern void func_002A0F48(void *);
extern void FastVecScale(void *,void *,float);
extern void BindVendorPreviewModel(void),PrepareVendorSelectionPreview(void);
extern void menu_dispatch_by_mode(void),shop_dispatch_purchase_confirm(void);
extern void module_l00_call_handler_with_arg_3(int),module_l00_call_handler_with_arg(int,int),func_L00_0030C710(int);
extern void level_run_callbacks(void);
extern s32 UpdateSoundVoices(void);
#define MF(o) (*(float *)(m + (o)))
/* Advances the purchase menu and its model previews, then runs the shared update. */
void UpdatePurchaseMenuAndPreview(void)
{
    int i, item_id;
    char *m;
    float x, y;
    double stick_magnitude;
    float vec[4];

    switch (g_purchase_menu_model[0].f00) {
    case 0:
        D_L00_001AD570 += 0.1f;
        module_l00_call_handler_with_arg_2(1);
        if (D_L00_001AD570 >= 1.0f) {
            g_purchase_menu_model[0].f00 = 1;
            D_L00_001AD570 = 1.0f;
            g_purchase_menu_model[0].f04 = 0;
        }
        break;
    case 2:
        D_L00_001AD570 += 0.1f;
        module_l00_call_handler_with_arg_2(0);
        if (D_L00_001AD570 < 1.0f)
            break;
        D_L00_001AD570 = 1.0f;
        if (g_purchase_menu_model[0].f08) {
            g_purchase_menu_model[0].f08 = 0;
            if (g_purchase_menu_model[0].fa0 >= 0) {
                item_id = g_copy_setup_data[0].entries[g_purchase_menu_model[0].fa0].value;
                snd_pump_music_and_disc_read(1);
                LoadClassIntoFreeCacheSlot(item_id);
                snd_pump_music_and_disc_read(1);
                SwitchCachedDiscAsset(item_id);
            } else {
                D_00152CE4 = -1;
            }
        }
        g_purchase_menu_model[0].f04 = 0;
        if (!g_purchase_menu_model[0].f60) {
            game_reset_frame_counters();
            moby_update_visible_objects();
            snd_run_callbacks();
            hero_l00_update_frame_2();
            part_update_all();
        }
        request_end_slot(0, 0);
        hud_update_record_timers(1);
        if (!g_purchase_menu_model[0].f60) {
            object_copy_vector_to_selected(MENU + 0xD0);
            cam_set_state_rotation(MENU + 0xE0);
        }
        UpdateLightingEnvironment();
        game_update_idle_frame_counters();
        break;
    case 1:
        if (g_pad_state[0].held & 0x8000)
            D_L00_001B259C++;
        else
            D_L00_001B259C = 0;
        if (g_pad_state[0].held & 0x2000)
            D_L00_001B25A0++;
        else
            D_L00_001B25A0 = 0;
        if (g_purchase_menu_model[0].f90 == 0) {
            g_purchase_menu_model[0].f94 += 3;
            if (g_purchase_menu_model[0].f94 >= 128) {
                g_purchase_menu_model[0].f94 = 128;
                g_purchase_menu_model[0].f90 = 2;
            }
        } else if (g_purchase_menu_model[0].f90 == 1) {
            g_purchase_menu_model[0].f94 -= 16;
            g_purchase_menu_model[0].f98 *= 0.9f;
            if (g_purchase_menu_model[0].f94 <= 0) {
                g_purchase_menu_model[0].f94 = 0;
                g_purchase_menu_model[0].f90 = 3;
            }
        }
        if (g_purchase_menu_model[0].f88) {
            for (i = 0; i < g_purchase_menu_model[0].f34; i++) {
                float stickScale = 0.0033333334f;
                m = (char *)g_purchase_menu_model[0].f2c + i * 256;
                matrix_mul_vec3(m + 16, MENU + 0xC0, (char *)g_purchase_menu_model[0].f28 + 0xC0);
                FastVecAdd(m + 16, m + 16, (char *)g_purchase_menu_model[0].f28 + 16);
                MF(0x2C) = *(float *)(*(char **)(m + 0x24) + 0x24) * g_purchase_menu_model[0].f98;
                if (*(short *)(m + 0xAA) == MOBY_CLASS_SPACESHIP_ATTACHMENT_15)
                    m[0x23] = g_purchase_menu_model[0].f94 / 2;
                else
                    m[0x23] = g_purchase_menu_model[0].f94;
                if (g_purchase_menu_model[0].f50 != 2) {
                    MF(0xF8) = FastAddRotations(MF(0xF8), func_L00_002EDCF0(0.01f));
                } else {
                    x = g_pad_state[0].x * stickScale;
                    y = g_pad_state[0].y * stickScale;
                    if (g_purchase_menu_model[0].fa4 <= 0) {
                        g_purchase_menu_model[0].fb4 = FastAddRotations(g_purchase_menu_model[0].fb4,
                            (g_purchase_menu_model[0].fa8 - g_purchase_menu_model[0].fb4) * 0.006666667f);
                        g_purchase_menu_model[0].fb8 = FastAddRotations(g_purchase_menu_model[0].fb8,
                            (g_purchase_menu_model[0].fac - g_purchase_menu_model[0].fb8) * 0.006666667f);
                        g_purchase_menu_model[0].fbc = FastAddRotations(g_purchase_menu_model[0].fbc,
                            (g_purchase_menu_model[0].fb0 - g_purchase_menu_model[0].fbc) * 0.006666667f);
                    } else {
                        g_purchase_menu_model[0].fbc = FastAddRotations(g_purchase_menu_model[0].fbc, x);
                        g_purchase_menu_model[0].fb8 = FastAddRotations(g_purchase_menu_model[0].fb8, y);
                    }
                    MF(0xF0) = g_purchase_menu_model[0].fb4;
                    MF(0xF4) = g_purchase_menu_model[0].fb8;
                    MF(0xF8) = g_purchase_menu_model[0].fbc;
                    stick_magnitude = x;
                    if (stick_magnitude < 0.0)
                        stick_magnitude = 0.0 - stick_magnitude;
                    if (stick_magnitude > (double)0.0001f)
                        goto moved;
                    stick_magnitude = y;
                    if (stick_magnitude < 0.0)
                        stick_magnitude = 0.0 - stick_magnitude;
                    if (stick_magnitude > (double)0.0001f) {
                    moved:
                        g_purchase_menu_model[0].fa4 = 180;
                    }
                }
                func_002A0F48(m);
                if (g_purchase_menu_model[0].f50 != 2) {
                    FastVecScale(vec, m, 0.0009765625f);
                    MF(0x10) += MF(0x10) - vec[0];
                    MF(0x14) += MF(0x14) - vec[1];
                    func_002A0F48(m);
                }
            }
            if (g_purchase_menu_model[0].fa4 > 0)
                g_purchase_menu_model[0].fa4--;
        }
        if (g_purchase_menu_model[0].f8c)
            BindVendorPreviewModel();
        else if (g_purchase_menu_model[0].f90 == 3 && g_purchase_menu_model[0].f84 == 0 &&
                 g_purchase_menu_model[0].f6c == 0)
            PrepareVendorSelectionPreview();
        g_purchase_menu_model[0].f04++;
        menu_dispatch_by_mode();
        shop_dispatch_purchase_confirm();
        D_L00_001B25A4 = g_pad_state[0].pressed;
        if (g_purchase_menu_model[0].f50 == 0 &&
            *(int *)(MENU + 0x144 + g_purchase_menu_model[0].f80 * 24) == 1) {
            module_l00_call_handler_with_arg_3(*(int *)(MENU + 0x140 + g_purchase_menu_model[0].f80 * 24));
            {
                int selected = *(int *)(MENU + 0x140 + g_purchase_menu_model[0].f80 * 24);
                unsigned int classIndex = g_item_slot_to_record[selected];
                module_l00_call_handler_with_arg(((MenuShopClass *)g_weapon_l00_table)[classIndex].value, 10);
            }
        } else {
            module_l00_call_handler_with_arg_3(0);
        }
        hud_update_record_timers(1);
        if (g_purchase_menu_model[0].f50 != 2)
            func_L00_0030C710(180);
        level_run_callbacks();
        break;
    }
    UpdateSoundVoices();
}
