PROG = tp1a

GCCOBJ = gcc -c
GCCLNK = gcc
CFLAGS = -Wall -I -D_DEBUG
OBJ = emetteur.o recepteur.o canal.o tp1a.o matrice_tab.o

tp1a: $(OBJ)
	$(GCCLNK) $(CFLAGS) -o $@ $(OBJ)

tp1a.o: tp1a.c
	$(GCCOBJ) $(CFLAGS) $< -o $@

canal.o: canal.c canal.h
	$(GCCOBJ) $(CFLAGS) $< -o $@

emetteur.o: emetteur.c emetteur.h
	$(GCCOBJ) $(CFLAGS) $< -o $@

recepteur.o: recepteur.c recepteur.h
	$(GCCOBJ) $(CFLAGS) $< -o $@

matrice_tab.o: matrice_tab.c matrice_tab.h
		$(GCCOBJ) $(CFLAGS) $< -o $@

all: $(PROG)

clean:
	rm *.o
	rm $(PROG)

documentation:
	@doxygen doc/Doxyfile
	@xdg-open doc/html/index.html
	@echo "Documentation generated"
