.TH "XFCE-THEME-MANAGER" "1" "0.3.0" "K.D.Hedger" ""

.SH NOMBRE
xfce-theme-manager - Un administrador de temas para Xfce
.SH "SINOPSIS"
.B xfce-theme-manager
[opción.1] ... [opción.2]
.br 
.SH "DESCRIPCION"
Este manual documenta brevemente
.B xfce-theme-manager.
.br 
xfce-theme-manager es un administrador que permite la fácil configuración de temas,
bordes de ventana, controles, iconos y cursores, etc, para Xfce.
.SH "OPERACION"
Cuando xfce-theme-manager se inicia, el usuario puede hacer cualquiera de lo siguiente:
.br

.B [Restablecer Tema]
.br
Descarta todos los cambios.
.br

.B [Personalizar Tema]
.br
Ingresa un nombre de tema personalizado para guardar/borrar; también se puede borrar rápidamente un tema personalizado con control-click sobre la miniatura de un tema personalizado.
.br

.B [Acerca de]
.br
Créditos y cosas.
.br

.B [Pestaña Avanzado]
.br



.B [Reconstruir DB]
.br
Reconstruir la base de datos.
.br

.B [Xfce-Composite-Editor]
.br
Ejecuta el editor de composición (si está instalado).
.br
Disponible aquí:
.br
http://keithhedger.hostingsiteforfree.com/zips/Xfce4-Composite-Editor.tar.gz
.br
Necesita tener gtkdialog versión 0.8.x y BASH instalado para ejecutar el Editor de Composición.
.br

.B [Ajustes de Fondo de Escritorio]
.br
Ajustar Brillo/Saturación del fondo de pantalla.
.br

.B [Orden de los Botones]
.br
El orden de cerrar, maximizar, etc. (Algunos temas pueden ignorar esto).
.br

.B [Posición del Título]
.br
Ubicación del título de la ventana (algunos temas pueden ignorar esto).
.br

.B [Selección de Fuentes]
.br
Fuente de Barra de título/Aplicación.
.br

.B [Tamaño del cursor]
.br
Ajusta el tamaño del cursor si el tema lo permite, algunos temas no lo hacen.
.br

.B [Opciones de Vista]
.br
.B [Mostrar Temas del Sistema]
.br
Muestra partes de tema instaladas globalmente.
.br

.B [Mostrar Sólo Temas Personalizados]
.br
Muestra sólo metatemas que usted haya creado, los metatemas generados automáticamente
no son mostrados.

.B [Temas]
.br
Muestra metatemas instalados globalmente.
.br

.B [Bordes de Ventana]
.br
Muestra temas Xfwm4 instalados globalmente.
.br

.B [Controles]
.br
Muestra temas de controles Gtk instalados globalmente.
.br

.B [Iconos]
.br
Muestra temas de iconos instalados globalmente.
.br

.B [Cursores]
.br
Muestra temas de cursotes instalados globalmente.
.br

.B [Fondos de pantalla]
.br
Muestra fondos de pantalla instalados globalmente.
.br

Las partes de temas instaladas localmente siempre se muestran, excepto por los meta temas si 
.B [Mostrar Sólo Temas Personalizados]
está marcado.
.br
Se puede eliminar rápidamente un tema personalizado presionando Control y haciendo click sobre la miniatura; sólo los temas personalizados que haya creado pueden borrarse, y sólo la entrada en la base de datos es borrada, nada se desintala de su sistema.
.br
Para instalar un tema/gtk/icono/cursor/borde/fondo de pantalla, sólo arrastre y suelte el archivo (los fondos no debieran estar comprimidos) en cualquier parte de la ventana principal, y si es posible el tema, etc, será instalado en el lugar correcto; todas las instalaciones son locales. Los tipos soportados de archivo son: "*.tgz","*.gz","*.zip","*.tar","*.bz2"; los tipos de fondo soportados son: "*.jpg","*.png","*.bmp","*.gif", cualquier otro tendrá que instalarlo usted mismo.
.br

Debe tener instalado unzip para arrastrar y soltar archivos.
.br

Las miniaturas son almacenadas en ${HOME}/.config/XfceThemeManager.
.br

La base de datos es actualizada automáticamente al arrastrar y soltar. Si usted instala y elimina muchos temas/iconos, etc, puede querer ejecutar Reconstruir DB de la pestaña Avanzado.
.br

Metatemas son temas que contienen una carpeta gtk2 y una xfwm4 (controles y borde de ventana); si es un tema de Gnome puede haber también un archivo theme.index que además especifique el tema de iconos que usará.
.br
.SH COMMAND LINE OPTIONS
-v, --version
.br
	Imprime información de la versión y sale.
.br

-u, --update-db
.br
	Actualiza la base de datos.
.br

-r, --build-db
.br
	Reconstruye la base de datos.
.br

-n, --nogui
.br
	No ejecuta la GUI.
.br

-t, --theme=ARG
.br
	Ajusta el metatema a ARG.
.br

-c, --controls=ARG
.br
	Ajusta el tema de controles a ARG.
.br

-w, --wmborder=ARG
.br
	Ajusta el tema de ventana a ARG.
.br

-i, --icons=ARG
.br
	Ajusta el tema de iconos a ARG.
.br

-p, --cursors=ARG
.br
	Ajusta el tema de cursor a ARG.
.br

-b, --backdrop=ARG
.br
	Ajusta el fondo de escritorio a ARG.
.br

-l, --list=ARG
.br
	Lista de las entradas de la base de datos, donde ARG = cualquiera de "*Ctwcib".
.br

	Donde 'C' imprime temas personalizados, 't' imprime temas, 'w' imprime bordes de pantalla, 'c' imprime controles, 'i' imprime iconos, y 'b' imprime fondos.
	Si el primer/único caracter es un '*', entonces todas las entradas son impresas.
.br

-?, --help
.br
	Imprime ayuda.
.br

Opciones tcwipblvh? todas implican -n.
.br 
.SH "AUTOR"
.B Xfce-Theme-Manager
xfce-theme-manager fue escrito por Keith Hedger

Esta página de manual fue escrita por Eduardo Echeverria <echevemaster@gmail.com>,
para el Proyecto Fedora (y puede ser usado por otros), arreglada por Keith Hedger, traducida por Pablo Morales Romero <pg.morales.romero@gmail.com> (Español), Martin F. Schumann. <mfs@mfs.name> (Alemán)

