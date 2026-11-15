#include "names.h"


/* Copies one counter in a small state block into the one before it. */
void mpeg_restore_counter(void* state)
{
  *(int*)(state + 8) = *(int*)(state + 12);
}
