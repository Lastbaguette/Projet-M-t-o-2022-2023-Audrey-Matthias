
sort: weathersort.o ./ABR/ABRSort.o ./AVL/AVLSort.o ./display/display.o ./create/create.o
	gcc weathersort.o ABRSort.o AVLSort.o display.o create.o -o sort

weathersort.o: weathersort.c
	gcc -c weathersort.c

./ABR/ABRSort.o: ./ABR/ABRSort.c
	gcc -c ABRSort.c

./AVL/AVLSort.o: ./AVL/AVLSort.c
	gcc -c AVLSort.c

./display/display.o: ./display/display.c
	gcc -c display.c

./create/create.o: ./create/create.c
	gcc -c create.c


clean:
	rm *.o sort