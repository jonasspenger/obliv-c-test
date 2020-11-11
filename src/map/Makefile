CILPATH=../../obliv-c
COMMONPATH=../../obliv-c/test/oblivc/common
REMOTE_HOST=localhost
CFLAGS += -DREMOTE_HOST=$(REMOTE_HOST) -O3

./a.out: main.c map.oc map.c map.h $(COMMONPATH)/util.c $(CILPATH)/_build/libobliv.a oblivstatefun.o
	$(CILPATH)/bin/oblivcc $(CFLAGS) -I . main.c map.oc map.c $(COMMONPATH)/util.c oblivstatefun.o

oblivstatefun.o: oblivstatefun.c
	$(CILPATH)/bin/oblivcc -c oblivstatefun.c

clean:
	rm -f a.out oblivstatefun.o
