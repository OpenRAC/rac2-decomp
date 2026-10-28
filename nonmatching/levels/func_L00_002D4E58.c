/* func_L00_002D4E58 - 420 bytes.  Worker attempt, 27 October 2026 (draft below).

   404 B vs 420 (level 00). Decoded: set D_L00_001A7CF4=0.875 (1.56 if
   D_001A7A41), D_L00_001A7CF8=1.0 (1.8 if D_001A7A43); if byte
   D_L00_001B16D1==0 { func_00311238(obj,0x18,&D_L00_001B16D0);
   obj+0xAA==0xF6B ? 3 floats=0.92 : D_1B16F8=D_1A7CF4, F4=F0=D_1A7CF4*0.97 };
   if obj+0xAA==0xF6B return; flag ? func_L00_002D4D98 : (D_0018B090 nonzero:
   2 entries at D_L00_001B2D80 stride 0x40, if entry[1]==0
   {func_00311238(obj,0x16+i,entry); +0x20/24/28=0.01f}) then
   func_L00_002D4C28(obj).
   Diffs: retail keeps all constants in $f0 and uses beql with the store in
   the delay slot (value stored once: f0=0.875 preloaded, branch likely); mine
   uses $f1 and plain beqz. D_0018B090 must be an incomplete array to avoid
   $gp; D_L00_001B16D1 likewise (lui, not $gp). Missing 4 insns somewhere in
   the 0.92 / 0.97 stores. */

/* new file src/levels/shared/L00_002D4E58-g8.c (-G8 by name); remove INCLUDE_ASM from L00_002D3798.c. Level data must be checked for ref_L00_002D4E58_kk at other levels (only level 00 compiled so far) */
extern unsigned char D_001A7A41;
extern unsigned char D_001A7A43;
extern int D_0018B090[];
extern float D_L00_001A7CF4 __attribute__((sda));
extern float D_L00_001A7CF8 __attribute__((sda));
extern unsigned char D_L00_001B16D0[];
extern unsigned char D_L00_001B16D1[];
extern float D_L00_001B16F0;
extern float D_L00_001B16F4;
extern float D_L00_001B16F8;
extern unsigned char D_L00_001B2D80[];

extern void func_00311238(char *, int, void *);
extern void func_L00_002D4D98(char *);
extern void func_L00_002D4C28(char *);

void func_L00_002D4E58(char *object, int flag)
{
    float value;
    unsigned char *entry;
    int i;

    value = 0.875f;
    if (D_001A7A41)
        value = 1.56f;
    D_L00_001A7CF4 = value;
    value = 1.0f;
    if (D_001A7A43)
        value = 1.8f;
    D_L00_001A7CF8 = value;
    if (D_L00_001B16D1[0] == 0) {
        func_00311238(object, 0x18, D_L00_001B16D0);
        if (*(short *)(object + 0xAA) == 0xF6B) {
            D_L00_001B16F8 = 0.92f;
            D_L00_001B16F0 = 0.92f;
            D_L00_001B16F4 = 0.92f;
        } else {
            value = D_L00_001A7CF4;
            D_L00_001B16F8 = value;
            value *= 0.97f;
            D_L00_001B16F4 = value;
            D_L00_001B16F0 = value;
        }
    }
    if (*(short *)(object + 0xAA) == 0xF6B)
        return;
    if (flag != 0) {
        func_L00_002D4D98(object);
        return;
    }
    if (D_0018B090[0] != 0) {
        entry = D_L00_001B2D80;
        for (i = 0; i < 2; i++) {
            if (entry[1] == 0) {
                func_00311238(object, i + 0x16, entry);
                *(float *)(entry + 0x20) = 0.01f;
                *(float *)(entry + 0x24) = 0.01f;
                *(float *)(entry + 0x28) = 0.01f;
            }
            entry += 0x40;
        }
    }
    func_L00_002D4C28(object);
}
