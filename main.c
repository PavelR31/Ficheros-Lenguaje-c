#include "ejercicio1.h"


int main(int argc, char *argv[]) {

/*
	+---------------------------------------------------+
    |         		     Integrantes                    |
    +---------------------------------------------------+
    |   (1) Pavel Inmanol Rodriguez Pozo    21-03943-0  |
    |   (2) Erving Alejandro Caceres Collado 21-01531-0 |
    |   (3)	Luis Fernando Morales Aguilar    21-01049-0 |
    +---------------------------------------------------+*/	
	int num;
	printf("Se ha creado ficheros\n");

	// Creación de los archivos de datos si no existen
	creacionfichero();
	system("cls");

	// Ciclo para mostrar el menú hasta que se seleccione la opción de salida
	do {
		menu();
		printf ("\t\n\nEscriba la accion que desea realizar...\n");
		scanf("%d", &num);
		
		switch(num) {
			case 1:
				agregarLibros();
				system("cls");
				break;
			case 2:
				mostrarListadoLibros();
				system("cls");
				break;
			case 3:
				agregarUsuarios();
				system("cls");
				break;
			case 4:
				mostrarListadoUsuarios();
				system("cls");
				break;
			case 5:
			    realizarPrestamo();
				system("cls");
				break;
			case 6:
				mostrarPrestamos();
				system("cls");
				break;
			case 7:
				eliminarLibro();
				system("cls");
				break;
			case 8:
				eliminarUsuarios();
				system("cls");
				break;
			case 9:
				devolverLibro();
				system("cls");
				break;
		}
		if (num==0)
		{
			printf ("\n\nGracias por utilizar este software!:D");
		}

	} while(num!=0);
}

