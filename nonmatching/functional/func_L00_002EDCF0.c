/* functional: high. Unchecked: no capture calls it (the gate finds no states). Read against all 4 retail instructions of level 00's copy (lwc1 $f0,-0x76DC($gp) = D_001A7914; jr; mul.s $f0,$f0,$f12): the same product, D_001A7914 * a0. */
/* func_L00_002EDCF0 (16 bytes): returns D_001A7914 * a0 (twin of func_L00_002EDCB8). */
extern float D_001A7914 __attribute__((sda));

float func_L00_002EDCF0(float a0)
{
    return D_001A7914 * a0;
}
