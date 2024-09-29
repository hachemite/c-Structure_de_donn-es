#include <stdio.h>

void fixerAdix(int **ptr) {
  **ptr = 10;
}
int main() {
  int x = 5;
  int *ptr = &x;
  printf("La valeur de x est : %d\n", x);
  fixerAdix (&ptr);
  printf("La nouvelle valeur de x est : %d\n", x);
  return 0;
}

