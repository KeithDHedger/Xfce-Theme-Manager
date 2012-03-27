PROGRAM=xfce-theme-manager
PREFIX=/usr/local
LAUNCHER=Xfce-Theme-Manager.desktop
VERSION=0.0.5

all:
	rm -f $(PROGRAM)
	sed '/###MAIN###/r main.inc' Xfce-Theme-Manager.main|sed 's/###[[:alpha:]]*###//' > $(PROGRAM)
	chmod +x $(PROGRAM)

install:
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	rm -f $(PROGRAM)
	sed '/###MAIN###/r main.inc'  Xfce-Theme-Manager.main|sed 's/###[[:alpha:]]*###//' > $(PROGRAM)
	chmod +x $(PROGRAM)
	cp $(PROGRAM) $(DESTDIR)$(PREFIX)/bin/$(PROGRAM)
	cp $(LAUNCHER) $(DESTDIR)$(PREFIX)/share/applications

uninstall:
	rm $(DESTDIR)$(PREFIX)/bin/$(PROGRAM)
	rm $(DESTDIR)$(PREFIX)/share/applications/$(LAUNCHER)
	rm $(DESTDIR)$(PREFIX)/bin/gtkprev
clean:
	rm -f $(PROGRAM)

pkg:
	rm -f $(PROGRAM)
	sed '/###MAIN###/r main.inc'  Xfce-Theme-Manager.main|sed 's/###[[:alpha:]]*###//' > $(PROGRAM)
	chmod +x $(PROGRAM)
	tar --exclude .svn --exclude gtkprev -cvzf Xfce-Theme-Manager-$(VERSION).tar.gz xfce-theme-manager Xfce-Theme-Manager.desktop gtkpreview README

slackpkg:
	cd slackbuild
	tar --exclude .svn -cvzf Xfce-Theme-Manager.tar.gz Xfce-Theme-Manager
