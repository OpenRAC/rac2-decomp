#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern u8 D_00188660[];
extern u8 D_00189EA0[];
extern u8 D_0019B2E8[][16];
extern s32 D_001A79F0[] __attribute__((sda));
extern u8 *D_L11_001FF580[];
extern s32 func_002E5CF8(s32, s32, u8 *);
extern void func_002E59F8(s32);
extern s32 func_L00_00324120(u8 *);
extern u8 *func_PAL_L00_002D7850(s32);
extern void func_L00_002D7140(u8 *);
extern void func_00282F20(void *, void *, f32);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, const void *, const void *);
extern f32 func_00282E48(void *, void *);
extern f32 func_00282E80(void *, void *);
extern void func_002A8598(s32, s32);
extern s32 func_002ACBC8(void *, s32);
extern void func_002AD6F0(void *, void *, void *, void *);
extern void func_PAL_L01_00322798(u8 *, void *, s32);

/* Moves the entity along its path, managing its effect and sound during state changes. */
void func_PAL_L11_0041AB00(u8 *object) {
    f32 previous[4] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    f32 rotation[4] __attribute__((aligned(16)));
    f32 point[4] __attribute__((aligned(16)));
    f32 step[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(object + 0x68);
    u8 *position;
    s32 slot;
    *(TI128 *)(previous) = *(TI128 *)(object + 0x10);
    *(TI128 *)(rotation) = *(TI128 *)(object + 0xF0);
    if (object[0x95] == 0) {
        object[0x95] = 1;
        *(u16 *)(object + 0x34) |= 0x2000;
    }
    if (object[0xBC] == 0) *(s32 *)(object + 0x98) = 0;
    else *(s32 *)(object + 0x98) = *(s32 *)(*(u8 **)(object + 0x24) + 0x10);
    if (func_L00_00324120(object)) {
        if (object[0x20] == 0) {
            {
                u8 *record = (u8 *)D_00188660 + *(s32 *)(state + 0x70) * 0x70;
                if (*(u8 **)(record + 0x88) != object || record[0x74] == 0)
                    *(s32 *)(state + 0x70) = func_002E5CF8(0, 4, object);
            }
            *(u8 **)(state + 0x68) = func_PAL_L00_002D7850(5);
            *(f32 *)(*(u8 **)(state + 0x68)) = 10.0f;
            *(s16 *)(*(u8 **)(state + 0x68) + 0x1A) = 1;
            *(s32 *)(*(u8 **)(state + 0x68) + 0x3C) = 1;
            (*(u8 **)(state + 0x68))[0x18] = 1;
            {
                u8 *record = *(u8 **)(state + 0x68) + 0x20;
                *(TI128 *)(record) = *(TI128 *)(object + 0xC0);
                func_00282F20(record, record, -1.0f);
            }
            (*(u8 **)(state + 0x68))[0x1E] = 1;
            object[0x20] = 1;
            if (D_0019B2E8[D_001A79F0[0]][object[0xB0]] & 0x80) {
                u8 *path;
                func_L00_002D7140(*(u8 **)(state + 0x68));
                path = D_L11_001FF580[*(s32 *)(state + 0x60)];
                object[0x20] = 6;
                *(s32 *)(state + 0x64) = *(s32 *)path - 1;
            }
        }
    } else if (object[0x20] == 0) {
        slot = *(s32 *)(state + 0x70);
        if (slot != -1) {
            u8 *record = (u8 *)D_00188660 + slot * 0x70;
            if (*(u8 **)(record + 0x88) == object && record[0x74]) func_002E59F8(slot);
        }
        *(s32 *)(state + 0x70) = -1;
    }
    if (object[0x20] == 1) {
        u8 *path;
        path = D_L11_001FF580[*(s32 *)(state + 0x60)];
        if (*(s32 *)(state + 0x64) >= *(s32 *)path) {
            if (!func_L00_00324120(object)) {
                object[0x20] = 2;
                func_L00_002D7140(*(u8 **)(state + 0x68));
                func_002A8598(object[0x21], 0);
            }
            slot = *(s32 *)(state + 0x70);
            if (slot != -1) {
                u8 *record = (u8 *)D_00188660 + slot * 0x70;
                if (*(u8 **)(record + 0x88) == object && record[0x74]) func_002E59F8(slot);
            }
            *(s32 *)(state + 0x70) = -1;
        } else {
            *(TI128 *)(point) = *(TI128 *)(path + 0x10 + *(s32 *)(state + 0x64) * 16);
            func_00282CF0(step, point, (object + 0x10));
            func_00282F20(step, step, 0.040000003f);
            func_00282CC0((object + 0x10), (object + 0x10), step);
            if (func_00282E80((object + 0x10), point) < 0.05f) ++*(s32 *)(state + 0x64);
        }
        if (func_002ACBC8(D_00189EA0, *(s32 *)(state + 0x6C))) {
            func_002A8598(object[0x21], 0);
            *(TI128 *)((object + 0x10)) = *(TI128 *)(path + 0x10);
            object[0x20] = 0;
            *(s32 *)(state + 0x64) = 0;
            slot = *(s32 *)(state + 0x70);
            if (slot != -1) {
                u8 *record = (u8 *)D_00188660 + slot * 0x70;
                if (*(u8 **)(record + 0x88) == object && record[0x74]) func_002E59F8(slot);
            }
            *(s32 *)(state + 0x70) = -1;
            func_L00_002D7140(*(u8 **)(state + 0x68));
        }
    }
    position = object + 0x10;
    if (object[0x20] == 2) {
        u8 *path;
        if (func_002ACBC8(D_00189EA0, *(s32 *)(state + 0x6C))) {
            path = D_L11_001FF580[*(s32 *)(state + 0x60)];
            func_002A8598(object[0x21], 0);
            *(TI128 *)(position) = *(TI128 *)(path + 0x10);
            object[0x20] = 0;
            *(s32 *)(state + 0x64) = 0;
            slot = *(s32 *)(state + 0x70);
            if (slot != -1) {
                u8 *record = (u8 *)D_00188660 + slot * 0x70;
                if (*(u8 **)(record + 0x88) == object && record[0x74]) func_002E59F8(slot);
            }
            *(s32 *)(state + 0x70) = -1;
            func_L00_002D7140(*(u8 **)(state + 0x68));
        }
    }
    if (object[0x20] == 3) {
        u8 *path;
        path = D_L11_001FF580[*(s32 *)(state + 0x60)];
        if (*(s32 *)(state + 0x64) < 0) {
            object[0x20] = 0;
            *(s32 *)(state + 0x64) = 0;
        } else {
            *(TI128 *)(point) = *(TI128 *)(path + 0x10 + *(s32 *)(state + 0x64) * 16);
            func_00282CF0(step, point, position);
            func_00282F20(step, step, 0.080000006f);
            func_00282CC0(position, position, step);
            if (func_00282E80(position, point) < 0.05f) --*(s32 *)(state + 0x64);
        }
    }
    if (object[0x20] == 5) {
        u8 *path;
        path = D_L11_001FF580[*(s32 *)(state + 0x60)];
        if (*(s32 *)(state + 0x64) < 0) {
            object[0x20] = 0;
            *(s32 *)(state + 0x64) = 0;
            slot = *(s32 *)(state + 0x70);
            if (slot != -1) {
                u8 *record = (u8 *)D_00188660 + slot * 0x70;
                if (*(u8 **)(record + 0x88) == object && record[0x74]) func_002E59F8(slot);
            }
            *(s32 *)(state + 0x70) = -1;
        } else {
            *(TI128 *)(point) = *(TI128 *)(path + 0x10 + *(s32 *)(state + 0x64) * 16);
            func_00282CF0(step, point, position);
            func_00282F20(step, step, 0.080000006f);
            func_00282CC0(position, position, step);
            if (func_00282E48(position, point) < 0.05f) --*(s32 *)(state + 0x64);
        }
    }
    if (object[0x20] == 6) {
        u8 *path;
        path = D_L11_001FF580[*(s32 *)(state + 0x60)];
        if (*(s32 *)(state + 0x64) >= *(s32 *)path) {
            if (!func_L00_00324120(object)) {
                object[0x20] = 2;
                *(s32 *)(state + 0x64) = 0;
                func_002A8598(object[0x21], 0);
                slot = *(s32 *)(state + 0x70);
                if (slot != -1) {
                    u8 *record = (u8 *)D_00188660 + slot * 0x70;
                    if (*(u8 **)(record + 0x88) == object && record[0x74]) func_002E59F8(slot);
                }
                *(s32 *)(state + 0x70) = -1;
            }
        } else {
            *(TI128 *)(point) = *(TI128 *)(path + 0x10 + *(s32 *)(state + 0x64) * 16);
            func_00282CF0(step, point, position);
            func_00282F20(step, step, 0.080000006f);
            func_00282CC0(position, position, step);
            if (func_00282E48(position, point) < 0.05f) ++*(s32 *)(state + 0x64);
        }
    }
    func_00282CF0(delta, position, previous);
    func_002AD6F0(state + 0x20, delta, rotation, rotation);
    func_PAL_L01_00322798(object, state + 0x74, object[0xBC]);
}
