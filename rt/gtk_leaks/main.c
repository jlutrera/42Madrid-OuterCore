#include <gtk/gtk.h>
#include <stdio.h>

static void on_btn_exit_clicked(GtkButton *button, gpointer user_data)
{
    GtkApplication *app = GTK_APPLICATION(user_data);
    g_application_quit(G_APPLICATION(app));
}

static void activate(GtkApplication *app, gpointer user_data)
{
    // Create the main window
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Ejemplo leaks GTK");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    // Create a grid layout
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_widget_set_visible(grid, TRUE);

    // Create the exit button
    GtkWidget *btn_exit = gtk_button_new_with_label("Salir");
    gtk_widget_set_visible(btn_exit, TRUE);
    gtk_widget_set_can_focus(btn_exit, TRUE);
    gtk_widget_set_receives_default(btn_exit, TRUE);

    // Add button to the grid (center position: row 1, column 1)
    gtk_grid_attach(GTK_GRID(grid), btn_exit, 1, 1, 1, 1);

    // Connect the button click signal
    g_signal_connect(btn_exit, "clicked", G_CALLBACK(on_btn_exit_clicked), app);

    // Show the window
    gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.ejemplo.minimo", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
   
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    
    printf("Bye!\n");
    return status;
}