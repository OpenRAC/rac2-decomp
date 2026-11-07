/* func_US2_002FA240, the USA v2.00 copy of func_002F93B0: the same C, where rename func_002F9198 becomes func_US2_002FA028. */
#include "common.h"

extern void func_0027AB40(void);

#ifndef RAC2_T_F32_F2144BF3D
#define RAC2_T_F32_F2144BF3D
#endif

#ifndef RAC2_T_S32_F2144BF3D
#define RAC2_T_S32_F2144BF3D
typedef int s32_F2144bf3d;
#endif

/* Resident record reached through a fixed core symbol: the retail body keeps
   the base in a register and addresses every field by displacement. */
#ifndef RAC2_T_RESIDENT138180_F2144BF3D
#define RAC2_T_RESIDENT138180_F2144BF3D
#endif

extern char D_00138180[];

extern s32_F2144bf3d D_0018D198[];

extern s32_F2144bf3d D_L06_001AD3A0 __attribute__((sda));

extern s32_F2144bf3d D_001A7390;

extern s32_F2144bf3d D_001A79F0;

extern s32_F2144bf3d D_L06_001B2348;

extern s32_F2144bf3d D_L06_001A8FC0;

extern s32_F2144bf3d D_L06_001B2900;

extern s32_F2144bf3d D_L06_001AA0F0;

/* Applies the current cutscene camera key and returns its flag byte. */
#include "common.h"

typedef struct { u8 pad00[0xC]; u8 kind; u8 pad0D[3]; f32 w0[4]; } CamRec_2F5AF8;
typedef struct { u8 pad00[0x38]; s32 index; u8 pad3C[0x68 - 0x3C]; CamRec_2F5AF8 *recs; } CamList_2F5AF8;
typedef struct { u8 pad[0xB0]; f32 scale; } CamView_2F5AF8;
typedef struct {
    u8 pad000[0x140];
    f32 pos[4];
    u8 pad150[0x370 - 0x150];
    f32 row0[3];
    f32 pad37C;
    f32 row1[3];
    f32 pad38C;
    f32 row2[3];
} Cam_2F5AF8;

extern CamList_2F5AF8 D_001B8840;
extern CamView_2F5AF8 D_001B9040;
extern Cam_2F5AF8 D_001B5200;
extern void func_0027AB40(void);
/* Publishes the slow-down factor and, while the frame rate is below one, asks
   for the six-frame path. */


extern void (*ref_L00_002F5EF8_00)(int);
/* func_002F6510: the copied records have the measured 0xE0-byte extent. */
typedef int F6510Quad __attribute__((mode(TI)));
typedef union {
    F6510Quad raw[14];
    struct { char prefix[0x80]; int value; char tail[0x5C]; } fields;
} F6510Record;
typedef struct { int type; char pad[12]; int locked; int active; } F6510Row;
typedef struct { char pad[0x80]; int selected; char pad84[0xBC]; F6510Row rows[1]; } F6510State;
extern F6510State D_L00_0022F7C0;
extern unsigned char D_00139568[];
extern F6510Record D_L00_00262570[];
int func_002F6510(void);

extern unsigned char D_001A7AB8[] MACRO_ADDR;
extern unsigned char D_001A7AF8[] MACRO_ADDR;
extern unsigned char D_001A7A80[] MACRO_ADDR;
typedef struct { int active; char pad4[0x10]; int info; char pad18[0x80]; int channels[3]; char padA4[0x3C]; } F73Record;
extern F73Record D_00239BA0[];
typedef struct { char pad[0x140]; int rows[96][4]; int count; } F73StateType;
extern F73StateType D_0021F240_rows __asm__("D_0021F240");
typedef struct { unsigned char pad0[0x3C]; char *destination; unsigned char pad1[0x24]; int clear; } Func_002F88D8State;
extern Func_002F88D8State ref_L00_002F88D8_00;
typedef unsigned int Quad_002F9198 __attribute__((mode(TI), aligned(16)));
typedef struct { Quad_002F9198 a, b, c; } Three_002F9198;
typedef struct { int words[5]; } Five_002F9198;
typedef struct { int state; char pad4[0x24]; char *moby; char pad2C[0x24]; int mode; char pad54[0xC]; int restore; char pad64[0x7C]; Quad_002F9198 saved; } Shop_002F9198;
typedef struct { char *moby; char pad4[0x14]; int a; char pad1C[0x14]; int b; } HeroMenu_002F9198;
extern Shop_002F9198 D_0021F240;
/* Its address is one `la` (assembler lui/addiu pair), not a split %hi/%lo: retail
   schedules the pair as one insn ahead of dst + 0x220. */
extern Three_002F9198 D_001B2250 MACRO_ADDR;
/* 0x40-byte block that func_002DE990 saves and restores whole. */
typedef struct { char pad0[0x20]; short level; char pad22[0x1E]; } Settings_002F9198;
extern Settings_002F9198 D_001A79F8 MACRO_ADDR;
extern Five_002F9198 D_001AD308;
extern HeroMenu_002F9198 D_00152C00;
extern int func_002E5CF8(int, int, void *);
void func_US2_002FA028(void);

