#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED
#define true 1
#define false 0
#define CUENTAINIT 33000
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <windowsx.h>
#include <errno.h>
#include <mysql.h>
#include <cstdbool>
#include <time.h>
#include <iomanip>
#include "graphics.h"
#include <ctype.h>

using namespace std;

const char* hostname = "localhost";
const char* userid = "root";
const char * password = "master";
const char * dbprefix = "atm";

char * queryTmp;

typedef struct xbase{
    int status;
    my_ulonglong rowsentinel= -1;
    unsigned int fieldsentinel = -1;
    MYSQL * conn = NULL;
    MYSQL * connenviroment = NULL;
    MYSQL_RES * result = NULL;
    MYSQL_ROW row = NULL;
    MYSQL_FIELD *fields;

    void free(){
        this->status=-1;
        this->rowsentinel =0;
        this->conn = NULL;
        this->connenviroment = NULL;
        this->result = NULL;
        this->row = NULL;
        this->fields = NULL;
    }
}base;

typedef struct xuser{
    int id;
    char nombre[45];
    double saldo;
    char * saldoT;
    char fechanacimiento[25];
    char curp[30];
    char rfc[30];
    char calle[40];
    char colonia[50];
    char cp[15];
    char nacionalidad[45];
    char estado[45];
    char ciudad[45];
    char password[30];
    char numerodecuenta[20];

    const char * INSERTNEW = "INSERT INTO usuario(nombre,saldo,fechanacimiento,curp,rfc,calle,colonia,cp,nacionalidad,estado,ciudad,password,ncuenta)VALUES('";
    const char * SELECTEXIST = "SELECT idusuario FROM usuario WHERE ncuenta = ";
    const char * SELECTALL = "SELECT * FROM usuario WHERE ncuenta =";
    const char * UPDATE = "UPDATE usuario SET ";

    xuser(){
        this->init_commit();
    }

    void init_commit(){
        this->id = -1;
        this->saldo = 0;
        this->saldoT = NULL;
        for(int x=0; x<(sizeof(nombre)/sizeof(char));++x){
            this->nombre[x]=NULL;
        }
        for(int x=0; x<(sizeof(fechanacimiento)/sizeof(fechanacimiento));++x){
            this->fechanacimiento[x]=NULL;
        }
        for(int x=0; x<(sizeof(curp)/sizeof(char));++x){
            this->curp[x]=NULL;
        }
        for(int x=0; x<(sizeof(rfc)/sizeof(char));++x){
            this->rfc[x]=NULL;
        }
        for(int x=0; x<(sizeof(calle)/sizeof(char));++x){
            this->calle[x]=NULL;
        }
        for(int x=0; x<(sizeof(colonia)/sizeof(char));++x){
            this->colonia[x]=NULL;
        }
        for(int x=0; x<(sizeof(nacionalidad)/sizeof(char));++x){
            this->nacionalidad[x]=NULL;
        }
        for(int x=0; x<(sizeof(estado)/sizeof(char));++x){
            this->estado[x]=NULL;
        }
        for(int x=0; x<(sizeof(ciudad)/sizeof(char));++x){
            this->ciudad[x]=NULL;
        }
        for(int x=0; x<(sizeof(cp)/sizeof(char));++x){
            this->cp[x]=NULL;
        }
        for(int x=0; x<(sizeof(password)/sizeof(char)); ++x){
            this->password[x]=NULL;
        }
        for(int x=0; x<(sizeof(numerodecuenta)/sizeof(char));++x){
            this->numerodecuenta[x]=NULL;
        }
    }
    const char * SELECTLIKENAME = "SELECT * FROM usuario WHERE nombre LIKE '%s%';";
    const char * SELECTLIKECURP = "SELECT * FROM usuario WHERE curp LIKE '%s%';";
    const char * SELECTLIKERFC = "SELECT * FROM usuario WHERE rfc LIKE '%s%';";
    const char * SELECTLIKENCUENTA = "SELECT * FROM usuario WHERE ncuenta LIKE '%s%';";
    const char * UPDATESALDO = "UPDATE usuario SET saldo = %s WHERE ncuenta = %s";
    const char * INSERTINTORETIRO = "INSERT INTO RETIROS (saldoinicial,saldofinal,monto,fecha,idusuario) VALUES(%.2f,%.2f,%.2f,'%s',%d);";
    const char * INSERTINTODEPOSITO = "INSERT INTO DEPOSITOS (saldoinicial,saldofinal,monto,fecha,idusuario) VALUES(%.2f,%.2f,%.2f,'%s',%d);";
    const char * SELECTDEPOSITO = "SELECT * FROM depositos WHERE idusuario = %d";
    const char * SELECTRETIRO = "SELECT * FROM retiros WHERE idusuario = %d";
}usuario;

