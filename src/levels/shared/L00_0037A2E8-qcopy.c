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
extern PreviewModel D_L00_0022F7C0;
extern unsigned char D_00139568[];
typedef struct { unsigned char pad[4]; unsigned char alternate; unsigned char tail[219]; } PreviewInfo;
extern PreviewInfo D_L00_00262570[];
extern PreviewPose D_L00_0028D900[];
extern unsigned char D_001A7BB0[] __attribute__((sda));
extern int func_L00_00305600(int, int);
extern void func_0029F0C8(unsigned char *, int);
extern void func_002A0468(void *, int, int, int, int);
extern void func_0029F390(unsigned char *);
extern void func_002A0F48(unsigned char *);

/* Once the selected preview resource is loaded: binds it to the preview object and sets its pose. */
void func_L00_0037A2E8(void) {
    char *model = (char *)&gPurchaseMenuModel;
    unsigned char *object;
    int selection;
    if (*(int *)(model + 0x50) == 0) {
        if (!TryStartTocEntryAction(gPurchaseMenuModel.mode0.rows[*(int *)(model + 0x70)].resource, *(int *)(model + 0x1C))) return;
        object = *(unsigned char **)(model + 0x2C);
        *(int *)(model + 0x8C) = 0;
        *(int *)(model + 0x88) = 1;
        InitMobyInstance(object, gPurchaseMenuModel.mode0.rows[*(int *)(model + 0x70)].resource);
        if (!*(void **)(object + 0x24)) {
            *(int *)(model + 0x8C) = 0;
            *(int *)(model + 0x88) = 0;
            return;
        }
        PackRenderCommandFields(object, 0x202020, 14, 14, 0);
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
        if (!((PreviewInfo *)((char *)gWeaponTable_L00 + gItemSlotToRecord[selection] * 224))->alternate) {
            *(float *)(model + 0x98) = D_L00_0028D900[selection].position.f[3];
            *(Quad *)(model + 0xC0) = D_L00_0028D900[selection].position.q;
            *(Quad *)(object + 0xF0) = D_L00_0028D900[selection].rotation.q;
        } else {
            *(float *)(model + 0x98) = D_L00_0028D900[selection].alternate_position.f[3];
            *(Quad *)(model + 0xC0) = D_L00_0028D900[selection].alternate_position.q;
            *(Quad *)(object + 0xF0) = D_L00_0028D900[selection].alternate_rotation.q;
        }

    } else {
        if (*(int *)(model + 0x50) != 1) return;
        if (!TryStartTocEntryAction(gPurchaseMenuModel.mode1.rows[*(int *)(model + 0x70)].resource, *(int *)(model + 0x1C))) return;
        object = *(unsigned char **)(model + 0x2C);
        *(int *)(model + 0x8C) = 0;
        *(int *)(model + 0x88) = 1;
        InitMobyInstance(object, gPurchaseMenuModel.mode1.rows[*(int *)(model + 0x70)].resource);
        if (!*(void **)(object + 0x24)) {
            *(int *)(model + 0x8C) = 0;
            *(int *)(model + 0x88) = 0;
            return;
        }
        PackRenderCommandFields(object, 0x202020, 14, 14, 0);
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
        selection = gPurchaseMenuModel.choices1.rows[*(int *)(model + 0x70)].resource;
        if (!((PreviewInfo *)((char *)gWeaponTable_L00 + gItemSlotToRecord[selection] * 224))->alternate) {
            *(float *)(model + 0x98) = D_L00_0028D900[selection].position.f[3];
            *(Quad *)(model + 0xC0) = D_L00_0028D900[selection].position.q;
            *(Quad *)(object + 0xF0) = D_L00_0028D900[selection].rotation.q;
        } else {
            *(float *)(model + 0x98) = D_L00_0028D900[selection].alternate_position.f[3];
            *(Quad *)(model + 0xC0) = D_L00_0028D900[selection].alternate_position.q;
            *(Quad *)(object + 0xF0) = D_L00_0028D900[selection].alternate_rotation.q;
        }

    }
    if (D_001A7BB0[1]) gPurchaseMenuModel.state.position.f[2] -= 0.55f;
    gPurchaseMenuModel.state.dirty = 1;
    func_002A0F48(object);
    if (gPurchaseMenuModel.state.state == 0 && gPurchaseMenuModel.state.loading == gPurchaseMenuModel.state.selected)
    gPurchaseMenuModel.state.timer = 0;
}
