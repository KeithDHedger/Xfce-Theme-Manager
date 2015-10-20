/*
 *
 * ©K. D. Hedger. Tue 20 Oct 15:55:34 BST 2015 keithhedger@keithhedger.darktech.org

 * This file (panels.h) is part of Xfce-Theme-Manager.

 * Xfce-Theme-Manager is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.

 * Xfce-Theme-Manager is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Xfce-Theme-Manager.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PANELS_
#define _PANELS_

void selectPanel(GtkComboBox *widget, gpointer user_data);
void populatePanels(void);
void selectPanel(GtkComboBox *widget, gpointer user_data);
gboolean panelSizeCallback(GtkWidget *widget,GdkEvent *event,gpointer user_data);
void selectPanelStyle(GtkWidget* widget,gpointer data);
void commnonPanelCallback(GtkWidget* widget,gpointer data);
void setPanelColour(GtkColorButton *widget, gpointer user_data);
void setPanels(void);
void resetPanels(void);

#endif