typedef struct xadmon{
    int id;
    char nombre[45];
    char alias[45];
    char password[45];

    xadmon(){
        this->init_commit();
    }

    void init_commit(){
        this->id=-1;
        for(int x=0; x<sizeof(nombre)/sizeof(char); ++x){
            this->nombre[x]=NULL;
        }
        for(int x=0; x<sizeof(alias)/sizeof(char);++x){
            this->alias[x]=NULL;
        }
        for(int x=0; x<sizeof(password)/sizeof(char); ++x){
            this->password[x]=NULL;
        }
    }

    char*SELECTID="SELECT idadministrador FROM administrador WHERE (nombre = '%s' OR alias = '%s') AND (password = '%s');";

}administrador;

int Setw;
bool sentinela;
bool flag;
time_t tx;
struct tm * xt;
void STMTclose(MYSQL*);
bool STMTconnect(bool x);
void printDBinfoHost();
char*getInsertUsuarioQ(usuario&);
bool PrepareStatmentInsertQuery(char*);
bool PrepareStatmentSelectQueryGLOBAL(char*,void (*)(void));
bool existUser(char*);
char*getExisteUsuarioQ(char*,char*);
char*getExisteUsuarioQ(char*);
bool generar_numero_de_cuenta(usuario&);
bool eliminar_user(char*);
void gfillObjectUsuario();
char*getSelectAllUserQ(char*ncuenta);
void printUsuarioDatos();
bool actualizar_usuario_FINAL(char*);
char*getUpdateUsuarioQ(usuario&,int);
char* validate_logon(usuario&);
bool existAdministrador(char*);
char* getSelectAdministradorQ(char*,char*);
char* getSelectLikeUsuarioQ(char*,int&);
void printUsersGeneric(void);
char* gdate();
void printdate();
bool retiroEfectivo(usuario&,double);
bool triggerRetiro(usuario&,double&,double&);
char monto[50];
bool depositoEfectivo(usuario&,double);
bool triggerDeposito(usuario&,double,double);
void printMovimientos();
double dmonto;
char*getQMovimientos(int,int);

base DB;
usuario USUARIO;
usuario TMPUSER;
administrador ADMINISTRADOR;

void printMovimientos(){

    if(DB.rowsentinel<=0){
        cout<<"No existen coincidencias"<<endl;
        return;
    }
    else{
        cout<<setw(20)<<"NUMERO DE DEPOSITO"<<setw(20)<<"SALDO INICIAL"<<setw(20)<<"SALDO FINAL"<<setw(20)<<"CANTIDAD"<<setw(30)<<"FECHA Y HORA"<<endl;
        for(int x=0; x<DB.rowsentinel; ++x){
            while(DB.row = mysql_fetch_row(DB.result)){
                cout<<setw(20)<<DB.row[0]<<setw(20)<<DB.row[1]<<setw(20)<<DB.row[2]<<setw(20)<<DB.row[3]<<setw(30)<<DB.row[4]<<endl;
            }
        }
    }
}

bool PrepareStatmentSelectQueryGLOBAL(char*QUERYStmt,void(*LISTENER)(void)){

    if(!STMTconnect(true)){
        return false;
    }

    flag = true;

    try{
        DB.status = mysql_query(DB.conn,QUERYStmt);

        if(DB.status){
            flag = false;
            cerr<<mysql_error(DB.conn)<<endl;
        }
        else{
            DB.result = mysql_store_result(DB.conn);
            DB.rowsentinel = mysql_num_rows(DB.result);
            DB.fieldsentinel = mysql_num_fields(DB.result);
            LISTENER();
            if(DB.result){
                mysql_free_result(DB.result);
            }
        }

    }catch(exception &ex){
        flag = false;
        cerr<<ex.what()<<endl;
        throw ex;
    }
    if(DB.conn){
       STMTclose(DB.conn);
    }

    return flag;
}
char * getQMovimientos(int id,int lcase){
    if(queryTmp){
        free(queryTmp);
    }

    switch(lcase){
        case(1):{
            queryTmp = (char*)malloc((sizeof(char)*(strlen(USUARIO.SELECTDEPOSITO)+sizeof(id)+20)));
            sprintf(queryTmp,USUARIO.SELECTDEPOSITO,id);
            break;
        }
        case(2):{
            queryTmp = (char*)malloc((sizeof(char)*(strlen(USUARIO.SELECTRETIRO)+sizeof(id)+20)));
            sprintf(queryTmp,USUARIO.SELECTRETIRO,id);
            break;
        }
    }

    return queryTmp;
}

