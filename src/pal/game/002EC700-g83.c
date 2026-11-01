#include "include_asm.h"

#include "common.h"
typedef struct SceneObject {
    char pad0[0x24]; unsigned char *model; char pad28[0xA]; unsigned short flags32, flags34;
    char pad36[2]; unsigned long long color; char pad40[2]; unsigned char slot, slot2;
    char pad44[0x1E]; unsigned char alpha, mode; char pad64[4]; void *data;
    char pad6C[0x2C]; int field98; char pad9C[0xE]; short kind;
} SceneObject;
typedef struct {
    char pad[0x38]; int frame; char pad3C[4]; short field40; char pad42[2]; short count;
    char pad46[2]; short field48; char pad4A[2]; void *optional; char pad50[4]; SceneObject *special;
    char pad58[0x10]; void *tail; unsigned char *source; int destination;
    char pad74[0x118]; SceneObject *objects[17];
} SceneList;
extern SceneList D_001B8840;
typedef struct { char pad0[0x24]; int pending; char pad28[0x40]; int busy; char pad6C[6]; unsigned short state; } SceneContextEnd;
extern SceneContextEnd D_001A63A8_3;
typedef struct { char pad[0x12C0]; SceneObject *object; } SceneEndRoot;
extern SceneEndRoot D_00189E20_9;
typedef struct { char pad[0xB0]; float fade; } SceneFade;
extern SceneFade D_001B9040;
typedef struct { char pad[0xFC]; SceneObject *object; } SceneOwnerEnd;
extern SceneOwnerEnd D_001F2840;
typedef struct { int unk0; SceneObject *moby; void *data; } SceneTalkEnd;
extern SceneTalkEnd D_001B178C MACRO_ADDR;
extern int D_001B15A8 __attribute__((section(".sdata")));
extern int D_001B15AC __attribute__((section(".sdata")));
extern float D_001B15A0 __attribute__((sda));
extern void func_0027D330(int);
extern void func_PAL_002E5898(void);
extern int func_001261F0(int);
extern int func_00132028(void);
extern void func_0027AB40(void);
extern void func_0029F338(SceneObject *);

/* Scene teardown: puts the transition word back to 5 unless it is 6 or 7,
   calls func_0027D330(12) and waits until the transition is idle with
   nothing pending, then until func_00132028 returns 0; sets the fade to
   0.63, clears the control words, releases every scene object (dropping its
   model's use count and entry) and the object held at D_00189E20+0x12C0,
   and clears bit 0 of flags34 on the objects held at D_001B178C+4 and
   D_001F2840+0xFC. */
void func_PAL_002EC9C0(void)
{
    int i;
    SceneObject *obj;
    SceneContextEnd *context = &D_001A63A8_3;
    unsigned short state = context->state;
    if ((unsigned int)(state - 6) >= 2) context->state = 5;
    func_0027D330(12);
    while (D_001A63A8_3.busy || D_001A63A8_3.pending != -1) {
        func_PAL_002E5898(); func_001261F0(0);
    }
    while (func_00132028()) {}
    D_001B9040.fade = 0.63f;
    D_001B15A8 = 0;
    D_001B15AC = 0;
    D_001B15A0 = 0.0f;
    func_0027AB40();
    for (i = 0; i < D_001B8840.count; i++) {
        obj = D_001B8840.objects[i];
        if (obj) {
            obj->model[12]--;
            { unsigned char *model = obj->model;
            model += model[12] * 4;
            *(int *)(model + 0x48) = 0; }
            func_0029F338(obj);
        }
    }
    { SceneEndRoot *owner = &D_00189E20_9;
    if (owner->object) { func_0029F338(owner->object); owner->object = 0; } }
    if (D_001B178C.moby) D_001B178C.moby->flags34 &= ~1;
    obj = D_001F2840.object;
    if (obj) { obj->flags34 &= ~1; D_001F2840.object = 0; }
}
