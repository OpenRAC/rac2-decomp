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
extern PreviewState D_0021F240;
extern PreviewClasses D_001AD500;
extern int D_001A7290[] MACRO_ADDR;
extern int D_001AD250[] SDATA(D_001AD250);
extern int D_001A8B00[] MACRO_ADDR;
extern const int D_001A7AF0[] MACRO_ADDR;
extern short D_001A8C20[] MACRO_ADDR, D_001A8C28[] MACRO_ADDR, D_001A8C30[] MACRO_ADDR, D_001A8C38[] MACRO_ADDR, D_001A8C40[] MACRO_ADDR, D_001A8C48[] MACRO_ADDR, D_001A8C50[] MACRO_ADDR, D_001A8C58[] MACRO_ADDR;
extern float D_001B1390[] MACRO_ADDR;
typedef struct { float m[16]; } PreviewTransform;
extern PreviewTransform D_001B2980[];
extern float D_001A7C94[] MACRO_ADDR;
extern char D_001AD1D0[] SDATA(D_001AD1D0);
extern unsigned char D_001A7BB1;
typedef struct { char pad[0x370]; float x, y; } PreviewCamera;
extern PreviewCamera D_001B5200;
extern int D_00152C00[];
extern unsigned char D_00139568[];
typedef struct { char pad[0x46]; short text; char pad48[0x98]; } PreviewInfo;
extern PreviewInfo D_00239BA0[];
extern void func_002FB170(void), func_002F88D8(char *);
extern int func_00288FB8(int);
extern void func_002923C0(void *), func_002926B8(int);
extern float func_00283248(float, float), func_00283B98(float, float), func_00283BE0(float, float);
extern void func_0029F0C8(void *, int), func_002A0468(void *, int, int, int, int);
extern void func_002A0F48(void *), func_0029F390(void *);
extern void func_00282A60(void *, int, int), func_0029F978(void *, unsigned int, void *);
extern void func_002A1130(void *, unsigned int, long long, unsigned int);
extern int func_00288870(void *, int, int);
extern short func_002B7CE0(int);
extern void func_00294BC8(int, int);

typedef char PreviewMobySize[(sizeof(PreviewMoby) == 0x100) ? 1 : -1];
typedef char PreviewStateSize[(sizeof(PreviewState) == 0x760) ? 1 : -1];

/* Sets up the 3D preview for the shop entry that is selected: armor, equipment pieces or an item
   model, or a picture and description for items and ammo. */
