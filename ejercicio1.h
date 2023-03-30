#ifndef _EJERCICIO1_H_
#define _EJERCICIO1_H_

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

// Definición de estructuras
typedef struct libro {
	char titulo[100];
	int edicion;
	char autor[60];
} Libro;

typedef struct usuario {
	char nombre[60];
	char identificacion[20];
	char tipo_usuario[15];
} Usuario;

typedef struct prestamo {
	char titulo_libro[100];
	char nombre_usuario[60];
	char fecha_prestamo[12];
	char fecha_devolucion[12];
} Prestamo;

// Declaración de prototipos de funciones
void creacionfichero();
void menu();
void agregarLibros();
void mostrarListadoLibros();
void eliminarLibro();
void agregarUsuarios();
void mostrarListadoUsuarios();
void eliminarUsuarios();
void realizarPrestamo();
void mostrarPrestamos();
void devolverLibro();



#endif