bool triggerDeposito(usuario&USR,double mont, double sfinal){
    if(queryTmp){
        free(queryTmp);
    }
    queryTmp = (char*)malloc((strlen(USR.INSERTINTODEPOSITO)+sizeof(USR.saldo)+sizeof(sfinal)+sizeof(mont)+sizeof(gdate()+sizeof(USR.id))*sizeof(char)));
    sprintf(queryTmp,USR.INSERTINTODEPOSITO,USR.saldo,sfinal,mont,gdate(),USR.id);
    DB.status = mysql_query(DB.conn,queryTmp);
    cout<<queryTmp<<endl;
    getchar();
    if(!DB.status){
        return true;
    }
    else{
        return false;
    }
}
bool depositoEfectivo(usuario&USR,double depositar){
    if(USR.saldoT){
        free(USR.saldoT);
    }

    memcpy(&TMPUSER,&USR,sizeof(usuario));

    USR.saldo += depositar;
    USR.saldoT = (char*)malloc(sizeof(char)*(sizeof(USR.saldo)+15));
    sprintf(USR.saldoT,"%.2f",USR.saldo);

    if(queryTmp){
        free(queryTmp);
    }

    queryTmp = (char*)malloc((strlen(USR.UPDATESALDO)+strlen(USR.saldoT)+strlen(USR.numerodecuenta))*sizeof(char));
    sprintf(queryTmp,USR.UPDATESALDO,USR.saldoT,USR.numerodecuenta);

    flag = false;

    if(STMTconnect(true)){
        try{
            DB.status = mysql_query(DB.conn,queryTmp);

            if(!DB.status){
                if(mysql_affected_rows(DB.conn)>0){
                    flag = true;
                    if(!triggerDeposito(TMPUSER,depositar,USR.saldo)){
                       cerr<<"Problema al adecuar transaccion, reportelo al administrador.\n"<<endl;
                    }
                }
            }
        }catch(exception &ex){
            flag = false;
            throw ex;
        }
    }
    if(DB.conn){
        STMTclose(DB.conn);
    }
    return flag;
}

bool retiroEfectivo(usuario&USR,double retirar){

    if(USR.saldoT){
        free(USR.saldoT);
    }

    memcpy(&TMPUSER,&USR,sizeof(usuario));
    USR.saldo -= retirar;
    USR.saldoT = (char*)malloc(sizeof(char)*(sizeof(USR.saldo)+10));
    sprintf(USR.saldoT,"%.2f",USR.saldo);

    if(queryTmp){
        free(queryTmp);
    }

    queryTmp = (char*)malloc((strlen(USR.UPDATESALDO)+sizeof(USR.saldoT)+strlen(USR.numerodecuenta)+10)*sizeof(char));
    sprintf(queryTmp,USR.UPDATESALDO,USR.saldoT,USR.numerodecuenta);

    flag = false;

    if(STMTconnect(true)){
        try{
            DB.status = mysql_query(DB.conn,queryTmp);

            if(!DB.status){
                if(mysql_affected_rows(DB.conn)>0){
                    flag = true;
                    if(!triggerRetiro(TMPUSER,retirar,USR.saldo)){
                       cerr<<"Problema al adecuar transaccion, reportelo al administrador.\n"<<endl;
                    }
                }
            }
        }catch(exception &ex){
            flag = false;
            throw ex;
        }
    }
    if(DB.conn){
        STMTclose(DB.conn);
    }
    return flag;
}

bool triggerRetiro(usuario&USR, double &mont,double &sfinal){
    if(queryTmp){
        free(queryTmp);
    }
    queryTmp = (char*)malloc((strlen(USR.INSERTINTORETIRO)+sizeof(USR.saldo)+sizeof(sfinal)+sizeof(mont)+sizeof(gdate()+sizeof(USR.id))*sizeof(char)));
    sprintf(queryTmp,USR.INSERTINTORETIRO,USR.saldo,sfinal,mont,gdate(),USR.id);
    DB.status = mysql_query(DB.conn,queryTmp);
    cout<<queryTmp<<endl;
    getchar();
    if(!DB.status){
        return true;
    }
    else{
        return false;
    }
}

