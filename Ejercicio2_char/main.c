#include <stdio.h>

int main()
{
    int semilla=4;
    unsigned int metodo=1;
    string archivo_entrada="metodo1_char_codificado.txt";
    string archivo_salida="metodo1_char_decodificado.txt";

    // Comprobar si el archivo fuente existe
    /*ifstream fin;
    fin.open(archivo_entrada);

    while(!fin.is_open()){
        cout << "Ingrese nombre del archivo fuente: ";
        cin >> archivo_entrada;
        fin.open(archivo_entrada);
        if (!fin.is_open()) cout << "El archivo no existe. \n";
    }

    cout << "Ingrese semilla de codificacion: ";
    cin >> semilla;

    while(metodo!=1 && metodo!=2){
        cout << "(1) Primer metodo. \n(2) Segundo metodo. \nIngrese metodo de codificacion: ";
        cin >> metodo;
        if (metodo!=1 && metodo!=2) cout << "Metodo invalido \n";
    }*/



    return 0;
}
