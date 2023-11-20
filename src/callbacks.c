#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "functions_ets.h"
#include "functions_user.h"
#include "functions_don.h"
#include "functions_request.h"

extern const char *ets_path;
extern const char *ets_by_capacity_path;
extern const char *ets_by_name_path;
extern const char *ets_by_region_path;

extern const char *req_path;
extern const char *req_by_ets_path;
extern const char *req_by_blood_type_path;
extern const char *req_by_date_max_path;

extern const char *activity_path;
char cin[LENGTH];


void
on_editUsersButton_admin_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{

}


void on_editButton_edit_editEts_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget* widget = lookup_widget (button, "idEntry_edit_editEts");
	char id[LENGTH_ETS];
	strcpy (id, gtk_entry_get_text (GTK_ENTRY (widget)));
	char error[100];
	etablissement ets;
	lookup_ets_by_id (id, &ets, error);
	widget = lookup_widget (button, "errorLabelLookupEts_edit_editEts");
	if (strcmp (error, "ets successfully found") == 0)
	{
		gtk_label_set_text (GTK_LABEL (widget), "Veuillez modifier les informations");

		widget = lookup_widget (button, "idMaskedLabel_edit_editEts");
		gtk_label_set_text (GTK_LABEL (widget), id);

		widget = lookup_widget (button, "nameEtsEntry_edit_editEts");
		gtk_entry_set_text (GTK_ENTRY (widget), ets.name);

		widget = lookup_widget (button, "regionComboBox_edit_editEts");
		gtk_combo_box_set_active (GTK_COMBO_BOX (widget), region_toInt (ets.region));

		widget = lookup_widget (button, "adressEntry_edit_editEts");
		gtk_entry_set_text (GTK_ENTRY (widget), ets.address);

		widget = lookup_widget (button, "fromSpinButton_edit_editEts");
		gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget), ets.from_hour);

		widget = lookup_widget (button, "toSpinButton_edit_editEts");
		gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget), ets.to_hour);

		widget = lookup_widget (button, "capacitySpinButton_edit_editEts");
		gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget), ets.capacity);

		widget = lookup_widget (button, "contactEntry_edit_editEts");
		gtk_entry_set_text (GTK_ENTRY (widget), ets.contact);

		if (ets.type == 0)
		{
			widget = lookup_widget (button, "cntsRadioButton_edit_editEts");
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), TRUE);
		}
		else if(ets.type == 1)
		{
			widget = lookup_widget (button, "crtsRadioButton_edit_editEts");
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), TRUE);
		}
	}
	else 
	{		
		on_clearButton_edit_editEts_clicked (button, NULL);
		
		if (strcmp(error, "ets not found") == 0)
			gtk_label_set_text (GTK_LABEL (widget), "Aucun etablissement trouvé avec cet ID.");
		else if (strcmp (error, "couldn't open ets_file") == 0)
			gtk_label_set_text (GTK_LABEL (widget), "Problème d'accés vers la Base de Données.");

		widget = lookup_widget (button, "idMaskedLabel_edit_editEts");
		gtk_label_set_text (GTK_LABEL (widget), "");
	}
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
	char password[LENGTH];
	char role[LENGTH];
	char error[100];
	widget = lookup_widget(button, "cinEntry_authentification");
	strcpy(cin, gtk_entry_get_text (GTK_ENTRY (widget)));
	widget = lookup_widget(button, "passwordEntry_authentification");
	strcpy(password, gtk_entry_get_text (GTK_ENTRY (widget)));
	int check =  authenticate(cin, password, role, error);
	widget = lookup_widget(button, "errorLabel_authentification");
	gtk_label_set_text (GTK_LABEL (widget), "");
	gtk_label_set_text (GTK_LABEL (widget), error);
	if (check == 1)
		if(strcmp (role, "admin") == 0)
		{
			widget = lookup_widget(button, "authentificationWindow");
			gtk_widget_destroy (widget);
			widget = create_adminWindow();
			user admin = get_userInfo (cin);
			GtkWidget *data = lookup_widget (widget, "welcomeUserLabel_admin");
			gchar *string = g_strdup_printf ("Bienvenue admin  : %s, %s", admin.surname, admin.name);
			gtk_label_set_text(GTK_LABEL (data), string);
			g_free (string);
			char activity[LENGTH_ETS] = "connexion";
			add_activity (cin, activity);
			gtk_widget_show (widget); 
		}
		else if (strcmp (role, "medecin") == 0)
		{
			widget = lookup_widget(button, "authentificationWindow");
			gtk_widget_destroy (widget);
			widget = create_gestionDonsWindow();
			GtkWidget *data = lookup_widget (widget, "ets_ajouter_don");
			fill_etsComboBox (GTK_COMBO_BOX (data));
			char activity[LENGTH_ETS] = "connexion";
			add_activity (cin, activity);
			gtk_widget_show (widget);
		}
		else if (strcmp (role, "responsable") == 0)
		{
			widget = lookup_widget(button, "authentificationWindow");
			gtk_widget_destroy (widget);
			widget = create_editBloodRequestWindow();
			char activity[LENGTH_ETS] = "connexion";
			add_activity (cin, activity);
			GtkWidget *data = lookup_widget (widget, "bloodRequestTreeView");
			on_display_bloodRequest_changed (data, NULL);
			gtk_widget_show (widget);
		}
}


void on_settingsButton_admin_enter (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(button, "onHoverLabel_admin");
	gtk_misc_set_alignment (GTK_MISC (widget), 1, 0.5);
	gtk_label_set_text(GTK_LABEL(widget), "Gérer votre Compte");
}


void on_settingsButton_admin_leave (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(button, "onHoverLabel_admin");
	gtk_label_set_text (GTK_LABEL (widget), "");
}


void on_logoutButton_admin_enter (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(button, "onHoverLabel_admin");
	gtk_misc_set_alignment (GTK_MISC (widget), 1, 0.5);
	gtk_label_set_text(GTK_LABEL (widget), "se déconnecter");
}


void on_logoutButton_admin_leave (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(button, "onHoverLabel_admin");
	gtk_label_set_text (GTK_LABEL (widget), "");
}


void on_editEtsButton_admin_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget (button, "adminWindow");
	gtk_widget_destroy (widget);
	widget = create_editEtsWindow();
	on_display_editEts_changed (widget, NULL);
	gtk_widget_show (widget);
}


void
on_statisticsButton_admin_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{

}


void on_logoutButton_settingsUser_enter (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget (button, "onHoverLabel_settingsUser");
	gtk_misc_set_alignment (GTK_MISC (widget), 1, 0.5);
	gtk_label_set_text (GTK_LABEL (widget), "se déconnecter");
}


void on_logoutButton_settingsUser_leave (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(button, "onHoverLabel_settingsUser");
	gtk_label_set_text (GTK_LABEL (widget), "");
}


void on_showPasswordCheckButton_editCin_toggled (GtkWidget *togglebutton, gpointer user_data)
{
	GtkWidget *widget = lookup_widget (togglebutton, "passwordEntry_editCin");
	gtk_entry_set_visibility (GTK_ENTRY (widget), gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(togglebutton)));
}


void on_continueButton_editCin_clicked (GtkWidget *button, gpointer user_data)
{
	char password[LENGTH];
	GtkWidget *widget = lookup_widget (button, "passwordEntry_editCin");
	strcpy (password, gtk_entry_get_text (GTK_ENTRY (widget)));
	user admin = get_userInfo(cin);
	
	if (strcmp (password, admin.password) == 0)
	{
		widget = lookup_widget (button, "editCinPopupWindow");
		GtkWindow *mainWindow = gtk_window_get_transient_for (GTK_WINDOW (widget));
		gtk_widget_destroy (widget);
		widget = create_enterCinPopupWindow();
		gtk_window_set_transient_for (GTK_WINDOW (widget), mainWindow);
		gtk_widget_show (widget);
	}
	else
	{
		gtk_entry_set_text (GTK_ENTRY (widget), "");
		widget = lookup_widget (button, "errorNumberLabel_editCin");
		int nbr_error = 1 + atoi(gtk_label_get_text (GTK_LABEL (widget)));
		if (nbr_error >= 3)
		{
			widget = lookup_widget (button, "editCinPopupWindow");
			GtkWindow *mainWindow = gtk_window_get_transient_for (GTK_WINDOW (widget));
			gtk_widget_destroy (widget);
			gtk_widget_destroy (GTK_WIDGET (mainWindow));
			widget = create_authentificationWindow();
			strcpy (cin, "");
			GtkWidget *data = lookup_widget (widget, "errorLabel_authentification");
			gtk_label_set_text (GTK_LABEL (data), "Pour des raisons de sécurité, vous avez été déconnecté");
			gtk_widget_show (widget);
		}
		else
		{
			widget = lookup_widget (button, "errorNumberLabel_editCin");
			char nbr_errorStr[3];
			sprintf (nbr_errorStr, "%d", nbr_error);
			gtk_label_set_text (GTK_LABEL (widget), nbr_errorStr);
			widget = lookup_widget (button, "errorLabel_editCin");
			char text[LENGTH_ETS];
			sprintf (text, "Tentatives restantes : %d", 3-nbr_error);
			gtk_label_set_text (GTK_LABEL (widget), text);	
		}
	}
}


