#ifndef DISTRO_DTO_H
#define DISTRO_DTO_H

typedef struct DistroDTO {
  const char *id;
  const char *name;
  const char *base;
  const char *package_manager;
  const char *environment;

  const char *(*get_id)(struct DistroDTO *self);
  void (*set_id)(struct DistroDTO *self, char *id);
  const char *(*get_name)(struct DistroDTO *self);
  void (*set_name)(struct DistroDTO *self, char *name);
  const char *(*get_base)(struct DistroDTO *self);
  void (*set_base)(struct DistroDTO *self, char *base);
  const char *(*get_package_manager)(struct DistroDTO *self);
  void (*set_package_manager)(struct DistroDTO *self, char *package_manager);
  const char *(*get_environment)(struct DistroDTO *self);
  void (*set_environment)(struct DistroDTO *self, char *environment);
} DistroDTO;

const char *get_id_impl(DistroDTO *self);

void set_id_impl(DistroDTO *self, char *id);

const char *get_name_impl(DistroDTO *self);

void set_name_impl(DistroDTO *self, char *name);

const char *get_base_impl(DistroDTO *self);

void set_base_impl(DistroDTO *self, char *base);

const char *get_package_manager_impl(DistroDTO *self);

void set_package_manager_impl(DistroDTO *self, char *package_manager);

const char *get_environment_impl(DistroDTO *self);

void set_environment_impl(DistroDTO *self, char *environment);

DistroDTO *create_distro();

void free_distro(DistroDTO *self);

#endif