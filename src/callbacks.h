#include <gtk/gtk.h>


void
on_editUsersButton_admin_clicked       (GtkButton       *button,
                                        gpointer         user_data);


void on_editButton_edit_editEts_clicked (GtkWidget *button, gpointer user_data);                                        


void on_showPasswordCheckButton_authentification_toggled (GtkWidget *togglebutton, gpointer user_data);


void on_loginButton_authentification_clicked (GtkWidget *button, gpointer user_data);


void on_settingsButton_admin_enter (GtkWidget *button, gpointer user_data);


void on_settingsButton_admin_leave (GtkWidget *button, gpointer user_data);


void on_logoutButton_admin_enter (GtkWidget *button, gpointer user_data);


void on_logoutButton_admin_leave (GtkWidget *button, gpointer user_data);


void on_editEtsButton_admin_clicked (GtkWidget *button, gpointer user_data);


void
on_statisticsButton_admin_clicked      (GtkButton       *button,
                                        gpointer         user_data);


void on_logoutButton_settingsUser_enter (GtkWidget *button, gpointer user_data);


void on_logoutButton_settingsUser_leave (GtkWidget *button, gpointer user_data);


void on_showPasswordCheckButton_editCin_toggled (GtkWidget *togglebutton, gpointer user_data);


void on_continueButton_editCin_clicked (GtkWidget *button, gpointer user_data);


void on_confirmButton_enterCin_clicked (GtkWidget *button, gpointer user_data);


void on_confirmButton_enterPassword_clicked (GtkWidget *button, gpointer user_data);


void on_passwordEntry_enterPassword_changed (GtkWidget *button, gpointer user_data);


void on_showPasswordButton_enterPassword_pressed (GtkWidget *button, gpointer user_data);


void on_showPasswordButton_enterPassword_released (GtkWidget *button, gpointer user_data);


void on_logoutButton_editEts_enter (GtkWidget *button, gpointer user_data);


void on_logoutButton_editEts_leave (GtkWidget *button, gpointer user_data);


void on_advancedSettingsButton_editEts_clicked (GtkWidget *button, gpointer user_data);


void on_cancelButton_add_editEts_clicked (GtkWidget *button, gpointer user_data);


void on_addButton_add_editEts_clicked (GtkWidget *button, gpointer user_data);


void on_etsTreeView_row_activated (GtkWidget *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);


void on_regionCheckButton_editEts_toggled (GtkWidget *togglebutton, gpointer user_data);


void on_capacityCheckButton_editEts_toggled (GtkWidget *togglebutton, gpointer user_data);


void on_resetFiltersButton_manage_editEts_clicked (GtkWidget *button, gpointer user_data);


void on_confirmButton_edit_editEts_clicked (GtkWidget *button, gpointer user_data);


void on_cancelButton_edit_editEts_clicked (GtkWidget *button, gpointer user_data);


void on_continueButton_enterCin_resetPassword_clicked (GtkWidget *button, gpointer user_data);


void on_confirmButton_deleteEts_clicked (GtkWidget *button, gpointer user_data);


void on_confirmButton_deletePopup_clicked (GtkWidget *button, gpointer user_data);


void
on_addButton_advancedSettings_clicked  (GtkButton       *button,
                                        gpointer         user_data);


void
on_deleteButton_advancedSettings_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);


void on_editPasswordButton_authentification_clicked (GtkWidget *button, gpointer user_data);


void on_editCinButton_settingsUser_clicked (GtkWidget *button, gpointer user_data);


void on_editPasswordButton_settingsUser_clicked (GtkWidget *button, gpointer user_data);


void on_settingsButton_editEts_enter (GtkWidget *button, gpointer user_data);


void on_settingsButton_editEts_leave (GtkWidget *button, gpointer user_data);


void on_mainMenuButton_settingsUser_enter (GtkWidget *button, gpointer user_data);


void on_mainMenuButton_settingsUser_leave (GtkWidget *button, gpointer user_data);


void on_resetButton_settingsUser_clicked (GtkWidget *button, gpointer user_data);


void on_confirmButton_settingsUser_clicked (GtkWidget *button, gpointer user_data);


void on_continueButton_editPassword_clicked (GtkWidget *button, gpointer user_data);


void on_mainMenuButton_editEts_enter (GtkWidget *button, gpointer user_data);


void on_mainMenuButton_editEts_leave (GtkWidget *button, gpointer user_data);


void on_cancelPopup_clicked (GtkWidget *button, gpointer user_data);


void on_logoutButton_clicked (GtkWidget *button, gpointer user_data);


void on_leaveButton_logout_clicked (GtkWidget *button, gpointer user_data);


void on_leaveButton_mainMenu_clicked (GtkWidget *button, gpointer user_data);


void on_mainMenuButton_clicked (GtkWidget *button, gpointer user_data);


void on_settingsButton_clicked (GtkWidget *button, gpointer user_data);


void on_leaveButton_settings_clicked(GtkWidget *button, gpointer user_data);


gboolean on_confirmation_key_press_event (GtkWidget *widget, GdkEventKey *event, gpointer user_data);


void on_confirmationButton_clicked (GtkWidget *button, gpointer user_data);


void on_ajouter_don_clicked (GtkWidget *button, gpointer user_data);


void on_display_editEts_changed (GtkWidget *button, gpointer user_data);


void on_logoutButton_bloodRequest_enter (GtkWidget *button, gpointer user_data);


void on_cancelButton_add_bloodRequest_clicked (GtkWidget *button, gpointer user_data);


void on_addButton_add_bloodRequest_clicked (GtkWidget *button, gpointer user_data);


void on_display_bloodRequest_changed (GtkWidget *button, gpointer user_data);


void on_bloodRequestTreeView_row_activated (GtkWidget *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);


void on_bloodTypeCheckButton_bloodRequest_toggled (GtkWidget *button, gpointer user_data);


void on_resetFiltersButton_manage_bloodRequest_clicked (GtkWidget *button, gpointer user_data);


void on_dateCheckButton_bloodRequest_toggled (GtkWidget *togglebutton, gpointer user_data);


void on_confirmButton_edit_bloodRequest_clicked (GtkWidget *button, gpointer user_data);


void on_editButton_edit_bloodRequest_clicked (GtkWidget *button, gpointer user_data);


void on_cancelButton_edit_bloodRequest_clicked (GtkWidget *button, gpointer user_data);


void on_cancelbutton_calendarDialog_clicked (GtkWidget *button, gpointer user_data);


void on_confirmButton_calendarDialog_clicked (GtkWidget *button, gpointer user_data);


void on_settingsButton_bloodRequest_enter (GtkWidget *button, gpointer user_data);


void on_settingsButton_bloodRequest_leave (GtkWidget *button, gpointer user_data);


void on_logoutButton_bloodRequest_leave (GtkWidget *button, gpointer user_data);


void on_editDateButton_manage_bloodRequest_clicked (GtkWidget *button, gpointer user_data);


void on_clearButton_edit_editEts_clicked (GtkWidget *button, gpointer user_data);


void on_editEts_changed (GtkWidget *button, gpointer user_data);

void
on_clearButton_edit_bloodRequest_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);
