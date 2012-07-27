
# ------------------------------------------------- -----
#
# Xfce-theme-manager
#
# © 2012 K.D.Hedger
# Kdhedger@yahoo.co.uk
#
# Distribuido bajo licencia GPL, es decir, puede hacer lo que quiera con ella
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

Para instalar un tema/gtk/icono/cursor/borde/fondo de pantalla sólo tienes que arrastrar y soltar el archivo (los fondos de pantalla no deberían estar dentro de un archivo) en cualquier lugar de la ventana principal, y si es posible, el archivo  de tema, etc, será instalado en el lugar correcto; todas las instalaciones son locales, los tipos de archivo soportados son: "*.tgz", "*.gz", "*.zip.", "*.tar.", "*.bz2."; los tipos de fondos de pantalla soportados son: "*.jpg", "*.png "," *.bmp "," *.gif ". Cualquier otra cosa tendrá que instalarla usted mismo.

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

Si usted tiene un gestor de paquetes basado en fuentes, como slackware, los archivos dev para glib, etc, ya deberían estar instalados. Si usted está usando una instalación basada en Debian tal vez tenga que instalar los paquetes dev, probablemente algo a lo largo de las líneas de glib2-dev/gdk2-dev. Consulte la documentación de instalación para más detalles.

Es posible que tenga que ejecutar xfce4-panel --restart para ver el menú de Xfce-theme-manager en la configuración.

Si está actualizando desde una versión anterior por favor, reconstruya la base de datos (desde la pestaña "Avanzado").

***************************************
BUGS:
Por favor, envíelas directamente a mí en: kdhedger@yahoo.co.uk Su publicación en xfce-look, etc, se vuelve demasiado complicada!
***************************************

Cambios:

0.1.14 Se agregó diálogo "Acerca de".
	Añadidas opciones de visualización en "Opciones avanzadas"
	Añadido CNTRL-clic en el tema personalizado para eliminar.

0.1.13 Lanzamiento interno.

0.1.12 Corrección de errores/hack para xfwm4-settings defectuoso.

0.1.11 Corrección de errores de variables LANG del entorno mal formado/inexistente .
	Corrección de errores de la versión preliminar del cursor.
	Taponadas algunas pérdidas de memoria.
	Ordenado el diálogo de la reconstrucción de base de datos (eliminado el botón de cierre, etc).
	Cambios menores a Makefile/README.

0.1.10 Añadida traducción al alemán, gracias a Martin F. Schumann por ello.
	Eliminadas advertencias de xconf acerca de la configuración de usuario no establecida.
	Añadido "Personalizar" al guardar tema personalizado si es necesario.
	Corregida pérdida menor de memoria.
	Nuevo icono de la aplicación.
	Corrección menor de errores utilizando coma en lugar de punto (¡otra vez!)
	Limpieza de código.

0.1.9 Lanzamiento interno.

0.1.8 Finalmente rehecha la vista previa de los bordes, para utilizar mosaico en vez de estirado, más preciso.
	Añadido icono de aplicación.
	Cambiado 'Guardar tema' al botón 'Personalizar Tema' para ahora añadir/eliminar temas personalizados.

0.1.7 README actualizado.
	Se ignoran sub-carpetas incluidas en las carpetas de Fondo de escritorio, de acuerdo con Xfce GUI.
	Agregada solución para comas en lugar de puntos en deslizadores.
	Añadida traducción al español (gracias a Pablo Morales Romero, por su ayuda)
	Corrección de errores por temas de xfwm4 malformados.
	Eliminada salida anormal en cursores sin pixmaps.

0.1.6 corrección de errores privada.

0.1.5 Re-añadido tamaño del cursor en avanzado.
	'Restablecer temas' ahora restablece los controles en la pestaña de avanzado.
	Añadido 'Guardar tema', ahora guarda temas personalizados completos.
	Movido "Reconstruir BD" a pestaña Avanzado.
	Brillo/Saturación ahora sólo se actualizan al soltar el botón.

0.1.4 ahora debería ser compatible con gtk3.
	Eliminado el botón manual de "actualización de base de datos" debido a que la actualización es ahora automática.
	La primera versión de código completamente reescrito en 'c' principalmente para mejoras de velocidad.
	Ordenar por orden alfabético y el usuario primero y luego el sistema.
	Actualización automática de base de datos tras la instalación correcta del tema, etc
	Arrastrar y soltar para la instalación completa de los temas, iconos, fondos de escritorio, etc 
	Página Avanzado reordenada.
	Botones Fuentes mostrar el nombre de la fuente en el estilo de fuente.
	Multi-threaded barra de progreso.

0.1.3 versiones privadas.
0.0.9

0.0.8 aplicación auxiliar ajustada para mostrar superposiciones de representación correctamente en las vistas previas.
	Añadido el tamaño del cursor, posición del título y la disposición de los botones a Avanzado.
	Añadido botón 'Instalar tema/Wallpaper' a avanzado.
	Añadido selección fuente de WM/aplicación en GUI y aplicación auxiliar.
	Movido el brillo de la ventana / la saturación de avanzada.
	Añadido lanzador "Xfce4-Composite-editor en avanzado.
	Añadida opción "Advanzado".

0.0.7 Se agregó una sección Fondos.
	Sometido a pruebas en Xfce 4.10.
	Añade propiedades a xconf si no están definidas.
	Actualiza escritorio Xfce al cambiar los iconos.
	Ajustado el Makefile para considerar las burlas de Fedora con el enlazador!

0.0.6 temas de iconos ahora a cargo de aplicación auxiliar, es de esperar no más iconos "desaparecidos" de la interfaz gráfica de usuario.
	Meta-Temas incluyen ahora icono 'Home' y puntero 'izquierda' en la vista previa.
	Tamaño de las vistas previas de meta-temas ahora más consistente.
	Corrección de numerosos errores menores.

0.0.5 Añadida vista previa de personalizado.
	Corrección de numerosos errores para temas mal formados.
	Limpieza de código.

0.0.4b Se ha corregido un error donde imagemagick traga a stdin
	Añadida pestaña tema del Cursor.
	Añadida vista previa del cursor en aplicación auxiliar.
	Corregido otro error de "espacios de nombre de archivo"

0.0.03b Ahora se soporta una gran cantidad de temas, >200.
	Se han solucionado algunos errores con los temas con espacios en sus nombres.

0.0.2b Re-escribió aplicación auxiliar para crear miniaturas de bordes de ventanas
0.0.1b primera liberación al medio salvaje

Disfrute!

