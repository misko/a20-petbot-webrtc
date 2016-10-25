plugin_LTLIBRARIES = libgstrtcpdemux.la

libgstrtcpdemux_la_SOURCES = \
./kms-marshal.c\
./kmsrtcpdemux.c\
./rtcpdemux.c

#libgstsrtp_la_CFLAGS = $(GST_CFLAGS) $(GST_PLUGINS_BASE_CFLAGS) $(SRTP_CFLAGS)
#libgstsrtp_la_LIBADD = $(GST_PLUGINS_BASE_LIBS) \
#        -lgstrtp-@GST_API_VERSION@              \
#        $(GST_LIBS)                             \
#        $/SRTP_LIBS)
#libgstsrtp_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)
#libgstsrtp_la_LIBTOOLFLAGS = $(GST_PLUGIN_LIBTOOLFLAGS)

libgstrtcpdemux_la_CFLAGS = \
    $(GST_PLUGINS_BASE_CFLAGS) \
    $(GST_BASE_CFLAGS) \
    $(GST_CFLAGS) \
    $(DTLS_CFLAGS)

libgstrtcpdemux_la_LIBADD = $(GST_LIBS) $(GST_BASE_LIBS) $(DTLS_LIBS)  $(GST_PLUGINS_BASE_LIBS)
libgstrtcpdemux_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS) -L/usr/local/Cellar/gnutls/3.4.16/lib -lgnutls -L/usr/local/Cellar/glib/2.48.1/lib -L/usr/local/opt/gettext/lib -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl -L/usr/local/Cellar/gst-plugins-base/1.8.3/lib -L/usr/local/Cellar/gstreamer/1.8.3/lib -L/usr/local/Cellar/glib/2.48.1/lib -L/usr/local/opt/gettext/lib -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0 -lintl
#gnutls , gio-2.0, gst-plugins-base-1.0
libgstrtcpdemux_la_LIBTOOLFLAGS = $(GST_PLUGIN_LIBTOOLFLAGS)

noinst_HEADERS = \
./kms-marshal.h\
./kmsrtcpdemux.h\
./rtcpdemux.h

