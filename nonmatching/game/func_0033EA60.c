/* func_0033EA60 - retained C reconstruction, not an exact match.
 * Profile: -O2 -G8 -ffunction-sections.
 * Measured in src/game/0033EA60-g8.c: 560/564 bytes.
 * US: 0/28 local places; PAL: ABSENT; US2: ABSENT.
 * No strict linked build was run because no local placement matched.
 * Seven initializer calls agree in instruction order; the menu base lifetime and second-word table addressing still differ. Reopen with independent menu/table layout evidence.
 */

#include "common.h"

extern void func_0033AE28(char *);
extern void func_0033B018(float **, float, float);
extern void func_00335E38(unsigned char *, float, float, float, float);
extern char *func_002DF1F8(char *, int);
extern int func_00288FB8(int);
extern void func_00336A38(int, unsigned int);
extern void func_0033EC98(char *);
extern int func_002D6F38(int);
extern char ref_L00_00434390_00[] __attribute__((sda));
extern int ref_L00_00434390_01[][2];
extern char ref_L00_00434390_02[];extern float D_001ADF28 __attribute__((sda));
extern float D_001ADF2C MACRO_ADDR;
extern float D_001ADF30 __attribute__((sda));
extern float D_001ADF34 MACRO_ADDR;
extern float D_001ADF38 __attribute__((sda));
extern float D_001ADF3C MACRO_ADDR;
extern float D_001ADF50 __attribute__((sda));
extern float D_001ADF54 MACRO_ADDR;
extern float D_001ADF58 __attribute__((sda));
extern float D_001ADF5C MACRO_ADDR;
extern float D_001ADF48 __attribute__((sda));
extern float D_001ADF4C MACRO_ADDR;
extern float D_001ADF40 __attribute__((sda));
extern float D_001ADF44 MACRO_ADDR;

int func_0033EA60(char *object, int flags)
{
    char *first = object + 8;
    char *label = object + 0x578;
    float *position;
    int id;
    func_0033AE28(first);
    position = *(float **)(object + 0x2A8);
    func_0033B018((float **)first, position[0], position[1]);    position = *(float **)(object + 0x2A8);
    func_00335E38((unsigned char *)object + 0x2E8, D_001ADF28 + position[0], D_001ADF2C + position[1], 0.0f, 0.0f);
    position = *(float **)(object + 0x2A8);
    func_00335E38((unsigned char *)object + 0x330, D_001ADF30 + position[0], D_001ADF34 + position[1], 0.0f, 0.0f);
    position = *(float **)(object + 0x2A8);
    func_00335E38((unsigned char *)object + 0x378, D_001ADF38 + position[0], D_001ADF3C + position[1], 0.0f, 0.0f);
    position = *(float **)(object + 0x2A8);
    func_00335E38((unsigned char *)object + 0x2AC, D_001ADF50 + position[0], D_001ADF54 + position[1], 0.0f, 0.0f);
    position = *(float **)(object + 0x2A8);
    func_00335E38((unsigned char *)object + 0x3C0, D_001ADF58 + position[0], D_001ADF5C + position[1], 0.0f, 0.0f);
    position = *(float **)(object + 0x2A8);
    func_00335E38((unsigned char *)object + 0x578, D_001ADF48 + position[0], D_001ADF4C + position[1], 0.0f, 0.0f);
    position = *(float **)(object + 0x2A8);
    func_00335E38((unsigned char *)object + 0x530, D_001ADF40 + position[0], D_001ADF44 + position[1], 0.0f, 0.0f);
    func_002DF1F8(object + 0x5C0, *(int *)(ref_L00_00434390_00 + 0x230));
    id = ref_L00_00434390_01[*(int *)(ref_L00_00434390_00 + 0x230)][1];
    if (id >= 0)
        func_00336A38((int)label, func_00288FB8(id));
    else
        func_00336A38((int)label, (unsigned int)ref_L00_00434390_02);
    func_0033EC98(object);
    func_002D6F38(0);
    return (flags >> 6) & 1;
}