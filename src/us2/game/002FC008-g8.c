/* func_US2_002FC008, the USA v2.00 copy of func_002FB1A0 (src/game/002F9BC0-preview-g8.c): the same C,
 * where the empty-armor text 0x3188 becomes 0x301E, func_002923C0 becomes func_US2_00292C70, and the
 * equipment part loop tests each part's top bit directly and takes position x and z from D_001A7BB1
 * (-22 or -19, 2.25 or 3). */
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
extern void func_US2_00292C70(void *), func_002926B8(int);
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

void func_US2_002FC008(void)
{
    PreviewClasses classes;
    int parts[20] __attribute__((aligned(16)));
    PreviewInfo info;

    PreviewMoby *moby;
    PreviewState *state;
    int mode;
    float facing;
    if (D_0021F240.resourceActive) func_002FB170();
    mode = D_0021F240.mode;
    moby = D_0021F240.objects;
    D_0021F240.objectCount = 1;
    if (mode == 3) {
        D_0021F240.objectCount = 0;
        classes = D_001AD500;
        if (D_0021F240.rows.armor[D_0021F240.selected].value == 0) {
            func_002F88D8(((char *)func_00288FB8(0x301E)));
        } else {
            if (D_001A7290[0] != D_0021F240.rows.armor[D_0021F240.selected].value)
                func_US2_00292C70((void *)D_0021F240.rows.armor[D_0021F240.selected].value);
            func_002F88D8(((char *)func_00288FB8(D_001AD250[D_0021F240.rows.armor[D_0021F240.selected].value])));
        }
        facing = func_00283B98(func_00283248(D_001B5200.x, D_001B5200.y), 1.7453294f);
        while (classes.ids[D_0021F240.objectCount] >= 0) {
            moby = &D_0021F240.objects[D_0021F240.objectCount];
            func_0029F0C8(moby, classes.ids[D_0021F240.objectCount]);
            func_002A0468(moby, 0x202020, 14, 14, 0);
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
            func_0029F390(moby);
            if (D_001A7290[0]) moby->rotZ = facing;
            if (D_001A7290[0] == 4 && moby->classId == 0x50A) moby->flags |= 1;
            if (D_001A7290[0] >= 3 && moby->classId == 0xA73) moby->flags |= 1;
            D_0021F240.objectCount++;
        }
        func_00282A60(D_001B1390, 0, 0x40);
        func_0029F978(D_0021F240.objects, 24, D_001B1390);
        D_001B1390[10] = D_001A7C94[0];
        D_001B1390[9] = D_001B1390[8] = D_001A7C94[0] * 0.97f;
        if (D_001A7290[0] < 3) {
            int i;
            func_00282A60(&D_001B2980[0], 0, 0x40);
            func_00282A60(&D_001B2980[1], 0, 0x40);
            for (i = 0; i < 2; i++) {
                PreviewTransform *transform = &D_001B2980[i];
                func_0029F978(D_0021F240.objects, i + 22, transform);
                transform->m[8] = 0.01f;
                transform->m[9] = 0.01f;
                transform->m[10] = 0.01f;
            }
        }
        {
            PreviewMoby *moby = D_0021F240.objects;
            PreviewClass *pc = moby->pclass;
            PreviewAnimation *anim = pc->anim[moby->anim];
            if (anim->data[0] & 0xF0000000) {
                func_002A1130((char *)&anim->data[anim->frames] + anim->triggers * 4,
                             anim->data[moby->frame], D_0021F240.animBuffers[0], pc->count);
                moby->animData = D_0021F240.animBuffers[0];
            }
            {
                PreviewClass *pc2 = moby->pclass;
                PreviewAnimation *anim2 = pc2->anim[moby->anim2];
                if (anim2->data[0] & 0xF0000000) {
                    func_002A1130((char *)&anim2->data[anim2->frames] + anim2->triggers * 4,
                                 anim2->data[moby->frame2], D_0021F240.animBuffers[1], pc2->count);
                    moby->animData2 = D_0021F240.animBuffers[1];
                }
            }
        }
        do {
            D_0021F240.position[0] = -9.0f; D_0021F240.position[1] = 4.5f; D_0021F240.position[2] = -1.0f;
            D_0021F240.scale = 3.5f; D_0021F240.modelActive = 1;
            D_0021F240.field9c = 0; D_0021F240.resourceActive = 0; D_0021F240.field90 = 0;
        } while (0);
    } else if (mode == 2) {
        int index = D_0021F240.selected;
        int kind;
        int value;
        int armor;
        D_0021F240.objectCount = 10;
        D_0021F240.equipment = (D_001A7AF0[0] & ~D_0021F240.rows.equipment[index].value) | D_0021F240.rows.equipment[index].unknown;
        parts[0] = D_001A8C20[D_0021F240.equipment & 3] << 16;
        if (D_0021F240.rows.equipment[index].value == 3) parts[0] |= 0x80000000;
        parts[1] = D_001A8C28[(D_0021F240.equipment & 12) >> 2] << 16;
        parts[2] = parts[1] | 0x8000;
        if (D_0021F240.rows.equipment[index].value == 12) { parts[1] |= 0x80000000; parts[2] |= 0x80000000; }
        parts[3] = D_001A8C50[(D_0021F240.equipment & 0xC00) >> 10] << 16;
        parts[4] = parts[3] | 0x8000;
        if (D_0021F240.rows.equipment[index].value == 0xC00) { parts[3] |= 0x80000000; parts[4] |= 0x80000000; }
        parts[5] = D_001A8C30[(D_0021F240.equipment & 0x30) >> 4] << 16;
        if (D_0021F240.rows.equipment[index].value == 0x30) parts[5] |= 0x80000000;
        parts[6] = D_001A8C38[(D_0021F240.equipment & 0x40) >> 6] << 16;
        parts[7] = parts[6] | 0x8000;
        if (D_0021F240.rows.equipment[index].value == 0x40) { parts[6] |= 0x80000000; parts[7] |= 0x80000000; }
        parts[8] = D_001A8C48[(D_0021F240.equipment & 0x200) >> 9] << 16;
        parts[9] = parts[8] | 0x8000;
        if (D_0021F240.rows.equipment[index].value == 0x200) { parts[8] |= 0x80000000; parts[9] |= 0x80000000; }
        kind = (D_0021F240.equipment & 0x180) >> 7;
        if (kind) {
            int n = D_0021F240.objectCount;
            parts[n] = parts[n + 1] = D_001A8C40[kind] << 16;
            parts[n + 1] |= 0x8000;
            if (D_0021F240.rows.equipment[index].value == 0x180) {
                parts[n] |= 0x80000000;
                parts[n + 1] |= 0x80000000;
            }
            D_0021F240.objectCount += 2;
        }
        parts[D_0021F240.objectCount] = D_001A8C58[(D_0021F240.equipment & 0xC000) >> 14] << 16;
        if (D_0021F240.rows.equipment[index].value == 0xC000) parts[D_0021F240.objectCount] |= 0x80000000;
        D_0021F240.objectCount++;
        if (D_0021F240.equipment & 0x1000) {
            parts[D_0021F240.objectCount] = 0x10E20000;
            if (D_0021F240.rows.equipment[index].value == 0x1000) parts[D_0021F240.objectCount] = 0x90E20000;
            D_0021F240.objectCount++;
        }
        if (D_0021F240.equipment & 0x2000) {
            parts[D_0021F240.objectCount] = 0x10E40000;
            if (D_0021F240.rows.equipment[index].value == 0x2000) parts[D_0021F240.objectCount] = 0x90E40000;
            D_0021F240.objectCount++;
        }
        parts[D_0021F240.objectCount++] = 0x10E30000;
        D_0021F240.fielda4 = 0;
        value = D_0021F240.rows.equipment[index].value;
        if (value == 0xC00 || value == 0x200 || value == 12 || value == 3 || value == 0x40) {
            D_0021F240.x = 0.346f; D_0021F240.y = 0.3227f; D_0021F240.z = -0.7141964f;
        } else if (value == 0x30 || value == 0x2000) {
            D_0021F240.x = 0.0225f; D_0021F240.y = 0.0239f; D_0021F240.z = func_00283BE0(-3.0301f, 1.5707964f);
        } else if (value == 0x1000 || value == 0x180) {
            D_0021F240.x = -0.587f; D_0021F240.y = 0.165f; D_0021F240.z = 0.4842037f;
        } else if (value == 0x1F0000) {
            D_0021F240.x = (index & 1) ? 0.533f : 0.566f;
            D_0021F240.y = (index & 1) ? 0.3203f : 0.165f;
            D_0021F240.z = (index & 1) ? -0.90089637f : -0.13629639f;
        } else if (value == 0xC000) {
            D_0021F240.x = -0.5f; D_0021F240.y = -0.4f; D_0021F240.z = func_00283BE0(-2.1f, 1.5707964f);
        } else {
            D_0021F240.x = 0; D_0021F240.y = 0; D_0021F240.z = -1.5707964f;
        }
        {
            int i;
            int n = 0;
            D_0021F240.selectedPart[1] = D_0021F240.selectedPart[0] = -1;
            for (i = 0; i < D_0021F240.objectCount; i++) {
                PreviewState *loopState = &D_0021F240;
                PreviewMoby *moby = &loopState->objects[i];
                float one = 1.0f;
                func_0029F0C8(moby, (unsigned short)((unsigned)parts[i] >> 16) & 0x7FFF);
                func_002A0468(moby, 0x202020, 14, 14, 0);
                if ((unsigned)parts[i] & 0x80000000) loopState->selectedPart[n++] = i;
                moby->drawMask = 0x100;
                moby->render = 1;
                moby->color = 0x80808080;
                moby->opacity = 0;
                moby->flags = (unsigned short)parts[i] | 0x2010;
                moby->unk23 = 255;
                moby->state = 0;
                moby->unk98 = 0;
                moby->scale = one;
                loopState->scale = one;
                if (D_001A7BB1) loopState->position[0] = -22.0f;
                else loopState->position[0] = -19.0f;
                D_0021F240.position[1] = -2.0f;
                if (D_001A7BB1) D_0021F240.position[2] = 2.25f;
                else D_0021F240.position[2] = 3.0f;
                moby->rotX = 0; moby->rotY = 0; moby->rotZ = -1.5707964f;
                func_002A0F48(moby);
            }
        }
        state = &D_0021F240;
        state->modelActive = 1; state->field9c = 0; state->resourceActive = 0; state->field90 = 0;
        func_002F88D8(((char *)func_00288FB8(state->rows.equipment[state->selected].extra)));
        armor = ((unsigned)state->equipment >> 16) & 0x1F;
        if (D_00152C00[12] != armor) func_002926B8(armor);
    } else if (mode == 0) {
        D_0021F240.field750 = 0;
        if (D_0021F240.rows.item[D_0021F240.selected].kind == 1) {
            func_0029F0C8(moby, 0xCDB);
            func_002A0468(moby, 0x202020, 14, 14, 0);
            moby->drawMask = 64; moby->color = 0x80808080; moby->flags = 0x2010;
            moby->render = 1; moby->opacity = 0; moby->unk23 = 0; moby->state = 0; moby->unk98 = 0; moby->unk7c = 1;
            D_0021F240.scale = 3.5f;
            qcopy(D_0021F240.position, D_001AD1D0);
            if (D_001A7BB1) D_0021F240.position[2] -= 0.55f;
            moby->rotX = 0; moby->rotY = 0; moby->rotZ = 0;
            D_0021F240.field9c = 0;
            func_002A0F48(moby);
            D_0021F240.modelActive = 1; D_0021F240.resourceActive = 0;
            D_0021F240.field90 = 0;
        } else {
            if (D_0021F240.rows.item[D_0021F240.selected].owned) {
                int special = 0;
                switch (D_0021F240.rows.item[D_0021F240.selected].id) {
                case 12: case 14: case 17: case 18: case 53: special = 1;
                }
                func_00288870(&info, D_0021F240.rows.item[D_0021F240.selected].id, special ? 1 : 2);
                func_002F88D8(((char *)func_00288FB8(info.text)));
            } else {
                func_002F88D8(((char *)func_00288FB8((D_00139568[D_0021F240.rows.item[D_0021F240.selected].id] + D_00239BA0)->text)));
            }
            func_002B7CE0(1);
            state = &D_0021F240;
            func_00294BC8(state->rows.item[state->selected].resource, state->buffer);
            state->resourceActive = 1; state->previous = state->selected; state->modelActive = 0;
        }
    } else if (mode == 1) {
        if (D_0021F240.count) {
            func_002F88D8(((char *)func_00288FB8(D_001A8B00[D_0021F240.rows.ammo[D_0021F240.selected][0]])));
            func_002B7CE0(1);
            func_00294BC8(D_0021F240.rows.ammo[D_0021F240.selected][3], D_0021F240.buffer);
            D_0021F240.resourceActive = 1; D_0021F240.previous = D_0021F240.selected; D_0021F240.modelActive = 0;
        }
    } else {
        D_0021F240.resourceActive = 0; D_0021F240.modelActive = 0;
    }
}
