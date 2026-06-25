#ifndef DISTRO_DAO_H
#define DISTRO_DAO_H

#include "../models/distro_dto.h"

#include <libpq-fe.h>

void register_distro(PGconn *conn, DistroDTO *distro);

void select_all_distros(PGconn *conn);

int select_distro_by_name(PGconn *conn, char *distro_name, int output);

void update_distro(PGconn *conn, DistroDTO *distro);

void delete_distro(PGconn *conn, char *distro_id);

#endif