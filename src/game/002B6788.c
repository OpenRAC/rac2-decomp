#include "names.h"
extern char D_00188660[];
extern int D_0014B540[];
extern void func_002B6770(int, long);
extern void func_00132498(void *, int, void (*)(int, long), unsigned long);

/* Starts loading the first sound bank and stores the result in its status slot when done. */
void func_002B6788(void) {
    char *statusBase = gSoundState;
    int *soundTable = gCopySetupData;
    *(unsigned int *)(statusBase + 0x17A0) = 0xFFFFFFFFu;
    StartSoundBankRead((void *)(soundTable[0x14AC] + soundTable[0x14A7]), 0, StoreCallbackResult,
                  (unsigned long)(unsigned int)(statusBase + 0x17A0));
}
