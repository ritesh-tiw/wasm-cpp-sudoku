.PHONY: build
build:
	docker run --rm -v $(PWD):/src emscripten/emsdk:2.0.15 ./build.sh

.PHONY: run
run: build
	docker run --rm -v $(PWD)/public:/usr/share/nginx/html -p 80:80 nginx:latest