void on_confirmButton_enterCin_clicked (GtkWidget *button, gpointer user_data)
{
	char new_cin[LENGTH];
	GtkWidget *widget = lookup_widget (button, "cinEntry_enterCin");
	strcpy (new_cin, gtk_entry_get_text (GTK_ENTRY (widget)));
	widget = lookup_widget (button, "errorLabel_enterCin");
	char error[LENGTH_ETS];
	if (strcmp (cin, new_cin) == 0)
	{
		gtk_label_set_text (GTK_LABEL (widget), "Entrez un nouveau CIN.");
	}
	else if (check_cin_user (new_cin, error) != 0)
	{
		gtk_label_set_text (GTK_LABEL (widget), "CIN déja existant.");	
	}
	else
	{
		user admin = get_userInfo (cin);
		delete_user (cin);
		strcpy (cin, new_cin);
		strcpy (admin.cin, new_cin);
		add_user (admin);
		char activity[40] = "modification_cin";
		add_activity (new_cin, activity);
		// modifier tout les cins dans les autres fichiers.txt contenant old_cin !!!!!!!!!
		widget = lookup_widget (button, "enterCinPopupWindow");
		GtkWindow *mainWindow = gtk_window_get_transient_for (GTK_WINDOW (widget));
		gtk_widget_set_sensitive (GTK_WIDGET (mainWindow), TRUE);
		gtk_widget_destroy (widget);
		widget = lookup_widget (GTK_WIDGET (mainWindow), "activityTreeView_settingsUser");
		display_user_activity (widget, cin, "");
	}
}


void on_confirmButton_enterPassword_clicked (GtkWidget *button, gpointer user_data)
{
	char password1[LENGTH];
	char password2[LENGTH];;
	user user = get_userInfo (cin);
	GtkWidget *widget = lookup_widget (button, "passwordEntry_enterPassword");
	strcpy (password1, gtk_entry_get_text (GTK_ENTRY (widget)));
	widget = lookup_widget (button, "confirmPasswordEntry_enterPassword");
	strcpy (password2, gtk_entry_get_text (GTK_ENTRY (widget)));
	if (get_password_difficulty (password1) == 0)
	{
		widget = lookup_widget (button, "errorLabel_enterPassword");
		gtk_label_set_text (GTK_LABEL (widget), "Mot de passe trop faible");
	}
	else if (strcmp (password1, password2) != 0)
	{
		widget = lookup_widget (button, "errorLabel_enterPassword");
		gtk_label_set_text (GTK_LABEL (widget), "Mots de passe non identiques");	
	}
	else if (strcmp (password1, user.password) == 0)
	{
		widget = lookup_widget (button, "errorLabel_enterPassword");
		gtk_label_set_text (GTK_LABEL (widget), "Entrer un nouveau Mot de passe");	
	}
	else
	{
		strcpy (user.password, password1);
		edit_user (user);

		char *activity = "modification_mdp";
		add_activity (user.cin, activity);

		widget = lookup_widget (button, "enterPasswordPopupWindow");
		GtkWindow *mainWindow = gtk_window_get_transient_for (GTK_WINDOW (widget));
		gtk_widget_set_sensitive (GTK_WIDGET (mainWindow), TRUE);
		
		if (strcmp (gtk_window_get_title (mainWindow), "Gérer votre compte") == 0)
		{
			char string[LENGTH_ETS];
			widget = lookup_widget (GTK_WIDGET (mainWindow), "lastEditPasswordLabel_settingsUser");
			get_last_reset_password (cin, string);
			gtk_label_set_text (GTK_LABEL (widget), string);
			widget = lookup_widget (GTK_WIDGET (mainWindow), "activityTreeView_settingsUser");
			display_user_activity (widget , cin, "");
		}
		else if (strcmp (gtk_window_get_title (mainWindow), "Authentification") == 0)
		{
			widget = lookup_widget (GTK_WIDGET (mainWindow), "errorLabel_authentification");
			gtk_label_set_text (GTK_LABEL (widget), "Mot de passe modifié avec succés.");
		}
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
	gtk_entry_set_visibility (GTK_ENTRY (widget), TRUE);
}


void on_showPasswordButton_enterPassword_released (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(button, "passwordEntry_enterPassword");
	gtk_entry_set_visibility (GTK_ENTRY (widget), FALSE);
}


void on_logoutButton_editEts_enter (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(button, "onHoverLabel_editEts");
	gtk_misc_set_alignment (GTK_MISC (widget), 1, 0.5);
	gtk_label_set_text (GTK_LABEL (widget), "se déconnecter");
}


void on_logoutButton_editEts_leave (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(button, "onHoverLabel_editEts");
	gtk_label_set_text(GTK_LABEL(widget), "");
}


void on_advancedSettingsButton_editEts_clicked (GtkWidget *button, gpointer user_data)
{

}


void on_cancelButton_add_editEts_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget (button, "nameEtsEntry_add_editEts");
	gtk_entry_set_text (GTK_ENTRY (widget), "");

	widget = lookup_widget (button, "regionComboBox_add_editEts");
	gtk_combo_box_set_active (GTK_COMBO_BOX (widget), -1);

	widget = lookup_widget (button, "adressEntry_add_editEts");
	gtk_entry_set_text (GTK_ENTRY (widget), "");

	widget = lookup_widget (button, "fromSpinButton_add_editEts");
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget), 8);

	widget = lookup_widget (button, "toSpinButton_add_editEts");
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget), 14);

	widget = lookup_widget (button, "capacitySpinButton_add_editEts");
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget), 0);

	widget = lookup_widget (button, "contactEntry_add_editEts");
	gtk_entry_set_text (GTK_ENTRY (widget), "");

	widget = lookup_widget (button, "cntsRadioButton_add_editEts");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), TRUE);

	widget = lookup_widget (button, "errorLabel_add_editEts");
	gtk_label_set_text (GTK_LABEL (widget), "");
}


