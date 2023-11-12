#include <gtk/gtk.h>



gboolean
on_label14_button_press_event          (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

void
on_confirmationButton_deletePopupWindow_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancelButton_deletePopupWindow_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_addButton_advancedSettingsWindow_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_deleteButton_advancedSettingsWindow_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_editUsersButton_admin_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_editButton_edit_editEts_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_searchEntry_display_editEts_changed (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_deleteButton_edit_editEts_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_regionCheckButton_display_editEts_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_capacityCheckButton_display_editEts_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_searchButton_display_editEts_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);
                                        

void on_showPasswordCheckButton_authentification_toggled (GtkWidget *togglebutton, gpointer user_data);

void on_loginButton_authentification_clicked (GtkWidget *button, gpointer user_data);

void on_settingsButton_admin_clicked (GtkWidget *button, gpointer user_data);

void on_settingsButton_admin_enter (GtkWidget *button, gpointer user_data);

void on_settingsButton_admin_leave (GtkWidget *button, gpointer user_data);

void on_logoutButton_admin_clicked (GtkWidget *button, gpointer user_data);

void on_logoutButton_admin_enter (GtkWidget *button, gpointer user_data);

void on_logoutButton_admin_leave (GtkWidget *button, gpointer user_data);

void on_editEtsButton_admin_clicked (GtkWidget *button, gpointer user_data);

void
on_statisticsButton_admin_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void on_logoutButton_settingsAdmin_enter (GtkWidget *button, gpointer user_data);

void on_logoutButton_settingsAdmin_leave (GtkWidget *button, gpointer user_data);

void on_showPasswordCheckButton_editCin_toggled (GtkWidget *togglebutton, gpointer user_data);

void
on_continueButton_editCin_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_confirmButton_enterCin_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void on_confirmButton_enterPassword_clicked (GtkWidget *button, gpointer user_data);

void on_passwordEntry_enterPassword_changed (GtkWidget *button, gpointer user_data);

void on_showPasswordButton_enterPassword_pressed (GtkWidget *button, gpointer user_data);

void on_showPasswordButton_enterPassword_released (GtkWidget *button, gpointer user_data);

void on_logoutButton_editEts_enter (GtkWidget *button, gpointer user_data);

void on_logoutButton_editEts_leave (GtkWidget *button, gpointer user_data);

void on_advancedSettingsButton_editEts_clicked (GtkWidget *button, gpointer user_data);

void
on_cancelButton_add_editEts_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_addButton_add_editEts_clicked       (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_addLabel_editEts_button_press_event (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

void
on_nameEtsEntry_manage_editEts_changed (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_capacitySpinButton_display_editEts_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_etsTreeView_row_activated           (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_regionCheckButton_editEts_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_capacityCheckButton_editEts_toggled (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_deleteCheckButton_manage_editEts_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_resetFiltersButton_manage_editEts_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_regionComboBox_display_editEts_changed
                                        (GtkComboBox     *combobox,
                                        gpointer         user_data);

gboolean
on_displayLabel_editEts_button_press_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

void
on_confirmButton_edit_editEts_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancelButton_edit_editEts_clicked   (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_editLabel_editEts_button_press_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

void
on_cancelButton_enterCin_resetPassword_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_continueButton_enterCin_resetPassword_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_confirmButton_deleteEts_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_addButton_advancedSettings_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_deleteButton_advancedSettings_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_editPasswordButton_authentification_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_editCinButton_settingsAdmin_clicked (GtkButton       *button,
                                        gpointer         user_data);

void on_editPasswordButton_settingsAdmin_clicked (GtkWidget *button, gpointer user_data);

void
on_leaveButton_confirmLeave_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_continueButton_enterCin_clicked     (GtkButton       *button,
                                        gpointer         user_data);




void on_leaveButton_leaveSettingsAdmin_clicked (GtkWidget *button, gpointer user_data);

void
on_leaveButton_leaveEditEts_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void on_settingsButton_editEts_enter (GtkWidget *button, gpointer user_data);

void on_settingsButton_editEts_leave (GtkWidget *button, gpointer user_data);

void
on_cancelButton_deleteEts_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void on_leaveSettingsAdmin_clicked (GtkWidget *button, gpointer user_data);

void on_mainMenuButton_settingsAdmin_enter (GtkWidget *button, gpointer user_data);

void on_mainMenuButton_settingsAdmin_leave (GtkWidget *button, gpointer user_data);

void on_resetButton_settingsAdmin_clicked (GtkWidget *button, gpointer user_data);

void on_confirmButton_settingsAdmin_clicked (GtkWidget *button, gpointer user_data);

void on_cancelButton_leaveSettingsAdmin_clicked (GtkWidget *button, gpointer user_data);

void on_cancelEditSettingsAdmin_clicked (GtkWidget *button, gpointer user_data);

void on_continueButton_editPassword_clicked (GtkWidget *button, gpointer user_data);

void on_leaveEditEts_clicked (GtkWidget *button, gpointer user_data);

void on_mainMenuButton_editEts_enter (GtkWidget *button, gpointer user_data);

void on_mainMenuButton_editEts_leave (GtkWidget *button, gpointer user_data);

void on_cancelButton_leaveEditEts_clicked (GtkWidget *button, gpointer user_data);
