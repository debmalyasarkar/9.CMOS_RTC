CC = gcc

CFLAGS = -Wall -g

INCLUDES = 

LIBS = 

SRCS = usrSpaceRtc.c

OBJS = $(SRCS:.c=.o)

MAIN = usrSpaceRtc

all:    $(MAIN)
	@echo compilation completed

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)
