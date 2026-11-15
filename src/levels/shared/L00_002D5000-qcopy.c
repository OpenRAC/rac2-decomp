#include "include_asm.h"
#include "names.h"

#ifndef RAC2_T_V4_F6A70B950
#define RAC2_T_V4_F6A70B950
typedef int V4_F6a70b950 __attribute__((mode(TI)));
#endif

extern void moby_transform_joint_point(char *, int, char *);

extern void copy_matrix3x4(void *, void *);

extern void func_002A10E8(void *);

extern void PackPose(void *, void *, int, int, void *);

extern char ref_L00_002D5000_00[];

extern char ref_L00_002D5000_01[];

/* Fills a 0x40 stack block through the engine, copies its last 16 bytes into the
   record at +0x10, hands the record's +0xC0 and then the record itself to two more
   setters, queues one five-argument request and stamps four resident words. */
/* Sets up a record from an object: copies its position, queues a level request and clears two fields. */
void level_init_record_from_object(char *object, char *record)
{
    char block[0x40];
    V4_F6a70b950 *dst;
    V4_F6a70b950 *src;

    moby_transform_joint_point(object, 4, block);
    dst = (V4_F6a70b950 *)(record + 0x10);
    src = (V4_F6a70b950 *)(block + 0x30);
    *dst = *src;
    copy_matrix3x4(record + 0xC0, block);
    func_002A10E8(record);
    PackPose(ref_L00_002D5000_00, ref_L00_002D5000_01,
                *(int *)(record + 0x24), 0, object);
    *(void **)(record + 0x58) = ref_L00_002D5000_01;
    *(void **)(record + 0x5C) = ref_L00_002D5000_01;
    *(int *)(record + 0x44) = 0;
    *(int *)(record + 0x40) = 0;
}
