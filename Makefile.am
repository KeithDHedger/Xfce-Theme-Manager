
SUBDIRS = Xfce-Theme-Manager/app
TRANSFORMNAME = Xfce-Theme-Manager/app/xfce-theme-manager

install-data-hook:
	chmod +x $(DESTDIR)$(pkgdatadir)/scripts/*
	
remake:
	./remakesourcelist

all-local:
	mv Xfce-Theme-Manager/app/xfcethememanager $(TRANSFORMNAME)

clean-local:
	rm $(TRANSFORMNAME)
