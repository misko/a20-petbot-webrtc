plugin_LTLIBRARIES = libgstdtls.la librtcmpdemux.la

libgstdtls_la_SOURCES = \
  gstdtls.c\
  gstdtlsenc.c\
  gstdtlsdec.c\
  gstdtlsbase.c\
  gstiostream.c\
  gstdtlsconnection.c\
  gstdtlssrtpdemux.c\
  gstdtlssrtpdec.c\
  gstdtlssrtpenc.c\
  ext/gio/kmsgtlsconnection.c\
  ext/gio/kmsgtlsclientconnection.c\
  ext/gio/kmsgtlsserverconnection.c\
  ext/gio/kmsgioenumtypes.c\
  ext/gio/kmsgtlscertificate.c\
  ext/gnutls/gtlsbackend-gnutls.c\
  ext/gnutls/gtlscertificate-gnutls.c\
  ext/gnutls/gtlsclientconnection-gnutls.c\
  ext/gnutls/gtlsconnection-gnutls.c\
  ext/gnutls/gtlsdatabase-gnutls.c\
  ext/gnutls/gtlsfiledatabase-gnutls.c\
  ext/gnutls/gtlsinputstream-gnutls.c\
  ext/gnutls/gtlsoutputstream-gnutls.c\
  ext/gnutls/gtlsserverconnection-gnutls.c

#libgstsrtp_la_CFLAGS = $(GST_CFLAGS) $(GST_PLUGINS_BASE_CFLAGS) $(SRTP_CFLAGS)
#libgstsrtp_la_LIBADD = $(GST_PLUGINS_BASE_LIBS) \
#        -lgstrtp-@GST_API_VERSION@              \
#        $(GST_LIBS)                             \
#        $(SRTP_LIBS)
#libgstsrtp_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)
#libgstsrtp_la_LIBTOOLFLAGS = $(GST_PLUGIN_LIBTOOLFLAGS)

libgstdtls_la_CFLAGS = \
    $(GST_PLUGINS_BASE_CFLAGS) \
    $(GST_BASE_CFLAGS) \
    $(GST_CFLAGS) \
    $(DTLS_CFLAGS)

libgstdtls_la_LIBADD = $(GST_LIBS) $(GST_BASE_LIBS) $(DTLS_LIBS)  $(GST_PLUGINS_BASE_LIBS)
libgstdtls_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS) -L/usr/local/Cellar/gnutls/3.4.16/lib -lgnutls -L/usr/local/Cellar/glib/2.48.1/lib -L/usr/local/opt/gettext/lib -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl -L/usr/local/Cellar/gst-plugins-base/1.8.3/lib -L/usr/local/Cellar/gstreamer/1.8.3/lib -L/usr/local/Cellar/glib/2.48.1/lib -L/usr/local/opt/gettext/lib -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0 -lintl
#gnutls , gio-2.0, gst-plugins-base-1.0
libgstdtls_la_LIBTOOLFLAGS = $(GST_PLUGIN_LIBTOOLFLAGS)

noinst_HEADERS = \
ext/gio/kmsgioenums.h\
ext/gio/kmsgioenumtypes.h\
ext/gio/kmsgtlscertificate.h\
ext/gio/kmsgtlsclientconnection.h\
ext/gio/kmsgtlsconnection.h\
ext/gio/kmsgtlsserverconnection.h\
ext/gnutls/gtlsbackend-gnutls.h\
ext/gnutls/gtlscertificate-gnutls.h\
ext/gnutls/gtlsclientconnection-gnutls.h\
ext/gnutls/gtlsconnection-gnutls.h\
ext/gnutls/gtlsdatabase-gnutls.h\
ext/gnutls/gtlsfiledatabase-gnutls.h\
ext/gnutls/gtlsinputstream-gnutls.h\
ext/gnutls/gtlsoutputstream-gnutls.h\
ext/gnutls/gtlsserverconnection-gnutls.h\
gstdtlsbase.h\
gstdtlsconnection.h\
gstdtlsdec.h\
gstdtlsenc.h\
gstdtlssrtp.h\
gstdtlssrtpdec.h\
gstdtlssrtpdemux.h\
gstdtlssrtpenc.h\
gstiostream.h

plugin_LTLIBRARIES = libgstrtcpdemux.la

libgstrtcpdemux_la_SOURCES = \
rtcpdemux/kms-marshal.c\
rtcpdemux/kmsrtcpdemux.c\
rtcpdemux/rtcpdemux.c

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
rtcpdemux/kms-marshal.h\
rtcpdemux/kmsrtcpdemux.h\
rtcpdemux/rtcpdemux.h

