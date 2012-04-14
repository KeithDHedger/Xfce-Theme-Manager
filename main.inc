
main ()
{

MAIN_DIALOG='
<window title="Xfce-Theme-Manager" height_request="480" window_position="1">
	<vbox>
	<notebook page="0" show-tabs="false" show-border="false" labels="Themes|Advanced"  space-fill="true" space-expand="true">

		<vbox>
		
		<notebook labels="Themes|Window Borders|Controls|Icons|Cursors|Wallpapers|Advanced" space-fill="true" space-expand="true">


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

			<vbox>
				<vbox>
					<comboboxtext>
						<variable>imagestyle</variable>
						<default>'"$DEFAULTSTYLE"'</default>
						<item>Auto</item>
						<item>Centered</item>
						<item>Tiled</item>
						<item>Stretched</item>
						<item>Scaled</item>
						<item>Zoomed</item>
						<action>exec $SHELL -c '"setimagestyle"'</action>
					</comboboxtext>
				</vbox>

				<vbox scrollable="true">
					'"$WALLPAPERSLIST"'
				</vbox>
			</vbox>


		</notebook>

		</vbox>
			<vbox>
				<text label="Select Theme Archive"></text>
				<hbox>
					<entry fs-action="file"  fs-filters-mime="application/x-compressed-tar|application/x-bzip-compressed-tar|image/*">
						<variable>archive</variable>
					</entry>
					<button>
						<input file stock="gtk-open"></input>
						<action>fileselect:archive</action>
					</button>
					<button>
						<label>Install Theme</label>
						<action>exec $SHELL -c '"doarchive"'</action>
						<action>exec '"xfce-theme-manager"' '"-u &"'</action>
						<action>exit:EXIT</action>
					</button>
				</hbox>
				<hbox>
					<entry fs-action="file"  fs-filters-mime="image/*">
						<variable>papers</variable>
					</entry>
					<button>
						<input file stock="gtk-open"></input>
						<action>fileselect:papers</action>
					</button>
					<button>
						<label>Install Wallpaper</label>
						<action>cp "$papers" '"$LOCALWALLPAPERS"'</action>
						<action>exec '"xfce-theme-manager"' '"-u &"'</action>
						<action>exit:EXIT</action>
					</button>
				</hbox>
				<hseparator></hseparator>
				<text label="Launch Xfce-Composite-Editor"></text>
				<hbox homogenous="true">
					<button  space-expand="true">
						<label>Xfce-Composite-Editor</label>
						<action>exec $SHELL -c '"xfce4-composite-editor"'</action>
					</button>
				</hbox>
				<hseparator></hseparator>
				<text label="Backdrop Adjustments"></text>
				<hbox homogeneous="false">
					<button border-width="8" space-expand="false" >
						<label>Reset</label>
						<variable>bright=0</variable>
						<action>refresh:imagebright</action>
					</button>

				<hscale space-fill="true" space-expand="true" update-policy="1" wrap="true" range-min="-128" range-max="127" value-pos="0">
					<default>'"$DEFAULTBRIGHTNESS"'</default>
					<variable>imagebright</variable>
					<input>echo $bright</input>
					<action>exec $SHELL -c '"setimagestyle"'</action>
				</hscale>
				<text label="Brightness"></text>
</hbox>

				<hbox homogeneous="false">
					<button border-width="8" space-expand="false" >
						<label>Reset</label>
						<variable>sat=1.0</variable>
						<action>refresh:imagesat</action>
					</button>

					<hscale space-fill="true" space-expand="true" update-policy="1" wrap="true" range-min="-10.0" range-max="10.0" range-step="0.1" value-pos="0">
						<default>'"$DEFAULTSAT"'</default>
						<variable>imagesat</variable>
						<input>echo $sat</input>
						<action>exec $SHELL -c '"setimagestyle"'</action>
					</hscale>
					<text label="Saturation"></text>
				</hbox>
				<hseparator></hseparator>
				<text label="Fonts"></text>
				<hbox homogeneous="false" border-width="0">
					<button border-width="8" space-expand="false" >
						<label>Reset</label>
						<action>xfconf-query -c xfwm4 -vp /general/title_font -s "$OLDWMFONT"</action>
						<action>refresh:wmfont</action>
					</button>
					<entry space-expand="true">
						<default>'"$OLDWMFONT"'</default>
						<variable>wmfont</variable>
						<input>xfconf-query -c xfwm4 -vp /general/title_font</input>
					</entry>

					<button border-width="8" space-expand="false" >
						<label>WM Font</label>
						<input file stock="gtk-select-font"></input>
						<action>xfconf-query -c xfwm4 -vp /general/title_font -s "$(gtkprev "fontpicker" "$wmfont")"</action>
						<action>refresh:wmfont</action>
					</button>
				</hbox>
				<hbox homogeneous="false" border-width="0">
					<button border-width="8" space-expand="false" >
						<label>Reset</label>
						<action>xfconf-query -c xsettings -vp /Gtk/FontName -s "$OLDAPPFONT"</action>
						<action>refresh:appfont</action>
					</button>
					<entry space-expand="true">
						<default>'"$OLDAPPFONT"'</default>
						<variable>appfont</variable>
						<input>xfconf-query -c xsettings -vp /Gtk/FontName</input>
					</entry>

					<button border-width="8" space-expand="false" >
						<label>App Font</label>
						<input file stock="gtk-select-font"></input>
						<action>xfconf-query -c xsettings -vp /Gtk/FontName -s "$(gtkprev "fontpicker" "$appfont")"</action>
						<action>refresh:appfont</action>
					</button>
				</hbox>
				<hseparator></hseparator>
				<hbox>
					<text label="Cursor Size"></text>
					<spinbutton update-policy="0" range-min="16" range-max="48" >
						<default>'"$CURSORSIZE"'</default>
						<variable>cursorsize</variable>
						<action>xfconf-query -c xsettings -vp /Gtk/CursorThemeSize -s $cursorsize</action>
					</spinbutton>
				</hbox>
			</vbox>

		<variable>mainui</variable>
		<input>if [ X"$mainui" = "X0" ];then echo 1;else echo 0;fi</input>

	</notebook>

		<hbox  homogeneous="true" space-fill="true" space-expand="false">

			<button>
				<label>Reset Theme</label>
				<variable>reset</variable>
				<action>exec $SHELL -c '"resettheme"'</action>
			</button>

			<button>
				<label>Rebuild DB</label>
				<variable>rbdb</variable>
				<action>exec '"xfce-theme-manager"' '"-m &"'</action>
				<action>exit:EXIT</action>
			</button>

			<button>
				<label>Update DB</label>
				<variable>updb</variable>
				<action>exec '"xfce-theme-manager"' '"-u &"'</action>
				<action>exit:EXIT</action>
			</button>

			<togglebutton>
				<label>Advanced</label>
				<variable>advanced</variable>
				<action>refresh:mainui</action>
				<action>if true disable:rbdb</action>
				<action>if false enable:rbdb</action>
				<action>if true disable:updb</action>
				<action>if false enable:updb</action>
				<action>if true disable:reset</action>
				<action>if false enable:reset</action>
			</togglebutton>

		</hbox>

		<hseparator space-fill="true" ></hseparator>

		<hbox  homogeneous="true" space-fill="false" space-expand="false">
			<button>
				<input file stock="gtk-quit"></input> 
			</button>
		</hbox>

	</vbox>
</window>'

export LANG=en_US

if [ ${#MAIN_DIALOG} -ge 131072 ];then
	echo "$MAIN_DIALOG" > "/tmp/xfcethememanager$$"
	unset MAIN_DIALOG
	$GTKDIALOG --file="/tmp/xfcethememanager$$"

else
	export MAIN_DIALOG
	$GTKDIALOG --program=MAIN_DIALOG >/dev/null
fi

}

