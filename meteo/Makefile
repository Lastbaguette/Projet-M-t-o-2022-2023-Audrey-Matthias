
sort: weathersort.o ./ABR/ABRSort.o ./AVL/AVLSort.o ./display/display.o ./create/create.o
	gcc weathersort.o ./ABR/ABRSort.o ./AVL/AVLSort.o ./display/display.o ./create/create.o -o sort

weathersort.o: weathersort.c
	gcc -c weathersort.c

./ABR/ABRSort.o: ./ABR/ABRSort.c
	gcc -c ./ABR/ABRSort.c

./AVL/AVLSort.o: ./AVL/AVLSort.c
	gcc -c ./AVL/AVLSort.c

./display/display.o: ./display/display.c
	gcc -c ./display/display.c

./create/create.o: ./create/create.c
	gcc -c ./create/create.c


clean:
	rm *.o sort
