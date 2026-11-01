#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef struct {
    char pad[0x1C];
    char *definition;
} CameraEntry;
typedef struct {
    Quad rotation;
    float pad[2];
    float fov;
    float unused;
} CameraPreset;
extern CameraEntry *D_L04_001B1E84;
extern char *D_L04_001B24DC;
extern int D_L04_001B1CB8 __attribute__((sda));
extern int D_L04_001B1CBC __attribute__((sda));
extern float D_L04_001B1CC0 __attribute__((sda));
extern int D_L04_001B1CC4 __attribute__((sda));
extern int D_L04_001B1CC8 __attribute__((sda));
extern int D_001A79F0;
extern CameraPreset D_L04_002C6F00[], D_L04_002C7100[];
extern char ref_L04_0046CFB8_00[];
extern float D_L04_001BDC30[];
extern int func_002ACBC8(void *, int);
extern void func_L04_0046CD68(void *, int);
extern float func_00283198(float);
extern float func_00283180(float);
extern float func_002A7878(float, float);
extern void func_0027AB40(void);
extern void func_L04_0046D6A8(void *);
extern void func_PAL_L04_004734D8(void *);

/* Pick the camera for the region the target moby stands in: entering one of
 * the definition's sixteen cuboids either switches to that region's fixed
 * preset or flips the follow side; outside every region the follow camera runs. */
void func_PAL_L04_00473240(char *obj)
{
    char *definition = D_L04_001B1E84[*(short *)(obj + 0x84)].definition;
    char *moby = D_L04_001B24DC + (*(int *)(definition + 0x60) << 8);
    int follow = 0;
    int i;
    float sine;

    if (*(unsigned char *)(moby + 0x20) == 3) {
        D_L04_001B1CB8 = -1;
        for (i = 0; i < 16; i++) {
            if (*(int *)(definition + 0x20 + i * 4) != -1
                && func_002ACBC8(moby + 0x10, *(int *)(definition + 0x20 + i * 4)))
                D_L04_001B1CB8 = i;
        }
        if (D_L04_001B1CB8 == -1) {
            if (D_L04_001B1CBC != -1) {
                if (D_L04_001B1CC4) D_L04_001B1CC4 = 0;
                else D_L04_001B1CC4 = 1;
                func_L04_0046CD68(obj, 1);
                sine = func_00283198(0.562170565f);
                D_L04_001BDC30[0] = sine / func_00283180(0.562170565f);
                func_0027AB40();
                D_L04_001B1CC8 = 0;
                D_L04_001B1CBC = D_L04_001B1CB8;
            }
            follow = 1;
        } else {
            if (D_L04_001B1CB8 != D_L04_001B1CBC) {
                if (func_002A7878(0, 1) < .65f) {
                    D_L04_001B1CC8 = 1;
                    if (D_001A79F0 == 4 || (int)ref_L04_0046CFB8_00 == 40) {
                        CameraPreset *preset = &D_L04_002C6F00[D_L04_001B1CB8];
                        qcopy(obj + 0x30, preset);
                        D_L04_001B1CC0 = preset->fov;
                    } else {
                        CameraPreset *preset = &D_L04_002C7100[D_L04_001B1CB8];
                        qcopy(obj + 0x30, preset);
                        D_L04_001B1CC0 = preset->fov;
                    }
                } else {
                    if (D_L04_001B1CC4) D_L04_001B1CC4 = 0;
                    else D_L04_001B1CC4 = 1;
                    func_L04_0046CD68(obj, 1);
                    D_L04_001B1CC8 = 0;
                }
                D_L04_001B1CBC = D_L04_001B1CB8;
            }
            if (D_L04_001B1CC8) {
                float half = D_L04_001B1CC0 * .5f;
                float sine2 = func_00283198(half);
                D_L04_001BDC30[0] = sine2 / func_00283180(half);
                func_0027AB40();
                func_L04_0046D6A8(obj);
            } else {
                follow = 1;
            }
        }
    } else {
        follow = *(unsigned char *)(moby + 0xBC) != 0;
    }
    if (follow) {
        func_PAL_L04_004734D8(obj);
        func_L04_0046D6A8(obj);
    }
}
