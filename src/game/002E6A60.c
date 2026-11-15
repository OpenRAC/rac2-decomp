/* Partial layouts measured from the selected-record table and output fields. */
#include "common.h"
typedef struct { char pad[0x38]; int index; char gap[0x2c]; char *records; } Table;
extern Table ref_L00_002E6A60_00;
extern float ref_L00_002E6A60_01;
typedef struct { float x, y, z, w; } Vec;
typedef struct { char pad[0x140]; Vec position; char gap[0x220]; Vec basis[3]; } Output;
extern Output ref_L00_002E6A60_02;
extern void UpdateViewContext(void);
extern void func_00129178(void *);
extern void pad_vib_routine_f(void *, void *, float);
extern void pad_vib_routine_g(void *, void *, float);
extern void pad_vib_routine_e(void *, void *, float);
/* Apply the selected record and build the output basis from its Euler angles. */
int cam_set_from_selected_record(void)
{
    float rotation[16];
    char *rec = ref_L00_002E6A60_00.records + (ref_L00_002E6A60_00.index << 5);
    char *angles = rec + 0x10;
    int result = *(unsigned char *)(rec + 12);
    float *out;
    ref_L00_002E6A60_01 = *(float *)(angles + 12);
    UpdateViewContext();
    out = (float *)&ref_L00_002E6A60_02.position;
    qcopy(out, rec);
    func_00129178(rotation);
    pad_vib_routine_f(rotation, rotation, *(float *)(rec + 16));
    pad_vib_routine_g(rotation, rotation, *(float *)(angles + 4));
    pad_vib_routine_e(rotation, rotation, *(float *)(angles + 8));

    ref_L00_002E6A60_02.basis[0].x = -rotation[8];
    ref_L00_002E6A60_02.basis[1].x = -rotation[0];
    ref_L00_002E6A60_02.basis[2].x = rotation[4];
    ref_L00_002E6A60_02.basis[0].y = -rotation[9];
    ref_L00_002E6A60_02.basis[1].y = -rotation[1];
    ref_L00_002E6A60_02.basis[2].y = rotation[5];
    ref_L00_002E6A60_02.basis[0].z = -rotation[10];
    ref_L00_002E6A60_02.basis[1].z = -rotation[2];
    ref_L00_002E6A60_02.basis[2].z = rotation[6];
    return result;
}
