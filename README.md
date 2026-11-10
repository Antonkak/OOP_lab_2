# Лабораторная работа 2 — вариант 17, семейство C: класс Matrix

## Структура

- `matrix.h` / `matrix.cpp` — класс `Matrix`: плоский буфер `double*`(элемент `(r, c)` → индекс `r * cols + c`), RAII, правило пяти, copy-and-swap.
- `main.cpp` — демонстрационная программа (пример использования из задания + `sum()`).
- `test_matrix.cpp` — тесты Google Test (23 теста).
- Вариант 17 — метод `double sum() const`: сумма всех элементов матрицы.

## Реализовано

- **RAII**: конструктор выделяет буфер `new double[...]`, деструктор освобождает `delete[]`.
- **Правило пяти**: копирующий конструктор (глубокая копия), перемещающий конструктор, перемещающий/копирующий деструктор.
- **Copy-and-swap**: `Matrix& operator=(Matrix other)` — аргумент по значению.
- **Методы**: `rows`, `cols`, `get`, `set`, `add`, `mul`, `sum` (вариант 17), `print`.
- `get`/`set` при неверных индексах и `add`/`mul` при несовпадении размеров кидают исключения.

## Сборка и запуск

```sh
cmake -S . -B build
cmake --build build
.\build\lab_02.exe        # демонстрация
.\build\test_matrix.exe   # тесты
```

## Проверка утечек

```sh
cmake -S . -B build -DCMAKE_CXX_FLAGS="-fsanitize=address"
cmake --build build
.\build\lab_02.exe
```