void printUsersGeneric(){

    if(DB.rowsentinel < 1){
        cerr<<"No existen Coincidencias!"<<endl;
        return;
    }
    printLine();
    cout<<left<<setw(11)<<"ID USUARIO"<<setw(25)<<"NOMBRE"<<setw(15)<<"SALDO"<<setw(20)<<"FECHA DE NACIMIENTO"<<setw(20)<<"CURP"<<setw(19)<<"RFC"<<setw(28)<<"CALLE"<<setw(15)<<"COLONIA"<<setw(15)<<"CP"<<setw(15)<<"NACIONALIDAD"<<setw(20)<<"ESTADO"<<setw(20)<<"CIUDAD"<<setw(15)<<"PASSWORD"<<setw(20)<<"CUENTA"<<endl;
    printLine();

    for(int x=0; x<DB.rowsentinel; ++x){
        while(DB.row = mysql_fetch_row(DB.result)){
            cout<<setw(11)<<DB.row[0]<<setw(25)<<DB.row[1]<<setw(15)<<DB.row[2]<<setw(20)<<DB.row[3]<<setw(20)<<DB.row[4]<<setw(19)<<DB.row[5]<<setw(28)<<DB.row[6]<<setw(15)<<DB.row[7]<<setw(15)<<DB.row[8]<<setw(15)<<DB.row[9]<<setw(20)<<DB.row[10]<<setw(20)<<DB.row[11]<<setw(15)<<DB.row[12]<<setw(20)<<DB.row[13]<<endl;
            cout<<endl;
        }
    }
}

char* getSelectLikeUsuarioQ(char*Q,int opt){
    if(queryTmp){
        free(queryTmp);
        queryTmp = NULL;
    }
    switch(opt){
        case(1):{
            queryTmp = (char*)malloc(sizeof(char)*(strlen(USUARIO.SELECTLIKENAME)+strlen(Q)+1));
            sprintf(queryTmp,USUARIO.SELECTLIKENAME,Q);
            break;
        }
        case(2):{
            queryTmp = (char*)malloc(sizeof(char)*(strlen(USUARIO.SELECTLIKECURP)+strlen(Q)+1));
            sprintf(queryTmp,USUARIO.SELECTLIKECURP,Q);
            break;
        }
        case(3):{
            queryTmp = (char*)malloc(sizeof(char)*(strlen(USUARIO.SELECTLIKERFC)+strlen(Q)+1));
            sprintf(queryTmp,USUARIO.SELECTLIKERFC,Q);
            break;
        }
        case(4):{
            queryTmp = (char*)malloc(sizeof(char)*(strlen(USUARIO.SELECTLIKENCUENTA)+strlen(Q)+1));
            sprintf(queryTmp,USUARIO.SELECTLIKENCUENTA,Q);
            break;
        }
    }
    return queryTmp;
}

char* validate_logon(usuario&USR){
    sentinela = false;
    for(int x=0; x<strlen(USR.numerodecuenta); ++x){
        if(isalpha(USR.numerodecuenta[x])){
            sentinela = true;
            break;
        }
    }

    if(existAdministrador(getSelectAdministradorQ(USR.numerodecuenta,USR.password))){
        return "ADMINISTRADOR";
    }

    if(!sentinela){
        if(existUser(getExisteUsuarioQ(USR.numerodecuenta,USR.password))){
            return "USUARIO";
        }
    }
    return "NULL";
}
char* getSelectAdministradorQ(char*a,char*password){
    if(queryTmp){
        free(queryTmp);
    }
    queryTmp = (char*)malloc(sizeof(char)*(strlen(a)*2+strlen(password)+100));

    sprintf(queryTmp,ADMINISTRADOR.SELECTID,a,a,password);

    return queryTmp;
}

bool existAdministrador(char*FQUERY){
    flag = true;

    if(STMTconnect(true)){

        DB.status=mysql_query(DB.conn,FQUERY);

        if(!DB.status){
            DB.result = mysql_store_result(DB.conn);

            if(DB.result){
                if(mysql_num_rows(DB.result)<=0){
                    flag = false;
                }
            }
        }
    }
    if(DB.result){
        mysql_free_result(DB.result);
    }
    if(DB.conn){
        STMTclose(DB.conn);
    }

    return flag;
}

bool actualizar_usuario_FINAL(char*FQUERY){
   flag = false;

   if(STMTconnect(true)){
        try{

            DB.status = mysql_query(DB.conn,FQUERY);

            if(DB.status == 0 && mysql_affected_rows(DB.conn)>0){
                cout<<"Se ha actualizado usuario."<<endl;
                flag = true;
            }
            else{
            cerr<<"No se ha podido actualizar usuario"<<endl;
            }
        }catch(exception &ex){
            cerr<<ex.what();
            throw ex;
        }
    }
    else{
        cerr<<"No se ha podido actualizar usuario"<<endl;
    }

    if(DB.conn){
        STMTclose(DB.conn);
    }

    return flag;
}