void on_addButton_add_editEts_clicked (GtkWidget *button, gpointer user_data)
{
	etablissement new;
	char error[100];

	GtkWidget *widget = lookup_widget (button, "nameEtsEntry_add_editEts");
	strcpy (new.name, gtk_entry_get_text (GTK_ENTRY (widget)));
	
	widget = lookup_widget (button, "regionComboBox_add_editEts");
	if (gtk_combo_box_get_active (GTK_COMBO_BOX (widget)) >= 0)
		strcpy (new.region, gtk_combo_box_get_active_text (GTK_COMBO_BOX (widget)));	

	widget = lookup_widget (button, "adressEntry_add_editEts");
	strcpy (new.address, gtk_entry_get_text (GTK_ENTRY (widget)));
	
	widget = lookup_widget (button, "fromSpinButton_add_editEts");
	new.from_hour = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (widget));

	widget = lookup_widget (button, "toSpinButton_add_editEts");
	new.to_hour = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (widget));

	widget = lookup_widget (button, "capacitySpinButton_add_editEts");
	new.capacity = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (widget));

	widget = lookup_widget (button, "contactEntry_add_editEts");
	strcpy (new.contact, gtk_entry_get_text (GTK_ENTRY (widget)));

	widget = lookup_widget (button, "cntsRadioButton_add_editEts");
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
		new.type = 0;
	else
		new.type = 1;

	widget = lookup_widget (button, "errorLabel_add_editEts");
	if (strlen (new.name) == 0 || region_toInt (new.region) == -1 || strlen(new.address) == 0 || new.capacity == 0 || strlen(new.contact) == 0)
	{
		gtk_label_set_text (GTK_LABEL (widget), "Veuillez remplir tous les champs.");	
	}
	else if (is_all_alpha (new.name) == 0 || has_double_whitespace (new.name) == 1)
	{
		gtk_label_set_text (GTK_LABEL (widget), "Seulement les lettres autorisées dans le champ nom.");
	}
	else if (is_all_alnum (new.address) == 0 || has_double_whitespace (new.address) == 1)
	{
		gtk_label_set_text (GTK_LABEL (widget), "Champ addresse contient des caractères invalides.");	
	}
	else if (is_all_digit (new.contact) == 0)
	{
		gtk_label_set_text (GTK_LABEL (widget), "Seulement 0 .. 9 autorisés dans le champ contact.");
	}
	else 
	{
		whitespace_to_underscore (new.name);
		whitespace_to_underscore (new.region);
		whitespace_to_underscore (new.address);
		new = generate_id_ets (new);
		add_ets (new, error); 
		on_cancelButton_add_editEts_clicked (widget, NULL);
		widget = lookup_widget (button, "editEtsWindow");
		GtkWidget *popup = create_confirmationPopupWindow();
		gtk_window_set_transient_for (GTK_WINDOW (popup), GTK_WINDOW (widget));
		gtk_widget_set_sensitive (widget, FALSE);
		widget = lookup_widget (popup, "confirmationLabel");
		gtk_label_set_text (GTK_LABEL (widget), "Etablissement ajouté avec succés.");
		gtk_widget_show (popup);
	}
}


void on_etsTreeView_row_activated (GtkWidget *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data)
{
	gchar *id;
	char error[100];
	GtkWidget *widget = lookup_widget (treeview, "deleteCheckButton_manage_editEts");
	GtkTreeModel *model = gtk_tree_view_get_model (GTK_TREE_VIEW (treeview));
	GtkTreeIter iter;
	if (gtk_tree_model_get_iter (model, &iter, path))
		gtk_tree_model_get (GTK_TREE_MODEL (model), &iter, ID_ETS, &id, -1);
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
	{
		widget = lookup_widget (treeview, "editEtsWindow");
		GtkWidget *popup = create_deletePopupWindow();
		gtk_window_set_transient_for (GTK_WINDOW (popup), GTK_WINDOW (widget));
		gtk_widget_set_sensitive (widget, FALSE);
		widget = lookup_widget (popup, "dataLabel_deletePopup");
		gtk_label_set_text (GTK_LABEL (widget), id);
		gtk_widget_show (popup);
	}	
	else
	{
		widget = lookup_widget (treeview, "idEntry_edit_editEts");
		gtk_entry_set_text (GTK_ENTRY (widget), id);
		on_editButton_edit_editEts_clicked (widget, NULL);
		widget = lookup_widget (treeview, "notebook_editEts");
		gtk_notebook_set_current_page (GTK_NOTEBOOK (widget), 2);
	}
	g_free (id);
}


void on_regionCheckButton_editEts_toggled (GtkWidget *togglebutton, gpointer user_data)
{
	GtkWidget *widget = lookup_widget (togglebutton, "regionComboBox_manage_editEts");
	gtk_widget_set_sensitive (widget, gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton)));
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton)))
		gtk_widget_show (widget);
	else
	{
		gtk_widget_hide (widget);
		gtk_combo_box_set_active (GTK_COMBO_BOX (widget), -1);
	}
}


void on_capacityCheckButton_editEts_toggled (GtkWidget *togglebutton, gpointer user_data)
{
	GtkWidget *widget = lookup_widget (togglebutton, "capacitySpinButton_manage_editEts");
	gtk_widget_set_sensitive (widget, gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton)));
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton)))
		gtk_widget_show (widget);
	else
	{
		gtk_widget_hide (widget);
		gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget), 0);
	}
}


void on_resetFiltersButton_manage_editEts_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget (button, "regionCheckButton_editEts");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), FALSE);
	on_regionCheckButton_editEts_toggled (widget, NULL);
	widget = lookup_widget (button, "capacityCheckButton_editEts");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), FALSE);
	on_capacityCheckButton_editEts_toggled (widget, NULL);
	widget = lookup_widget (button, "nameEtsEntry_manage_editEts");
	gtk_entry_set_text (GTK_ENTRY (widget), "");
	on_display_editEts_changed (widget, NULL);
}


void on_confirmButton_edit_editEts_clicked (GtkWidget *button, gpointer user_data)
{
	char id[LENGTH_ETS];
	GtkWidget *widget = lookup_widget (button, "idMaskedLabel_edit_editEts");
	strcpy (id, gtk_label_get_text (GTK_LABEL (widget)));
	
	widget = lookup_widget (button, "errorLabelLookupEts_edit_editEts");
	if (strlen (id) == 0)
	{
		gtk_label_set_text (GTK_LABEL (widget), "Aucun Etablissement à modifier.");	
	}
	else 
	{
		etablissement ets;
		char error[100];
		lookup_ets_by_id (id, &ets, error);

		if (strcmp (error, "ets not found") == 0)
		{
			gtk_label_set_text (GTK_LABEL (widget), "Cet Etablissement a été supprimé.");
			on_clearButton_edit_editEts_clicked (widget, NULL);		
		}
		else if (strcmp (error, "couldn't open ets_file") == 0)
		{
			gtk_label_set_text (GTK_LABEL (widget), "Problème d'accés vers la Base de Données.");
			on_clearButton_edit_editEts_clicked (widget, NULL);	
		}
		else
		{
			widget = lookup_widget (button, "nameEtsEntry_edit_editEts");
			strcpy (ets.name, gtk_entry_get_text (GTK_ENTRY (widget)));

			widget = lookup_widget (button, "regionComboBox_edit_editEts");
			if (gtk_combo_box_get_active (GTK_COMBO_BOX (widget)) >= 0)
				strcpy (ets.region, gtk_combo_box_get_active_text (GTK_COMBO_BOX (widget)));

			widget = lookup_widget (button, "adressEntry_edit_editEts");
			strcpy (ets.address, gtk_entry_get_text (GTK_ENTRY (widget)));

			widget = lookup_widget (button, "fromSpinButton_edit_editEts");
			ets.from_hour = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (widget));

			widget = lookup_widget (button, "toSpinButton_edit_editEts");
			ets.to_hour = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (widget));

			widget = lookup_widget (button, "capacitySpinButton_edit_editEts");
			ets.capacity = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (widget));

			widget = lookup_widget (button, "contactEntry_edit_editEts");
			strcpy (ets.contact, gtk_entry_get_text (GTK_ENTRY (widget)));

			widget = lookup_widget (button, "cntsRadioButton_edit_editEts");
			if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget))) 
				ets.type = 0;
			else
				ets.type = 1;

			widget = lookup_widget (button, "errorLabeleditEts_edit_editEts");
			if (strlen (ets.name) == 0 || region_toInt (ets.region) == -1 || strlen(ets.address) == 0 || ets.capacity == 0 || strlen(ets.contact) == 0)
			{
				gtk_label_set_text (GTK_LABEL (widget), "Veuillez remplir tous les champs.");	
			}
			else if (is_all_alpha (ets.name) == 0 || has_double_whitespace (ets.name) == 1)
			{
				gtk_label_set_text (GTK_LABEL (widget), "Seulement les lettres autorisées dans le champ nom.");
			}
			else if (is_all_alnum (ets.address) == 0 || has_double_whitespace (ets.address) == 1)
			{
				gtk_label_set_text (GTK_LABEL (widget), "Champ addresse contient des caractères invalides.");	
			}
			else if (is_all_digit (ets.contact) == 0)
			{
				gtk_label_set_text (GTK_LABEL (widget), "Seulement 0 .. 9 autorisés dans le champ contact.");
			}
			else
			{
				whitespace_to_underscore (ets.name);
				whitespace_to_underscore (ets.region);
				whitespace_to_underscore (ets.address);
				edit_ets (ets, error);

				on_clearButton_edit_editEts_clicked (widget, NULL);

				widget = lookup_widget (button, "idMaskedLabel_edit_editEts");	
				gtk_label_set_text (GTK_LABEL (widget), "");

				widget = lookup_widget (button, "idEntry_edit_editEts");
				gtk_entry_set_text (GTK_ENTRY (widget), "");

				widget = lookup_widget (button, "errorLabelLookupEts_edit_editEts");
				gtk_label_set_text (GTK_LABEL (widget), "");

				widget = lookup_widget (button, "editEtsWindow");
				GtkWidget *popup = create_confirmationPopupWindow();
				gtk_window_set_transient_for (GTK_WINDOW (popup), GTK_WINDOW (widget));
				gtk_widget_set_sensitive (widget, FALSE);
				widget = lookup_widget (popup, "confirmationLabel");
				gtk_label_set_text (GTK_LABEL (widget), "Etablissement modifié avec succés.");

				gtk_widget_show (popup);		
			}
				
			
		}
	}			
}


