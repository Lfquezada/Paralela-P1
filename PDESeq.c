#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char* argv[]) {
  double err, t0, tl, tr;
  int N;
  double c = pow(10, -5);

  if(argc > 1) {
    err = strtol(argv[1], NULL, 10); // Valor de error
    N = strtol(argv[2], NULL, 10); // Numero de intervalo discretos
    t0= strtol(argv[3], NULL, 10); // Temperatura inicial
    tl= strtol(argv[4], NULL, 10); // Temperatura de la frontera izquierda
    tr= strtol(argv[5], NULL, 10); // Temperatura de la frontera derecha
  }

  printf("VALORES: %f %d %f %f %F", err,N,t0,tl,tr);


  return 0;
}