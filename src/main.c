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

  printf("\e[1J\e[H"); // Clear
  printf("----- Gerenciador de Distros de Linux -----");

  do {
    printf("\nSelecione uma opção:\n"
           "1) Registrar Distro\n2) Listar Distros\n"
           "3) Atualizar Distro\n4) Excluir Distro\n"
           "0) Encerrar programa\n> ");

    scanf(" %c", &opt);

    switch (opt) {
    case '1': {
      DistroDTO *distro = create_distro();

      read_distro(distro);

      register_distro(conn, distro);

      free_distro(distro);

      break;
    }

    case '2':
      select_all_distros(conn);
      break;

    case '3': {
      DistroDTO *distro = create_distro();
      char distro_id[40];

      printf("Insira o ID da distro a atualizar: ");
      scanf("%s", distro_id);
      distro->set_id(distro, distro_id);

      read_distro(distro);

      update_distro(conn, distro);

      free_distro(distro);

      break;
    }

    case '4': {
      char distro_id[40];

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