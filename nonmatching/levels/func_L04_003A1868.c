/* Nonmatching reconstruction. Profile: -O2 -G8 -ffunction-sections -mno-split-addresses.
 * Compiled 384 bytes; retail 384 bytes.
 * USA v1.01, PAL and USA v2.00: 0/5 places per release; no carrying absence.
 * No strict linked qualification. Absolute versus GP declarations and the documented no-split-addresses profile recover the retail size. Independent global-store scheduling, two constant FPR assignments and the initial address/frame schedule differ. Reopen with a truthful shared settings view that preserves measured access widths and order.
 */
extern char D_L04_001C7400[];
extern float D_L04_001AD844[] __attribute__((section(".data")));
extern float D_L04_001AD84C[] __attribute__((section(".data")));
extern float D_L04_001AD854[] __attribute__((section(".data")));
extern float D_L04_001AD858[] __attribute__((section(".data")));
extern float D_L04_001AD840 __attribute__((sda));
extern float D_L04_001AD848[] __attribute__((section(".data")));
extern float D_L04_001AD850[] __attribute__((section(".data")));
extern float D_L04_001AD860[] __attribute__((section(".data")));
extern float D_L04_001AD870[] __attribute__((section(".data")));
extern float D_L04_001AD874[] __attribute__((section(".data")));
extern float D_L04_001AD878[] __attribute__((section(".data")));
extern int D_L04_001B2C70[] __attribute__((section(".data")));
extern int D_L04_001B2C74[] __attribute__((section(".data")));
extern int D_L04_001B2C78[] __attribute__((section(".data")));
extern int D_L04_001AD868[] __attribute__((section(".data")));
extern int D_L04_001AD86C[] __attribute__((section(".data")));
extern unsigned char D_L04_001AD87D[] __attribute__((section(".data")));
extern unsigned char D_L04_001AD87C[] __attribute__((section(".data")));
extern float D_L04_001AD80C __attribute__((sda));
extern float D_L04_001AD810 __attribute__((sda));
extern float D_L04_001AD814 __attribute__((sda));
extern int D_L04_001AD808 __attribute__((sda));
extern float func_00283248(float, float);
extern float func_00283180(float);
extern float func_00283198(float);

void func_L04_003A1868(int first, int second, int third)
{
    float angle;
    char *settings = D_L04_001C7400;
    D_L04_001AD844[0] = 16.0f;
    D_L04_001AD84C[0] = -8.0f;
    D_L04_001AD854[0] = 1.0f;
    D_L04_001AD858[0] = 0.9f;
    D_L04_001AD840 = 16.0f;
    D_L04_001AD848[0] = -8.0f;
    D_L04_001AD850[0] = 1.0f;
    D_L04_001AD860[0] = 0.1f;
    angle = func_00283248(*(float *)(settings + 0x10), *(float *)(settings + 0x14));
    D_L04_001AD870[0] = func_00283180(angle) * 0.5773500204086304f;
    D_L04_001AD874[0] = func_00283198(angle) * 0.5773500204086304f;
    D_L04_001B2C70[0] = first;
    D_L04_001B2C74[0] = second;
    D_L04_001B2C78[0] = third;
    D_L04_001AD878[0] = -0.5773500204086304f;
    D_L04_001AD868[0] = 63;
    D_L04_001AD86C[0] = 64;
    D_L04_001AD87D[0] = 127;
    D_L04_001AD80C = 32768.0f;
    D_L04_001AD810 = 255.0f;
    D_L04_001AD814 = 48.0f;
    D_L04_001AD87C[0] = 127;
    D_L04_001AD808 = 0;
}
