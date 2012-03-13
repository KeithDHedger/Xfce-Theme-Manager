main ()
{
export MAIN_DIALOG="
<window title=\"Xfce-Theme-Manager\" height_request=\"480\" width_request=\"500\" window_position=\"1\">
	<vbox>
		<notebook labels=\"Themes|Window Borders|Controls|Icons\" space-fill=\"true\" space-expand=\"true\">
			<vbox>
				<tree selection-mode=\"1\">
					<label>Theme Name</label>
					<input file>testfile</input>
					<variable>THEMETREE</variable>
				</tree>

			</vbox>

		</notebook>

	<hbox  homogeneous=\"true\" space-fill=\"false\" space-expand=\"false\">
		<button>
			<label>Set Theme</label>
			<action>exec $SHELL -c 'liveupdate'</action>
		</button>

		<button>
			<input file stock=\"gtk-quit\"></input> 
		</button>
	</hbox>

	</vbox>
</window>"

$GTKDIALOG --program=MAIN_DIALOG >/dev/null
}

