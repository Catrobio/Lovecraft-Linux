# Lovecraf-Linux

<img src="https://raw.githubusercontent.com/CatrobioLovecraft-Linux/blob/master/Lovecraft-images/Lovecraft-logo.png" />

_Lovecraft para Linux - Postgresql_

## Comenzando 🚀

_Está diseñada para configurar el archivo .lvc para conexión a base de datos Postgres.
Posteriormente este archivo funcionará para que los .cgi [Yogsothoth](https://github.com/Catrobio/YogSothoth) y [Azathoth](https://github.com/Catrobio/Azathoth) puedan conectarse a la base de datos.
Tambien puedes hacer purebas de conexión y Querys a la base de datos que se encuentre configurada._

### Pre-requisitos 📋

_Necesitas para que funcione: linux y potgresql._

### Instalación 🔧

_Una serie de ejemplos paso a paso que te dice lo que debes ejecutar para tener un entorno de desarrollo ejecutandose_

_Primero se debe compilar el ejecuable_
```
g++ Lovecraft.cpp -o Lovecraft -Wall -I/usr/local/pgsql/include -L/usr/local/pgsql/lib -lpq
```
_Ejecutar Lovecraft_
```
./Lovecraft
```
_Solicitará la configuración de conexion a la base de datos_
```
Configurations...
Server database:localhost

Port:5432

Database:postgres

Schema:example

User:postgres

Password:postgres123

Are you sure this is your configuration: (Server: localhost Database: postgres User: postgres)? 'y' to confirm
```

_Finalizado mostrará el menú_

```
************************************************
*                      PGSQL                   *
*                 L O V E C R A F T            *
************************************************

************************************************
*                     Menu                     *
************************************************

1. Test to Database Connection
2. Build Query
3. Exit
Option:
```

_Seleccionar la opcion 1 para hacer el test de conexion_

## Ejecutando las pruebas ⚙️

```
************************************************
*                      PGSQL                   *
*                 L O V E C R A F T            *
************************************************

************************************************
*    1. Test to Database Connection            *
************************************************

{"Data":[{"tablename":"operations"},{"tablename":"usersinformations"},{"tablename":"users"}], "CodeStatus":"0", "Msg" : ""}
```

### Al hacer un Query con la opcion 2 ⌨️

```
Query: select * from "example"."users"

{"Data":[{"iduser":"31","username":"fpacheco","pass":"q1c.AQ$QB309","identy":"123","names":"Francisco","lastname":"Pacheco","datecreate":"2017-05-08 14:30:00","datebirthday":"1987-05-27","ispublic":"","iduserstatus":"1","idusertype":"2","idtypeauthentication":"2"},{"iduser":"30","username":"mchirinos","pass":"u3c,=f<QB3","identy":"85765","names":"Milagros","lastname":"Chirinos","datecreate":"2019-05-08 14:30:00","datebirthday":"1984-05-29","ispublic":"","iduserstatus":"1","idusertype":"2","idtypeauthentication":"2"},{"iduser":"36","username":"ialva","pass":"ti];z}A02O 7j8","identy":"123","names":"Ignacio","lastname":"Alvarez","datecreate":"2017-05-08 14:30:00","datebirthday":"1987-05-27","ispublic":"","iduserstatus":"1","idusertype":"1","idtypeauthentication":"1"},{"iduser":"37","username":"vrodriguez","pass":"nLB5pP0QB309","identy":"212345","names":"Victor","lastname":"Rodriguez","datecreate":"2017-05-08 14:30:00","datebirthday":"1980-05-27","ispublic":"","iduserstatus":"1","idusertype":"2","idtypeauthentication":"2"}], "CodeStatus":"0", "Msg" : ""}
```

## En caso de necesitar la libreria de de conexion de postgres 📦

```
apt-get install libpq-devy
apt install g++
```

## Autor ✒️

_Lovecraft se compone de tres proyectos: Lovecraft, YogSothoth y Azathoth_

* **Francisco Ignacio Pacheco** - *Trabajo Inicial* - [Desaroollador backend](https://www.linkedin.com/in/francisco-ignacio-pacheco-72293431)

## Muchas gracias!! 🎁

