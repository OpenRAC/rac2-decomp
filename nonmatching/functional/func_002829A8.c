/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* 28 October 2026: functional C adapted from RAC1's equivalent timer
 * reconstruction. It compiles to 48 bytes but matches 0/28 placements.
 * Retail uses pmaxw on $at in the beqz delay slot; blocker 52 records that
 * this compiler never emits pmaxw from C. Leave the source marker in place
 * pending maintainer review of the original-assembly evidence.
 */
int func_002829A8(unsigned char *p)
{
    if (*p == 0)
        return 1;
    if (*p - 1 > 0) {
        *p = *p - 1;
        return 0;
    }
    *p = 0;
    return 2;
}
