#include "include_asm.h"
#include "names.h"
typedef struct {float amplitude, offset; int frames, longest;} CameraShake;
typedef struct { char prefix[0x140]; float pos[4]; char pad[0x40]; char *current; char pad194[0x1dc]; float rows[12]; } CameraSystem;
extern CameraSystem D_001B5200;
extern float D_001A85B8 __attribute__((sda));
extern int func_00282948(void *);
extern float func_00283CE0(int);
extern float func_00283C28(float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002ACE78(void *, void *, float);
extern void func_00283958(void *, void *);
extern void func_00283738(void *, void *, void *);
/* Shakes the camera for a short time, fading out as the frames run down. */
void func_00271958(CameraShake *shake, int mode)
{
    float buf[4], matrix[12];
    float ratio, cube, frequency, elapsed, ramp;
    if (gActiveCamera.current != 0 && *(short *)(gActiveCamera.current + 0x86) == 6) {
        shake->frames = 0;
        shake->longest = 0;
    } else if (shake->frames != 0) {
        if (shake->longest < shake->frames) shake->longest = shake->frames;
        FastFloatHelperD(&shake->frames);
        ratio = IntToFloat(shake->frames) / IntToFloat(shake->longest);
        switch (mode) {
        case 0: {
            float value = shake->amplitude * FastSinOrCosA(FastFloatHelperG(IntToFloat(shake->frames) * 2.0f)) * ratio * ratio;
            shake->offset = value;
            vec_scale_to_length(buf, (gActiveCamera.rows + 8), value);
            FastVecAdd(gActiveCamera.pos, gActiveCamera.pos, buf);
            break;
        }
        case 1: {
            float value = shake->amplitude * FastSinOrCosA(FastFloatHelperG(IntToFloat(shake->frames) * 2.0f)) * ratio * ratio;
            shake->offset = value;
            vec_scale_to_length(buf, gActiveCamera.rows, value);
            FastVecAdd(gActiveCamera.pos, gActiveCamera.pos, buf);
            break;
        }
        case 2: {
            float value;
            cube = ratio * ratio * ratio;
            frequency = D_001A85B8 * 0.017453294f;
            elapsed = IntToFloat(shake->longest - shake->frames) * (1.0f / 60.0f);
            ramp = elapsed * 6.0f;
            if (ramp > 1.0f) ramp = 1.0f;
            value = shake->amplitude * FastSinOrCosB(FastFloatHelperG(elapsed * frequency - frequency * 10.0f)) * cube * ramp;
            shake->offset = value;
            SetDirectionWithComplement(buf, gActiveCamera.rows, value);
            quaternion_to_rotation_basis(buf, matrix);
            multiply_matrix3x3(gActiveCamera.rows, matrix, gActiveCamera.rows);
            break;
        }
        }
    } else shake->longest = 0;
}
