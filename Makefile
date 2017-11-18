KODEV=../kore/kodev/kodev
all: build
	@echo "Compiled"

run:
	${KODEV} run
clean:
	${KODEV} clean

build:
	${KODEV} build
