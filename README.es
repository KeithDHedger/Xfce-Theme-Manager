
#------------------------------------------------------ # ------------------------------------------------- -----
# #
#   Xfce-Theme-Manager # Xfce-theme-manager
# #
#   ©K.D.Hedger 2012 # © 2012 K.D.Hedger
#   kdhedger@yahoo.co.uk # Kdhedger@yahoo.co.uk
# #
#   Released under GPL ie do what you want with it # Distribuido bajo licencia GPL, es decir hacer lo que quiera con ella
# #
#------------------------------------------------------ # ------------------------------------------------- -----

DEPENDENCIES: Dependencias:

glib-2.0 glib-2.0
gdk-2.0 GDK-2.0
cairo El Cairo

**************************************************** ************************************************** **
EXTERNAL APPS (Optional): Aplicaciones externas (opcional):

Xfce4-Composite-Editor Available here: Xfce4-Composite Editor, disponible aquí:

**************************************************** ************************************************** **

USAGE: USO:
xfce-theme-manager [-m] [-u] xfce-theme-manager [m] [-u]

-m force a make of all the thumbnails for meta-themes/frames/controls/cursors and icons. -M fuerza de una marca de todas las imágenes en miniatura para meta-themes/frames/controls/cursors e iconos.
-u just build misssing thumbnails -U acabamos de crear miniaturas misssing

To install a theme/gtk/icon/cursor/border/wallpaper just drag and drop the archive ( wallpapers should not be archived ) anywhere on the main window and if posible the theme etc will be installed into the correct place, all installations are local, supported archive types are:"*.tgz","*.gz","*.zip","*.tar","*.bz2", supported wallpaper types are:"*.jpg","*.png","*.bmp","*.gif" anything else you will have to install yourself. Para instalar un tema / gtk / icono / cursor / frontera / fondo de pantalla sólo tienes que arrastrar y soltar el archivo (fondos de pantalla no se debería archivar) en cualquier lugar de la ventana principal, y si el archivo etc Posible tema será instalado en el lugar correcto, todas las instalaciones son locales , los tipos de archivo soportados son: "*. tgz", "*. gz", "* zip.", "* tar.", "* bz2.", con el apoyo tipos de fondos de pantalla son: "*. jpg", "*. png "," *. bmp "," *. gif "cualquier cosa que usted tendrá que instalar usted mismo.

The thumbnails are stored in ${HOME}/.config/XfceThemeManager Las miniaturas se almacenan en $ {HOME} / .config / XfceThemeManager
The first time you use Xfce-Theme-Manager you should either run it from the command line with the -m switch or click on the "Rebuld DB" button, the first build of the DB can take a while so be patient! La primera vez que utiliza Xfce-theme-manager que sea debe ejecutar desde la línea de comandos con el modificador-m o haga clic en el "DB Rebuld" el botón, la primera compilación de la base de datos puede tomar un tiempo así que tenga paciencia!

The DB is updated automatically on drag'n'drop, if you do a lot of adding and removeing of themes/icons etc you may want to run Re-build DB from the advanced tab. La base de datos se actualiza automáticamente en arrastrar y soltar, si usted hace un montón de añadir y removeing ​​de los temas o iconos, etc es posible que desee ejecutar Re-construcción de base de datos de la ficha Opciones avanzadas.

Meta Themes are themes that contain a gtk2 folder and an xfwm4 folder (ie window frames and controls), if their is a gnome-like theme.index file that also specifies an icon set this will be used as well. Temas Meta son los temas que contienen una carpeta gtk2 y una carpeta de xfwm4 (es decir, marcos de ventanas y controles), si su archivo es un theme.index con aspecto de gnomo, que también especifica un conjunto de iconos que este será utilizado también.

Spanish is now catered for if you have set the 'LANG' enviroment variable properly, other translations are invited email me for a list to be translated. Española está ahora atendidos si se ha configurado la variable "LANG" entorno adecuadamente, otras traducciones están invitados envíeme un correo electrónico a una lista para ser traducido.

INSTALL: INSTALACIÓN:
Extract the archive say into /tmp, cd into /tmp/Xfce-Theme-Manager, if you are extracting from the command line you may want to put the archive in a subfolder first, run sudo make install, this will iinstall the Xfce-Theme-Manager GUI and the desktop file. Extrae el archivo dicen en / tmp, cd en / tmp / Xfce-theme-manager, si usted está extrayendo de la línea de comandos es posible que desee poner el archivo en una subcarpeta en primer lugar, ejecutar sudo make install, esto iinstall el Xfce- theme-manager y el archivo de interfaz gráfica de usuario de escritorio.
The GUI can be run from the command line or from the settings menu. La interfaz gráfica de usuario se pueden ejecutar desde la línea de comandos o desde el menú de configuración.
The GUI can be manually installed and/or run from the main folder. La interfaz gráfica de usuario puede ser instalado manualmente y / o ejecutar desde la carpeta principal.

