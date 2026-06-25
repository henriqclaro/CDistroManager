#include "../include/models/distro_dao.h"

#include <libpq-fe.h>
#include <locale.h>
#include <stdio.h>

void register_distro(PGconn *conn, DistroDTO *distro) {
  if (select_distro_by_name(conn, distro->name, 0)) {
    printf("\e[1J\e[H\nNão é possível cadastrar uma distro com nome %s", distro->name);
    return;
  }

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
    fprintf(stderr, "Erro ao registrar distro:\n%s", PQerrorMessage(conn));
  } else {
    printf("\e[1J\e[HDistro cadastrada.");
  }

  PQclear(res);
}

void select_all_distros(PGconn *conn) {
  const char *query = "SELECT * FROM distro";

  PGresult *res = PQexec(conn, query);

  if (PQresultStatus(res) != PGRES_TUPLES_OK) {
    fprintf(stderr, "Erro ao selecionar distros:\n%s", PQerrorMessage(conn));
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

    printf("ID: %-5s | Nome: %-20s | Base: %-20s | Gerenciador: %-8s | "
           "Ambiente: %-15s\n",
           id, name, base, pkg_mng, env);
  }

  PQclear(res);
}

int select_distro_by_name(PGconn *conn, char *distro_name, int output) {
  const char *query = "SELECT * FROM distro WHERE name = $1";

  const char *value[1];
  value[0] = distro_name;

  PGresult *res = PQexecParams(conn, query, 1, NULL, value, NULL, NULL, 0);

  if (PQresultStatus(res) != PGRES_TUPLES_OK) {
    fprintf(stderr, "Erro ao buscar distro por nome:\n%s",
            PQerrorMessage(conn));
    PQclear(res);
    return 0;
  }

  int line = PQntuples(res);

  if (line == 0) {
    if (output) {
      printf("\e[1J\e[H\nNenhuma distro com nome %s encontrada.", distro_name);
    }
    PQclear(res);
    return 0;
  }

  if (output) {
    char *id = PQgetvalue(res, 0, 0);
    char *name = PQgetvalue(res, 0, 1);
    char *base = PQgetvalue(res, 0, 2);
    char *pkg_mng = PQgetvalue(res, 0, 3);
    char *env = PQgetvalue(res, 0, 4);

    printf(
        "\e[1J\e[H\nID: %-5s | Nome: %-20s | Base: %-20s | Gerenciador: %-8s | "
        "Ambiente: %-15s\n",
        id, name, base, pkg_mng, env);
  }

  PQclear(res);

  return 1;
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
    fprintf(stderr, "Erro ao atualizar distro:\n%s", PQerrorMessage(conn));
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
    fprintf(stderr, "Erro ao excluir distro:\n%s", PQerrorMessage(conn));
  } else {
    printf("\e[1J\e[HDistro excluída.");
  }

  PQclear(res);
}