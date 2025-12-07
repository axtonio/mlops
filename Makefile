all: build

build:
	python3 -m build

install:
	PYTHONNOUSERSITE=1 pip install .

test:
	PYTHONNOUSERSITE=1 pytest tests

clean:
	rm -rf dist build src/hw1_mlops.egg-info src/hw1_mlops/*.so src/hw1_mlops/*.pyd _skbuild

docker-build:
	docker build -t hw1_mlops .

docker-run:
	docker run --rm hw1_mlops

wheel: docker-build
	mkdir -p dist
	@id=$$(docker create hw1_mlops); \
	docker cp $$id:/app/dist/. dist/; \
	docker rm -v $$id
	@if [ -n "$${SUDO_UID}" ]; then \
		chown -R $${SUDO_UID}:$${SUDO_GID} dist; \
	fi
