#include <gtk/gtk.h>
#include <webkit2/webkit2.h>


static void destroyWindowCb(GtkWidget * widget, GtkWidget * window);
static gboolean closeWebViewCb(WebKitWebView * webView,
			       GtkWidget * window);

void
user_fct(WebKitWebView * web_view,
	 WebKitWebResource * resource,
	 WebKitURIRequest * request, gpointer user_data) {

	printf("%s\n", webkit_web_resource_get_uri(resource));

}


int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);

	GtkWidget *main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 600);

	WebKitWebView *webView = WEBKIT_WEB_VIEW(webkit_web_view_new());
	gtk_container_add(GTK_CONTAINER(main_window), GTK_WIDGET(webView));

	g_signal_connect(main_window, "destroy",
			 G_CALLBACK(destroyWindowCb), NULL);
	g_signal_connect(webView, "close", G_CALLBACK(closeWebViewCb),
			 main_window);
	g_signal_connect(webView, "resource-load-started",
			 G_CALLBACK(user_fct), NULL);

	webkit_web_view_load_uri(webView, argv[1]);

	gtk_widget_grab_focus(GTK_WIDGET(webView));
	gtk_widget_show_all(main_window);

	gtk_main();

	return 0;
}


static void destroyWindowCb(GtkWidget * widget, GtkWidget * window) {
	gtk_main_quit();
}

static gboolean closeWebViewCb(WebKitWebView * webView, GtkWidget * window) {
	gtk_widget_destroy(window);
	return TRUE;
}
