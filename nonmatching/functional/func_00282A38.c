/* functional: high. A busy-wait: retail spins six nops per pass while n > 0, n going down by 2; it touches no memory and returns nothing, so the loop has no effect but time. */
void func_00282A38(int n)
{
    while (n > 0) {
        n -= 2;
    }
}
