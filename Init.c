#define _WIN32_WINNT 0X05232
#include <iostream>
#include "core.h"
#include <string>
#include <stdio.h>
#include "graphics.h"

using namespace std;

char confirm[2]{NULL};
char usertype[15]{NULL};
void altausuario(void);
void eliminausuario(void);
void actualizarusuario(void);
bool getvaluesusuario(usuario&);
bool startLogon(void);
void admonmenu(void);
void clientemenu(void);
void admonconsultas();
bool retiro();
bool deposito();
bool movimientos();

int main(char *****SQLDriver[], char ***GLOBALDestination[], byte **** URIUnion){
   init_sheet_WNDPROC();
   startLogon();
   return 33;
}

bool movimientos(){
    system("cls");
    if(!PrepareStatmentSelectQueryGLOBAL(getSelectAllUserQ(USUARIO.numerodecuenta),gfillObjectUsuario)){
        cerr<<"Error al cargar datos de usuario"<<endl;
        system("pause");
        return false;
    }
    printLine();
    cout<<endl<<"Movimientos de Efectivo. (-1 Para Regresar)"<<endl;
    printLine();
    cout<<"Depositos..."<<endl;
    if(!PrepareStatmentSelectQueryGLOBAL(getQMovimientos(USUARIO.id,1),printMovimientos)){
        cerr<<"Problema Al Cargar Set de Depositos, contacte al administrador"<<endl;
    }
    printLine();
    cout<<"Retiros..."<<endl;
    if(!PrepareStatmentSelectQueryGLOBAL(getQMovimientos(USUARIO.id,2),printMovimientos)){
        cerr<<"Problema Al Cargar Set de Retiros, contacte al administrador"<<endl;
    }
    cout<<endl;
    return true;
}

bool startLogon(void){
    Setw = 30;
    USUARIO.init_commit();
    flag = true;

    while(true){
        system("cls");
        tileLogon();
        cout<<setw(Setw)<<">>>Ingrese Numero de cuenta: ";
        gets(USUARIO.numerodecuenta);

        if(!strcmp(USUARIO.numerodecuenta,"-1")){
            break;
        }
        setCursor(getRowT()/2,getColumnT()/2-24);
        cout<<setw(Setw)<<">>>Ingrese Password de Acceso: ";
        gets(USUARIO.password);
        if(!strcmp(USUARIO.password,"-1")){
            break;
        }
        strcpy(usertype,validate_logon(USUARIO));

        if(!strcmp(usertype,"ADMINISTRADOR")){
            admonmenu();
        }
        else if(!strcmp(usertype,"USUARIO")){
            clientemenu();
        }
        else{
            setCursor(getRowT()/2+3,getColumnT()/2-24);
            cerr<<"->Numero de cuenta o Password Invalido"<<endl;
        }
        setCursor(getRow(),getColumnT()/2-24);
        system("pause");
    }
    setCursor(getRowT()/2+2,getColumnT()/2-24);
    cout<<"->Hasta Luego!"<<endl;
    setCursor(getRow(),getColumnT()/2-24);
    getchar();
    system("cls");
    return true;
}

