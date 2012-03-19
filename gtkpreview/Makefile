PROGRAM=gtkprev
SOURCES=main.cpp
VERSION=0.0.2

ifeq ($(strip $(PREFIX)),)
	PREFIX=/usr/local
endif

ifeq ($(strip $(CXXFLAGS)),)
	CXXFLAGS=-O3 `pkg-config --cflags --libs glib-2.0` `pkg-config --cflags --libs gdk-2.0` `pkg-config --cflags --libs gtk+-2.0`

endif

$(PROGRAM):$(SOURCES)
	g++ $(CXXFLAGS) -o $(PROGRAM) $(SOURCES)
	strip $(PROGRAM)

install:
	rm $(PROGRAM)||true
	g++ $(CXXFLAGS) -o $(PROGRAM) $(SOURCES)
	strip $(PROGRAM)
	cp $(PROGRAM) $(PREFIX)/bin

clean:
	rm $(PROGRAM)

