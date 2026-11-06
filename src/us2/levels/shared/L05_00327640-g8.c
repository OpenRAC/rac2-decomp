/* func_US2_L05_00327640, v2.00's own function (no v1.01 counterpart): while the short at
 * D_0018A000 is not positive, stores its argument plus one in a small level variable, which sits at
 * another address in levels 10 and 15, hence the ref_ name. */
extern short D_0018A000[];
extern int ref_US2_L05_00327640_00 __attribute__((sda));

void func_US2_L05_00327640(int value)
{
    if (D_0018A000[0] <= 0) {
        ref_US2_L05_00327640_00 = value + 1;
    }
}
