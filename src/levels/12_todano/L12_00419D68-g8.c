#include "names.h"
/* Transforms the two vectors by the object matrix (the second one also lifted by 2) and reports success when the object is in step 5 with its marker value. The two small-data vectors are 8-byte sda arrays so that their addresses come out as `addiu $gp`. */
extern float g_driver_sight_start_local[2] __attribute__((sda));
extern float g_driver_sight_end_local[2] __attribute__((sda));
extern void func_002F1E08(float *, float *, char *);
extern void func_002F1928(float *, float *, char *);
extern float func_0031F718(float, float *, int);

/* Works out two sight points in front of the object for the line-of-sight test. Only works while the object is in its ready state. */
int gate_compute_sight_points(char *obj, float *sight_end, float *sight_start) {
    char *matrix;
    char *position;
    if (*(short *)(obj + 0xAA) != 0xFA5 /* moby class 4005 */ || *(unsigned char *)(obj + 0x20) != 5) {
        return 0;
    } else {
        matrix = obj + 0xC0;
        func_002F1E08(sight_start, g_driver_sight_start_local, matrix);
        position = obj + 0x10;
        func_002F1928(sight_start, sight_start, position);
        func_002F1E08(sight_end, g_driver_sight_end_local, matrix);
        func_002F1928(sight_end, sight_end, position);
        sight_end[2] = sight_end[2] + 2.0f;
        sight_end[2] = func_0031F718(0.5f, sight_end, 0);
    }
    return 1;
}
