/* func_PAL_00287018, the PAL copy of func_00286738: the same C at 50 Hz timings, where
 * the mode 1 accept path also runs when D_001A7424 & 0x600 and func_PAL_00299518() hold,
 * and clears those flags with func_PAL_00299520() before closing.
 * It needs its own unit: -O2 -G8 -ffunction-sections -frac2-zero-ti-por
 * (config/cflags.txt). D_001B17D0's sda declaration gives retail's repeated
 * lui/addiu; D_0018C0D4, D_001F29A0 and D_001F2930 need absolute addressing;
 * D_001B1680 uses an incomplete sda view for its absolute store macro.
 * func_002AA548 returns float; func_0028B3D0 and func_PAL_002E5898 return int.
 * In USA v1.01 ref_00286738_00 is 0x1A8A44 in the boot and 0x1A8D94 in every level, where
 * func_L00_003A0C00 uses the name D_001A8A44 for a different word at 0x1A8A44.
 */

#include "common.h"

/* Modal state observed by the menu and camera transition handlers. */
typedef int Quadword __attribute__((mode(TI)));
typedef struct {
    float cameraPosition[4];
    float cameraAngles[4];
    float returnPosition[4];
    float returnAngles[4];
    int mode;
    int countdown;
    char reserved48[12];
    int selection;
    int phase;
    int elapsed;
    int inputDelay;
    int reserved64;
    int pending;
    float fraction;
    float angle;
    char reserved74[8];
    short timer;
    short cameraActive;
    int savedValue;
    short result;
    short reserved86;
    int enabled;
    unsigned int acceptMask;
    unsigned int cancelMask;
    int gameState;
} ModalState;

typedef struct {
    char reserved00[0x100];
    float roll;
    char reserved104[0x44];
    float horizontal;
    float vertical;
    char reserved150[0x54];
    unsigned int buttons;
    char reserved1A8[0x18];
    unsigned int held;
    unsigned int pressed;
} ModalInput;

typedef struct CameraObject CameraObject;
struct CameraObject {
    char reserved00[0x64];
    void (*update)(CameraObject *);
    char reserved68[0x42];
    short kind;
    char reservedAC[0x54];
};

extern ModalState g_modal_state;
extern ModalInput g_pad_state;
extern int D_001B170C;
extern int g_save_menu_screen;
extern int g_save_menu_flags;
extern int D_001A8C88;
extern int D_001A8C8C;
extern int D_001F29A0 NOT_SDA;
typedef struct {
    char reserved00[0x18];
    int selection;
    char reserved1C[0xE4];
    int savedSelection;
} ModalSelection;
extern ModalSelection g_pause_menu_state;
extern int *D_001F2930 NOT_SDA;
extern unsigned short g_subtitle_history[];
extern unsigned char D_001B1F10;
typedef struct {
    char reserved00[8];
    int status;
    char reserved0C[4];
    int result;
} ModalCardState;
extern ModalCardState g_memcard_state;
extern int D_0013955C[];
extern int D_001A8B84 __attribute__((sda));
extern int D_001B1680[] __attribute__((sda));
extern int D_001A8A78 __attribute__((sda));
extern float D_001A8A7C __attribute__((sda));
typedef struct {
    float position[4];
    float angles[4];
    char reserved20[0x210];
    float matrix[16];
} ModalCamera;
extern ModalCamera g_camera_eye_state;
extern float D_001B17D0[4] __attribute__((sda));
extern unsigned char D_001A7A44;
extern int g_current_map_index;
extern CameraObject *D_001B1B5C;
extern CameraObject *D_001B1B60;
extern unsigned char D_0018C0D4 NOT_SDA;
extern int D_001A8A40 __attribute__((sda));
extern int ref_00286738_00 __attribute__((sda));
extern int D_001A8A48 __attribute__((sda));
extern int D_001A8A60 __attribute__((sda));
extern int g_widescreen_flag;

