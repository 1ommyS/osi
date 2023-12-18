# Исходные файлы
SRC = client.cpp server.cpp

# Объектные файлы
OBJ = $(SRC:.cpp=.o)

# Выходной файл
OUT = game

# Компилятор и флаги
CC = g++
FLAGS = -g -Wall -lzmq -pthread

# Правило по умолчанию
default: $(OUT)

# Правило для компиляции
.cpp.o:
	$(CC) $(FLAGS) -c $< -o $@

# Правило для линковки
$(OUT): $(OBJ)
	$(CC) $(FLAGS) -o $(OUT) $(OBJ)

# Правило для запуска игры
run: $(OUT)
	./$(OUT)

# Правило для очистки
clean:
	rm -f $(OBJ) $(OUT)