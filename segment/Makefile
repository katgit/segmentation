CC = gcc

LIBRARY = -L. -lm -L/project/earth/packages/gdal-1.10.0/lib  -lgdal

OBJECTS = bihcheck.o bihdup.o bihmake.o bihread.o bihwrite.o hdralloc.o hnbands.o hnbits.o hnbytes.o hnlines.o hnsamps.o ipwenter.o main.o pixel.o region.o segment.o set.o uropen.o ustdin.o uwopen.o _bug.o _errno.o _error.o _fderr.o _usrerr.o usrerr.o uferr.o uclose.o uwrite.o uremove.o uread.o uwflush.o ufilename.o ipwexit.o syserr.o allocnd.o ecalloc.o hwprmb.o skiphdrs.o hrname.o hrskip.o _uiocb.o _uread.o _uwrite.o _uioinit.o _hrrec.o _hdriocb.o _hwrec.o uputs.o ugets.o rmtrail.o hputrec.o ubof.o ndig.o _argv.o _bih.o hstrdup.o hrband.o hgetrec.o hostorder.o rmlead.o addsv.o ok_sv.o pvwrite.o _pioinit.o _piocb.o hbyteorder.o walksv.o no_tty.o _nohist.o dupsv.o getargs.o ipwgetopt.o _descrip.o _optv.o cmdline.o itoa.o usage.o _ipwenter.o do_headers.o header_read.o get_header_field_value.o trim.o 

INCLUDE_FILES=segment.h set.h segport.h 

EXECUTABLE = segment

.SUFFIXES:
.SUFFIXES: .c .o 

%.o: %.c
	gcc -g -c $< 

$(EXECUTABLE): $(OBJECTS)
	gcc -o $@ $(OBJECTS) $(LIBRARY) 

$(OBJECTS): $(INCLUDE_FILES) 

clean:
	rm f *.o $(EXECUTABLE)
