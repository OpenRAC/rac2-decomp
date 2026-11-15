#include "common.h"

typedef unsigned int PreviewQuad __attribute__((mode(TI)));
typedef struct {
    int value, displayChoice, selectionMask, requiredBits, unused;
} PreviewChoice;
extern PreviewChoice D_0026CFD0[];
typedef struct {
    char pad0[0x140];
    float analogX, analogY;
    char pad148[0x7C];
    int flags;
} InputState;
typedef struct {
    char pad0[0x14];
    char *source;
    int value;
    char pad1c[0x118];
    int fallback;
    char pad138[0x94];
    char *entries;
    int count, timer;
    char pad1d8[8];
    float x, y, z;
} PreviewState;
typedef struct {
    char pad0[0x34];
    int choice;
    char pad38[4];
    int timer;
} PreviewDisplay;

extern InputState g_pad_state;
extern PreviewState g_pause_menu_state;
extern PreviewDisplay D_0025D478;
typedef struct { int selection; } PreviewSelection;
extern PreviewSelection D_001ABA74 __attribute__((sda));
extern unsigned int g_equipment_bits;
extern void snd_play_from_global_bank(int, int, int);
extern int math_ping_pong_blend_values(int, int, int, int, int);
extern float FastAddRotations(float, float);
extern void gfx_pack_render_command_fields(void *, int, int, int, int);
extern void func_002A0F48(void *);
#define F(p, o) (*(float *)((char *)(p) + (o)))

