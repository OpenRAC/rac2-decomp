#include "include_asm.h"
#include "names.h"
typedef unsigned char QwenRecovery_84e23fd54f9f_AbiByte16;
extern int moby_step_controller(QwenRecovery_84e23fd54f9f_AbiByte16 *owner, QwenRecovery_84e23fd54f9f_AbiByte16 *input, float factor);

int func_PAL_002B5E30(QwenRecovery_84e23fd54f9f_AbiByte16 *param_1, float factor)
{
    return moby_step_controller(param_1, param_1 + 0x10, factor);
}
