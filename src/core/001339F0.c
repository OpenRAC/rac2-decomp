#include "include_asm.h"
#include "names.h"

/* Copies a block of bytes from one place to another. */
void func_001339F0(void *dest, const void *src, int n)
{
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    int i = 0;

    if (n <= 0) {
        return;
    }

    do {
        d[i] = s[i];
        i++;
    } while (i < n);
}

extern void func_001334B8(int, int, void *, unsigned char *);
extern void func_00133230(void);
extern void func_00132028(void);
extern void func_00133580(int);

/* Sets up a load request with fixed settings and starts it. */
void func_00133A28(int first, int second, void *third) {
    int enabled = 1;
    unsigned char mode[16];
    mode[0] = 32;
    mode[1] = enabled;
    mode[2] = 0;
    mode[3] = 0;
    CdStartRead(first, second, third, mode);
    ClearSoundFlagAndUpdate();
    snd_Pump();
    snd_CheckLoadInProgress(0);
}

extern void func_00133A28(int, int, void *);
typedef struct {
    int first;
    int reserved04;
    int second;
    int reserved0c;
    int third;
    int reserved14;
} CopySetupRow;
typedef struct {
    char reserved00[0x4FF8];
    CopySetupRow rows[28];
    char first[0x60];
    char second[0x1018];
    char third[0x137C];
} CopySetupData;
extern CopySetupData D_0014B540;

/* Starts loading the default data set into the shared data area. */
void func_00133A78(void) {
    StartLoadRequest(1001, 11, &gCopySetupData);
}

/* Loads the three data parts for an entry and copies each into the shared data area. */
void func_00133AA0(int index, void *buffer) {
    StartLoadRequest(gCopySetupData.rows[index].first, 1, buffer);
    MemcpyBytes(gCopySetupData.first, buffer, 0x60);
    StartLoadRequest(gCopySetupData.rows[index].second, 3, buffer);
    MemcpyBytes(gCopySetupData.second, buffer, 0x1018);
    StartLoadRequest(gCopySetupData.rows[index].third, 3, buffer);
    MemcpyBytes(gCopySetupData.third, buffer, 0x137C);
}