void on_cancelButton_edit_editEts_clicked (GtkWidget *button, gpointer user_data)
{
	char id[LENGTH_ETS];
	GtkWidget *widget = lookup_widget (button, "idMaskedLabel_edit_editEts");
	strcpy (id, gtk_label_get_text (GTK_LABEL (widget)));

	widget = lookup_widget (button, "errorLabelLookupEts_edit_editEts");
	if (strlen (id) == 0)
	{
		gtk_label_set_text (GTK_LABEL (widget), "Aucun Etablissement à modifier.");
		return;
	}
	
	etablissement ets;
	char error[100];
	lookup_ets_by_id (id, &ets, error);


	if (strcmp (error, "ets not found") == 0)
	{
		gtk_label_set_text (GTK_LABEL (widget), "Cet Etablissement a été supprimé.");
	}
	else if (strcmp (error, "couldn't open ets_file") == 0)
	{
		gtk_label_set_text (GTK_LABEL (widget), "Problème d'accés vers la Base de Données.");		
	}
	else if (strcmp (error, "ets successfully found") == 0)
	{
		widget = lookup_widget (button, "idEntry_edit_editEts");
		gtk_entry_set_text (GTK_ENTRY (widget), id);
		
		widget = lookup_widget (button, "nameEtsEntry_edit_editEts");
		gtk_entry_set_text (GTK_ENTRY (widget), ets.name);

		widget = lookup_widget (button, "regionComboBox_edit_editEts");
		gtk_combo_box_set_active (GTK_COMBO_BOX (widget), region_toInt (ets.region));

		widget = lookup_widget (button, "adressEntry_edit_editEts");
		gtk_entry_set_text (GTK_ENTRY (widget), ets.address);

		widget = lookup_widget (button, "fromSpinButton_edit_editEts");
		gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget), ets.from_hour);

		widget = lookup_widget (button, "toSpinButton_edit_editEts");
		gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget), ets.to_hour);

		widget = lookup_widget (button, "capacitySpinButton_edit_editEts");
		gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget), ets.capacity);

		widget = lookup_widget (button, "contactEntry_edit_editEts");
		gtk_entry_set_text (GTK_ENTRY (widget), ets.contact);
		if (ets.type == 0)
		{
			widget = lookup_widget (button, "cntsRadioButton_edit_editEts");
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), TRUE);
		}
		else if (ets.type == 1)
		{
			widget = lookup_widget (button, "crtsRadioButton_edit_editEts");
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), TRUE);
		}
	}		
}


void on_continueButton_enterCin_resetPassword_clicked (GtkWidget *button, gpointer user_data)
{
	char error[100];
	GtkWidget *widget = lookup_widget ( button, "cinEntry_enterCin_resetPassword");
	strcpy (cin, gtk_entry_get_text (GTK_ENTRY (widget)));
	if (check_cin_user (cin, error) == 0)
	{
		gtk_entry_set_text (GTK_ENTRY (widget), "");
		widget = lookup_widget (button, "errorLabel_enterCin_resetPassword");
		gtk_label_set_text (GTK_LABEL (widget), "");
		gtk_label_set_text (GTK_LABEL (widget), error);
	}
	else
	{
		widget = lookup_widget (button, "enterCin_resetPasswordPopupWindow");
		GtkWindow *mainWindow = gtk_window_get_transient_for (GTK_WINDOW (widget));
		gtk_widget_destroy (widget);
		widget = create_editPasswordPopupWindow();
		gtk_window_set_transient_for (GTK_WINDOW (widget), mainWindow);
		user user = get_userInfo (cin);
		GtkWidget *data = lookup_widget (widget, "secretQuestionLabel_editPassword");
		gtk_label_set_text (GTK_LABEL (data), user.question);
		gtk_widget_show (widget);
	}
}


void on_confirmButton_deletePopup_clicked (GtkWidget *button, gpointer user_data)
{
	char id[LENGTH_ETS];
	char error[100];
	GtkWidget *widget = lookup_widget (button, "dataLabel_deletePopup");
	strcpy (id, gtk_label_get_text (GTK_LABEL (widget)));
	widget = lookup_widget (button, "confirmationLabel_deletePopup");
	if (strstr (gtk_label_get_text (GTK_LABEL (widget)), "Etablissement") != NULL)
	{
		delete_ets (ets_path, id, error);
		widget = lookup_widget (button, "deletePopupWindow");
		GtkWindow *mainWindow = gtk_window_get_transient_for (GTK_WINDOW (widget));
		gtk_widget_set_sensitive (GTK_WIDGET (mainWindow), TRUE);

		widget = lookup_widget (GTK_WIDGET (mainWindow), "statLabel_manage_editEts");
		on_display_editEts_changed (widget, NULL);
		if (strcmp (error, "ets successfully deleted") == 0)
			gtk_label_set_text (GTK_LABEL (widget), "Etablissement supprimé avezc succés.");
		else if (strcmp (error, "ets not found") == 0)
			gtk_label_set_text (GTK_LABEL (widget), "Un problème est survenue lors de la suppression.");
		else
			gtk_label_set_text (GTK_LABEL (widget), "Problème d'accés vers la base de données.");
	}
	else if (strstr (gtk_label_get_text (GTK_LABEL (widget)), "Demande") != NULL)
	{
		delete_req (req_path, id, error);

		widget = lookup_widget (button, "deletePopupWindow");
		GtkWindow *mainWindow = gtk_window_get_transient_for (GTK_WINDOW (widget));
		gtk_widget_set_sensitive (GTK_WIDGET (mainWindow), TRUE);

		widget = lookup_widget (GTK_WIDGET (mainWindow), "statLabel1_manage_bloodRequest");
		on_display_bloodRequest_changed (widget, NULL);
		if (strcmp (error, "request successfully deleted") == 0)
			gtk_label_set_text (GTK_LABEL (widget), "Demande de sang supprimée avezc succés.");
		else if (strcmp (error, "request not found") == 0)
			gtk_label_set_text (GTK_LABEL (widget), "Un problème est survenue lors de la suppression.");
		else
			gtk_label_set_text (GTK_LABEL (widget), "Problème d'accés vers la base de données.");
	}
	widget = lookup_widget (button, "deletePopupWindow");
	gtk_widget_destroy (widget);
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


void on_editPasswordButton_authentification_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget *mainWindow = lookup_widget (button, "authentificationWindow");
	GtkWidget *popup = create_enterCin_resetPasswordPopupWindow();
	gtk_window_set_transient_for (GTK_WINDOW (popup), GTK_WINDOW (mainWindow));
	gtk_widget_set_sensitive (mainWindow, FALSE);

	gtk_widget_show (popup);
}


void on_editCinButton_settingsUser_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget *mainWindow = lookup_widget (button, "settingsUserWindow");
	gtk_widget_set_sensitive (mainWindow, FALSE);
	GtkWidget *popup = create_editCinPopupWindow();
	gtk_window_set_transient_for (GTK_WINDOW (popup), GTK_WINDOW (mainWindow));
	gtk_widget_show (popup);
}


void on_editPasswordButton_settingsUser_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget *mainWindow = lookup_widget (button, "settingsUserWindow");
	gtk_widget_set_sensitive (mainWindow, FALSE);

	GtkWidget *popup = create_editPasswordPopupWindow();
	gtk_window_set_transient_for (GTK_WINDOW (popup), GTK_WINDOW (mainWindow));

	GtkWidget *widget = lookup_widget (popup, "secretQuestionLabel_editPassword");
	user user = get_userInfo(cin);
	gchar *string = g_strdup_printf ("%s ?", user.question);
	gtk_label_set_text (GTK_LABEL (widget), string);
	g_free (string);

	gtk_widget_show (popup);
}


