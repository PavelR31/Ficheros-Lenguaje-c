#include "ejercicio1.h"

// Función para crear los archivos de datos si no existen
void creacionfichero() {
	// Crear los archivos de datos para libros, usuarios y préstamos
	FILE *fLibros, *fUsuarios, *fPrestamo;
	fLibros = fopen("libros.dat", "wb");
	fUsuarios = fopen("usuarios.dat", "wb");
	fPrestamo = fopen("prestamo.dat", "wb");

	// Si alguno de los archivos no se pudo crear, salir del programa
	if(fLibros==NULL || fUsuarios== NULL|| fPrestamo==NULL)
		exit(1);

	// Cerrar los archivos
	fclose(fLibros);
	fclose(fUsuarios);
	fclose(fPrestamo);
	printf ("\nPresione para continuar...\n");
	getch();
}

void menu() {
	printf("+------------------------+\n");
    printf("|         MEN%c           |\n", 233);
    printf("+------------------------+\n");
    printf("|   (1) Agregar libro    |\n");
    printf("|   (2) Mostrar libros   |\n");
    printf("|   (3) Agregar usuario  |\n");
    printf("|   (4) Mostrar usuarios |\n");
    printf("|   (5) Prestar libro    |\n");
    printf("|   (6) Mostrar prestamos|\n");
    printf("|   (7) Eliminar libro   |\n");
    printf("|   (8) Eliminar usuario |\n");
    printf("|   (9) Devolver libro   |\n");
    printf("|   (0) Salir            |\n");
    printf("+------------------------+\n");
}

// Función para agregar un libro al archivo "libros.dat"
void agregarLibros() {
	FILE *fLibros; // Archivo de libros
	fLibros=fopen("libros.dat", "ab"); 
	if(fLibros==NULL)
		exit(1); // Si no se puede abrir el archivo, salir del programa
	Libro libro; // Crear objeto libro

	// Pedir al usuario que ingrese información sobre el libro
	fflush(stdin);
	printf ("Ingrese el titulo del libro\n");
	gets(libro.titulo);

	fflush(stdin);
	printf("Ingrese la edicion del libro\n");
	scanf("%d", &libro.edicion);

	fflush(stdin);
	printf("Ingrese nombre de autor del libro\n");
	gets(libro.autor);

	// Escribir el objeto libro en el archivo
	fwrite(&libro, sizeof(Libro),1,fLibros);
	fclose(fLibros); 
	printf ("\nPresione para continuar...\n");
	getch();
}

// Función para agregar un usuario al archivo "usuarios.dat"
void agregarUsuarios() {
	FILE *fUsuarios; // Archivo de usuarios
	fUsuarios=fopen("usuarios.dat", "ab"); 
	if(fUsuarios==NULL)
		exit(1); // Si no se puede abrir el archivo, salir del programa
	Usuario usuario; // Crear objeto usuario

	// Pedir al usuario que ingrese información sobre el usuario
	fflush(stdin);
	printf ("Ingrese nombre de usuario\n");
	gets(usuario.nombre);

	fflush(stdin);
	printf ("Ingrese identificacion de usuario\n");
	gets(usuario.identificacion);

	fflush(stdin);
	printf ("Ingrese que tipo de usuario es\n");
	gets(usuario.tipo_usuario);

	// Escribir el objeto usuario en el archivo
	fwrite(&usuario, sizeof(Usuario),1,fUsuarios);
	fclose(fUsuarios); // Cerrar el archivo
	printf ("\nPresione para continuar...\n");
	getch();
}

