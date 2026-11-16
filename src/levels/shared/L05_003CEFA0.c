#include "common.h"
extern char *CreateMoby(int);
extern void moby_randomize_reach_and_angles(char *);
extern int moby_class_id_to_table_index(int);
extern float g_shot_reach_table[] SDATA(D_L05_001AFB68);

/* Spawns one flying piece of a given kind at a position, sized to match its owner. */
char *func_L05_003CEFA0(char *owner,void *position,int kind)
{
    char *object=CreateMoby(kind);
    if (object) {
        char *state=*(char **)(object+0x68);
        int index;
        qcopy(object+0x10,position);
        qzero(state+0x10);
        object[0x31]=1;
        moby_randomize_reach_and_angles(object);
        object[0x20]=1;
        *(u64 *)(object+0x38)=*(u64 *)(owner+0x38);
        index=moby_class_id_to_table_index(*(short *)(object+0xAA));
        *(float *)(object+0x2C) *= g_shot_reach_table[index];
    }
    return object;
}
