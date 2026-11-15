#include "include_asm.h"
#include "names.h"

/* func_L00_003EFA00 is a unit of its own: it needs the opt-in quadword-copy profile
   (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which gives retail's grouped
   `lq`/`sq` with register addresses for the 16-byte block copied out of the object. */

typedef int TI128 __attribute__((mode(TI)));

extern int func_002B4038(int, int);

extern void func_L00_003EF550(void);

extern void func_0029F338(char *);

extern int func_00283DB8(char *, float);

extern void func_L00_003EFA98(char *);

extern void func_L00_003EFD00(char *);

extern void func_L00_003F0130(char *);

/* Queries the object; on a null answer it resets it and returns, otherwise it works on a
   local copy of its 16-byte block and runs the three update steps. */
/* Runs one frame of the blast effect while the moby is near the camera, and removes the moby
   when its owner is gone. */
void func_L00_003EFA00(char *obj)
{
    char local[16];
    int r;

    r = IsSavedRecordValue(*(short *)(obj + 0xAA), *(int *)(*(int *)(obj + 0x68) + 0x28));
    if (r == 0) {
        ClearEffectRecordsAndFlag();
        MarkMobySpawned(obj);
        return;
    }
    *(TI128 *)local = *(TI128 *)(obj + 0x10);
    *(float *)(local + 0xC) = 2.0f;
    r = FastMathHelperA(local, 100.0f);
    if (r == -1)
        return;
    DrawQuadSphereLarge(obj);
    DrawQuadSphereSmall(obj);
    DrawOwnerEffectRecords(obj);
}
