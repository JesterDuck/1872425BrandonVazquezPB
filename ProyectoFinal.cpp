//ProyectoFinal.cpp 
//Brandon Alberto Vazquez Alonso   Matricula:1872425  Gpo:051

#define _CRT_SECURE_NO_WARNINGS //Desactiva las advertencias de obsolecencia 
#include <iostream>
#include <string> 
#include <ctime> //Libreria para usar la fecha del dispositivo
#include <vector> //biblioteca para crear un vector de datos
#include <cstdio> //biblioteca para usar scanf_s
#include <map> //crear una lista de productos y precios
#include <conio.h>//Getche
#include <fstream>//Guardar Archivos



using namespace std;

struct Menu {
	//Datos del restaurante
	string RazonSocial = "Garbage Burgers S.A de C.V";//Razon Social del restaurante
	string Nombre; 
	double TotalCompra = 0;// Variable para almacenar el total de la compra
    double Descuentos = 0;
	double Propina = 0;
	string IVA = "16% por precio unitario";
	map<int, int> productosSeleccionados;// Mapa para almacenar los productos seleccionados
	int ConProd = 0;//Se guardan el contador de cada orden 
	int ticket = 0;//numero de ticket
	string status = "NORMAL";

	//Fecha
	time_t Tiempo = time(nullptr); //: Obtiene el tiempo actual en segundos desde la época (el 1 de enero de 1970 a las 00:00:00 UTC).
	tm* Fecha = localtime(&Tiempo); //estructura que contiene los componentes de fecha y hora, como año, mes, día, hora, minuto, segundo, etc. 

};

vector<Menu>Orden;// Declaración global del vector Orden para poder usarlo dentro del void
int opcion = 0, numero = 0, TicketMod = 0;;// La declaro fuera del main para poder usarlo en el void

void ListaProductos(const map<int, pair<string, double>>& productos);
void imprimirDetallesOrden(const Menu& orden, const map<int, pair<string, double>>& productos);
void ALTA(Menu& empleado, map<int, pair<string, double>> productos);
void MODIFICAR(vector<Menu>& Orden, const map<int, pair<string, double>>& productos, int& TicketMod);
void ELIMINAR(vector<Menu>& Orden, const map<int, pair<string, double>>& productos, Menu& empleado);
void LISTA(const vector<Menu>& Orden, const map<int, pair<string, double>>& productos);
void CAMBIARNOMBRE(Menu& empleado);
void ARCHIVOS(const vector<Menu>& Orden, const map<int, pair<string, double>>& productos);

//Se usan en Alta y Modificar
void ModOrden(vector<Menu>& Orden, const map<int, pair<string, double>>& productos, const int& TicketMod);



int main()
{
	//Se usa el map para definir una lista de productos con sus códigos y precios sin IVA 
	//Se pueden agregar mas productos sin alterar el codigo 
	map<int, pair<string, double>> productos = {
		{1, {"Hamburguesa de Res", 82.50}},
		{2, {"Hamburguesa Doble de Res", 107.75}},
		{3, {"Hamburguesa de pollo", 77.50}},
		{4, {"Hamburguesa Doble de Pollo", 99}},
		{5, {"Papas a la Francesa Chicas", 30}},
		{6, {"Papas a la Francesa Grandes", 47.4}},
		{7, {"Aros de Cebolla Chicas", 30}},
		{8, {"Aros de Cebolla Grandes", 47.4}},
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
		{19, {"Galleta de Chispas de Chocolate", 14.66}},
	    {20, {"*PROMOCION* Hamburguesa Sencilla 2x1",82.50 }},
		{21, {"*PROMOCION* Papas Chicas 2x1", 30}},
		{22, {"*PROMOCION* Combo 1 (3 prouctos)", 129.31}},
		{23, {"*PROMOCION* Combo 2 (4 productos)", 181.0}}
	};


	int opc1;

	//Nombre del empleado se guarda en una estructura aparte
	Menu empleado;
	printf_s("Ingrese nombre de Empleado:\n");
	getline(cin, empleado.Nombre);

	system("cls");

	do {
		//int contador = 0;

		printf_s("Elija una opcion:\n1.- Nueva Orden\n2.- Modificar Orden\n3.- Eliminar o Cancelar Orden\n4.- Lista de Ordenes\n5.- Limpiar Pantalla\n6.- Cambiar Nombre\n7.- Salir\n");
		scanf_s("%i", &opc1);

		system("cls");

		switch (opc1)
		{
		case 1:
			ALTA(empleado, productos);
			break;

		case 2:
			MODIFICAR(Orden, productos, TicketMod);
			break;

		case 3:
			ELIMINAR(Orden, productos, empleado);
			break;

		case 4:
			LISTA(Orden, productos);
			break;

		case 5:
			system("cls");
			break;

		case 6:
			CAMBIARNOMBRE(empleado);
			break;

		case 7:
			ARCHIVOS(Orden, productos);
			break;

		default:
			printf_s("Opcion incorrecta:\n\n");
		}
		cin.ignore();

	} while (opc1 != 7);
}

