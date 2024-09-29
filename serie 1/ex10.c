#include <stdio.h>

long factorielle(int n) {
    if(n==0){
        return 1;
    }
    else{
        return n*factorielle(n-1);
    }
}

int main() {
    int n;
    printf("Entrez un nombre entier : ");
    scanf("%d", &n);
    long fact = factorielle(n);
    printf("La factorielle des chiffres de %d est : %d\n", n, fact);
    return 0;
}
