sort: weathersort.c ./ABR/ABRSort.o ./AVL/AVLSort.o ./List/List.o ./display/display.o ./create/create.o
	gcc weathersort.c -lm ABRSort.o AVLSort.o List.o display.o create.o -o sort

./ABR/ABRSort.o: ./ABR/ABRSort.c
	gcc -c ./ABR/ABRSort.c 

./AVL/AVLSort.o: ./AVL/AVLSort.c
	gcc -c ./AVL/AVLSort.c 

./List/List.o: ./List/List.c
	gcc -c ./List/List.c 

./display/display.o: ./display/display.c
	gcc -c ./display/display.c 

./create/create.o: ./create/create.c 
	gcc -c ./create/create.c 


clean:
	rm *.o sort

