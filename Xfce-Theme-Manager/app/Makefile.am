AUTOMAKE_OPTIONS = subdir-objects
include ../flagsandlibs
include ../sources

TRANSFORMNAME = xfce-theme-manager
NAME = Xfce-Theme-Manager

xfcethememanager_SOURCES = $(COMMONSRC)

docfilesdir = $(pkgdatadir)/docs
docfiles_DATA = ../resources/docs/*

scriptfilesdir = $(pkgdatadir)/scripts
scriptfiles_DATA = ../resources/scripts/*

bin_PROGRAMS = xfcethememanager
 
install-exec-hook:
	mv $(DESTDIR)${bindir}/xfcethememanager $(DESTDIR)${bindir}/$(TRANSFORMNAME)
	mkdir -p $(DESTDIR)${prefix}/share/man/man1 $(DESTDIR)${prefix}/share/man/de/man1 $(DESTDIR)${prefix}/share/man/es/man1 $(DESTDIR)${prefix}/share/man/pl/man1 $(DESTDIR)${prefix}/share/man/fr/man1

	mkdir -p $(DESTDIR)${datadir}/applications $(DESTDIR)${datadir}/pixmaps

	gzip --stdout ../resources/man/$(TRANSFORMNAME).1 > $(DESTDIR)${prefix}/share/man/man1/$(TRANSFORMNAME).1.gz
	gzip --stdout ../resources/man/$(TRANSFORMNAME).1.es > $(DESTDIR)${prefix}/share/man/es/man1/$(TRANSFORMNAME).1.gz
	gzip --stdout ../resources/man/$(TRANSFORMNAME).1.de > $(DESTDIR)${prefix}/share/man/de/man1/$(TRANSFORMNAME).1.gz
	gzip --stdout ../resources/man/$(TRANSFORMNAME).1.pl > $(DESTDIR)${prefix}/share/man/pl/man1/$(TRANSFORMNAME).1.gz
	gzip --stdout ../resources/man/$(TRANSFORMNAME).1.fr > $(DESTDIR)${prefix}/share/man/fr/man1/$(TRANSFORMNAME).1.gz

	cp ../resources/pixmaps/$(NAME).desktop $(DESTDIR)${datadir}/applications/
	cp ../resources/pixmaps/$(TRANSFORMNAME).png $(DESTDIR)${datadir}/pixmaps/

uninstall-hook:
	rm $(DESTDIR)$(prefix)/share/man/man1/$(TRANSFORMNAME).1.gz $(DESTDIR)$(prefix)/share/man/es/man1/$(TRANSFORMNAME).1.gz $(DESTDIR)$(prefix)/share/man/de/man1/$(TRANSFORMNAME).1.gz $(DESTDIR)$(prefix)/share/man/pl/man1/$(TRANSFORMNAME).1.gz $(DESTDIR)$(prefix)/share/man/fr/man1/$(TRANSFORMNAME).1.gz
	rm $(DESTDIR)${datadir}/applications/$(NAME).desktop $(DESTDIR)${datadir}/pixmaps/$(TRANSFORMNAME).png
	rm -r $(DESTDIR)$(pkgdatadir)
	rm $(DESTDIR)/${bindir}/$(TRANSFORMNAME)


