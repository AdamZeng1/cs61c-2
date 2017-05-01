beargit: main.c beargit.c beargit.h util.h
	gcc -std=c99 main.c beargit.c -o beargit

clean:
	rm -rf beargit autotest test

test:
	gcc -g ./tests/test_beargit.c beargit.c ./Unity/src/unity.c -o ./tests/test-beargit && cd tests && ./test-beargit && cd ..

check::
ifndef INSTMANPATH
	$(error You need to run 'make check' on an instructional machine, such as hive*.cs.berkeley.edu)
endif
	python2.7 tester.pyc beargit.c
