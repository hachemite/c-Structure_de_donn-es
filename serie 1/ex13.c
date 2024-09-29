#include <stdio.h>
#include <stdlib.h>

int main() {
    char* chaine;

    chaine = (char*)malloc(100 * sizeof(char));

    if (chaine == NULL) {
        printf("Allocation de mémoire échouée.\n");
        return 1;
    }

    printf("Entrez une chaine de caracteres : ");
    scanf("%s", chaine);

    printf("Vous avez saisi : %s\n", chaine);

    free(chaine);

    return 0;
}