void on_settingsButton_editEts_enter (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget (button, "onHoverLabel_editEts");
	gtk_misc_set_alignment (GTK_MISC (widget), 1, 0.5);
	gtk_label_set_text (GTK_LABEL (widget), "Gérer votre Compte");
}


void on_settingsButton_editEts_leave (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget(button, "onHoverLabel_editEts");
	gtk_label_set_text(GTK_LABEL(widget), "");
}


void on_mainMenuButton_settingsUser_enter (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget (button, "onHoverLabel_settingsUser");
	gtk_misc_set_alignment (GTK_MISC (widget), 0, 0.5);
	gtk_label_set_text (GTK_LABEL (widget), "Menu Principal");
}


void on_mainMenuButton_settingsUser_leave (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget (button, "onHoverLabel_settingsUser");
	gtk_label_set_text (GTK_LABEL (widget), "");
}


void on_resetButton_settingsUser_clicked (GtkWidget *button, gpointer user_data)
{
	user user = get_userInfo(cin);

	GtkWidget *widget = lookup_widget (button, "firstNameEntry_settingsUser");
	gtk_entry_set_text (GTK_ENTRY (widget), user.name);

	widget = lookup_widget (button, "lastNameEntry_settingsUser");
	gtk_entry_set_text (GTK_ENTRY (widget), user.surname);

	widget = lookup_widget (button, "telephoneEntry_settingsUser");
	gtk_entry_set_text (GTK_ENTRY (widget), user.tel);

	if (user.sex == 0)
		{
			widget = lookup_widget (button, "maleRadioButton_settingsUser");
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), TRUE);
		}
	else if (user.sex == 1)
	{
		widget = lookup_widget (button, "femaleRadioButton_settingsUser");
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), TRUE);
	}

	widget = lookup_widget (button, "etsComboBox_settingsUser");
	gtk_combo_box_set_active (GTK_COMBO_BOX (widget), ets_toInt (user.est));
}


void on_confirmButton_settingsUser_clicked (GtkWidget *button, gpointer user_data)
{
	user user = get_userInfo(cin);

	GtkWidget *widget = lookup_widget (button, "firstNameEntry_settingsUser");
	strcpy (user.name, gtk_entry_get_text (GTK_ENTRY (widget)));

	widget = lookup_widget (button, "lastNameEntry_settingsUser");
	strcpy (user.surname, gtk_entry_get_text (GTK_ENTRY (widget)));

	widget = lookup_widget (button, "telephoneEntry_settingsUser");
	strcpy (user.tel, gtk_entry_get_text (GTK_ENTRY (widget)));

	widget = lookup_widget (button, "maleRadioButton_settingsUser");
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
		user.sex = 0;
	else
		user.sex = 1;

	widget = lookup_widget (button, "etsComboBox_settingsUser");
	strcpy (user.est, gtk_combo_box_get_active_text (GTK_COMBO_BOX (widget)));
	edit_user (user);
}


void on_continueButton_editPassword_clicked (GtkWidget *button, gpointer user_data)
{
	char answer[LENGTH];
	user User = get_userInfo(cin);
	GtkWidget *widget = lookup_widget (button, "secretAnswerEntry_editPassword");
	strcpy (answer, gtk_entry_get_text (GTK_ENTRY (widget)));
	if (strcmp (answer, User.answer) == 0)
	{
		widget = lookup_widget (button, "editPasswordPopupWindow");
		GtkWindow *mainWindow = gtk_window_get_transient_for (GTK_WINDOW (widget));
		gtk_widget_destroy (widget);
		widget = create_enterPasswordPopupWindow();
		gtk_window_set_transient_for (GTK_WINDOW (widget), mainWindow);
		gtk_widget_show (widget);
	}
	else
	{
		gtk_entry_set_text (GTK_ENTRY (widget), "");
		int nbr_error = 1;
		widget = lookup_widget (button, "errorNumberLabel_editPassword");
		nbr_error += atoi(gtk_label_get_text (GTK_LABEL (widget)));
		if (nbr_error >= 3)
		{
			widget = lookup_widget (button, "editPasswordPopupWindow");
			GtkWindow *mainWindow = gtk_window_get_transient_for (GTK_WINDOW (widget));
			gtk_widget_destroy (widget);
			gtk_widget_destroy (GTK_WIDGET (mainWindow));
			widget = create_authentificationWindow();
			strcpy (cin, "");
			GtkWidget *data = lookup_widget (widget, "errorLabel_authentification");
			gtk_label_set_text (GTK_LABEL (data), "Pour des raisons de sécurité, vous avez été déconnecté");
			gtk_widget_show (widget);
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


void on_cancelPopup_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = gtk_widget_get_toplevel(button);
	GtkWindow *mainWindow = gtk_window_get_transient_for (GTK_WINDOW (widget));
	gtk_widget_set_sensitive (GTK_WIDGET (mainWindow), TRUE);
	gtk_widget_destroy (widget);
}


void on_logoutButton_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget *mainWindow = gtk_widget_get_toplevel (button);
	GtkWidget *popup = create_logoutPopupWindow();
	gtk_window_set_transient_for (GTK_WINDOW(popup), GTK_WINDOW (mainWindow));
	gtk_widget_set_sensitive (mainWindow, FALSE);
	gtk_widget_show (popup);
}


void on_leaveButton_logout_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget *popup = lookup_widget (button, "logoutPopupWindow");
	GtkWindow *mainWindow = gtk_window_get_transient_for (GTK_WINDOW (popup));
	gtk_widget_destroy (popup);
	gtk_widget_destroy (GTK_WIDGET (mainWindow));
	popup = create_authentificationWindow();
	strcpy (cin, "");
	gtk_widget_show (popup);	
}


void on_leaveButton_mainMenu_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget *popup = lookup_widget (button, "mainMenuPopupWindow");
	GtkWindow *mainWindow = gtk_window_get_transient_for (GTK_WINDOW (popup));
	gtk_widget_destroy (popup);
	gtk_widget_destroy (GTK_WIDGET (mainWindow));

	user user = get_userInfo (cin);
	if (strcmp (user.role, "admin") == 0)
	{
		popup = create_adminWindow();

		gchar *string = g_strdup_printf ("Bienvenue admin : %s, %s", user.surname, user.name);
		GtkWidget *data = lookup_widget (popup, "welcomeUserLabel_admin");
		gtk_label_set_text (GTK_LABEL (data), string);
		g_free (string);

		gtk_widget_show (popup);
	}
	else if (strcmp (user.role, "responsable") == 0)
	{
		popup = create_editBloodRequestWindow();
		on_display_bloodRequest_changed (popup, NULL);
		gtk_widget_show (popup);	
	}
	else if (strcmp (user.role, "medecin") == 0)
	{
		popup = create_gestionDonsWindow();

		GtkWidget *data = lookup_widget (popup, "ets_ajouter_don");
		fill_etsComboBox (GTK_COMBO_BOX (data));

		gtk_widget_show (popup);
	}
}


void on_mainMenuButton_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget *mainWindow = gtk_widget_get_toplevel (GTK_WIDGET (button));
	gtk_widget_set_sensitive (mainWindow, FALSE);
	GtkWidget *popup = create_mainMenuPopupWindow();
	gtk_window_set_transient_for (GTK_WINDOW (popup), GTK_WINDOW (mainWindow));
	gtk_widget_show (popup);
}


void on_settingsButton_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget *mainWindow = gtk_widget_get_toplevel (button);
	GtkWidget *popup = create_settingsPopupWindow();
	gtk_window_set_transient_for (GTK_WINDOW (popup), GTK_WINDOW (mainWindow));
	gtk_widget_set_sensitive (mainWindow, FALSE);
	gtk_widget_show (popup);	
}


