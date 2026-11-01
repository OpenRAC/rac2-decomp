#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 quad; float f[4]; } TriggerVector;
extern u8 D_00188660[];
extern void func_002A7750(u8 *, u8, s32);
extern s32 func_002E5CF8(s32, s32, char *);
extern float func_00283B98(float, float);
extern void *func_002A9640(void *, u32, s32);
extern void func_002E59F8(s32);
extern s32 func_002A8508(s32, s32);
extern void func_PAL_L00_003281C0(void *, s32, float);
extern void func_00283098(void *, void *, void *);
extern void func_PAL_002B15D8(char *, s32, void *, u8, float, float, float, float);
extern void func_0029F338(void *);

/* Keep the trigger slot alive until touched, then release it and emit the final burst. */
void func_PAL_L06_0045C028(u8 *object)
{
    TriggerVector offset;
    u8 *state = *(u8 **)(object + 0x68);
    u8 *record;
    s32 slot;

    switch (object[0x20]) {
    case 0:
        func_002A7750(object, 1, -1);
        break;
    case 1:
        {
            u8 *active = D_00188660 + *(s32 *)(state + 0xC) * 0x70;
            if (*(u8 **)(active + 0x88) != object || !active[0x74])
                *(s32 *)(state + 0xC) = func_002E5CF8(1, 4, (char *)object);
        }
        *(float *)(object + 0xF8) = func_00283B98(*(float *)(object + 0xF8), *(float *)(state + 4) * 0.0003490659f);
        if (func_002A9640(object, 0x4010000, 0) && *(s32 *)state == 0) {
            func_002E5CF8(0, 0, (char *)object);
            func_002A7750(object, 2, -1);
            slot = *(s32 *)(state + 0xC);
            if (slot != -1) {
                record = D_00188660 + slot * 0x70;
                if (*(u8 **)(record + 0x88) == object && record[0x74])
                    func_002E59F8(slot);
            }
            *(s32 *)(state + 0xC) = -1;
        }
        object[0xA8] = 0xFF;
        break;
    case 2:
        if (func_002A8508(*(s32 *)(state + 8), -1) == 1)
            func_PAL_L00_003281C0(object, 15, 0.0f);
        offset.quad = 0;
        offset.f[0] = -0.14000002f;
        func_00283098(&offset, &offset, object + 0xC0);
        func_PAL_002B15D8((char *)object, 31, &offset, 255, 3.0f, 6.0f, 3.0f, 6.0f);
        func_0029F338(object);
        break;
    }
}
