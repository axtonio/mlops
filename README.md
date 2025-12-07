# MLOps | HW1

Реализована функция **To Gray**, код тут [`src/main.cpp`](src/main.cpp)

## Local

Подготовка окружения:

```bash
conda create -n hw1_env python=3.10
conda activate hw1_env
conda install numpy pytest pybind11
```

Установка и тесты:

```bash
make install
make test
```

## Docker

```bash
sudo make docker-build
sudo make docker-run
```

## WHL

Получить whl из докера себе на компьютер:

```bash
sudo make wheel
```

Файл появится в папке `dist/`
