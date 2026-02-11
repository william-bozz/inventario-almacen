#ifndef INVENTARIO_H
#define INVENTARIO_H

#define MAX_PRODUCTOS 10
#define MAX_NOMBRE 50
#define MAX_UBICACION 15
#define STOCK_BAJO 5

typedef struct{
	int id;
	char nombre[MAX_NOMBRE];
	int cantidad;
	float valor;
	char ubicacion[MAX_UBICACION];
} Producto;

void mostrarMenu();

void agregarProducto();

void mostrarProducto(Producto p);
void mostrarTodosProductos();

void buscarProducto();
int buscarPorID(int id);
void buscarPorNombre(char nombre[]);

void actualizarCantidad();

void mostrarStockBajo();

void guardarInventario();

void cargarInventario();

#endif

