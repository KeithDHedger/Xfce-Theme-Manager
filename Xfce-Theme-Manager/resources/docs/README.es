# ------------------------------------------------- -----
#
#   Xfce-theme-manager
#
#   © 2013 K.D.Hedger
#   kdhedger68713@gmail.com
#
#   Distribuido bajo licencia GPL. Ver el archivo de licencia incluido (gpl-3.0.txt)
#   Traducciones de la licencia pueden encontrarse aquí:
#   http://www.gnu.org/licenses/translations.html
# ------------------------------------------------- -----

DEPENDENCIAS:

glib-2.0
gdk-2.0
cairo
gtk+-2.0

unzip - dependencia en tiempo de ejecución para arrastrar y soltar archivos zip.

****************************************************
APLICACIONES EXTERNAS (opcional):

Xfce4-Composite Editor, disponible aquí:
http://gtk-apps.org/content/show.php/Xfce4-Composite-Editor?content=149523&PHPSESSID=f9317d406c1ed0e51799fb6b6a1e3e32
****************************************************

USO:
xfce-theme-manager [-m] [-u]

-m fuerza la creación de todas las imágenes en miniatura para meta-temas/bordes/controles/cursores e iconos.
-u crea miniaturas perdidas

[Restablecer Tema]
	Desecha todos los cambios.
[Tema personalizado]
	Escriba un nombre de tema personalizado para guardar/eliminar, también puede eliminar rápidamente un tema personalizado haciendo control-clic en una miniatura del tema personalizado.

[Pestaña Opciones avanzadas]
	[Acerca de]
		Créditos y esas cosas.
	[Reconstruir DB]
		Reconstruir la base de datos.
	[Xfce-Composite-Editor]
		Ejecute el editor de composición (si está instalado, ver arriba).
	[Ajustes Fondo]
		Ajuste de brillo/saturación de la imagen de fondo.
	[Disposición de los botones]
		La disposición de cerrar, maximizar, etc (algunos temas pueden ignorar esto).
	[Podición del Título]
		La colocación del título de la ventana, (algunos temas pueden ignorar esto).
	[Selección de Fuentes]
		Fuente de la Barra de título/aplicación.
	[Tamaño del cursor]
		Ajuste el tamaño del cursor si el tema de cursor lo soporta, algunos lo hacen y otros no.
	[Ver Opciones]
		[Mostrar Temas del Sistema]
			Mostrar partes de temas instalados a nivel de sistema.
		[Mostrar Sólo Temas personalizados]
			Sólo muestra los temas meta que se han creado, los temas meta generados automáticamente no se muestran.
		[Temas]
			Mostrar temas meta instalados en el sistema.
		[Bordes de ventana]
			Mostrar temas Xfwm4 instalados en el sistema.
		[Control]
			Mostrar temas Gtk instalados en el sistema.
		[Iconos]
			Mostrar temas de iconos instalados en el sistema.
		[Cursores]
			Mostrar temas de cursor instalados en el sistema.
		[Imágenes]
			Mostrar los fondos de pantalla instalados en el sistema.

Las partes de tema instaladas localmente siempre se muestran, a excepción de los temas meta si está marcada [Mostrar Sólo Temas Personalizados].
Rápidamente se puede eliminar un tema personalizado presionando la tecla control y haciendo clic en la imagen; sólo los temas personalizados que ha creado se pueden eliminar, y sólo la entrada de la base de datos es eliminada, nada se desinstala de su sistema.

Para instalar un tema/gtk/icono/cursor/borde/fondo de pantalla sólo tienes que arrastrar y soltar el archivo (los fondos de pantalla no deberían estar dentro de un archivo) en cualquier lugar de la ventana principal, y si es posible, el archivo  de tema, etc, será instalado en el lugar correcto; todas las instalaciones son locales, los tipos de archivo soportados son: "*.tgz", "*.gz", "*.zip.", "*.tar.", "*.bz2."; los tipos de fondos de pantalla soportados son: "*.jpg", "*.png"," *.bmp"," *.gif". Cualquier otra cosa tendrá que instalarla usted mismo.

Las miniaturas se almacenan en ${HOME}/.config/XfceThemeManager.

La primera vez que utiliza Xfce-theme-manager debe ejecutarlo desde la línea de comandos con el modificador -m, o hacer clic en el botón "Reconstruir DB". La primera compilación de la base de datos puede tomar un tiempo así que ¡tenga paciencia!

La base de datos se actualiza automáticamente al arrastrar y soltar; si usted hace un montón de añadir y eliminar ​​de los temas o iconos, etc, es posible que desee ejecutar Re-Construir La Base De Datos de la pestaña Avanzado.

Temas Meta son los temas que contienen una carpeta gtk2 y una carpeta de xfwm4 (es decir, controles y bordes de ventanas); si su archivo es un theme.index como en Gnome, que también especifica un conjunto de iconos, éste será utilizado también.

Español/Alemán son ahora atendidos si se ha configurado la variable "LANG" del entorno adecuadamente. Otras traducciones son bienvenidas, envíeme un correo electrónico para una lista de traducción.

INSTALACIÓN:
Extraer el archivo, digamos en /tmp; cd a /tmp/Xfce-Theme-Manager-(VERSION); ejecutar sudo make install. Esto instalará la interfaz gráfica de usuario Xfce-theme-manager, el icono y el archivo de menú.

La interfaz gráfica de usuario se puede ejecutar desde la línea de comandos o desde el menú de configuración.
La interfaz gráfica de usuario puede ser instalada manualmente y/o ejecutada desde la carpeta principal.

No hay ningún script de configuración ya que el makefile es muy simple. Por defecto se instala en /usr/local/bin; esto se puede cambiar mediante el establecimiento de la variable PREFIX antes de make install (PREFIX="/usr" make install).

Si usted tiene un gestor de paquetes basado en fuentes, como slackware, los archivos dev para glib, etc, ya deberían estar instalados. Si usted está usando una instalación basada en Debian tal vez tenga que instalar los paquetes dev también. Desde una terminal, para un sistema limpio, escriba:

sudo apt-get update
sudo apt-get install build-essential glib-2.0-dev libgtk2.0-dev libxfce4ui-1-dev

Revise su documentación de instalación para más detalles, pero esto funciona sobre una versión limpia de Xubuntu-12.10. Otras distribuciones basadas en Debian debieran funcionar igual.
Quizás deba acceder a xfce-theme-manager por medio del Administrador de Configuración en el Menú Principal.

Es posible que tenga que ejecutar xfce4-panel --restart para ver el menú de Xfce-theme-manager en la configuración.

Si está actualizando desde una versión anterior por favor, reconstruya la base de datos (desde la pestaña "Avanzado").

***************************************
BUGS:
Por favor, envíelas directamente a mí en: kdhedger68713@gmail.com Su publicación en xfce-look, etc, se vuelve demasiado complicada!
***************************************

Disfrute!

