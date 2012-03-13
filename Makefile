PROGRAM=xfce-theme-manager
PREFIX=/usr/local
LAUNCHER=xfce-theme-manager.desktop

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

clean:
	rm -f $(PROGRAM)

pkg:
	rm -f $(PROGRAM)
	sed '/###MAIN###/r main.inc'  Xfce-Theme-Manager.main|sed 's/###[[:alpha:]]*###//' > $(PROGRAM)
	chmod +x $(PROGRAM)
	tar -cvzf Xfce-Theme-Manager.tar.gz xfce-theme-manager xfce-theme-manager.desktop README
