# Makefile для сборки библиотеки и программы pr01

CC = gcc
CFLAGS = -Wall -Wextra -I.
AR = ar
ARFLAGS = rcs

LIB_DIR = mySimpleComputer
LIB_NAME = libmySimpleComputer.a
LIB_TARGET = $(LIB_DIR)/$(LIB_NAME)

SRCS = reg.c ram.c deviceControl.c input_output.c  # Добавлен input_output.c
OBJS = $(SRCS:.c=.o)
PR01_SRC = pr01.c
PR01_OBJ = $(PR01_SRC:.c=.o)
PR01_TARGET = pr01

all: $(LIB_TARGET) $(PR01_TARGET)

# Создание каталога, если он не существует
$(LIB_DIR):
	mkdir -p $(LIB_DIR)

# Сборка библиотеки
$(LIB_TARGET): $(OBJS) | $(LIB_DIR)
	@echo "Создание библиотеки $@"
	$(AR) $(ARFLAGS) $@ $^
	@echo "Содержимое библиотеки:"
	ar -t $@

# Сборка программы pr01
$(PR01_TARGET): $(PR01_OBJ) $(LIB_TARGET)
	@echo "Сборка программы $@"
	$(CC) $(CFLAGS) -o $@ $(PR01_OBJ) -L$(LIB_DIR) -lmySimpleComputer

# Компиляция исходных файлов в объектные
%.o: %.c
	@echo "Компиляция $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJS) $(LIB_TARGET) $(PR01_OBJ) $(PR01_TARGET)
	rm -rf $(LIB_DIR)

# Запуск программы pr01
run: $(PR01_TARGET)
	@echo "Запуск программы $(PR01_TARGET)"
	./$(PR01_TARGET)