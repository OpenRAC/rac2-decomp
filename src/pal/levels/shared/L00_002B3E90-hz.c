/* func_PAL_L00_002B3E90, the PAL copy of func_L00_002B3F68: the same C, where 0.022f becomes
   0.031680003f; 0.02f becomes 0.028800001f; 0.01f becomes 0.014400001f; 0.09308424592018127f
   becomes 0.11170109f; 0.06399541348218918f becomes 0.0767945f; 0.03199770674109459f becomes
   0.03839725f; 0.27f becomes 0.38880002f; 0.035f becomes 0.050400004f; 0.19489513337612152f
   becomes 0.23387417f; 0.017f becomes 0.024480002f; 0.18f becomes 0.2592f; 0.1454441249370575f
   becomes 0.17453296f; 0.009f becomes 0.01296f; 0.15f becomes 0.21600002f; 0.07853982597589493f
   becomes 0.094247796f. */
typedef struct {
    unsigned char prefix[0x40F];
    unsigned char alternate;
    unsigned char gap[0x1EA8];
    unsigned char special;
    unsigned char gap2[0x1FF];
    float speed;
} MovementView;
extern char D_00189E20[];
extern int func_L00_002ADEA0(int index);
extern void func_L00_002B3EF8(int index, float a, float b, float c);

void func_PAL_L00_002B3E90(void)
{
    float speed = ((MovementView *)D_00189E20)->speed;
    float first;
    float second;
    float third;
    if (speed == 1.0f) {
        first = 0.031680003f;
    } else {
        first = speed * 0.028800001f;
        if (first > 0.031680003f)
            first = 0.031680003f;
        if (first < 0.014400001f)
            first = 0.014400001f;
    }
    if (((MovementView *)D_00189E20)->speed == 1.0f) {
        third = 0.11170109f;
    } else {
        third = speed * 0.0767945f;
        if (third > 0.11170109f)
            third = 0.11170109f;
        if (third < 0.03839725f)
            third = 0.03839725f;
    }
    second = 0.38880002f;
    if (((MovementView *)D_00189E20)->alternate) {
        first = 0.050400004f;
        third = 0.23387417f;
    }
    switch (func_L00_002ADEA0(0)) {
    case 16:
    case 28:
    case 29:
    case 30:
    case 39:
    case 46:
        if (((MovementView *)D_00189E20)->special && !((MovementView *)D_00189E20)->alternate) {
            if (speed > 0.95f) {
                first = 0.024480002f;
                second = 0.2592f;
                third = 0.17453296f;
            } else {
                first = speed * 0.01296f;
                second = 0.21600002f;
                third = speed * 0.094247796f;
            }
        }
        break;
    default:
        break;
    }
    func_L00_002B3EF8(0, first, second, third);
}
