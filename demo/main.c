#include <gfc.h>

int
main (int   argc,
      char**argv)
{
  GtkWidget* window;

  gtk_init (&argc, &argv);

  window = gfc_window_new ();

  /* FIXME: move into GfcWindow */
  g_signal_connect (window, "destroy",
                    G_CALLBACK (gtk_main_quit), NULL);

  gtk_widget_show_all (window);

  gtk_main ();
  return 0;
}

