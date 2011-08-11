#include <Platform.h>

#include <stdio.h>
#include <X11/Xlib.h>
#include <gtk/gtk.h>

#include "GraphDB.h"
#include "GraphRender.h"
#include "SvgShapes.h"
#include "SvgParser.h"
#include "GraphvizLayout.h"

void LoadTestData(ln::IGraph * g, ln::ICluster * c, ln::IVertex * v, int depth = 0)
{
	if (++depth > 9)
		return;

	ln::IClusterPtr c2 = (depth % 5 == 0) ? c : g->CreateCluster(c);
	//c2->SetProperty(ln::PROP_LABEL, (boost::_tformat(_T("Cluster Depth %1%")) % depth).str().c_str());
	int tot = (depth % 5 == 0) ? 5 : 1;
	for (int i = 0; i < tot; ++i)
	{
		ln::IVertexPtr v2 = g->CreateVertex(c2);
		//v2->SetProperty(ln::PROP_LABEL, (boost::_tformat(_T("Depth %1%\\nVertex %2%")) % depth % v2->GetIDString()).str().c_str());
		LoadTestData(g, c2, v2, depth);
		if (v)
		{
			ln::IEdgePtr e = g->CreateEdge(v, v2);
			//e->SetProperty(ln::PROP_LABEL, (boost::_tformat(_T("Edge %1%")) % e->GetIDString()).str().c_str());
		}
	}
}

class CDotView
{
public:
    GtkWidget *m_canvas;

	ln::IGraphBufferPtr m_buffer;
	ln::IGraphPtr m_g;
	ln::IGraphRenderPtr m_gr;
	ln::IGraphHotItemPtr m_hotItem;

	GdkRectangle m_boundingRect;

	GdkRectangle m_renderRect;

public:
	CDotView(GtkWidget *canvas)
    {
        m_canvas = canvas;

        m_g = ln::CreateGraph();
        m_buffer = ln::CreateGraphBuffer(0, 0);
        m_hotItem = ln::CreateGraphHotItem();

        m_gr = ln::CreateGraphRender(m_g, m_buffer, m_hotItem);

    }

	void LoadTestData()
    {
        //m_g->SetProperty(ln::PROP_LABEL, _T("Graph 1"));
        ::LoadTestData(m_g, NULL, NULL, 0);

        std::string svg;
        ln::DoGraphvizLayout(m_g, svg);
        MergeSVG(m_g, svg);

        ln::RectD viewBox(m_g->GetPropertyDouble(ln::SVG_PROP_VIEWBOX_X), m_g->GetPropertyDouble(ln::SVG_PROP_VIEWBOX_Y), m_g->GetPropertyDouble(ln::SVG_PROP_VIEWBOX_W), m_g->GetPropertyDouble(ln::SVG_PROP_VIEWBOX_H));
        viewBox = viewBox.MulDiv(96, 72);
        std::cout << "x0:  " << viewBox.x << "\n";
        std::cout << "y0:  " << viewBox.y << "\n";
        std::cout << "w0:  " << viewBox.Width << "\n";
        std::cout << "h0:  " << viewBox.Height << "\n";

        gint width = (gint)((viewBox.Width * 96) / 72);
        gint height = (gint)((viewBox.Height * 96) / 72);

        gtk_widget_set_size_request(m_canvas, width, height);

        std::cout << "Well" << "\n";
    }
};

static void destroy( GtkWidget *widget, gpointer data )
{
    gtk_main_quit ();
}

