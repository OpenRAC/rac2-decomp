#include "include_asm.h"
#include "names.h"

/* Copies a block of bytes from one place to another. */
void mem_copy_bytes_2(void *dest, const void *src, int n)
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

extern int CdStartRead(int, int, void *, unsigned char *);
extern void snd_clear_flag_and_update(void);
extern int snd_Pump(void);
extern int snd_CheckLoadInProgress(int);

/* Sets up a load request with fixed settings and starts it. */
void load_start_request(int first, int second, void *third) {
    int enabled = 1;
    unsigned char mode[16];
    mode[0] = 32;
    mode[1] = enabled;
    mode[2] = 0;
    mode[3] = 0;
    CdStartRead(first, second, third, mode);
    snd_clear_flag_and_update();
    snd_Pump();
    snd_CheckLoadInProgress(0);
}

extern void load_start_request(int, int, void *);
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
extern CopySetupData g_copy_setup_data;

/* Starts loading the default data set into the shared data area. */
void load_default_copy_setup(void) {
    load_start_request(1001, 11, &g_copy_setup_data);
}

/* Loads the three data parts for an entry and copies each into the shared data area. */
void load_copy_setup_entry(int index, void *buffer) {
    load_start_request(g_copy_setup_data.rows[index].first, 1, buffer);
    mem_copy_bytes_2(g_copy_setup_data.first, buffer, 0x60);
    load_start_request(g_copy_setup_data.rows[index].second, 3, buffer);
    mem_copy_bytes_2(g_copy_setup_data.second, buffer, 0x1018);
    load_start_request(g_copy_setup_data.rows[index].third, 3, buffer);
    mem_copy_bytes_2(g_copy_setup_data.third, buffer, 0x137C);
}