// Función para mostrar una lista de todos los usuarios almacenados en el archivo "usuarios.dat"
void mostrarListadoUsuarios() {
	FILE *fUsuarios; // Archivo de usuarios
	int i=0;
	fUsuarios =fopen("usuarios.dat", "rb"); // Abrir archivo en modo binario
	if (fUsuarios==NULL)
		exit(1); // Si no se puede abrir el archivo, salir del programa
	Usuario usuario; // Crear objeto usuario

	// Leer cada objeto usuario del archivo y mostrar su información en pantalla
	fread(&usuario, sizeof(Usuario), 1, fUsuarios);
	while(!feof(fUsuarios)) {
		printf("[%d]\n\tNombre:%s \n\tIdentificacion:%s\n\tTipo de usuario:%s\n",i+1,usuario.nombre, usuario.identificacion, usuario.tipo_usuario);
		fread(&usuario, sizeof(Usuario), 1, fUsuarios);
		i++;
	}

	fclose(fUsuarios); 
	printf ("\nPresione para continuar...\n");
	getch();
}

//Funcion para prestar un libro en existencia a una persona
void realizarPrestamo() {
	char nombre_usuario[60], titulo_libro[100];
	int usuario_encontrado = 0, libro_encontrado = 0;
	FILE *fUsuarios, *fLibros, *fPrestamo;
	fUsuarios = fopen("usuarios.dat", "rb"); 
	fLibros = fopen("libros.dat", "rb"); 
	fPrestamo = fopen("prestamo.dat", "ab"); 
	if(fUsuarios == NULL || fLibros == NULL || fPrestamo == NULL) { 
		printf("Error al abrir los archivos\n"); 
		exit(1); 
	}


	printf("Ingrese el nombre del usuario: ");
	scanf("%s", nombre_usuario);
	Usuario usuario;
	while(fread(&usuario, sizeof(Usuario), 1, fUsuarios)) { // Leer un registro de usuario del archivo
		if(strcmp(usuario.nombre, nombre_usuario) == 0) { // Si se encuentra un usuario con el nombre ingresado
			usuario_encontrado = 1; // Cambiar el indicador de usuario encontrado a verdadero
			break;
		}
	}
	rewind(fUsuarios); // Volver al principio del archivo de usuarios


	printf("Ingrese el titulo del libro: ");
	scanf("%s", titulo_libro);
	Libro libro;
	while(fread(&libro, sizeof(Libro), 1, fLibros)) { // Leer un registro de libro del archivo
		if(strcmp(libro.titulo, titulo_libro) == 0) { // Si se encuentra un libro con el título ingresado
			libro_encontrado = 1; // Cambiar el indicador de libro encontrado a verdadero
			break; // Salir del bucle
		}
	}
	rewind(fLibros); // Volver al principio del archivo de libros

	// Si el usuario y el libro existen, agregar los datos del préstamo en el archivo binario "prestamo.dat"
	if(usuario_encontrado == 1 && libro_encontrado == 1) { // Si se encontraron el usuario y el libro
		Prestamo prestamo;
		strcpy(prestamo.titulo_libro, titulo_libro);
		strcpy(prestamo.nombre_usuario, nombre_usuario);
		printf("Ingrese la fecha de prestamo (DD/MM/YYYY): ");
		scanf("%s", prestamo.fecha_prestamo);
		printf("Ingrese la fecha de devolucion (DD/MM/YYYY): ");
		scanf("%s", prestamo.fecha_devolucion);
		fwrite(&prestamo, sizeof(Prestamo), 1, fPrestamo); // Escribir el registro de préstamo en el archivo
		printf("Prestamo realizado con exito");
	} else {
		printf("El usuario o el libro no existe en el sistema.\n");
	}

	fclose(fUsuarios); 
	fclose(fLibros); 
	fclose(fPrestamo); 
	
	printf("\nPresione para continuar...\n");
	getch();
}

void mostrarListadoLibros() {

	FILE *fLibros;
	fLibros = fopen("libros.dat", "rb");

	if (fLibros==NULL)
		exit(1);

	Libro libro;

	fread(&libro, sizeof(Libro), 1, fLibros);
	int i=0;

	while(!feof(fLibros)) {
		printf("[%d]\n\tTitulo:%s \n\tEdicion:%d\n\tAutor: %s\n",i+1, libro.titulo, libro.edicion, libro.autor);
		
		fread(&libro,sizeof(Libro),1,fLibros);
		i++;
	}

	fclose(fLibros);
	printf ("\nPresione para continuar...\n");
	getch();
}

