TARGET = distro_manager

SRCS = src/main.c config/conn.c config/env.c models/distro_dto.c models/distro_dao.c
OBJS = $(SRCS:.c=.o)

CC = gcc

PG_CFLAGS = -I$(shell pg_config --includedir)

LDFLAGS = -L$(shell pg_config --libdir)

LDLIBS = -lpq

CFLAGS = -Wall -Wextra -O2 $(PG_CFLAGS)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean