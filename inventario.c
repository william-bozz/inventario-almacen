#include <stdio.h>
#include "inventario.h"
#include <stdlib.h>
#include <string.h>

Producto inventario[MAX_PRODUCTOS];
int numProductos = 0;

void leerCadena(char *cadena, int maxLongitud){
    fgets(cadena, maxLongitud, stdin);

    int len = strlen(cadena);
    if(len > 0 && cadena[len-1] == '\n'){
        cadena[len-1] = '\0';
    } else {
        while(getchar() != '\n');
    }
}

void mostrarMenu(){
	printf("\n=== MENÚ PRINCIPAL ===\n");
	printf("1. Agregar producto\n");
	printf("2. Buscar producto\n");
	printf("3. Acitualizar cantidad\n");
	printf("4. Mostrar stock bajo\n");
	printf("5. Guardar inventario\n");
	printf("6. Cargar inventario\n");
	printf("7. Salir\n");
	//printf("8. [DEBUG] Mostrar todos\n");
	printf("Seleccione una opción: ");
}

void agregarProducto(){
	printf("\n=== AGREGAR NUEVO PRODUCTO ===\n");

	if(numProductos >= MAX_PRODUCTOS){
		printf("¡Inventario lleno! No se pueden agregar más productos.\n");
		printf("Máximo permitido: %d productos.\n", MAX_PRODUCTOS);
		return;
	}

	Producto *p = &inventario[numProductos];

	printf("Ingrese ID del producto: ");
	scanf("%d", &p->id);
	while(getchar() != '\n');

	printf("Ingrese nombre del producto: ");
	leerCadena(p->nombre, MAX_NOMBRE);

	//Eliminar el salto de linea de fgets
	for(int i = 0; i < MAX_NOMBRE; i++){
		if(p->nombre[i] == '\n'){
			p->nombre[i] == '\0';
			break;
		}
	}

	do{
		printf("Ingrese cantidad inicial: ");
		scanf("%d", &p->cantidad);
		while(getchar() != '\n');

		if(p->cantidad < 0){
			printf("Error: La cantidad no puede ser negativa.\n");
		}
	} while(p->cantidad < 0);

	do{
		printf("Ingrese valor unitario: ");
		scanf("%f",&p->valor);
		while(getchar() != '\n');

		if(p->valor < 0){
			printf("Error: El valor no puede ser negativo.\n");
		}
	}while(p->valor < 0);

	printf("Ingrese ubicación (Ej: Estante 6-A): ");
	leerCadena(p->ubicacion, MAX_UBICACION);

	//Eliminar salto linea fgets
	for(int i = 0; i < MAX_UBICACION; i++){
		if(p->ubicacion[i] == '\n'){
			p->ubicacion[i] = '\0';
			break;
		}
	}

	numProductos++;

	printf("\n¡Producto agregado exitosamente!\n");
	printf("Productos en inventario: %d\n", numProductos);
}

void mostrarProducto(Producto p){
	printf("┌──────────────────────────────────────┐\n");
	printf("| ID: %-8d                         |\n", p.id);
	printf("| Nombre: %-30s |\n", p.nombre);
	printf("| Cantidad: %-6d Valor: $%-8.2f  |\n", p.cantidad, p.valor);
	printf("| Ubicación: %-25s |\n", p.ubicacion);
	printf("| Valor total: $%-8.2f               |\n", p.cantidad * p.valor);
	printf("└──────────────────────────────────────┘\n");
}

void mostrarTodosProductos(){
	printf("\n=== INVENTARIO COMPLETO ===\n");
	printf("Productos registrados: %d\n\n",  numProductos);

	if(numProductos == 0){
		printf("No hay productos en el inventario.\n");
		return;
	}

	for(int i = 0; i < numProductos; i++){
		printf("Producto %d:\n", i + 1);
		mostrarProducto(inventario[i]);
		printf("\n");
	}
}

int buscarPorID(int id){
    for(int i = 0; i < numProductos; i++){
        if(inventario[i].id == id){
            return i; //Encontrado
        }
    }
    return -1; //No encontrado
}

