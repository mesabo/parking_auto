#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

///ON INITIALISE UNE NOUVELLE BASE DE DONNEES
void initdb(MYSQL *con)
{
    if (mysql_query(con, "CREATE DATABASE IF NOT EXISTS parkingdb"))
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    mysql_close(con);
}

