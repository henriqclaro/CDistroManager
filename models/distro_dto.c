#include "../include/models/distro_dto.h"
#include <stdlib.h>

DistroDTO *create_distro() {
  DistroDTO *distro = (DistroDTO *)malloc(sizeof(DistroDTO));

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

void free_distro(DistroDTO *self) { free(self); }

const char *get_id_impl(DistroDTO *self) { return self->id; }

void set_id_impl(DistroDTO *self, char *id) { self->id = id; }

const char *get_name_impl(DistroDTO *self) { return self->name; }

void set_name_impl(DistroDTO *self, char *name) { self->name = name; }

const char *get_base_impl(DistroDTO *self) { return self->base; }

void set_base_impl(DistroDTO *self, char *base) { self->base = base; }

const char *get_package_manager_impl(DistroDTO *self) {
  return self->package_manager;
}

void set_package_manager_impl(DistroDTO *self, char *package_manager) {
  self->package_manager = package_manager;
}

const char *get_environment_impl(DistroDTO *self) { return self->environment; }

void set_environment_impl(DistroDTO *self, char *environment) {
  self->environment = environment;
}