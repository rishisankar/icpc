#include <stdio.h>
#include <stdlib.h>

int count[1000001];
int X[101], Y[101];

double left[101], right[101];


int cmp(const void *ap, const void *bp) {
  double a = *(double *)ap;
  double b = *(double *)bp;

  if (a < b) 
    return -1;
  if (a > b) 
    return 1;
  return 0;
}

int main () {
  int x, y, x1, x2, y1, y2;
  int n = 0, i, j, k, m;
  long long int res = 0;

  scanf("%d%d", &X[n], &Y[n]);
  n++;
  while (scanf("%d%d", &x, &y) == 2) {
    X[n] = x; Y[n] = y;
    n++;
  }
  X[n] = X[0]; Y[n] = Y[0];
  n++;

  for (j = 0; j < 1000000; j++) {
    k = 0;
    for (i = 0; i+1 < n; i++) {
      if (X[i] == X[i+1])
	continue;
      if (X[i] < X[i+1]) {
	x1 = X[i]; y1 = Y[i];
	x2 = X[i+1]; y2 = Y[i+1];
      } else if (X[i] > X[i+1]) {
	x2 = X[i]; y2 = Y[i];
	x1 = X[i+1]; y1 = Y[i+1];
      }
      if (j < x1 || x2 < j+1)
	continue;
      left[k] = 1.0*(j-x1)*(y2-y1)/(x2-x1)+y1;
      right[k] = 1.0*(j+1-x1)*(y2-y1)/(x2-x1)+y1;
      k++;
    }
    qsort(left, k, sizeof(double), cmp);
    qsort(right, k, sizeof(double), cmp);
    for (m = 0; m+1 < k; m += 2) {
      int t, b;
      double td, bd;
      b = bd = left[m] < right[m] ? right[m] : left[m];
      t = td = left[m+1] > right[m+1] ? right[m+1] : left[m+1];
      if (b < bd)
	b += 1;
      /*      printf("j %d m %d t %d b %d\n", j, m, t, b); */
      res += t > b ? t-b : 0;
    }
  }  
  printf ("%Ld\n", res);
  return 0;
}