#include <libpq-fe.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/config/conn.h"

PGconn *connect_db() {

  const char *dbname = getenv("DB_NAME");
  const char *user = getenv("DB_USER");
  const char *password = getenv("DB_PASSWORD");
  const char *host = getenv("DB_HOST");

  char conninfo[512];
  snprintf(conninfo, sizeof(conninfo), "dbname=%s user=%s password=%s host=%s",
           dbname, user, password, host);

  PGconn *conn = PQconnectdb(conninfo);

  if (PQstatus(conn) != CONNECTION_OK) {
    fprintf(stderr, "Database connection failed: %s", PQerrorMessage(conn));
    PQfinish(conn);
    return NULL;
  }

  return conn;
}

void disconnect_db(PGconn *conn) {
  if (conn != NULL) {
    PQfinish(conn);
    printf("Connection terminated.");
  }
}