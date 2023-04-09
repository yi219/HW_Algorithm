#include <stdio.h>
#include <stdlib.h>

struct sudoku{
  int number;
  int board[9][9];
};

FILE* fp = NULL;
int add=0;
struct sudoku list[100];

int check(int i, int row, int col, int x){
  int k=0;
  int u=0;
  int v=0;
  int r=row/3;
  int c=col/3;

  for(k=0; k<9; k++){
    if(list[i].board[k][col]==x) return -1;
    else if(list[i].board[row][k]==x) return -1;
  }

  for(u=r*3; u<r*3+3; u++){
    for(v=c*3; v<c*3+3; v++){
      if(list[i].board[u][v]==x) return -1;
    }
  }

  return 0;
}

void solve(int i){
  int m=0;
  int n=0;
  int x=0;

  for(m=0; m<9; m++){
    for(n=0; n<9; n++){
      if(list[i].board[m][n]==0){
        for(x=1; x<=9; x++){
          if(check(i, m, n, x)==0){
            list[i].board[m][n]=x;
            solve(i);
            if(add==1) return;
            list[i].board[m][n]=0;
          }
        }
        return;
      }
    }
  }

  add=1;
  return;
}

int main(void) {
  fp = fopen("input.txt", "rt");
  int num=0;
  int i=0;
  int m=0;
  int n=0;

  for(i=0; i<100; i++){
    list[i].number=-1;
  }

  fscanf(fp, "%d\n", &num);
  for(i=0; i<num; i++){
    list[i].number=i;
  }

  i=0;
  while(list[i].number!=-1){
    for (m=0; m<9; m++){
      for(n=0; n<9; n++){
        fscanf(fp, "%d ", &list[i].board[m][n]);
      }
    }
    i++;
  }

  for(i=0; i<num; i++){
    solve(i);
    add=0;
  }

  i=0;
  while(list[i].number!=-1){
    printf("sudoku %d\n", list[i].number+1);
    for(m=0; m<9; m++){
      for(n=0; n<9; n++){
        printf("%d ", list[i].board[m][n]);
      }
      printf("\n");
    }
    i++;
  }

}