char*getUpdateUsuarioQ(usuario&USR,int option){
    if(queryTmp){
        free(queryTmp);
    }

    USR.saldoT = (char*)malloc(sizeof(USR.saldo));
    sprintf(USR.saldoT,"%.2f",USR.saldo);

    switch(option){
        case(1):{
            queryTmp = (char*)malloc(sizeof(char)*(strlen(USR.UPDATE)+strlen(USR.nombre)+strlen(USR.numerodecuenta)+30));
            strcpy(queryTmp,USR.UPDATE);
            strcat(queryTmp,"nombre='");
            strcat(queryTmp,USR.nombre);
            strcat(queryTmp,"' WHERE ncuenta =");
            strcat(queryTmp,USR.numerodecuenta);
            strcat(queryTmp,";");
            break;
        }
        case(2):{
            queryTmp = (char*)malloc(sizeof(char)*(strlen(USR.UPDATE)+strlen(USR.saldoT)+strlen(USR.numerodecuenta)+30));
            strcpy(queryTmp,USR.UPDATE);
            strcat(queryTmp,"saldo=");
            strcat(queryTmp,USR.saldoT);
            strcat(queryTmp," WHERE ncuenta =");
            strcat(queryTmp,USR.numerodecuenta);
            strcat(queryTmp,";");
            break;
        }
        case(3):{
            queryTmp = (char*)malloc(sizeof(char)*(strlen(USR.UPDATE)+strlen(USR.fechanacimiento)+strlen(USR.numerodecuenta)+35));
            strcpy(queryTmp,USR.UPDATE);
            strcat(queryTmp,"fechanacimiento='");
            strcat(queryTmp,USR.fechanacimiento);
            strcat(queryTmp,"' WHERE ncuenta =");
            strcat(queryTmp,USR.numerodecuenta);
            strcat(queryTmp,";");
            break;
        }
        case(4):{
            queryTmp = (char*)malloc(sizeof(char)*(strlen(USR.UPDATE)+strlen(USR.curp)+strlen(USR.numerodecuenta)+30));
            strcpy(queryTmp,USR.UPDATE);
            strcat(queryTmp,"curp='");
            strcat(queryTmp,USR.curp);
            strcat(queryTmp,"' WHERE ncuenta =");
            strcat(queryTmp,USR.numerodecuenta);
            strcat(queryTmp,";");
            break;
        }
        case(5):{
            queryTmp = (char*)malloc(sizeof(char)*(strlen(USR.UPDATE)+strlen(USR.rfc)+strlen(USR.numerodecuenta)+30));
            strcpy(queryTmp,USR.UPDATE);
            strcat(queryTmp,"rfc='");
            strcat(queryTmp,USR.rfc);
            strcat(queryTmp,"' WHERE ncuenta =");
            strcat(queryTmp,USR.numerodecuenta);
            strcat(queryTmp,";");
            break;
        }
        case(6):{
            queryTmp = (char*)malloc(sizeof(char)*(strlen(USR.UPDATE)+strlen(USR.calle)+strlen(USR.numerodecuenta)+30));
            strcpy(queryTmp,USR.UPDATE);
            strcat(queryTmp,"calle='");
            strcat(queryTmp,USR.calle);
            strcat(queryTmp,"' WHERE ncuenta =");
            strcat(queryTmp,USR.numerodecuenta);
            strcat(queryTmp,";");
            break;
        }
        case(7):{
            queryTmp = (char*)malloc(sizeof(char)*(strlen(USR.UPDATE)+strlen(USR.colonia)+strlen(USR.numerodecuenta)+30));
            strcpy(queryTmp,USR.UPDATE);
            strcat(queryTmp,"colonia='");
            strcat(queryTmp,USR.colonia);
            strcat(queryTmp,"' WHERE ncuenta =");
            strcat(queryTmp,USR.numerodecuenta);
            strcat(queryTmp,";");
            break;
        }
        case(8):{
            queryTmp = (char*)malloc(sizeof(char)*(strlen(USR.UPDATE)+strlen(USR.cp)+strlen(USR.numerodecuenta)+30));
            strcpy(queryTmp,USR.UPDATE);
            strcat(queryTmp,"cp=");
            strcat(queryTmp,USR.cp);
            strcat(queryTmp," WHERE ncuenta =");
            strcat(queryTmp,USR.numerodecuenta);
            strcat(queryTmp,";");
            break;
        }
        case(9):{
            queryTmp = (char*)malloc(sizeof(char)*(strlen(USR.UPDATE)+strlen(USR.nacionalidad)+strlen(USR.numerodecuenta)+35));
            strcpy(queryTmp,USR.UPDATE);
            strcat(queryTmp,"nacionalidad='");
            strcat(queryTmp,USR.nacionalidad);
            strcat(queryTmp,"' WHERE ncuenta =");
            strcat(queryTmp,USR.numerodecuenta);
            strcat(queryTmp,";");
            break;
        }
        case(10):{
            queryTmp = (char*)malloc(sizeof(char)*((strlen(USR.UPDATE)+strlen(USR.estado)+strlen(USR.numerodecuenta)+30)));
            strcpy(queryTmp,USR.UPDATE);
            strcat(queryTmp,"estado='");
            strcat(queryTmp,USR.estado);
            strcat(queryTmp,"' WHERE ncuenta =");
            strcat(queryTmp,USR.numerodecuenta);
            strcat(queryTmp,";");
            break;
        }
        case(11):{
            queryTmp = (char*)malloc(sizeof(char)*(strlen(USR.UPDATE)+strlen(USR.ciudad)+strlen(USR.numerodecuenta)+30));
            strcpy(queryTmp,USR.UPDATE);
            strcat(queryTmp,"ciudad='");
            strcat(queryTmp,USR.ciudad);
            strcat(queryTmp,"' WHERE ncuenta =");
            strcat(queryTmp,USR.numerodecuenta);
            strcat(queryTmp,";");
            break;
        }
        case(12):{
            queryTmp = (char*)malloc(sizeof(char)*(strlen(USR.UPDATE)+strlen(USR.password)+strlen(USR.numerodecuenta)+30));
            strcpy(queryTmp,USR.UPDATE);
            strcat(queryTmp,"password='");
            strcat(queryTmp,USR.password);
            strcat(queryTmp,"' WHERE ncuenta =");
            strcat(queryTmp,USR.numerodecuenta);
            strcat(queryTmp,";");
            break;
        }
        case(13):{
            if(USUARIO.saldoT){
                free(USUARIO.saldoT);
            }
            USR.saldoT = (char*)malloc(sizeof(char)*sizeof(USR.saldo));
            sprintf(USR.saldoT,"%.2f",USR.saldo);
            queryTmp = (char*)malloc(sizeof(char)*(strlen(USR.nombre)+strlen(USR.saldoT)+strlen(USR.fechanacimiento)+strlen(USR.curp)+strlen(USR.curp)+strlen(USR.rfc)
            +strlen(USR.calle)+strlen(USR.colonia)+strlen(USR.cp)+strlen(USR.nacionalidad)+strlen(USR.estado)+strlen(USR.ciudad)+strlen(USR.UPDATE)+strlen(USR.password)+strlen(USR.numerodecuenta)+200));
            strcpy(queryTmp,USR.UPDATE);
            strcat(queryTmp,"nombre='");
            strcat(queryTmp,USR.nombre);
            strcat(queryTmp,"',saldo=");
            strcat(queryTmp,USR.saldoT);
            strcat(queryTmp,",fechanacimiento='");
            strcat(queryTmp,USR.fechanacimiento);
            strcat(queryTmp,"',curp='");
            strcat(queryTmp,USR.curp);
            strcat(queryTmp,"',rfc='");
            strcat(queryTmp,USR.rfc);
            strcat(queryTmp,"',calle='");
            strcat(queryTmp,USR.calle);
            strcat(queryTmp,"',colonia='");
            strcat(queryTmp,USR.colonia);
            strcat(queryTmp,"',cp='");
            strcat(queryTmp,USR.cp);
            strcat(queryTmp,"',nacionalidad='");
            strcat(queryTmp,USR.nacionalidad);
            strcat(queryTmp,"',estado='");
            strcat(queryTmp,USR.estado);
            strcat(queryTmp,"',ciudad='");
            strcat(queryTmp,USR.ciudad);
            strcat(queryTmp,"',password='");
            strcat(queryTmp,USR.password);
            strcat(queryTmp,"' WHERE ncuenta =");
            strcat(queryTmp,USR.numerodecuenta);
            strcat(queryTmp,";");
            break;
        }
    }
    cout<<queryTmp<<endl;
    return queryTmp;
}

