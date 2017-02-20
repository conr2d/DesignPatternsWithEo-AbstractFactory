CC = gcc
CFLAGS = -c -g -Wall
LDFLAGS =

SOURCES = main.c
OBJECTS = $(SOURCES:.c=.o)

CFLAGS += `pkg-config --cflags eina eo`
LDFLAGS += `pkg-config --libs eina eo`

EXECUTABLE = main

EO_CC = eolian_gen
EO_PATH = ./eo
EO_FILES = ui_factory.eo \
	mobile_ui_factory.eo \
	wearable_ui_factory.eo \
	ui_button.eo \
	mobile_ui_button.eo \
	wearable_ui_button.eo

EO_SOURCES = $(EO_FILES:.eo=.eo.c)
EO_HEADERS = $(EO_FILES:.eo=.eo.h)

PREFIX = /usr/local

all: $(EXECUTABLE)
	rm -f $(EO_SOURCES) $(EO_HEADERS)

ccode: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

$(OBJECTS): $(SOURCES) $(EO_SOURCES)
	$(CC) $< $(CFLAGS)

$(EO_SOURCES):
	$(foreach EO, $(EO_FILES), $(EO_CC) $(EO_PATH)/$(EO) -I. -I$(PREFIX)/share/eolian/include;)
	mv $(EO_PATH)/*.eo.h .
	mv $(EO_PATH)/*.eo.c .

clean:
	rm -f $(EXECUTABLE) $(OBJECTS) *.eo.h *.eo.c