void clientemenu(){
    while(true){
        system("cls");
        printLine();
        cout<<"PANEL DE USUARIO...";
        setCursor(getRow(),getColumnT()-22);
        cout<<"Ingrese -1 Para Salir.";
        printLine();
        cout<<"->[1] Retiro de efectivo."<<endl;
        cout<<"->[2] Deposito de efectivo."<<endl;
        cout<<"->[3] Ver Movimientos."<<endl;
        cout<<"===>Ingrese Opcion:";
        gets(confirm);

        if(!strcmp(confirm,"1")){
            retiro();
        }
        else if(!strcmp(confirm,"2")){
            deposito();
        }
        else if(!strcmp(confirm,"3")){
            movimientos();
        }
        else if(!strcmp(confirm,"-1")){
            return;
        }
        else{
            cerr<<"->Opcion Invalida!"<<endl;
        }
        system("pause");
    }

}
bool deposito(){
    while(true){
        system("cls");

        if(!PrepareStatmentSelectQueryGLOBAL(getSelectAllUserQ(USUARIO.numerodecuenta),gfillObjectUsuario)){
            cerr<<"Error al cargar datos de usuario"<<endl;
            system("pause");
            return false;
        }

        printLine();
        cout<<endl<<"Deposito de Efectivo... (Ingrese -1 Para regresar)"<<endl<<endl;
        printLine();
        cout<<"=>Saldo Actual: $"<<USUARIO.saldo<<endl;
        printLine();
        cout<<">>Ingrese Monto a Depositar: ";
        gets(monto);
        if(!strcmp(monto,"-1")){
            return false;
        }
        sentinela = true;
        for(int x=0; x<strlen(monto); ++x){
            if(isalpha(monto[x])){
                sentinela = false;
            }
        }
        if(!sentinela){
            cerr<<"Ingrese Cantidad Valida!"<<endl;
        }
        else{
            dmonto = atof(monto);
            if(dmonto <= 0 || dmonto > 200000){
               cerr<<"Ingrese Cantidad Valida!"<<endl;
            }
            else{
                cout<<"=>Desea Depositar $"<<dmonto<<"? (Ingrese 1 Para confirmar)"<<endl;
                gets(confirm);
                if(!strcmp(confirm,"1")){
                    if(depositoEfectivo(USUARIO,dmonto)){
                        cout<<"Transaccion Completa!"<<endl;
                    }
                    else{
                        cout<<"No se ha podido realizar la transaccion!"<<endl;
                    }
                }
                else{
                    cout<<"Cancelado!"<<endl;
                }

            }
        }
        system("pause");
    }
}
bool retiro(void){

    while(true){
        system("cls");

        if(!PrepareStatmentSelectQueryGLOBAL(getSelectAllUserQ(USUARIO.numerodecuenta),gfillObjectUsuario)){
            cerr<<"Error al cargar datos de usuario"<<endl;
            system("pause");
            return false;
        }

        printLine();
        cout<<endl<<"Retiro de Efectivo... (Ingrese -1 Para regresar)"<<endl<<endl;
        printLine();
        cout<<"=>Saldo Actual: $"<<USUARIO.saldo<<endl;
        printLine();
        cout<<">>Ingrese Monto a retirar: ";
        gets(monto);
        if(!strcmp(monto,"-1")){
            return false;
        }
        sentinela = true;
        for(int x=0; x<strlen(monto); ++x){
            if(isalpha(monto[x])){
                sentinela = false;
            }
        }
        if(!sentinela){
            cerr<<"Ingrese Cantidad Valida!"<<endl;
        }
        else{
            dmonto = atof(monto);
            if((USUARIO.saldo-dmonto <= 0) || dmonto <= 0){
               cerr<<"Ingrese Cantidad Valida!"<<endl;
            }
            else{
                cout<<"=>Desea Retirar $"<<dmonto<<"? (Ingrese 1 Para confirmar)"<<endl;
                gets(confirm);
                if(!strcmp(confirm,"1")){
                    if(retiroEfectivo(USUARIO,dmonto)){
                        cout<<"Transaccion Completa!"<<endl;
                    }
                    else{
                        cout<<"No se ha podido realizar la transaccion!"<<endl;
                    }
                }
                else{
                    cout<<"Cancelado!"<<endl;
                }

            }
        }
        system("pause");
    }
}

void admonconsultas(){
    while(true){
        system("cls");
        printLine();
        cout<<"Opciones de Busqueda. (Presione -1 Para regresar)"<<endl;
        printLine();
        cout<<"->[1] Busqueda Por Nombre."<<endl;
        cout<<"->[2] Busqueda Por Curp."<<endl;
        cout<<"->[3] Busqueda Por Rfc."<<endl;
        cout<<"->[4] Busqueda Por Numero de Cuenta."<<endl;
        if(feof){
            fflush(stdin);
        }
        cout<<"\n===> Ingrese Opcion: ";
        gets(confirm);

        if(!strcmp(confirm,"1")){
            system("cls");
            cout<<">>Ingrese Nombre: ";
            gets(USUARIO.nombre);
            PrepareStatmentSelectQueryGLOBAL(getSelectLikeUsuarioQ(USUARIO.nombre,1),printUsersGeneric);
        }
        else if(!strcmp(confirm,"2")){
            system("cls");
            cout<<">>Ingrese Curp: ";
            gets(USUARIO.curp);
            PrepareStatmentSelectQueryGLOBAL(getSelectLikeUsuarioQ(USUARIO.curp,2),printUsersGeneric);
        }
        else if(!strcmp(confirm,"3")){
            system("cls");
            cout<<">>Ingrese Rfc: ";
            gets(USUARIO.rfc);
            PrepareStatmentSelectQueryGLOBAL(getSelectLikeUsuarioQ(USUARIO.rfc,3),printUsersGeneric);
        }
        else if(!strcmp(confirm,"4")){
            system("cls");
            cout<<">>Ingrese Numero de cuenta: ";
            gets(USUARIO.numerodecuenta);
            sentinela=false;
            for(int x=0; x<strlen(USUARIO.numerodecuenta); ++x){
                if(isalpha(USUARIO.numerodecuenta[x])){
                    sentinela = true;
                }
            }
            if(!sentinela){
                PrepareStatmentSelectQueryGLOBAL(getSelectLikeUsuarioQ(USUARIO.numerodecuenta,4),printUsersGeneric);
            }
            else{
                cerr<<"Numero de cuenta Invalido!"<<endl;
            }
        }
        else if(!strcmp(confirm,"-1")){
            return;
        }
        else{
            cerr<<"Seleccione Opcion Valida!"<<endl;
        }

        system("pause");
    }
}

