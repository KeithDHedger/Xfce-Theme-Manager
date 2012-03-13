main ()
{
export MAIN_DIALOG="
<window title=\"Xfce-Theme-Manager\" height_request=\"480\" width_request=\"500\" window_position=\"1\">
	<vbox>
		<notebook labels=\"Themes|Window Borders|Controls|Icons\">
			<vbox>
				<checkbox>
					<label>This is a checkbox</label>
				</checkbox>
			</vbox>

		</notebook>
	</vbox>
</window>"

$GTKDIALOG --program=MAIN_DIALOG >/dev/null
}

