#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<windows.h>

using namespace std;


struct Producto {
    int codigo; 
    string nombre;
    int cantidad; 
    float precio; 
};

const string archivoDatos = "tienda.txt";

void guardarProducto(Producto& p) {
    //Escribimos al final del archivo nuestro nuevo producto
    ofstream archivo(archivoDatos, ios::app);
    if (archivo.is_open()) {
        archivo<<p.nombre<<";"
        <<p.codigo<<";"
        <<p.cantidad<<";"
        <<p.precio<<"\n";
    }else {
        cerr<<"No se pudo abrir el archivo para guardar\n";
    }
}

//Sobreescribir todo el archivo, para borrar el contenido anterior y escribir
//todo el vector, necesario para modificar o eliminar registros existentes
//ya que los archivos de texto no permite edicion secuencial (in situ).
void guardarTodo(vector<Producto>& productos) {
    ofstream archivo(archivoDatos);
    if (archivo.is_open()) {
        //Recorro todo el vector y lo sobrescribo en el archivo
        for (auto& p : productos) {
        	archivo<<p.nombre<<";"
        	<<p.codigo<<";"
        	<<p.cantidad<<";"
        	<<p.precio<<"\n";
        }
    }
}

vector<Producto> cargarProductos() {
    vector<Producto> productos;
    ifstream archivo(archivoDatos);

    if (archivo.is_open()) {
        string linea;
        //Leer linea por linea hasta el final del archivo
        while (getline(archivo,linea)) {
            //Ignorar lineas en blanco o vacias
            if (linea.empty()) {
                continue;
            }
            //Parseo de la linea, tomar datos usando ";"como delimitador
            vector<string>produ;
            size_t pos = 0;
            //Buscar cada ";" y extrae el texto antes de el
            while ((pos = linea.find(";")) != string::npos) {
                produ.push_back(linea.substr(0,pos)); //Extrae campo
                linea.erase(0,pos+1); //Elimina lo extraido
            }
            produ.push_back(linea);
            if (produ.size() == 4) {
                Producto p;
                p.codigo = stoi(produ[0]);
                p.nombre = produ[1];
                p.cantidad = stoi(produ[2]);
                p.precio = stof(produ[3]);
                productos.push_back(p);
            }
        }
    }
    return productos;
}

int main() {
    //Configurar consola para tildes y ñ
    system("chcp 65001 > nul");
    int opcion = 0;
    do {
	    cout << "\n---Sistema de Registro de Productos---\n";
	    cout << "1. Agregar Producto\n";
	    cout << "2. Ver lista de Productos\n";
	    cout << "3. Actualizar Producto\n";
	    cout << "4. Eliminar Producto\n";
	    cout << "5. Salir\n";
	    cout << "Seleccione una opción: ";
	    cin >> opcion;
	    cin.ignore();
	    //Estructura de las opciones
	    if (opcion == 1) {  
	        
	    }else if (opcion == 2) {
	    	
	    }else if (opcion == 3) {

	    }else if (opcion == 4) {
	    	
	    }else if(opcion == 5){
			cout<<"Saliendo del sistema...\n";
		}else {
	            cout<<"Opción no válida. Ingresa un número del 1 al 4";
	        }


	    } while (opcion != 5);
    return 0;
}