extern int func_PAL_002E5898(void);
extern int request_begin_slot(int, int, int, int, unsigned char *);
extern void FadeToBlack(int);
extern int flag_get_word(void);
extern void flag_clear_word(void);
extern int func_PAL_00299518(void);
extern int func_PAL_00299520(void);
extern void menu_clear_counter(void);
extern int menu_is_known_screen_active(void);
extern int menu_get_saved_value(void);
extern void save_load_packet(int *);
extern void menu_clear_confirm_pending(void);
extern int request_end_slot(int, int);
extern void func_PAL_002997A0(void);
extern void load_data_and_setup_callback(void);
extern void func_PAL_002DF760(int);
extern void FastVecSub(void *, const void *, const void *);
extern float FastVecLength(void *);
extern float math_step_value_toward_target(float *, float *, float, float, float, float);
extern void vec_scale_to_length(void *, const void *, float);
extern void FastVecAdd(void *, const void *, const void *);
extern void func_PAL_002884F0(char *, int);
extern void matrix_mul_vec3(void *, const void *, const void *);
extern void vec_clamp_length(float *, float);
extern void FastVecScale(void *, const void *, float);
extern void cam_offset_direction(char *);
extern void func_PAL_00288638(float *);
extern void matrix_from_basis_rows(void *, const void *);
extern void mat_get_euler_angles(float *, float *);
extern void lerp_vector(void *, const void *, const void *, float);
extern void mat_build_rotation_from_angles(void *, float *);
extern void vec_fast_normalize3(void *, const void *, const void *, float);
extern void quaternion_to_rotation_basis(const void *, void *);
extern void func_PAL_0026F620(void);
extern void hud_request_letterbox_bars(void);
extern void menu_set_state_word_three(void);
extern int hud_set_slot_contents(int, int, void (*)(unsigned char *), void (*)(), void (*)(), int, int);
extern void menu_init_panel_layout(unsigned char *);
extern void weapon_wheel_update_select();
extern int weapon_wheel_draw();
extern void weapon_wheel_init(unsigned char *);
extern void UpdateRadialMenuSelection();
extern int DrawRadialSelectorPanel();
extern void func_PAL_0029D7D0(void);
extern void func_PAL_0029C0B8(int);
extern void level_forward_value(int);
extern void hud_clear_flag_b(void);
extern void hud_clear_flag_a(void);
extern void func_PAL_002B5570(int);
extern int snd_play_from_global_bank(int, int, void *);
extern void gfx_apply_screen_aspect_mode(void);

