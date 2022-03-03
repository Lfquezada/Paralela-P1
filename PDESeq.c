#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// gcc PDESeq.c -o PDESeq
// ./PDESeq 0.0001 5 30 10 100

//#define n 10
#define N 10
#define L 50

int main(int argc, char* argv[]) {
  double err, t0, tl, tr;
  //int N=n;
  //const int N = 10;
  double c = pow(10, -5);
  //const int L = 50;
  double vec_sol;

  if(argc > 1) {
    err = strtol(argv[1], NULL, 10); // Valor de error
    //N = strtol(argv[2], NULL, 10); // Numero de intervalo discretos
    t0 = strtol(argv[3], NULL, 10); // Temperatura inicial
    tl = strtol(argv[4], NULL, 10); // Temperatura de la frontera izquierda
    tr = strtol(argv[5], NULL, 10); // Temperatura de la frontera derecha
  }

  printf("VALORES: %f %d %f %f %F\n", err,N,t0,tl,tr);


  // 1. División del dominio en intervalos discretos (tiempo y distancia)

  const int intervalos = L/N;

  // 2. Ajustar los valores iniciales de los vectores de solución Ti y Ti+1, para tiempo i
  //double Ti_p1[N] = { 0 };

  double Ti[N] = {t0};
  double Ti_p1[N] = {0};

  //double Ti[N] = {t0};
  memcpy(Ti, (int[]){ t0 }, N*sizeof(int));

  

  // 3. For (resultado en vec_sol)

  while (err > (1000)) {
    for (int j = 1; j <= N-1; j++) {
      double Ti_p1[N] = {0};  //Cada iteracion de tiempo reiniciar el vector de resultados en 0
      for (int i=0; i<N; i++){
        //Calculo de las temperaturas
      }
    }
  }

  printf("Vector solución: %f\n", vec_sol);

  return 0;
}

double ecuacion(double Tj, double c, double ti, double x, double Tjp1, double Tjm1) {
  return Tj;
}