void buscarPorNombre(char nombreBuscado[]){
    int encontrados = 0;

    printf("\n=== RESULTADOS DE BÚSQUEDA: '%s' ===\n", nombreBuscado);

    for(int i = 0; i < numProductos; i++){
        if(strstr(inventario[i].nombre, nombreBuscado) != NULL){
            printf("\nProducto encontrado (índice %d):\n", i);
            mostrarProducto(inventario[i]);
            encontrados++;
        }
    }

    if(encontrados == 0){
        printf("No se encontraron productos con '%s' en el nombre.\n", nombreBuscado);
    } else {
        printf("\nTotal encontrados: %d\n", encontrados);
    }
}

void buscarProducto(){
    int opcion;
    char input[100];

    printf("\n== BUSCAR PRODUCTO==\n");
    printf("1. Buscar por ID\n");
    printf("2. Buscar por nombre\n");
    printf("Seleccione opción: ");

    fgets(input, sizeof(input), stdin);
    opcion = atoi(input);

    switch(opcion){
        case 1:{
            int idBuscado;
            printf("Ingrese ID a buscar: ");
            fgets(input, sizeof(input), stdin);
            idBuscado = atoi(input);

            int indice = buscarPorID(idBuscado);

            if(indice != -1){
                printf("\n¡Producto encontrado!\n");
                mostrarProducto(inventario[indice]);
            } else {
                printf("\nProducto con ID %d no encontrado.\n", idBuscado);
            }
            break;
        }

        case 2:{
            char nombreBuscado[MAX_NOMBRE];
            printf("Ingrese nombre o parte del nombre: ");
            fgets(nombreBuscado, sizeof(nombreBuscado), stdin);

            nombreBuscado[strcspn(nombreBuscado, "\n")] = '\0';

            buscarPorNombre(nombreBuscado);
            break;
        }

        default:
            printf("Opción no válida.\n");

    }
}

void actualizarCantidad(){
    int id, cantidad, indice;
    char input[100];
    char opcion;

    printf("\n=== ACTUALIZAR CANTIDAD ==\n");

    printf("Ingrede ID del producto a actualizar: ");
    fgets(input, sizeof(input), stdin);
    id = atoi(input);

    indice = buscarPorID(id);

    if(indice == -1){
        printf("Producto con ID %d no encontrado.\n", id);
        return;
    }

    printf("\nProducto encontrado:\n");
    mostrarProducto(inventario[indice]);

    printf("\nTipo de actualización:\n");
    printf("E - Entrada (agregar stock)\n");
    printf("S - Salida (retirar stock)\n");
    printf("Seleccione (E/S): ");

    fgets(input, sizeof(input), stdin);
    opcion = input[0];

    printf("Ingrese cantidad: ");
    fgets(input, sizeof(input), stdin);
    cantidad = atoi(input);

    if(cantidad <= 0){
        printf("Error: La cantidad debe ser positiva.\n");
        return;
    }

    if(opcion == 'E' || opcion == 'e'){
        inventario[indice].cantidad += cantidad;
        printf("\nSe agregaron %d unidades.\n", cantidad);
    } else if (opcion == 'S' || opcion == 's'){
        if(cantidad > inventario[indice].cantidad){
            printf("Error: No hay suficiente stock.\n");
            printf("Stock actual: %d, Intento de retiro: %d\n", inventario[indice].cantidad, cantidad);
            return;
        }
        inventario[indice].cantidad -= cantidad;
        printf("\nSe retiraron %d unidades.\n", cantidad);
    } else {
        printf("Opción no válida.\n");
        return;
    }

    printf("\nProducto actualizado:\n");
    mostrarProducto(inventario[indice]);
}

void mostrarStockBajo(){
    int productosBajo = 0;

    printf("\n=== PRODUCTOS CON STOCK BAJO (<%d unidades) ===\n", STOCK_BAJO);

    for(int i = 0; i < numProductos; i++){
        if(inventario[i].cantidad < STOCK_BAJO){
            printf("\n[ALERTA] Stock bajo encontrado:\n");
            mostrarProducto(inventario[i]);
            productosBajo++;
        }
    }

    if(productosBajo == 0){
        printf("No hay productos con stock bajo.\n");
        printf("Todos los productos tienen %d o más unidades.\n", STOCK_BAJO);
    } else {
        printf("\n============================\n");
        printf("Total de productos con stock bajo: %d\n", productosBajo);
    }
}

