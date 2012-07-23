PROGRAM=xfce-theme-manager
SOURCES=src/main.cpp src/globals.cpp src/database.cpp src/thumbnails.cpp src/gui.cpp src/callbacks.cpp
VERSION=0.1.13

LAUNCHER=Xfce-Theme-Manager.desktop

ifeq ($(strip $(PREFIX)),)
	PREFIX=/usr/local
endif

ifeq ($(strip $(CXXFLAGS)),)
	CXXFLAGS=-O3 -Wall -Wunused -Wunused-function -lXcursor `pkg-config --cflags --libs glib-2.0` `pkg-config --cflags --libs gdk-2.0` `pkg-config --cflags --libs gtk+-2.0` -DGTK_DISABLE_DEPRECATED -DGTK_DISABLE_SINGLE_INCLUDES -DGDK_DISABLE_DEPRECATED -DGSEAL_ENABLE
endif

$(PROGRAM):$(SOURCES)
	g++ $(CXXFLAGS) -o $(PROGRAM) $(SOURCES)
	strip $(PROGRAM)

install:
	mkdir -p $(DESTDIR)$(PREFIX)/bin $(DESTDIR)$(PREFIX)/share/applications $(DESTDIR)$(PREFIX)/share/pixmaps
	rm $(PROGRAM)||true
	g++ $(CXXFLAGS) -o $(PROGRAM) $(SOURCES)
	strip $(PROGRAM)
	cp -p $(PROGRAM) $(DESTDIR)$(PREFIX)/bin
	cp $(LAUNCHER) $(DESTDIR)$(PREFIX)/share/applications
	cp $(PROGRAM).png $(DESTDIR)$(PREFIX)/share/pixmaps

uninstall:
	rm $(DESTDIR)$(PREFIX)/bin/$(PROGRAM) $(DESTDIR)$(PREFIX)/share/applications/$(LAUNCHER) $(DESTDIR)$(PREFIX)/share/pixmaps/$(PROGRAM).png

clean:
	rm $(PROGRAM)

pkg:
	mkdir Xfce-Theme-Manager-$(VERSION)
	cp -r src Xfce-Theme-Manager.desktop README Makefile $(PROGRAM).png Xfce-Theme-Manager-$(VERSION)
	tar --exclude .svn -cvzf Xfce-Theme-Manager-$(VERSION).tar.gz Xfce-Theme-Manager-$(VERSION)
	rm -r Xfce-Theme-Manager-$(VERSION)


