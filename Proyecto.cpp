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


int main() {
    //Configurar consola para tildes y ñ

    system("chcp 65001 > nul");
    int opcion = 0;

    return 0;
}
