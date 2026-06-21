CC = gcc
PG_CONFIG = /usr/pgsql-18/bin/pg_config

CFLAGS = $(shell $(PG_CONFIG) --cflags)
LIBS = $(shell $(PG_CONFIG) --libs)

SRC = src/main.c
TARGET = distro_mvc

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)