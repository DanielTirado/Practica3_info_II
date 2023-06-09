#include <iostream>
#include <fstream>
#include <string>

using namespace std;

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

    // Almacenar el codigo binario codificado en un arreglo de char
    string linea;
    int long_linea;

    getline(fin, linea);
    long_linea=linea.length();

    fin.seekg(0);
    int p=0;
    char codificado[long_linea];

    while(fin.good()){
        char temp=fin.get();
        if(fin.good()){
            codificado[p]=temp;
        }
        p++;
    }
    fin.close();

    if (metodo == 1){

        cout << "Ingrese el archivo de salida: ";
        cin >> archivo_salida;

        ofstream fout;

        fout.open(archivo_salida);

        // Primer bloque
        int cont_cero = 0;
        int cont_uno = 0;

        for (int i=0; i<semilla; i++){
            if (codificado[i]=='0') {
                codificado[i]='1';
                cont_uno++;
            }
            else{
                codificado[i]='0';
                cont_cero++;
            }
        }

        int indice = 0;
        int cantidad_de_bloques = long_linea/semilla;

        for (int i=1; i<=cantidad_de_bloques; i++){

            indice = (semilla*i)-1;

            // Primer regla
            if (cont_cero==cont_uno){

                cont_cero=0;
                cont_uno=0;
                indice++;
                for (int j=0; j<semilla; j++){
                    if (codificado[indice]=='0') {
                        codificado[indice]='1';
                        cont_uno++;
                    }
                    else{
                        codificado[indice]='0';
                        cont_cero++;
                    }
                    indice++;
                }
            }

            // Segunda regla
            else if(cont_cero>cont_uno){

                cont_cero=0;
                cont_uno=0;

                for (int k=2; k<=semilla; k+=2){
                    indice+=2;
                    if (codificado[indice]=='0') codificado[indice]='1';
                    else codificado[indice]='0';
                }

                int index_para_contar = (semilla*i);

                // Contar los ceros y los unos
                for (int f=0; f<semilla; f++){
                    if (codificado[index_para_contar+f]=='0') cont_cero++;
                    else cont_uno++;
                }
            }

            // Tercer regla
            else if (cont_cero<cont_uno && semilla > 2){

                cont_cero=0;
                cont_uno=0;


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

                int index_para_contar = (semilla*i);
                // Contar los ceros y los unos
                for (int f=0; f<semilla; f++){
                    if (codificado[index_para_contar+f]=='0') cont_cero++;
                    else cont_uno++;
                }

            }

        }

        for (int n=0; n<cantidad_de_bloques*semilla; n++){
            fout << codificado[n];
        }

        fout.close();
    }

    //METODO 2
    else {
        ofstream fout;

        cout << "Ingrese el archivo de salida: ";
        cin >> archivo_salida;

        fout.open(archivo_salida);

        int cantidad_de_bloques = long_linea/semilla;
        fin.close();

        char decodificado[long_linea];

        for (int i=0; i<cantidad_de_bloques; i++){

            int indice = (semilla*i);

            decodificado[((i+1)*semilla)-1] = codificado[indice];

            for (int j=1; j<semilla; j++){
               decodificado[indice+j-1] = codificado[indice+j];
            }
        }

        for (int n=0; n<cantidad_de_bloques*semilla; n++){
            fout << decodificado[n];
        }
        fout.close();
    }
    return 0;
}