void on_leaveButton_settings_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget (button, "settingsPopupWindow");
	GtkWindow *mainWindow = gtk_window_get_transient_for (GTK_WINDOW (widget));
	gtk_widget_destroy (widget);
	gtk_widget_destroy (GTK_WIDGET (mainWindow));
	
	user user = get_userInfo(cin);
	
	widget = create_settingsUserWindow();

	GtkWidget *data = lookup_widget(widget, "firstNameEntry_settingsUser");
	gtk_entry_set_text(GTK_ENTRY(data), user.name);

	data = lookup_widget(widget, "lastNameEntry_settingsUser");
	gtk_entry_set_text(GTK_ENTRY(data), user.surname);

	data = lookup_widget(widget, "telephoneEntry_settingsUser");
	gtk_entry_set_text(GTK_ENTRY(data), user.tel);

	if (user.sex == 0)
	{
		data = lookup_widget (widget, "maleRadioButton_settingsUser");
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (data), TRUE);
	}
	else if (user.sex == 1)
	{
		data = lookup_widget (widget, "femaleRadioButton_settingsUser");
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (data), TRUE);
	}

	data = lookup_widget (widget, "etsComboBox_settingsUser");
	fill_etsComboBox (GTK_COMBO_BOX (data));

	if (ets_toInt (user.est) >= 0)
		gtk_combo_box_set_active (GTK_COMBO_BOX (data), ets_toInt (user.est));

	data = lookup_widget (widget, "activityTreeView_settingsUser");
	display_user_activity (data, cin, "");

	data = lookup_widget (widget, "lastEditPasswordLabel_settingsUser");
	char string[LENGTH_ETS];
	get_last_reset_password (cin, string);
	gtk_label_set_text (GTK_LABEL (data), string);

	gtk_widget_show(widget);
}


gboolean on_confirmation_key_press_event (GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
	if (event->keyval == '\r' || event->keyval == '\n')
	{
		on_confirmationButton_clicked (widget, user_data);
		return TRUE;
	}
  return FALSE;
}


void on_confirmationButton_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget *popup = lookup_widget (button, "confirmationPopupWindow");
	GtkWindow *mainWindow = gtk_window_get_transient_for (GTK_WINDOW (popup));
	gtk_widget_set_sensitive (GTK_WIDGET (mainWindow), TRUE);
	gtk_widget_destroy (popup);
}



void on_ajouter_don_clicked (GtkWidget *button, gpointer user_data)
{
	don nouveau;

	GtkWidget *widget = lookup_widget (button, "entry1");
	strcpy (nouveau.cin, gtk_entry_get_text (GTK_ENTRY (widget)));

	widget = lookup_widget (button, "sang");
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
		nouveau.types_don[0] = 1;
	else
		nouveau.types_don[0] = 0;

	widget = lookup_widget (button, "plaq");
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
		nouveau.types_don[1] = 1;
	else
		nouveau.types_don[1] = 0;

	widget = lookup_widget (button, "plasma");
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
		nouveau.types_don[2] = 1;
	else
		nouveau.types_don[2] = 0;

	widget = lookup_widget (button, "groupe_sanguin_ajouter_don");
	strcpy (nouveau.groupe_sanguin, gtk_combo_box_get_active_text (GTK_COMBO_BOX (widget)));

	widget = lookup_widget (button, "plus");
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
		nouveau.rhesus = 1;
	else 
		nouveau.rhesus = 0;

	widget = lookup_widget (button, "spinbutton1");
	nouveau.quantite = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (widget));

	widget = lookup_widget (button, "ets_ajouter_don");
	strcpy (nouveau.ets, gtk_combo_box_get_active_text (GTK_COMBO_BOX (widget)));

	widget = lookup_widget (button, "spinbutton2");
	nouveau.jour = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (widget));

	widget = lookup_widget (button, "spinbutton3");
	nouveau.mois = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (widget));

	widget = lookup_widget (button, "spinbutton4");
	nouveau.an = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (widget));

	nouveau = generate_id_don (nouveau);
	char error [100];
	add_don (nouveau, error);
}

void on_display_editEts_changed (GtkWidget *button, gpointer user_data)
{
	char region[LENGTH_ETS];
	strcpy (region, "");
	int capacity_min = -1;
	char name[LENGTH_ETS];
	strcpy (name, "");
	char error[100];
	int nbr = 0;

	GtkWidget *widget = lookup_widget (button, "regionCheckButton_editEts");
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
	{
		widget = lookup_widget (button, "regionComboBox_manage_editEts");
		strcpy (region, gtk_combo_box_get_active_text (GTK_COMBO_BOX (widget)));
	}

	widget = lookup_widget (button, "capacityCheckButton_editEts");
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
	{
		widget = lookup_widget (button, "capacitySpinButton_manage_editEts");
		capacity_min = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (widget));
	}

	widget = lookup_widget (button, "nameEtsEntry_manage_editEts");
	strcpy (name, gtk_entry_get_text (GTK_ENTRY (widget)));

	filter_ets_by_capacity (ets_path, capacity_min, error);
	filter_ets_by_name (ets_by_capacity_path, name, error);
	filter_ets_by_region (ets_by_name_path, region, error);
	
	widget = lookup_widget (button, "etsTreeView");	
	display_ets (widget, ets_by_region_path, &nbr);
	widget = lookup_widget (button, "statLabel_manage_editEts");
	gchar *string = g_strdup_printf ("Le nombre d'etablissement résultant est : %d .", nbr);
	gtk_label_set_text (GTK_LABEL (widget), string);
	g_free (string);	
}




void on_logoutButton_bloodRequest_enter (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget (button, "onHoverLabel_bloodRequest");
	gtk_label_set_text (GTK_LABEL (widget), "se déconnecter");
}


void on_cancelButton_add_bloodRequest_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget (button, "etsEntry_add_bloodRequest");
	gtk_entry_set_text (GTK_ENTRY (widget), "");

	widget = lookup_widget (button, "bloodGroupComboBox_add_bloodRequest");
	gtk_combo_box_set_active (GTK_COMBO_BOX (widget), -1);

	widget = lookup_widget (button, "plusRadioButton_add_bloodRequest");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), TRUE);

	widget = lookup_widget (button, "quantitySpinButton_add_bloodRequest");
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget), 0);

	widget = lookup_widget (button, "calendar_add_bloodRequest");
	gtk_calendar_select_month (GTK_CALENDAR (widget), 0, 2024);
}


void on_addButton_add_bloodRequest_clicked (GtkWidget *button, gpointer user_data)
{
	request new;

	GtkWidget *widget = lookup_widget (button, "etsEntry_add_bloodRequest");
	strcpy (new.ets, gtk_entry_get_text (GTK_ENTRY (widget)));

	widget = lookup_widget (button, "bloodGroupComboBox_add_bloodRequest");
	strcpy (new.bloodType.bloodGroup, gtk_combo_box_get_active_text (GTK_COMBO_BOX (widget)));

	widget = lookup_widget (button, "plusRadioButton_add_bloodRequest");
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
		new.bloodType.rhesus = 1;
	else
		new.bloodType.rhesus = 0;

	widget = lookup_widget (button, "quantitySpinButton_add_bloodRequest");
	new.quantity = gtk_spin_button_get_value (GTK_SPIN_BUTTON (widget));

	widget = lookup_widget (button, "calendar_add_bloodRequest");
	gtk_calendar_get_date (GTK_CALENDAR (widget), &new.date.y, &new.date.m, &new.date.d);

	new = generate_id_req (new);
	char error[100];

	widget = lookup_widget (button, "errorLabel_add_bloodRequest");
	if (is_all_alpha (new.ets) == 0)
	{
		gtk_label_set_text (GTK_LABEL (widget), "Seulement les lettres autorisées dans le champ etablissement.");
	}
	else
	{
		whitespace_to_underscore (new.ets);
		add_req (new, error);

		if (strcmp (error, "request successfully added") == 0)
		{
			on_cancelButton_add_bloodRequest_clicked (widget, NULL);

			GtkWidget *popup = create_confirmationPopupWindow();
			widget = lookup_widget (button, "editBloodRequestWindow");
			gtk_window_set_transient_for (GTK_WINDOW (popup), GTK_WINDOW (widget));
			gtk_widget_set_sensitive (widget, FALSE);

			widget = lookup_widget (popup, "confirmationLabel");
			gtk_label_set_text (GTK_LABEL (widget), "Demande ajoutée avec succés.");

			gtk_widget_show (popup);
		}
		else if (strcmp (error, "couldn't open request_file") == 0)
			gtk_label_set_text (GTK_LABEL (widget), "Problème d'accés vers la Base de Données.");
	}
}


