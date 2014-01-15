CC = g++

#LIBGDAL = -L$(HOME)/lib/gdal_build/gdal -lgdal
#INCGDAL = -I$(HOME)/lib/gdal_build/gdal/include
LIBGDAL = -L/net/usr/local/lib -lgdal
INCGDAL = -I/net/usr/local/include

CFLAGS = -lm -lpthread $(LIBGDAL) $(INCGDAL)

SOURCE = *.cpp

MYPROG = edge_mask

all: $(MYPROG)

$(MYPROG): $(SOURCE)
	    $(CC) $(SOURCE) -o $(MYPROG) $(CFLAGS)

clean:
	    rm -f $(MYPROG)
