#include "include_asm.h"
#include "names.h"
extern char D_00189E20_11[];
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern float func_L00_002D3B00(char *);

/* Returns the height reached by an object moving with the given velocity for the current
 * movement mode and optionally stores the quantized number of steps. */
float func_L00_002D3D98(float *position, float *velocity, int *out_steps, float step)
{
    int mode = *(unsigned char *)(D_00189E20_11 + 8899);

    switch (mode) {
    case 0: {
        int steps;
        float lift, drop, result;

        steps = FloatToInt(velocity[2] / step);
        lift = IntToFloat(steps);
        drop = IntToFloat((steps * steps + steps) >> 1);
        result = position[2] + velocity[2] * lift - drop * step;
        if (out_steps)
            *out_steps = steps;
        return result;
    }
    case 1:
    case 2: {
        int steps = FloatToInt(GetViewSpaceHeight((char *)velocity) / step);

        if (out_steps)
            *out_steps = steps;
        return position[2] + velocity[2] * 0.5f;
    }
    }
    return 0.0f;
}