void admonmenu(void){

    while(true){
        system("cls");
        printLine();
        cout<<"PANEL DE ADMINISTRADOR...";
        setCursor(getRow(),getColumnT()-22);
        cout<<"Ingrese -1 Para Salir.";
        printLine();

        cout<<"->[1] Alta Usuario."<<endl;
        cout<<"->[2] Modificar Usuario."<<endl;
        cout<<"->[3] Eliminar Usuario."<<endl;
        cout<<"->[4] Consultar Usuarios."<<endl;
        cout<<endl<<"===>Ingrese Opcion:";

        if(feof(stdin)){
            fflush(stdin);
        }
        gets(confirm);

        if(!strcmp(confirm,"1")){
            altausuario();
        }
        else if(!strcmp(confirm,"2")){
            actualizarusuario();
        }
        else if(!strcmp(confirm,"3")){
            eliminausuario();
        }
        else if(!strcmp(confirm,"4")){
            admonconsultas();
        }
        else if(!strcmp(confirm,"-1")){
            return;
        }
        else{
            cerr<<"Seleccione opcion valida!"<<endl;
        }
        system("pause");
    }
}

void actualizarusuario(void){
    while(true){
        system("cls");
        cout<<"***Apartado actualizar Usuario***";
        setCursor(getRow(),getColumnT()-22);
        cout<<"Presione -1 Para Salir";
        printLine();
        cout<<"*Ingrese Numero de cuenta:";
        gets(USUARIO.numerodecuenta);
        if(strcmp(USUARIO.numerodecuenta,"-1")==0){
            return;
        }
        if(existUser(getExisteUsuarioQ(USUARIO.numerodecuenta))){
            if(PrepareStatmentSelectQueryGLOBAL(getSelectAllUserQ(USUARIO.numerodecuenta),gfillObjectUsuario)){

                while(true){
                    printUsuarioDatos();
                    printLine();
                    cout<<"->Sub Menu de Atributos (-1 Regresar)."<<endl<<endl;
                    printLine();
                    cout<<"[1] ->Actualizar Nombre."<<endl;
                    cout<<"[2] ->Actualizar Saldo."<<endl;
                    cout<<"[3] ->Actualizar Fecha de nacimiento."<<endl;
                    cout<<"[4] ->Actualizar Curp."<<endl;
                    cout<<"[5] ->Actualizar Rfc."<<endl;
                    cout<<"[6] ->Actualizar Calle."<<endl;
                    cout<<"[7] ->Actualizar Colonia."<<endl;
                    cout<<"[8] ->Actualizar Codigo Postal."<<endl;
                    cout<<"[9] ->Actualizar Nacionalidad."<<endl;
                    cout<<"[10]->Actualizar Estado."<<endl;
                    cout<<"[11]->Actualizar Ciudad."<<endl;
                    cout<<"[12]->Actualizar Password."<<endl;
                    cout<<"[13]->Actualizar Todos los atributos."<<endl;

                    if(feof(stdin)){
                        fflush(stdin);
                    }
                    cout<<"\n====>Ingrese Opcion:";
                    gets(confirm);

                    if(strcmp(confirm,"-1")==0){
                        break;
                    }

                    if(strcmp(confirm,"1")==0){
                        cout<<endl<<endl<<"Ingrese Nombre:";
                        gets(USUARIO.nombre);

                        if(!actualizar_usuario_FINAL(getUpdateUsuarioQ(USUARIO,1))){
                            PrepareStatmentSelectQueryGLOBAL(getSelectAllUserQ(USUARIO.numerodecuenta),gfillObjectUsuario);
                        }
                    }
                    if(strcmp(confirm,"2")==0){
                        cout<<endl<<endl<<"Ingrese Saldo Nuevo:";
                        cin>>USUARIO.saldo;

                        if(!actualizar_usuario_FINAL(getUpdateUsuarioQ(USUARIO,2))){
                            PrepareStatmentSelectQueryGLOBAL(getSelectAllUserQ(USUARIO.numerodecuenta),gfillObjectUsuario);
                        }
                        fflush(stdin);
                    }
                    if(strcmp(confirm,"3")==0){
                        cout<<endl<<endl<<"Ingrese Fecha de Nacimiento:";
                        gets(USUARIO.fechanacimiento);

                        if(!actualizar_usuario_FINAL(getUpdateUsuarioQ(USUARIO,3))){
                            PrepareStatmentSelectQueryGLOBAL(getSelectAllUserQ(USUARIO.numerodecuenta),gfillObjectUsuario);
                        }
                    }
                    if(strcmp(confirm,"4")==0){
                        cout<<endl<<endl<<"Ingrese Curp:";
                        gets(USUARIO.curp);

                        if(!actualizar_usuario_FINAL(getUpdateUsuarioQ(USUARIO,4))){
                            PrepareStatmentSelectQueryGLOBAL(getSelectAllUserQ(USUARIO.numerodecuenta),gfillObjectUsuario);
                        }
                    }
                    if(strcmp(confirm,"5")==0){
                        cout<<endl<<endl<<"Ingrese Rfc:";
                        gets(USUARIO.rfc);

                        if(!actualizar_usuario_FINAL(getUpdateUsuarioQ(USUARIO,5))){
                            PrepareStatmentSelectQueryGLOBAL(getSelectAllUserQ(USUARIO.numerodecuenta),gfillObjectUsuario);
                        }
                    }
                    if(strcmp(confirm,"6")==0){
                        cout<<endl<<endl<<"Ingrese Calle:";
                        gets(USUARIO.calle);

                        if(!actualizar_usuario_FINAL(getUpdateUsuarioQ(USUARIO,6))){
                            PrepareStatmentSelectQueryGLOBAL(getSelectAllUserQ(USUARIO.numerodecuenta),gfillObjectUsuario);
                        }
                    }
                    if(strcmp(confirm,"7")==0){
                        cout<<endl<<endl<<"Ingrese Colonia:";
                        gets(USUARIO.colonia);

                        if(!actualizar_usuario_FINAL(getUpdateUsuarioQ(USUARIO,7))){
                            PrepareStatmentSelectQueryGLOBAL(getSelectAllUserQ(USUARIO.numerodecuenta),gfillObjectUsuario);
                        }
                    }
                    if(strcmp(confirm,"8")==0){
                        cout<<endl<<endl<<"Ingrese CP:";
                        gets(USUARIO.cp);

                        if(!actualizar_usuario_FINAL(getUpdateUsuarioQ(USUARIO,8))){
                            PrepareStatmentSelectQueryGLOBAL(getSelectAllUserQ(USUARIO.numerodecuenta),gfillObjectUsuario);
                        }
                    }
                    if(strcmp(confirm,"9")==0){
                        cout<<endl<<endl<<"Ingrese Nacionalidad:";
                        gets(USUARIO.nacionalidad);

                        if(!actualizar_usuario_FINAL(getUpdateUsuarioQ(USUARIO,9))){
                            PrepareStatmentSelectQueryGLOBAL(getSelectAllUserQ(USUARIO.numerodecuenta),gfillObjectUsuario);
                        }
                    }
                    if(strcmp(confirm,"10")==0){
                        cout<<endl<<endl<<"Ingrese Estado:";
                        gets(USUARIO.estado);

                        if(!actualizar_usuario_FINAL(getUpdateUsuarioQ(USUARIO,10))){
                            PrepareStatmentSelectQueryGLOBAL(getSelectAllUserQ(USUARIO.numerodecuenta),gfillObjectUsuario);
                        }
                    }
                    if(strcmp(confirm,"11")==0){
                        cout<<endl<<endl<<"Ingrese Ciudad:";
                        gets(USUARIO.ciudad);

                        if(!actualizar_usuario_FINAL(getUpdateUsuarioQ(USUARIO,11))){
                            PrepareStatmentSelectQueryGLOBAL(getSelectAllUserQ(USUARIO.numerodecuenta),gfillObjectUsuario);
                        }
                    }
                    if(strcmp(confirm,"12")==0){
                        cout<<endl<<endl<<"Ingrese Password:";
                        gets(USUARIO.password);

                        if(!actualizar_usuario_FINAL(getUpdateUsuarioQ(USUARIO,12))){
                            PrepareStatmentSelectQueryGLOBAL(getSelectAllUserQ(USUARIO.numerodecuenta),gfillObjectUsuario);
                        }
                    }
                    if(!strcmp(confirm,"13")){
                        if(!getvaluesusuario(USUARIO)){
                            cout<<"Cancelado!"<<endl;
                        }
                        else{
                            if(!actualizar_usuario_FINAL(getUpdateUsuarioQ(USUARIO,13))){
                                PrepareStatmentSelectQueryGLOBAL(getSelectAllUserQ(USUARIO.numerodecuenta),gfillObjectUsuario);
                            }
                        }
                    }
                    system("pause");
                }
            }
        }
        else{
            cout<<endl<<"->Este usuario no existe."<<endl;
        }
        system("pause");
    }

}