void ListaProductos(const map<int, pair<string, double>>& productos)
{
	printf("COMBOS\nCombo 1: HamburguesaSencilla, RefrescoChico, Papas o Aros Chicos.......$150\nCombo 2: HamburguesaDoble, Refresco Grande, Aros o Papas Grandes,Cono(Vainilla).......$210\n\n");
	printf("PROMOCIONES\nPromocion 1: HamburguesaSencilla 2x1\nPromocion 2: PapasChicas 2x1\n\n");

	printf("Codigos\t\t\t Productos\t\t\t Precio\n");
	for (const auto& producto : productos) {
		printf("%d. %-35s $%.2f\n", producto.first, producto.second.first.c_str(), producto.second.second * 1.16);//Multiplico por 1.16 para que se muestre el valor con iva incluido 
	}
	return;
}
void ALTA(Menu& empleado, map<int, pair<string, double>> productos)
{

	string letra;
	int propinita;
	int opcion = 0;

	//Creo la estructura para guardar los datos de las ordenes 
	Menu nuevaOrden;

	numero++;
	nuevaOrden.ticket = numero;

	//Razon Social y Nombre del restaurante
	nuevaOrden.RazonSocial;
	// Copiar el nombre del empleado a esta nueva estructura
	nuevaOrden.Nombre = empleado.Nombre;
	//Texto de cuanto iva se paga por producto
	nuevaOrden.IVA;
	//Fecha usando la libreria ctime
	nuevaOrden.Fecha->tm_mday;
	nuevaOrden.Fecha->tm_mon + 1;
	nuevaOrden.Fecha->tm_year + 1900;

	//Llamo al void de la impresion de productos
	ListaProductos(productos);

	//Se verifica el codigo comparandolo en el map y se agrega un contador de productos 
	do {

		printf_s("Seleccione un producto (0 para salir): ");
		scanf_s("%d", &opcion);

		if (productos.find(opcion) != productos.end() && opcion != 0) {
			//Verificar si es la primera promocion
			//Promocion 1
			if (opcion == 20) {
				printf_s("Se selecciono: %s - $% .2f\n", productos[opcion].first.c_str(), productos[opcion].second * 1.16);
				nuevaOrden.ConProd += 2;  // Agregar 2 productos al contador
				nuevaOrden.productosSeleccionados[opcion] += 1;  // Agregar dos productos al mapa
				nuevaOrden.TotalCompra += productos[opcion].second*1.16;  // Sumar el precio de la promoción al total
				nuevaOrden.Descuentos += productos[opcion].second * 1.16;
		
			}
			else 
				//Promocion 2
				if (opcion == 21) {
					printf("Se selecciono: %s - $% .2f\n", productos[opcion].first.c_str(), productos[opcion].second*1.16);
					nuevaOrden.ConProd += 2;  // Agregar 2 productos al contador
					nuevaOrden.productosSeleccionados[opcion] += 1;  // Agregar dos productos al mapa
					nuevaOrden.TotalCompra += productos[opcion].second*1.16;  // Sumar el precio de la promoción al total
					nuevaOrden.Descuentos += productos[opcion].second * 1.16;
		
				}else
					//Combo 1
					if(opcion == 22){
						printf("Se selecciono: %s - $% .2f\n", productos[opcion].first.c_str(), productos[opcion].second * 1.16);
						nuevaOrden.ConProd += 3;  // Agregar 3 productos al contador
						nuevaOrden.productosSeleccionados[opcion] += 1;  // Agregar dos productos al mapa
						nuevaOrden.TotalCompra += productos[opcion].second*1.16;  // Sumar el precio del combo al total
						nuevaOrden.Descuentos += 3.47;
				
					}else
						//Combo 2
						if (opcion == 23) {
							printf("Se selecciono: %s - $% .2f\n", productos[opcion].first.c_str(), productos[opcion].second * 1.16);
							nuevaOrden.ConProd += 4;  // Agregar 4 productos al contador
							nuevaOrden.productosSeleccionados[opcion] += 1;  // Agregar dos productos al mapa
							nuevaOrden.TotalCompra += productos[opcion].second * 1.16;  // Sumar el precio del combo al total
							nuevaOrden.Descuentos += 27.95;
							
						}else{
							// Lógica para productos que no son promociones
							printf("Ha seleccionado: %s - $%.2f\n", productos[opcion].first.c_str(), productos[opcion].second * 1.16);
						nuevaOrden.ConProd++;
						// Agregar el producto seleccionado al mapa de productos seleccionados
						if (nuevaOrden.productosSeleccionados.find(opcion) != nuevaOrden.productosSeleccionados.end()) {
							nuevaOrden.productosSeleccionados[opcion]++;
						}
						// El else sirve para saber si se pidió más de un producto del mismo tipo
						else {
							nuevaOrden.productosSeleccionados[opcion] = 1;
						}
						nuevaOrden.TotalCompra += productos[opcion].second * 1.16;  // Sumar el precio del producto al total
						
		                }
	    } 
		else if (opcion != 0) {
		        printf("Opcion no valida. Por favor, seleccione un producto valido.\n");

			
		}

	

	} while (opcion != 0);

	system("cls");
	//Do While para poder agregar la propina si se desea 
	do {
		printf("Desea Agregar Propina S/N\n");
		letra = _getche();
		printf("\n");

		if (letra == "s" || letra == "S") {
			printf("Cuanto de propina desea dejar?\n1: 10 por ciento, 2: 15 por ciento o 3: 20 por ciento\n");
			scanf_s("%d", &propinita);
			//guardo la opcion para poder modificar la propina en la opcion de modificar
		
			while (propinita != 1 && propinita != 2 && propinita != 3) {
				printf("Seleccione una opcion correcta.\n");
				printf("Cuanto de propina desea dejar?\n1: 10 por ciento, 2: 15 por ciento o 3: 20 por ciento\n");
				scanf_s("%d", &propinita);

			}

			switch (propinita) {
			case 1:
				nuevaOrden.Propina = nuevaOrden.TotalCompra * 0.1;
				break;
			case 2:
				nuevaOrden.Propina = nuevaOrden.TotalCompra * 0.15;
				break;
			case 3:
				nuevaOrden.Propina = nuevaOrden.TotalCompra * 0.2;
				break;

			default:
				printf("Ingrese una opcion correcta\n");
			}
			

			// Actualizar el total de la compra después de agregar la propina
			nuevaOrden.TotalCompra += nuevaOrden.Propina;
			//Imprime la lista de productos seleccionados
			printf("\nProductos seleccionados:\n");
			printf("%-40s %-10s %-10s\n", "Producto", "Cantidad", "Precio");
			for (const auto& producto : nuevaOrden.productosSeleccionados) {
				printf("%-40s %-10d $%-10.2f\n", productos[producto.first].first.c_str(), producto.second, productos[producto.first].second * producto.second * 1.16);
			}
			//Imprime la cantidad de productos
			printf("Ha seleccionado %d productos en total. Gracias por su compra.\n", nuevaOrden.ConProd);
			printf("Propina: $%.2f\n", nuevaOrden.Propina);//Imprime la propina
			printf("Descuentos: $%.2f\n", nuevaOrden.Descuentos);//Imprime los descuentos si hay
			printf("Total a pagar: $%.2f\n", nuevaOrden.TotalCompra);  // Imprimir el total de la compra
		

			Orden.push_back(nuevaOrden);


			printf("Orden registrada\n\n");
			break;
		}
		else
			if (letra == "n" || letra == "N") {
				//Imprime la lista de productos seleccionados
				printf("\nProductos seleccionados:\n");
				printf("%-40s %-10s %-10s\n", "Producto", "Cantidad", "Precio");
				for (const auto& producto : nuevaOrden.productosSeleccionados) {
					printf("%-40s %-10d $%-10.2f\n", productos[producto.first].first.c_str(), producto.second, productos[producto.first].second * producto.second * 1.16);
				}
				//Imprime la cantidad de productos
				printf("Ha seleccionado %d productos en total. Gracias por su compra.\n", nuevaOrden.ConProd);
				printf("Propina: $%.2f\n", nuevaOrden.Propina);//imprime 0 porque no se dejo propina
				printf("Descuentos: $%.2f\n", nuevaOrden.Descuentos);//Imprime los descuentos si hay
				printf("Total a pagar: $%.2f\n", nuevaOrden.TotalCompra);  // Imprimir el total de la compra
				Orden.push_back(nuevaOrden);


				printf("Orden registrada\n\n");
				break;
			}
			else
				printf("Ingrese una letra correcta");
		 
	} while (letra != "S" || letra != "s" || letra != "N" || letra != "n");

}
void LISTA(const vector<Menu>& Orden, const map<int, pair<string, double>>& productos)
{
	int busqueda = 0;
	if (Orden.empty()) {
		printf("No hay ordenes registradas:\n\n");

	}
	else {

		int listaopc = 0, i = 0;

		printf("1:Buscar por numero de ticket\t2:Mostrar Todos\t(3 para salir)\n");
		scanf_s("%d", &listaopc);

		do {



			switch (listaopc)
			{
			case 1:
				do {
					printf("Ingrese el numero de ticket que quiere ver\t(0 para salir)\n");
					scanf_s("%d", &busqueda);

					if (busqueda == 0) {
						break; // Salir del bucle
					}

					// Validar que el número de ticket sea válido
				
					if (busqueda - 1 >= 0 && busqueda - 1 < Orden.size()) {
						const Menu& orden = Orden[busqueda - 1];



						if (orden.status == "ELIMINADO" && orden.ticket == busqueda - 1) {
							printf("**Ticket %d Eliminado**\n", orden.ticket);
							printf("* * * * * * * * * * * * * * * * * * * *\n\n");
						}
						else {
							printf("%s\n", orden.RazonSocial.c_str());
							printf("Fecha: %02d / %02d / %d\n", orden.Fecha->tm_mday, orden.Fecha->tm_mon + 1, orden.Fecha->tm_year + 1900);
							printf("Empleado: %s\n", orden.Nombre.c_str());
							printf("Numero de Ticket: %d\n", orden.ticket);

							// Imprimir la lista de productos seleccionados
							printf("\nProductos seleccionados:\n");
							printf("%-40s %-10s %-10s\n", "Producto", "Cantidad", "Precio");
							for (const auto& producto : orden.productosSeleccionados) {
								printf("%-40s %-10d $%-10.2f\n", productos.at(producto.first).first.c_str(), producto.second, productos.at(producto.first).second * producto.second * 1.16);
							}

							// Imprimir la cantidad de productos
							printf("Ha seleccionado %d productos. Gracias por su compra.\n", orden.ConProd);
							printf("Descuentos: %.2f\n", orden.Descuentos);
							printf("Propina : %.2f\n", orden.Propina);
							printf("IVA: %s\n", orden.IVA.c_str());
							printf("Total a pagar: $%.2f\n", orden.TotalCompra);

							// Estado específico (ELIMINADO o CANCELADO)
							if (orden.status == "CANCELADO") {
								printf("**Ticket %d Cancelado**\n", orden.ticket);
							}

							printf("* * * * * * * * * * * * * * * * * * * *\n\n");
						}break;
					}
					else {
						printf("Numero de ticket no valido. Intente de nuevo.\n");
					}
				} while (busqueda != 0);
				return;
				break;

			case 2:

				printf("Registro de ordenes:\n");
				for (const Menu& Impr : Orden) {
					imprimirDetallesOrden(Impr, productos);
				}
				return;
				break;
	
			case 3:
				//Salir del blucle
				return;
				break;

			default:
				printf("Opcion incorrecta:\n\n");
				return;
				break;
		    }

			}while (listaopc != 3);
		}
}
void CAMBIARNOMBRE(Menu& empleado)
{
	printf("Ingrese nombre de Empleado:\n");
	cin.ignore();
	getline(cin, empleado.Nombre);

	system("cls");
	printf("Nombre de Empleado actualizado a: %s\n\n", empleado.Nombre.c_str());
	printf("Click para continuar\n");
}
void MODIFICAR(vector<Menu>& Orden, const map<int, pair<string, double>>& productos, int& TicketMod)
{
	//Si no hay ordenes se muestra este texto
	if (Orden.empty()) {
		printf("No hay ordenes registradas\n");
		return;
	}
	
	
		// Mostrar la lista de órdenes para que el usuario elija cuál modificar
		printf("Ordenes\n\n");
		//El for recorre el vector Orden mientras i sea menor al tamaño del vector imprime lo que esta dentro 
		for (size_t i = 0; i < Orden.size(); ++i) {
			//Imprime el numero de ticket y el nombre del empleado
			printf("Ticket: #%d\nEmpleado: %s\n\n", Orden[i].ticket, Orden[i].Nombre.c_str());

		}

		// Pedir al usuario que elija una orden para modificar

			printf("Seleccione el ticket que desee modificar (0 para cancelar)\n");
			scanf_s("%d", &TicketMod);

			// Verificar si la orden seleccionada tiene el estado "ELIMINADO"
			if (TicketMod >= 1 && TicketMod <= Orden.size() && Orden[TicketMod - 1].status == "ELIMINADO") {
				printf("No se puede modificar una orden eliminada\n");
			
			}
			

			int seguro = 0, MOD = 0;

			do {

				if (TicketMod >= 1 && TicketMod  <= Orden.size()) {
					// Restar 1 para obtener el índice correcto en el vector
					Menu& ordenAModificar = Orden[TicketMod - 1];

					//Seleccion de la opcion a modificar
					printf("1:Modificar Orden\t2: Salir\n");
					scanf_s("%d", &MOD);

					// Aquí puedes realizar las modificaciones necesarias en la orden
					switch (MOD)
					{
					case 1:

						ModOrden(Orden, productos, TicketMod);
						break;

					case 2:
						//Salir del blucle
						return;
						break;

					default:

						printf("Opcion incorrecta:\n\n");
						break;
					}

					printf("Orden Modificada con exito\n");
				}
				else if (TicketMod != 0) {
					printf("Opcion no Valida\n");
				}break;

			} while (MOD != 2);
}
void ELIMINAR(vector<Menu>& Orden, const map<int, pair<string, double>>& productos, Menu& empleado)
{
	int TicketEliminar = 0;
	//Si no hay ordenes se muestra este texto
	if (Orden.empty()) {
		printf("No hay ordenes registradas\n");
		return;
	}
	else
	{

		// Mostrar la lista de órdenes para que el usuario elija cuál eliminar
		printf("Ordenes\n\n");
		//El for recorre el vector Orden mientras i sea menor al tamaño del vector imprime lo que esta dentro 
		for (size_t i = 0; i < Orden.size(); ++i) {
			//Imprime el numero de ticket y el nombre del empleado
			printf("Ticket: #%d\nEmpleado: %s\n\n", Orden[i].ticket, Orden[i].Nombre.c_str());

		}

		// Pedir al usuario que elija una orden para Eliminar o Cancelar

		do {
			printf("Seleccione el ticket que Eliminar o Cancelar (0 para Terminar)\n");
			scanf_s("%d", &TicketEliminar);

			int seguro = 0, MOD = 0;

			

				if (TicketEliminar >= 1 && TicketEliminar <= Orden.size()) {
					// Restar 1 para obtener el índice correcto en el vector
					Menu& ordenAModificar = Orden[TicketEliminar - 1];

					// Buscar la orden con el número de ticket 'TicketEliminar'
					auto it = find_if(Orden.begin(), Orden.end(), [TicketEliminar](const Menu& orden) {
						return orden.ticket == TicketEliminar;
						});


					//Seleccion de opciones
					printf("1:Eliminar Orden\t2:Cancelar Orden\t3:Salir\n");
					scanf_s("%d", &MOD);

					// Aquí puedes eliminar o cancelar tickets
					switch (MOD)
					{
					case 1:
						// Verificar si se encontró la orden
						if (it != Orden.end()) {
							// Modificar el estado de la orden encontrada
							it->status = "ELIMINADO";
							printf("Orden con ticket #%d **Eliminado**\n", TicketEliminar);
						}
						else {
							printf("No se encontro el ticket");
						}
						break;



					case 2:
						// Verificar si se encontró la orden
						if (it != Orden.end()) {
							// Modificar el estado de la orden encontrada
							it->status = "CANCELADO";
							printf("Orden con ticket #%d **Cancelado**\n", TicketEliminar);
						}
						else {
							printf("No se encontro el ticket");
						}
						break;




					case 3:
						//Salir del blucle
						return;
						break;

					default:

						printf("Opcion incorrecta:\n\n");
					}

					printf("Orden Eliminada/Cancelada con exito\n");
				}
				else if (TicketEliminar != 0) {
					printf("Opcion no Valida\n");
				}
			

		} while (TicketEliminar != 0);
	}
}
void ARCHIVOS(const vector<Menu>& Orden, const map<int, pair<string, double>>& productos)
{
	ofstream archivo; // clase ofstream para escribir archivos
	string ArchivoTexto = "Ordenes.txt";

	// Abro el archivo
	archivo.open(ArchivoTexto);

	// Verifica si el archivo se abrió correctamente
	if (!archivo.is_open())
	{
		printf("Error (No se pudo guardar el archivo");
		exit(1);
	}

	for (size_t i = 0; i < Orden.size(); ++i)
	{
		if (Orden[i].status != "ELIMINADO")
		{
			archivo << "Razon Social:" << Orden[i].RazonSocial << "\t\t\t"
				<< "Fecha:" << Orden[i].Fecha->tm_mday << "/" << Orden[i].Fecha->tm_mon + 1 << "/" << Orden[i].Fecha->tm_year + 1900 << "\n\n";

			archivo << "Status\tEmpleado\t# Ticket\tNombre Producto\t\tCantidad\tPrecio\tTotalProductos\tDescuentos\tPropina\tIVA%\tTotal\n";

			archivo << Orden[i].status << "\t" << Orden[i].Nombre << "\t\t" << Orden[i].ticket << "\t";

			for (const auto& producto : Orden[i].productosSeleccionados)
			{
				archivo << productos.at(producto.first).first << "\t\t" << producto.second << "\t\t" << productos.at(producto.first).second * producto.second * 1.16 << "\t\t";
			}

			archivo << Orden[i].Descuentos << "\t\t" << Orden[i].Propina << "\t\t" << Orden[i].IVA << "\t\t" << Orden[i].TotalCompra << "\n";
		}
	}

	// Cierro el archivo al final de la función
	archivo.close();

}
void ModOrden(vector<Menu>& Orden, const map<int, pair<string, double>>& productos, const int& TicketMod)
{
	string letra;
	int propinita;
	int opcion = 0;
	int TicketRepair = TicketMod - 1;
	//Vuelvo 0 todos los parametros que se van a modificar
	Orden[TicketRepair].ConProd = 0;
	Orden[TicketRepair].Descuentos = 0.0;
	Orden[TicketRepair].productosSeleccionados.clear();
	Orden[TicketRepair].Propina = 0.0;
	Orden[TicketRepair].status = "MODIFICADO";
	Orden[TicketRepair].TotalCompra = 0.0;


	//Void de impresion de productos
	ListaProductos(productos);

	//Se verifica el codigo comparandolo en el map y se agrega un contador de productos 
	do {
		printf("Seleccione un producto (0 para salir):");
		scanf_s("%d", &opcion);

		//El .at permite acceder a los elementos de un map y evita los errores con las corchetes []

		if (productos.find(opcion) != productos.end() && opcion != 0) {
			//Verificar si es la primera promocion
			//Promocion 1
			if (opcion == 20) {
				printf("Se selecciono: %s - $% .2f\n", productos.at(opcion).first.c_str(), productos.at(opcion).second * 1.16);
				Orden[TicketRepair].ConProd += 2;  // Agregar 2 productos al contador
				Orden[TicketRepair].productosSeleccionados[opcion] += 1;  // Agregar dos productos al mapa
				Orden[TicketRepair].TotalCompra += productos.at(opcion).second * 1.16;  // Sumar el precio de la promoción al total
				Orden[TicketRepair].Descuentos += productos.at(opcion).second * 1.16;

			}
			else
				//Promocion 2
				if (opcion == 21) {
					printf("Se selecciono: %s - $% .2f\n", productos.at(opcion).first.c_str(), productos.at(opcion).second * 1.16);
					Orden[TicketRepair].ConProd += 2;  // Agregar 2 productos al contador
					Orden[TicketRepair].productosSeleccionados[opcion] += 1;  // Agregar dos productos al mapa
					Orden[TicketRepair].TotalCompra += productos.at(opcion).second * 1.16;  // Sumar el precio de la promoción al total
					Orden[TicketRepair].Descuentos += productos.at(opcion).second * 1.16;

				}
				else
					//Combo 1
					if (opcion == 22) {
						printf("Se selecciono: %s - $% .2f\n", productos.at(opcion).first.c_str(), productos.at(opcion).second * 1.16);
						Orden[TicketRepair].ConProd += 3;  // Agregar 3 productos al contador
						Orden[TicketRepair].productosSeleccionados[opcion] += 1;  // Agregar dos productos al mapa
						Orden[TicketRepair].TotalCompra += productos.at(opcion).second * 1.16;  // Sumar el precio del combo al total
						Orden[TicketRepair].Descuentos += 3.47;

					}
					else
						//Combo 2
						if (opcion == 23) {
							printf("Se selecciono: %s - $% .2f\n", productos.at(opcion).first.c_str(), productos.at(opcion).second * 1.16);
							Orden[TicketRepair].ConProd += 4;  // Agregar 4 productos al contador
							Orden[TicketRepair].productosSeleccionados[opcion] += 1;  // Agregar dos productos al mapa
							Orden[TicketRepair].TotalCompra += productos.at(opcion).second * 1.16;  // Sumar el precio del combo al total
							Orden[TicketRepair].Descuentos += 27.95;

						}
						else {
							// Lógica para productos que no son promociones
							printf("Ha seleccionado: %s - $%.2f\n", productos.at(opcion).first.c_str(), productos.at(opcion).second * 1.16);
							Orden[TicketRepair].ConProd++;
							// Agregar el producto seleccionado al mapa de productos seleccionados
							if (Orden[TicketRepair].productosSeleccionados.find(opcion) != Orden[TicketRepair].productosSeleccionados.end()) {
								Orden[TicketRepair].productosSeleccionados[opcion]++;
							}
							// El else sirve para saber si se pidió más de un producto del mismo tipo
							else {
								Orden[TicketRepair].productosSeleccionados[opcion] = 1;
							}
							Orden[TicketRepair].TotalCompra += productos.at(opcion).second * 1.16;  // Sumar el precio del producto al total

						}
		}
		else if (opcion != 0) {
			printf("Opcion no valida. Por favor, seleccione un producto valido.\n");


		}



	} while (opcion != 0);

	system("cls");
	//Do While para poder agregar la propina si se desea 
	do {
		printf("Desea Agregar Propina S/N\n");
		letra = _getche();
		printf("\n");

		if (letra == "s" || letra == "S") {
			printf("Cuanto de propina desea dejar?\n1: 10 por ciento, 2: 15 por ciento o 3: 20 por ciento\n");
			scanf_s("%d", &propinita);
			//guardo la opcion para poder modificar la propina en la opcion de modificar

			while (propinita != 1 && propinita != 2 && propinita != 3) {
				printf("Seleccione una opcion correcta.\n");
				printf("Cuanto de propina desea dejar?\n1: 10 por ciento, 2: 15 por ciento o 3: 20 por ciento\n");
				scanf_s("%d", &propinita);

			}

			switch (propinita) {
			case 1:
				Orden[TicketRepair].Propina = Orden[TicketRepair].TotalCompra * 0.1;
				break;
			case 2:
				Orden[TicketRepair].Propina = Orden[TicketRepair].TotalCompra * 0.15;
				break;
			case 3:
				Orden[TicketRepair].Propina = Orden[TicketRepair].TotalCompra * 0.2;
				break;

			default:
				printf("Ingrese una opcion correcta\n");
				break;
			}

			// Actualizar el total de la compra después de agregar la propina
			Orden[TicketRepair].TotalCompra += Orden[TicketRepair].Propina;
			//Imprime la lista de productos seleccionados
			printf("\nProductos seleccionados:\n");
			printf("%-40s %-10s %-10s\n", "Producto", "Cantidad", "Precio");
			for (const auto& producto : Orden[TicketRepair].productosSeleccionados) {
				printf("%-40s %-10d $%-10.2f\n", productos.at(producto.first).first.c_str(), producto.second, productos.at(producto.first).second * producto.second * 1.16);
			}
			//Imprime la cantidad de productos
			printf("Ha seleccionado %d productos en total. Gracias por su compra.\n", Orden[TicketRepair].ConProd);
			printf("Propina: $%.2f\n", Orden[TicketRepair].Propina);//Imprime la propina
			printf("Descuentos: $%.2f\n", Orden[TicketRepair].Descuentos);//Imprime los descuentos si hay
			printf("Total a pagar: $%.2f\n", Orden[TicketRepair].TotalCompra);  // Imprimir el total de la compra


			//Orden.push_back(Orden[TicketRepair]);


			printf("Orden Modificada\n\n");
			break;
		}
		else
			if (letra == "n" || letra == "N") {
				//Imprime la lista de productos seleccionados
				printf("\nProductos seleccionados:\n");
				printf("%-40s %-10s %-10s\n", "Producto", "Cantidad", "Precio");
				for (const auto& producto : Orden[TicketRepair].productosSeleccionados) {
					printf("%-40s %-10d $%-10.2f\n", productos.at(producto.first).first.c_str(), producto.second, productos.at(producto.first).second * producto.second * 1.16);
				}
				//Imprime la cantidad de productos
				printf("Ha seleccionado %d productos en total. Gracias por su compra.\n", Orden[TicketRepair].ConProd);
				printf("Propina: $%.2f\n", Orden[TicketRepair].Propina);//imprime 0 porque no se dejo propina
				printf("Descuentos: $%.2f\n", Orden[TicketRepair].Descuentos);//Imprime los descuentos si hay
				printf("Total a pagar: $%.2f\n", Orden[TicketRepair].TotalCompra);  // Imprimir el total de la compra

				//Orden.push_back(Orden[TicketRepair]);


				printf("Orden registrada\n\n");
				break;
			}
			else
				printf("Ingrese una letra correcta");

	} while (letra != "S" || letra != "s" || letra != "N" || letra != "n");

	printf("Propina Modificada\n\n");

}				
void imprimirDetallesOrden(const Menu& orden, const map<int, pair<string, double>>& productos) 
{

	// Si el estado es MODIFICADO o cualquier otro estado que quieras mostrar
	if (orden.status == "MODIFICADO" || orden.status == "NORMAL" || orden.status == "CANCELADO") {
		printf("%s\n", orden.RazonSocial.c_str());
		printf("Fecha: %02d / %02d / %d\n", orden.Fecha->tm_mday, orden.Fecha->tm_mon + 1, orden.Fecha->tm_year + 1900);
		printf("Empleado: %s\n", orden.Nombre.c_str());
		printf("Numero de Ticket: %d\n", orden.ticket);

		// Imprimir la lista de productos seleccionados
		printf("\nProductos seleccionados:\n");
		printf("%-40s %-10s %-10s\n", "Producto", "Cantidad", "Precio");
		for (const auto& producto : orden.productosSeleccionados) {
			printf("%-40s %-10d $%-10.2f\n", productos.at(producto.first).first.c_str(), producto.second, productos.at(producto.first).second * producto.second * 1.16);
		}

		// Imprimir la cantidad de productos
		printf("Ha seleccionado %d productos. Gracias por su compra.\n", orden.ConProd);
		printf("Descuentos: %.2f\n", orden.Descuentos);
		printf("Propina : %.2f\n", orden.Propina);
		printf("IVA: %s\n", orden.IVA.c_str());
		printf("Total a pagar: $%.2f\n", orden.TotalCompra);

		// Estado específico (ELIMINADO o CANCELADO)
		if (orden.status == "CANCELADO") {
			printf("**Ticket %d Cancelado**\n", orden.ticket);
		}

		printf("* * * * * * * * * * * * * * * * * * * *\n\n");
	}
}
		

		
	