There is no configure script as the makefile is very simple, default is to install in /usr/local/bin this can be changed by setting the PREFIX variable prior to make install. No hay ningún script de configuración como el makefile es muy simple, por defecto es instalar en / usr / local / bin esto se puede cambiar mediante el establecimiento de la variable PREFIX antes de make install.

If you have a source based pkg manager like slackware the dev files for glib etc should already be installed, if you are using a debian based install you may have to install the dev packages as well, probably somthing along the lines of glib2-dev/gdk2-dev check your installation documentation for further details. Si usted tiene una fuente de gestor de base como el paquete slackware los archivos para dev etc simplista ya debería estar instalado, si usted está usando una instalación basada en Debian tal vez tengas que instalar los paquetes dev, así, probablemente somthing a lo largo de las líneas de glib2-dev / gdk2-dev consulte la documentación de instalación para más detalles.

You may have to run  xfce4-panel --restart to see the Xfce-Theme-Manager menu item in settings. Es posible que tenga que ejecutar xfce4-panel - reiniciar para ver el menú de Xfce-theme-manager en la configuración.

If you are upgrading from an older version please rebuild the DB ( from the "Advanced" tab ). Si está actualizando desde una versión anterior por favor, a reconstruir la base de datos (desde la pestaña "Avanzado").

*************************************** ***************************************
BUGS: Bugs:
Please send them direct to me at: kdhedger@yahoo.co.uk posting them on xfce-look etc gets too messy! Por favor, envíelas directamente a mí en: kdhedger@yahoo.co.uk su publicación en xfce etc-mirada se vuelve demasiado complicado!
*************************************** ***************************************

Changelog: Cambios:

0.1.10 Added German translation, thanks to Martin F. Schumann for that. 0.1.10 Añadida traducción al alemán, gracias a Martin F. Schumann para ello.
	Removed warnings from xconf about user settings not set. Las advertencias suprimidas de xconf acerca de la configuración de usuario no se establece.
	Added "Custom" when saving custom theme if needed. Añadido "Personalizar" al guardar tema personalizado si es necesario.
	Fixed minor memory leak. Corregido pérdida de memoria menor.
	New application icon. Nuevo icono de la aplicación.
	Minor bug fix when using comma instead of point ( again! ) Corrección de errores de menor importancia cuando se utiliza coma en lugar de punto (¡otra vez!)
	Code clean. Código de limpiar.

0.1.9 Internal release. 0.1.9 comunicado de Interior.

0.1.8	Finally redone border preview to use tile instead of stretch, more accurate. 0.1.8 Por último rehacer las fronteras de vista previa para utilizar baldosas en vez de estiramiento, más precisa.
	Added Application Icon. Añadido icono de aplicación.
	Changed 'Save Theme' to 'Custom Theme' button to now add/delete custom themes. Cambiado 'Guardar tema' al botón 'Custom Theme' para añadir ahora / eliminar temas personalizados.

0.1.7 Updated README. 0.1.7 README actualizado.
	Ignore sub-folders embedded in 'Backdrop' folders as per Xfce gui. No haga caso de sub-carpetas incluidas en las carpetas de Telón de fondo de acuerdo con Xfce gui.
	added fix for commas instead of points in sliders. agregó solución para comas en lugar de puntos en deslizadores.
	Added spanish translation (thanks to Pablo Morales Romero for his help) Añadida traducción al español (gracias a Pablo Morales Romero, por su ayuda)
	Bug fix for malformed xfwm4 themes. Corrección de errores de malformaciones xfwm4 temas.
	Removed abnormal exit on no cursor pixmaps. Eliminado salida anormal en ninguna pixmaps cursor.

0.1.6	Private bug fixing. 0.1.6 corrección de errores privado.

0.1.5	Re-added cursor size to advanced. 0.1.5 Re-añadió tamaño del cursor hasta el avanzado.
	'Reset Theme' now resets controls in advanced tab. 'Restablecer temáticas' ahora controla restablece en la pestaña de avanzado.
	Added 'Save Theme', now saves complete custom themes. Añadido 'Guardar tema', ahora guarda completos temas personalizados.
	Moved 'Rebuild DB' to 'Advanced tab. Moved "Reconstruir BD" a "ficha Opciones avanzadas.
	Brightness/Saturation now only update on button up. Brillo / Saturación ahora sólo día en el botón de arriba.