void eliminausuario(void){

    while(true){
        system("cls");
        if(feof(stdin)){
            fflush(stdin);
        }
        printLine();
        cout<<"->Apartado eliminar Usuario. Ingrese -1 Para Salir."<<endl;
        printLine();

        cout<<"*Ingrese Numero de cuenta:";

        gets(USUARIO.numerodecuenta);
        if(strcmp(USUARIO.numerodecuenta,"-1")==0){
            return;
        }

        if(existUser(getExisteUsuarioQ(USUARIO.numerodecuenta))){
            cout<<"Desea eliminar usuario? (1-SI)\n >>";
            gets(confirm);
            if(strcmp(confirm,"1")==0){
                if(eliminar_user(USUARIO.numerodecuenta)){
                    cout<<"Usuario Eliminado!"<<endl;
                }
                else{
                    cerr<<"No se ha podido eliminar usuario."<<endl;
                }
            }
            else{
                cout<<endl<<"Cancelado"<<endl;
            }
        }
        else{
            cout<<"Numero de cuenta invalido"<<endl;
        }
        system("pause")        ;
    }
}

void altausuario(void){

    if(USUARIO.nombre){
        USUARIO.init_commit();
    }

    while(true){
        system("cls");

        if(feof(stdin)){
            fflush(stdin);
        }

        if(!getvaluesusuario(USUARIO)){
            break;
        }
        else{
            if(generar_numero_de_cuenta(USUARIO)){

                if(PrepareStatmentInsertQuery(getInsertUsuarioQ(USUARIO))){
                    cout<<"Se ha dado de alta la cuenta satisfactoriamente!\n";
                    cout<<"->Numero de cuenta: "<<USUARIO.numerodecuenta<<endl;
                    cout<<"->PIN de acceso: "<<USUARIO.password<<endl;
                }
                else{
                    cerr<<endl<<"->No se ha podido crear nuevo usuario"<<endl;
                }
            }
            else{
                cerr<<"Error al Generar Numero de cuenta, consulte al administrador."<<endl;
            }
        }
        system("pause");
    }
}