void mostrarPrestamos() {

	FILE *fPrestamo;
	fPrestamo = fopen("prestamo.dat", "rb");

	if (fPrestamo==NULL)
		exit(1);
	
	Prestamo prestamo;

	fread(&prestamo, sizeof(Prestamo), 1, fPrestamo);
	int i=0;
	while(!feof(fPrestamo)) {
		printf("[%d]\n\tTitulo:%s \n\tNombre Usuario:%s\n\tFecha de prestamo: %s\n\tFecha de devolucion: %s\n",i+1, prestamo.titulo_libro, prestamo.nombre_usuario, prestamo.fecha_prestamo, prestamo.fecha_devolucion);

		fread(&prestamo,sizeof(Prestamo),1,fPrestamo);
		i++;
	}

	fclose(fPrestamo);
	printf ("\nPresione para continuar...\n");
	getch();
}

void eliminarLibro() {
	char titulo[100];
	int encontrado = 0, libro_encontrado = 0;
	FILE *fLibros, *fTemp, *fPrestamo;
	fLibros = fopen("libros.dat", "rb");
	fPrestamo = fopen("prestamo.dat", "rb"); 
	fTemp = fopen("temp.dat", "wb"); 
	Libro libro;
	Prestamo prestamo;

	printf("Ingrese el titulo del libro a eliminar: ");
	fflush(stdin); 
	gets(titulo); 

	if(fLibros == NULL || fTemp == NULL || fPrestamo == NULL) { 
		printf("Error al abrir los archivos\n");
		exit(1); 
	}

	while(fread(&prestamo, sizeof(Prestamo), 1, fPrestamo)) { // Lee los registros del archivo "prestamo.dat"
		if (strcmp(prestamo.titulo_libro, titulo)==0) // Verifica si el libro está prestado
		{
			libro_encontrado = 1; // Establece la variable "libro_encontrado" en 1 si el libro está prestado
			break; 
		}
		else
		{
	}
}	
	rewind(fLibros); 

	while(fread(&libro, sizeof(Libro), 1, fLibros)) { 
			if((strcmp(libro.titulo, titulo) == 0) && libro_encontrado != 1){ // Verifica si el libro es el que se quiere eliminar y no está prestado
				encontrado = 1; // Establece la variable "encontrado" en 1 si se encuentra el libro
			continue; // Salta el registro actual
			}
			fwrite(&libro, sizeof(Libro), 1, fTemp); 
		}	

	if (libro_encontrado==1) // Verifica si el libro está prestado
	{
		printf("No se puede eliminar libro porque esta prestado"); // Muestra un mensaje indicando que no se puede eliminar el libro
	}
	else{
		if(!encontrado) {
		printf("El libro no se ha encontrado\n"); // Muestra un mensaje indicando que no se encuentra el libro
		} else {
			printf("El libro se ha eliminado con exito\n"); // Muestra un mensaje indicando que se eliminó el libro con éxito
		}
	}
	
	fclose(fLibros); 
	fclose(fTemp); 
	
	remove("libros.dat"); 
	rename("temp.dat", "libros.dat"); 
	printf ("\nPresione para continuar...\n");
	getch();
	}
	
	void eliminarUsuarios() {

	char nombre[100];
	int encontrado = 0;
	FILE *fUsuarios, *fTemp2;
	Usuario usuario;

	// Se abre el archivo "usuarios.dat" en modo lectura y se guarda en fUsuarios
	fUsuarios = fopen("usuarios.dat", "rb");
	// Se abre un archivo temporal "temp2.dat" en modo escritura y se guarda en fTemp2
	fTemp2 = fopen("temp2.dat", "wb");
	
	printf("Ingrese el nombre del usuario a eliminar : ");
	fflush(stdin);
	gets(nombre);

	if(fUsuarios == NULL || fTemp2 == NULL) {
		printf("Error al abrir los archivos\n");
		exit(1);
	}

	// Se lee cada registro del archivo "usuarios.dat" y se compara con el nombre ingresado por el usuario
	while(fread(&usuario, sizeof(Usuario), 1, fUsuarios)) {
		if(strcmp(usuario.nombre, nombre) == 0) { // Si el nombre del usuario es igual al ingresado por el usuario
			encontrado = 1; // Se marca como encontrado
			continue; // Y se pasa al siguiente registro
		}
		// Si el nombre del usuario no coincide con el ingresado por el usuario, se escribe el registro en el archivo temporal "temp2.dat"
		fwrite(&usuario, sizeof(Usuario), 1, fTemp2);
	}

	// Si no se encontró ningún registro con el nombre ingresado por el usuario, se imprime un mensaje de error
	if(!encontrado) {
		printf("El usuario no se ha encontrado\n");
	} else { // Si se encontró el registro, se imprime un mensaje de éxito
		printf("El usuario se ha eliminado con exito\n");
	}


	fclose(fUsuarios);
	fclose(fTemp2);
	// Se elimina el archivo original "usuarios.dat"
	remove("usuarios.dat");
	// Se renombra el archivo temporal "temp2.dat" como "usuarios.dat"
	rename("temp2.dat", "usuarios.dat");

	// Se espera a que el usuario presione una tecla para continuar
	printf ("\nPresione para continuar...\n");
	getch();
}

