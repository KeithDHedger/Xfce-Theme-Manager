main ()
{
export MAIN_DIALOG="
<window title=\"Xfce-Theme-Manager\" height_request=\"480\" width_request=\"500\" window_position=\"1\">
	<vbox>
		<notebook labels=\"Themes|Window Borders|Controls|Icons\" space-fill=\"true\" space-expand=\"true\">
			<vbox>
				<tree selection-mode=\"1\">
					<label>Theme Name</label>
					<input file>$THEMEFILES</input>
					<variable>THEMETREE</variable>
					<action>exec $SHELL -c 'settheme'</action>
				</tree>
			</vbox>

			<vbox>
				<tree selection-mode=\"1\">
					<label>Border Name</label>
					<input file>$BORDERFILES</input>
					<variable>BORDERTREE</variable>
					<action>exec $SHELL -c 'setborder'</action>
				</tree>
			</vbox>

			<vbox>
				<tree selection-mode=\"1\">
					<label>Control Name</label>
					<input file>$GTKFILES</input>
					<variable>GTKTREE</variable>
					<action>exec $SHELL -c 'setcontrols'</action>
				</tree>
			</vbox>

			<vbox>
				<tree selection-mode=\"1\">
					<label>Icon Name</label>
					<input file>$ICONFILES</input>
					<variable>ICONTREE</variable>
					<action>exec $SHELL -c 'seticons'</action>
				</tree>
			</vbox>

		</notebook>

	<hbox  homogeneous=\"true\" space-fill=\"false\" space-expand=\"false\">
		<button>
			<label>Reset Theme</label>
			<action>exec $SHELL -c 'resettheme'</action>
		</button>

		<button>
			<input file stock=\"gtk-quit\"></input> 
		</button>
	</hbox>

	</vbox>
</window>"

$GTKDIALOG --program=MAIN_DIALOG >/dev/null
}

