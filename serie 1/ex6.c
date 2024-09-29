#include<stdio.h>

int swap(int *ptr1, int *ptr2){
    int c = *ptr1;
    * ptr1 = *ptr2;
    *ptr2 = c;
}

int main(){
    int a,b;
    scanf("%d %d",&a,&b);

    printf("1:a=%d \tb=%d\n",a,b);

    swap(&a,&b);
    printf("2:a=%d \tb=%d\n",a,b);

    return 0;
}
