
# ------------------------------------------------- -----
#
# Xfce-theme-manager
#
# © 2012 K.D.Hedger
# Kdhedger@yahoo.co.uk
#
# Distribuido bajo licencia GPL, es decir hacer lo que quiera con ella
#
# ------------------------------------------------- -----

DEPENDENCIAS:

glib-2.0
gdk-2.0
cairo

****************************************************
APLICACIONES EXTERNAS (opcional):

Xfce4-Composite Editor, disponible aquí:
http://gtk-apps.org/content/show.php/Xfce4-Composite-Editor?content=149523&PHPSESSID=f9317d406c1ed0e51799fb6b6a1e3e32
****************************************************

USO:
xfce-theme-manager [m] [-u]

-m fuerza de una marca de todas las imágenes en miniatura para meta-themes/frames/controls/cursors e iconos.
-u acabamos de crear miniaturas misssing

[Restablecer Tema]
	Deseche todos los cambios.
[Tema personalizado]
	Escriba un nombre de tema personalizado para guardar/eliminar, también puede eliminar rápidamente un tema personalizado de control-clic en una miniatura del tema personalizado.

[Ficha Opciones avanzadas]
	[Acerca de]
		Créditos y esas cosas.
	[Reconstruir DB]
		Reconstruir la base de datos.
	[Xfce-Composite-Editor]
		Ejecute el editor de composit (si está instalado, ver arriba).
	[Ajustes Contexto]
		Ajuste de brillo/saturación de la imagen de fondo.
	[Disposición de los botones]
		La disposición de cerrar, maximizar, etc (algunos temas pueden overide esto).
	[Cargo]
		La colocación del título de la ventana, (algunos temas pueden overide esto).
	[Selección de Fuentes]
		Barra de título/letra de la aplicación.
	[Tamaño del cursor]
		Ajuste el tamaño del cursor si el tema de cursor que suports, algunos lo hacen y otros no.
	[Ver Opciones]
		[Mostrar Temas del sistema]
			Mostrar todo el mundo instaladas las partes del tema.
		[Mostrar sólo los temas personalizados]
			Sólo muestra los temas meta que se ha creado, los temas generados automáticamente meta no se muestran.
		[Temas]
			Mostrar todo el mundo instaladas temas meta.
		[Bordes de ventana]
			Mostrar todo el mundo instalado Xwm4 temas.
		[Control]
			Mostrar todo el mundo instala los temas Gtk.
		[Iconos]
			Mostrar todo el mundo instaladas temas de iconos.
		[Cursores]
			Mostrar todo el mundo instaladas temas de ratón.
		[Imágenes]
			Mostrar el mundo fondos de pantalla instalados.

Instalados localmente partes siempre se muestran los temas a excepción de los temas si la meta [Sólo mostrar Temas personalizados] está marcada.
Nada de lo que rápidamente se puede eliminar un tema personalizado manteniendo el control y haciendo clic en la imagen, sólo los temas personalizados que ha creado se pueden eliminar, y sólo la entrada de la base de datos se extrae de desinstalar de tu sistema.

Para instalar un tema /gtk/icono/cursor/frontera/fondo de pantalla sólo tienes que arrastrar y soltar el archivo (fondos de pantalla no se debería archivar) en cualquier lugar de la ventana principal, y si el archivo etc Posible tema será instalado en el lugar correcto, todas las instalaciones son locales , los tipos de archivo soportados son: "*. tgz", "*. gz", "* zip.", "* tar.", "* bz2.", con el apoyo tipos de fondos de pantalla son: "*. jpg", "*. png "," *. bmp "," *. gif "cualquier cosa que usted tendrá que instalar usted mismo.

Las miniaturas se almacenan en $ {HOME} / .config / XfceThemeManager.

La primera vez que utiliza Xfce-theme-manager que sea debe ejecutar desde la línea de comandos con el modificador-m o haga clic en el "DB Rebuld" el botón, la primera compilación de la base de datos puede tomar un tiempo así que tenga paciencia!

La base de datos se actualiza automáticamente en arrastrar y soltar, si usted hace un montón de añadir y removeing ​​de los temas o iconos, etc es posible que desee ejecutar Re-construcción de base de datos de la ficha Opciones avanzadas.

Temas Meta son los temas que contienen una carpeta gtk2 y una carpeta de xfwm4 (es decir, marcos de ventanas y controles), si su archivo es un theme.index con aspecto de gnomo, que también especifica un conjunto de iconos que este será utilizado también.

Español/Alemán es ahora atendidos si se ha configurado la variable "LANG" entorno adecuadamente, otras traducciones están invitados envíeme un correo electrónico a una lista para ser traducido.

INSTALACIÓN:
Extrae el archivo dicen en /tmp, cd en /tmp/Xfce-Theme-Manager-(versión), ejecutar sudo make install, este se instalará la interfaz gráfica de usuario Xfce-theme-manager, el icono y el archivo de escritorio.

La interfaz gráfica de usuario se pueden ejecutar desde la línea de comandos o desde el menú de configuración.
La interfaz gráfica de usuario puede ser instalado manualmente y / o ejecutar desde la carpeta principal.

No hay ningún script de configuración como el makefile es muy simple, por defecto es instalar en /usr/local/bin esto se puede cambiar mediante el establecimiento de la variable PREFIX antes de make install (prefix = "/usr" make install).

Si usted tiene una fuente de gestor de base como el paquete slackware los archivos para dev etc simplista ya debería estar instalado, si usted está usando una instalación basada en Debian tal vez tengas que instalar los paquetes dev, así, probablemente somthing a lo largo de las líneas de glib2-dev/gdk2-dev consulte la documentación de instalación para más detalles.

Es posible que tenga que ejecutar xfce4-panel - reiniciar para ver el menú de Xfce-theme-manager en la configuración.

Si está actualizando desde una versión anterior por favor, a reconstruir la base de datos (desde la pestaña "Avanzado").

***************************************
BUGS:
Por favor, envíelas directamente a mí en: kdhedger@yahoo.co.uk su publicación en xfce etc-mirada se vuelve demasiado complicado!
***************************************

Disfrute!

