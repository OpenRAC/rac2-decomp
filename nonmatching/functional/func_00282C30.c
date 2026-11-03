/* functional: high. Integer absolute value (retail: neg when negative); the negation is done unsigned so the host has no overflow (retail's sub would trap on 0x80000000, never seen). */
int func_00282C30(int x)
{
    if (x < 0) {
        return (int)(0u - (unsigned int)x);
    }
    return x;
}
