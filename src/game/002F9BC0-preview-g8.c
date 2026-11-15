#include "common.h"

typedef struct { int id, kind, resource, value, extra, owned; } PreviewItem;
typedef struct { int id, resource, value; } PreviewArmor;
typedef struct { int mask, bits, value, unknown, text, price, extra; } PreviewEquipment;
typedef struct PreviewMoby PreviewMoby;
typedef struct {
    char pad[0x10]; unsigned char frames, unused11, unused12, triggers;
    char pad14[8]; unsigned int data[1];
} PreviewAnimation;
typedef struct { char pad[8]; unsigned char count; char gap[0x3F]; PreviewAnimation *anim[1]; } PreviewClass;
struct PreviewMoby {
    char pad00[0x20];
    unsigned char state, unk21, unk22, unk23;
    PreviewClass *pclass;
    int unk28;
    float scale;
    unsigned char opacity, render; unsigned short drawMask;
    unsigned short flags;
    char pad36[0xA];
    unsigned char frame, frame2, anim, anim2;
    char pad44[0x14];
    int animData, animData2;
    char pad60[2]; unsigned char unk62, unk63;
    char pad64[0x14];
    unsigned int color;
    short unk7c;
    char pad7e[0x1A];
    int unk98;
    char pad9c[0xE];
    short classId;
    char padac[0x44];
    int rotX, rotY;
    float rotZ;
    char padfc[4];
};
typedef struct {
    char pad00[0x1C]; int buffer;
    int animBuffers[2]; int unused28; PreviewMoby *objects;
    int unused30, objectCount;
    char pad38[0x14]; int equipment;
    int mode, selectedPart[2];
    char pad5c[0x14]; int previous;
    char pad74[0xC]; int selected, unused84, modelActive, resourceActive;
    int field90, unused94; float scale; int field9c;
    int fielda0, fielda4; float x, y, z;
    char padb4[0xC]; float position[4];
    char padd0[0x70];
    union { PreviewItem item[64]; PreviewArmor armor[128]; PreviewEquipment equipment[54]; int ammo[96][4]; } rows;
    int count, field744, field748, field74c, field750;
    char pad754[0xC];
} PreviewState;
typedef struct { int ids[5]; } PreviewClasses;
extern PreviewState g_vendor_menu_state;
extern PreviewClasses D_001AD500;
extern int D_001A7290[] MACRO_ADDR;
extern int D_001AD250[] SDATA(D_001AD250);
extern int D_001A8B00[] MACRO_ADDR;
extern const int g_equipment_bits[] MACRO_ADDR;
extern short D_001A8C20[] MACRO_ADDR, D_001A8C28[] MACRO_ADDR, D_001A8C30[] MACRO_ADDR, D_001A8C38[] MACRO_ADDR, D_001A8C40[] MACRO_ADDR, D_001A8C48[] MACRO_ADDR, D_001A8C50[] MACRO_ADDR, D_001A8C58[] MACRO_ADDR;
extern float D_001B1390[] MACRO_ADDR;
typedef struct { float m[16]; } PreviewTransform;
extern PreviewTransform D_001B2980[];
extern float D_001A7C94[] MACRO_ADDR;
extern char D_001AD1D0[] SDATA(D_001AD1D0);
extern unsigned char D_001A7BB1;
typedef struct { char pad[0x370]; float x, y; } PreviewCamera;
extern PreviewCamera g_active_camera;
extern int g_hero_moby_default[];
extern unsigned char g_item_slot_to_record[];
typedef struct { char pad[0x46]; short text; char pad48[0x98]; } PreviewInfo;
extern PreviewInfo g_weapon_table[];
extern void shop_clear_preview(void), shop_set_message_text(char *);
extern int GetLocalizedString(int);
extern void tex_load_level_pack(void *), LoadDiscTableTexture(int);
extern float mat_fast_helper_a(float, float), FastAddRotations(float, float), fast_subtract_rotations(float, float);
extern void moby_init_instance(void *, int), gfx_pack_render_command_fields(void *, int, int, int, int);
extern void func_002A0F48(void *), update_moby_animation_state(void *);
extern void mem_clear(void *, int, int), AttachManipulator(void *, unsigned int, void *);
extern void func_002A1130(void *, unsigned int, long long, unsigned int);
extern int help_copy_record_at_depth(void *, int, int);
extern short snd_pump_music_and_disc_read(int);
extern void load_start_disc_entry_by_id(int, int);

