/* func_L00_00300438 - 468 bytes.  Worker attempt, 27 October 2026 (draft below).

   Replaces the marker in src/levels/shared/L00_002FC7A0.c (default flags).
   Semantics decoded: collect (float)e[1],(float)e[0] pairs (e[0]!=0, stride
   0x20) into an 8-byte pair array on the stack, turn b[] into scaled deltas
   (1/1024), last b = (limit-b)/1024, bubble sort descending on b swapping
   pairs, then func_0026FEB8(D_001A95A0, func_00283CF0(a), func_001234F0(b))
   per element.
   460 vs 468 B. First loop now matches (do/while(--count)). Remaining:
   register naming only plus 2 extra copies: retail n=$t1, last=$a1 (copy $t3,
   copy $t5 for the later loops), stack base $t4, outer index $a0 (caller-
   saved); mine n=$t3, base $t2, index $s1 (callee-saved, extra save/restore
   -> 8 B smaller). Retail also computes last=n-1 before the mtc1 of limit.
   Tried: last as separate var vs reusing count, hoisted float local for
   limit. */

typedef struct {
    float a;
    float b;
} F300438Pair;

extern char D_001A95A0[];
extern int func_00283CF0(float);
extern int func_001234F0(float);
extern void func_0026FEB8(const char *, ...);

void func_L00_00300438(int *entries, int count, int limit) {
    F300438Pair s[512];
    int n = 0;
    int i, j, sorted;
    float fl;

    if (count > 0) {
        do {
            if (entries[0] != 0) {
                s[n].a = (float)entries[1];
                s[n].b = (float)entries[0];
                n++;
            }
            entries += 8;
        } while (--count != 0);
    }
    count = n - 1;
    fl = (float)limit;
    for (i = 0; i < count; i++)
        s[i].b = (s[i + 1].b - s[i].b) * (1.0f / 1024.0f);
    s[count].b = (fl - s[count].b) * (1.0f / 1024.0f);
    do {
        sorted = 1;
        for (j = 0; j < count; j++) {
            if (s[j].b < s[j + 1].b) {
                F300438Pair t = s[j];
                s[j] = s[j + 1];
                s[j + 1] = t;
                sorted = 0;
            }
        }
    } while (!sorted);
    for (i = 0; i < n; i++)
        func_0026FEB8(D_001A95A0, func_00283CF0(s[i].a), func_001234F0(s[i].b));
}
