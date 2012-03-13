main ()
{
export MAIN_DIALOG="
<window title=\"Xfce-Theme-Manager\" height_request=\"480\" width_request=\"500\" window_position=\"1\">
	<vbox>

		<text>
			<label>\"Some Label\"</label>
		</text>

		<hbox>
			<text>
				<label>\"Shadow Opacity\"</label>
			</text>

			<spinbutton space-expand=\"false\" space-fill=\"false\" update-policy=\"0\" range-min=\"0\" range-max=\"100\" >
				<default>$DATA</default>
				<variable>DATA_SPIN</variable>
				<action>refresh:DATA_RANGE</action>
				<input>echo \$DATA_RANGE</input>
			</spinbutton>

			<hscale space-expand=\"true\" space-fill=\"true\" draw-value=\"false\" update-policy=\"0\" wrap=\"true\" range-min=\"0\" range-max=\"100\">
				<default>$DATA</default>
				<variable>DATA_RANGE</variable>
				<action>refresh:DATA_SPIN</action>
				<action>exec $SHELL -c 'liveupdate'</action>
				<input>\"if [ -e $RESET ];then echo $DATA_DEF;rm $RESET;else echo \$DATA_SPIN;fi\"</input>
			</hscale>
		</hbox>

		<hseparator height_request=\"16\"></hseparator>
		
		<hbox>
				
			<button space-expand=\"true\">
				<input file stock=\"gtk-quit\"></input> 
			</button>

		</hbox>

	</vbox>
</window>"

$GTKDIALOG --program=MAIN_DIALOG >/dev/null
}

