PROG = tp2_long_max tp2_gold tp2_jpl

GCCOBJ = gcc -c
GCCLNK = gcc
CFLAGS = -Wall -I -D_DEBUG
long_max_obj_message = tp2_long_max.o long_max.o
gold_obj_message = tp2_gold.o gold.o long_max.o
jpl_obj_message = tp2_jpl.o jpl.o long_max.o

tp2_long_max: $(long_max_obj_message)
	$(GCCLNK) $(CFLAGS) -o $@ $(long_max_obj_message) -lm

tp2_gold: $(gold_obj_message)
	$(GCCLNK) $(CFLAGS) -o $@ $(gold_obj_message) -lm

tp2_jpl: $(jpl_obj_message)
	$(GCCLNK) $(CFLAGS) -o $@ $(jpl_obj_message) -lm

jpl.o: jpl.c jpl.h
	$(GCCOBJ) $(CFLAGS) $< -o $@

gold.o: gold.c gold.h
	$(GCCOBJ) $(CFLAGS) $< -o $@

long_max.o: long_max.c long_max.h
	$(GCCOBJ) $(CFLAGS) $< -o $@

all: $(PROG)

clean:
	rm *.o
	rm $(PROG)

documentation:
	@doxygen doc/Doxyfile
	@xdg-open doc/html/index.html
	@echo "Documentation generated"