void on_display_bloodRequest_changed (GtkWidget *button, gpointer user_data)
{
	char bloodType[5] = "";
	char ets[LENGTH_ETS] = "";
	char date[20] = "";
	char error[100];
	float quantity;
	int nbr;
		
	GtkWidget *widget = lookup_widget (button, "bloodTypeCheckButton_bloodRequest");
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
	{
		widget = lookup_widget (button, "bloodTypeComboBox_manage_bloodRequest");
		strcpy (bloodType, gtk_combo_box_get_active_text (GTK_COMBO_BOX (widget)));
	}
		
	widget = lookup_widget (button, "dateCheckButton_bloodRequest");
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
	{
		widget = lookup_widget (button, "dateEntry_manage_bloodRequest");
		strcpy (date, gtk_entry_get_text (GTK_ENTRY (widget)));
	}
		
	widget = lookup_widget (button, "etsEntry_manage_bloodRequest");
	strcpy (ets, gtk_entry_get_text (GTK_ENTRY (widget)));
		
	filter_req_by_blood_type (req_path, bloodType, error);
	filter_req_by_ets (req_by_blood_type_path, ets, error);
	filter_req_by_date_max (req_by_ets_path, date, error);
			
	widget = lookup_widget (button, "bloodRequestTreeView");	
	display_req (widget, req_by_date_max_path, &quantity, &nbr);

	widget = lookup_widget (button, "statLabel1_manage_bloodRequest");
	gchar *string1 = g_strdup_printf ("La quantité totale de sang demandée est : %.2f ", quantity);
	gtk_label_set_text (GTK_LABEL (widget), string1);

	widget = lookup_widget (button, "statLabel2_manage_bloodRequest");
	gchar *string2 = g_strdup_printf ("Le nombre de demandes total est : %d ", nbr);
	gtk_label_set_text (GTK_LABEL (widget), string2);

	g_free (string1);
	g_free (string2);	
}


void on_bloodRequestTreeView_row_activated (GtkWidget *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data)
{
	gchar *id;
	char error[100];
	GtkWidget *widget = lookup_widget (treeview, "deleteCheckButton_manage_bloodRequest");
	GtkTreeModel *model = gtk_tree_view_get_model (GTK_TREE_VIEW (treeview));
	GtkTreeIter iter;
	if (gtk_tree_model_get_iter (model, &iter, path))
		gtk_tree_model_get (GTK_TREE_MODEL (model), &iter, ID_REQ, &id, -1);
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
	{
		widget = lookup_widget (treeview, "editBloodRequestWindow");
		GtkWidget *popup = create_deletePopupWindow();
		gtk_window_set_transient_for (GTK_WINDOW (popup), GTK_WINDOW (widget));
		gtk_widget_set_sensitive (widget, FALSE);

		widget = lookup_widget (popup, "dataLabel_deletePopup");
		gtk_label_set_text (GTK_LABEL (widget), id);

		widget = lookup_widget (popup, "confirmationLabel_deletePopup");
		gtk_label_set_text (GTK_LABEL (widget), "Êtes vous sûr de vouloir supprimer cette Demande de sang ?\n  Action irréversible !!");

		gtk_widget_show (popup);
	}	
	else
	{
		widget = lookup_widget (treeview, "idEntry_edit_bloodRequest");
		gtk_entry_set_text (GTK_ENTRY (widget), id);

		on_editButton_edit_bloodRequest_clicked (widget, NULL);

		widget = lookup_widget (treeview, "notebook_bloodRequest");
		gtk_notebook_set_current_page (GTK_NOTEBOOK (widget), 2);
	}
	g_free (id);
}


void on_bloodTypeCheckButton_bloodRequest_toggled (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget (button, "bloodTypeComboBox_manage_bloodRequest");
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (button)))
		gtk_widget_show (widget);
	else
	{
		gtk_combo_box_set_active (GTK_COMBO_BOX (widget), -1);
		gtk_widget_hide (widget);
	}
}


void on_resetFiltersButton_manage_bloodRequest_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget (button, "bloodTypeCheckButton_bloodRequest");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), FALSE);
	on_bloodTypeCheckButton_bloodRequest_toggled (widget, NULL);

	widget = lookup_widget (button, "dateCheckButton_bloodRequest");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), FALSE);
	on_dateCheckButton_bloodRequest_toggled (widget, NULL);

	widget = lookup_widget (button, "etsEntry_manage_bloodRequest");
	gtk_entry_set_text (GTK_ENTRY (widget), "");

	on_display_bloodRequest_changed (widget, NULL);
}


void on_dateCheckButton_bloodRequest_toggled (GtkWidget *togglebutton,  gpointer user_data)
{ 
	GtkWidget *widget = lookup_widget (togglebutton, "dateEntry_manage_bloodRequest");
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton)))
	{
		gtk_widget_show (widget);
		widget = lookup_widget (togglebutton, "editDateButton_manage_bloodRequest");
		gtk_widget_show (widget); 
	}
	else
	{
		gtk_entry_set_text (GTK_ENTRY (widget), "");
		gtk_widget_hide (widget);
		widget = lookup_widget (togglebutton, "editDateButton_manage_bloodRequest");
		gtk_widget_hide (widget);
	}
}


void on_confirmButton_edit_bloodRequest_clicked (GtkWidget *button, gpointer user_data)
{
	char id[LENGTH_REQ];
	GtkWidget *widget = lookup_widget (button, "idMaskedLabel_edit_bloodRequest");
	strcpy (id, gtk_label_get_text (GTK_LABEL (widget)));

	request req;
	char error[100];
	lookup_req_by_id (id, &req, error);

	widget = lookup_widget (button, "idEntry_edit_bloodRequest");
	gtk_entry_set_text (GTK_ENTRY (widget), id);

	widget = lookup_widget (button, "etsEntry_edit_bloodRequest");
	strcpy (req.ets, gtk_entry_get_text (GTK_ENTRY (widget)));
	
	widget = lookup_widget (button, "bloodGroupComboBox_edit_bloodRequest");
	strcpy (req.bloodType.bloodGroup, gtk_combo_box_get_active_text (GTK_COMBO_BOX (widget)));

	widget = lookup_widget (button, "plusRadioButton_edit_bloodRequest");
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget))) 
		req.bloodType.rhesus = 1;
	else
		req.bloodType.rhesus = 0;
		
	widget = lookup_widget (button, "quantitySpinButton_edit_bloodRequest");
	req.quantity = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (widget));

	widget = lookup_widget (button, "calendar_edit_bloodRequest");
	gtk_calendar_get_date (GTK_CALENDAR (widget), &req.date.y, &req.date.m, &req.date.d);

	widget = lookup_widget (button, "errorLabel_edit_bloodRequest");
	if (is_all_alpha (req.ets) == 0)
	{
		gtk_label_set_text (GTK_LABEL (widget), "Seulement les lettres autorisées dans le champ etablissement.");
	}
	else if (strlen (req.bloodType.bloodGroup) == 0)
	{
		gtk_label_set_text (GTK_LABEL (widget), "Veuillez choisir un group sanguin.");	
	}
	else if (req.date.d == 0)
	{
		gtk_label_set_text (GTK_LABEL (widget), "Veuillez entrez une date.");
	}
	else
	{
		whitespace_to_underscore (req.ets);
		edit_req (req, error);

		if (strcmp (error, "request successfully modified") == 0)
		{
			widget = lookup_widget (button, "idMaskedLabel_edit_bloodRequest");
			gtk_label_set_text (GTK_LABEL (widget), "");

			widget = lookup_widget (button, "errorLabelLookupEts_edit_editEts");
			gtk_label_set_text (GTK_LABEL (widget), "");

			widget = lookup_widget (button, "idEntry_edit_bloodRequest");
			gtk_entry_set_text (GTK_ENTRY (widget), "");

			widget = lookup_widget (button, "etsEntry_edit_bloodRequest");
			gtk_entry_set_text (GTK_ENTRY (widget), "");
	
			widget = lookup_widget (button, "bloodGroupComboBox_edit_bloodRequest");
			gtk_combo_box_set_active (GTK_COMBO_BOX (widget), -1);

			widget = lookup_widget (button, "plusRadioButton_edit_bloodRequest");
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), TRUE);

			widget = lookup_widget (button, "calendar_edit_bloodRequest");
			gtk_calendar_select_month (GTK_CALENDAR (widget), 0, 2024);
			gtk_calendar_select_day (GTK_CALENDAR (widget), -1);

			widget = lookup_widget (button, "ediBloodRequestsWindow");
			GtkWidget *popup = create_confirmationPopupWindow();
			gtk_window_set_transient_for (GTK_WINDOW (popup), GTK_WINDOW (widget));
			gtk_widget_set_sensitive (widget, FALSE);
			widget = lookup_widget (popup, "confirmationLabel");
			gtk_label_set_text (GTK_LABEL (widget), "Etablissement modifié avec succés.");

			gtk_widget_show (popup);		
		}
		else if (strcmp (error, "request not found") == 0)
		{
			gtk_label_set_text (GTK_LABEL (widget), "Demande de sang introuuvable.");		
		}
		else if (strcmp (error, "couldn't open request_file") == 0)
		{
			gtk_label_set_text (GTK_LABEL (widget), "Problème d'accés vers la Base de Données.");
		}
	}				
}


