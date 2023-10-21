// PrimerAvancePB.cpp
// Brandon Alberto Vazquez Alonso   Matricula:1872425  Gpo:051


//Menu:
//1.- Alta de Ordenes 2.- Modificar Orden 3.- Eliminar o cancelar Orden
//4.- LimpiarPantalla 5.- Salir
//Alta de 3 tickets
//Lista de tickets 
//Proyecto de GitHUb
#define _CRT_SECURE_NO_WARNINGS //Desactiva las advertencias de obsolecencia 
#include <iostream>
#include <string> 
#include <ctime> //Libreria para usar la fecha del dispositivo
#include <vector> //biblioteca para crear un vector de datos
#include <cstdio> //biblioteca para usar scanf_s
#include <map> //crear una lista de productos y precios

using namespace std;

//Alimentos separados por categoria para mayor facilidad.
struct Menu {
	//Datos del restaurante
	string RazonSocial = "Alimentos Basura S.A de C.V";//Razon Social Ficticia
	string Nombre;
	int ticket=0;//numero de ticket 
	double TotalCompra=0;// Variable para almacenar el total de la compra
	int Descuentos = 0;
	string IVA = "16%% por precio unitario";
	map<int, int> productosSeleccionados;// Mapa para almacenar los productos seleccionados

	//Fecha
	time_t Tiempo = time(nullptr); //: Obtiene el tiempo actual en segundos desde la época (el 1 de enero de 1970 a las 00:00:00 UTC).
	tm* Fecha = localtime(&Tiempo); //estructura que contiene los componentes de fecha y hora, como año, mes, día, hora, minuto, segundo, etc. 

};

int main()
{
	// Definir una lista de productos con sus códigos y precios sin IVA 
	map<int, pair<string, double>> productos = {
		{1, {"Hamburguesa de Res", 82.50}},
		{2, {"Hamburguesa Doble de Res", 107.75}},
		{3, {"Hamburguesa de pollo", 77.50}},
		{4, {"Hamburguesa Doble de Pollo", 99}},
		{5, {"Papas a la Francesa Chicas", 30}},
		{6, {"Papas a la Francesa Grandes", 47.4}},
		{7, {"Aros de Cebolla Chicas", 23.20}},
		{8, {"Aros de Cebolla Grandes", 39.5}},
		{9, {"Refresco Chico", 19.8}},
		{10, {"Refresco Grande", 29.3}},
		{11, {"Agua Mineral Chica", 16.38}},
		{12, {"Agua Mineral Grande", 22.40}},
		{13, {"Botella de Agua 500 ml", 14.65}},
		{14, {"Botella de Agua 1 Lt", 20.60}},
		{15, {"Te Helado Chico", 19.8}},
		{16, {"Te Helado Grande", 29.30}},
		{17, {"Cono de Helado (Vainilla)", 20.60}},
		{18, {"Vaso de Helado (Vainilla)", 17.24}},
		{19, {"Galleta de Chispas de Chocolate", 14.66}}
	};

	


	int opcion, numero = 0, contador = 0;

	//Vector que guarda la orden del cliente 
	vector<Menu>Orden;
	

	
	//Nombre del empleado
	Menu empleado;
	printf("Ingrese nombre de Empleado:\n");
	getline(cin, empleado.Nombre );

	system("cls");


	//Menu de Opciones creado con Switch
	do {

		printf("Elija una opcion:\n1.- Nueva Orden\n2.- Modificar Orden\n3.- Eliminar o Cancelar Orden\n4.- Lista de Ordenes\n5.- Limpiar Pantalla\n6.- Salir\n");
		scanf_s("%i", &opcion);

		system("cls");

		switch (opcion)
		{
		case 1: {

			numero++;

			Menu nuevaOrden;

			nuevaOrden.RazonSocial;

			nuevaOrden.Nombre;

			nuevaOrden.IVA;

			nuevaOrden.ticket = numero;

			nuevaOrden.Fecha->tm_mday;
			nuevaOrden.Fecha->tm_mon + 1;
			nuevaOrden.Fecha->tm_year + 1900;


			printf("Codigos\t\t\t Productos\t\t\t Precio\n");
			for (const auto& producto : productos) {
				printf("%d. %-35s $%.2f\n", producto.first, producto.second.first.c_str(), producto.second.second * 1.16);//Multiplico por 1.16 para que se muestre el valor con iva incluido 
			}

			//Se verifica el codigo comparandolo en el map y se agrega un contador de productos 
			do {
				printf("Seleccione un producto (0 para salir): ");
				scanf_s("%d", &opcion);

				if (productos.find(opcion) != productos.end() && opcion != 0) {
					printf("Ha seleccionado: %s - $%.2f\n", productos[opcion].first.c_str(), productos[opcion].second * 1.16);
					contador++;
					// Agregar el producto seleccionado al mapa de productos seleccionados
					if (nuevaOrden.productosSeleccionados.find(opcion) != nuevaOrden.productosSeleccionados.end()) {
						nuevaOrden.productosSeleccionados[opcion]++;
					}
					else {
						nuevaOrden.productosSeleccionados[opcion] = 1;
					}
					nuevaOrden.TotalCompra += productos[opcion].second * 1.16;  // Sumar el precio del producto al total
				}
				else if (opcion != 0) {
					printf("Opción no válida. Por favor, seleccione un producto válido.\n");
				}
			} while (opcion != 0);

			system("cls");

			//Imprime la lista de productos seleccionados
			printf("\nProductos seleccionados:\n");
			printf("%-40s %-10s %-10s\n", "Producto", "Cantidad", "Precio");
			for (const auto& producto : nuevaOrden.productosSeleccionados) {
				printf("%-40s %-10d $%-10.2f\n", productos[producto.first].first.c_str(), producto.second, productos[producto.first].second * producto.second * 1.16);
			}
			//Imprime la cantidad de productos
			printf("Ha seleccionado %d productos. Gracias por su compra.\n", contador);
			printf("Total a pagar: $%.2f\n", nuevaOrden.TotalCompra);  // Imprimir el total de la compra

			Orden.push_back(nuevaOrden);


			printf("Orden registrada\n");

			cin.ignore();

			return 0;


		}
			  //Modificar Orden	  
		case 2: {}

			  //Eliminar o Cancelar
		case 3: {}

			  //Lista de Ordenes
		case 4: {

		}
			  if (Orden.empty()) {
				  printf("No hay citas registradas:\n\n\n");

			  }
			  else {
				  printf("Registro de citas:\n");
				  for (const Menu& Impr : Orden) {
				  
					  printf("Fecha: % 02d / % 02d / % d\n", Impr.Fecha->tm_mday, Impr.Fecha->tm_mon + 1, Impr.Fecha->tm_year+1900);
					  printf("Empleado: %s\n", Impr.Nombre);
					  printf();

				  }

				  }

				  //Limpiar Pantalla
		case 5: {
			system("cls");
			break;

		}

			  //Salir
		case 6: {}

		default: {}

			  }


	} while (opcion != 6);

}
