CC = gcc
CFLAGS = -O2 -Wall -ansi 
DEBUG = 
INCLS = 
LIBS = -lm
# OBJS2 =  readfile.o utils.o dh2.o smooth.o integrate.o
OBJS =  readfile.o utils.o smooth.o integrate.o mecl.o 


#dh2: $(OBJS2)
#	$(CC) -o dh2 $(CFLAGS) $(DEBUG) $(OBJS2) $(LIBS)

mecl: $(OBJS)
	$(CC) -o mecl $(CFLAGS) $(DEBUG) $(OBJS) $(LIBS)
	
$(OBJS): 
	$(CC) $(CFLAGS) $(DEBUG) -c $*.c

#$(OBJS2): 
#	$(CC) $(CFLAGS) $(DEBUG) -c $*.c
	
clean:
	@echo Initalizing nuclear vacuum cleaner......
	rm   mecl *.o
	@echo Done.
	
