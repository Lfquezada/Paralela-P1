/*Universidad del Valle de Guatemala
  Computacion Paralela y Distribuida
  Jennifer Sandoval   18962
  Luis Quezada        18028
  Esteban del Valle   18221
  Proyecto 1 
  Programa paralelo
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <omp.h>

// Compilación y ejecución:
// gcc-11 PDEPar.c -fopenmp -o PDEPar
// gcc PDEPar.c -fopenmp -o PDEPar
// ./PDEPar 5000 50 30 100 1000000 16

#define L 5 // Longitud de la barra

//Definición de funciones
void copyArray(double arr[], double copy[], int size);
void displayArray(double arr[], int size);

int main(int argc, char* argv[]) {
  double t0, tl, tr; //Declaracion de variables de temperatura inicial, temperatura extremo izquierdo y temperatura extremo derecho
  int N,iterations = 100; //Declaración de variables de números de segmentos y cantidad de iteraciones de tiempo
  double c = pow(10, -1); //Declaración de la constante de de difusividad térmica con valor de 1*10-1
  

//Verificación de ingreso de los parametros requeridos
  if (argc == 1) {
      printf("Usage: PDEPar partes_barra T_inicial T_left T_right iteraciones\n");
      exit (1);
  }

  N =  atoi(argv[1]); // Numero de intervalo discretos
  t0 = strtol(argv[2], NULL, 10); // Temperatura inicial
  tl = strtol(argv[3], NULL, 10); // Temperatura de la frontera izquierda
  tr = strtol(argv[4], NULL, 10); // Temperatura de la frontera derecha
  iterations = atoi(argv[5]); // Cantidad de iteraciones temporales
  int thread_count = atoi(argv[6]); // Cantidad de hilos a utilizar en la paralelización 

  // Inicio del calculo de tiempo paralelo con omp
  double t_ini = omp_get_wtime();
  
  // 1. División del dominio en intervalos discretos (tiempo y distancia)
  double deltax = (double)L/(double)N;
  double deltat = (deltax*deltax)/(2*c);

  // 2. Ajuste de los valores iniciales de los vectores de solución Ti y Ti+1, para tiempo i
  double Ti[N];
  double Ti_p1[N];

  //Asignación de los vectores de temperaturas iniciales y de solucion con la temperatura inicial y temperaturas 0 respectivamente
  for (int i = 0; i<N; i++){
    Ti[i] = t0;
    Ti_p1[i] = 0;
  }
  //Comienzo de iteraciones para el cálculo de la disipación del calor a lo largo de la barra
  
  /*Se utilizo la directiva de parallel for para la paralelización así mismo se utilizó la directiva de 
  shared para los vectores en los cuales se encuentran las temperaturas iniciales y las resultantes, esto con 
  el objetivo de que todos los hilos tengan acceso a estas variables. Por último, se utilizó un esquema de 
  planificación dinámico con un blocksize de 640 para optimizar el desempeño del programa en cuanto a la asignación 
  de trabajo a los hilos.
  */ 
  #pragma omp parallel for num_threads(thread_count) shared(Ti, Ti_p1) schedule(dynamic, 640)
  for (int i = 1; i <= iterations; i++) {
    #pragma omp parallel for
    for (int j=0; j<N; j++) {
      // Calculo de las temperaturas
      int thread_ID = omp_get_thread_num(); // Obteniendo el ID del hilo que se está ejecutando
      double res = 0;

      if(j==0) { //Calculo para la primera temperatura
        res = Ti[j]+(((c*deltat/(deltax*deltax)))*(tl-(2*Ti[j])+Ti[j+1]));

      } else if(j==(N-1)) { //Calculo para la ultima temperatura
        res = Ti[j]+(((c*deltat/(deltax*deltax)))*(Ti[j-1]-(2*Ti[j])+tr));
      
      } else { //Calculo para las temperaturas del medio
        res = Ti[j]+(((c*deltat/(deltax*deltax)))*(Ti[j-1]-(2*Ti[j])+Ti[j+1]));

      }
      Ti_p1[j] = res;
      
    }

  //Uso de mecanismo de coordinación para evitar race conditions en la escritura del vector solución al vector de temperaturas iniciales
  #pragma omp task
  copyArray(Ti_p1,Ti,N);
}
  //Finalización de toma de tiempo
  double t_fin = omp_get_wtime();

  // Mostrar barra final
  displayArray(Ti,N);

  printf("VALORES: Segmentos: %d T inicial barra: %f T_L %f T_R %f Iteraciones: %d \n", N,t0,tl,tr, iterations);

  // Mostrar delta de tiempo
  printf("Tiempo: %f\n",(t_fin - t_ini));
  

  return 0;
}

// Funcion que sirve para copiar los elementos de un array en otro
void copyArray(double arr[], double copy[], int size) {
  for (int i = 0; i < size; ++i) {
    copy[i] = arr[i];
  }
}

// Funcion que sirve para mostrar el contenido de un array
void displayArray(double arr[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%f ",arr[i]);
  }
  printf("\n");
}
