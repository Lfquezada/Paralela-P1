# Cálculo de disipación de calor
El objetivo de este proyecto fue programar el cálculo de la ecuación diferencial que define el comportamiento de la disipación del calor en una barra de metal. Para esto se utilizaron dos programas, uno secuencial y uno paralelo el cual hace uso de la libreria de OpenMP que permite utilizar directivas de paralelización, coordinación y mecanismos de barrera, con el objetivo de reducir el tiempo de ejecución del programa secuencial. 

## Requerimientos
* OpenMP 

## Uso 
1. Descargar los archivos PDEPar.c y PDESeqv2.c
2. Compilar de la siguiente forma: 

```
gcc PDEPar.c -fopenmp -o PDEPar
```

```
gcc PDESeqv2.c -o PDESeqv2
```
3. Ejecutar reemplazando las variables presentadas por valores númericos de la siguiente forma:

```
./PDEPar num_fragmentos_barra temp_inicial temp_izquierda temp_derecha iteraciones num_hilos
```

```
./PDESeqv2 num_fragmentos_barra temp_inicial temp_izquierda temp_derecha iteraciones
```

## Autores
- *Jennifer Sandoval* - [@JennsiS](https://github.com/JennsiS)
- *Luis Quezada* - [@Lfquezada](https://github.com/Lfquezada)
- *Esteban del Valle* - [@Estdv](https://github.com/Estdv)