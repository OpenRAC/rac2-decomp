#include "common.h"

extern char g_hero_state[];

extern float D_L00_001A7FA4 __attribute__((sda));

extern float D_L00_001A7F9C __attribute__((sda));

/* Gives the camera values for hero states 98 to 100 and 17. Returns 1 if it filled them in, otherwise 0. */
int hero_get_camera_params(float *heightOut, float *pitchOut, float *yawOut)
{
    char *heroBase = g_hero_state;
    int heroState = *(int *)(heroBase + 8852);

    if (heroState >= 98 && heroState <= 100) {
        if (heightOut) *heightOut = *(float *)(heroBase + 6316);
        if (pitchOut) *pitchOut = D_L00_001A7FA4 * 4.8481374506081920117140e-06f;
        if (yawOut) *yawOut = D_L00_001A7F9C * 2.9088824521750211715698e-04f;
        return 1;
    }
    if (heroState == 17) {
        if (heightOut) *heightOut = *(float *)(heroBase + 152);
        if (pitchOut) *pitchOut = D_L00_001A7FA4 * 1.4544411897077225148678e-05f;
        if (yawOut) *yawOut = D_L00_001A7F9C * 8.7266473565250635147095e-04f;
        return 1;
    }
    return 0;
}

extern void func_0031DB00(void *, void *, float, float, float, float);
extern void func_L00_002EE3D0(void *, void *, float);
extern void func_L00_002EE108(void *, void *, void *);
extern void func_L00_002EE220(void *, void *, void *);
extern char g_camera_l00_position[];
extern char D_0018B2F0[];
/* Eases the camera height behind the hero and copies the hero camera data into the level camera block. */
void hero_update_camera_block(void) {
    char *hero = g_hero_state;
    char *cameraBlock;
    float targetHeight;
    if (*(float *)(hero + 0x151C) == 0.0f) *(float *)(hero + 0x151C) = 1.5f;
    targetHeight = 1.5f;
    if (*(int *)(hero + 0x2294) == 4) targetHeight = 0.75f;
    func_0031DB00(hero + 0x151C, hero + 0x1520, targetHeight, 0.004444444552063942f, 0.004444444552063942f, 0.5333333611488342f);
    func_L00_002EE3D0(hero + 0x14D0, hero + 0x20, *(float *)(hero + 0x151C));
    func_L00_002EE108(hero + 0x14D0, hero + 0x14D0, hero + 0x80);
    if (*(int *)(hero + 0x229C) == 25 || *(int *)(hero + 0x2294) == 102) {
        float minHeight = *(float *)(hero + 0x334) + 0.75f;
        if (*(float *)(hero + 0x14D8) < minHeight) *(float *)(hero + 0x14D8) = minHeight;
    }
    cameraBlock = g_camera_l00_position;
    qcopy(cameraBlock, D_0018B2F0);
    qcopy(cameraBlock + 0x230, D_0018B2F0 + 0x10);
    func_L00_002EE220(cameraBlock + 0x240, cameraBlock + 0x230, D_0018B2F0 - 0x14B0);
    func_L00_002EE3D0(cameraBlock + 0x240, cameraBlock + 0x240, 1.0f);
    func_L00_002EE220(cameraBlock + 0x250, cameraBlock + 0x240, cameraBlock + 0x230);
    func_L00_002EE3D0(cameraBlock + 0x250, cameraBlock + 0x250, 1.0f);
}
