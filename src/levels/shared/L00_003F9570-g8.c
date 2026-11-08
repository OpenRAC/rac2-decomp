#include "common.h"

/* Two level tables read both ways: the first word of each through $gp (the _gp views), the rest
   through the assembler's absolute macro form (incomplete sda arrays). The source vector of the
   first call is its own object at 0x1B0A80, just past the 4-float table at 0x1B0A70: SN builds
   `la table+16` as lui/addiu, but retail has one $gp addiu (owner ruling 8 November 2026). */
extern unsigned int D_L00_001B0A50[] __attribute__((sda));
extern unsigned int D_L00_001B0A50_gp[] SDATA(D_L00_001B0A50);
extern float D_L00_001B0A70[] __attribute__((sda));
extern float D_L00_001B0A70_gp[] SDATA(D_L00_001B0A70);
extern float D_L00_001B0A80[] __attribute__((sda));
extern float D_L00_001B0A80_gp[] SDATA(D_L00_001B0A80);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7878(float, float);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern float func_002A7940(void);
extern void func_00281EB8(void *, int, unsigned int, int, float, float, float);

/* Four particle emissions around the object, each with a colour picked between two table entries. */
void func_L00_003F9570(char *object)
{
    float position[4];
    float *data = *(float **)(object + 0x68);

    func_00283098(position, D_L00_001B0A80_gp, object + 0xC0);
    func_00282CC0(position, position, object + 0x10);
    {
        unsigned int color = func_00283D38(D_L00_001B0A50_gp[0], D_L00_001B0A50[1], func_002A7878(0.0f, 1.0f));
        float size = D_L00_001B0A70_gp[0] * data[0];
        func_00281EB8(position, 0x31, color, 1, size, 0.0f, func_002A7940());
    }
    {
        unsigned int color = func_00283D38(D_L00_001B0A50[2], D_L00_001B0A50[3], func_002A7878(0.0f, 1.0f));
        float size = D_L00_001B0A70[1] * data[0];
        func_00281EB8(position, 0x31, color, 1, size, 0.0f, func_002A7940());
    }
    {
        unsigned int color = func_00283D38(D_L00_001B0A50[4], D_L00_001B0A50[5], func_002A7878(0.0f, 1.0f));
        float size = D_L00_001B0A70[2] * data[0];
        func_00281EB8(position, 0xB, color, 1, size, 0.0f, func_002A7940());
    }
    {
        unsigned int color = func_00283D38(D_L00_001B0A50[5], D_L00_001B0A50[6], func_002A7878(0.0f, 1.0f));
        float size = D_L00_001B0A70[3] * data[0];
        func_00281EB8(position, 0xB, color, 1, size, 0.0f, func_002A7940());
    }
}
