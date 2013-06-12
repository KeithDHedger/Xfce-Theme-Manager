
include ../flagsandlibs
include ../sources

TRANSFORMNAME = xfce-theme-manager
NAME = Xfce-Theme-Manager

xfcethememanager_SOURCES = $(COMMONSRC)

xfcethememanager_CFLAGS = -O3 -export-dynamic
xfcethememanager_CXXFLAGS = -O3 -export-dynamic

#pixfilesdir = $(pkgdatadir)/pixmaps
#pixfiles_DATA = ../resources/pixmaps/*.png
#
#scriptfilesdir = $(pkgdatadir)/scripts
#scriptfiles_SCRIPTS = ../resources/scripts/README
#

docfilesdir = $(pkgdatadir)/docs
docfiles_DATA = ../resources/docs/*

bin_PROGRAMS = xfcethememanager
all-local:
	mv xfcethememanager $(TRANSFORMNAME)

clean-local:
	rm $(TRANSFORMNAME)

#man1_MANS = ../resources/man/xfce-theme-manager.1
#de_man1_MANS = ../resources/man/xfce-theme-manager.1.de

#
install-exec-hook:
	mv $(DESTDIR)${bindir}/xfcethememanager $(DESTDIR)${bindir}/$(TRANSFORMNAME)
	mkdir -p $(DESTDIR)${prefix}/share/man/man1 $(DESTDIR)${prefix}/share/man/de/man1 $(DESTDIR)${prefix}/share/man/es/man1
	mkdir -p $(DESTDIR)${datadir}/applications $(DESTDIR)${datadir}/pixmaps

	gzip --stdout ../resources/man/$(TRANSFORMNAME).1 > $(DESTDIR)${prefix}/share/man/man1/$(TRANSFORMNAME).1.gz
	gzip --stdout ../resources/man/$(TRANSFORMNAME).1.es > $(DESTDIR)${prefix}/share/man/es/man1/$(TRANSFORMNAME).1.gz
	gzip --stdout ../resources/man/$(TRANSFORMNAME).1.de > $(DESTDIR)${prefix}/share/man/de/man1/$(TRANSFORMNAME).1.gz

	cp ../resources/pixmaps/$(NAME).desktop $(DESTDIR)${datadir}/applications/
	cp ../resources/pixmaps/$(TRANSFORMNAME).png $(DESTDIR)${datadir}/pixmaps/
#echo Icon=${pkgdatadir}/pixmaps/$(TRANSFORMNAME).png >> $(DESTDIR)${datadir}/applications/$(NAME).desktop

#	echo Icon=${prefix}/share/$(PACKAGE)/pixmaps/$(TRANSFORMNAME).png >> $(DESTDIR)${prefix}/share/applications/$(PACKAGE).desktop
#	echo Exec=${prefix}/bin/dvdripper >> ${prefix}/share/applications/DVDRipper.desktop

#	cp ../resources/pixmaps/DVDRipper.desktop ${prefix}/share/applications/DVDRipper.desktop
#	echo Icon=${prefix}/share/DVDRipper/pixmaps/DVDRipper.png >> ${prefix}/share/applications/DVDRipper.desktop
#	echo Exec=${prefix}/bin/dvdripper >> ${prefix}/share/applications/DVDRipper.desktop
#
#
uninstall-hook:
	rm $(DESTDIR)$(PREFIX)/share/man/man1/$(TRANSFORMNAME).1.gz $(DESTDIR)$(PREFIX)/share/man/es/man1/$(TRANSFORMNAME).1.gz $(DESTDIR)$(PREFIX)/share/man/de/man1/$(TRANSFORMNAME).1.gz
	rm $(TRANSFORMNAME)
#	rm -f ${prefix}/share/applications/DVDRipper.desktop ${prefix}/share/pixmaps/CDRipper.png
#	rm -fr $(pkgdatadir)

