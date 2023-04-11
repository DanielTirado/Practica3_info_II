#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string convertir_a_binario(string archivo_entrada){
    ifstream fin;
    string linea;

    fin.open(archivo_entrada);

    getline(fin, linea);

    fin.seekg(0);

    string binario;

    while (fin.good()){
        int ascii = (char)fin.get();
        if (ascii<0) break;

        string Byte="";
        while (ascii>0){
            if (ascii%2==0){
                    Byte = "0" + Byte;
                    ascii /= 2;
            }

            else {
                Byte = "1" + Byte;
                ascii /=2;
            }
        }

        // Verificación de que el byte está completo
        while (Byte.length()<8){
            Byte = "0" + Byte;
        }

        binario += Byte;
    }

    fin.close();

    return binario;
}


int main()
{
    int semilla=0;
    unsigned int metodo=0;
    string archivo_entrada;
    string archivo_salida;

    // Comprobar si el archivo fuente existe
    ifstream fin;
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
    }

    if (metodo == 1){

        ofstream fout;

        cout << "Ingrese el archivo de salida: ";
        cin >> archivo_salida;

        fout.open(archivo_salida);

        string codificado = convertir_a_binario(archivo_entrada);

        int cantidad_de_bloques;
        cantidad_de_bloques=codificado.length()/semilla;

        int cont_cero = 0;
        int cont_uno = 0;

        for (int i=0; i<semilla; i++){
            if (codificado[i]=='0') {
                codificado[i]='1';
                cont_cero++;
            }
            else{
                codificado[i]='0';
                cont_uno++;
            }
        }

        for (int i=1; i<=cantidad_de_bloques; i++){

            int indice = (semilla*i)-1;


            // Primer regla
            if (cont_cero==cont_uno){

                cont_cero=0;
                cont_uno=0;
                indice++;
                for (int j=0; j<semilla; j++){
                    if (codificado[indice]=='0') {
                        codificado[indice]='1';
                        cont_cero++;
                    }
                    else{
                        codificado[indice]='0';
                        cont_uno++;
                    }
                    indice++;
                }
            }

            // Segunda regla
            else if(cont_cero>cont_uno){

                cont_cero=0;
                cont_uno=0;

                // Contar los ceros y los unos
                indice++;
                for (int f=0; f<semilla; f++){
                    if (codificado[indice+f]=='0') cont_cero++;
                    else cont_uno++;
                }
                indice--;

                for (int k=2; k<=semilla; k+=2){
                    indice+=2;
                    if (codificado[indice]=='0') codificado[indice]='1';
                    else codificado[indice]='0';
                }
            }


            // Tercera regla
            else if (cont_cero<cont_uno && semilla > 2){

                cont_cero=0;
                cont_uno=0;

                // Contar los ceros y los unos
                indice++;
                for (int f=0; f<semilla; f++){
                    if (codificado[indice+f]=='0') cont_cero++;
                    else cont_uno++;
                }
                indice--;

                for (int l=3; l<=semilla; l+=3){
                    indice+=3;
                    if (codificado[indice]=='0') {
                        codificado[indice]='1';
                        cont_cero++;
                    }
                    else {
                        codificado[indice]='0';
                        cont_uno++;
                    }
                }
            }

        }

        fout << codificado;
        fout.close();
    }

    else{
        ofstream fout;

        cout << "Ingrese el archivo de salida: ";
        cin >> archivo_salida;

        fout.open(archivo_salida);

        string binario = convertir_a_binario(archivo_entrada);
        string codificado = binario;

        int tamano_binario = binario.length();

        for (int i=0; i<tamano_binario; i++) codificado[i]='0';

        int cantidad_de_bloques;
        cantidad_de_bloques=binario.length()/semilla;

        for (int i=0; i<cantidad_de_bloques; i++){

            int indice = (semilla*i);

            codificado[indice]= binario[((i+1)*semilla)-1];

            for (int j=1; j<semilla; j++){
                codificado[indice+j] = binario[indice+j-1];
            }
        }

        fout << codificado;
        fout.close();
    }

    return 0;
}
