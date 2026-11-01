#include "include_asm.h"

#include "common.h"
typedef struct MobyClass_003BF9B0 {
    u8 pad000[0x24];
    f32 scale;  
} MobyClass_003BF9B0;
typedef struct Moby_003BF9B0 {
    u8 pad000[0x10];
    f32 pos[4];  
    u8 state;  
    u8 pad021[0x3];
    MobyClass_003BF9B0 *pClass;  
    u8 pad028[0x4];
    f32 scale;  
    u8 f30;  
    u8 f31;  
    u16 f32;  
    u16 flags;  
    u8 pad036[0x2];
    u64 f38;  
    u8 pad040[0x28];
    struct State_003BF9B0 *pVars;  
    u8 pad06C[0x3];
    u8 f6F;  
    u8 pad070[0x8];
    s32 f78;  
    u8 pad07C[0x44];
    u8 fC0[0x10];  
} Moby_003BF9B0;
typedef struct State_003BF9B0 {
    u8 pad000[0x20];
    f32 f20;  
    s16 f24;  
    s16 f26;  
    s8 f28;  
    u8 pad029[0x1F];
    s8 f48;  
    u8 pad049[0x1];
    s8 f4A;  
    u8 pad04B[0x5];
    f32 f50;  
    f32 f54;  
    f32 f58;  
    f32 f5C;  
    f32 f60;  
    u8 pad064[0xC];
    f32 f70;  
    f32 f74;  
    f32 f78;  
    u8 pad07C[0x4];
    f32 f80;  
    f32 f84;  
    u32 f88;  
    u8 pad08C[0xAC];
    s8 f138;  
    s8 f139;  
    u8 pad13A[0x6];
    u8 f140[0x10];  
    s8 f150;  
    s8 f151;  
    s8 f152;  
    u8 pad153[0x3];
    s8 f156;  
    s8 f157;  
    u8 pad158[0x4];
    f32 f15C;  
    f32 f160;  
    f32 f164;  
    f32 f168;  
    f32 f16C;  
    f32 f170;  
    f32 f174;  
    s16 f178;  
    u8 pad17A[0x2];
    f32 f17C;  
    u8 pad180[0x8];
    s32 f188;  
    u8 pad18C[0xC];
    f32 f198;  
    f32 f19C;  
    u8 pad1A0[0xC];
    s8 f1AC;  
    s8 f1AD;  
    s8 f1AE;  
    s8 f1AF;  
    u8 pad1B0[0x2];
    s8 f1B2;  
    s8 f1B3;  
    u8 pad1B4[0x3];
    s8 f1B7;  
    u8 pad1B8[0xA0];
    s32 f258;  
    u8 pad25C[0x10];
    s16 f26C;  
    s16 f26E;  
    u8 pad270[0x10];
    u8 f280[0x20];  
    struct Moby_003BF9B0 *child;  
    u8 pad2A4[0x2];
    s16 f2A6;  
    f32 f2A8;  
    u8 pad2AC[0x7C];
    s32 f328;  
    s32 f32C;  
    u8 pad330[0x84];
    s32 f3B4;  
    u8 pad3B8[0x6];
    s16 f3BE;  
} State_003BF9B0;
typedef struct {
    u8 pad000[0xAA];
    s16 fAA;  
} Info_003BF9B0;
typedef struct {
    u8 pad000[0x20];
    Info_003BF9B0 *info;  
} Found_003BF9B0;
extern f32 D_L23_001AFA58 __attribute__((sda));
extern s32 D_L23_001B1424 __attribute__((sda));
extern s32 ref_L23_003BF9B0_00;
extern s32 D_L23_001B1650 __attribute__((sda));
extern s32 D_L23_001B36AC;
extern s32 D_L23_001B36F0;
extern u8 D_L23_001BA640[];
extern Moby_003BF9B0 *func_0029EFD0(s32);
extern void func_00283360(void *);
extern void func_L23_003C0028(Moby_003BF9B0 *);
extern s32 func_00283CF0(f32);
extern void func_PAL_L23_003C5480(Moby_003BF9B0 *);
extern void func_002B60B0(Moby_003BF9B0 *, f32, f32, f32, f32);
extern f32 func_00282E48(void *, void *);
extern void func_002A93B0(Moby_003BF9B0 *);
extern Found_003BF9B0 *func_002A9640(Moby_003BF9B0 *, s32, s32);
extern void func_PAL_002B1A50(Moby_003BF9B0 *, void *, s32);
extern void func_002AFFD8(void *, void *, s32);
extern void func_L00_00325600(void *, void *, s32);

