#include "include_asm.h"
#include "names.h"

/* func_002D16C8 needs 20-byte menu table in small data (-G32) and quadword copy (-frac2-qcopy). */

typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;
typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;
typedef int TI128 __attribute__((mode(TI)));

extern SelectionCallback D_001F2840;
extern CallbackMenuState D_00138180;
extern int func_002E5E58(int, unsigned int, void *);
extern void func_0028B338(int);
extern char *func_0029EFD0(int);
extern int D_001ABA3C __attribute__((sda));
extern int D_001ABA40[5] __attribute__((sda));
extern short D_001A63AC[];
extern char D_00189EA0[];
extern int D_0025C780[], D_0025C970[], D_0025CB60[];
typedef struct { char reserved00[0x10]; int flags; } FlagTarget;
typedef struct { char reserved00[0x44]; int f44; int f48; int f4c; int f50; int f54; int f58; } MenuFields;
extern MenuFields D_0025C718;
extern FlagTarget *D_0025C6D8[];

/* Handles input on the five-entry Extras page: opens a sub-page or spawns a special object for the chosen entry. */
int func_002D16C8(void)
{
    int flags = ((CallbackMenuState *)&gPadState)->flags;
    int oldCursor = D_001ABA3C;
    int result = 0;

    if (flags & 0x10) {
        int value;
        int returnCode;
        D_001ABA3C = 0;
        value = *(int *)(gPauseMenuState.source + 0xE0);
        if (value != 0)
            gPauseMenuState.value = value;
        else if (gPauseMenuState.fallback == 0) {
            returnCode = -1;
            goto finish;
        }
        returnCode = 0;
finish:
        return returnCode;
    }
    if (flags & 0x900) {
        D_001ABA3C = 0;
        result = 1;
    } else {
        if (flags & 0x1000) {
            PlaySoundFromGlobalBank(3, 0, 0);
            if (--D_001ABA3C < 0)
                D_001ABA3C = 4;
        } else if (flags & 0x4000) {
            PlaySoundFromGlobalBank(3, 0, 0);
            if (++D_001ABA3C >= 5)
                D_001ABA3C = 0;
        }
        if (((CallbackMenuState *)&gPadState)->flags & 0x40) {
            if (D_001ABA40[D_001ABA3C] != 0) {
                PlaySoundFromGlobalBank(4, 0, 0);
                switch (D_001ABA3C) {
                case 1:
                case 2: {
                    char *obj;
                    select_moby_context(0);
                    obj = CreateMoby(D_001ABA3C == 2 ? 0x88D /* moby class 2189 */ : 0x1335 /* moby class 4917 */);
                    select_moby_context(1);
                    if (obj != 0) {
                        *(unsigned char *)(obj + 0x30) = 0xFF;
                        {
                            TI128 *dst = (TI128 *)(obj + 0x10);
                            TI128 *src = (TI128 *)gHeroPosition;
                            *dst = *src;
                        }
                        result = 1;
                    }
                    break;
                }
                case 0:
                    gPauseMenuState.value = (int)D_0025C780;
                    break;
                case 3:
                    gPauseMenuState.value = (int)D_0025C970;
                    break;
                case 4:
                    gPauseMenuState.value = (int)D_0025CB60;
                    break;
                default:
                    break;
                }
            } else {
                PlaySoundFromGlobalBank(5, 0, 0);
            }
        }
        {
            MenuFields *menu = &D_0025C718;
            menu->f58 = D_001ABA3C;
            if (D_001ABA40[D_001ABA3C] != 0) {
                if (oldCursor == D_001ABA3C) {
                    if (D_001A63AC[0] == 0) {
                        if (menu->f50 == oldCursor && menu->f44 == 2) {
                            D_0025C6D8[0]->flags &= -5;
                        } else if (menu->f54 == oldCursor && menu->f44 == 4) {
                            D_0025C6D8[0]->flags &= -5;
                        }
                    }
                }
            } else {
                D_0025C6D8[0]->flags |= 4;
            }
        }
    }
    return result;
}
