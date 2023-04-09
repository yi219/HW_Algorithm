#include <stdio.h>
#include <time.h>
#include <stdlib.h>

FILE* fp = NULL;

void merge(int arr[], int l, int m, int r)
{
    int *b=(int*)malloc(sizeof(int)*1000000);
    int i, j, k;

    for (i = l; i <= r; i++) {
        b[i] = arr[i];
    }

    i = l; j = m + 1; k = l;

    while (i <= m && j <= r) {
        if (b[i] <= b[j]) {
            arr[k++] = b[i++];
        }
        else
        {
            arr[k++] = b[j++];
        }
    }

    if (i > m) {
        while (j <= r) {
            arr[k++] = b[j++];
        }
    }
    else {
        while (i <= m) {
            arr[k++] = b[i++];
        }
    }
    
    free(b);
}

void mergesort(int arr[], int l, int r) {
    int m;
    if (l < r) {
        m = (l + r) / 2;
        mergesort(arr, l, m);
        mergesort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}


int partition(int arr[], int l, int r) {
    int x = arr[l];
    int i = l + 1;
    int j = r;
    int tmp = 0;
    while (1) {
        while (arr[i] <= x) {
            i++;
        }
        while (arr[j] > x) {
            j--;
        }
        if (i < j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
        else
            break;
    }
    tmp = arr[l];
    arr[l] = arr[j]; arr[j] = tmp;
    return j;
}

void quicksort(int arr[], int l, int r) {
    int p = 0;
    if (l < r) {
        p = partition(arr, l, r);
        quicksort(arr, l, p - 1);
        quicksort(arr, p + 1, r);
    }
}


int main(void) {
    int sort[3] = { 0, };
    int mix[3] = { 0, };
    double sort_Q[3] = { 0, };
    double sort_M[3] = { 0, };
    double n1_m[3]={0,};
    double n2_m[3]={0,};
    double n3_m[3]={0,};    
    double n1_q[3]={0,};
    double n2_q[3]={0,};
    double n3_q[3]={0,}; 
    int *arr_s=(int*)malloc(sizeof(int)*1000000);
    int *arr_m=NULL;
    int *copy_m=NULL;
    int i = 0;
    int j=0;
    int num = 0;
    double sum[3]={0,};
    clock_t start, end;

    fp = fopen("input.txt", "rt");
    srand(time(NULL));

    for (i = 0; i < 3; i++) {
        fscanf(fp, "%d\n", &sort[i]);
    }
    for (i = 0; i < 3; i++) {
        fscanf(fp, "%d\n", &mix[i]);
    }

    for (i = 0; i < sort[2]; i++) {
        arr_s[i] = i;
    }
    for (i = 0; i < 3; i++) {
        start = clock();
        mergesort(arr_s, 0, sort[i] - 1);
        end = clock();
        sort_M[i] = (end - start) / (double)CLOCKS_PER_SEC;
    }
    for (i = 0; i < 3; i++) {
        start = clock();
        quicksort(arr_s, 0, sort[i] - 1);
        end = clock();
        sort_Q[i] = (end - start) / (double)CLOCKS_PER_SEC;
    }
    free(arr_s);


    arr_m=(int*)malloc(sizeof(int)*1000000);
    copy_m=(int*)malloc(sizeof(int)*1000000);


  for(j=0; j<3; j++){
    for(i=0; i<mix[0]; i++) {
      arr_m[i]=rand()%1000000;
      copy_m[i]=arr_m[i];
    }
    start = clock();
    quicksort(arr_m, 0, mix[0] - 1);
    end = clock();
    n1_q[j] = (end - start) / (double)CLOCKS_PER_SEC;

    start = clock();
    mergesort(copy_m, 0, mix[0] - 1);
    end = clock();
    n1_m[j] = (end - start) / (double)CLOCKS_PER_SEC;
  }

  for(j=0; j<3; j++){
    for(i=0; i<mix[1]; i++) {
      arr_m[i]=rand()%1000000;
      copy_m[i]=arr_m[i];
    }
    start = clock();
    quicksort(arr_m, 0, mix[1] - 1);
    end = clock();
    n2_q[j] = (end - start) / (double)CLOCKS_PER_SEC;

    start = clock();
    mergesort(copy_m, 0, mix[1] - 1);
    end = clock();
    n2_m[j] = (end - start) / (double)CLOCKS_PER_SEC;
  }

  for(j=0; j<3; j++){
    for(i=0; i<mix[2]; i++) {
      arr_m[i]=rand()%1000000;
      copy_m[i]=arr_m[i];
    }
    start = clock();
    quicksort(arr_m, 0, mix[2] - 1);
    end = clock();
    n3_q[j] = (end - start) / (double)CLOCKS_PER_SEC;

    start = clock();
    mergesort(copy_m, 0, mix[2] - 1);
    end = clock();
    n3_m[j] = (end - start) / (double)CLOCKS_PER_SEC;
  }

    free(arr_m);
    free(copy_m);

    printf("  sorted      N=%d    N=%d    N=%d\n", sort[0], sort[1], sort[2]);

    printf("Merge Sort   ");
    for (i = 0; i < 3; i++) {
        printf("%f    ", sort_M[i]);
    }
    printf("\n");

    printf("Quick Sort   ");
    for (i = 0; i < 3; i++) {
        printf("%f   ", sort_Q[i]);
    }

    printf("\n");
    printf("\n");
    printf("\n");

    printf("  random              N=%d   N=%d   N=%d\n", mix[0], mix[1], mix[2]);
    printf("Merge Sort   data 1   ");
    printf("%f   ", n1_m[0]);
    printf("%f   ", n2_m[0]);
    printf("%f   ", n3_m[0]);
    printf("\n"); 
    printf("             data 2   ");
    printf("%f   ", n1_m[1]);
    printf("%f   ", n2_m[1]);
    printf("%f   ", n3_m[1]); 
    printf("\n");
    printf("             data 3   ");
    printf("%f   ", n1_m[2]);
    printf("%f   ", n2_m[2]);
    printf("%f   ", n3_m[2]); 
    printf("\n");

    for(i=0; i<3; i++){
      sum[0]+=n1_m[i];
    }
    for(i=0; i<3; i++){
      sum[1]+=n2_m[i];
    }
    for(i=0; i<3; i++){
      sum[2]+=n3_m[i];
    }

    printf("             average  ");
    for(i=0; i<3; i++){
      printf("%.6f   ", (double)sum[i]/3);
    }
    printf("\n");

    printf("Quick Sort   data 1   ");
    printf("%f   ", n1_q[0]);
    printf("%f   ", n2_q[0]);
    printf("%f   ", n3_q[0]);
    printf("\n"); 
    printf("             data 2   ");
    printf("%f   ", n1_q[1]);
    printf("%f   ", n2_q[1]);
    printf("%f   ", n3_q[1]); 
    printf("\n");
    printf("             data 3   ");
    printf("%f   ", n1_q[2]);
    printf("%f   ", n2_q[2]);
    printf("%f   ", n3_q[2]); 
    printf("\n");

    for(i=0; i<3; i++){
      sum[i]=0;
    }

    for(i=0; i<3; i++){
      sum[0]+=n1_q[i];
    }
    for(i=0; i<3; i++){
      sum[1]+=n2_q[i];
    }
    for(i=0; i<3; i++){
      sum[2]+=n3_q[i];
    }

    printf("             average  ");
    for(i=0; i<3; i++){
      printf("%.6f   ", (double)sum[i]/3);
    }
    printf("\n");
}