void func_002FB1A0(void)
{
    PreviewClasses classes;
    int parts[20] __attribute__((aligned(16)));
    PreviewInfo info;

    PreviewMoby *moby;
    PreviewState *state;
    int mode;
    float facing;
    if (gVendorMenuState.resourceActive) ClearShopPreview();
    mode = gVendorMenuState.mode;
    moby = gVendorMenuState.objects;
    gVendorMenuState.objectCount = 1;
    if (mode == 3) {
        gVendorMenuState.objectCount = 0;
        classes = D_001AD500;
        if (gVendorMenuState.rows.armor[gVendorMenuState.selected].value == 0) {
            SetShopMessageText(((char *)GetLocalizedString(0x3188)));
        } else {
            if (D_001A7290[0] != gVendorMenuState.rows.armor[gVendorMenuState.selected].value)
                LoadLevelTexturePack((void *)gVendorMenuState.rows.armor[gVendorMenuState.selected].value);
            SetShopMessageText(((char *)GetLocalizedString(D_001AD250[gVendorMenuState.rows.armor[gVendorMenuState.selected].value])));
        }
        facing = FastAddRotations(FastMatrixHelperA(gActiveCamera.x, gActiveCamera.y), 1.7453294f);
        while (classes.ids[gVendorMenuState.objectCount] >= 0) {
            moby = &gVendorMenuState.objects[gVendorMenuState.objectCount];
            InitMobyInstance(moby, classes.ids[gVendorMenuState.objectCount]);
            PackRenderCommandFields(moby, 0x202020, 14, 14, 0);
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
            gVendorMenuState.objectCount++;
        }
        ClearMemory(D_001B1390, 0, 0x40);
        AttachManipulator(gVendorMenuState.objects, 24, D_001B1390);
        D_001B1390[10] = D_001A7C94[0];
        D_001B1390[9] = D_001B1390[8] = D_001A7C94[0] * 0.97f;
        if (D_001A7290[0] < 3) {
            int i;
            ClearMemory(&D_001B2980[0], 0, 0x40);
            ClearMemory(&D_001B2980[1], 0, 0x40);
            for (i = 0; i < 2; i++) {
                PreviewTransform *transform = &D_001B2980[i];
                AttachManipulator(gVendorMenuState.objects, i + 22, transform);
                transform->m[8] = 0.01f;
                transform->m[9] = 0.01f;
                transform->m[10] = 0.01f;
            }
        }
        {
            PreviewMoby *moby = gVendorMenuState.objects;
            PreviewClass *pc = moby->pclass;
            PreviewAnimation *anim = pc->anim[moby->anim];
            if (anim->data[0] & 0xF0000000) {
                func_002A1130((char *)&anim->data[anim->frames] + anim->triggers * 4,
                             anim->data[moby->frame], gVendorMenuState.animBuffers[0], pc->count);
                moby->animData = gVendorMenuState.animBuffers[0];
            }
            {
                PreviewClass *pc2 = moby->pclass;
                PreviewAnimation *anim2 = pc2->anim[moby->anim2];
                if (anim2->data[0] & 0xF0000000) {
                    func_002A1130((char *)&anim2->data[anim2->frames] + anim2->triggers * 4,
                                 anim2->data[moby->frame2], gVendorMenuState.animBuffers[1], pc2->count);
                    moby->animData2 = gVendorMenuState.animBuffers[1];
                }
            }
        }
        do {
            gVendorMenuState.position[0] = -9.0f; gVendorMenuState.position[1] = 4.5f; gVendorMenuState.position[2] = -1.0f;
            gVendorMenuState.scale = 3.5f; gVendorMenuState.modelActive = 1;
            gVendorMenuState.field9c = 0; gVendorMenuState.resourceActive = 0; gVendorMenuState.field90 = 0;
        } while (0);
    } else if (mode == 2) {
        int index = gVendorMenuState.selected;
        int kind;
        int value;
        int armor;
        gVendorMenuState.objectCount = 10;
        gVendorMenuState.equipment = (gEquipmentBits[0] & ~gVendorMenuState.rows.equipment[index].value) | gVendorMenuState.rows.equipment[index].unknown;
        parts[0] = D_001A8C20[gVendorMenuState.equipment & 3] << 16;
        if (gVendorMenuState.rows.equipment[index].value == 3) parts[0] |= 0x80000000;
        parts[1] = D_001A8C28[(gVendorMenuState.equipment & 12) >> 2] << 16;
        parts[2] = parts[1] | 0x8000;
        if (gVendorMenuState.rows.equipment[index].value == 12) { parts[1] |= 0x80000000; parts[2] |= 0x80000000; }
        parts[3] = D_001A8C50[(gVendorMenuState.equipment & 0xC00) >> 10] << 16;
        parts[4] = parts[3] | 0x8000;
        if (gVendorMenuState.rows.equipment[index].value == 0xC00) { parts[3] |= 0x80000000; parts[4] |= 0x80000000; }
        parts[5] = D_001A8C30[(gVendorMenuState.equipment & 0x30) >> 4] << 16;
        if (gVendorMenuState.rows.equipment[index].value == 0x30) parts[5] |= 0x80000000;
        parts[6] = D_001A8C38[(gVendorMenuState.equipment & 0x40) >> 6] << 16;
        parts[7] = parts[6] | 0x8000;
        if (gVendorMenuState.rows.equipment[index].value == 0x40) { parts[6] |= 0x80000000; parts[7] |= 0x80000000; }
        parts[8] = D_001A8C48[(gVendorMenuState.equipment & 0x200) >> 9] << 16;
        parts[9] = parts[8] | 0x8000;
        if (gVendorMenuState.rows.equipment[index].value == 0x200) { parts[8] |= 0x80000000; parts[9] |= 0x80000000; }
        kind = (gVendorMenuState.equipment & 0x180) >> 7;
        if (kind) {
            int n = gVendorMenuState.objectCount;
            parts[n] = parts[n + 1] = D_001A8C40[kind] << 16;
            parts[n + 1] |= 0x8000;
            if (gVendorMenuState.rows.equipment[index].value == 0x180) {
                parts[n] |= 0x80000000;
                parts[n + 1] |= 0x80000000;
            }
            gVendorMenuState.objectCount += 2;
        }
        parts[gVendorMenuState.objectCount] = D_001A8C58[(gVendorMenuState.equipment & 0xC000) >> 14] << 16;
        if (gVendorMenuState.rows.equipment[index].value == 0xC000) parts[gVendorMenuState.objectCount] |= 0x80000000;
        gVendorMenuState.objectCount++;
        if (gVendorMenuState.equipment & 0x1000) {
            parts[gVendorMenuState.objectCount] = 0x10E20000;
            if (gVendorMenuState.rows.equipment[index].value == 0x1000) parts[gVendorMenuState.objectCount] = 0x90E20000;
            gVendorMenuState.objectCount++;
        }
        if (gVendorMenuState.equipment & 0x2000) {
            parts[gVendorMenuState.objectCount] = 0x10E40000;
            if (gVendorMenuState.rows.equipment[index].value == 0x2000) parts[gVendorMenuState.objectCount] = 0x90E40000;
            gVendorMenuState.objectCount++;
        }
        parts[gVendorMenuState.objectCount++] = 0x10E30000;
        gVendorMenuState.fielda4 = 0;
        value = gVendorMenuState.rows.equipment[index].value;
        if (value == 0xC00 || value == 0x200 || value == 12 || value == 3 || value == 0x40) {
            gVendorMenuState.x = 0.346f; gVendorMenuState.y = 0.3227f; gVendorMenuState.z = -0.7141964f;
        } else if (value == 0x30 || value == 0x2000) {
            gVendorMenuState.x = 0.0225f; gVendorMenuState.y = 0.0239f; gVendorMenuState.z = fast_subtract_rotations(-3.0301f, 1.5707964f);
        } else if (value == 0x1000 || value == 0x180) {
            gVendorMenuState.x = -0.587f; gVendorMenuState.y = 0.165f; gVendorMenuState.z = 0.4842037f;
        } else if (value == 0x1F0000) {
            gVendorMenuState.x = (index & 1) ? 0.533f : 0.566f;
            gVendorMenuState.y = (index & 1) ? 0.3203f : 0.165f;
            gVendorMenuState.z = (index & 1) ? -0.90089637f : -0.13629639f;
        } else if (value == 0xC000) {
            gVendorMenuState.x = -0.5f; gVendorMenuState.y = -0.4f; gVendorMenuState.z = fast_subtract_rotations(-2.1f, 1.5707964f);
        } else {
            gVendorMenuState.x = 0; gVendorMenuState.y = 0; gVendorMenuState.z = -1.5707964f;
        }
        {
            int i;
            int n = 0;
            gVendorMenuState.selectedPart[1] = gVendorMenuState.selectedPart[0] = -1;
            for (i = 0; i < gVendorMenuState.objectCount; i++) {
                PreviewState *loopState = &gVendorMenuState;
                PreviewMoby *moby = &loopState->objects[i];
                float one = 1.0f;
                unsigned mask = 0x80000000;
                InitMobyInstance(moby, (unsigned short)((unsigned)parts[i] >> 16) & 0x7FFF);
                PackRenderCommandFields(moby, 0x202020, 14, 14, 0);
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
        state = &gVendorMenuState;
        state->modelActive = 1; state->field9c = 0; state->resourceActive = 0; state->field90 = 0;
        SetShopMessageText(((char *)GetLocalizedString(state->rows.equipment[state->selected].extra)));
        armor = ((unsigned)state->equipment >> 16) & 0x1F;
        if (gHeroMoby_00152C00[12] != armor) LoadDiscTableTexture(armor);
    } else if (mode == 0) {
        gVendorMenuState.field750 = 0;
        if (gVendorMenuState.rows.item[gVendorMenuState.selected].kind == 1) {
            InitMobyInstance(moby, 0xCDB /* Ammo */);
            PackRenderCommandFields(moby, 0x202020, 14, 14, 0);
            moby->drawMask = 64; moby->color = 0x80808080; moby->flags = 0x2010;
            moby->render = 1; moby->opacity = 0; moby->unk23 = 0; moby->state = 0; moby->unk98 = 0; moby->unk7c = 1;
            gVendorMenuState.scale = 3.5f;
            qcopy(gVendorMenuState.position, D_001AD1D0);
            if (D_001A7BB1) gVendorMenuState.position[2] -= 0.55f;
            moby->rotX = 0; moby->rotY = 0; moby->rotZ = 0;
            gVendorMenuState.field9c = 0;
            func_002A0F48(moby);
            gVendorMenuState.modelActive = 1; gVendorMenuState.resourceActive = 0;
            gVendorMenuState.field90 = 0;
        } else {
            if (gVendorMenuState.rows.item[gVendorMenuState.selected].owned) {
                int special = 0;
                switch (gVendorMenuState.rows.item[gVendorMenuState.selected].id) {
                case 12: case 14: case 17: case 18: case 53: special = 1;
                }
                CopyHelpRecordAtDepth(&info, gVendorMenuState.rows.item[gVendorMenuState.selected].id, special ? 1 : 2);
                SetShopMessageText(((char *)GetLocalizedString(info.text)));
            } else {
                SetShopMessageText(((char *)GetLocalizedString((gItemSlotToRecord[gVendorMenuState.rows.item[gVendorMenuState.selected].id] + gWeaponTable_00239BA0)->text)));
            }
            PumpMusicAndDiscRead(1);
            state = &gVendorMenuState;
            StartDiscEntryLoadById(state->rows.item[state->selected].resource, state->buffer);
            state->resourceActive = 1; state->previous = state->selected; state->modelActive = 0;
        }
    } else if (mode == 1) {
        if (gVendorMenuState.count) {
            SetShopMessageText(((char *)GetLocalizedString(D_001A8B00[gVendorMenuState.rows.ammo[gVendorMenuState.selected][0]])));
            PumpMusicAndDiscRead(1);
            StartDiscEntryLoadById(gVendorMenuState.rows.ammo[gVendorMenuState.selected][3], gVendorMenuState.buffer);
            gVendorMenuState.resourceActive = 1; gVendorMenuState.previous = gVendorMenuState.selected; gVendorMenuState.modelActive = 0;
        }
    } else {
        gVendorMenuState.resourceActive = 0; gVendorMenuState.modelActive = 0;
    }
}
