/*Universidad del Valle de Guatemala
  Computacion Paralela y Distribuida
  Jennifer Sandoval   18962
  Luis Quezada        18028
  Esteban del Valle   18221
  Proyecto 1 
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

// Compilar y correr 
// gcc PDESeqv2.c -o PDESeqv2
// ./PDESeqv2 5000 50 30 100 1000000

#define L 5 // Longitud de la barra

double ecuacion(double Ti[],int j, double c,double dt,double x, double tl, double tr, int n);
void copyArray(double arr[], double copy[], int size);
void displayArray(double arr[], int size);


int main(int argc, char* argv[]) {
  clock_t c_clock;
  double t0, tl, tr;
  int N,iterations = 100;
  double c = pow(10, -1);

  if (argc == 1) {
      printf("Usage: PDESeq partes_barra T_inicial T_left T_right iteraciones\n");
      exit (1);
    }

  N =  atoi(argv[1]); // Numero de intervalo discretos
  t0 = strtol(argv[2], NULL, 10); // Temperatura inicial
  tl = strtol(argv[3], NULL, 10); // Temperatura de la frontera izquierda
  tr = strtol(argv[4], NULL, 10); // Temperatura de la frontera derecha
  iterations = atoi(argv[5]);

  // Tiempo POSIX
  c_clock = clock();
  
  // Mitad de la barra para cálculo del error
  int half = (int)((double)N/(double)2);

  // 1. División del dominio en intervalos discretos (tiempo y distancia)
  double deltax = (double)L/(double)N;
  double deltat = (deltax*deltax)/(2*c);

  // 2. Ajustar los valores iniciales de los vectores de solución Ti y Ti+1, para tiempo i
  double Ti[N];
  double Ti_p1[N];

  //Llenar los vectores de temperaturas iniciales y de solucion con la temperatura inicial y 0 respectivamente
  for (int i = 0; i<N; i++){
    Ti[i] = t0;
    Ti_p1[i] = 0;
  }

  // 3. For (resultado en vec_sol)
  for (int i = 1; i <= iterations; i++) {
    for (int j=0; j<N; j++) {
      // Calculo de las temperaturas en cada segmento
      double res = ecuacion(Ti, j, c, deltat, deltax, tl, tr, N);
      Ti_p1[j] = res;
    }
    copyArray(Ti_p1,Ti,N);
  }
  c_clock = clock() - c_clock;
  // Mostrar barra final
  displayArray(Ti,N);

  printf("VALORES: %d %f %f %f %d \n", N,t0,tl,tr, iterations);

  // Mostrar delta de tiempo
  printf("Tiempo: %f\n",((float)c_clock)/CLOCKS_PER_SEC);

  return 0;
}

double ecuacion(double Ti[],int j, double c,double dt,double x, double tl, double tr, int n) {
  double result;
  //Calculo para la primera temperatura
  if(j==0){
    result = Ti[j]+(((c*dt/(x*x)))*(tl-(2*Ti[j])+Ti[j+1]));
  }
  //Calculo para la ultima temperatura
  else if(j==(n-1)){
    result = Ti[j]+(((c*dt/(x*x)))*(Ti[j-1]-(2*Ti[j])+tr));
  }
  //Calculo para las temperaturas del medio
  else{
    result = Ti[j]+(((c*dt/(x*x)))*(Ti[j-1]-(2*Ti[j])+Ti[j+1]));
  }

  return result;
}

// Function to copy the elements of an array in other
void copyArray(double arr[], double copy[], int size)
{
  
  for (int i = 0; i < size; ++i)
  {
    copy[i] = arr[i];
  }
}

// Function to display an array
void displayArray(double arr[], int size){
  for (int i = 0; i < size; i++) {
    printf("%f ",arr[i]);
    }
    printf("\n");
}
