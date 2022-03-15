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
#include <omp.h>

// Compilar y correr 
// gcc-11 PDEPar.c -fopenmp -o PDEPar
// gcc PDEPar.c -fopenmp -o PDEPar
// ./PDEPar 5000 50 30 100 1000 16

#define L 5 // Longitud de la barra

double ecuacion(double Ti[],int j, double c,double dt,double x, double tl, double tr, int n);
void copyArray(double arr[], double copy[], int size);
void displayArray(double arr[], int size);


int main(int argc, char* argv[]) {
  double t0, tl, tr; //Declaracion de variables de temperatura inicial, temperatura extremo izquierdo y temperatura extremo derecho
  int N,iterations = 100;
  double c = pow(10, -1);
  

  if (argc == 1) {
      printf("Usage: PDEPar partes_barra T_inicial T_left T_right iteraciones\n");
      exit (1);
  }

  N =  atoi(argv[1]); // Numero de intervalo discretos
  t0 = strtol(argv[2], NULL, 10); // Temperatura inicial
  tl = strtol(argv[3], NULL, 10); // Temperatura de la frontera izquierda
  tr = strtol(argv[4], NULL, 10); // Temperatura de la frontera derecha
  iterations = atoi(argv[5]);
  int thread_count = atoi(argv[6]);
  omp_set_num_threads(T);

  //printf("VALORES: %f %f %f %f %d \n", N,t0,tl,tr, iterations);

  // Tiempo paralelo con omp
  double t_ini = omp_get_wtime();
  
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

double temp_extremos[2*N] = {}; //Array de tamaño 2N en el cual se encuentran las temperaturas de los extremos para segmento de la barra
  for (int i = 1; i <= iterations; i++) {
    for (int j=0; j<N; j++) {
      // Calculo de las temperaturas
      int thread_ID = omp_get_thread_num(); // Obteniendo el ID del hilo que se está ejecutando
      double res = ecuacion(Ti, j, c, deltat, deltax, tl, tr, N);
      Ti_p1[j] = res;
      
    }
    copyArray(Ti_p1,Ti,N);
  }

  // Mostrar barra final
  displayArray(Ti,N);

  // Mostrar delta de tiempo
  double t_fin = omp_get_wtime();
  printf("Tiempo: %f\n",(t_fin - t_ini));

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

// Funcion que sirve para copiar los elementos de un array en otro
void copyArray(double arr[], double copy[], int size)
{
  
  for (int i = 0; i < size; ++i)
  {
    copy[i] = arr[i];
  }
}

// Funcion que sirve para mostrar el contenido de un array
void displayArray(double arr[], int size){
  for (int i = 0; i < size; i++) {
    printf("%f ",arr[i]);
    }
    printf("\n");
}
