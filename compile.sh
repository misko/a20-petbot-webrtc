#/usr/local//Cellar/openssl/1.0.2f/bin/openssl req -new -x509 -nodes -days 365 -newkey rsa:2048 -sha256 -keyout PrivateKey.key -out certificate.crt
#cat certificate.crt PrivateKey.key  > pem

#/usr/local//Cellar/openssl/1.0.2f/bin/openssl

#./configure CC=/usr/bin/gcc CXX=/usr/bin/g++ OBJC=/usr/bin/gcc
#CC=/usr/bin/gcc ./configure
 
gcc `pkg-config --cflags gstreamer-1.0` -I/usr/local/include/libsoup-2.4/ `pkg-config --libs libsoup-2.4 nice gstreamer-1.0`  webrtc_http_server.c -o webrtc_http_server
gcc `pkg-config --cflags gstreamer-1.0` -I/usr/local/include/libsoup-2.4/ `pkg-config --libs libsoup-2.4 nice gstreamer-1.0`  webrtc_http_sendonly.c -o webrtc_http_sendonly
gcc `pkg-config --cflags gstreamer-1.0` -I/usr/local/include/libsoup-2.4/ `pkg-config --libs libsoup-2.4 nice gstreamer-1.0`  webrtc_route.c -o webrtc_route
#cmake -DCMAKE_C_COMPILER=/usr/local/bin/gcc  -DCMAKE_MODULE_PATH=//usr/local/share/cmake-3.6/Modules/ -DVERSION=1 .
#https://github.com/ibc/mediasoup/

#env PKG_CONFIG_PATH=/usr/local/Cellar/openssl101/1.0.1u/lib/pkgconfig ./configure

#Macintosh:dtls miskodzamba$ glib-genmarshal  --header rtcpdemux/kms-marshal.list  > rtcpdemux/kms-marshal.h
#Macintosh:dtls miskodzamba$ glib-genmarshal  --body rtcpdemux/kms-marshal.list  > rtcpdemux/kms-marshal.c

#Macintosh:gst-plugins-bad-1.8.3 miskodzamba$ /usr/local/Cellar/gettext/0.19.8.1/bin/autopoint 
#Macintosh:gst-plugins-bad-1.8.3 miskodzamba$ export AUTOPOINT=/usr/local/Cellar/gettext/0.19.8.1/bin/autopoint
#Macintosh:gst-plugins-bad-1.8.3 miskodzamba$ autoreconf -fvi
