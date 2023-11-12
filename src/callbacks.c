#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "functions_ets.h"
#include "functions_user.h"



gboolean on_label14_button_press_event (GtkWidget *widget, GdkEventButton  *event, gpointer user_data)
{

  return FALSE;
}


void on_confirmationButton_deletePopupWindow_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void on_cancelButton_deletePopupWindow_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_addButton_advancedSettingsWindow_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_deleteButton_advancedSettingsWindow_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_editUsersButton_admin_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_editButton_edit_editEts_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_searchEntry_display_editEts_changed (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_deleteButton_edit_editEts_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_regionCheckButton_display_editEts_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void on_capacityCheckButton_display_editEts_toggled (GtkToggleButton *togglebutton, gpointer user_data)
{

}


void on_searchButton_display_editEts_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void on_showPasswordCheckButton_authentification_toggled (GtkWidget *togglebutton, gpointer user_data)
{
	GtkWidget *widget;
	widget = lookup_widget(togglebutton, "passwordEntry_authentification");
	gtk_entry_set_visibility(GTK_ENTRY(widget), gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)));	
}


void on_loginButton_authentification_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget;
	char cin[LENGTH];
	char password[LENGTH];
	char role[LENGTH];
	char error[100];
	widget = lookup_widget(button, "cinEntry_authentification");
	strcpy(cin, gtk_entry_get_text(GTK_ENTRY(widget)));
	widget = lookup_widget(button, "passwordEntry_authentification");
	strcpy(password, gtk_entry_get_text(GTK_ENTRY(widget)));
	int check =  authenticate(cin, password, role, error);
	widget = lookup_widget(button, "errorLabel_authentification");
	gtk_label_set_text(GTK_LABEL(widget), error);
	if(check == 1)
		if(strcmp(role, "admin") == 0)
		{
			GtkWidget *data;
			widget = lookup_widget(button, "authentificationWindow");
			gtk_widget_destroy(widget);
			widget = create_adminWindow();
			data = lookup_widget(widget, "dataLabel_admin");
			gtk_label_set_text(GTK_LABEL(data), cin);
			user admin;
			admin = get_userInfo(cin);
			data = lookup_widget(widget, "welcomeUserLabel_admin");
			char *string = g_strdup_printf("Bienvenue admin  : %s, %s", admin.surname, admin.name);
			gtk_label_set_text(GTK_LABEL(data), string);
			g_free(string);
			gtk_widget_show(widget); 
		}
}


void on_settingsButton_admin_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget;
	char admin_data[LENGTH];
	widget = lookup_widget(button, "dataLabel_admin");
	strcpy(admin_data, gtk_label_get_text(GTK_LABEL(widget)));
	widget = lookup_widget(button, "adminWindow");
	gtk_widget_destroy(widget);
	widget = create_settingsAdminWindow();
	GtkWidget *data = lookup_widget(widget, "dataLabel_settingsAdmin");
	gtk_label_set_text(GTK_LABEL(data), admin_data);
	user admin;
	admin = get_userInfo(admin_data);
	data = lookup_widget(widget, "firstNameEntry_settingsAdmin");
	gtk_entry_set_text(GTK_ENTRY(data), admin.name);
	data = lookup_widget(widget, "lastNameEntry_settingsAdmin");
	gtk_entry_set_text(GTK_ENTRY(data), admin.surname);
	data = lookup_widget(widget, "telephoneEntry_settingsAdmin");
	gtk_entry_set_text(GTK_ENTRY(data), admin.tel);
	gtk_widget_show(widget);
}


void on_settingsButton_admin_enter (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(button, "onHoverLabel_admin");
	gtk_label_set_text(GTK_LABEL(widget), "Gérer votre Compte");
}


void on_settingsButton_admin_leave (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(button, "onHoverLabel_admin");
	gtk_label_set_text(GTK_LABEL(widget), "");
}


void on_logoutButton_admin_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(button, "adminWindow");
	gtk_widget_destroy(widget);
	widget = create_authentificationWindow();
	gtk_widget_show(widget);
}


void on_logoutButton_admin_enter (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(button, "onHoverLabel_admin");
	gtk_misc_set_alignment (GTK_MISC (widget), 1, 0.5);
	gtk_label_set_text(GTK_LABEL(widget), "se déconnecter");
}


