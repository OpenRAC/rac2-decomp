#include "include_asm.h"

#include "common.h"
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; char *ptr[0x980]; } Hero;
#define H ((Hero *)D_00189E20)
#define PAD ((Hero *)D_00138180)
extern u8 D_00189E20[];
extern u8 D_00138180[];
extern float D_L00_001AF624 __attribute__((sda));
extern float D_L00_0025C64C NOT_SDA;
extern int D_L00_001B2860;
extern unsigned char D_00139580[];
typedef struct { char prefix[0x54]; float fireRate; char tail[0x88]; } WeaponEntry;
extern WeaponEntry D_L00_00262570[];
extern void func_002A75E0(void *, int, int, int, int);
extern void func_L00_0037E000(void *);
extern void func_PAL_L00_002C4480(int, int);
extern int func_L00_002D4040(int);
extern void func_00273318(void *, unsigned int, int, int, int, int, float, float, float);
extern int func_00282948(void *);
extern int func_002829D8(void *);
extern int func_L00_002D3F30(int, int);
extern void func_0029FCC0(char *, int, char *);
extern int func_002E5CF8(int, int, char *);
extern char *func_PAL_L00_003AF088(void *, void *);

/* Update the firing effect and its input-controlled cooldown. */
void func_PAL_L00_003A7518(char *moby)
{
    float position[4];
    float *cooldown = *(float **)(moby + 0x68);
    int ready;
    if (*(unsigned char *)(moby + 0x20) == 0)
        *(unsigned char *)(moby + 0x20) = 1;
    if (*(unsigned char *)(moby + 0x42) == *(unsigned char *)(moby + 0x43) &&
        (*(unsigned char *)(moby + 0x60) & 2))
        func_002A75E0(moby, 1, 0, 2, 0);
    func_L00_0037E000(H->ptr[0x2290 / 4]);
    *(float *)(moby + 0x2C) = *(float *)(*(char **)(moby + 0x24) + 0x24) * D_L00_001AF624;
    D_L00_0025C64C = 0.1f;
    if (H->i[0x2294 / 4] == 1)
        func_PAL_L00_002C4480(29, 1);
    if (H->i[0x2294 / 4] == 29) {
        unsigned int color;
        if (*cooldown > 0.0f && func_L00_002D4040(-1))
            color = 0x600000FF;
        else
            color = 0x600FFF0F;
        func_00273318(moby, color, 0, 0x27, -1, 4, 2.0f, 0.0f, 90.0f);
    }
    if (H->ptr[0x1450 / 4])
        H->ptr[0xBF8 / 4] = H->ptr[0x1450 / 4];
    ready = 1;
    if (H->i[0x2294 / 4] == 29) {
        if (func_00282948(&H->i[0x2534 / 4]) == 0)
            ready = 0;
    } else
        H->i[0x2534 / 4] = 33;
    if (func_002829D8(cooldown) && !H->b[0x22BC] &&
        (PAD->u[0x1A0 / 4] & H->u[0x1230 / 4]) && H->i[0x1240 / 4] > 18 && ready) {
        if (func_L00_002D3F30(-1, 1)) {
            char *effect;
            D_L00_001B2860 = 1;
            func_0029FCC0(moby, 0, (char *)position);
            func_002E5CF8(1, 0, moby);
            func_002A75E0(moby, 2, 0, 2, 0);
            effect = func_PAL_L00_003AF088(position, moby);
            if (effect)
                *(char **)(effect + 0xB8) = moby;
        } else if ((PAD->u[0x1A4 / 4] & H->u[0x1230 / 4]) || D_L00_001B2860 == 1) {
            func_002E5CF8(0, 0, moby);
            D_L00_001B2860 = 0;
        }
        {
            WeaponEntry *entry = &D_L00_00262570[D_00139580[0]];
            *cooldown = 1.0f / entry->fireRate;
        }
    }
}
