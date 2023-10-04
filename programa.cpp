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
    DATA info;
    NODO *sig;
};

void cargar_archivo(FILE *);
void leer_archivo(FILE *);
int main(){
    setlocale(LC_ALL,"spanish");
    FILE *archivo;
    archivo=fopen("RESERVAS.DAT","wb+");

    cargar_archivo(archivo);
    leer_archivo(archivo);

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