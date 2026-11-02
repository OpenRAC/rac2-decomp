/* functional: medium. Carried from Ratchet & Clank (func_001F9938, FastDecTimer); same instructions as rac1's. Countdown timer tick on a 16-bit counter: a counter already at 0 returns 1 and is left alone; otherwise the counter (clamped up to 1 first, so negatives count as 1) is decremented and stored, returning 0 while it is still above 0 and 2 on the tick that reaches 0. */
int func_00282978(short *timer) {
    int t = *timer;
    if (t == 0) {
        return 1;
    }
    if (t < 1) {
        t = 1;
    }
    t--;
    *timer = (short)t;
    return t > 0 ? 0 : 2;
}