void  on_editButton_edit_bloodRequest_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget* widget = lookup_widget (button, "idEntry_edit_bloodRequest");
	char id[LENGTH_ETS];
	strcpy (id, gtk_entry_get_text (GTK_ENTRY (widget)));
	char error[100];
	request req;
	lookup_req_by_id (id, &req, error);
	widget = lookup_widget (button, "errorLabelLookupBloodRequest_edit_bloodRequest");
	if (strcmp (error, "request successfully found") == 0)
	{
		gtk_label_set_text (GTK_LABEL (widget), "Veuillez modifier les informations");

		widget = lookup_widget (button, "idMaskedLabel_edit_bloodRequest");
		gtk_label_set_text (GTK_LABEL (widget), id);

		widget = lookup_widget (button, "etsEntry_edit_bloodRequest");
		gtk_entry_set_text (GTK_ENTRY (widget), req.ets);

		widget = lookup_widget (button, "bloodGroupComboBox_edit_bloodRequest");
		gtk_combo_box_set_active (GTK_COMBO_BOX (widget), blood_group_to_int (req.bloodType.bloodGroup));

		if (req.bloodType.rhesus == 1)
		{
			widget = lookup_widget (button, "plusRadioButton_edit_bloodRequest");
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), TRUE);
		}
		else
		{
			widget = lookup_widget (button, "minusRadioButton_edit_bloodRequest");
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), TRUE);	
		}
		
		widget = lookup_widget (button, "quantitySpinButton_edit_bloodRequest");
		gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget), req.quantity);

		widget = lookup_widget (button, "calendar_edit_bloodRequest");
		gtk_calendar_select_month (GTK_CALENDAR (widget), req.date.m, req.date.y);
		gtk_calendar_select_day (GTK_CALENDAR (widget), req.date.d);
		
		
	}
	else 
	{
		widget = lookup_widget (button, "etsEntry_edit_bloodRequest");
		gtk_entry_set_text (GTK_ENTRY (widget), "");

		widget = lookup_widget (button, "bloodGroupComboBox_edit_bloodRequest");
		gtk_combo_box_set_active (GTK_COMBO_BOX (widget), -1);

		widget = lookup_widget (button, "plusRadioButton_edit_bloodRequest");
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), TRUE);

		widget = lookup_widget (button, "quantitySpinButton_edit_bloodRequest");
		gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget), 0);

		widget = lookup_widget (button, "calendar_edit_bloodRequest");
		gtk_calendar_select_month (GTK_CALENDAR (widget), 0, 2024);
		gtk_calendar_select_day (GTK_CALENDAR (widget), 0);
		
		widget = lookup_widget (button, "errorLabelLookupBloodRequest_edit_bloodRequest");
		if (strcmp(error, "request not found") == 0)		
			gtk_label_set_text (GTK_LABEL (widget), "Aucune demande de sang trouvée avec cet ID.");
		else if( strcmp (error, "couldn't open request_file") == 0)
			gtk_label_set_text (GTK_LABEL (widget), "Problème d'accés vers la Base de Données.");
	}
}


void on_cancelButton_edit_bloodRequest_clicked (GtkWidget *button, gpointer user_data)
{
	char id[LENGTH_REQ];
	GtkWidget *widget = lookup_widget (button, "idMaskedLabel_edit_bloodRequest");
	strcpy (id, gtk_label_get_text (GTK_LABEL (widget)));

	widget = lookup_widget (button, "idEntry_edit_bloodRequest");
	gtk_entry_set_text (GTK_ENTRY (widget), id);

	on_editButton_edit_bloodRequest_clicked (widget, NULL);
}


void on_cancelbutton_calendarDialog_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget *dialog = lookup_widget (button, "calendarDialog_manage_bloodRequest");
	gtk_widget_destroy (dialog);
}


void on_confirmButton_calendarDialog_clicked (GtkWidget *button, gpointer user_data)
{
	date date;
	char date_string [15];
	GtkWidget *widget = lookup_widget (button, "calendar_manage_bloodRequest");
	gtk_calendar_get_date (GTK_CALENDAR (widget), &date.y, &date.m, &date.d);
	date_to_string (date_string, date);

	widget = lookup_widget (button, "calendarDialog_manage_bloodRequest");
	GtkWindow *mainWindow = gtk_window_get_transient_for (GTK_WINDOW (widget));
	gtk_widget_destroy (widget);

	widget = lookup_widget (GTK_WIDGET (mainWindow), "dateEntry_manage_bloodRequest");
	gtk_entry_set_text (GTK_ENTRY (widget), date_string);
	on_display_bloodRequest_changed (widget, NULL);
}


void on_settingsButton_bloodRequest_enter (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget (button, "onHoverLabel_bloodRequest");
	gtk_label_set_text (GTK_LABEL (widget), "Gérer votre Compte");
}


void on_settingsButton_bloodRequest_leave (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget (button, "onHoverLabel_bloodRequest");
	gtk_label_set_text (GTK_LABEL (widget), "");
}


void on_logoutButton_bloodRequest_leave (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget (button, "onHoverLabel_bloodRequest");
	gtk_label_set_text (GTK_LABEL (widget), "");
}


void on_editDateButton_manage_bloodRequest_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget *dialog = create_calendarDialog_manage_bloodRequest();
	GtkWidget *mainWindow = lookup_widget (button, "editBloodRequestWindow");
	gtk_window_set_transient_for (GTK_WINDOW (dialog), GTK_WINDOW (mainWindow));
	gtk_widget_show (dialog);
}



void on_clearButton_edit_editEts_clicked (GtkWidget *button, gpointer user_data)
{
	GtkWidget *widget = lookup_widget (button, "nameEtsEntry_edit_editEts");
	gtk_entry_set_text (GTK_ENTRY (widget), "");

	widget = lookup_widget (button, "regionComboBox_edit_editEts");
	gtk_combo_box_set_active (GTK_COMBO_BOX (widget), -1);

	widget = lookup_widget (button, "adressEntry_edit_editEts");
	gtk_entry_set_text (GTK_ENTRY (widget), "");

	widget = lookup_widget (button, "fromSpinButton_edit_editEts");
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget), 8);

	widget = lookup_widget (button, "toSpinButton_edit_editEts");
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget), 12);

	widget = lookup_widget (button, "capacitySpinButton_edit_editEts");
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget), 0);

	widget = lookup_widget (button, "contactEntry_edit_editEts");
	gtk_entry_set_text (GTK_ENTRY (widget), "");

	widget = lookup_widget (button, "cntsRadioButton_edit_editEts");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), TRUE);

	widget = lookup_widget (button, "errorLabeleditEts_edit_editEts");
	gtk_label_set_text (GTK_LABEL (widget), "");
}


void on_editEts_changed (GtkWidget *button, gpointer user_data)
{
	char id[LENGTH_ETS];
	GtkWidget *widget = lookup_widget (button, "idMaskedLabel_edit_editEts");
	strcpy (id, gtk_label_get_text (GTK_LABEL (widget)));

	if (strlen(id) == 0)
	{
		widget = lookup_widget (button, "errorLabelLookupEts_edit_editEts");
		gtk_label_set_text (GTK_LABEL (widget), "Aucun Etablissement à modifier.");
	}
	else
	{
		widget = lookup_widget (button, "idEntry_edit_editEts");
		gtk_entry_set_text (GTK_ENTRY (widget), id);
	}
	
}


void
on_clearButton_edit_bloodRequest_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{

}

