#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void connexion(MYSQL *con, char username[50], char user_password[50], char dbname[50]) {
    if (mysql_real_connect(con, "localhost", username, user_password, dbname, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
}

