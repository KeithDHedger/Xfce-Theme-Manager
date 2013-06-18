
SUBDIRS = Xfce-Theme-Manager/app

remake:
	$(shell ./remakesourcelist)

makepkg:
	svn commit -m ""
	(
	mkdir /tmp/xfm
	cd /tmp/xfm
	svn co file:///media/LinuxData/Development/SVN/Xfce-Theme-Manager
	echo $(VERSION)
	)