void devolverLibro()
{
    

    char nombreLibro[50];
    char fechaDevolucion[50];
    int encontrado=0, devo=0;
    
    // Declaramos los punteros de archivo para los archivos de préstamos y temporales.
    FILE *fPrestamo, *fTemp3;
    
    // Abrimos los archivos de préstamos y temporales.
    fPrestamo = fopen("prestamo.dat", "rb");
    fTemp3 = fopen("temp3.dat", "wb");
    
    // Creamos una estructura Prestamo para almacenar los datos de cada préstamo.
    Prestamo prestamo;
    

    fflush(stdin);
    printf ("Ingrese nombre del libro a devolver: ");
    gets(nombreLibro);
    

    fflush(stdin);
    printf ("Ingrese la fecha en que lo esta devolviendo: ");
    gets (fechaDevolucion);
    
    
    if(fPrestamo == NULL || fTemp3 == NULL) {
        printf("Error al abrir los archivos\n");
        exit(1);
    }
    // Leemos los préstamos del archivo de préstamos.
    while(fread(&prestamo, sizeof(Prestamo), 1, fPrestamo)) {
        // Si la fecha de devolución del préstamo no coincide con la fecha ingresada por el usuario, seteamos devo a 1.
        if (strcmp(prestamo.fecha_devolucion, fechaDevolucion) != 0)
        {
            devo = 1;
        }
        // Si el título del libro del préstamo coincide con el título ingresado por el usuario, seteamos encontrado a 1.
        if(strcmp(prestamo.titulo_libro, nombreLibro) == 0) {
            encontrado = 1;
            continue;
        }
        // Escribimos el préstamo en el archivo temporal.
        fwrite(&prestamo, sizeof(Prestamo), 1, fTemp3);
    }
    
   
    if(!encontrado) {
        printf("El libro no se ha encontrado\n");
    } 
    // Si se encontró el libro pero la fecha de devolución no coincide, mostramos un mensaje de advertencia.
    else if(encontrado==1 && devo == 1) {
        printf("El libro se ha devuelto con exito, sin embargo las fechas de devolucion no coinciden\n");
        printf ("\tFecha esperada: %s  -- Fecha que se entrego: %s ", prestamo.fecha_devolucion, fechaDevolucion);
    }
    // Si se encontró el libro y la fecha de devolución coincide, mostramos un mensaje de éxito.
    else{
        printf ("\nSe ha devuelto con exito :D");
    }
    
    
    fclose(fPrestamo);
    fclose(fTemp3);
    
    remove("prestamo.dat");
	rename("temp3.dat", "prestamo.dat");
	printf ("\nPresione para continuar...\n");
	getch();
	

}