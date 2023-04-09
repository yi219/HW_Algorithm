#include <stdio.h>
#include <stdlib.h>

FILE* fp = NULL;

struct data{
	int m;
  int n;
  char x[100];
  char y[100];
};

struct arr_M{
  int M[101][101];
  int P[100][100];
};

int main(){
  int num=0;
  struct data *d=(struct data*)malloc(sizeof(struct data)*100);
  struct arr_M *p=(struct arr_M*)malloc(sizeof(struct arr_M)*100);
  char *arr=NULL;
  int max[100]={0,};
  int l=0;
  int i=0;
  int j=0;
  int k=0;
  int t=0;
  int penalty=0;
  int min=0;
  int case_n=0;

  fp = fopen("input.txt", "rt");
  
  fscanf(fp, "%d\n", &num);

  for(l=0; l<num; l++){
    fscanf(fp, "%d\n", &d[l].m);
    fscanf(fp, "%s\n", d[l].x+1);
    fscanf(fp, "%d\n", &d[l].n);
    fscanf(fp, "%s\n", d[l].y+1);

    if(d[l].m>d[l].n)
      max[l]=d[l].m;
    else max[l]=d[l].n;

    for(i=d[l].m; i>=0; i--) p[l].M[i][0]=3*i;
    for(j=d[l].n; j>=0; j--) p[l].M[0][j]=3*j;

    for(i=1; i<=d[l].m; i++){
      for(j=1; j<=d[l].n; j++){
        if(d[l].x[i]==d[l].y[j]) penalty=0;
        else penalty=2;

        min=p[l].M[i-1][j-1]+penalty;
        case_n=1;
        if (min>p[l].M[i-1][j]+3) {
          min=p[l].M[i-1][j]+3;
          case_n=2;
        }
        if (min>p[l].M[i][j-1]+3) {
          min=p[l].M[i][j-1]+3;
          case_n=3;
        }

        p[l].M[i][j]=min;
        p[l].P[i][j]=case_n;
      }
    }
  }

  
  for(l=0; l<num; l++){
    i=d[l].m;
    j=d[l].n;
    t=max[l];
    arr=(char*)malloc(sizeof(char)*101);
    for(k=0; k<max[l]; k++){
      if (p[l].P[i][j]==1) {
        arr[t]=d[l].x[i];
        i--; j--;
        t--;
      }
      else if (p[l].P[i][j]==2) {
        arr[t]=d[l].x[i];
        i--;
        t--;
      }
      else if (p[l].P[i][j]==3){
        arr[t]='-';
        j--;
        t--;
      }
      else {
        if(d[l].m>d[l].n){
          arr[t]=d[l].x[i];
        }
        else {
          arr[t]='-';
        }
        i--;
        t--;
      }
    }
    for(i=1; i<=max[l]; i++) {
      printf("%c", arr[i]);
    }
    printf("\n");

    i=d[l].m;
    j=d[l].n;
    t=max[l];
    for(k=0; k<max[l]; k++){
      if (p[l].P[i][j]==1) {
        arr[t]=d[l].y[j];
        i--; j--;
        t--;
      }
      else if (p[l].P[i][j]==2) {
        arr[t]='-';
        i--;
        t--;
      }
      else if (p[l].P[i][j]==3){
        arr[t]=d[l].y[j];
        j--;
        t--;
      }
      else {
        if(d[l].m<d[l].n){
          arr[t]=d[l].y[j];
        }
        else {
          arr[t]='-';
        }
        i--;
        t--;
      }
    }
    for(j=1; j<=max[l]; j++) {
      printf("%c", arr[j]);
    }
    printf("\n");
    free(arr);

    for(i=0; i<=d[l].m; i++){
      for(j=0; j<=d[l].n; j++){
        printf("%-3d", p[l].M[i][j]);
      }
      printf("\n");
    }
  }
}