/* Lets the player move through the model preview list with left and right, turns the shown model toward a set angle (or by the stick) and highlights the matching part. */
int UpdateModelPreviewMenu(void)
{
    int result = 0, flags = g_pad_state.flags, oldSelection = D_001ABA74.selection;
    int i, color, type;
    float dx, dy;
    union { unsigned int q __attribute__((mode(TI))); float f[4]; } pos;
    char *previewObj;
    if (flags & 0x10) {
        int callbackValue = *(int *)(g_pause_menu_state.source + 0xE0);
        if (callbackValue) g_pause_menu_state.value = callbackValue;
        else if (!g_pause_menu_state.fallback) { callbackValue = -1; goto callback_done; }
        callbackValue = 0;
callback_done:
        return callbackValue;
    }
    if (flags & 0x900) { result = 1; goto done; }
    if (flags & 0x8000) {
        int selection;
        for (;;) {
            selection = --D_001ABA74.selection;
            if (selection < 0) goto previous_failed;
            if ((g_equipment_bits & D_0026CFD0[selection].selectionMask) == D_0026CFD0[selection].requiredBits) break;
        }
        snd_play_from_global_bank(3, 0, 0);
        goto previous_done;
previous_failed:
        snd_play_from_global_bank(5, 0, 0); D_001ABA74.selection = oldSelection;
previous_done:
        if (D_001ABA74.selection < 0) D_001ABA74.selection = 0;
    }
    if (g_pad_state.flags & 0x2000) {
        int selection;
        for (;;) {
            selection = ++D_001ABA74.selection;
            if (selection >= 13) goto next_failed;
            if ((g_equipment_bits & D_0026CFD0[selection].selectionMask) == D_0026CFD0[selection].requiredBits) break;
        }
        snd_play_from_global_bank(3, 0, 0);
        goto next_done;
next_failed:
        snd_play_from_global_bank(5, 0, 0); D_001ABA74.selection = oldSelection;
next_done:
        if (D_001ABA74.selection >= 13) D_001ABA74.selection = 12;
    }
    {
        int choice = D_0026CFD0[D_001ABA74.selection].selectionMask;
        if (choice == 0xc00 || choice == 0x200 || choice == 0x40) goto default_rotation;
        else if (choice == 0x30 || choice == 0x2000) {
            g_pause_menu_state.x = -0.01605300046503544f;
            g_pause_menu_state.y = -0.028157999739050865f;
            g_pause_menu_state.z = 0.07763200253248215f;
        }
        else if (choice == 0x1000 || choice == 0x180) {
            g_pause_menu_state.x = -0.5713149905204773f;
            g_pause_menu_state.y = -0.007104999851435423f;
            g_pause_menu_state.z = -0.6278929710388184f;
        }
        else if (choice == 0xc000) {
            g_pause_menu_state.x = -0.0807889997959137f;
            g_pause_menu_state.y = -0.547631025314331f;
            g_pause_menu_state.z = 0.4349989891052246f;
        }
        else {
default_rotation:
            g_pause_menu_state.x = 0.21184299886226654f;
            g_pause_menu_state.y = 0.33421000838279724f;
            g_pause_menu_state.z = -2.782352924346924f;
        }
    }
    if (oldSelection != D_001ABA74.selection) {
        g_pause_menu_state.timer = 0;
        math_ping_pong_blend_values(-1, 0xff606060, 30, 1, 1);
        D_0025D478.timer = -580;
    }
    dx = g_pad_state.analogX * 0.02f;
    dy = g_pad_state.analogY * 0.02f;
    pos.q = 0;
    D_0025D478.choice = D_0026CFD0[D_001ABA74.selection].displayChoice;
    pos.f[0] = 270.0f;
    pos.f[1] = 257.0f;
    pos.f[2] = 65.0f;
    color = math_ping_pong_blend_values(0xffffff, 0x606060, 30, 1, 0);
    for (i = 0; i < g_pause_menu_state.count; i++) {
        float step = 0.0057142856530845165f;
        previewObj = g_pause_menu_state.entries + i * 0x100;
        *(PreviewQuad *)(previewObj + 0x10) = pos.q;
        if (g_pause_menu_state.timer <= 0) {
            F(previewObj, 0xf0) = FastAddRotations(F(previewObj, 0xf0), (g_pause_menu_state.x - F(previewObj, 0xf0)) * step);
            F(previewObj, 0xf4) = FastAddRotations(F(previewObj, 0xf4), (g_pause_menu_state.y - F(previewObj, 0xf4)) * step);
            F(previewObj, 0xf8) = FastAddRotations(F(previewObj, 0xf8), (g_pause_menu_state.z - F(previewObj, 0xf8)) * step);
        } else {
            F(previewObj, 0xf8) = FastAddRotations(F(previewObj, 0xf8), dx);
            F(previewObj, 0xf4) = FastAddRotations(F(previewObj, 0xf4), dy);
        }
        type = ((unsigned char *)previewObj)[0xbc];
        F(previewObj, 0x2c) = F(*(char **)(previewObj + 0x24), 0x24);
        if ((type == 0 && D_0026CFD0[D_001ABA74.selection].selectionMask == 0x30) ||
            (type == 1 && D_0026CFD0[D_001ABA74.selection].selectionMask == 0x40) ||
            (type == 2 && D_0026CFD0[D_001ABA74.selection].selectionMask == 0x180) ||
            (type == 3 && D_0026CFD0[D_001ABA74.selection].selectionMask == 0x200) ||
            (type == 4 && D_0026CFD0[D_001ABA74.selection].selectionMask == 0xc00) ||
            (type == 5 && D_0026CFD0[D_001ABA74.selection].selectionMask == 0x1000) ||
            (type == 6 && D_0026CFD0[D_001ABA74.selection].selectionMask == 0x2000) ||
            (type == 7 && D_0026CFD0[D_001ABA74.selection].selectionMask == 0xc000))
            gfx_pack_render_command_fields(previewObj, color, 14, 14, 0);
        else gfx_pack_render_command_fields(previewObj, 0x202020, 14, 14, 0);
        func_002A0F48(previewObj);
    }
    if (__builtin_fabs((double)dx) > 9.999999747378752e-05 ||
        __builtin_fabs((double)dy) > 9.999999747378752e-05)
        g_pause_menu_state.timer = 180;
    if (g_pause_menu_state.timer > 0) --g_pause_menu_state.timer;
done:
    return result;
}
