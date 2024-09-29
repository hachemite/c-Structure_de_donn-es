#include<stdio.h>

int main(){
    int x=15;
    int *ptr =&x;
    *ptr *= 2;


    printf("la résultat est %d",x);



}
