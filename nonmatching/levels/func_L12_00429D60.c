/* Nonmatching C reconstruction.
 * Profile: -O2 -G8 -ffunction-sections.
 * Compiled 228 bytes; retail 228 bytes.
 * USA v1.01, PAL and USA v2.00: 0/3 places in each release.
 * No applicable carrying place was absent; no strict-build qualification.
 * Right size; object/value/position saved-register priorities and size/one FPR assignments differ. Reopen with measured allocator evidence; do not permute physical argument banks.
 */
extern float D_L12_001B2328 __attribute__((sda));
extern float D_L12_001B232C __attribute__((sda));
extern int D_L12_001B22E4 __attribute__((sda));
extern int D_L12_001B22E8 __attribute__((sda));
extern int D_L12_001B2320 __attribute__((sda));
extern int D_L12_001B2324 __attribute__((sda));
extern int func_002A7820(int, int);
extern float func_002A7940(void);
extern void func_L12_00429ED8(void *, int, int, int, int, void *, float, float, float);

void func_L12_00429D60(char *object)
{
    float size;
    int value;
    char *position = object + 0x10;
    size = D_L12_001B2328 * *(float *)(object + 0x2C);
    value = func_002A7820(0x5F, 0x6F);
    func_L12_00429ED8(position, D_L12_001B22E4, value,
                     D_L12_001B2320, 2, object, size, func_002A7940(), 1.0f);
    size = D_L12_001B2328 * *(float *)(object + 0x2C) * D_L12_001B232C;
    value = func_002A7820(0x6F, 0x7F);
    func_L12_00429ED8(position, D_L12_001B22E8, value,
                     D_L12_001B2324, 2, object, size, func_002A7940(), 1.0f);
}
