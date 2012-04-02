
main ()
{
MAIN_DIALOG='
<window title="Xfce-Theme-Manager" height_request="480" window_position="1">
	<vbox>
		<notebook labels="Themes|Window Borders|Controls|Icons|Cursors|Wallpapers" space-fill="true" space-expand="true">


			<vbox scrollable="true">
				'"$METALIST"'
			</vbox>

			<vbox scrollable="true">
				'"$FRAMESLIST"'
			</vbox>

			<vbox scrollable="true">
				'"$CONTROLSLIST"'
			</vbox>

			<vbox scrollable="true">
				'"$ICONSLIST"'
			</vbox>

			<vbox scrollable="true">
				'"$CURSORSLIST"'
			</vbox>

			<vbox scrollable="true">
				'"$WALLPAPERSLIST"'
			</vbox>

		</notebook>

		<hbox  homogeneous="true" space-fill="true" space-expand="false">

			<button>
				<label>Reset Theme</label>
				<action>exec $SHELL -c '"resettheme"'</action>
			</button>

			<button>
				<label>Rebuild DB</label>
				<action>exec '"xfce-theme-manager"' '"-m &"'</action>
				<action>exit:EXIT</action>
			</button>

			<button>
				<label>Update DB</label>
				<action>exec '"xfce-theme-manager"' '"-u &"'</action>
				<action>exit:EXIT</action>
			</button>

		</hbox>

		<hseparator space-fill="true" ></hseparator>

		<hbox  homogeneous="true" space-fill="false" space-expand="false">
			<button>
				<input file stock="gtk-quit"></input> 
			</button>
		</hbox>

	</vbox>
</window>'

if [ ${#MAIN_DIALOG} -ge 131072 ];then
	echo "$MAIN_DIALOG" > "/tmp/xfcethememanager$$"
	unset MAIN_DIALOG
	$GTKDIALOG --file="/tmp/xfcethememanager$$"

else
	export MAIN_DIALOG
	$GTKDIALOG --program=MAIN_DIALOG >/dev/null
fi

}

