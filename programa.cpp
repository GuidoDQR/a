#include <iostream>
#include <locale.h>
#include <string.h>
#include <stdio.h>
using namespace std;

struct DATA {
    int codCiudad;
    int codDia;
    int dni;
};

struct NODO {
    int dni;
    NODO *sig;
};

const int maxFilas = 100;
const int maxColumnas = 7;

void cargar_archivo(FILE *);
void leer_archivo(FILE *);
void procesar_archivo(FILE *, NODO *matriz[maxFilas][maxColumnas]);
void emitir_reporte(NODO *matriz[maxFilas][maxColumnas]);

int main(){
    setlocale(LC_ALL,"spanish");
    FILE *archivo;
    archivo=fopen("RESERVAS.DAT","wb+");
    
    // matriz de 100 filas y 7 columnas.
    NODO* matriz[maxFilas][maxColumnas];
    
    cargar_archivo(archivo);
    leer_archivo(archivo);
    procesar_archivo(archivo,matriz);
    emitir_reporte(matriz);

    fclose(archivo);
    
    return 0;
};

void cargar_archivo(FILE *f){
    DATA reg;
    char confirmar;
    confirmar='s';
    while(confirmar=='S' || confirmar=='s'){
        cout<<"Ingrese el código de ciudad (0..99): ";
        cin>>reg.codCiudad;
        cout<<"Ingrese el código del día (0..6): ";
        cin>>reg.codDia;
        cout<<"Ingrese el DNI: ";
        cin>>reg.dni;
        fwrite(&reg,sizeof(DATA),1,f);
        cout<<"Desea seguir ingresando más información de los usuarios?"<<endl;
        cout<<"---------   Si=S   |   No=N   ---------"<<endl;
        cin>>confirmar;
    };
    fseek(f,0,SEEK_SET);
};
void leer_archivo(FILE *f){
    DATA reg;
    fread(&reg,sizeof(DATA),1,f);
    while(!feof(f)){
        cout<<"Código de ciudad: "<<reg.codCiudad;
        cout<<" --- Código del día: "<<reg.codDia;
        cout<<" --- DNI: "<<reg.dni<<endl;
        fread(&reg,sizeof(DATA),1,f);
    };
    fseek(f,0,SEEK_SET);
};

void procesar_archivo(FILE *f, NODO *matriz[maxFilas][maxColumnas]){

    // se inicializa la matriz como NULL
    for(int i=0; i<maxFilas;i++){
        for(int j=0; j<maxColumnas;j++){
            matriz[i][j] = NULL;
        }
    }

    // pruebas para probar la funcion emitir_reporte, esto se puede borrar
    // matriz[1][1] = new NODO;
    // matriz[1][1]->dni = 10;
    // matriz[1][1]->sig = new NODO;
    // matriz[1][1]->sig->dni = 20;
    // matriz[1][1]->sig->sig = NULL;

    // matriz[2][3] = new NODO;
    // matriz[2][3]->dni = 90;
    // matriz[2][3]->sig = NULL;

    // matriz[3][5] = new NODO;
    // matriz[3][5]->dni = 23;
    // matriz[3][5]->sig = NULL;

    // matriz[3][2] = new NODO;
    // matriz[3][2]->dni = 50;
    // matriz[3][2]->sig = new NODO;
    // matriz[3][2]->sig->dni = 60;
    // matriz[3][2]->sig->sig = new NODO;
    // matriz[3][2]->sig->sig->dni = 70;
    // matriz[3][2]->sig->sig->sig = NULL;
}

void emitir_reporte(NODO *matriz[maxFilas][maxColumnas]){
    int reservas[maxFilas];
    NODO* valor;

    for(int i=0; i<maxFilas;i++){
        reservas[i] = 0;
    }
   
    for(int i=0; i<maxFilas;i++){
        for(int j=0; j<maxColumnas;j++){
            valor = matriz[i][j];
            while(valor != NULL){
                reservas[i]++; // Cuenta la cantidad total de reservas por cod_ciudad
                valor = valor->sig;
            }
        }
        cout << "reserva["<<i<<"]: " << reservas[i] << endl; // muestra la cantidad total de reservas por cod_ciudad
    }

    // borra la memoria dinamica
    for(int i=0; i<maxFilas;i++){
        for(int j=0; j<maxColumnas;j++){
            while(matriz[i][j] != NULL){
                valor = matriz[i][j];   
                matriz[i][j] = matriz[i][j]->sig;
                delete valor;
            }
        }
    }
}