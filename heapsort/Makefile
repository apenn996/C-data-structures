# Define the machine object files for your program
OBJECTS = alm996Project6.o


# make for the executable
p6: ${OBJECTS}
	gcc -g -o p6 ${OBJECTS}

# Simple suffix rules for the .o
%.o: %.c 
	gcc -g -c -O3 $<

# Clean the .o files
clean:
	rm -f ${OBJECTS}