/* Run the active modal dialog, camera return, or display-confirmation phase. */
void func_PAL_00287018(void)
{
    float delta[4], target[4], transform[16];
    float distance;
    ModalState *loadDialog, *saveDialog, *phaseDialog;
    ModalInput *saveInput;

    func_PAL_002E5898();
    D_001B170C = g_modal_state.gameState;
    if (g_modal_state.countdown)
        --g_modal_state.countdown;
    if (g_modal_state.timer)
        --g_modal_state.timer;
    switch (g_modal_state.mode) {
    case 2:
        ++g_modal_state.elapsed;
        if (g_modal_state.elapsed > 75 && g_modal_state.inputDelay)
            --g_modal_state.inputDelay;
        if (g_save_menu_screen == 2) {
            request_begin_slot(4, 2, 1, 0, 0);
            break;
        }
        if (g_modal_state.elapsed >= 101 && (g_pad_state.buttons & 0x40)) {
            if (!g_subtitle_history[0x84 / 2])
                g_subtitle_history[0x84 / 2] = 1;
            { request_end_slot(0, 0); break; }
        }
        break;
    case 5:
        ++g_modal_state.elapsed;
        if (g_modal_state.elapsed > 25 && g_modal_state.inputDelay)
            --g_modal_state.inputDelay;
        if (!g_modal_state.inputDelay && (g_pad_state.buttons & 0x40)) {
            g_save_menu_flags &= ~0x40;
            D_0013955C[0] = 0;
            { func_PAL_002DF760(-1); load_data_and_setup_callback(); break; }
        }
        break;
    case 4:
        ++g_modal_state.elapsed;
        if (g_modal_state.elapsed > 25 && g_modal_state.inputDelay)
            --g_modal_state.inputDelay;
        if (!g_modal_state.inputDelay && (g_pad_state.buttons & 0x40)) {
            D_0013955C[0] = 0;
            { func_PAL_002DF760(-1); load_data_and_setup_callback(); break; }
        }
        break;
    case 3:
        switch (g_modal_state.phase) {
        case 0:
            if (!g_modal_state.countdown)
                g_modal_state.phase = 1;
            break;
        case 1:
            if (g_pad_state.buttons & 0x10)
                { request_end_slot(0, 0); break; }
            if (g_pad_state.buttons & 0x40) {
                FadeToBlack(4);
                D_001B1F10 = 0;
                g_modal_state.phase = 2;
                g_modal_state.elapsed = 500;
            }
            break;
        case 2:
            if (!g_modal_state.elapsed || --g_modal_state.elapsed == 0) {
                D_001B1F10 = 1;
                g_modal_state.phase = 3;
                break;
            }
            if (g_pad_state.buttons & 0x10) {
                FadeToBlack(4);
                D_001B1F10 = 1;
                { request_end_slot(0, 0); break; }
            } else if (g_pad_state.buttons & 0x40) {
                D_001B1F10 = 0;
                { request_end_slot(0, 0); break; }
            }
            break;
        case 3:
            if (!(g_pad_state.buttons & 0x40))
                break;
        default:
            { request_end_slot(0, 0); break; }
        }
        break;
    case 1:
        ++g_modal_state.elapsed;
        if (g_modal_state.elapsed > 25 && g_modal_state.inputDelay)
            --g_modal_state.inputDelay;
        if (flag_get_word() || ((g_save_menu_flags & 0x600) && func_PAL_00299518())) {
            if (!(g_pad_state.buttons & 0x40))
                break;
            flag_clear_word();
            g_save_menu_flags &= ~0x640;
            func_PAL_00299520();
            menu_clear_counter();
            { request_end_slot(0, 0); break; }
        }
        switch (g_save_menu_screen) {
        case 2:
            if (!g_modal_state.inputDelay && (g_pad_state.buttons & 0x40)) {
                g_modal_state.result = 2;
                g_save_menu_flags &= ~1;
                { request_end_slot(0, 0); break; }
            }
            break;
        case 6:
            if (!g_modal_state.inputDelay && (g_pad_state.buttons & 0x20)) {
                g_save_menu_flags |= 8;
                g_modal_state.result = 2;
                break;
            }
            if (g_modal_state.countdown || !(g_pad_state.buttons & 0x10))
                break;
            if (D_001A8C8C) {
                g_modal_state.result = 2;
                { func_PAL_002DF760(-1); load_data_and_setup_callback(); break; }
            }
            g_save_menu_flags |= 0x20;
            if (!menu_is_known_screen_active())
                g_save_menu_flags &= ~2;
            g_save_menu_flags &= ~4;
            g_modal_state.result = 1;
            if (!D_001A8C88) {
                request_end_slot(0, 0);
                break;
            }
            break;
        case 13:
            if (!g_modal_state.inputDelay && (g_pad_state.buttons & 0x20)) {
                g_save_menu_flags |= 0x10;
                g_modal_state.result = 2;
                break;
            }
            if (g_modal_state.countdown || !(g_pad_state.buttons & 0x10))
                break;
            if (D_001A8C8C) {
                g_modal_state.result = 2;
                { func_PAL_002DF760(-1); load_data_and_setup_callback(); break; }
            }
            g_save_menu_flags |= 0x20;
                g_save_menu_flags &= ~2;
                g_save_menu_flags &= ~4;
            g_modal_state.result = 1;
            if (!D_001A8C88)
                { request_end_slot(0, 0); break; }
            break;
        case 20:
            if (g_modal_state.inputDelay || !(g_pad_state.buttons & 0x40))
                break;
            g_save_menu_flags &= ~0x40;
                g_save_menu_flags &= ~0x400;
                g_save_menu_flags &= ~2;
                g_save_menu_flags &= ~4;
            g_modal_state.result = 2;
            if (!D_001A8C88) {
                if (menu_get_saved_value()) {
                    save_load_packet(D_001F2930);
                    request_end_slot(0, 0);
                } else {
                    D_0013955C[0] = 0;
                    D_001B1680[0] = -1;
                    D_001A8B84 = 1;
                }
                break;
            }
            request_end_slot(0, 0);
            break;
        case 17:
        case 18:
        case 21:
            if (g_modal_state.pending > 0) {
                if (--g_modal_state.pending <= 0) {
                    if (g_memcard_state.status == 2) {
                        if (!g_memcard_state.result) {
                            g_save_menu_screen = 9;
                        } else if (g_memcard_state.result == -1) {
                            g_save_menu_screen = 9;
                            g_memcard_state.result = 0;
                        } else if (g_memcard_state.result == -2) {
                            g_save_menu_screen = 5;
                        } else {
                            g_save_menu_screen = 12;
                        }
                        request_end_slot(0, 0);
                    } else {
                        g_modal_state.result = 2;
                        menu_clear_confirm_pending();
                        func_PAL_002DF760(-1);
                        load_data_and_setup_callback();
                    }
                    break;
                }
            } else {
                if (g_modal_state.inputDelay || !(g_pad_state.buttons & 0x40))
                    break;
                menu_clear_confirm_pending();
                if (D_001A8C8C) {
                    g_modal_state.pending = 12;
                } else {
                    g_modal_state.result = 2;
                    g_save_menu_flags &= ~0x40;
                    g_save_menu_flags &= ~0x400;
                    g_save_menu_flags &= ~2;
                    g_save_menu_flags &= ~4;
                    request_end_slot(0, 0);
                }
            }
            break;
        case 1:
        case 16:
            request_end_slot(0, 0);
            g_pause_menu_state.selection = g_modal_state.selection;
            g_pause_menu_state.savedSelection = g_modal_state.selection;
            break;
        case 12:
            if (!D_001F29A0)
                break;
        case 3:
        case 5:
            if (!g_modal_state.inputDelay && (g_pad_state.buttons & 0x10)) {
                g_modal_state.result = 1;
                g_save_menu_flags &= ~2;
                g_save_menu_flags &= ~4;
                { request_end_slot(0, 0); break; }
            }
            break;
        case 19:
            if (D_001A8C88 && !D_001F29A0) {
                /* Set once, unlike a shared pointer, so alias analysis knows its
                 * base and the cancel arm's store has no tie to D_001A7424. The
                 * accept body below merges with case 23's copy at jump2. */
                ModalState *pickDialog = &g_modal_state;
                if (pickDialog->inputDelay)
                    break;
                if (g_pad_state.buttons & 0x40) {
                    func_PAL_002997A0();
                    pickDialog->result = 2;
                    g_save_menu_flags &= ~2;
                    g_save_menu_flags &= ~4;
                    g_save_menu_flags |= 0x20;
                    load_data_and_setup_callback();
                    break;
                }
                if (!(g_pad_state.buttons & 0x10))
                    break;
                pickDialog->result = 1;
                g_save_menu_flags &= ~2;
                g_save_menu_flags &= ~4;
                { request_end_slot(0, 0); break; }
            }
            if (D_001A8C8C)
                goto acceptReload;
            {
                if (g_modal_state.inputDelay)
                    break;
                if (!(g_pad_state.buttons & 0x40) || D_001F29A0) {
                    if (!(g_pad_state.buttons & 0x10) || !D_001F29A0)
                        break;
                }
                g_save_menu_flags &= ~2;
                g_save_menu_flags &= ~4;
                g_modal_state.result = 1;
                { request_end_slot(0, 0); break; }
            }
        case 23:
        case 24:
            loadDialog = &g_modal_state;
            if (loadDialog->inputDelay)
                break;
            if (g_pad_state.buttons & 0x40) {
                func_PAL_002997A0();
                loadDialog->result = 2;
                g_save_menu_flags &= ~2;
                g_save_menu_flags &= ~4;
                g_save_menu_flags |= 0x20;
                load_data_and_setup_callback();
                break;
            }
            if (g_pad_state.buttons & 0x10) {
                loadDialog->result = 1;
                g_save_menu_flags |= 0x20;
                { request_end_slot(0, 0); break; }
            }
            break;
        case 4:
            if (D_001A8C88) {
                if (!D_001F29A0) {
                    saveDialog = &g_modal_state;
                    if (saveDialog->inputDelay)
                        break;
                    saveInput = &g_pad_state;
                    if (saveInput->buttons & 0x40) {
                        func_PAL_002997A0();
                        saveDialog->result = 2;
                        g_save_menu_flags &= ~2;
                        g_save_menu_flags &= ~4;
                        load_data_and_setup_callback();
                    }
                    if (!saveDialog->inputDelay && (saveInput->buttons & 0x10)) {
                        saveDialog->result = 1;
                        g_save_menu_flags |= 0x20;
                        g_save_menu_flags &= ~2;
                        g_save_menu_flags &= ~4;
                        request_end_slot(0, 0);
                    }
                    break;
                }
            } else if (D_001A8C8C) {
acceptReload:
                if (!g_modal_state.inputDelay && (g_pad_state.buttons & 0x40)) {
                    g_modal_state.result = 2;
                    func_PAL_002DF760(-1);
                    load_data_and_setup_callback();
                }
                break;
            }
            if (!g_modal_state.inputDelay && (g_pad_state.buttons & 0x10)) {
                g_modal_state.result = 1;
                g_save_menu_flags |= 0x20;
                g_save_menu_flags &= ~2;
                g_save_menu_flags &= ~4;
                request_end_slot(0, 0);
            }
            break;
        case 9:
            if (!(g_save_menu_flags & 6))
                { request_end_slot(0, 0); break; }
            break;
        }
        break;
    case 6:
        switch (g_modal_state.phase) {
        case 0:
            qcopy(g_modal_state.cameraPosition, g_camera_eye_state.position);
            qcopy(g_modal_state.cameraAngles, g_camera_eye_state.angles);
            g_modal_state.phase = 1;
            break;
        case 1:
            D_001B170C = 3;
            FastVecSub(delta, g_camera_eye_state.position, D_001B17D0);
            distance = FastVecLength(delta);
            math_step_value_toward_target(&distance, &g_modal_state.fraction, (float)D_001A8A78,
                    0.060000002f, 0.060000002f, 6.0000005f);
            vec_scale_to_length(delta, delta, distance);
            FastVecAdd(g_camera_eye_state.position, delta, D_001B17D0);
            func_PAL_002884F0((char *)&g_modal_state.angle, 0);
            if ((float)D_001A8A78 <= distance)
                g_modal_state.phase = 2;
            break;
        case 2:
            D_001B170C = 3;
            if (g_pad_state.horizontal != 0.0f || g_pad_state.vertical != 0.0f) {
                *(Quadword *)target = 0;
                target[1] = g_pad_state.horizontal;
                target[2] = g_pad_state.vertical;
                *(Quadword *)delta = *(Quadword *)target;
                matrix_mul_vec3(delta, delta, g_camera_eye_state.matrix);
                vec_clamp_length(delta, 1.0f);
                FastVecScale(delta, delta,
                        (float)-D_001A8A78 * 0.0003490659f * D_001A8A7C);
                cam_offset_direction((char *)delta);
            }
            func_PAL_002884F0((char *)&g_modal_state.angle, 1);
            func_PAL_00288638(&g_pad_state.roll);
            break;
        case 3: {
            float speed;
            D_001B170C = 3;
            speed = (float)D_001A8A78 * 0.0003490659f * D_001A8A7C;
            FastVecSub(target, g_modal_state.cameraPosition, D_001B17D0);
            vec_scale_to_length(target, target, (float)D_001A8A78);
            FastVecAdd(target, target, D_001B17D0);
            FastVecSub(delta, target, g_camera_eye_state.position);
            matrix_from_basis_rows(transform, g_camera_eye_state.matrix);
            matrix_mul_vec3(delta, delta, transform);
            delta[0] = 0.0f;
            if (delta[1] == 0.0f && delta[2] == 0.0f)
                delta[1] = 1.0f;
            vec_clamp_length(delta, speed);
            matrix_mul_vec3(delta, delta, g_camera_eye_state.matrix);
            cam_offset_direction((char *)delta);
            func_PAL_002884F0((char *)&g_modal_state.angle, 1);
            if (FastVecLength(delta) < speed - 0.01f) {
                /* The transition publishes its separate state word before capturing the return pose. */
                { extern int D_001B1710; D_001B1710 = 2; }
                qcopy(g_modal_state.returnPosition, g_camera_eye_state.position);
                if (D_001A7A44) {
                    FastVecScale(g_camera_eye_state.matrix + 4, g_camera_eye_state.matrix + 4, -1.0f);
                    mat_get_euler_angles(g_camera_eye_state.matrix, g_modal_state.returnAngles);
                    FastVecScale(g_camera_eye_state.matrix + 4, g_camera_eye_state.matrix + 4, -1.0f);
                } else {
                    mat_get_euler_angles(g_camera_eye_state.matrix, g_modal_state.returnAngles);
                }
                g_modal_state.phase = 4;
            }
            break;
        }
        case 4:
            D_001B170C = 3;
            math_step_value_toward_target(&g_modal_state.fraction, &g_modal_state.angle,
                    1.0f, 0.00080000004f, 0.00080000004f, 0.030000001f);
            lerp_vector(g_camera_eye_state.position, g_modal_state.returnPosition,
                    g_modal_state.cameraPosition, g_modal_state.fraction);
            mat_build_rotation_from_angles(delta, g_modal_state.returnAngles);
            mat_build_rotation_from_angles(target, g_modal_state.cameraAngles);
            vec_fast_normalize3(transform, delta, target, g_modal_state.fraction);
            quaternion_to_rotation_basis(transform, g_camera_eye_state.matrix);
            if (D_001A7A44)
                FastVecScale(g_camera_eye_state.matrix + 4, g_camera_eye_state.matrix + 4, -1.0f);
            if (g_modal_state.fraction >= 1.0f)
                request_end_slot(0, 0);
            break;
        }
        g_modal_state.cameraActive = 1;
        if ((g_pad_state.buttons & 0x500) && g_modal_state.phase == 2) {
            g_modal_state.fraction = 0.0f;
            g_modal_state.phase = 3;
            g_modal_state.angle = 0.0f;
        }
        if ((unsigned)(g_current_map_index - 22) < 2) {
            CameraObject *object = D_001B1B5C;
            if (object < D_001B1B60) {
                do {
                    if (object->kind == 0xD3D && object->update)
                        object->update(object);
                    ++object;
                } while (object < D_001B1B60);
            }
        }
        break;
    case 7:
        switch (g_modal_state.phase) {
        case 0:
            g_modal_state.cameraActive = 1;
            g_modal_state.phase = 1;
            if (D_0018C0D4 != 1)
                func_PAL_0026F620();
            D_001A8A48 = 0;
            D_001A8A40 = ref_00286738_00;
            hud_request_letterbox_bars();
            menu_set_state_word_three();
            break;
        case 1:
            if (D_0018C0D4 != 1) {
                func_PAL_0026F620();
                hud_set_slot_contents(0x23, 0, menu_init_panel_layout, weapon_wheel_update_select, weapon_wheel_draw, 0, 0);
            } else {
                hud_set_slot_contents(0x23, 0, weapon_wheel_init, UpdateRadialMenuSelection, DrawRadialSelectorPanel, 0, 0);
            }
            func_PAL_0029D7D0();
            func_PAL_0029C0B8(300);
            level_forward_value(150);
            hud_request_letterbox_bars();
            {
                int remaining = D_001A8A40;
                if (remaining > 0) {
                    D_001A8A40 = remaining - 1;
                    remaining = D_001A8A40;
                }
                D_001A8A40 = remaining;
            }
            --D_001A8A60;
            if (D_001A8A60 < 0)
                D_001A8A60 = 0;
            if (!D_001A8A60)
                ++g_modal_state.phase;
            break;
        case 2:
            if (D_0018C0D4 != 1) {
                func_PAL_0026F620();
                hud_set_slot_contents(0x23, 0, menu_init_panel_layout, weapon_wheel_update_select, weapon_wheel_draw, 0, 0);
            } else {
                hud_set_slot_contents(0x23, 0, weapon_wheel_init, UpdateRadialMenuSelection, DrawRadialSelectorPanel, 0, 0);
            }
            func_PAL_0029D7D0();
            func_PAL_0029C0B8(300);
            level_forward_value(150);
            hud_request_letterbox_bars();
            {
                int remaining = D_001A8A40;
                if (remaining > 0) {
                    D_001A8A40 = remaining - 1;
                    remaining = D_001A8A40;
                }
                D_001A8A40 = remaining;
            }
            if (D_001A8A40 <= 0) {
                D_001A8A40 = 0;
                ++g_modal_state.phase;
            }
            break;
        case 3:
            if (D_0018C0D4 != 1)
                func_PAL_0026F620();
            hud_clear_flag_b();
            hud_clear_flag_a();
            { request_end_slot(0, 0); break; }
        }
        break;
    case 8:
        phaseDialog = &g_modal_state;
        if (phaseDialog->phase != 2) {
            if (phaseDialog->phase >= 3)
                break;
            if (phaseDialog->phase < 0)
                break;
            ++phaseDialog->phase;
            break;
        }
        request_begin_slot(3, 2, phaseDialog->selection, 0, 0);
        func_PAL_002B5570(3);
        goto advanceModalPhase;
    case 9:
        phaseDialog = &g_modal_state;
        switch (phaseDialog->phase) {
        case 1:
            if (g_pad_state.pressed & phaseDialog->acceptMask) {
                phaseDialog->result = 2;
                request_end_slot(0, 0);
            } else if (g_pad_state.held & phaseDialog->cancelMask) {
                phaseDialog->result = 1;
                request_end_slot(0, 0);
            }
            break;
        case 0:
            goto initializeDialog;
        }
        break;
    case 10:
        phaseDialog = &g_modal_state;
        switch (phaseDialog->phase) {
        case 0:
initializeDialog:
            menu_clear_counter();
advanceModalPhase:
            ++phaseDialog->phase;
            break;
        case 1:
            if (g_pad_state.pressed & phaseDialog->acceptMask) {
                phaseDialog->result = 2;
                snd_play_from_global_bank(0x12, 0, 0);
                request_end_slot(0, 0);
            }
            break;
        default:
            break;
        }
        break;
    case 11:
        switch (g_modal_state.phase) {
        case 0:
            menu_clear_counter();
            ++g_modal_state.phase;
            if (g_widescreen_flag) {
                g_widescreen_flag = !g_widescreen_flag;
                gfx_apply_screen_aspect_mode();
                { request_end_slot(0, 0); break; }
            }
            break;
        case 1:
            if (g_pad_state.pressed & 0x40) {
                g_modal_state.result = 2;
                ++g_modal_state.phase;
            } else if (g_pad_state.held & 0x10) {
                g_modal_state.result = 1;
                { request_end_slot(0, 0); break; }
            }
            break;
        case 2:
            g_modal_state.elapsed = 750;
            g_modal_state.inputDelay = 0;
            ++g_modal_state.phase;
            g_modal_state.result = 0;
            g_widescreen_flag = !g_widescreen_flag;
            gfx_apply_screen_aspect_mode();
            break;
        case 3:
            if (g_pad_state.pressed & 0x40)
                g_modal_state.result = 2;
            else if (g_pad_state.pressed & 0x10)
                g_modal_state.result = 1;
            --g_modal_state.elapsed;
            if (g_modal_state.elapsed <= 0)
                goto advanceConfirmation;
            if (!g_modal_state.result)
                break;
            goto advanceConfirmation;
        case 4:
            if (g_modal_state.result < 0)
                goto advanceConfirmation;
            if (g_modal_state.result < 2) {
                g_widescreen_flag = !g_widescreen_flag;
                gfx_apply_screen_aspect_mode();
            }
advanceConfirmation:
            ++g_modal_state.phase;
            break;
        case 5:
            request_end_slot(0, 0);
            break;
        }
        break;
    }

}