void func_PAL_L23_003C3258(Moby_003BF9B0 *moby)
{
    State_003BF9B0 *vars = moby->pVars;
    f32 k;

    if (moby->state == 0) {
        f32 fps;

        vars->f2A8 = D_L23_001AFA58;
        vars->f3B4 = -1;
        vars->f3BE = 0;
        vars->f26C = 0;
        vars->f26E = 0;
        vars->f32C = 0;
        vars->f328 = 0;
        vars->f2A6 = 0;
        moby->flags |= 0x100;
        vars->f1B7 = 1;
        vars->f150 = 12;
        vars->f151 = 8;
        vars->f152 = 8;
        vars->f156 = 8;
        vars->f157 = 8;
        vars->f1AC = -1;
        vars->f1AD = -1;
        vars->f1AE = -1;
        vars->f1AF = -1;
        vars->f1B2 = -1;
        vars->f1B3 = -1;
        fps = D_L23_001B36F0;
        vars->f15C = 0.70000005f;
        vars->f188 = 3;
        vars->f174 = 4.0f;
        vars->f160 = 0.080000006f;
        vars->f164 = 0.060000002f;
        vars->f168 = 0.120000005f;
        vars->f16C = 0.024f;
        vars->f170 = 3.0f;
        vars->f17C = 0.4f;
        vars->f19C = 150.0f / fps;
        vars->f138 = 5;
        vars->f139 = 6;
        vars->f198 = 40.0f / fps;
        vars->f84 = 4.0f;
        vars->f70 = 0.0064000003f;
        vars->f74 = 0.0064000003f;
        vars->f78 = 0.24000001f;
        vars->f50 = 2.5f;
        vars->f54 = 0.75f;
        vars->f60 = 2.0f;
        vars->f58 = 2.75f;
        vars->f5C = 2.75f;
        vars->f80 = 0.78539824f;
        vars->f20 = D_L23_001B36F0;
        vars->f24 = D_L23_001B36F0;
        vars->f28 = 3;
        vars->f26 = 50;
        vars->f88 |= 0x81;
        moby->f32 = 0xFF;
        moby->f30 = 0xFF;
        vars->child = func_0029EFD0(0x7E6);
        func_00283360(vars->child->fC0);
        vars->f258 = 0;
        func_L23_003C0028(moby);
        vars->f48 = func_00283CF0(12.0f);
        vars->f4A = func_00283CF0(14.4f);
    } else if (ref_L23_003BF9B0_00 != 0 && D_L23_001B1424 == 0) {
        if (D_L23_001B36AC < 10)
            func_PAL_L23_003C5480(moby);
        else
            D_L23_001B1650 = 0;
    }
    if (moby->state == 13)
        return;
    func_002B60B0(moby, 0.0064000003f, 0.16000001f, 0.0025132746f, 0.25132746f);
    k = 1.4f;
    if (moby->state == 2)
        k = 0.7f;
    moby->scale = moby->pClass->scale * k;
    if (vars->child != 0) {
        vars->child->f32 = moby->f32;
        vars->child->f30 = moby->f30;
        vars->child->f38 = moby->f38;
        vars->child->f78 = moby->f78;
        vars->child->f31 = 1;
        vars->child->scale = vars->child->pClass->scale * k;
        if (vars->child->f31 != 0 && func_00282E48(vars->child->pos, D_L23_001BA640) < 24.0f) {
            func_002A93B0(vars->child);
            vars->child->f6F = 22;
        }
    }
    if (moby->f31 != 0 && func_00282E48(moby->pos, D_L23_001BA640) < 24.0f) {
        func_002A93B0(moby);
        moby->f6F = 22;
    }
    {
        Found_003BF9B0 *found = func_002A9640(moby, 0x30000, 1);

        if (found != 0 && found->info != 0 && found->info->fAA == 0x1190)
            vars->f20 = 0;
    }
    if (moby->state == 2)
        vars->f178 = 0;
    func_PAL_002B1A50(moby, vars->f140, 0);
    func_002AFFD8(moby->pos, vars->f280, 0);
    func_L00_00325600(moby->fC0, vars->f280, 0);
}