bool getvaluesusuario(usuario&USR){
        cout<<"*Ingrese Nombre de Usuario:";
        gets(USR.nombre);
        if(strcmp(USR.nombre,"-1")==0){
            return false;
        }
        cout<<endl<<"*Ingrese Saldo:";
        cin>>USR.saldo;
        if(USR.saldo==-1){
            return false;
        }
        fflush(stdin);
        cout<<endl<<"*Ingrese Fecha de Nacimiento:";
        gets(USR.fechanacimiento);
        if(strcmp(USR.fechanacimiento,"-1")==0){
            return false;
        }
        cout<<endl<<"*Ingrese Curp:";
        gets(USR.curp);
        if(strcmp(USR.curp,"-1")==0){
            return false;
        }
        cout<<endl<<"*Ingrese Rfc:";
        gets(USR.rfc);
        if(strcmp(USR.rfc,"-1")==0){
            return false;
        }
        cout<<endl<<"*Ingrese Calle:";
        gets(USR.calle);
        if(strcmp(USR.calle,"-1")==0){
            return false;
        }
        cout<<endl<<"*Ingrese Colonia:";
        gets(USR.colonia);
        if(strcmp(USR.colonia,"-1")==0){
            return false;
        }
        cout<<endl<<"*Ingrese CP:";
        gets(USR.cp);
        if(strcmp(USR.cp,"-1")==0){
            return false;
        }
        cout<<endl<<"*Ingrese Nacionalidad:";
        gets(USR.nacionalidad);
        if(strcmp(USR.nacionalidad,"-1")==0){
            return false;
        }
        cout<<endl<<"*Ingrese Estado de Residencia:";
        gets(USR.estado);
        if(strcmp(USR.estado,"-1")==0){
            return false;
        }
        cout<<endl<<"*Ingrese Ciudad de Residencia:";
        gets(USR.ciudad);
        if(strcmp(USR.ciudad,"-1")==0){
            return false;
        }
        cout<<endl<<"*Ingrese PIN de Acceso(Password): ";
        gets(USR.password);
        if(strcmp(USR.password,"-1")==0){
            return false;
        }
        return true;
}




