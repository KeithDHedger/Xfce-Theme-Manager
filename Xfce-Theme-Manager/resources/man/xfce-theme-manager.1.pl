.TH "XFCE-THEME-MANAGER" "1" "0.3.0" "K.D.Hedger" ""
.SH NAME
xfce-theme-manager - Menedżer stylów dla Xfce
.SH SYNOPSIS
.B xfce-theme-manager
[option.1] ... [option.N]
.br
.SH DESCRIPTION
Krótka dokumencja podręcznika
.B xfce-theme-manager.
.br
xfce-theme-manager jest menedżerem stylów, który pozwala na łatwą konfigurację wyglądu systemu, w tym: style środowiska, obramawania okien, ikony, kontrolki, ikony, kursor, tła i inne.
.SH OPERATION
Kiedy startuje xfce-theme-manager, użytkownik może zrobić cokolwiek innego.
.br

.B [Reset Theme]
.br
Porzucenie wszystkich zmian.
.br

.B [Save Theme]
.br
Należy wpisać nazwę stylu do zapamiętania / skasowania. Można także szybko wykasować styl, klikając na wybraną miniaturkę.
.br

.B [About]
.br
Podsumowanie i zespół.
.br

.B [Advanced Tab]
.br

.B [Rebuild DB]
.br
Przebudowanie bazy danych.
.br

.B [Xfce-Composite-Editor]
.br
Uruchomienie edytora kompozycji (jeżeli jest zainstalowany).
.br
Dostępne tutaj:
.br
http://keithhedger.hostingsiteforfree.com/zips/Xfce4-Composite-Editor.tar.gz
.br
Należy posiadać zainstalowane pakiety: gtkdialog version 0.8.x i BASH, aby móc uruchomić Edytor Kompozycji.
.br

.B [Backdrop Adjustments]
.br
Ustawia jasność / nasycenie tapety.
.br

.B [Button Layout]
.br
Położenie kontrolek, czyli Zamknięcie, Maksymalizacja okna itp. (pewne ustawienia mogą to nadpisać)
.br

.B [Title Position]
.br
Położenie nazwy okna, (pewne ustawienia mogą to nadpisać).
.br

.B [Font Selection]
.br
Czcionka na pasku nazwy paska / aplikacji.
.br

.B [Cursor Size]
.br
Wybieranie wielkości kursora, jeżeli jest wspierany przez wygląd. Część osób to robi, inni nie.
.br

.B [View Options]
.br
.B [Show system Themes]
.br
Pokazuje wszystkie zainstalowne części stylu systemowego w naszym systemie.
.br

.B [Only show Custom Themes]
.br
Pokazuje tylko meta style, które zostały stoworzone przez użytkownika. Automatycznie generowane meta style nie są pokazywane.
.br

.B [Themes]
.br
Pokazuje wszystkie zainstalowne meta style.
.br

.B [Window Borders]
.br
Pokazuje wszystkie zainstalowne style Xwm4.
.br

.B [Controls]
.br
Pokazuje wszystkie zainstalowne style Gtk.
Show globally installed Gtk themes.
.br

.B [Icons]
.br
Pokazuje wszystkie zainstalowne style ikon.
Show globally installed icon themes.
.br

.B [Cursors]
.br
Pokazuje wszystkie zainstalowne style kursora myszki.
.br

.B [Wallpapers]
.br
Pokazuje wszystkie zainstalowne tapety.
.br

Pokazuje lokalnie zainstalowane style, z wyjątkiem meta stylów, jeżeli
Locally installed themes parts are always shown except for meta themes if the
.B [Only show Custom Themes]
został sprawdzony.
.br
Można szybko skasować własny styl, po przez przytrzymanie klawicza Control i kliknięcie na miniaturkę.
Kasować można tylko stworzone style i usuwany jest wpis z bazy danych, a nie z systemu.
.br
Aby móc zainstalować theme/gtk/icon/cursor/border/wallpaper wystarczy przeciągnąć i upuścić paczkę
(tapety nie powinny być archiwami) gdziekolwiek w oknie głównym i jeżeli to możliwe styl itp
zostanie zainstalowny w odpowiednim miejscu. Wszystkie instalacje są lokalne. Wspierane są
następujące typy archiwów: "*.tgz","*.gz","*.zip","*.tar","*.bz2", oraz tapet: "*.jpg","*.png","*.bmp","*.gif".
Wszystko inne należy zainstalować ręcznie.
.br

Należy ręcznie wypakować instalowalne archiwum, aby móc przeciągnąć i upuścić pliki .zip
.br

Miniaturki są przechowywane w ${HOME}/.config/XfceThemeManager.
.br

Baza danych jest aktualizowana automatycznie w przypadku przeciągnięcia i upuszczenia. Jednakże
w momencie dodania lub usunięcia dużej liczby themes/icons itp powinno się ręcznie przebudować
bazę danych z zakładki Zaawansowane.
.br

Meta Style są stylami, które zawierają katalog gtk2 i xfwm4. Jeżeli są tam pliki typu theme.index, które
określają zestaw ikon, wtedy zostaną one użyte.
.br
.SH COMMAND LINE OPTIONS
-v, --version
.br
		Drukuje informacje i wychodzi.
.br

-u, --update-db
.br
		Aktualizuje bazę danych.
.br

-r, --build-db
.br
		Przebudowuje bazę danych.
.br

-n, --nogui
.br
		Aplikacja nie uruchamia interfejsu graficznego.
.br

-t, --theme=ARG
.br
		Ustaw meta-styl na ARG.
.br

-c, --controls=ARG
.br
		Ustaw style kontrolek na ARG
.br

-w, --wmborder=ARG
.br
		Ustaw styl obramowania okien na ARG.
.br

-i, --icons=ARG
.br
		Ustaw style ikon na ARG.
.br

-p, --cursors=ARG
.br
		Ustaw styl kursora na ARG.
.br

-b, --backdrop=ARG
.br
		Ustaw tapetę na ARG.
.br

-l, --list=ARG
.br
		Pokaż wpisy w bazie danych, gdzie ARG = dowolny znak z "*Ctwcib".
.br

	Gdzie 'C' pokazuje własne style, 't' pokazuje style, 'w' pokazuje obramowania okien, 'c' pokazuje style kontrolek, 'i' pokazuje style ikon, a 'b' pokazuje tapety.
	Jeżeli wpiszemy '*' to zostaną wyświetlone wszystkie wpisy.
.br

-?, --help
.br
		Pokazuje pomoc.
.br

Options tcwipblvh? all imply -n.
.br
.SH  AUTHOR
.B Xfce-Theme-Manager
został stworzony przez Keitha Hedgera

Strona podręcznika została napisana przez Eduardo Echeverria <echevemaster@gmail.com>,
dla projektu Fedora (i może być używana przez innych), zmienione przez Keith Hedger, przetłumaczone przez Pablo Morales Romero
<pg.morales.romero@gmail.com> (hiszpański), Martin F. Schumann <mfs@mfs.name> (niemiecki), Michał Olber (redakcja@osworld.pl)(polski).
