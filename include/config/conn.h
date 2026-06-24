#ifndef CONN_H
#define CONN_H

#include <libpq-fe.h>

PGconn *connect_db();

void disconnect_db(PGconn *conn);

#endif