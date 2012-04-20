PROGRAM=gtkprev
SOURCES=main.cpp globals.cpp database.cpp
VERSION=0.0.3
GUI=xfce-theme-manager
LAUNCHER=Xfce-Theme-Manager.desktop

ifeq ($(strip $(PREFIX)),)
	PREFIX=/usr/local
endif

ifeq ($(strip $(CXXFLAGS)),)
	CXXFLAGS=-O3 -Wall -lXcursor `pkg-config --cflags --libs glib-2.0` `pkg-config --cflags --libs gdk-2.0` `pkg-config --cflags --libs gtk+-2.0`
endif

$(PROGRAM):$(SOURCES)
	g++ $(CXXFLAGS) -o $(PROGRAM) $(SOURCES)
	strip $(PROGRAM)

install:
	mkdir -p $(DESTDIR)$(PREFIX)/bin $(DESTDIR)$(PREFIX)/share/applications
	rm $(PROGRAM)||true
	g++ $(CXXFLAGS) -o $(PROGRAM) $(SOURCES)
	strip $(PROGRAM)
	chmod +x ../$(GUI)
	cp $(PROGRAM) ../$(GUI) $(DESTDIR)$(PREFIX)/bin
	cp ../$(LAUNCHER) $(DESTDIR)$(PREFIX)/share/applications

install-helper:
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	rm $(PROGRAM)||true
	g++ $(CXXFLAGS) -o $(PROGRAM) $(SOURCES)
	strip $(PROGRAM)
	cp $(PROGRAM) $(DESTDIR)$(PREFIX)/bin

uninstall:
	rm $(DESTDIR)$(PREFIX)/bin/$(PROGRAM) $(DESTDIR)$(PREFIX)/share/applications/$(LAUNCHER) $(DESTDIR)$(PREFIX)/bin/$(GUI)
clean:
	rm $(PROGRAM)

