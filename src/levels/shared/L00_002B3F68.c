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

void func_L00_002B3F68(void)
{
    float speed = ((MovementView *)D_00189E20)->speed;
    float first;
    float second;
    float third;
    if (speed == 1.0f) {
        first = 0.022f;
    } else {
        first = speed * 0.02f;
        if (first > 0.022f)
            first = 0.022f;
        if (first < 0.01f)
            first = 0.01f;
    }
    if (((MovementView *)D_00189E20)->speed == 1.0f) {
        third = 0.09308424592018127f;
    } else {
        third = speed * 0.06399541348218918f;
        if (third > 0.09308424592018127f)
            third = 0.09308424592018127f;
        if (third < 0.03199770674109459f)
            third = 0.03199770674109459f;
    }
    second = 0.27f;
    if (((MovementView *)D_00189E20)->alternate) {
        first = 0.035f;
        third = 0.19489513337612152f;
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
                first = 0.017f;
                second = 0.18f;
                third = 0.1454441249370575f;
            } else {
                first = speed * 0.009f;
                second = 0.15f;
                third = speed * 0.07853982597589493f;
            }
        }
        break;
    default:
        break;
    }
    func_L00_002B3EF8(0, first, second, third);
}