void on_logoutButton_admin_leave (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(button, "onHoverLabel_admin");
	gtk_label_set_text(GTK_LABEL(widget), "");
}


void on_editEtsButton_admin_clicked (GtkWidget *button, gpointer user_data)
{
	char string[LENGTH];
	GtkWidget *widget = lookup_widget(button, "dataLabel_admin");
	strcpy(string, gtk_label_get_text(GTK_LABEL(widget)));
	widget = lookup_widget(button, "adminWindow");
	gtk_widget_destroy(widget);
	widget = create_editEtsWindow();
	GtkWidget *data = lookup_widget(widget, "dataLabel_editEts");
	gtk_label_set_text(GTK_LABEL(data), string);
	gtk_widget_show(widget);
}


void
on_statisticsButton_admin_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{

}


void on_logoutButton_settingsAdmin_enter (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(button, "onHoverLabel_settingsAdmin");
	gtk_misc_set_alignment (GTK_MISC (widget), 1, 0.5);
	gtk_label_set_text (GTK_LABEL (widget), "se déconnecter");
}


void on_logoutButton_settingsAdmin_leave (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(button, "onHoverLabel_settingsAdmin");
	gtk_label_set_text (GTK_LABEL (widget), "");
}


void on_showPasswordCheckButton_editCin_toggled (GtkWidget *togglebutton, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(togglebutton, "passwordEntry_editCin");
	gtk_entry_set_visibility(GTK_ENTRY(widget), gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)));
}


void
on_continueButton_editCin_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_confirmButton_enterCin_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{

}


void on_confirmButton_enterPassword_clicked (GtkWidget *button, gpointer user_data)
{
	char password1[LENGTH];
	char password2[LENGTH];
	char cin[LENGTH];
	GtkWidget *widget = lookup_widget (button, "dataLabel_enterPassword");
	strcpy (cin, gtk_label_get_text (GTK_LABEL (widget)));
	user admin = get_userInfo (cin);
	widget = lookup_widget (button, "passwordEntry_enterPassword");
	strcpy (password1, gtk_entry_get_text (GTK_ENTRY (widget)));
	widget = lookup_widget (button, "confirmPasswordEntry_enterPassword");
	strcpy (password2, gtk_entry_get_text (GTK_ENTRY (widget)));
	if (get_password_difficulty (password1) == 0)
	{
		widget = lookup_widget (button, "errorLabel_enterPassword");
		gtk_label_set_text (GTK_LABEL (widget), "Mot de pass trop faible");
	}
	else if (strcmp (password1, password2) != 0)
	{
		widget = lookup_widget (button, "errorLabel_enterPassword");
		gtk_label_set_text (GTK_LABEL (widget), "Mots de passe non identiques");	
	}
	else
	{
		strcpy (admin.password, password1);
		edit_user (admin);
		gtk_widget_set_sensitive (GTK_WIDGET (user_data), TRUE);
		widget = lookup_widget (button, "enterPasswordPopupWindow");
		gtk_widget_destroy (widget);	
	}
}


void on_passwordEntry_enterPassword_changed (GtkWidget *button, gpointer user_data)
{
	char password[LENGTH];
	GtkWidget *widget = lookup_widget (button, "passwordEntry_enterPassword");
	strcpy (password, gtk_entry_get_text (GTK_ENTRY (widget)));
	int difficulty = get_password_difficulty (password);
	widget = lookup_widget (button, "passwordDifficultyProgressBar_enterPassword");
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (widget), difficulty * 0.33);
}


void on_showPasswordButton_enterPassword_pressed (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(button, "passwordEntry_enterPassword");
	gtk_entry_set_visibility(GTK_ENTRY(widget), TRUE);
}


void on_showPasswordButton_enterPassword_released (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(button, "passwordEntry_enterPassword");
	gtk_entry_set_visibility(GTK_ENTRY(widget), FALSE);
}


void on_logoutButton_editEts_enter (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(button, "onHoverLabel_editEts");
	gtk_misc_set_alignment (GTK_MISC (widget), 1, 0.5);
	gtk_label_set_text(GTK_LABEL(widget), "se déconnecter");
}


