PROG = tp1b

GCCOBJ = gcc -c
GCCLNK = gcc
CFLAGS = -Wall -I -D_DEBUG
OBJ = codeurs.o decodeurs.o tp1b.o

tp1b: $(OBJ)
	$(GCCLNK) $(CFLAGS) -o $@ $(OBJ)

tp1b.o: tp1b.c
	$(GCCOBJ) $(CFLAGS) $< -o $@

codeurs.o: codeurs.c codeurs.h
	$(GCCOBJ) $(CFLAGS) $< -o $@

decodeurs.o: decodeurs.c decodeurs.h 
	$(GCCOBJ) $(CFLAGS) $< -o $@

all: $(PROG)

clean:
	rm *.o
	rm $(PROG)

documentation:
	@doxygen doc/Doxyfile
	@xdg-open doc/html/index.html
	@echo "Documentation generated"