void printUsuarioDatos(){
    Setw = 22;
    system("cls");
    printLine();
    cout<<left<<setw(Setw)<<"->Datos de Usuario para el numero de cuenta: "<<USUARIO.numerodecuenta<<endl<<endl;
    printLine();
    cout<<setw(Setw)<<"@Id de usuario: "<<USUARIO.id<<endl;
    cout<<setw(Setw)<<"@Nombre de usuario: "<<USUARIO.nombre<<endl;
    cout<<setw(Setw)<<"@Saldo: "<<"$"<<USUARIO.saldo<<endl;
    cout<<setw(Setw)<<"@Fecha de nacimiento: "<<USUARIO.fechanacimiento<<endl;
    cout<<setw(Setw)<<"@Curp: "<<USUARIO.curp<<endl;
    cout<<setw(Setw)<<"@RFC: "<<USUARIO.rfc<<endl;
    cout<<setw(Setw)<<"@Calle: "<<USUARIO.calle<<endl;
    cout<<setw(Setw)<<"@Colonia: "<<USUARIO.nombre<<endl;
    cout<<setw(Setw)<<"@CP: "<<USUARIO.cp<<endl;
    cout<<setw(Setw)<<"@Nacionalidad: "<<USUARIO.nacionalidad<<endl;
    cout<<setw(Setw)<<"@Estado: "<<USUARIO.estado<<endl;
    cout<<setw(Setw)<<"@Ciudad: "<<USUARIO.ciudad<<endl;
    cout<<setw(Setw)<<"@Password: "<<USUARIO.password<<endl;
}

