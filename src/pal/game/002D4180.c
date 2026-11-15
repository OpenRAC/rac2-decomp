#include "include_asm.h"
#include "names.h"

typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackState;
extern CallbackState g_pause_menu_state;
extern int D_00138344;
extern void func_0029C8B0(int);

int func_PAL_002D4180(void) {
    int result = 0;
    int flags = D_00138344;
    if (flags & 0x10) {
        int value = *(int *)(g_pause_menu_state.source + 0xE0);
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }
    if (flags & 0x900)
        result = 1;
    else
        func_0029C8B0(flags);
    return result;
}

extern void SetupGifPaging(long);
extern void DoGifPaging(void);
void SetupGifPaging(long);
void DoGifPaging(void);
extern void SetupGifPaging(long arg0);
extern void func_0029C8F0(void);
extern void SetupGifPaging(long param_1);

/* Implementation matching decompiled output */
long func_PAL_002D4208(void)
{
  SetupGifPaging(0);
  func_0029C8F0();
  DoGifPaging();
  return 0;
}

extern void func_0029C960(void);

/* Candidate function: FUN_002d3390 */
unsigned long long func_PAL_002D4308(void)
{
    SetupGifPaging(0);
    func_0029C960();
    DoGifPaging();
    return 0;
}

extern char *D_001A8CFC[] __attribute__((sda));
extern float ref_L00_002D33C0_00[];
extern void ref_L00_002D33C0_01(unsigned char *, float *);
extern char *D_001A8CFC[] __attribute__((sda));
extern char *D_001A8CFC[] __attribute__((sda));

int func_PAL_002D4338(void)
{
    if (D_001A8CFC[0] != 0)
        ref_L00_002D33C0_01((unsigned char *)(D_001A8CFC[0] + 0x3F4A0), ref_L00_002D33C0_00);
    return 0;
}

typedef struct {
    char reserved00[0x1C0];
    int message;
    int flags;
} MenuGameState;
extern MenuGameState g_pad_state;
extern void func_0029C5D0(int);

int func_PAL_002D4378(void)
{
    int flags = g_pad_state.flags;
    int result = 0;
    if (flags & 0x10) {
        int value = *(int *)(g_pause_menu_state.source + 0xE0);
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }
    if (flags & 0x900)
        result = 1;
    else
        func_0029C5D0(g_pad_state.message);
    return result;
}

extern void func_0029C5A0(void);

int func_PAL_002D4400(void) {
    SetupGifPaging(0);
    func_0029C5A0();
    DoGifPaging();
    return 0;
}

