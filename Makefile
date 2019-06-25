OBJ=main.o utils.o csv.o dbscan.o points.o distance.o
#OBJ=main.o csv.o points.o distance.o
CC=g++

all: dbscan

dbscan: $(OBJ)
	$(CC) -o dbscan $(OBJ)

main.o: utils.h points.h distance.h csv.h main.cc

utils.o: utils.h utils.cc

csv.o: csv.h utils.h distance.h csv.cc

dbscan.o: utils.h dbscan.h distance.h dbscan.cc

points.o: utils.h points.h points.cc

distance.o: points.h distance.h distance.cc