FROM python:3.10-slim

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

RUN pip install --upgrade pip build scikit-build-core pybind11 numpy pytest

COPY . .

RUN python3 -m build

RUN pip install dist/*.whl

CMD ["pytest", "tests"]
