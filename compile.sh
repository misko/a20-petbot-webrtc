#/usr/local//Cellar/openssl/1.0.2f/bin/openssl req -new -x509 -nodes -days 365 -newkey rsa:2048 -sha256 -keyout PrivateKey.key -out certificate.crt
#cat certificate.crt PrivateKey.key  > pem

#/usr/local//Cellar/openssl/1.0.2f/bin/openssl

#./configure CC=/usr/bin/gcc CXX=/usr/bin/g++ OBJC=/usr/bin/gcc
#CC=/usr/bin/gcc ./configure
 
gcc `pkg-config --cflags gstreamer-1.0` -I/usr/local/include/libsoup-2.4/ `pkg-config --libs libsoup-2.4 nice gstreamer-1.0`  webrtc_http_server.c
#cmake -DCMAKE_C_COMPILER=/usr/local/bin/gcc  -DCMAKE_MODULE_PATH=//usr/local/share/cmake-3.6/Modules/ -DVERSION=1 .
#https://github.com/ibc/mediasoup/
