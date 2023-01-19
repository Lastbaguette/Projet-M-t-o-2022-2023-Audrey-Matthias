
sort: weathersort.o ABRSort.o AVLSort.o display.o create.o
	gcc weathersort.o ABRSort.o AVLSort.o display.o create.o -o sort

weathersort.o: weathersort.c
	gcc -c weathersort.c

ABRSort.o: ABRSort.c
	gcc -c ABRSort.c

AVLSort.o: AVLSort.c
	gcc -c AVLSort.c

display.o: display.c
	gcc -c display.c

create.o: create.c
	gcc -c create.c


clean:
	rm *.o sort
