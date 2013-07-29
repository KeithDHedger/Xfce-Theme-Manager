

Xfce-Theme-Manager Installation Instructions.


Source based distros (slackware etc):
./configure --prefix=/usr
make
sudo make install --prefix=/usr

Or if you have autotools installed:
./autogen.sh
make
sudo make install

Add --prefix=/usr etc to change the default installation from /usr/local

******************

Debian install.

sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install glib-2.0-dev libgtk2.0-dev libxfce4ui-1-dev

./configure --prefix=/usr
make
sudo make install

Debian install using autotools.

sudo apt-get install automake
sudo apt-get install autotools-dev
sudo apt-get install aclocal autoheader autoconf

./autogen.sh --prefix=/usr
make
sudo make install

*********************

Fedora 16 Install
sudo yum update kernel*
sudo yum install gcc-c++ glib2-devel gtk2-devel libxfce4ui-devel xfconf-devel gcc

Fedora Install using autotools.
The above +
sudo yum install automake autoconf

./autogen.sh --prefix=/usr
make
sudo make install
