//programa en C para consultar los datos de la base de datos
//#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char consulta [80];
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL)
	{
		printf ("Error al crear la conexión: %u %s\n",
		mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "Ej",0, NULL, 0);
	if (conn==NULL)
	{
		printf ("Error al inicializar la conexión: %u %s\n",
		mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	err=mysql_query (conn, "SELECT * FROM JUGADOR");
	if (err!=0)
	{
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
	exit (1);
	}

/*
. . .
*/
	//recogemos el resultado de la consulta
	resultado = mysql_store_result (conn);
	// El resultado es una estructura matricial en la que cada
	// fila contiene los datos de una socio y sucesivos
	// columnas contienen cada uno de los datos del socio
	// recorremos una a una cada fila del resultado
	// ahora obtenemos la siguiente fila
	row = mysql_fetch_row (resultado);
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
		while (row !=NULL)
		{
			// las columnas 0,1,2, 3 y 4 contienen (ID,user,pass,email,amigos);
			printf ("User: %s Pass: %s Email: %s Amigos: %s\n",
					row[1], row[2], row[3], row[4]);
			// obtenemos la siguiente fila
			row = mysql_fetch_row (resultado);
		}
		
		
		
		
	printf ("Selecione fila a cambiar:\n");
	int* x;
	char name [10];
	char pass [12];
	char email[30];
	scanf ("%d", &x);
	printf("Nuevo User:\n");
	scanf ("%s", name);
	printf("Nuevo Pass:\n");
	scanf ("%s", pass);
	printf("Nuevo Email:\n");
	scanf ("%s", email);
	
	sprintf (consulta, "UPDATE JUGADOR SET USERNAME = REPLACE(USERNAME, USERNAME, '%s') WHERE JUGADOR.ID = '%d'", name, x);
	err=mysql_query (conn, consulta);
	if (err!=0)
	{
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}	
	
	sprintf (consulta, "UPDATE JUGADOR SET PASS = REPLACE(PASS, PASS, '%s') WHERE JUGADOR.ID = '%d'", pass, x);
	err=mysql_query (conn, consulta);
	if (err!=0)
	{
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}	
	
	sprintf (consulta, "UPDATE JUGADOR SET EMAIL = REPLACE(EMAIL, EMAIL, '%s') WHERE JUGADOR.ID = '%d'", email, x);
	err=mysql_query (conn, consulta);
	if (err!=0)
	{
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	
	err=mysql_query (conn, "SELECT * FROM JUGADOR");
	if (err!=0)
	{
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	resultado = mysql_store_result (conn);
	row = mysql_fetch_row (resultado);
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
		while (row !=NULL)
	{
			// las columnas 0,1,2, 3 y 4 contienen (ID,user,pass,email,amigos);
			printf ("User: %s Pass: %s Email: %s Amigos: %s\n",
					row[1], row[2], row[3], row[4]);
			// obtenemos la siguiente fila
			row = mysql_fetch_row (resultado);
	}
	
	// cerrar la conexión con el servidor MYSQL
	mysql_close (conn);
}
	
