
.TH "XFCE-THEME-MANAGER" "1" "Nov 25, 2012" "" ""
.SH "NOMBRE"
xfce\-theme\-manager \- Un administrador de temas para Xfce
.SH "SINOPSIS"
.B xfce\-theme\-manager
.RI [\-m]
.RI [\-u]
.br 
.PP 
\-m Fuerza la creación de todas las miniaturas para meta\-temas/bordes/controles/cursores
e iconos.

\-u Sólo construye las miniaturas faltantes
.br 
.SH "DESCRIPCION"
Este manual documenta brevemente
.B xfce\-theme\-manager.
.PP 
xfce\-theme\-manager es un administrador que permite la fácil configuración de temas,
bordes de ventana, controles, icones y cursores para Xfce

.br 
.SH "OPERACION"
.PP 
Cuando xfce\-theme\-manager se inicia, el usuario puede hacer cualquiera de lo siguiente:

.B [Restablecer Tema]

Descarta todos los cambios.

.B [Personalizar Tema]

Ingresa un nombre de tema personalizado para guardar/borrar; también se puede borrar rápidamente un tema personalizado con control\-click sobre la miniatura de un tema personalizado.

.B [Pestaña Avanzado]

.B [Acerca de]

Creditos y cosas.


.B [Reconstruir DB]

Reconstruir la base de datos.

.B [Xfce\-Composite\-Editor]

Ejecuta el editor de composición (si está instalado).

Disponible aquí:

http://keithhedger.hostingsiteforfree.com/zips/Xfce4\-Composite\-Editor.tar.gz

Necesita tener gtkdialog versión 0.8.x y BASH instalado para ejecutar el Editor de Composición.

.B [Ajustes de Fondo de Escritorio]

Ajustar Brill/Saturación del fondo de pantalla.

.B [Orden de los Botones]

El orden de cerrar, maximizar, etc. (Algunos temas pueden ignorar esto).

.B [Posición del Título]

Ubicación del título de la ventana (algunos temas pueden ignorar esto).

.B [Selección de Fuentes]

Fuente de Barra de título/Aplicación.

.B [Tamaño del cursor]

Ajusta el tamaño del cursor si el tema lo permite, algunos temas no lo hacen.

.B [Opciones de Vista]

.B [Mostrar Temas del Sistema]

Muestra partes de tema instaladas globalmente.

.B [Mostrar Sólo Temas Personalizados]

Muestra sólo metatemas que usted haya creado, los metatemas automáticamente
no son mostrados.

.B [Temas]

Muestra metatemas instalados globalmente.

.B [Bordes de Ventana]

Muestra temas Xfwm4 instalados globalmente.

.B [Controles]

Muestra temas de controles instalados globalmente.

.B [Iconos]

Muestra temas de iconos instalados globalmente.

.B [Cursores]

Muestra temas de cursotes instalados globalmente.

.B [Fondos de pantalla]

Muestra fondos de pantalla.

Las partes de temas instaladas localmente siempre se muestran, excepto por los meta temas si [Mostrar Sólo Temas Personalizados] está marcado.

Se puede eliminar rápidamente un tema personalizado presionando Control y haciendo click sobre la miniatura; sólo los temas personalizados que haya creado pueden borrarse, y sólo la entrada en la base de datos es borrada, nada se desintala de su sistema.

Para instalar un tema/gtk/icono/cursor/borde/fondo de pantalla, sólo arrastre y suelte el archivo (los fondos no debieran estar comprimidos) en cualquier parte de la ventana principal, y si es posible el tema, etc, será instalado en el lugar correcto; todas las instalaciones son locales. Los tipos soportados de archivo son: "*.tgz","*.gz","*.zip","*.tar","*.bz2"; los tipos de fondo soportados son: "*.jpg","*.png","*.bmp","*.gif", cualquier otro tendrá que instalarlo usted mismo.

Las miniaturas son almacenadas en ${HOME}/.config/XfceThemeManager.

La primera vez que use Xfce\-Theme\-Manager debiera ejecutarlo desde la línea de comando con el modificador \-m, o usar el botón "Reconstruir DB". La primera construcción de la base de datos puede llevar un tiempo.

La base de datos es actualizada automáticamente al arrastrar y soltar. Si usted instala y elimina muchos temas/iconos, etc, puede querer ejecutar Reconstruir DB de la pestaña Avanzado.

Metatemas son temas que contienen una carpeta gtk2 y una xfwm4 (controles y borde de ventana); si es un tema de Gnome puede haber también un archivo theme.index que además especifique el tema de iconos que usará.
.br 
.SH "AUTOR"
xfce\-theme\-manager fue escrito por Keith Hedger
.PP 
Esta página de manual fue escrita por Eduardo Echeverria <echevemaster@gmail.com>,
para el Proyecto Fedora (y puede ser usado por otros), arreglada por Keith Hedger, traducida por Pablo Morales Romero <pg.morales.romero@gmail.com> (Español), Martin F. Schumann. <mfs@mfs.name> (Alemán)

