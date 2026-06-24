#include "../include/config/conn.h"
#include "../include/config/env.h"

#include <libpq-fe.h>

int main() {
  load_env();

  PGconn *conn = connect_db();

  disconnect_db(conn);

  return 0;
}