#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// gcc PDESeq.c -o PDESeq
// ./PDESeq 1 10 100 200 10000

//#define n 10
#define N 10
#define L 5
double ecuacion(double Ti[],int j, double c,double dt,double x, double tl, double tr, int n);
void copyArray(double arr[], double copy[], int size);
void displayArray(double arr[], int size);


int main(int argc, char* argv[]) {
  double err, t0, tl, tr;
  int teri =100;
  int cont = 0;

  //int N=n;
  //const int N = 10;
  double c = pow(10, -5);
  //const int L = 50;
  double vec_sol;

  if(argc > 1) {
    printf("\n");
    err = strtol(argv[1], NULL, 10); // Valor de error
    //N = strtol(argv[2], NULL, 10); // Numero de intervalo discretos
    t0 = strtol(argv[2], NULL, 10); // Temperatura inicial
    tl = strtol(argv[3], NULL, 10); // Temperatura de la frontera izquierda
    tr = strtol(argv[4], NULL, 10); // Temperatura de la frontera derecha
    teri = atoi(argv[5]);
  }

  printf("VALORES: %f %f %f %F %d \n", err,t0,tl,tr, teri);
  printf("\n");


  // 1. División del dominio en intervalos discretos (tiempo y distancia)

  const int intervalos = L/N;

  // 2. Ajustar los valores iniciales de los vectores de solución Ti y Ti+1, para tiempo i
  //double Ti_p1[N] = { 0 };
  double Ti[N];
  double Ti_p1[N];
  for (int i = 0; i<N; i++){
    Ti[i] = t0;
    Ti_p1[i] = 0;

  }


  //double Ti[N] = {t0};
  //Por si acaso
  //memcpy(Ti, (int[]){ t0 }, N*sizeof(int));

  
   //displayArray(Ti,N);
  // 3. For (resultado en vec_sol)
  printf("%d", teri);
  printf("\n");
  printf("%d",cont);
  printf("\n");
  while (cont < teri) {
    for (int i = 1; i <= N-1; i++) {
      double Ti_p1[N] = {0};  //Cada iteracion de tiempo reiniciar el vector de resultados en 0
      for (int j=0; j<N; j++){
        //Calculo de las temperaturas
        double res = ecuacion(Ti, j, c, i, L, tl, tr, N);
        Ti_p1[j]=res;
      }
      //displayArray(Ti,N);
      copyArray(Ti_p1,Ti,N);
  

    }
    cont++;
  }

  displayArray(Ti,N);
  printf("\n");

  return 0;
}

double ecuacion(double Ti[N],int j, double c,double dt,double x, double tl, double tr, int n) {
  double result;
  if(j==0){
    result = Ti[j]+(((c*dt/(x*x)))*(tl-(2*Ti[j])+Ti[j+1]));
  }

  else if(j==(n-1)){
    result = Ti[j]+(((c*dt/(x*x)))*(Ti[j-1]-(2*Ti[j])+tr));
  }

  else{
    result = Ti[j]+(((c*dt/(x*x)))*(Ti[j-1]-(2*Ti[j])+Ti[j+1]));
  }

  return result;
}


void copyArray(double arr[], double copy[], int size)
{
  // loop to iterate through array
  for (int i = 0; i < size; ++i)
  {
    copy[i] = arr[i];
  }
}

// function to display an array
void displayArray(double arr[], int size){
  for (int i = 0; i < size; i++) {
    printf("%f ",arr[i]);
    }
    printf("\n");
}