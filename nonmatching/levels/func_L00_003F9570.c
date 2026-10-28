/* Nonmatching C reconstruction.
 * Profile: -O2 -G8 -ffunction-sections -mno-split-addresses.
 * Compiled 484 bytes; retail 472 bytes.
 * Carrying checks: 0/3 in us, pal and us2. No strict linked qualification.
 * The four emissions preserve four GPR and three FPR arguments and packed 32-bit colours. The external source vector remains incomplete because a sixteen-byte read alone does not qualify its complete allocation for SDA. Absolute load placement, saved-register/FPR priorities and source-vector address formation differ. Reopen with actual object extent and ABI-consistent scheduling evidence.
 */
#include "common.h"
extern unsigned char D_L00_001B0A80[] MACRO_ADDR;
extern unsigned int D_L00_001B0A50 __attribute__((sda));
extern unsigned int D_L00_001B0A54[] NOT_SDA;
extern unsigned int D_L00_001B0A58[] NOT_SDA;
extern unsigned int D_L00_001B0A5C[] NOT_SDA;
extern unsigned int D_L00_001B0A60[] NOT_SDA;
extern unsigned int D_L00_001B0A64[] NOT_SDA;
extern unsigned int D_L00_001B0A68[] NOT_SDA;
extern float D_L00_001B0A70 __attribute__((sda));
extern float D_L00_001B0A74[] NOT_SDA;
extern float D_L00_001B0A78[] NOT_SDA;
extern float D_L00_001B0A7C[] NOT_SDA;
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7878(float, float);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern float func_002A7940(void);
extern void func_00281EB8(void *, int, unsigned int, int, float, float, float);

void func_L00_003F9570(char *object)
{
    float position[4];
    float *data = *(float **)(object + 0x68);
    unsigned int color;
    float size;
    func_00283098(position, D_L00_001B0A80, object + 0xC0);
    func_00282CC0(position, position, object + 0x10);
    color = func_00283D38(D_L00_001B0A50, D_L00_001B0A54[0], func_002A7878(0.0f, 1.0f));
    size = D_L00_001B0A70 * data[0];
    func_00281EB8(position, 0x31, color, 1, size, 0.0f, func_002A7940());
    color = func_00283D38(D_L00_001B0A58[0], D_L00_001B0A5C[0], func_002A7878(0.0f, 1.0f));
    size = D_L00_001B0A74[0] * data[0];
    func_00281EB8(position, 0x31, color, 1, size, 0.0f, func_002A7940());
    color = func_00283D38(D_L00_001B0A60[0], D_L00_001B0A64[0], func_002A7878(0.0f, 1.0f));
    size = D_L00_001B0A78[0] * data[0];
    func_00281EB8(position, 0xB, color, 1, size, 0.0f, func_002A7940());
    color = func_00283D38(D_L00_001B0A64[0], D_L00_001B0A68[0], func_002A7878(0.0f, 1.0f));
    size = D_L00_001B0A7C[0] * data[0];
    func_00281EB8(position, 0xB, color, 1, size, 0.0f, func_002A7940());
}
