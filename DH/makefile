CC = gcc
CFLAGS = -O2 -Wall -ansi 
DEBUG = 
INCLS = 
LIBS = -lm
OBJS_DH =  readfile.o utils.o dh.o smooth.o integrate.o
OBJS =  readfile.o utils.o smooth.o integrate.o dh2.o help.o
OBSFD = fakedata_dh.o utils_fd.o

#dh2: $(OBJS2)
#	$(CC) -o dh2 $(CFLAGS) $(DEBUG) $(OBJS2) $(LIBS)

dh2: $(OBJS)
	$(CC) -o dh2 $(CFLAGS) $(DEBUG) $(OBJS) $(LIBS)

dh:  $(OBJS_DH)
	$(CC) -o dh $(CFLAGS) $(DEBUG) $(OBJS_DH) $(LIBS)
	
fakedata: $(OBSFD)
	$(CC) -o fakedata $(CFLAGS) $(DEBUG) $(OBSFD) $(LIBS)


$(OBJS): 
	$(CC) $(CFLAGS) $(DEBUG) -c $*.c

$(OBSFD): 
	$(CC) $(CFLAGS) $(DEBUG) -c $*.c

$(OBS_DH): 
	$(CC) $(CFLAGS) $(DEBUG) -c $*.c
	
clean:
	@echo Initalizing nuclear vacuum cleaner......
	rm   dh dh2 fakedata *.o
	@echo Done.
	
