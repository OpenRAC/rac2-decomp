#include "include_asm.h"

#include "common.h"
typedef struct { u8 data[256]; } AttachObject;
extern AttachObject *D_L01_001B255C __attribute__((sda));
extern u8 *D_L01_001FE180[] NOT_SDA;
extern f32 func_00282E80(void *, void *);
extern s32 func_002A8AF0(void *, void *, s32);
extern f32 func_002A7878(f32,f32);
extern f32 func_00283248(f32, f32);
extern f32 func_00283BE0(f32, f32);
extern f32 func_00283B98(f32, f32);
extern void func_0029FCC0(void *, s32, void *);
extern s32 func_002A8C28(void *, void *, f32, s32, f32, f32, s32, s32, s32);
extern s32 func_L01_003120A8(void *, void *, void *, f32, s32, f32, s32, s32, s32);
extern s32 func_001163B0(void);
extern s32 func_00283CF0(f32);
extern u8 *func_002BAA28(void *, void *, void *, u32, u32, s32, s32, s32, s32);
extern s32 func_L01_00321178(void *, void *);
extern s32 func_310648();
extern f32 func_310580(f32 x, f32 y);
extern s32 func_310528(s32 a, s32 b);
extern f32 func_2E3A48(f32 x);
extern f32 func_2E3A60(f32 x);
extern s32 func_00277F48(f32 radius, void *pos, s32 flag, void *obj, s32 arg);
extern u32 D_L01_001C3980[];
extern s32 func_00282948(void *);
extern f32 func_00283B98(f32, f32);
extern void func_0029FCC0(void *, s32, void *);
extern f32 func_00283198(f32);
extern s32 func_00283CF0(f32);
extern s32 func_002E5DA0(s32, s32, void *, s32);
typedef struct { u8 pad[0x80]; f32 pos[4]; u8 pad90[0x2AC]; u8 *object; s32 active; } PlayerECC;
extern PlayerECC D_00189E20;
extern s32 D_001A79F0[] __attribute__((sda));
extern u8 D_0019B4A8[];
typedef struct { u8 pad[0x464]; u8 collected[0]; } LevelSaveState;
extern LevelSaveState D_L01_0021E4B0;
extern u8 *D_L01_001B1F04 __attribute__((sda));
extern s32 func_L00_004290C0(void *);

/* Pulses the object's grey colour until the player touches it (save nibble counter at
   D_0019B4A8) or its id is already collected; then marks it and its linked record active
   and plays sound 0x8A1 once. */
void func_PAL_L01_003F1598(u8 *obj) {
    f32 pos[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj + 0x68);
    f32 dist;
    s32 shade;
    u16 id;
    u32 color;
    if (!state) return;
    *(f32 *)(state + 4) = func_00283B98(*(f32 *)(state + 4), 0.12566373f);
    if (obj[0x20] == 0) {
        func_0029FCC0(obj, 0, pos);
        dist = func_00282E80(D_00189E20.pos, pos);
        *(s32 *)(state + 8) = 0;
        if (D_00189E20.object == obj && D_00189E20.active && dist < 0.5f) {
            u16 objectId;
            objectId = *(u16 *)(obj + 0xB2);
            if (objectId & 1) {
                if (((D_0019B4A8[((s16)objectId >> 1) + (D_001A79F0[0] << 10)] >> 4) & 7) != 7)
                    D_0019B4A8[((s16)objectId >> 1) + (D_001A79F0[0] << 10)] += 16;
            } else {
                if ((D_0019B4A8[((s16)objectId >> 1) + (D_001A79F0[0] << 10)] & 7) != 7)
                    D_0019B4A8[((s16)objectId >> 1) + (D_001A79F0[0] << 10)] += 1;
            }
        }
        if (obj[0xB0] != 255) {
            s32 nibble;
            id = *(u16 *)(obj + 0xB2);
            if (D_L01_0021E4B0.collected[(s16)id] != 0) goto activate;
            nibble = D_0019B4A8[((s16)id >> 1) + (D_001A79F0[0] << 10)];
            if ((id & 1) ? ((nibble >> 4) & 7) : (nibble & 7)) {
activate:
                obj[0x20] = 1;
                obj[0xBC] = 1;
                if (*(s32 *)state != -1) D_L01_001B255C[*(s32 *)state].data[0xBC] = 1;
            }
        }
        shade = func_00283CF0((func_00283198(*(f32 *)(state + 4)) * 4.0f - 3.0f) * 128.0f);
        if (shade > 128) shade = 128;
        else if (shade < 32) shade = 32;
        color = (shade << 8) | 0x80000000;
        *(u32 *)(obj + 0x78) = (shade << 16) | color | shade;
    } else {
        if (!*(s32 *)(state + 8)) {
            func_002E5DA0(0, 0, obj, 0x8A1);
            *(s32 *)(state + 8) = 1;
        }
        *(u32 *)(obj + 0x78) = 0x80208010;
    }
}

