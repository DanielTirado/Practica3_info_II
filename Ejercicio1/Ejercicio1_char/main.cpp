#include <iostream>
#include <fstream>
#include <string>

using namespace std;

char *convertir_a_binario(string archivo_entrada){
    ifstream fin;
    string linea;
    int long_linea;

    fin.open(archivo_entrada);

    getline(fin, linea);
    long_linea=linea.length();


    fin.seekg(0);

    char binario[long_linea][8];

    int tamano_binario = long_linea*8;
    char* binario_en_1_linea = new char[tamano_binario];

    for (int i=0; i<long_linea; i++){
        for (int j=0; j<8; j++){
            binario[i][j]='0';
        }
    }

    unsigned int i=0;
    while (fin.good()){
        unsigned int j=0;
        int ascii = (char)fin.get();

        while (ascii>0){
            if (ascii%2==0){
                    binario[i][7-j] = '0';
                    ascii /= 2;
            }

            else {
                binario[i][7-j]= '1';
                ascii /=2;
            }
            j++;
        }
        i++;
    }
    fin.close();

    int k=0;
    for (int i=0; i<long_linea; i++){
        for (int j=0; j<8; j++){
            binario_en_1_linea[k] = binario[i][j];
            k++;
        }
    }

    return binario_en_1_linea;
}


int main()
{
    int semilla;
    unsigned int metodo;
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

        char *codificado = convertir_a_binario(archivo_entrada);

        int cont_cero = 0;
        int cont_uno = 0;

        // Primer bloque
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

        string linea;
        int cantidad_de_bloques;

        getline(fin, linea);
        cantidad_de_bloques=linea.length()*8/semilla;
        fin.close();

        int indice = 0 ;
        for (int i=1; i<cantidad_de_bloques; i++){

            indice = (semilla*i)-1;


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
                for (int f=0; f<semilla; f++){
                    if (codificado[indice+1+f]=='0') cont_cero++;
                    else cont_uno++;
                }

                for (int k=2; k<=semilla; k+=2){
                    indice+=2;
                    if (codificado[indice]=='0') codificado[indice]='1';
                    else codificado[indice]='0';
                }
            }


            // Tercer regla
            else if (cont_cero<cont_uno && semilla > 2){

                cont_cero=0;
                cont_uno=0;

                // Contar los ceros y los unos
                for (int f=0; f<semilla; f++){
                    if (codificado[indice+1+f]=='0') cont_cero++;
                    else cont_uno++;
                }

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

        for (int n=0; n<cantidad_de_bloques*semilla; n++){
            fout << codificado[n];
        }
        fout.close();

    }

    // METODO 2
    else {
        ofstream fout;

        cout << "Ingrese el archivo de salida: ";
        cin >> archivo_salida;

        fout.open(archivo_salida);

        char *binario = convertir_a_binario(archivo_entrada);

        string linea;
        int cantidad_de_bloques;

        getline(fin, linea);

        int tamano_binario = linea.length()*8;

        cantidad_de_bloques = tamano_binario/semilla;
        fin.close();


        char codificado[tamano_binario] = {'0'};

        for (int i=0; i<cantidad_de_bloques; i++){

            int indice = (semilla*i);

            codificado[indice]= binario[((i+1)*semilla)-1];

            for (int j=1; j<semilla; j++){
                codificado[indice+j] = binario[indice+j-1];
            }
        }

        for (int n=0; n<tamano_binario; n++){
            fout << codificado[n];
        }
        fout.close();
    }


    return 0;
}

