# LP check

Проект для тестирования скорости работы LP решателей

___

## <a id="title1"> **:computer: Установка и запуск**

### 1. Клонирование репозитория
```bash
git clone https://github.com/arssmol1029/lp_check
cd lp_check
```

### 2. Установка зависимостей

**Системные зависимости**
+ CMake ≥ 3.10
+ C++17
+ Make или Ninja

**Зависимости решателей**
+ [SCIP](https://scipopt.org/#download)
+ [HiGHS](https://ergo-code.github.io/HiGHS/dev/installation/)
+ [lp_solve](https://web.mit.edu/lpsolve/doc/)


### 3. Сборка и запуск
```bash
mkdir build && cd build
cmake ..
```

Если решатели установлены не по стандартным путям, при сборке необходимо указать пути до них
```bash
cmake -DLPSOLVE_ROOT_DIR=/path/to/lp_solve \
      -DHIGHS_ROOT_DIR=/path/to/scip \
      -DSCIP_ROOT_DIR=/path/to/highs \
      ..
```

```bash
cmake --build .
./lp_benchmark
```

___

## <a id="title2"> :file_folder: Структура проекта

```text
lp_check/
├── CMakeLists.txt              # Конфигурация сборки
├── .gitignore
├── src/
│   ├── main.cpp                # Основная программа
│   ├── ScipSolver.cpp          # Реализация SCIP решателя
│   ├── HighsSolver.cpp         # Реализация HiGHS решателя
│   └── LpSolveSolver.cpp       # Реализация LP_Solve решателя
├── include/                    # Заголовочные файлы
├── tests/                      # Тестовые задачи LP
│   ├── lp_files                # Задачи в формате .lp
└── ├── mps_files               # Задачи в формате .mps
```

___

## <a id="title3"> :mailbox_with_mail: Контакты

+ **Автор:** arssmol1029
+ **Telegram:** [@kepolb](https://t.me/kepolb)