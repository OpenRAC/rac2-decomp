/* functional: high (fcheck covers 1 call only). Reconstruction from a 560/564-byte near miss; same calls in order with the same arguments; globals addressed absolutely instead of via $gp. */

extern void func_0033AE28(char *);
extern void func_0033B018(float **, float, float);
extern void func_00335E38(unsigned char *, float, float, float, float);
extern char *func_002DF1F8(char *, int);
extern int func_00288FB8(int);
extern void func_00336A38(int, unsigned int);
extern void func_0033EC98(char *);
extern int func_002D6F38(int);
extern char D_001C4FA0[];
extern int D_00258D70[][2];
extern char D_001ADC88[];extern float D_001ADF28;
extern float D_001ADF2C;
extern float D_001ADF30;
extern float D_001ADF34;
extern float D_001ADF38;
extern float D_001ADF3C;
extern float D_001ADF50;
extern float D_001ADF54;
extern float D_001ADF58;
extern float D_001ADF5C;
extern float D_001ADF48;
extern float D_001ADF4C;
extern float D_001ADF40;
extern float D_001ADF44;

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
    func_002DF1F8(object + 0x5C0, *(int *)(D_001C4FA0 + 0x230));
    id = D_00258D70[*(int *)(D_001C4FA0 + 0x230)][1];
    if (id >= 0)
        func_00336A38((int)label, func_00288FB8(id));
    else
        func_00336A38((int)label, (unsigned int)D_001ADC88);
    func_0033EC98(object);
    func_002D6F38(0);
    return (flags >> 6) & 1;
}
