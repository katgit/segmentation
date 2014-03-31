CC = gcc

LIBRARY = -L. -lm -L/project/earth/packages/gdal-1.10.0/lib  -lgdal


OBJECTS = envi_read.o


EXECUTABLE = segment

.SUFFIXES:
.SUFFIXES: .c .o 

%.o: %.c
	gcc -g -c $< 

$(EXECUTABLE): $(OBJECTS)
	gcc -o $@ $(OBJECTS) $(LIBRARY) 


clean:
	rm f *.o $(EXECUTABLE)
