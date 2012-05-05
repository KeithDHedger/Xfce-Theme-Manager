PROGRAM=xfce-theme-manager
SOURCES=src/main.cpp src/globals.cpp src/database.cpp src/thumbnails.cpp src/gui.cpp src/callbacks.cpp
VERSION=0.1.7
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
	mkdir -p $(DESTDIR)$(PREFIX)/bin $(DESTDIR)$(PREFIX)/share/applications
	rm $(PROGRAM)||true
	g++ $(CXXFLAGS) -o $(PROGRAM) $(SOURCES)
	strip $(PROGRAM)
	cp -p $(PROGRAM) $(DESTDIR)$(PREFIX)/bin
	cp $(LAUNCHER) $(DESTDIR)$(PREFIX)/share/applications

uninstall:
	rm $(DESTDIR)$(PREFIX)/bin/$(PROGRAM) $(DESTDIR)$(PREFIX)/share/applications/$(LAUNCHER)

clean:
	rm $(PROGRAM)

pkg:
	tar --exclude .svn -cvzf Xfce-Theme-Manager-$(VERSION).tar.gz src Xfce-Theme-Manager.desktop README Makefile