0.1.4	Should now be gtk3 compliant. 0.1.4 ahora debería ser compatible con gtk3.
	Removed manual 'Update DB' button as update is now automatic. Eliminado el botón manual de "actualización de base de datos 'como la actualización es ahora automática.
	First release of completely rewritten code into 'c' mainly for speed improvements. La primera versión de código completamente reescrito en 'c' principalmente para mejoras de velocidad.
	Sort alphabetically and user first then system. Ordenar por orden alfabético y el usuario primero y luego el sistema.
	Automatic DB update on successful install of theme etc. Automático de actualización de base de datos sobre la instalación correcta del tema, etc
	Full drag'N'drop for installation of themes, icons backdrops etc. Arrastrar y soltar para la instalación completa de los temas, iconos, etc telones de fondo
	Re-arranged advanced page. Re-arranged página avanzada.
	Font buttons show font name in font style. Botones Fuentes mostrar el nombre de la fuente en el estilo de fuente.
	Multi-threaded progress bar. Multi-threaded barra de progreso.

0.1.3	Private release versions. 0.1.3 versiones comerciales privadas.
0.0.9 0.0.9

0.0.8	Tweaked helper app to show render overlays in previews properly. 0.0.8 aplicación auxiliar ha ajustado para mostrar superposiciones de representación en las vistas previas correctamente.
	Added Cursor size,title position and button layout to advanced. Añadido el tamaño del cursor, título de la posición y la disposición de los botones hasta el avanzado.
	Added 'Install Theme/Wallpaper' to advanced. Añadido botón 'Instalar tema / Wallpaper' a avanzado.
	Added WM/App font selector to gui and helper app. Añadido WM / aplicación de la fuente de selección para GUI y aplicación auxiliar.
	Moved window brightness/saturation to advanced. Movido el brillo de la ventana / la saturación de avanzada.
	Added launch 'Xfce4-Composite-Editor' to advanced. Añadido lanzamiento "Xfce4-Composite-editor de avanzada.
	Added 'Advanced' option. Añadido "Advanced" opción.

0.0.7	Added Wallpaper Section. 0.0.7 Se agregó una sección Fondos.
	Tested under Xfce 4.10. Sometido a pruebas en Xfce 4,10.
	Adds properties to xconf if not defined. Añade propiedades a xconf si no se define.
	Refresh Xfce desktop when changing icons. Actualizar Xfce de escritorio al cambiar los iconos.
	Tweaked the Makefile to take acount of Fedora's mucking about with the linker! Ajustado el Makefile para tomar acount de Fedora de perder el tiempo con el enlazador!

0.0.6	Icon themes now handled by helper app hopefully no more 'missing' icons in the gui. 0.0.6 temas de iconos ahora a cargo de ayudante de aplicación es de esperar no más "desaparecido" iconos de la interfaz gráfica de usuario.
	Meta-Themes now include 'Home' icon and 'Left' pointer in preview. Meta-Temas incluyen ahora icono 'Home' y 'la izquierda' puntero en la vista previa.
	Size of Meta-Theme previews nor more consistant. Tamaño de las vistas previas temáticas Meta-ni consistant más.
	Numerous minor bug fix's. Numerosos corrección de errores menor.

0.0.5	Added Custom preview. 0.0.5 Añadido Previo con tu mensaje.
	Numerous bug fix's for badly formed themes. Corrección de errores es para numerosos temas mal formados.
	Code clean up. Código limpio para arriba.

0.0.4b	Fixed a bug where imagemagick swallows stdin 0.0.4b Se ha corregido un error por el que se traga imagemagick stdin
	Added Cursor theme tab. Añadido ficha tema del cursor.
	Added cursor previews to helper app. Añadido previstas cursor se convierte en ayudante de aplicación.
	Fixed another "spaces in file name" bug Corregido otro "en espacios de nombre de archivo" error

0.0.03b	Large numbers of themes now supported >200. 0.0.03b Un gran número de temas ahora compatible> 200.
	Fixed some bugs with themes with spaces in their names. Se han solucionado algunos bugs con los temas con espacios en sus nombres.

0.0.2b	Re-wrote helper app to create window frame thumbnails 0.0.2b Re-escribió ayudante de aplicación para crear miniaturas de marcos de ventanas
0.0.1b	1st release into the wild 0.0.1b primera liberación en el medio silvestre

Enjoy! Disfrute!

<script>_addload(function(){_setupIW();_csi('en','es','out.txt');});</script>
