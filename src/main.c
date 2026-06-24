#include "../include/config/conn.h"
#include "../include/config/env.h"
#include "../include/models/distro_dao.h"
#include "../include/models/distro_dto.h"

#include <libpq-fe.h>
#include <locale.h>
#include <stdio.h>

int main() {
  setlocale(LC_ALL, "Portuguese");
  load_env();

  PGconn *conn = connect_db();

  char opt;

  printf("\e[1J\e[H");
  printf("----- Gerenciador de Distros de Linux -----");

  do {
    printf("\nSelecione uma opção:\n1) Registrar Distro\n2) Listar "
           "Distros\n3) Atualizar Distro\n4) Excluir Distro\n0) Encerrar "
           "programa\n> ");

    scanf(" %c", &opt);

    switch (opt) {
    case '1': {
      DistroDTO *distro = create_distro();

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

      register_distro(conn, distro);

      free_distro(distro);

      break;
    }
    case '2':
      select_all_distros(conn);
      break;
    case '3': {
      DistroDTO *distro = create_distro();

      char name[50];
      char base[50];
      char pkg_mng[50];
      char env[50];
      char distro_id[40];

      printf("Insira o ID da distro a atualizar: ");
      scanf("%s", distro_id);
      distro->set_id(distro, distro_id);

      printf("Insira o novo nome: ");
      scanf("%s", name);
      distro->set_name(distro, name);

      printf("Insira a nova base: ");
      scanf("%s", base);
      distro->set_base(distro, base);

      printf("Insira o novo gerenciador de pacotes: ");
      scanf("%s", pkg_mng);
      distro->set_package_manager(distro, pkg_mng);

      printf("Insira o novo ambiente gráfico: ");
      scanf("%s", env);
      distro->set_environment(distro, env);

      update_distro(conn, distro);

      free_distro(distro);

      break;
    }
    case '4': {
      char distro_id[8];

      printf("Insira o ID da distro a excluir: ");
      scanf("%s", distro_id);

      delete_distro(conn, distro_id);

      break;
    }
    case '0':
      printf("Encerrando programa...\n");
      break;
    default:
      printf("Selecione uma opção válida.\n");
      break;
    }
  } while (opt != '0');

  disconnect_db(conn);

  return 0;
}