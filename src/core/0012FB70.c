

/* Copies one counter in a small state block into the one before it. */
void func_0012FB70(void* state)
{
  *(int*)(state + 8) = *(int*)(state + 12);
}