char*getSelectAllUserQ(char*ncuenta){
    if(queryTmp){
       free(queryTmp) ;
    }
    queryTmp = (char*)malloc(sizeof(char)*(strlen(USUARIO.SELECTALL)+strlen(ncuenta)+1));

    strcpy(queryTmp,USUARIO.SELECTALL);
    strcat(queryTmp,ncuenta);
    strcat(queryTmp,";");

    return queryTmp;
}
void gfillObjectUsuario(void){
    DB.row = mysql_fetch_row(DB.result);
    USUARIO.id=atoi(DB.row[0]);
    strcpy(USUARIO.nombre,DB.row[1]);
    USUARIO.saldo = atof(DB.row[2]);
    strcpy(USUARIO.fechanacimiento,DB.row[3]);
    strcpy(USUARIO.curp,DB.row[4]);
    strcpy(USUARIO.rfc,DB.row[5]);
    strcpy(USUARIO.calle,DB.row[6]);
    strcpy(USUARIO.colonia,DB.row[7]);
    strcpy(USUARIO.cp,DB.row[8]);
    strcpy(USUARIO.nacionalidad,DB.row[9]);
    strcpy(USUARIO.estado,DB.row[10]);
    strcpy(USUARIO.ciudad,DB.row[11]);
    strcpy(USUARIO.password,DB.row[12]);
    strcpy(USUARIO.numerodecuenta,DB.row[13]);
}

bool eliminar_user(char*cuenta){
    flag = false;

    if(STMTconnect(true)){
        if(!queryTmp){
            free(queryTmp);
        }
        queryTmp = (char*)malloc(sizeof(char)*(40+strlen(cuenta)));
        strcpy(queryTmp,"DELETE FROM usuario WHERE ncuenta =");
        strcat(queryTmp,cuenta);
        strcat(queryTmp,";");

        try{
            DB.status = mysql_query(DB.conn,queryTmp);
            if(DB.status ==0 && mysql_affected_rows(DB.conn)>0){
                flag = true;
            }
        }
        catch(exception &z){
            cerr<<z.what();
            throw z;
        }
    }
    if(DB.conn){
        STMTclose(DB.conn);
    }
    return flag;
}

bool generar_numero_de_cuenta(usuario&USR){
    flag = true;

    if(queryTmp){
        free(queryTmp);
    }

    queryTmp = (char*)malloc(54);

    strcpy(queryTmp,"SELECT idusuario FROM usuario order by idusuario DESC;");

    if(STMTconnect(true)){
        try{
            DB.status = mysql_query(DB.conn,queryTmp);
            if(DB.status){
                cerr<<mysql_error(DB.conn);
                flag = false;
            }else{
                DB.result = mysql_store_result(DB.conn);

                if(DB.result){
                    DB.row = mysql_fetch_row(DB.result);

                    int res = atoi(DB.row[0]) + 1;

                    sprintf(USR.numerodecuenta,"%d",res+CUENTAINIT);
                }
                else{
                    strcpy(USR.numerodecuenta,(char*)(CUENTAINIT+1));
                }
            }

        }catch(exception &ex){
            cerr<<ex.what()<<endl;
            throw ex;
            flag = false;
        }
        STMTclose(DB.conn);
    }
    else{
        flag = false;
    }
    return flag;
}


bool PrepareStatmentInsertQuery(char*QUERYStmt){

    if(!STMTconnect(true)){
        return false;
    }
    flag = true;

    try{
        DB.status= mysql_query(DB.conn,QUERYStmt);

        if(DB.status){
            flag = false;
        }
    }
    catch(exception ex){
        cerr<<&ex<<endl;
        flag = false;
    }
    return flag;
}


