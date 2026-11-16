#include "names.h"
/* Partial layouts measured from the resource and pose accesses. */
typedef struct { int resource; int pad[5]; } PreviewResource24;
typedef struct { int resource; int pad[3]; } PreviewResource16;
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
typedef struct { Vector rotation, position, alternate_rotation, alternate_position; } PreviewPose;
typedef union {
    struct { char prefix[0x148]; PreviewResource24 rows[0];
} mode0;
    struct { char prefix[0x14C]; PreviewResource16 rows[0];
} mode1;
    struct { char prefix[0x144]; PreviewResource16 rows[0];
} choices1;
    struct { char prefix[0x70]; int loading; char pad74[12]; int selected, state, active, pending, timer; int pad94; float zoom; int dirty; char pada0[0x20]; Vector position;
} state;
} PreviewModel;
extern PreviewModel g_purchase_menu_model;
extern unsigned char g_item_slot_to_record[];
typedef struct { unsigned char pad[4]; unsigned char alternate; unsigned char tail[219]; } PreviewInfo;
extern PreviewInfo g_weapon_l00_table[];
extern PreviewPose g_preview_pose_table[];
extern unsigned char g_language_settings[] __attribute__((sda));
extern int menu_try_start_toc_entry(int, int);
extern void moby_init_instance(unsigned char *, int);
extern void gfx_pack_render_command_fields(void *, int, int, int, int);
extern void update_moby_animation_state(unsigned char *);
extern void func_002A0F48(unsigned char *);

/* Once the selected preview resource is loaded: binds it to the preview object and sets its pose. */
void BindVendorPreviewModel(void) {
    char *model = (char *)&g_purchase_menu_model;
    unsigned char *object;
    int selection;
    if (*(int *)(model + 0x50) == 0) {
        if (!menu_try_start_toc_entry(g_purchase_menu_model.mode0.rows[*(int *)(model + 0x70)].resource, *(int *)(model + 0x1C))) return;
        object = *(unsigned char **)(model + 0x2C);
        *(int *)(model + 0x8C) = 0;
        *(int *)(model + 0x88) = 1;
        moby_init_instance(object, g_purchase_menu_model.mode0.rows[*(int *)(model + 0x70)].resource);
        if (!*(void **)(object + 0x24)) {
            *(int *)(model + 0x8C) = 0;
            *(int *)(model + 0x88) = 0;
            return;
        }
        gfx_pack_render_command_fields(object, 0x202020, 14, 14, 0);
        *(unsigned short *)(object + 0x32) = 64;
        *(unsigned short *)(object + 0x34) = 0x2010;
        object[0x31] = 1;
        object[0x30] = 0;
        object[0x23] = 0;
        object[0x20] = 0;
        if (*(unsigned char *)(*(char **)(object + 0x24) + 0xC) > 1) {
            object[0x42] = 1;
            object[0x43] = 1;
            update_moby_animation_state(object);
        }
        selection = *(int *)(model + 0x140 + *(int *)(model + 0x70) * 24);
        if (!((PreviewInfo *)((char *)g_weapon_l00_table + g_item_slot_to_record[selection] * 224))->alternate) {
            *(float *)(model + 0x98) = g_preview_pose_table[selection].position.f[3];
            *(Quad *)(model + 0xC0) = g_preview_pose_table[selection].position.q;
            *(Quad *)(object + 0xF0) = g_preview_pose_table[selection].rotation.q;
        } else {
            *(float *)(model + 0x98) = g_preview_pose_table[selection].alternate_position.f[3];
            *(Quad *)(model + 0xC0) = g_preview_pose_table[selection].alternate_position.q;
            *(Quad *)(object + 0xF0) = g_preview_pose_table[selection].alternate_rotation.q;
        }

    } else {
        if (*(int *)(model + 0x50) != 1) return;
        if (!menu_try_start_toc_entry(g_purchase_menu_model.mode1.rows[*(int *)(model + 0x70)].resource, *(int *)(model + 0x1C))) return;
        object = *(unsigned char **)(model + 0x2C);
        *(int *)(model + 0x8C) = 0;
        *(int *)(model + 0x88) = 1;
        moby_init_instance(object, g_purchase_menu_model.mode1.rows[*(int *)(model + 0x70)].resource);
        if (!*(void **)(object + 0x24)) {
            *(int *)(model + 0x8C) = 0;
            *(int *)(model + 0x88) = 0;
            return;
        }
        gfx_pack_render_command_fields(object, 0x202020, 14, 14, 0);
        *(unsigned short *)(object + 0x32) = 64;
        *(unsigned short *)(object + 0x34) = 0x2010;
        object[0x31] = 1;
        object[0x30] = 0;
        object[0x23] = 0;
        object[0x20] = 0;
        if (*(unsigned char *)(*(char **)(object + 0x24) + 0xC) > 1) {
            object[0x42] = 1;
            object[0x43] = 1;
            update_moby_animation_state(object);
        }
        selection = g_purchase_menu_model.choices1.rows[*(int *)(model + 0x70)].resource;
        if (!((PreviewInfo *)((char *)g_weapon_l00_table + g_item_slot_to_record[selection] * 224))->alternate) {
            *(float *)(model + 0x98) = g_preview_pose_table[selection].position.f[3];
            *(Quad *)(model + 0xC0) = g_preview_pose_table[selection].position.q;
            *(Quad *)(object + 0xF0) = g_preview_pose_table[selection].rotation.q;
        } else {
            *(float *)(model + 0x98) = g_preview_pose_table[selection].alternate_position.f[3];
            *(Quad *)(model + 0xC0) = g_preview_pose_table[selection].alternate_position.q;
            *(Quad *)(object + 0xF0) = g_preview_pose_table[selection].alternate_rotation.q;
        }

    }
    if (g_language_settings[1]) g_purchase_menu_model.state.position.f[2] -= 0.55f;
    g_purchase_menu_model.state.dirty = 1;
    func_002A0F48(object);
    if (g_purchase_menu_model.state.state == 0 && g_purchase_menu_model.state.loading == g_purchase_menu_model.state.selected)
    g_purchase_menu_model.state.timer = 0;
}
