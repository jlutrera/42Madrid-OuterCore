# Test program #
```c
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
```

# How to compile #
```bash
gcc main.c -o gtk_leaks `pkg-config --cflags --libs gtk+-3.0` -g
```

# Detecting leaks with Valgrind #
**Only show definite leaks (more likely to be real bugs)**
```bash
valgrind --leak-check=full --show-leak-kinds=definite ./exec_name
```
**Show use summary mode first**
```bash
valgrind --leak-check=summary ./exec_name
```
**Run your program directly under Valgrind (not through shell)**
```bash
valgrind --child-silent-after-fork=yes ./exec_name
```
**Or use exec to replace the shell process with your application**
```bash
valgrind bash -c "exec ./exec_name"
```
**If you want to see the details of the "still reachable" memory out of curiosity**
```bash
bash valgrind --leak-check=full --show-leak-kinds=reachable ./exec_name
```

# Understanding the output #
```bash
"definitely lost: 0 bytes in 0 blocks" - No memory leaks from your code
"indirectly lost: 0 bytes in 0 blocks" - No secondary leaks caused by primary leaks
"possibly lost: 0 bytes in 0 blocks" - No suspicious memory patterns
"still reachable: 2,265 bytes in 66 blocks" - This is the key part
```

**What "still reachable" means:**

The "still reachable" memory is not a leak. This is memory that:

- Was properly allocated by your application
- Still has pointers/references to it when the program exits
- Is cleaned up by the OS when the process terminates
- This typically includes:

        · GTK internal caches (fontconfig, icon themes, etc.)
        · Library initialization data that's kept for performance
        · Static variables and global state
        · Memory pools that libraries maintain

# Why this is normal for GTK applications: #

GTK and related libraries (GLib, Pango, Fontconfig) intentionally keep some memory allocated for:

- Performance optimization (caching)
- Shared resource management
- Internal bookkeeping

This memory is designed to be cleaned up by the operating system when your process exits.

Your application status:

- Memory management is correct - no leaks from your code
- GTK usage is proper - you're following best practices
- Application is production-ready - the memory profile is normal

# Conclutions #
The memory leaks you're seeing are internal to the GTK and Fontconfig libraries and are not something you can avoid or fix in your application code. These are known issues with the libraries themselves.

Why you can't avoid these leaks:
- Library internals: The leaks come from libfontconfig.so, libpangoft2.so, libgtk-3.so - these are system libraries
- Intentional caching: GUI libraries often cache resources (fonts, icons, themes) for performance and don't clean them up immediately
- Process exit cleanup: This memory is designed to be reclaimed by the operating system when the process terminates

What the leaks represent:
- Fontconfig: Font caching and configuration parsing
- Pango: Text rendering and font handling
- GTK: UI element caching and theme resources

This is completely normal behavior for GTK applications!  The fact that you have:
- 0 bytes definitely lost from your code
- Proper cleanup in your application
- If you print a final message, it will print at the end

means your application is perfectly written and memory leak free.

If you really want to minimize library leaks:
You can try forcing cleaner shutdown, but this is usually not recommended:

```c
#include <gtk/gtk.h>
#include <stdio.h>

static void on_btn_exit_clicked(GtkButton *button, gpointer user_data)
{
    GtkApplication *app = GTK_APPLICATION(user_data);
    
    // Force some cleanup before quitting
    gtk_style_context_reset_widgets();
    
    g_application_quit(G_APPLICATION(app));
}
// ... rest of your code unchanged ...
```

The reality is that these library leaks are harmless because:

- They don't grow over time (fixed amount)
- They're cleaned up by the OS
- Every GTK application has them
- They don't affect application performance or stability

Final recommendation:
Stop worrying about these leaks! Your code is correct. The leaks are:

- Not your responsibility
- Normal for GTK applications
- Harmless in practice
- Well-known in the GTK community

Focus on ensuring your own code is clean (which it is) and ignore the library internals. The leaks you see are just the cost of using a complex GUI framework like GTK.