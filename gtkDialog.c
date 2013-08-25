#include <gtk/gtk.h>

static void on_response(GtkDialog *dialog, gint response_id, gpointer user_data)
{
	g_print("response is %d\n", response_id);

	gtk_widget_destroy(GTK_WIDGET(dialog));
}

static void show_dialog(GtkButton *button, gpointer user_data)
{
	GtkWindow *window = user_data;
	GtkWidget *dialog;
	GtkWidget *content_area;
	GtkWidget *label;

	dialog = gtk_dialog_new_with_buttons("A GTK+ Dialog", window, GTK_DIALOG_MODAL, GTK_STOCK_OK,
		GTK_RESPONSE_OK, NULL);

	content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
	label = gtk_label_new("This demonstrate a dialog with a label");
	gtk_container_add(GTK_CONTAINER(content_area), label);

	gtk_widget_show_all(dialog);

	g_signal_connect(GTK_DIALOG(dialog), "response", G_CALLBACK(on_response), NULL);
}

static void activate(GtkApplication *app, gpointer user_data)
{
	GtkWidget *window;
	GtkWidget *button;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "GNOME Button");
	gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

	button = gtk_button_new_with_label("Click Me");
	gtk_container_add(GTK_CONTAINER(window), button);
	g_signal_connect(GTK_BUTTON(button), "clicked", G_CALLBACK(show_dialog), GTK_WINDOW(window));
	gtk_widget_show_all(window);
}

int main(int argc, char *argv[])
{
	GtkApplication *app;
	int status;

	app = gtk_application_new("gtk.example.org", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}
