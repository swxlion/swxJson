dirs = src tests

all:
	for x in $(dirs); do (cd $$x; make) || exit 1; done

lib:
	make -C src

test: lib
	make -C tests

clean:
	for x in $(dirs); do (cd $$x; make clean) || exit 1; done
