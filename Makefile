PROGRAM=xfce-theme-manager
SOURCES=src/main.cpp src/globals.cpp src/database.cpp src/thumbnails.cpp src/gui.cpp src/callbacks.cpp
VERSION=0.2.1
LAUNCHER=Xfce-Theme-Manager.desktop

ifeq ($(strip $(PREFIX)),)
	PREFIX=/usr/local
endif

TESTFORLIBXFCEUI=$(shell pkg-config --exists libxfce4ui-1 2>/dev/null;echo $$?)

ifeq ($(TESTFORLIBXFCEUI),0)
	USELIBXFCEUI="-DGOT_LIBXFCEUI"
	LIBXFCEUI=`pkg-config --cflags --libs libxfce4ui-1`	
endif

ifeq ($(strip $(CXXFLAGS)),)
	CXXFLAGS=-O3 -Wall -Wunused-result -Wunused-function -lXcursor -lgthread-2.0 `pkg-config --cflags --libs glib-2.0` `pkg-config --cflags --libs gdk-2.0` `pkg-config --cflags --libs gtk+-2.0` -DGTK_DISABLE_DEPRECATED -DGTK_DISABLE_SINGLE_INCLUDES -DGDK_DISABLE_DEPRECATED -DGSEAL_ENABLE $(LIBXFCEUI) $(USELIBXFCEUI)
endif

$(PROGRAM):$(SOURCES)
	g++ $(SOURCES) $(CXXFLAGS) -o $(PROGRAM)
	strip $(PROGRAM)

install:
	mkdir -p $(DESTDIR)$(PREFIX)/bin $(DESTDIR)$(PREFIX)/share/applications $(DESTDIR)$(PREFIX)/share/pixmaps $(DESTDIR)$(PREFIX)/share/man/man1
	mkdir -p $(DESTDIR)$(PREFIX)/share/man/es/man1 $(DESTDIR)$(PREFIX)/share/man/de/man1
	rm $(PROGRAM)||true
	g++ $(SOURCES) $(CXXFLAGS) -o $(PROGRAM)
	strip $(PROGRAM)
	cp -p $(PROGRAM) $(DESTDIR)$(PREFIX)/bin
	cp $(LAUNCHER) $(DESTDIR)$(PREFIX)/share/applications
	cp $(PROGRAM).png $(DESTDIR)$(PREFIX)/share/pixmaps
	gzip --stdout $(PROGRAM).1 > $(DESTDIR)$(PREFIX)/share/man/man1/$(PROGRAM).1.gz
	gzip --stdout $(PROGRAM).1.es > $(DESTDIR)$(PREFIX)/share/man/es/man1/$(PROGRAM).1.gz
	gzip --stdout $(PROGRAM).1.de > $(DESTDIR)$(PREFIX)/share/man/de/man1/$(PROGRAM).1.gz

uninstall:
	rm $(DESTDIR)$(PREFIX)/bin/$(PROGRAM) $(DESTDIR)$(PREFIX)/share/applications/$(LAUNCHER) $(DESTDIR)$(PREFIX)/share/pixmaps/$(PROGRAM).png
	rm $(DESTDIR)$(PREFIX)/share/man/de/man1/$(PROGRAM).1 $(DESTDIR)$(PREFIX)/share/man/es/man1/$(PROGRAM).1 $(DESTDIR)$(PREFIX)/share/man/man1/$(PROGRAM).1

clean:
	rm $(PROGRAM)

pkg:
	mkdir Xfce-Theme-Manager-$(VERSION)
	cp -r src $(PROGRAM).1 $(PROGRAM).1.es $(PROGRAM).1.de Xfce-Theme-Manager.desktop README README.de README.es Makefile $(PROGRAM).png ChangeLog gpl-3.0.txt Xfce-Theme-Manager-$(VERSION)
	tar --exclude .svn -cvzf Xfce-Theme-Manager-$(VERSION).tar.gz Xfce-Theme-Manager-$(VERSION)
	rm -r Xfce-Theme-Manager-$(VERSION)

version:
	sed -i "s/^#define VERSION.*/#define VERSION \"$(VERSION)\"/" src/globals.h

debug:
	g++ $(SOURCES) $(CXXFLAGS) -ggdb -O0 -o $(PROGRAM)-debug