void on_logoutButton_editEts_leave (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(button, "onHoverLabel_editEts");
	gtk_label_set_text(GTK_LABEL(widget), "");
}


void on_advancedSettingsButton_editEts_clicked (GtkWidget *button, gpointer user_data)
{

}


void
on_cancelButton_add_editEts_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_addButton_add_editEts_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{

}


gboolean
on_addLabel_editEts_button_press_event (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{

  return FALSE;
}


void
on_nameEtsEntry_manage_editEts_changed (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_capacitySpinButton_display_editEts_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_etsTreeView_row_activated           (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}


void
on_regionCheckButton_editEts_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_capacityCheckButton_editEts_toggled (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_deleteCheckButton_manage_editEts_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_resetFiltersButton_manage_editEts_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_regionComboBox_display_editEts_changed
                                        (GtkComboBox     *combobox,
                                        gpointer         user_data)
{

}


gboolean
on_displayLabel_editEts_button_press_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{

  return FALSE;
}


void
on_confirmButton_edit_editEts_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_cancelButton_edit_editEts_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{

}


gboolean
on_editLabel_editEts_button_press_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{

  return FALSE;
}


void
on_cancelButton_enterCin_resetPassword_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_continueButton_enterCin_resetPassword_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_confirmButton_deleteEts_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_addButton_advancedSettings_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_deleteButton_advancedSettings_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_editPasswordButton_authentification_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_editCinButton_settingsAdmin_clicked (GtkButton       *button,
                                        gpointer         user_data)
{

}


void on_editPasswordButton_settingsAdmin_clicked (GtkWidget *button, gpointer user_data)
{
	char cin[LENGTH];
	GtkWidget *widget = lookup_widget (button, "dataLabel_settingsAdmin");
	strcpy (cin, gtk_label_get_text (GTK_LABEL (widget))); 
	GtkWidget *mainWindow = lookup_widget (button, "settingsAdminWindow");
	gtk_widget_set_sensitive (mainWindow, FALSE);
	GtkWidget *popupWindow = create_editPasswordPopupWindow();
	widget = lookup_widget (popupWindow, "cancelButton_editPassword");
	g_signal_connect (G_OBJECT (widget), "clicked", G_CALLBACK (on_cancelEditSettingsAdmin_clicked), (gpointer) mainWindow);
	widget = lookup_widget (popupWindow, "secretAnswerEntry_editPassword");
	g_signal_connect (G_OBJECT (widget), "activate", G_CALLBACK (on_continueButton_editPassword_clicked), (gpointer) mainWindow);
	widget = lookup_widget (popupWindow, "continueButton_editPassword");
	g_signal_connect (G_OBJECT (widget), "clicked", G_CALLBACK (on_continueButton_editPassword_clicked), (gpointer) mainWindow);
	widget = lookup_widget (popupWindow, "secretQuestionLabel_editPassword");
	user admin = get_userInfo(cin);
	gtk_label_set_text (GTK_LABEL (widget), admin.question);
	widget = lookup_widget (popupWindow, "dataLabel_editPassword");
	gtk_label_set_text (GTK_LABEL (widget), cin);
	gtk_widget_show (popupWindow);
	
}


void
on_leaveButton_confirmLeave_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_continueButton_enterCin_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{

}






void on_leaveButton_leaveSettingsAdmin_clicked (GtkWidget *button, gpointer user_data)
{
	
}


void
on_leaveButton_leaveEditEts_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void on_settingsButton_editEts_enter (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(button, "onHoverLabel_editEts");
	gtk_misc_set_alignment (GTK_MISC (widget), 1, 0.5);
	gtk_label_set_text(GTK_LABEL(widget), "Gérer votre Compte");
}


void on_settingsButton_editEts_leave (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(button, "onHoverLabel_editEts");
	gtk_label_set_text(GTK_LABEL(widget), "");
}


void
on_cancelButton_deleteEts_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{

}


void on_leaveSettingsAdmin_clicked (GtkWidget *button, gpointer user_data)
{
	char string[20];
	GtkWidget *mainWindow = lookup_widget(button, "settingsAdminWindow");
	gtk_widget_set_sensitive(mainWindow, FALSE);
	GtkWidget *popupWindow = create_leaveSettingsAdminPopupWindow();
	GtkWidget *data = lookup_widget(popupWindow, "cancelButton_leaveSettingsAdmin");
	g_signal_connect (G_OBJECT (data), "clicked", G_CALLBACK (on_cancelButton_leaveSettingsAdmin_clicked), (gpointer) mainWindow);
	data = lookup_widget(popupWindow, "leaveButton_leaveSettingsAdmin");
	g_signal_connect (G_OBJECT (data), "clicked", G_CALLBACK (on_leaveButton_leaveSettingsAdmin_clicked), (gpointer) mainWindow);
	data = lookup_widget(popupWindow, "dataLabel_leaveSettingsAdmin");
	gtk_label_set_text(GTK_LABEL(data), gtk_button_get_label(GTK_BUTTON(button)));
	gtk_widget_show(popupWindow);
}


void on_mainMenuButton_settingsAdmin_enter (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(button, "onHoverLabel_settingsAdmin");
	gtk_misc_set_alignment(GTK_MISC (widget), 0, 0.5);
	gtk_label_set_text(GTK_LABEL (widget), "Menu Principal");
}


void on_mainMenuButton_settingsAdmin_leave (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(button, "onHoverLabel_settingsAdmin");
	gtk_label_set_text(GTK_LABEL(widget), "");
}


void on_resetButton_settingsAdmin_clicked (GtkWidget *button, gpointer user_data)
{
	char cin[LENGTH];
	GtkWidget *widget = lookup_widget (button, "dataLabel_settingsAdmin");
	strcpy (cin, gtk_label_get_text (GTK_LABEL (widget)));
	user admin = get_userInfo(cin);
	widget = lookup_widget (button, "firstNameEntry_settingsAdmin");
	gtk_entry_set_text (GTK_ENTRY (widget), admin.name);
	widget = lookup_widget (button, "lastNameEntry_settingsAdmin");
	gtk_entry_set_text (GTK_ENTRY (widget), admin.surname);
	widget = lookup_widget (button, "telephoneEntry_settingsAdmin");
	gtk_entry_set_text (GTK_ENTRY (widget), admin.tel);
}


void on_confirmButton_settingsAdmin_clicked (GtkWidget *button, gpointer user_data)
{
	user data;
	char cin[LENGTH];
	GtkWidget *widget = lookup_widget (button, "dataLabel_settingsAdmin");
	strcpy (cin, gtk_label_get_text (GTK_LABEL (widget)));
	data = get_userInfo(cin);
	widget = lookup_widget (button, "firstNameEntry_settingsAdmin");
	strcpy (data.name, gtk_entry_get_text (GTK_ENTRY (widget)));
	widget = lookup_widget (button, "lastNameEntry_settingsAdmin");
	strcpy (data.surname, gtk_entry_get_text (GTK_ENTRY (widget)));
	widget = lookup_widget (button, "telephoneEntry_settingsAdmin");
	strcpy (data.tel, gtk_entry_get_text (GTK_ENTRY (widget)));
	edit_user (data);
}


void on_cancelButton_leaveSettingsAdmin_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(button, "leaveSettingsAdminPopupWindow");
	gtk_widget_set_sensitive(GTK_WIDGET(user_data), TRUE);
	gtk_widget_destroy(widget);
}


void on_cancelEditSettingsAdmin_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = gtk_widget_get_toplevel (button);
	gtk_widget_set_sensitive (GTK_WIDGET (user_data), TRUE);
	gtk_widget_destroy (widget);
}


void on_continueButton_editPassword_clicked (GtkWidget *button, gpointer user_data)
{
	char answer[LENGTH];
	char cin[LENGTH];
	GtkWidget *widget = lookup_widget (button, "dataLabel_editPassword");
	strcpy (cin, gtk_label_get_text (GTK_LABEL (widget)));
	user admin = get_userInfo(cin);
	widget = lookup_widget (button, "secretAnswerEntry_editPassword");
	strcpy (answer, gtk_entry_get_text (GTK_ENTRY (widget)));
	if (strcmp (answer, admin.answer) == 0)
	{
		widget = lookup_widget (button, "editPasswordPopupWindow");
		gtk_widget_destroy (widget);
		GtkWidget *popupWindow = create_enterPasswordPopupWindow();
		widget = lookup_widget (popupWindow, "dataLabel_enterPassword");
		gtk_label_set_text (GTK_LABEL (widget), cin);
		widget = lookup_widget (popupWindow, "cancelButton_enterPassword");
		g_signal_connect (G_OBJECT (widget), "clicked", G_CALLBACK (on_cancelEditSettingsAdmin_clicked), user_data);
		widget = lookup_widget (popupWindow, "confirmButton_enterPassword");
		g_signal_connect (G_OBJECT (widget), "clicked", G_CALLBACK (on_confirmButton_enterPassword_clicked), user_data);
		widget = lookup_widget (popupWindow, "passwordEntry_enterPassword");
		g_signal_connect (G_OBJECT (widget), "activate", G_CALLBACK (on_confirmButton_enterPassword_clicked), user_data);
		widget = lookup_widget (popupWindow, "confirmPasswordEntry_enterPassword");
		g_signal_connect (G_OBJECT (widget), "activate", G_CALLBACK (on_confirmButton_enterPassword_clicked), user_data);
		gtk_widget_show (popupWindow);
	}
	else
	{
		gtk_entry_set_text (GTK_ENTRY (widget), "");
		int nbr_error = 1;
		widget = lookup_widget (button, "errorNumberLabel_editPassword");
		nbr_error += atoi(gtk_label_get_text (GTK_LABEL (widget)));
		if (nbr_error >= 3)
		{
			gtk_widget_destroy (GTK_WIDGET (user_data));
			widget = lookup_widget (button, "editPasswordPopupWindow");
			gtk_widget_destroy (widget);
			GtkWidget *mainWindow = create_authentificationWindow();
			widget = lookup_widget (mainWindow, "errorLabel_authentification");
			gtk_label_set_text (GTK_LABEL (widget), "Pour des raisons de sécurité, vous avez été déconnecté");
			gtk_widget_show (mainWindow);
		}
		else
		{
			widget = lookup_widget (button, "errorNumberLabel_editPassword");
			char nbr_errorStr[3];
			sprintf (nbr_errorStr, "%d", nbr_error);
			gtk_label_set_text (GTK_LABEL (widget), nbr_errorStr);
			widget = lookup_widget (button, "errorLabel_editPassword");
			char text[50];
			sprintf (text, "Tentatives restantes : %d", 3-nbr_error);
			gtk_label_set_text (GTK_LABEL (widget), text);	
		}
	}
	
}


void on_leaveEditEts_clicked (GtkWidget *button, gpointer user_data)
{
	char string[20];
	GtkWidget *mainWindow = lookup_widget (button, "editEtsWindow");
	gtk_widget_set_sensitive(mainWindow, FALSE);
	GtkWidget *popupWindow = create_leaveEditEtsPopupWindow();
	GtkWidget *data = lookup_widget (popupWindow, "dataLabel_leaveEditEts");
	gtk_label_set_text (GTK_LABEL (data), gtk_button_get_label (GTK_BUTTON (button)));
	data = lookup_widget(popupWindow, "cancelButton_leaveEditEts");
	g_signal_connect (G_OBJECT (data), "clicked", G_CALLBACK (on_cancelButton_leaveEditEts_clicked), (gpointer) mainWindow);
	data = lookup_widget(popupWindow, "leaveButton_leaveEditEts");
	g_signal_connect (G_OBJECT (data), "clicked", G_CALLBACK (on_leaveButton_leaveEditEts_clicked), (gpointer) mainWindow);
	gtk_widget_show(popupWindow);
}


void on_mainMenuButton_editEts_enter (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget (button, "onHoverLabel_editEts");
	gtk_misc_set_alignment (GTK_MISC (widget), 0, 0.5);
	gtk_label_set_text (GTK_LABEL (widget), "Menu Principal");
}


void on_mainMenuButton_editEts_leave (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget (button, "onHoverLabel_editEts");
	gtk_label_set_text (GTK_LABEL (widget), "");
}


void on_cancelButton_leaveEditEts_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget (button, "leaveEditEtsPopupWindow");
	gtk_widget_set_sensitive (GTK_WIDGET (user_data), TRUE);
	gtk_widget_destroy(widget);
}