gboolean _EventCallback(GtkWidget *widget, GdkEvent *_event, gpointer user_data)
{
    if (!user_data)
        return 0;

    CDotView * win = (CDotView *)user_data;

    switch(_event->type)
    {
    case GDK_EXPOSE:
        {
            std::cout << "GDK_EXPOSE:  Start" << "\n";
            GdkEventExpose * event = reinterpret_cast<GdkEventExpose *>(_event);
            std::cout << "GDK_EXPOSE:  Start 2" << "\n";
            //GtkAdjustment * hadj = gtk_scrolled_window_get_hadjustment(GTK_SCROLLED_WINDOW(win->m_scrolled_window));
            //GtkAdjustment * vadj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(win->m_scrolled_window));

            //ln::RectI rect(hadj->value, vadj->value, hadj->value + hadj->page_size, vadj->value + vadj->page_size);
            win->m_buffer->Resize(event->area.width, event->area.height);
            ln::RectI rect(event->area.x, event->area.y, event->area.x + event->area.width, event->area.y + event->area.height);
            std::cout << "GDK_EXPOSE:  Start 3" << "\n";
            win->m_gr->DoRender(rect, true);
            std::cout << "GDK_EXPOSE:  Start 4" << "\n";

            std::cout << "x2:  " << event->area.x << "\t";
            std::cout << "y2:  " << event->area.y << "\t";
            std::cout << "w2:  " << event->area.width << "\t";
            std::cout << "h2:  " << event->area.height << "\t";
            std::cout << "Count:  " << event->count << "\n";
            win->m_buffer->Draw(win->m_canvas, event->area.x, event->area.y);

            std::cout << "GDK_EXPOSE:  End" << "\n";

            return true;
        }
        break;

    case GDK_CONFIGURE:
        {
            GdkEventConfigure * event = reinterpret_cast<GdkEventConfigure *>(_event);
            std::cout << "x" << event->x << "\n";
            std::cout << "y" << event->y << "\n";
            std::cout << "w" << event->width << "\n";
            std::cout << "h" << event->height << "\n";

                /*
                GdkRectangle area;
                area.x = event->x;
                area.y = event->y;
                area.width = event->width;
                area.height = event->height;

                win->DoRender(area);
                //gtk_widget_set_size_request (win->m_scrolled_window, area.width, area.height);
                //gtk_widget_set_size_request (win->m_canvas, 150, 100);
                */
            return true;
        }
        break;
    }
    return false;
}

int main( int   argc, char *argv[] )
{
    static GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *scrolled_window;
    GtkWidget *drawing_area;

    gtk_init (&argc, &argv);

    /* Create a new dialog window for the scrolled window to be
     * packed into.  */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    g_signal_connect (window, "destroy", G_CALLBACK (destroy), NULL);

    gtk_window_set_title (GTK_WINDOW (window), "GtkScrolledWindow example");
    gtk_container_set_border_width (GTK_CONTAINER (window), 0);
    gtk_widget_set_size_request (window, 640, 480);

    vbox = gtk_vbox_new(FALSE, 0);

    /* create a new scrolled window. */
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);

    //gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);

    /* the policy is one of GTK_POLICY AUTOMATIC, or GTK_POLICY_ALWAYS.
     * GTK_POLICY_AUTOMATIC will automatically decide whether you need
     * scrollbars, whereas GTK_POLICY_ALWAYS will always leave the scrollbars
     * there.  The first one is the horizontal scrollbar, the second,
     * the vertical. */
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
    /* The dialog window is created with a vbox packed into it. */
    gtk_box_pack_start (GTK_BOX (vbox), scrolled_window, TRUE, TRUE, 0);
    gtk_widget_show (scrolled_window);

    /* create a table of 10 by 10 squares. */
    drawing_area = gtk_drawing_area_new ();
    CDotView dotView(drawing_area);

    /* pack the table into the scrolled window */
    gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_window), drawing_area);
    gtk_widget_show (drawing_area);

    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);

    gtk_widget_show (window);

    //gtk_drawing_area_size (GTK_DRAWING_AREA (drawing_area), 2000, 2000);
    dotView.LoadTestData();

    gtk_widget_add_events(
        drawing_area,
        GDK_BUTTON_PRESS_MASK |
        GDK_BUTTON_RELEASE_MASK |
        GDK_KEY_PRESS_MASK |
        GDK_KEY_RELEASE_MASK |
        GDK_POINTER_MOTION_MASK |
        GDK_POINTER_MOTION_HINT_MASK |
        GDK_SCROLL_MASK |
        GDK_EXPOSURE_MASK |
        GDK_VISIBILITY_NOTIFY_MASK |
        GDK_ENTER_NOTIFY_MASK |
        GDK_LEAVE_NOTIFY_MASK |
        GDK_FOCUS_CHANGE_MASK
    );

    g_signal_connect(G_OBJECT(drawing_area), "event", G_CALLBACK(&_EventCallback), &dotView);

    gtk_main();

    return 0;
}
