## Exemple de Makefile avec macros
# definition du compilateur
CC = gcc
# definition des options de compilation pour obtenir un fichier .o
MYFLAGS = -c -O3
# definition des options de compilation pour obtenir un fichier .do
DEBUGFLAGS =-c -g -O3
#output folder
OUTPUTFOLDER = -o ./ofile/

#mysql lib
SQLIB = -lmysqlclient


# Fichier executable prod
parking: ./ofile/connexion.o ./ofile/createdb.o ./ofile/populate.o ./ofile/ajouterauto.o ./ofile/listerplaces.o ./ofile/marquerplace.o ./ofile/facture.o main.o
	$(CC) -o parking "./ofile/connexion.o" "./ofile/createdb.o" "./ofile/populate.o" "./ofile/ajouterauto.o" "./ofile/listerplaces.o" "./ofile/marquerplace.o" "./ofile/facture.o" "main.o" $(SQLIB)

# compile main
main.o: main.c
	$(CC) $(MYFLAGS) main.c $(SQLIB)

./ofile/lire.o:  lire.c
	$(CC) $(MYFLAGS) "lire.c" $(OUTPUTFOLDER)main.o $(SQLIB)

# compile connexion
./ofile/connexion.o:  ./source/connexion.c ./header/connexion.h
	$(CC) $(MYFLAGS) "./source/connexion.c" $(OUTPUTFOLDER)connexion.o $(SQLIB)

# compile ajouterauto
./ofile/ajouterauto.o:  ./source/ajouterauto.c ./header/ajouterauto.h
	$(CC) $(MYFLAGS) "./source/ajouterauto.c" $(OUTPUTFOLDER)ajouterauto.o $(SQLIB)

# compile createdb
./ofile/createdb.o:  ./source/createdb.c ./header/createdb.h
	$(CC) $(MYFLAGS) "./source/createdb.c" $(OUTPUTFOLDER)createdb.o $(SQLIB)

# compile facture
./ofile/facture.o:  ./source/facture.c ./header/facture.h
	$(CC) $(MYFLAGS) "./source/facture.c" $(OUTPUTFOLDER)facture.o $(SQLIB)

# compile listerplaces
./ofile/listerplaces.o:  ./source/listerplaces.c ./header/listerplaces.h
	$(CC) $(MYFLAGS) "./source/listerplaces.c" $(OUTPUTFOLDER)listerplaces.o $(SQLIB)

# compile marquerplace
./ofile/marquerplace.o:  ./source/marquerplace.c ./header/marquerplace.h
	$(CC) $(MYFLAGS) "./source/marquerplace.c" $(OUTPUTFOLDER)marquerplace.o $(SQLIB)

# compile populate
./ofile/populate.o:  ./source/populate.c ./header/populate.h
	$(CC) $(MYFLAGS) "./source/populate.c" $(OUTPUTFOLDER)populate.o $(SQLIB)

## Fichier executable pour le debuggage prod.db
#prod.db: produit.do main.do
#	$(CC) -o prod.db produit.do main.do
#main.do: main.c produit.h
#	$(CC) -o main.do $(DEBUGFLAGS) main.c
#produit.do: produit.c produit.h
#	$(CC) -o produit.do $(DEBUGFLAGS) produit.c