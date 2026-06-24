#include "../include/models/distro_dao.h"

#include <libpq-fe.h>
#include <locale.h>
#include <stdio.h>

void register_distro(PGconn *conn, DistroDTO *distro) {
  const char *query = "INSERT INTO distro "
                      "(name, base, package_manager, environment) "
                      "VALUES ($1, $2, $3, $4)";

  const char *values[4];
  values[0] = distro->name;
  values[1] = distro->base;
  values[2] = distro->package_manager;
  values[3] = distro->environment;

  PGresult *res = PQexecParams(conn, query, 4, NULL, values, NULL, NULL, 0);

  if (PQresultStatus(res) != PGRES_COMMAND_OK) {
    fprintf(stderr, "Error on registering distro:\n%s", PQerrorMessage(conn));
  } else {
    printf("\e[1J\e[HDistro cadastrada.");
  }

  PQclear(res);
}

void select_all_distros(PGconn *conn) {
  const char *query = "SELECT * FROM distro";

  PGresult *res = PQexec(conn, query);

  if (PQresultStatus(res) != PGRES_TUPLES_OK) {
    fprintf(stderr, "Error on fetching distros:\n%s", PQerrorMessage(conn));
    PQclear(res);
    return;
  }

  int lines = PQntuples(res);

  printf("\e[1J\e[H\n%d distros selecionadas:\n", lines);

  for (int i = 0; i < lines; i++) {
    char *id = PQgetvalue(res, i, 0);
    char *name = PQgetvalue(res, i, 1);
    char *base = PQgetvalue(res, i, 2);
    char *pkg_mng = PQgetvalue(res, i, 3);
    char *env = PQgetvalue(res, i, 4);

    printf("ID: %s | Nome: %s | Base: %s | Gerenciador: %s | Ambiente: %s\n",
           id, name, base, pkg_mng, env);
  }

  PQclear(res);
}

void update_distro(PGconn *conn, DistroDTO *distro) {
  const char *query =
      "UPDATE distro SET "
      "name = $1, base = $2, package_manager = $3, environment = $4 "
      "WHERE id = $5";

  const char *values[5];
  values[0] = distro->name;
  values[1] = distro->base;
  values[2] = distro->package_manager;
  values[3] = distro->environment;
  values[4] = distro->id;

  PGresult *res = PQexecParams(conn, query, 5, NULL, values, NULL, NULL, 0);

  if (PQresultStatus(res) != PGRES_COMMAND_OK) {
    fprintf(stderr, "Error on updating distro:\n%s", PQerrorMessage(conn));
  } else {
    printf("\e[1J\e[HDistro atualizada.");
  }

  PQclear(res);
}

void delete_distro(PGconn *conn, char *distro_id) {
  const char *query = "DELETE FROM distro WHERE id = $1";

  const char *value[1];
  value[0] = distro_id;

  PGresult *res = PQexecParams(conn, query, 1, NULL, value, NULL, NULL, 0);

  if (PQresultStatus(res) != PGRES_COMMAND_OK) {
    fprintf(stderr, "Error on deleting distro:\n%s", PQerrorMessage(conn));
  } else {
    printf("\e[1J\e[HDistro excluída.");
  }

  PQclear(res);
}