extern int D_001B2240, D_001B223C;
extern int D_001B2244 __attribute__((sda));
extern int D_00139688[];
extern void func_0028B6C8(int, unsigned int);
extern int func_002F6510(void);
extern void func_US2_002FA028(void);

typedef struct { int id, kind; int fields[4]; } ShopRow_93;
typedef struct {
    char pad0[0x28]; char *moby; char pad2C[0x24];
    int mode; char pad54[0x18]; int scroll;
    char pad70[8]; int handle; char pad7C[4]; int selected;
    int busy; int animated; char pad8C[4]; int animation;
    char pad94[0xAC]; ShopRow_93 rows[64]; int count;
} ShopInput_93;
extern ShopInput_93 F93State __asm__("D_0021F240");
typedef struct { char pad[0x1C4]; int buttons; } Input_93;
void func_US2_002FA240(void)
{
    ShopInput_93 *state = &F93State;
    int cost;
    char *record;
    if (state->busy) return;
    {
        Input_93 *input = (Input_93 *)D_00138180;
        if ((input->buttons & 0x2000) ||
                (D_001B2240 >= 16 && D_001B2240 % 10 == 1)) {
            if (state->scroll < 57) {
                int moved = 0;
                if (state->selected < state->count - 1) {
                    ++state->selected;
                    moved = 1;
                }
                if (moved) {
                    if (state->animated) {
                        int animation = 3;
                        if (state->mode != 2) animation = 1;
                        state->animation = animation;
                    }
                    state->scroll += 56;
                    func_002E5CF8(1, 17, state->moby);
                    if (state->handle != -1) {
                        if (state->mode == 0)
                            func_0028B6C8(state->handle, 0);
                    }
                    F93State.handle = -1;
                }
            }
        }
    }
    {
        Input_93 *input = (Input_93 *)D_00138180;
        ShopInput_93 *state;
        if ((input->buttons & 0x8000) ||
                (D_001B223C >= 16 && D_001B223C % 10 == 1)) {
            state = &F93State;
            if (state->scroll >= -56) {
                int moved = 0;
                if (state->selected > 0) {
                    --state->selected;
                    moved = 1;
                }
                if (moved) {
                    if (state->animated) {
                        int animation = 3;
                        if (state->mode != 2) animation = 1;
                        state->animation = animation;
                    }
                    state->scroll -= 56;
                    func_002E5CF8(1, 17, state->moby);
                    if (state->handle != -1) {
                        if (state->mode == 0)
                            func_0028B6C8(state->handle, 0);
                    }
                    F93State.handle = -1;
                }
            }
        }
    }
    {
        Input_93 *input = (Input_93 *)D_00138180;
        ShopInput_93 *state;
        if (((input->buttons & 0x40) && !(D_001B2244 & 0x40) && F93State.mode != 3) ||
            ((input->buttons & 0x40) && !(D_001B2244 & 0x40) && F93State.mode == 3 &&
             *(int *)((char *)&F93State + 0x144 + F93State.selected * 12) != 0)) {
                state = &F93State;
                if (state->mode == 0) {
                    int stride = sizeof(ShopRow_93);
                    int *kinds = &state->rows[0].kind;
                    if (*(int *)((char *)kinds + state->selected * stride) == 0) {
                        cost = func_002F6510();
                        if ((*(int *)&D_001A79F8) >= cost) goto activate;
                    }
                    if (*(int *)((char *)kinds + state->selected * stride) != 1) goto rejected;
                    {
                        int id = state->rows[state->selected].id;
                        int owned = D_00139688[id];
                        record = (char *)D_00239BA0 + D_00139568[id] * 224;
                        if (owned >= *(unsigned short *)(record + 0x8E)) goto rejected;
                    }
                    if ((*(int *)&D_001A79F8) < *(unsigned short *)(record + 0x88)) goto rejected;
                }
activate:
                {
                    ShopInput_93 *active = &F93State;
                    if (active->animated) active->animation = 1;
                    active->busy = 1;
                    func_002E5CF8(0, 17, active->moby);
                    goto finish;
                }
rejected:
                func_002E5CF8(2, 17, F93State.moby);
        }
    }
finish:
    if (((Input_93 *)D_00138180)->buttons & 0x10) func_US2_002FA028();
}

extern void func_US2_002FA240(void);

/* One font glyph: its texture cell, its top offset and its advance. */
typedef struct { u8 u, v; signed char top, adv; } Glyph_002F97A0;

extern Glyph_002F97A0 D_00263EF0[];
/* Prints up to `limit` characters of `text` from (x, y) at `scale`, in the large font, fading
   each glyph's left and right edges out with their distance from the screen centre (215 on
   the second screen layout, 256 elsewhere, three quarters as fast). Characters 0x80..0xa7
   draw their entry 0x40 later; control characters below 0x20 draw a grey 24-pixel sprite. */
