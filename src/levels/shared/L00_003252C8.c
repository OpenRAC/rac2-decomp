#include "include_asm.h"
#include "names.h"

typedef void *V;

extern int D_001A8FF0;

extern void func_00282C98(V);

extern void func_002AFFD8(V,V,int);

/* Clears the vector, or computes it from the object when the global switch is set. */
void func_L00_003252C8(V object,V vector) {
 if(D_001A8FF0==0) {
  VectorCopyHelperA(vector);
  return;
 }
 ComputeViewDirection(object,vector,1);
}