typedef char PreviewMobySize[(sizeof(PreviewMoby) == 0x100) ? 1 : -1];
typedef char PreviewStateSize[(sizeof(PreviewState) == 0x760) ? 1 : -1];

/* Sets up the 3D preview for the shop entry that is selected: armor, equipment pieces or an item
   model, or a picture and description for items and ammo. */
void PrepareVendorSelectionPreview(void)
{
    PreviewClasses classes;
    int parts[20] __attribute__((aligned(16)));
    PreviewInfo info;

    PreviewMoby *moby;
    PreviewState *state;
    int mode;
    float facing;
    if (g_vendor_menu_state.resourceActive) shop_clear_preview();
    mode = g_vendor_menu_state.mode;
    moby = g_vendor_menu_state.objects;
    g_vendor_menu_state.objectCount = 1;
    if (mode == 3) {
        g_vendor_menu_state.objectCount = 0;
        classes = D_001AD500;
        if (g_vendor_menu_state.rows.armor[g_vendor_menu_state.selected].value == 0) {
            shop_set_message_text(((char *)GetLocalizedString(0x3188)));
        } else {
            if (D_001A7290[0] != g_vendor_menu_state.rows.armor[g_vendor_menu_state.selected].value)
                tex_load_level_pack((void *)g_vendor_menu_state.rows.armor[g_vendor_menu_state.selected].value);
            shop_set_message_text(((char *)GetLocalizedString(D_001AD250[g_vendor_menu_state.rows.armor[g_vendor_menu_state.selected].value])));
        }
        facing = FastAddRotations(mat_fast_helper_a(g_active_camera.x, g_active_camera.y), 1.7453294f);
        while (classes.ids[g_vendor_menu_state.objectCount] >= 0) {
            moby = &g_vendor_menu_state.objects[g_vendor_menu_state.objectCount];
            moby_init_instance(moby, classes.ids[g_vendor_menu_state.objectCount]);
            gfx_pack_render_command_fields(moby, 0x202020, 14, 14, 0);
            moby->color = 0x80808080;
            moby->drawMask = 64;
            moby->render = 1;
            moby->flags = 0x2010;
            moby->opacity = 0;
            moby->unk23 = 0;
            moby->state = 0;
            moby->unk98 = 0;
            moby->rotX = 0; moby->rotY = 0; moby->rotZ = 0;
            moby->unk62 = 255;
            func_002A0F48(moby);
            moby->anim = 0; moby->anim2 = 0;
            update_moby_animation_state(moby);
            if (D_001A7290[0]) moby->rotZ = facing;
            if (D_001A7290[0] == 4 && moby->classId == 0x50A /* moby class 1290 */) moby->flags |= 1;
            if (D_001A7290[0] >= 3 && moby->classId == 0xA73 /* moby class 2675 */) moby->flags |= 1;
            g_vendor_menu_state.objectCount++;
        }
        mem_clear(D_001B1390, 0, 0x40);
        AttachManipulator(g_vendor_menu_state.objects, 24, D_001B1390);
        D_001B1390[10] = D_001A7C94[0];
        D_001B1390[9] = D_001B1390[8] = D_001A7C94[0] * 0.97f;
        if (D_001A7290[0] < 3) {
            int i;
            mem_clear(&D_001B2980[0], 0, 0x40);
            mem_clear(&D_001B2980[1], 0, 0x40);
            for (i = 0; i < 2; i++) {
                PreviewTransform *transform = &D_001B2980[i];
                AttachManipulator(g_vendor_menu_state.objects, i + 22, transform);
                transform->m[8] = 0.01f;
                transform->m[9] = 0.01f;
                transform->m[10] = 0.01f;
            }
        }
        {
            PreviewMoby *moby = g_vendor_menu_state.objects;
            PreviewClass *pc = moby->pclass;
            PreviewAnimation *anim = pc->anim[moby->anim];
            if (anim->data[0] & 0xF0000000) {
                func_002A1130((char *)&anim->data[anim->frames] + anim->triggers * 4,
                             anim->data[moby->frame], g_vendor_menu_state.animBuffers[0], pc->count);
                moby->animData = g_vendor_menu_state.animBuffers[0];
            }
            {
                PreviewClass *pc2 = moby->pclass;
                PreviewAnimation *anim2 = pc2->anim[moby->anim2];
                if (anim2->data[0] & 0xF0000000) {
                    func_002A1130((char *)&anim2->data[anim2->frames] + anim2->triggers * 4,
                                 anim2->data[moby->frame2], g_vendor_menu_state.animBuffers[1], pc2->count);
                    moby->animData2 = g_vendor_menu_state.animBuffers[1];
                }
            }
        }
        do {
            g_vendor_menu_state.position[0] = -9.0f; g_vendor_menu_state.position[1] = 4.5f; g_vendor_menu_state.position[2] = -1.0f;
            g_vendor_menu_state.scale = 3.5f; g_vendor_menu_state.modelActive = 1;
            g_vendor_menu_state.field9c = 0; g_vendor_menu_state.resourceActive = 0; g_vendor_menu_state.field90 = 0;
        } while (0);
    } else if (mode == 2) {
        int index = g_vendor_menu_state.selected;
        int kind;
        int value;
        int armor;
        g_vendor_menu_state.objectCount = 10;
        g_vendor_menu_state.equipment = (g_equipment_bits[0] & ~g_vendor_menu_state.rows.equipment[index].value) | g_vendor_menu_state.rows.equipment[index].unknown;
        parts[0] = D_001A8C20[g_vendor_menu_state.equipment & 3] << 16;
        if (g_vendor_menu_state.rows.equipment[index].value == 3) parts[0] |= 0x80000000;
        parts[1] = D_001A8C28[(g_vendor_menu_state.equipment & 12) >> 2] << 16;
        parts[2] = parts[1] | 0x8000;
        if (g_vendor_menu_state.rows.equipment[index].value == 12) { parts[1] |= 0x80000000; parts[2] |= 0x80000000; }
        parts[3] = D_001A8C50[(g_vendor_menu_state.equipment & 0xC00) >> 10] << 16;
        parts[4] = parts[3] | 0x8000;
        if (g_vendor_menu_state.rows.equipment[index].value == 0xC00) { parts[3] |= 0x80000000; parts[4] |= 0x80000000; }
        parts[5] = D_001A8C30[(g_vendor_menu_state.equipment & 0x30) >> 4] << 16;
        if (g_vendor_menu_state.rows.equipment[index].value == 0x30) parts[5] |= 0x80000000;
        parts[6] = D_001A8C38[(g_vendor_menu_state.equipment & 0x40) >> 6] << 16;
        parts[7] = parts[6] | 0x8000;
        if (g_vendor_menu_state.rows.equipment[index].value == 0x40) { parts[6] |= 0x80000000; parts[7] |= 0x80000000; }
        parts[8] = D_001A8C48[(g_vendor_menu_state.equipment & 0x200) >> 9] << 16;
        parts[9] = parts[8] | 0x8000;
        if (g_vendor_menu_state.rows.equipment[index].value == 0x200) { parts[8] |= 0x80000000; parts[9] |= 0x80000000; }
        kind = (g_vendor_menu_state.equipment & 0x180) >> 7;
        if (kind) {
            int n = g_vendor_menu_state.objectCount;
            parts[n] = parts[n + 1] = D_001A8C40[kind] << 16;
            parts[n + 1] |= 0x8000;
            if (g_vendor_menu_state.rows.equipment[index].value == 0x180) {
                parts[n] |= 0x80000000;
                parts[n + 1] |= 0x80000000;
            }
            g_vendor_menu_state.objectCount += 2;
        }
        parts[g_vendor_menu_state.objectCount] = D_001A8C58[(g_vendor_menu_state.equipment & 0xC000) >> 14] << 16;
        if (g_vendor_menu_state.rows.equipment[index].value == 0xC000) parts[g_vendor_menu_state.objectCount] |= 0x80000000;
        g_vendor_menu_state.objectCount++;
        if (g_vendor_menu_state.equipment & 0x1000) {
            parts[g_vendor_menu_state.objectCount] = 0x10E20000;
            if (g_vendor_menu_state.rows.equipment[index].value == 0x1000) parts[g_vendor_menu_state.objectCount] = 0x90E20000;
            g_vendor_menu_state.objectCount++;
        }
        if (g_vendor_menu_state.equipment & 0x2000) {
            parts[g_vendor_menu_state.objectCount] = 0x10E40000;
            if (g_vendor_menu_state.rows.equipment[index].value == 0x2000) parts[g_vendor_menu_state.objectCount] = 0x90E40000;
            g_vendor_menu_state.objectCount++;
        }
        parts[g_vendor_menu_state.objectCount++] = 0x10E30000;
        g_vendor_menu_state.fielda4 = 0;
        value = g_vendor_menu_state.rows.equipment[index].value;
        if (value == 0xC00 || value == 0x200 || value == 12 || value == 3 || value == 0x40) {
            g_vendor_menu_state.x = 0.346f; g_vendor_menu_state.y = 0.3227f; g_vendor_menu_state.z = -0.7141964f;
        } else if (value == 0x30 || value == 0x2000) {
            g_vendor_menu_state.x = 0.0225f; g_vendor_menu_state.y = 0.0239f; g_vendor_menu_state.z = fast_subtract_rotations(-3.0301f, 1.5707964f);
        } else if (value == 0x1000 || value == 0x180) {
            g_vendor_menu_state.x = -0.587f; g_vendor_menu_state.y = 0.165f; g_vendor_menu_state.z = 0.4842037f;
        } else if (value == 0x1F0000) {
            g_vendor_menu_state.x = (index & 1) ? 0.533f : 0.566f;
            g_vendor_menu_state.y = (index & 1) ? 0.3203f : 0.165f;
            g_vendor_menu_state.z = (index & 1) ? -0.90089637f : -0.13629639f;
        } else if (value == 0xC000) {
            g_vendor_menu_state.x = -0.5f; g_vendor_menu_state.y = -0.4f; g_vendor_menu_state.z = fast_subtract_rotations(-2.1f, 1.5707964f);
        } else {
            g_vendor_menu_state.x = 0; g_vendor_menu_state.y = 0; g_vendor_menu_state.z = -1.5707964f;
        }
        {
            int i;
            int n = 0;
            g_vendor_menu_state.selectedPart[1] = g_vendor_menu_state.selectedPart[0] = -1;
            for (i = 0; i < g_vendor_menu_state.objectCount; i++) {
                PreviewState *loopState = &g_vendor_menu_state;
                PreviewMoby *moby = &loopState->objects[i];
                float one = 1.0f;
                unsigned mask = 0x80000000;
                moby_init_instance(moby, (unsigned short)((unsigned)parts[i] >> 16) & 0x7FFF);
                gfx_pack_render_command_fields(moby, 0x202020, 14, 14, 0);
                if ((unsigned)parts[i] & mask) loopState->selectedPart[n++] = i;
                moby->drawMask = 0x100;
                moby->render = 1;
                moby->color = 0x80808080;
                moby->opacity = 0;
                moby->flags = (unsigned short)parts[i] | 0x2010;
                moby->unk23 = 255;
                moby->state = 0;
                moby->unk98 = 0;
                moby->scale = one;
                loopState->position[0] = -19.0f; loopState->position[1] = -2.0f; loopState->position[2] = 3.0f;
                loopState->scale = one;
                moby->rotX = 0; moby->rotY = 0; moby->rotZ = -1.5707964f;
                func_002A0F48(moby);
            }
        }
        state = &g_vendor_menu_state;
        state->modelActive = 1; state->field9c = 0; state->resourceActive = 0; state->field90 = 0;
        shop_set_message_text(((char *)GetLocalizedString(state->rows.equipment[state->selected].extra)));
        armor = ((unsigned)state->equipment >> 16) & 0x1F;
        if (g_hero_moby_default[12] != armor) LoadDiscTableTexture(armor);
    } else if (mode == 0) {
        g_vendor_menu_state.field750 = 0;
        if (g_vendor_menu_state.rows.item[g_vendor_menu_state.selected].kind == 1) {
            moby_init_instance(moby, MOBY_CLASS_AMMO);
            gfx_pack_render_command_fields(moby, 0x202020, 14, 14, 0);
            moby->drawMask = 64; moby->color = 0x80808080; moby->flags = 0x2010;
            moby->render = 1; moby->opacity = 0; moby->unk23 = 0; moby->state = 0; moby->unk98 = 0; moby->unk7c = 1;
            g_vendor_menu_state.scale = 3.5f;
            qcopy(g_vendor_menu_state.position, D_001AD1D0);
            if (D_001A7BB1) g_vendor_menu_state.position[2] -= 0.55f;
            moby->rotX = 0; moby->rotY = 0; moby->rotZ = 0;
            g_vendor_menu_state.field9c = 0;
            func_002A0F48(moby);
            g_vendor_menu_state.modelActive = 1; g_vendor_menu_state.resourceActive = 0;
            g_vendor_menu_state.field90 = 0;
        } else {
            if (g_vendor_menu_state.rows.item[g_vendor_menu_state.selected].owned) {
                int special = 0;
                switch (g_vendor_menu_state.rows.item[g_vendor_menu_state.selected].id) {
                case 12: case 14: case 17: case 18: case 53: special = 1;
                }
                help_copy_record_at_depth(&info, g_vendor_menu_state.rows.item[g_vendor_menu_state.selected].id, special ? 1 : 2);
                shop_set_message_text(((char *)GetLocalizedString(info.text)));
            } else {
                shop_set_message_text(((char *)GetLocalizedString((g_item_slot_to_record[g_vendor_menu_state.rows.item[g_vendor_menu_state.selected].id] + g_weapon_table)->text)));
            }
            snd_pump_music_and_disc_read(1);
            state = &g_vendor_menu_state;
            load_start_disc_entry_by_id(state->rows.item[state->selected].resource, state->buffer);
            state->resourceActive = 1; state->previous = state->selected; state->modelActive = 0;
        }
    } else if (mode == 1) {
        if (g_vendor_menu_state.count) {
            shop_set_message_text(((char *)GetLocalizedString(D_001A8B00[g_vendor_menu_state.rows.ammo[g_vendor_menu_state.selected][0]])));
            snd_pump_music_and_disc_read(1);
            load_start_disc_entry_by_id(g_vendor_menu_state.rows.ammo[g_vendor_menu_state.selected][3], g_vendor_menu_state.buffer);
            g_vendor_menu_state.resourceActive = 1; g_vendor_menu_state.previous = g_vendor_menu_state.selected; g_vendor_menu_state.modelActive = 0;
        }
    } else {
        g_vendor_menu_state.resourceActive = 0; g_vendor_menu_state.modelActive = 0;
    }
}
