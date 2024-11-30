head = pctl2.h 
srcs = pctl2.c 
objs = pctl2.o 
opts = -g -c 
all: pctl2 
pctl2: $(objs) 
	gcc $(objs) -o pctl2  
pctl2.o: $(srcs) $(head) 
	gcc $(opts) $(srcs)  
clean: 
	rm pctl2 *.o
