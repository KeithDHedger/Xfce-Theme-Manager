#				<tree selection-mode=\"2\">
#					<label>Theme Name</label>
#					<input file>$THEMEFILES</input>
#					<variable>THEMETREE</variable>
 #    					<action signal=\"cursor-changed\">echo cursor-changed: \$THEMETREE >&2</action>
  #   					<action signal=\"button-press-event\">echo button-press-event[BUTTON=\$BUTTON]: \$THEMETREE >&2</action>
   #  					<action signal=\"button-release-event\">echo button-release-event[BUTTON=\$BUTTON]: \$THEMETREE >&2</action>
	#				<action>exec $SHELL -c 'settheme'</action>
	#				
	#			</tree>


main ()
{
export MAIN_DIALOG="
<window title=\"Xfce-Theme-Manager\" height_request=\"480\" width_request=\"500\" window_position=\"1\">
	<vbox>
		<notebook labels=\"Themes|Window Borders|Controls|Icons\" space-fill=\"true\" space-expand=\"true\">
			<vbox scrollable=\"true\">
				<hbox>
					<text use-markup=\"true\" width_request=\"100\" space-expand=\"false\">
						<label>\"<span fgcolor='black' bgcolor='white'>AllHallowsEveII</span>\"</label>
					</text>
					<pixmap space-expand=\"true\" space-expand=\"true\" >
						<input file>/tmp/XFTE/meta/AllHallowsEveII.bmp</input>
					</pixmap>
				</hbox>
				<hbox space-expand=\"false\" space-fill=\"true\">
					<button space-expand=\"false\" space-fill=\"false\" image-position=\"2\">
						<input file>/tmp/XFTE/meta/OldWoodAndSteel.bmp</input>

						<label>\"OldWoodAndSteel\"</label>
						<action>echo \"dooo it\" >&2</action>
					</button>
					<pixmap space-expand=\"true\" space-fill=\"false\" >
						<input file>/tmp/XFTE/meta/OldWoodAndSteel.bmp</input>
					</pixmap>
				</hbox>
				<hbox space-expand=\"false\" space-fill=\"true\">
					<button space-expand=\"false\" space-fill=\"false\" image-position=\"2\">
						<input file>/tmp/XFTE/meta/OldWoodAndSteel.bmp</input>

						<label>\"OldWoodAndSteel\"</label>
						<action>echo \"dooo it\" >&2</action>
					</button>
					<pixmap space-expand=\"true\" space-fill=\"false\" >
						<input file>/tmp/XFTE/meta/OldWoodAndSteel.bmp</input>
					</pixmap>
				</hbox>
				<hbox space-expand=\"false\" space-fill=\"true\">
					<button space-expand=\"false\" space-fill=\"false\" image-position=\"2\">
						<input file>/tmp/XFTE/meta/OldWoodAndSteel.bmp</input>

						<label>\"OldWoodAndSteel\"</label>
						<action>echo \"dooo it\" >&2</action>
					</button>
					<pixmap space-expand=\"true\" space-fill=\"false\" >
						<input file>/tmp/XFTE/meta/OldWoodAndSteel.bmp</input>
					</pixmap>
				</hbox>
				<hbox space-expand=\"false\" space-fill=\"true\">
					<button space-expand=\"false\" space-fill=\"false\" image-position=\"2\">
						<input file>/tmp/XFTE/meta/OldWoodAndSteel.bmp</input>

						<label>\"OldWoodAndSteel\"</label>
						<action>echo \"dooo it\" >&2</action>
					</button>
					<pixmap space-expand=\"true\" space-fill=\"false\" >
						<input file>/tmp/XFTE/meta/OldWoodAndSteel.bmp</input>
					</pixmap>
				</hbox>
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