char * getInsertUsuarioQ(usuario&USR){

    USR.saldoT = (char*)malloc(sizeof(USR.saldo)*sizeof(char));

    sprintf(USR.saldoT,"%.2f",USR.saldo);

    if(queryTmp){
        free(queryTmp);
    }

    queryTmp = (char*)malloc(strlen(USR.nombre)+strlen(USR.saldoT)+strlen(USR.fechanacimiento)+strlen(USR.curp)+strlen(USR.curp)+strlen(USR.rfc)
    +strlen(USR.calle)+strlen(USR.colonia)+strlen(USR.cp)+strlen(USR.nacionalidad)+strlen(USR.estado)+strlen(USR.ciudad)+strlen(USR.INSERTNEW)+strlen(USR.numerodecuenta)+strlen(USR.password)+40);

    if(queryTmp == NULL){
        return NULL;
    }
    strcpy(queryTmp,USR.INSERTNEW);
    strcat(queryTmp,USR.nombre);
    strcat(queryTmp,"',");
    strcat(queryTmp,USR.saldoT);
    strcat(queryTmp,",'");
    strcat(queryTmp,USR.fechanacimiento);
    strcat(queryTmp,"','");
    strcat(queryTmp,USR.curp);
    strcat(queryTmp,"','");
    strcat(queryTmp,USR.rfc);
    strcat(queryTmp,"','");
    strcat(queryTmp,USR.calle);
    strcat(queryTmp,"','");
    strcat(queryTmp,USR.colonia);
    strcat(queryTmp,"',");
    strcat(queryTmp,USR.cp);
    strcat(queryTmp,",'");
    strcat(queryTmp,USR.nacionalidad);
    strcat(queryTmp,"','");
    strcat(queryTmp,USR.estado);
    strcat(queryTmp,"','");
    strcat(queryTmp,USR.ciudad);
    strcat(queryTmp,"','");
    strcat(queryTmp,USR.password);
    strcat(queryTmp,"',");
    strcat(queryTmp,USR.numerodecuenta);
    strcat(queryTmp,");");

    return queryTmp;
}

bool STMTconnect(bool x){
    flag = true;
    if(x){
        try{
            DB.conn = mysql_init(NULL);

            DB.connenviroment = mysql_real_connect(DB.conn,hostname,userid,password,dbprefix,0,NULL,0);

            if(DB.connenviroment == NULL){
               cerr<<((char*)mysql_error(DB.connenviroment));
               system("pause");
               flag = false;
            }
        }
        catch(exception ex){
            cerr<<&ex<<endl;
            flag = false;
        }
    }
    return flag;
}

void STMTclose(MYSQL*HENV){
    mysql_close(HENV);
    DB.free();
}

void printDBinfoHost(){
    if(!STMTconnect(true)){
        return;
    }
    cout<<"                MySql Conexion: "<<mysql_get_host_info(DB.conn)<<endl;
    cout<<"                 MySql Cliente: "<<mysql_get_client_info()<<endl;
    cout<<"MySql Informacion del Servidor: "<<mysql_get_server_info(DB.conn)<<endl;
    STMTclose(DB.conn);
}

//<ENVIROMENT DATA BASE>

bool existUser(char*QUERYStmt){

    if(!STMTconnect(true)){
        return false;
    }
    flag = false;

    try{
        DB.status = mysql_query(DB.conn,QUERYStmt);
        if(DB.status){
            cerr<<mysql_error(DB.conn)<<endl;
        }
        else{
            DB.result = mysql_store_result(DB.conn);
            DB.rowsentinel = mysql_num_rows(DB.result);
            DB.fieldsentinel = mysql_num_fields(DB.result);

            if(DB.rowsentinel > 0){
                flag = true;
            }

            if(DB.result){
                mysql_free_result(DB.result);
            }
        }

    }catch(exception &ex){
        cerr<<ex.what()<<endl;
        throw ex;
    }

    if(DB.conn){
        STMTclose(DB.conn);
    }

    return flag;
}

char * getExisteUsuarioQ(char*account,char*pass){
    if(queryTmp){
        free(queryTmp);
    }
    queryTmp =(char*)malloc(sizeof(char)*(70+strlen(account)+strlen(pass)));

    if(!queryTmp){
        return NULL;
    }
    strcpy(queryTmp,USUARIO.SELECTEXIST);
    strcat(queryTmp,account);
    strcat(queryTmp," AND password = '");
    strcat(queryTmp,pass);
    strcat(queryTmp,"';");
    return queryTmp;
}
char * getExisteUsuarioQ(char*account){
    if(queryTmp){
        free(queryTmp);
    }
    queryTmp =(char*)malloc(sizeof(char)*(strlen(account)+strlen(USUARIO.SELECTEXIST)+10));

    if(!queryTmp){
        return NULL;
    }
    strcpy(queryTmp,USUARIO.SELECTEXIST);
    strcat(queryTmp,account);
    strcat(queryTmp,";");
    return queryTmp;
}

char* gdate(){
    tx = time(NULL);
    xt = localtime(&tx);
    char * loc = ctime(&tx);
    *(loc+24)=NULL;
    return loc;
}
void printdate(){
    gdate();
    (xt->tm_mday<10)?cout<<"0"<<xt->tm_mday<<"/":cout<<xt->tm_mday<<"/";
    (xt->tm_mon<10)?cout<<"0"<<xt->tm_mon<<"/":cout<<xt->tm_mon<<"/";
    cout<<xt->tm_year+1900;
}
#endif // CORE_H_INCLUDED