void guardarInventario(){
    FILE *archivo;

    printf("\n=== GUARDAR INVENTARIO ===\n");

    archivo = fopen("inventario.txt", "w");

    if(archivo == NULL){
        printf("Error: No se pudo crear el archvio 'inventario.txt'\n");
        return;
    }

    fprintf(archivo, "%d\n", numProductos);

    for(int i = 0; i < numProductos; i++){
        fprintf(archivo, "%d\n", inventario[i].id);
        fprintf(archivo, "%s\n", inventario[i].nombre);
        fprintf(archivo, "%d\n", inventario[i].cantidad);
        fprintf(archivo, "%.2f\n", inventario[i].valor);
        fprintf(archivo, "%s\n", inventario[i].ubicacion);
    }

    fclose(archivo);

    printf("Inventario guardado exitosamente en 'inventario.txt'\n");
    printf("Productos guardados: %d\n", numProductos);

}

void cargarInventario(){
    FILE *archivo;
    int productosEnArchivo;
    char buffer[100];

    printf("\n=== CARGAR INVENTARIO ===\n");


    archivo = fopen("inventario.txt", "r");
    if(archivo == NULL){
        printf("Error: No se pudo abrir 'inventario.txt'\n");
        printf("Guarde el inventario primero (opción 5).\n");
        return;
    }
    
    if(fgets(buffer, sizeof(buffer), archivo) == NULL){
        printf("Error: Archivo vacío\n");
        fclose(archivo);
        return;
    }

    productosEnArchivo = atoi(buffer);

    if(productosEnArchivo <= 0 || productosEnArchivo > MAX_PRODUCTOS){
        printf("Error: Número de productos inválido: %d\n", productosEnArchivo);
        fclose(archivo);
        return;
    }

    printf("Cargando %d productos...\n", productosEnArchivo);

    numProductos = 0;

    for(int i = 0; i < productosEnArchivo; i++){
        if(numProductos >= MAX_PRODUCTOS){
            printf("Advertencia: Limite alcanzado, solo se cargarán %d productos\n", MAX_PRODUCTOS);
            break;
        }

        Producto *p = &inventario[numProductos];

        if(fgets(buffer, sizeof(buffer), archivo) == NULL) break;
        p->id = atoi(buffer);

        if(fgets(buffer, sizeof(buffer), archivo) == NULL) break;
        buffer[strcspn(buffer, "\n")] = '\0';
        strncpy(p->nombre, buffer, MAX_NOMBRE);

        if(fgets(buffer, sizeof(buffer), archivo) == NULL) break;
        p->cantidad = atoi(buffer);

        if(fgets(buffer, sizeof(buffer), archivo) == NULL) break;
        p->valor = atof(buffer);

        if(fgets(buffer, sizeof(buffer), archivo) == NULL) break;
        buffer[strcspn(buffer, "\n")] = '\0';
        strncpy(p->ubicacion, buffer, MAX_UBICACION);

        numProductos++;
    }
    
    fclose(archivo);

    printf("Inventario cargado exitosamente.\n");
    printf("Productos cargados: %d\n", numProductos);
}    

int main(){

	int opcion;

	printf("Sistema de Inventario - Almacén Familiar");
	printf("======================================\n");

	do{
		mostrarMenu();

		if(scanf("%d", &opcion) != 1){
			while(getchar() != '\n');
			continue;
		}

		while(getchar() != '\n');

		switch(opcion){
			case 1:
				agregarProducto();
				break;
			case 2:
				buscarProducto();
				break;
			case 3:
				actualizarCantidad();
                break;
			case 4:
				mostrarStockBajo();
				break;
			case 5:
				guardarInventario();
				break;
			case 6:
				cargarInventario();
				break;
			case 7:
				printf("\nSaliendo del sistema...\n");
				break;
			//DEBUG
			/*case 8:
				mostrarTodosProductos();
				break;*/
			default:
				printf("\nOpción no válida. Intente de nuevo.\n");
		}

	} while(opcion != 7);

	return 0;

}
