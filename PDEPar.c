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

// gcc PDEPar.c -o PDEPar
// ./PDEPar 5000 50 30 100 1000

#define L 5 // Longitud de la barra
double ecuacion(double *Ti_func,int j, double c,double dt,double x, double tl, double tr, int n);
void copyArray(double* arr1, double* arr2, int arr_len);
void displayArray(double arr[], int size);
double *array_dinamico(int arr_len, double value);
void display_array(double* arr_dinamico, int arr_len);

int main(int argc, char* argv[]) {
  double err, t0, tl, tr;
  int iterations = 100;
  int N = 5000;
  double c = pow(10, -1);

  if(argc > 1) {
    printf("\n");
    N =  atoi(argv[1]); // Numero de intervalo discretos
    t0 = strtol(argv[2], NULL, 10); // Temperatura inicial
    tl = strtol(argv[3], NULL, 10); // Temperatura de la frontera izquierda
    tr = strtol(argv[4], NULL, 10); // Temperatura de la frontera derecha
    iterations = atoi(argv[5]);
  }

  printf("VALORES: %d %f %f %F %d \n", N,t0,tl,tr, iterations);


  // 1. División del dominio en intervalos discretos (tiempo y distancia)
  double deltax = (double)L/(double)N;
  double deltat = (deltax*deltax)/(2*c);

  // 2. Ajustar los valores iniciales de los vectores de solución Ti y Ti+1, para tiempo i
  double *Ti = array_dinamico(N,t0);
  display_array(Ti,N);
  printf("\n\n");
  double *Ti_p1 = array_dinamico(N,0.0);
  display_array(Ti_p1,N);

  // 3. For (resultado en vec_sol)
  for (int i = 1; i <= iterations; i++) {
    Ti_p1 = array_dinamico(N,0.0); //Cada iteracion de tiempo reiniciar el vector de resultados en 0
    for (int j=0; j<N; j++){
      // Calculo de las temperaturas 
      double res = ecuacion(Ti, j, c, deltat, deltax, tl, tr, N);
      *(Ti_p1+j)=res;
    }
    copyArray(Ti_p1,Ti,N);
  }

  printf("\n\n");
  display_array(Ti,N);
  printf("\n");

  return 0;
}

double ecuacion(double* Ti_func,int j, double c,double dt,double x, double tl, double tr, int n) {
  double result;
  double Ti_mas_j = *(Ti_func+j);
  double Ti_mas_j_mas_uno = *(Ti_func+j+1);
  double Ti_mas_j_menos_uno = *(Ti_func+j-1);

  if (j==0) {
    result = Ti_mas_j + (((c*dt/(x*x))) * (tl-(2*Ti_mas_j) + Ti_mas_j_mas_uno));
    //result = Ti[j] + (((c*dt/(x*x))) * (tl - (2* Ti[j]) + Ti[j+1]));
  
  } else if (j==(n-1)) {
    result =  Ti_mas_j + (((c*dt/(x*x))) * (Ti_mas_j_menos_uno - (2 * Ti_mas_j) +tr));
    //result = Ti[j] + (((c*dt/(x*x))) * (Ti[j-1] - (2* Ti[j]) +tr));
  } else {
    result = Ti_mas_j + (((c*dt/(x*x))) * (Ti_mas_j_menos_uno - (2* Ti_mas_j) + Ti_mas_j_mas_uno));
    // result = Ti[j] + (((c*dt/(x*x))) * (Ti[j-1] - (2* Ti[j]) + Ti[j+1] ));
  }

  return result;
}

// Function to copy the elements of an array in other
void copyArray(double* arr1, double* arr2, int arr_len) {
  for (int i = 0; i < arr_len; ++i) {
    *(arr1+i) = *(arr2+i);
  }
}

// Function to display an array
void displayArray(double arr[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%f ",arr[i]);
  }
  printf("\n");
}

double* array_dinamico(int arr_len, double value) {
    double *ptr;
    ptr = (double *)malloc(arr_len*sizeof(int));

    for (int i=0; i<arr_len; i++) {
      ptr[i]=value;
    }

    return ptr;
}

void display_array(double* arr_dinamico, int arr_len) {
  for(int i = 0; i < arr_len; i++) {
    printf("%f ",*(arr_dinamico+i));
  }
}
