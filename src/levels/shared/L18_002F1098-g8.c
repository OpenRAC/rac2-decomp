/* True when the resident flag word is set or the stage byte is 4. */
typedef unsigned char u8;

extern int D_L18_001AFBB0;
extern u8 D_L18_0018C0D4[];

/* Returns 1 when the flag word is set or the stage byte is 4. */
int func_L18_002F1098(void) {
    int result = 0;
    if (D_L18_001AFBB0 != 0 || D_L18_0018C0D4[0] == 4) {
        result = 1;
    }
    return result;
}
