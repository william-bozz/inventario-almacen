# Sistema de inventario para Almacén
![Version](https://img.shields.io/badge/version-1.0.0-blue)
![C](https://img.shields.io/badge/language-C-orange)

Sistema de gestión de inventario programado en C para pequeños negocios.
Permite controlar productos, stock, precios, y ubicaciones con uso en archivos.

## Tabla de contenidos
- [Descripción]
- [Caracteristicas]
- [Capturas]
- [Requisitos]
- [Instalación]
- [Uso]
- [Estructura del proyecto]
- [Tecnologías]
- [Autor]

## Descripción

Este proyecto es un sistema de inventario básico para **pequeñas bodegas o tiendas familiares**.
Desarrollado completamente en C como proyecto de aprendizaje de estructuras, archivos y lógia de programación.

**Características principales**
- Interfaz de consola intuitiva
- Gestión completa de productos (CRUD)
- Búsqueda por ID o nombre
- Control de entrada y salidas de stock
- Alerta de productos con stock bajo
- Uso de archivo de texto

## Capturas
- Aún no sé como subir capturas a github, lol.

## Requisitos
- Compilador de C (GCC recomendado)
- Sistema operativo: solamente probado en linux
- Terminal

## Instalación en linux
git clone https://github.com/william-bozz/inventario-almacen.git
gcc inventario.c -o inventario
./inventario

## Uso

1. Ejecuta el programa
2. Selecciona una opción del menú
3. Sigue las instrucciones en pantalla
4. Guarda antes de salir para no perder datos

## Estructura del proyecto
/inventario-almacen
--inventario.c #código fuente principales
--inventario.h #cabeceras y estructuras
--inventario.txt #archivo de datos (se genera automáticamente)
--README.md #documentación
--.gitignore #archivos ignorados

## Tecnologías
· Lenguaje: C
· Compilador: GCC
· ID: Vim
· Controlador de versiones: Git

## Autor
· Github: william-bozz
