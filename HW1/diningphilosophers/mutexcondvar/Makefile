CC	= cc
CFLAGS	= -O
LDFLAGS	=

NAME	= diningphilos
HDRS	= diningphilos.h
OBJS	= $(NAME).o monitor.o 
LIBS	= -lpthread -lm
OUT	= $(NAME)

$(OUT):	$(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

$(NAME).o:	$(NAME).c $(HDRS)
monitor.o:	monitor.c diningphilos.h
dingphilos.o:	diningphilos.c dingphilos.h

clean:
	/bin/rm -f $(OBJS)

clobber:
	/bin/rm -f $(OBJS) $(OUT)
