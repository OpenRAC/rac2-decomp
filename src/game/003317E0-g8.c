#include "include_asm.h"
#include "names.h"

typedef struct {
    char reserved[0x28];
    int active;
} ActiveData_3317E0;
typedef struct {
    char reserved[0x68];
    ActiveData_3317E0 *data;
} ActiveRoot_3317E0;
extern ActiveRoot_3317E0 *D_001B0A70 __attribute__((sda));

/* Turns on the active flag in the data of the global root object, if there is one. */
void object_set_root_data_active(void) {
    if (D_001B0A70 != 0) D_001B0A70->data->active = 1;
}
