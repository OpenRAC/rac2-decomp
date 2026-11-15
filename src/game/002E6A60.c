/* Partial layouts measured from the selected-record table and output fields. */
#include "common.h"
typedef struct { char pad[0x38]; int index; char gap[0x2c]; char *records; } Table;
extern Table ref_L00_002E6A60_00;
extern float ref_L00_002E6A60_01;
typedef struct { float x, y, z, w; } Vec;
typedef struct { char pad[0x140]; Vec position; char gap[0x220]; Vec basis[3]; } Output;
extern Output ref_L00_002E6A60_02;
extern void func_0027AB40(void);
extern void func_00129178(void *);
extern void func_001292C0(void *, void *, float);
extern void func_00129368(void *, void *, float);
extern void func_00129218(void *, void *, float);
/* Apply the selected record and build the output basis from its Euler angles. */
int func_002E6A60(void)
{
    float m[16];
    char *rec = ref_L00_002E6A60_00.records + (ref_L00_002E6A60_00.index << 5);
    char *angles = rec + 0x10;
    int result = *(unsigned char *)(rec + 12);
    float *out;
    ref_L00_002E6A60_01 = *(float *)(angles + 12);
    UpdateViewContext();
    out = (float *)&ref_L00_002E6A60_02.position;
    qcopy(out, rec);
    func_00129178(m);
    func_001292C0(m, m, *(float *)(rec + 16));
    func_00129368(m, m, *(float *)(angles + 4));
    func_00129218(m, m, *(float *)(angles + 8));

    ref_L00_002E6A60_02.basis[0].x = -m[8];
    ref_L00_002E6A60_02.basis[1].x = -m[0];
    ref_L00_002E6A60_02.basis[2].x = m[4];
    ref_L00_002E6A60_02.basis[0].y = -m[9];
    ref_L00_002E6A60_02.basis[1].y = -m[1];
    ref_L00_002E6A60_02.basis[2].y = m[5];
    ref_L00_002E6A60_02.basis[0].z = -m[10];
    ref_L00_002E6A60_02.basis[1].z = -m[2];
    ref_L00_002E6A60_02.basis[2].z = m[6];
    return result;
}
