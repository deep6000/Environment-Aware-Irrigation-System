VPATH:=../src

# Declaration of variables
PLATFORM=HOST
TARGET=project02
BUILD:=DEFAULT 

ifeq ($(PLATFORM),HOST)
        CC := gcc
endif

ifeq ($(PLATFORM),BBG)
        CC := arm-linux-gcc
endif

CC_FLAGS = -Wall -g

#file names 
SOURCES = $(wildcard *.c)
INCLUDES:=-I../inc/
OBJECTS = $(SOURCES:.c=.o)
LIBS= -pthread -lrt -lm

build: $(OBJECTS)
	$(CC) $(LIBS) $(OBJECTS) -o $(TARGET) $(INCLUDES)

run : build
ifeq ($(PLATFORM),BBG)
	scp $(TARGET) debian@192.168.7.2:/home/debian/project02/$(TARGET)
else
	config-pin P9.11 uart
	config-pin P9.13 uart
	config-pin P9.22 uart
	config-pin P9.21 uart
	./$(TARGET) log.txt
endif


# to obtain object files
# object files for default build
ifeq ($(BUILD),DEFAULT)
%.o: %.c
	$(CC) -c $(CC_FLAGS) $^ -o $@ $(LIBS) $(INCLUDES)
endif

#object files for UART Loopback testing
ifeq ($(BUILD),LO)
%.o: %.c
	$(CC) -c $(CC_FLAGS) $^ -o $@ $(LIBS) $(INCLUDES) -DLO
endif

#object files for printf debugging
ifeq ($(BUILD),DEBUG)
%.o: %.c
	$(CC) -c $(CC_FLAGS) $^ -o $@ $(LIBS) $(INCLUDES) -DDEBUG
endif

#object files for UART Loopback and printf debugging
ifeq ($(BUILD),LO_DEBUG)
%.o: %.c
	$(CC) -c $(CC_FLAGS) $^ -o $@ $(LIBS) $(INCLUDES) -DLO -DDEBUG
endif

#object files for UART Loopback and printf debugging
ifeq ($(BUILD),LBC)
%.o: %.c
	$(CC) -c $(CC_FLAGS) $^ -o $@ $(LIBS) $(INCLUDES) -DLO -DDEBUG -DUART_CHAR
endif

# clean
clean:
	rm -rf $(TARGET) $(OBJECTS)
