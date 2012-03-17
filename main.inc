
main ()
{
export MAIN_DIALOG='
<window title="Xfce-Theme-Manager" height_request="480" width_request="320" window_position="1">
	<vbox>
		<notebook labels="Themes|Window Borders|Controls|Icons" space-fill="true" space-expand="true">
			<vbox scrollable="true">
				'"$METALIST"'
			</vbox>

			<vbox scrollable="true">
				'"$FRAMESLIST"'
			</vbox>

			<vbox scrollable="true">
				'"$CONTROLSLIST"'
			</vbox>

			<vbox>
				<tree selection-mode="1">
					<label>Icon Name</label>
					<input file>'"$ICONFILES"'</input>
					<variable>ICONTREE</variable>
					<action>exec $SHELL -c '"seticons"'</action>
				</tree>
			</vbox>

		</notebook>

	<hbox  homogeneous="true" space-fill="false" space-expand="false">
		<button>
			<label>Reset Theme</label>
			<action>exec $SHELL -c '"resettheme"'</action>
		</button>

		<button>
			<input file stock="gtk-quit"></input> 
		</button>
	</hbox>

	</vbox>
</window>'
#export METALIST='<button space-expand="false" space-fill="false" image-position="2" relief="2">
#<label>AllHallowsEveII</label>
#</button>'

#echo -e $MAIN_DIALOG > ./MAINDIA
#echo -e $METALIST > ./METAL
#export testdia=$MAIN_DIALOG
$GTKDIALOG --program=MAIN_DIALOG >/dev/null
}

