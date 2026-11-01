#include "include_asm.h"

#include "common.h"
extern void func_0027AB40(void);
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
extern u8 D_001A7A40;
extern f32 D_001A8C74;
extern f32 D_001A8C78;
extern f32 D_001B5360[12];
extern void func_0027AB40(void);
extern void func_00129178(f32 *);
extern void func_001292C0(f32 *, f32 *, f32);
extern void func_00129368(f32 *, f32 *, f32);
extern void func_00129218(f32 *, f32 *, f32);
extern void func_00282F20(f32 *, f32 *, f32);
extern void func_00282CF0(f32 *, f32 *, f32 *);
extern void func_PAL_002717F8(f32 *, int);

u8 func_PAL_002F6A48(void)
{
    f32 m[16] __attribute__((aligned(16)));
    f32 t[4] __attribute__((aligned(16)));
    CamRec_2F5AF8 *rec;
    f32 *w;
    f32 scale;
    f32 k;
    u8 kind;

    rec = &D_001B8840.recs[D_001B8840.index];
    w = rec->w0;
    kind = rec->kind;
    scale = w[3];
    D_001B9040.scale = scale;
    if (D_001A7A40 != 0)
        D_001B9040.scale = scale * D_001A8C74;
    func_0027AB40();
    qcopy(D_001B5200.pos, rec);
    func_00129178(m);
    func_001292C0(m, m, w[0]);
    func_00129368(m, m, w[1]);
    func_00129218(m, m, w[2]);
    D_001B5200.row0[0] = -m[8];
    D_001B5200.row1[0] = -m[0];
    D_001B5200.row2[0] = m[4];
    D_001B5200.row0[1] = -m[9];
    D_001B5200.row1[1] = -m[1];
    D_001B5200.row2[1] = m[5];
    D_001B5200.row0[2] = -m[10];
    D_001B5200.row1[2] = -m[2];
    D_001B5200.row2[2] = m[6];
    if (D_001A7A40 != 0 && (k = D_001A8C78) != 0.0f) {
        qcopy(t, D_001B5200.row0);
        func_00282F20(t, t, k);
        func_00282CF0(D_001B5200.pos, D_001B5200.pos, t);
    }
    func_PAL_002717F8(&D_001B5360[0], 0);
    func_PAL_002717F8(&D_001B5360[4], 1);
    func_PAL_002717F8(&D_001B5360[8], 2);
    return kind;
}
