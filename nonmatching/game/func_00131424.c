/* func_00131424 - 268 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   draft.c compiles (264 vs 268 bytes). Retail keeps `daddu s3,zero,zero` in a
   saved reg (used as func_123028 arg2 and
   r.result when mode==0); GCC folds the zero (sd $zero / a1 zero) in my C.
   Regs then shift (s1<->s2, s4 holds %hi of D_0013BF10).
   Tried: zero as long long/int/unsigned local declared at top. */

extern long long func_001310C0(void);
extern int func_001313C8(long long);
extern int *func_00115200(void);
extern int D_0013BF10;
extern char D_0013BF28[];
extern long long D_0013BF30;

typedef struct {
    int op;
    void *name;
    long long arg0;
    long long arg1;
    long long result;
    int err;
} Request;

long long func_00131424(long long a0)
{
    Request r;
    long long ret = func_001310C0();
    int mode = D_0013BF10;
    unsigned zero = 0;

    if (mode != -1 && func_001313C8(a0) == 0) {
        if (func_00123028(a0, zero) < 0) {
            r.op = 1;
            r.name = D_0013BF28;
            r.arg0 = a0;
            r.err = 0;
            r.arg1 = a0;
            if (mode == 0) {
                r.result = zero;
            } else {
                r.result = D_0013BF30;
            }
            if (D_0013BF10 != 2 && func_00131400(&r) == 0) {
                *func_00115200() = 0x21;
            }
            if (r.err != 0) {
                *func_00115200() = r.err;
            }
            return r.result;
        }
    }
    return ret;
}
