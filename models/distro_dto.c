#include "../include/models/distro_dto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DistroDTO *create_distro() {
  DistroDTO *distro = (DistroDTO *)malloc(sizeof(DistroDTO));
  memset(distro, 0, sizeof(DistroDTO));

  distro->get_id = get_id_impl;
  distro->set_id = set_id_impl;
  distro->get_name = get_name_impl;
  distro->set_name = set_name_impl;
  distro->get_base = get_base_impl;
  distro->set_base = set_base_impl;
  distro->get_package_manager = get_package_manager_impl;
  distro->set_package_manager = set_package_manager_impl;
  distro->get_environment = get_environment_impl;
  distro->set_environment = set_environment_impl;

  return distro;
}

void read_distro(DistroDTO *distro) {
  char name[50];
  char base[50];
  char pkg_mng[50];
  char env[50];

  printf("Insira o nome: ");
  scanf("%s", name);
  distro->set_name(distro, name);

  printf("Insira a base: ");
  scanf("%s", base);
  distro->set_base(distro, base);

  printf("Insira o gerenciador de pacotes: ");
  scanf("%s", pkg_mng);
  distro->set_package_manager(distro, pkg_mng);

  printf("Insira o ambiente gráfico: ");
  scanf("%s", env);
  distro->set_environment(distro, env);
}

void free_distro(DistroDTO *distro) {
  if (distro == NULL) {
    return;
  }

  if (distro->id != NULL) {
    free(distro->id);
  }

  if (distro->name != NULL) {
    free(distro->name);
  }

  if (distro->base != NULL) {
    free(distro->base);
  }

  if (distro->package_manager != NULL) {
    free(distro->package_manager);
  }

  if (distro->environment != NULL) {
    free(distro->environment);
  }

  free(distro);
}

const char *get_id_impl(DistroDTO *self) {
  return self->id;
}

void set_id_impl(DistroDTO *self, char *id) {
  self->id = id;
}

const char *get_name_impl(DistroDTO *self) {
  return self->name;
}

void set_name_impl(DistroDTO *self, char *name) {
  self->name = strdup(name);
}

const char *get_base_impl(DistroDTO *self) {
  return self->base;
}

void set_base_impl(DistroDTO *self, char *base) {
  self->base = strdup(base);
}

const char *get_package_manager_impl(DistroDTO *self) {
  return self->package_manager;
}

void set_package_manager_impl(DistroDTO *self, char *package_manager) {
  self->package_manager = strdup(package_manager);
}

const char *get_environment_impl(DistroDTO *self) {
  return self->environment;
}

void set_environment_impl(DistroDTO *self, char *environment) {
  self->environment = strdup(environment);
}