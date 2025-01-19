#include <iostream>
#include <vector>
#include <mysql/mysql.h>
using std::cout;
using std::vector;
using std::endl;

typedef unsigned long long ull;

int main(int argc, char** argv) {

    // Init
    mysql_library_init(0, NULL, NULL);
    MYSQL* connection = mysql_init(NULL);


    const char* host, *user, *password, *db;
    host = "localhost";
    user = "datura";
    password = "goose";
    db = "supp";

    connection = mysql_real_connect(connection, host, user, password, db, 0, NULL, 0);

    const char* query = "SELECT * FROM S";
    int err = mysql_query(connection, query);

    if (err) {
        const char* e = mysql_error(connection);
        unsigned int en = mysql_errno(connection);
        cout << e << endl;
        exit(1);
    }

    my_ulonglong affected = mysql_affected_rows(connection);
    unsigned int fc = mysql_field_count(connection);
    cout << "Affected: " << affected << endl;
    cout << "Field count: " << fc << endl << endl;

    MYSQL_RES* res = mysql_store_result(connection);
    ull returned = mysql_num_rows(res);

    cout << "Returned: " << returned << endl;

    MYSQL_ROW row;
    unsigned int num_fields = mysql_num_fields(res);
    while ( (row = mysql_fetch_row(res)) ) {
        for (unsigned int i=0; i< num_fields; ++i) {
            cout << (row[i] ? row[i] : "NULL") << '\t';
        }
        cout << endl;
    }
    mysql_free_result(res);

    mysql_close(connection);
    mysql_library_end();

    /* 
        #include <mysql.h>

        MYSQL
        MYSQL_RES
        MYSQL_ROW
        my_ulonglong

        unsigned int mysql_errno(MYSQL *mysql);
        const char *mysql_error(MYSQL *mysql);

        int mysql_library_init(int argc, char **argv, char **groups)
        void mysql_library_end(void)
        MYSQL *mysql_init(MYSQL *mysql)
        MYSQL *mysql_real_connect(MYSQL *mysql, const char *host, const char *user, const char *passwd, const char *db, unsigned int port, const char *unix_socket, unsigned long client_flag)
        void mysql_close(MYSQL *mysql)

        int mysql_query(MYSQL *mysql, const char *stmt_str)
        int mysql_real_query(MYSQL *mysql, const char *stmt_str, unsigned long length)

        my_ulonglong mysql_affected_rows(MYSQL *mysql)
        my_ulonglong mysql_num_rows(MYSQL_RES *result)
        unsigned int mysql_field_count(MYSQL *mysql)
        my_ulonglong mysql_insert_id(MYSQL *mysql)

        MYSQL_RES *mysql_store_result(MYSQL *mysql)
        MYSQL_RES *mysql_use_result(MYSQL *mysql)
        MYSQL_ROW mysql_fetch_row(MYSQL_RES *result)
        unsigned long *mysql_fetch_lengths(MYSQL_RES *result)

        g++ -I/usr/include/mariadb -lmariadb -o bin src.cc





     */

    return 0;
}
