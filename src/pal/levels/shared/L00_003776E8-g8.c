#include "common.h"

/* func_PAL_L00_003776E8, the PAL copy of func_L00_00374C18: the same C with two more calls, where the
   arguments 10 and 180 become 8 and 150 at 50 Hz. */

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
extern s16 func_PAL_002B8898(int);
extern int ForceClaimNotice(int, int, int);
extern void LoadClassIntoFreeCacheSlot(int);
extern void func_PAL_00295298(int);
extern void game_reset_frame_counters(void),moby_update_visible_objects(void),snd_run_callbacks(void);
extern void func_PAL_L00_002A6CB8(void);
extern void part_update_all(void),UpdateLightingEnvironment(void),func_PAL_002F6208(void);
extern int request_end_slot(int,int);
extern int func_PAL_0028E9B8(int);
extern void object_copy_vector_to_selected(void *),cam_set_state_rotation(void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern float func_L00_002EDCF0(float);
extern float FastAddRotations(float,float);
extern void func_002A0F48(void *);
extern void FastVecScale(void *,void *,float);
extern void BindVendorPreviewModel(void),func_PAL_002FC1D0(void);
extern void func_PAL_L00_00377668(void),func_PAL_L00_003771D8(void);
extern void module_l00_call_handler_with_arg_3(int),module_l00_call_handler_with_arg(int,int),func_L00_0030C710(int);
extern void level_run_callbacks(void);
extern s32 func_PAL_002E5898(void);
#define MF(o) (*(float *)(m + (o)))
/* Advances the purchase menu and its model previews, then runs the shared update. */
void func_PAL_L00_003776E8(void)
{
    int i, v;
    char *m;
    float x, y;
    double d;
    float vec[4];

    ForceClaimNotice(6, 0, 1);
    switch (g_purchase_menu_model[0].f00) {
    case 0:
        func_PAL_002B8898(1);
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
                v = g_copy_setup_data[0].entries[g_purchase_menu_model[0].fa0].value;
                func_PAL_002B8898(1);
                LoadClassIntoFreeCacheSlot(v);
                func_PAL_002B8898(1);
                func_PAL_00295298(v);
            } else {
                D_00152CE4 = -1;
            }
        }
        g_purchase_menu_model[0].f04 = 0;
        if (!g_purchase_menu_model[0].f60) {
            game_reset_frame_counters();
            moby_update_visible_objects();
            snd_run_callbacks();
            func_PAL_L00_002A6CB8();
            part_update_all();
        }
        request_end_slot(0, 0);
        func_PAL_0028E9B8(1);
        if (!g_purchase_menu_model[0].f60) {
            object_copy_vector_to_selected(((char *)g_purchase_menu_model) + 0xD0);
            cam_set_state_rotation(((char *)g_purchase_menu_model) + 0xE0);
        }
        UpdateLightingEnvironment();
        func_PAL_002F6208();
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
                matrix_mul_vec3(m + 16, ((char *)g_purchase_menu_model) + 0xC0, (char *)g_purchase_menu_model[0].f28 + 0xC0);
                FastVecAdd(m + 16, m + 16, (char *)g_purchase_menu_model[0].f28 + 16);
                MF(0x2C) = *(float *)(*(char **)(m + 0x24) + 0x24) * g_purchase_menu_model[0].f98;
                if (*(short *)(m + 0xAA) == 0x10E3)
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
                    d = x;
                    if (d < 0.0)
                        d = 0.0 - d;
                    if (d > (double)0.0001f)
                        goto moved;
                    d = y;
                    if (d < 0.0)
                        d = 0.0 - d;
                    if (d > (double)0.0001f) {
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
            func_PAL_002FC1D0();
        g_purchase_menu_model[0].f04++;
        func_PAL_L00_00377668();
        func_PAL_L00_003771D8();
        D_L00_001B25A4 = g_pad_state[0].pressed;
        if (g_purchase_menu_model[0].f50 == 0 &&
            *(int *)(((char *)g_purchase_menu_model) + 0x144 + g_purchase_menu_model[0].f80 * 24) == 1) {
            module_l00_call_handler_with_arg_3(*(int *)(((char *)g_purchase_menu_model) + 0x140 + g_purchase_menu_model[0].f80 * 24));
            {
                int selected = *(int *)(((char *)g_purchase_menu_model) + 0x140 + g_purchase_menu_model[0].f80 * 24);
                unsigned int classIndex = g_item_slot_to_record[selected];
                module_l00_call_handler_with_arg(((MenuShopClass *)g_weapon_l00_table)[classIndex].value, 8);
            }
        } else {
            module_l00_call_handler_with_arg_3(0);
        }
        func_PAL_0028E9B8(1);
        if (g_purchase_menu_model[0].f50 != 2)
            func_L00_0030C710(150);
        level_run_callbacks();
        break;
    }
    func_PAL_002E5898();
}
