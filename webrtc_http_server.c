/*
 * (C) Copyright 2013 Kurento (http://kurento.org/)
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU Lesser General Public License
 * (LGPL) version 2.1 which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/lgpl-2.1.html
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 */

 #include <stdio.h>
#include <gst/gst.h>
#include <libsoup/soup.h>
#include <nice/nice.h>
#include <string.h>
#include <stdlib.h>

#define GST_CAT_DEFAULT webrtc_http_server
GST_DEBUG_CATEGORY_STATIC (GST_CAT_DEFAULT);

#define DEBUG_NAME "webrtc_http_server"

#define PORT 8080
#define MIME_TYPE "text/html"
#define HTML_FILE "webrtc_loopback.html"

#define CERTTOOL_TEMPLATE "/tmp/certtool.tmpl"
#define CERT_KEY_PEM_FILE "/tmp/certkey.pem"

char pem[] = "-----BEGIN CERTIFICATE-----\
MIICxjCCAi+gAwIBAgIJAMjcXehohH9WMA0GCSqGSIb3DQEBCwUAMHwxCzAJBgNV\
BAYTAklUMQ8wDQYDVQQIDAZOYXBvbGkxDzANBgNVBAcMBk5hcG9saTEYMBYGA1UE\
CgwPTWVldGVjaG8gcy5yLmwuMQ4wDAYDVQQDDAVqYW51czEhMB8GCSqGSIb3DQEJ\
ARYSamFudXNAbWVldGVjaG8uY29tMB4XDTE1MDYwNDEzMjAxOFoXDTE2MDYwMzEz\
MjAxOFowfDELMAkGA1UEBhMCSVQxDzANBgNVBAgMBk5hcG9saTEPMA0GA1UEBwwG\
TmFwb2xpMRgwFgYDVQQKDA9NZWV0ZWNobyBzLnIubC4xDjAMBgNVBAMMBWphbnVz\
MSEwHwYJKoZIhvcNAQkBFhJqYW51c0BtZWV0ZWNoby5jb20wgZ8wDQYJKoZIhvcN\
AQEBBQADgY0AMIGJAoGBALFYwKzIRd4mhG4unmZ8dM95Iz+SJTJYSSphVxDqW0Vy\
AXxMFrCb5KiXuOKNgyPQMjRzXl5QVBwRhOh+sR4bk3KvtBwQ5EeKlQoWKpahTjzX\
Nt2e30BT+TF2QH0Hkvd7E4zR9YvHTPpZpdIWWj90pS5BMAwCtisXJDKtoLPFnL7t\
AgMBAAGjUDBOMB0GA1UdDgQWBBTXYPi6RVDqd4vCD5f8bTH9h7+F5jAfBgNVHSME\
GDAWgBTXYPi6RVDqd4vCD5f8bTH9h7+F5jAMBgNVHRMEBTADAQH/MA0GCSqGSIb3\
DQEBCwUAA4GBAAOi1TaCPUZxn1ns0uWn5mRquxSTuQ/picYrbasKkM+5gNMeYnay\
jJzigo3UQGJBnTmvJOuEIaRmnKsVet+wbx26t690BP8KcawRybYM6+6av5AXxwrl\
sDpjOaAha5JZ/y1kPu7Vk0XPIgYw3vx7/BbxYC7Fbyet+ZVDd7vdBx+V\
-----END CERTIFICATE-----";

char pemc[] = "-----BEGIN PRIVATE KEY-----\
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\
0qgfH8qILf4t1ULeWxPK4n3dHZ49K2E=\
-----END PRIVATE KEY-----\
-----BEGIN CERTIFICATE-----\
MIIFhTCCA22gAwIBAgIJALqPiXsVwZGuMA0GCSqGSIb3DQEBCwUAMFkxCzAJBgNV\
BAYTAkFVMRMwEQYDVQQIDApTb21lLVN0YXRlMSEwHwYDVQQKDBhJbnRlcm5ldCBX\
aWRnaXRzIFB0eSBMdGQxEjAQBgNVBAMMCWxvY2FsaG9zdDAeFw0xNjA1MDMwODA1\
NDdaFw0xNzA1MDMwODA1NDdaMFkxCzAJBgNVBAYTAkFVMRMwEQYDVQQIDApTb21l\
LVN0YXRlMSEwHwYDVQQKDBhJbnRlcm5ldCBXaWRnaXRzIFB0eSBMdGQxEjAQBgNV\
BAMMCWxvY2FsaG9zdDCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAMu4\
8c4IwR1pO7N0H1D1PFFOgveRtLZu7vk8iEjsjAf+DD8CGpZ9BeV1/D4cMmn5Q2bp\
y3UpwIiUeuz8fGVN3hhR3vaY2JS97qTK5+83pP09gperD5/+yZqT6CLuRoh6CYp0\
vEHD5CyfUK9HSRhlKVeAnWYrIWD0krN1WRrgZVIcvzlV/pmbj1aKuQ1+cXJxAEfj\
2/rhWTZf15hNu2fLWXemBeqQZTMOAl55CFVx5r7wPyYw4i9I2az9aj/fQRPjMQDV\
j/d5bdF68t5hxIf5wk/gGo8XBMBmo0uAj60Qp81wHirEr2FFMK7I+48XMFA9SfxR\
SahVZhjbz58K0+URD/taJewL3qrkoivJGQfL9waF+NlLJ8DoGQLN/tWNX9nsQIwu\
HBijg7z4hDP/cTm2dzIyxaSpSp904r3SE74n/+jI+BOWmZwo3iRJMKzWhx80VtM4\
qXZyHUrxCSf0Q1yqSlcyNAVpe3fCpGO9hR6ao3MX6xx3fgdQ1LUcNyZbmHFWPZ0N\
pp+oI8kx+9ksMMtcCJq4KGgoLaCEtJjf4a0TDiCL1eNnym79YSto2hQc8cyvc4my\
kerRAy9mcvmpd/e7j/eKQikNi/usWxGbeIOiy/5zG2Xrf9S2fNsc4/TdnLn+OLJX\
5pJ4AuVIxkA/zHsE0kcANssoJk6Hgxxek6GizytdAgMBAAGjUDBOMB0GA1UdDgQW\
BBSP8O2pIi6niJ4w0gHXR6PzawwRrDAfBgNVHSMEGDAWgBSP8O2pIi6niJ4w0gHX\
R6PzawwRrDAMBgNVHRMEBTADAQH/MA0GCSqGSIb3DQEBCwUAA4ICAQCkxybb3ci2\
NjbzjmvPflqmdTwyGOvreouCXmVHvm5vNL69LSOgZ6PmyEpyywALJqhaEhCXLJrq\
yyZ82My9TxYn84rukH20lyBgbjIMFnabamFAOB9LqMqM4jaedT00OEbfY+uEE5Nw\
NwOjNdUrrwfD2PQLAF06Orft4wex/L9psHBHaxWybnPkx+UAlA/Moz8kmCWWq9SA\
JPvFNXwN3WylgCgAG8kR9PYtLWQEFSp8D9lSezI1C8Ddk0ymTw4aF+p9gHbbjZw4\
XEEpKgRwhpHa7IrcVyeXdQ78/pYc1f7fThL88LLv7lwtJnDWqWYOJrO4HH064IKn\
KazLz1v9UT6yegUFiP/y688BH9LTNNf4pxGOee7LiDpfc7wyIkwrAjxoy4gc8xjp\
Gp6aAvLC9Wzc+i2P0Hz/CvS5ffhZ9k0XGIvSHGbMRN1G4l9cOEQadyzGZGUryFRC\
yBvXGBfSEYdr4OWOhdrelwpZXvl8rLRaAKU2xxIYZT9JtAXmTjWRFnjYLAuJil7e\
ywPbGFYsB5d9Buiw+rJLnGF4NOudk1wXBElrhdjoajDS3Miw5vn2TbuHxIleoszC\
fojNr80RenHT+EnY+0MecCUaeKfU4xd9nIl9I/1MpvM84zSu7Rhd0xEli6SN3fen\
8zRCZGBfwD1y21dDrpgWDPFxjc5Cas63bg==\
-----END CERTIFICATE-----";

char pem3[] = "-----BEGIN CERTIFICATE-----\
MIIDXTCCAkWgAwIBAgIJAK3Sp1t2sTX2MA0GCSqGSIb3DQEBCwUAMEUxCzAJBgNV\
BAYTAkFVMRMwEQYDVQQIDApTb21lLVN0YXRlMSEwHwYDVQQKDBhJbnRlcm5ldCBX\
aWRnaXRzIFB0eSBMdGQwHhcNMTYxMDIyMjMzMzU5WhcNMTcxMDIyMjMzMzU5WjBF\
MQswCQYDVQQGEwJBVTETMBEGA1UECAwKU29tZS1TdGF0ZTEhMB8GA1UECgwYSW50\
ZXJuZXQgV2lkZ2l0cyBQdHkgTHRkMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIB\
CgKCAQEAyJwQZh75ckP2wsPKLSrHiV2MYXXGhNr9YHDSVVDv49E+UPGUcK9QiTN4\
XV4sXtSTyEBcAqmgc22oBTQe0jmkPdOdIN/CW6rAZob2IAuw7h57ZcQlTwkbLY8Q\
1SJEUU4aCgbpo3IC7HsiL3XLpSiJK0Xsa742lD9r/eG0v1nYm6dxXnCFW1m2nUX7\
QGB8/fEqcrNC16QvFIvASRYUn51SJOMep4BDZJETYtFs6ZVsVVG7C+/plWRZIUkZ\
OycfmP4POtNZb6GLYfAoYeDKRLINivBIENHAKeN2yID2kxxLV4OTno/lThXpALpk\
3RZdqu0f5Lv2X76cunuIuZeeMGeuNwIDAQABo1AwTjAdBgNVHQ4EFgQUmhwU+bf2\
Dbgd2KF/uBFwlRhIzyYwHwYDVR0jBBgwFoAUmhwU+bf2Dbgd2KF/uBFwlRhIzyYw\
DAYDVR0TBAUwAwEB/zANBgkqhkiG9w0BAQsFAAOCAQEAquNaOrMyKARqRIM2oZSB\
keu5BuhMn2iH3rXdo9RVGizQ6Hy7o+BhOvy6Ln/OWdK8+CH0Rm6gkt6g/Nd96+qG\
JEvxn7Tbv1ZFTHv7m4n4i0kuAcAFkCvaZVWi5Vfl+FCybNLQdWiQd6WjvZn3Mpgo\
YcMwy2ii7QrNT41Sjj5/uKLwSrL9K9c/tvtc/BXVFjIM5DrTGYddFlEwkcHgdUhX\
gjmVlQWd3Tx6NIH12wFagBHd6PmXz/OOcQn6PHoRx4W/eCsZLANWa1Qv7SS6R9yx\
Ajm/SXfc7BIRzHHvOt6CtKrG6xK7Kx8p0W/DNZTkJxFUQ6YYYRSkCwhcpyWT4wIq\
sw==\
-----END CERTIFICATE-----\
-----BEGIN PRIVATE KEY-----\
MIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQDInBBmHvlyQ/bC\
w8otKseJXYxhdcaE2v1gcNJVUO/j0T5Q8ZRwr1CJM3hdXixe1JPIQFwCqaBzbagF\
NB7SOaQ9050g38JbqsBmhvYgC7DuHntlxCVPCRstjxDVIkRRThoKBumjcgLseyIv\
dculKIkrRexrvjaUP2v94bS/Wdibp3FecIVbWbadRftAYHz98Spys0LXpC8Ui8BJ\
FhSfnVIk4x6ngENkkRNi0WzplWxVUbsL7+mVZFkhSRk7Jx+Y/g8601lvoYth8Chh\
4MpEsg2K8EgQ0cAp43bIgPaTHEtXg5Oej+VOFekAumTdFl2q7R/ku/Zfvpy6e4i5\
l54wZ643AgMBAAECggEBALbVlhSc0lgUHUgxTYiQ3r8RZapFvyLCu/8zlF9xntGR\
mSwIoXN6NPp20JK4C9R6Bh6SmclLdBL/tAzaDeUn58r5nNGjXe5R130aMCPQw/ai\
DXEYrbA06nJBW+QEkSNQ/WZ6GmJ+vK9vIh8DSxFBupKX7fvcpr3Cd9gx55wmdMaW\
3Z82rdeE9m6z2jucTy2AtuVF/ZGSRb/UeRSfatfgiR55qQcjWApTBjAb75+0hm66\
VUgHHGymmYUI5e4p/YT9e9H/e8Qv35FbyyxGXeHcO0DFbH9U6ewJ0TqFjSIS2VWS\
6hHcuR7/jm5w2UAmj0N5dsbHa/VgVKwg7UzBFa9OxJECgYEA7k2S+w+I1PLy4ejc\
HY1A6h4e1wcKcJ9KL0DvMRHldZiLo2uGqHItS+q8+zhFCX8xlYo39N5IC3uGk6rS\
SE1dlKWF+eM3BjzDVrlgLF7u+lVFhElja2/jy3Q11iMQEPgcE2R6jjY8nnSxJlOd\
VF2/BZi5nzsxf3HJxg9nlzuIbpsCgYEA14HkrRSBrWL/HbLdlfm4LbiIcU2Ao8gl\
P+cSHxaoNqkLswROte7ALqCJ6ie5xu8MpTfPVpCKiYyva10N+nhm92jXvfGZtaGX\
KOcdFEHmpMgzbgfv5gZd8ApMI8Gx/EsJUHX9MF3RgHSsE9prCnnGz2cyySDqXjJx\
hDPik/87ypUCgYA+F1BYwi9w7OyEGFxiBtAHMFnwxRDfT2HQ9iZcrsEO5vRbXET1\
1uoegcdD3eF/G/kbcawqzVAQTds+1p9730ym0ooaFi3cHjD3g82fQg0ahOVcFpMl\
Bz5fYKQ2a2RgR4VpOCEGtPMOhnEx/09bECIZnzWeW5oGDuv4A0OGkCh4SQKBgHPr\
lsnS4f4V5gxfjfmCHaPaQupPOgbfPcolzQWT9l+Qho6AnqYWCqIKEKU3QSLUqwSk\
BI8XqK1cU2942nAEG76xUnsFXhzpEpoZ1vZyjFHOrntdIZmlixn3MAV7xvVil1wE\
W3CMxohGOdlj/3ffESW26QZvAiIxGAZ4skPRYqQRAoGAQchgvYDxfc/8xUqWauI7\
mv0JCBEFBDOwAZlbQWwFUJtQZ/e91fLkKcoj45+QRkncXXhoRM2r7gy9NXbFBlsB\
39x3huZhpQ6Tr7d1kb2aAczDYPt/atzLpxI6d+Mdql8nFSwCqRAvebAOBiIIXcUT\
+oQRxdvN3O3mpoPgOi7A3GI=\
-----END PRIVATE KEY-----";

char pem2[] = "-----BEGIN RSA PRIVATE KEY----- \
MIIEpAIBAAKCAQEAxjZmocDDI/bHcR7AnqnHmR3/HBO7G1Ovm1+TGcuxVsxRBBRZ\
rvenBplQDNgTPtlOO5SofV39CG/h/ecM7p1kjeaBGeqVhGv4w5ktH4sZUiMpAlf/\
+ylS+WUKvcd/TCXuG8vLqo2ojGnuDX1hsJgNjrLkpJdo4WN2LYtUB4kgEqaJTNiI\
rqXr8NL3cO03f087abqiSlBNY1gsPuBt01KpKuQikATnWmefcFq0LUh7/IH4aBAQ\
OHbrAmYIJDchiR5HD9IzI0gwdJUINv3rfQ097vQhZKaTWd4iPTM5zo6dKJ3+CbYg\
TPyXyIye/dVRFunu8uPddomMayfqkH6q0CbLAwIDAQABAoIBACob9pPYotxqGhbj\
JKLQiPHzmHX7jx2QGteUZ2jsiEFbaL7IIAF25YoWWhZQdU491kv8GguAQzhepJFP\
W8T5tRocZUL/PkKCube8PATehUOY6qZv0ZcnQVRwbebBkj64NCy9kAgszij+fC9r\
eqyMsRymzsJU1FhFzB6C4hgzvpeXX2VcNud3+gEInoHrYywBIhP0AzpIpcEJYGij\
0/dEkZhX1p/pjooJaOgSdPHnP1NjfZQ2a7fM6QN5Y13ZNhgHaTjmnCWxqTxN2yV+\
iAZpJhPFMO/YU/PsXdzldpvuH42R2zoakyjM5DzgdBb1DFch6fIPoweY9mCqk6IZ\
VDazu9ECgYEA/WvUyZLlcVC/N7cPZ+rsE0mHPEGTEhaNNIDQzvgRrtC91HmMJZnG\
Ns9xquk0l9kKMnEXEbBjAc3gxxJvfJsn67gQ/ak3hBGx77Aho1KKhmwDydmSiUbs\
dj/pCL4afhwwfshJKJ9Mt6Xn5wvCsN7B0HG9G+B8x1EWY0PpC95J+bsCgYEAyDq/\
5OrmdSCgYUNPXca5kslI1ZTnhUtf6U72nyYdfm0sCtVS49lhUC7/Q/ykKyMHq1iW\
oD1g/fTzJ78VZzy9nELQsJI16HTsQzbwVRfTjghBw6hA2g+zuwGyWATNH4OMbXB/\
5q6fscSZtJd1ubf1f63uV/x2+Qh5HU4TEYyk21kCgYEAibqrIQpnDJjX883X36B7\
wVe62fLBnZkIETrZQULtSVdFdE7C7kSOx4civcKUxNo+gn+YDBMTHA3qVgcc9FnW\
7nNROKtY8rwzOpM9FOhtRPU7cd5/l4AmT3YYjpnTCCsF6EGuERfSuBTA3n8zxrCq\
IUFPh/EPn7vgMP7dj4e2KLUCgYEAlKw6zCk3EYU2UMH/7mueY0WeFSjJeAntn3kI\
Wkec4sEBUNHxCEninf0ngT3YUEdkbHAM99JbcHYvDjYuGEfbqmlaN6F48a/PtmDW\
tvhIF1A+NJ979+5sz9CEsiJuhJXS8Xf1ID5NSVvnnVZRDaNwYGuvbBmD5YnLFF1i\
f0dlKZECgYAUJ1//jhv5DOjBt6Ho3d0BUZmVl504lAbwSkzI+uy76wAhHbqxbQXn\
mYAZdHF7i9PTl90RYSejcM4ZcEoFwPG5kG0+VcrlR1GgNTsufc4ci6evsHMbylkw\
CPzkAbX0TE7iHSDulU69cZYu/dV4HHp7Zqzz/rKxDv2uPqtSYoThCw==\
-----END RSA PRIVATE KEY-----";

static GRand *_rand;
static GHashTable *cookies;

typedef struct _MesiaSession {
  gint64 id;

  GMainContext *context;
  GMainLoop * loop;

  SoupServer *server;
  SoupMessage *msg;

  NiceAgent *agent;
  guint stream_id;

  GstElement *pipeline;
} MesiaSession;

static void
bus_msg (GstBus * bus, GstMessage * msg, gpointer pipe)
{
  switch (GST_MESSAGE_TYPE (msg)) {
    case GST_MESSAGE_ERROR: {
      gchar *error_file;

      error_file = g_strdup_printf ("error-%s", GST_OBJECT_NAME (pipe));
      GST_ERROR ("Error: %" GST_PTR_FORMAT, msg);
      GST_DEBUG_BIN_TO_DOT_FILE_WITH_TS (GST_BIN (pipe),
          GST_DEBUG_GRAPH_SHOW_ALL, error_file);
      g_free (error_file);

      /* TODO: free mediaSession*/
      break;
    }
    case GST_MESSAGE_WARNING:{
      gchar *warn_file = g_strdup_printf ("warning-%s", GST_OBJECT_NAME (pipe));

      GST_WARNING ("Warning: %" GST_PTR_FORMAT, msg);
      GST_DEBUG_BIN_TO_DOT_FILE_WITH_TS (GST_BIN (pipe),
          GST_DEBUG_GRAPH_SHOW_ALL, warn_file);
      g_free (warn_file);
      break;
    }
    default:
      break;
  }
}

static void
create_pipeline (MesiaSession *mediaSession)
{
  GstElement *pipeline = gst_pipeline_new (NULL);
  GstBus *bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
  //GstElement *rtpvp8pay = gst_element_factory_make ("rtpvp8pay", NULL);
  //GstElement *rtpvp8depay = gst_element_factory_make ("rtpvp8depay", NULL);
  //GstElement *vp8dec = gst_element_factory_make ("vp8dec", NULL);
  //GstElement *vp8enc = gst_element_factory_make ("vp8enc", NULL);
  GstElement *rtpvp8pay = gst_element_factory_make ("rtph264pay", NULL);
  printf("pay %p\n",rtpvp8pay);
  GstElement *rtpvp8depay = gst_element_factory_make ("rtph264depay", NULL);
  printf("pay %p\n",rtpvp8depay);
  GstElement *vp8dec = gst_element_factory_make ("avdec_h264", NULL);
  printf("pay %p\n",vp8dec);
  GstElement *vp8enc = gst_element_factory_make ("x264enc", NULL);
  printf("pay %p\n",vp8enc);
  GstElement *dtlssrtpenc = gst_element_factory_make ("dtlssrtpenc", NULL);
  printf("pay %p\n",dtlssrtpenc);
  GstElement *dtlssrtpdec = gst_element_factory_make ("dtlssrtpdec", NULL);
  printf("pay %p\n",dtlssrtpdec);
  GstElement *nicesink = gst_element_factory_make ("nicesink", NULL);
  printf("pay %p\n",nicesink);
  GstElement *nicesrc = gst_element_factory_make ("nicesrc", NULL);
  printf("pay %p\n",nicesrc);
  GstElement *capsfilter = gst_element_factory_make ("capsfilter", NULL);
  printf("pay %p\n",capsfilter);
  //GstElement *clockoverlay = gst_element_factory_make ("clockoverlay", NULL);
  GstElement *clockoverlay = gst_element_factory_make ("identity", NULL);
  printf("pay %p\n",clockoverlay);

  GstCaps *caps;

  g_object_set (G_OBJECT (pipeline), "async-handling", TRUE, NULL);
  gst_bus_add_signal_watch (bus);
  g_signal_connect (bus, "message", G_CALLBACK (bus_msg), pipeline);
  g_object_unref(bus);

  caps = gst_caps_new_simple("application/x-rtp",
                              "payload", G_TYPE_INT, 126,
                              NULL);
  g_object_set (capsfilter, "caps", caps, NULL);
  gst_caps_unref (caps);

  g_object_set (clockoverlay, "font-desc", "Sans 28", NULL);
  g_object_set(vp8enc, "deadline", GST_SECOND / 30, "target-bitrate", 256000,
                "keyframe-mode", 0, "end-usage", 2, NULL);

  //g_object_set (G_OBJECT (dtlssrtpenc), "channel-id", GST_OBJECT_NAME (pipeline), NULL);
  g_object_set (G_OBJECT (dtlssrtpenc), "connection-id", GST_OBJECT_NAME (pipeline), NULL);
  g_object_set (G_OBJECT (dtlssrtpenc), "is-client", FALSE, NULL);
  //g_object_set (G_OBJECT (dtlssrtpdec), "channel-id", GST_OBJECT_NAME (pipeline), NULL);
  g_object_set (G_OBJECT (dtlssrtpdec), "connection-id", GST_OBJECT_NAME (pipeline), NULL);
  g_object_set (G_OBJECT (dtlssrtpdec), "is-client", FALSE, NULL);
  char * buffer = (char*)malloc(sizeof(char)*4096*16);
  if (buffer==NULL) {
    fprintf(stderr,"SHIT BUFFER\n");
    exit(1);
  }
  FILE * fptr = fopen(CERT_KEY_PEM_FILE,"r");
  size_t off = 0;
  while(fgets(buffer+off, 4096, fptr)) {
	off=strlen(buffer);
  }
  //g_object_set (G_OBJECT (dtlssrtpdec), "certificate-pem-file", CERT_KEY_PEM_FILE, NULL);
  //g_object_set (G_OBJECT (dtlssrtpdec), "pem", CERT_KEY_PEM_FILE, NULL); //TODO THIS SHOULD BE THE FILE CONENTS?
  g_object_set (G_OBJECT (dtlssrtpdec), "pem", buffer, NULL); //TODO THIS SHOULD BE THE FILE CONENTS?

  g_object_set (G_OBJECT (nicesink), "agent", mediaSession->agent, "stream", mediaSession->stream_id, "component", 1, NULL);
  g_object_set (G_OBJECT (nicesrc), "agent", mediaSession->agent, "stream", mediaSession->stream_id, "component", 1, NULL);

  gst_bin_add_many (GST_BIN (pipeline), nicesrc, dtlssrtpdec, rtpvp8depay, rtpvp8pay, dtlssrtpenc, nicesink,
                    capsfilter, vp8dec, vp8enc, clockoverlay, NULL);
  gst_element_link_many (nicesrc, dtlssrtpdec, capsfilter, rtpvp8depay, vp8dec, clockoverlay,
                         vp8enc, rtpvp8pay, dtlssrtpenc, nicesink, NULL);

  gst_element_set_state (pipeline, GST_STATE_PLAYING);
  //GST_DEBUG_BIN_TO_DOT_FILE_WITH_TS(GST_BIN(pipeline), GST_DEBUG_GRAPH_SHOW_ALL,
  //                              GST_OBJECT_NAME(pipeline));

  mediaSession->pipeline = pipeline;
}

static gboolean
generate_certkey_pem_file (const gchar * cert_key_pem_file)
{
  gchar *cmd;
  int ret;

  cmd =
      g_strconcat ("/bin/sh -c \"gnutls-certtool --generate-privkey --outfile ",
      cert_key_pem_file, "\"", NULL);
  ret = system (cmd);
  g_free (cmd);

  if (ret == -1)
    return FALSE;

  cmd =
      g_strconcat
      ("/bin/sh -c \"echo 'organization = kurento' > ", CERTTOOL_TEMPLATE,
      " && gnutls-certtool --generate-self-signed --load-privkey ", cert_key_pem_file,
      " --template ", CERTTOOL_TEMPLATE, " >> ", cert_key_pem_file, "\"", NULL);
  ret = system (cmd);
  g_free (cmd);

  return (ret != -1);
}

static gchar*
generate_fingerprint (const gchar *pem_file)
{
  GTlsCertificate *cert;
  GError *error = NULL;
  GByteArray *ba;
  gssize length;
  int size;
  gchar *fingerprint;
  gchar *fingerprint_colon;
  int i, j;

  cert = g_tls_certificate_new_from_file (pem_file, &error);
  g_object_get (cert, "certificate", &ba, NULL);
  fingerprint = g_compute_checksum_for_data (G_CHECKSUM_SHA256, ba->data, ba->len);
  g_object_unref (cert);

  length = g_checksum_type_get_length (G_CHECKSUM_SHA256);
  size = (int)(length*2 + length) * sizeof (gchar);
  fingerprint_colon = g_malloc0 (size);

  j = 0;
  for (i=0; i< length*2; i+=2) {
    fingerprint_colon[j] = g_ascii_toupper (fingerprint[i]);
    fingerprint_colon[++j] = g_ascii_toupper (fingerprint[i+1]);
    fingerprint_colon[++j] = ':';
    j++;
  };
  fingerprint_colon[size-1] = '\0';
  g_free (fingerprint);

  return fingerprint_colon;
}

static void
gathering_done (NiceAgent *agent, guint stream_id, MesiaSession *mediaSession)
{
  SoupServer *server = mediaSession->server;
  SoupMessage *msg = mediaSession->msg;
  GString *sdpStr;
  GSList *candidates;
  GSList *walk;
  NiceCandidate *lowest_prio_cand = NULL;
  gchar addr[NICE_ADDRESS_STRING_LEN+1];
  gchar *ufrag, *pwd;
  gchar *fingerprint;
  gchar *line;

  nice_agent_get_local_credentials (mediaSession->agent, mediaSession->stream_id, &ufrag, &pwd);
  candidates = nice_agent_get_local_candidates (mediaSession->agent, mediaSession->stream_id, 1);

  for (walk = candidates; walk; walk = walk->next) {
    NiceCandidate *cand = walk->data;

    if (nice_address_ip_version (&cand->addr) == 6)
      continue;

    if (!lowest_prio_cand ||
        lowest_prio_cand->priority < cand->priority)
      lowest_prio_cand = cand;
  }

  candidates = g_slist_concat (candidates,
                               nice_agent_get_local_candidates (mediaSession->agent, mediaSession->stream_id, 2));

  nice_address_to_string (&lowest_prio_cand->addr, addr);
  fingerprint = generate_fingerprint (CERT_KEY_PEM_FILE);


/*"v=0
o=- 1477382546589972 1477382546589972 IN IP4 192.168.2.147
s=Streaming Test
t=0 0
a=group:BUNDLE video
a=msid-semantic: WMS janus
m=video 9 RTP/SAVPF 126
c=IN IP4 192.168.2.147
a=sendonly
a=mid:video
a=rtcp-mux
a=ice-ufrag:6mLs
a=ice-pwd:EpDfWcTB5AQuY6/iXVSHIU
a=ice-options:trickle
a=fingerprint:sha-256 D2:B9:31:8F:DF:24:D8:0E:ED:D2:EF:25:9E:AF:6F:B8:34:AE:53:9C:E6:F3:8F:F2:64:15:FA:E8:7F:53:2D:38
a=setup:actpass
a=rtpmap:126 H264/90000
a=fmtp:126 profile-level-id=42e01f;packetization-mode=1
a=rtcp-fb:126 nack
a=rtcp-fb:126 goog-remb
a=ssrc:3547346012 cname:janusvideo
a=ssrc:3547346012 msid:janus janusv0
a=ssrc:3547346012 mslabel:janus
a=ssrc:3547346012 label:janusv0
a=candidate:1 1 udp 2013266431 10.0.2.15 60302 typ host
a=candidate:2 1 udp 2013266431 192.168.2.147 42943 typ host
a=candidate:1 2 udp 2013266430 10.0.2.15 42451 typ host
a=candidate:2 2 udp 2013266430 192.168.2.147 57371 typ host
"*/

  sdpStr = g_string_new ("");
  g_string_append_printf (sdpStr,
      "\"v=0\\r\\n\" +\n"
      "\"o=- 2750483185 0 IN IP4 %s\\r\\n\" +\n"
      "\"s=Streaming test\\r\\n\" +\n"
      "\"t=0 0\\r\\n\" +\n"
      "\"a=group:BUNDLE video\\r\\n\" +\n"
      "\"a=msid-semantic: WMS janus\\r\\n\" +\n"
      "\"m=video 9 RTP/SAVPF 126\\r\\n\" +\n"
      "\"c=IN IP4 %s\\r\\n\" +\n"
      "\"a=sendonly\\r\\n\" +\n"
      "\"a=mid:video\\r\\n\" +\n"
      "\"a=rtcp-mux\\r\\n\" +\n"
      "\"a=ice-ufrag:%s\\r\\n\" +\n"
      "\"a=ice-pwd:%s\\r\\n\" +\n"
      "\"a=fingerprint:sha-256 %s\\r\\n\" +\n"
//      "\"a=rtpmap:96 VP8/90000\\r\\n\" +\n"
      "\"a=rtpmap:126 H264/90000\\r\\n\" +\n"
      "\"a=fmtp:126 profile-level-id=42e01f;packetization-mode=1\\r\\n\" +\n"
      "\"a=sendrecv\\r\\n\" +\n"
      "\"a=mid:video\\r\\n\" +\n"
      "\"a=rtcp-mux\\r\\n\"",
      addr, addr, ufrag, pwd, fingerprint, nice_address_get_port (&lowest_prio_cand->addr), addr);
  /*g_string_append_printf (sdpStr,
      "\"v=0\\r\\n\" +\n"
      "\"o=- 2750483185 0 IN IP4 %s\\r\\n\" +\n"
      "\"s=Streaming test\\r\\n\" +\n"
      "\"t=0 0\\r\\n\" +\n"
      "\"a=ice-ufrag:%s\\r\\n\" +\n"
      "\"a=ice-pwd:%s\\r\\n\" +\n"
      "\"a=fingerprint:sha-256 %s\\r\\n\" +\n"
      "\"a=group:BUNDLE video\\r\\n\" +\n"
      "\"m=video %d RTP/SAVPF 126\\r\\n\" +\n"
      "\"c=IN IP4 %s\\r\\n\" +\n"
//      "\"a=rtpmap:96 VP8/90000\\r\\n\" +\n"
      "\"a=rtpmap:126 H264/90000\\r\\n\" +\n"
      "\"a=fmtp:126 profile-level-id=42e01f\\r\\n\" +\n"
      "\"a=sendrecv\\r\\n\" +\n"
      "\"a=mid:video\\r\\n\" +\n"
      "\"a=rtcp-mux\\r\\n\"",
      addr, ufrag, pwd, fingerprint, nice_address_get_port (&lowest_prio_cand->addr), addr);*/

  g_free (ufrag);
  g_free (pwd);
  g_free (fingerprint);

  int i=0; 
  for (walk = candidates; walk; walk = walk->next) {
    if (i%2==1) {
    NiceCandidate *cand = walk->data;
  
    nice_address_to_string (&cand->addr, addr);
    g_string_append_printf (sdpStr,
        "+\n\"a=candidate:%s %d UDP %d %s %d typ host\\r\\n\"",
        cand->foundation, cand->component_id, cand->priority, addr,
        nice_address_get_port (&cand->addr));
    }
    i++;
  }
  g_slist_free_full (candidates, (GDestroyNotify) nice_candidate_free);

  line = g_strdup_printf("sdp = %s;\n", sdpStr->str);
  soup_message_body_append (msg->response_body, SOUP_MEMORY_TAKE, line,
                            strlen(line));
  g_string_free (sdpStr, FALSE);

  line = "</script>\n</body>\n</html>\n";
  soup_message_body_append (msg->response_body, SOUP_MEMORY_STATIC, line,
                            strlen(line));

  soup_message_set_status (msg, SOUP_STATUS_OK);
  soup_server_unpause_message (server, msg);

  g_object_unref (server);
  g_object_unref (msg);
}

static void
kms_nice_agent_recv (NiceAgent *agent, guint stream_id, guint component_id,
                 guint len, gchar *buf, gpointer user_data)
{
  /* Nothing to do, this callback is only for negotiation */
}

static gpointer
loop_thread (gpointer loop)
{
  g_main_loop_run (loop); /* TODO: g_main_loop_quit */

  return NULL;
}

static gchar *
get_substring (const gchar *regex, const gchar *string)
{
  GRegex *gregex;
  GMatchInfo *match_info = NULL;
  gchar *ret = NULL;

  gregex = g_regex_new (regex,
      G_REGEX_MULTILINE | G_REGEX_NEWLINE_CRLF, 0, NULL);
  g_assert (gregex);

  g_regex_match (gregex, string, 0, &match_info);

  if (g_match_info_get_match_count (match_info) == 2)
    ret = g_match_info_fetch (match_info, 1);

  g_match_info_free (match_info);
  g_regex_unref (gregex);

  return ret;
}

static gboolean
configure_media_session (MesiaSession *mediaSession, const gchar *sdp)
{
  gboolean ret;
  gchar *ufrag;
  gchar *pwd;
  GRegex *regex;
  GMatchInfo *match_info = NULL;

  GST_DEBUG ("Process SDP:\n%s", sdp);

  ufrag = get_substring ("^a=ice-ufrag:([A-Za-z0-9\\+\\/]+)$", sdp);
  pwd = get_substring ("^a=ice-pwd:([A-Za-z0-9\\+\\/]+)$", sdp);
  /* TODO: get remote fingerprint and pt*/

  nice_agent_set_remote_credentials (mediaSession->agent, mediaSession->stream_id, ufrag, pwd);
  g_free (ufrag);
  g_free (pwd);

  regex = g_regex_new ("^a=candidate:(?<foundation>[0-9]+) (?<cid>[0-9]+)"
      " (udp|UDP) (?<prio>[0-9]+) (?<addr>[0-9.:a-zA-Z]+) (?<port>[0-9]+) typ host( generation [0-9]+)?$",
      G_REGEX_MULTILINE | G_REGEX_NEWLINE_CRLF, 0, NULL);
  g_assert (regex);
  g_regex_match (regex, sdp, 0, &match_info);

  while (g_match_info_matches (match_info)) {
    NiceCandidate *cand;
    GSList *candidates;

    gchar *foundation = g_match_info_fetch_named (match_info, "foundation");
    gchar *cid_str = g_match_info_fetch_named (match_info, "cid");
    gchar *prio_str = g_match_info_fetch_named (match_info, "prio");
    gchar *addr = g_match_info_fetch_named (match_info, "addr");
    gchar *port_str = g_match_info_fetch_named (match_info, "port");

    cand = nice_candidate_new (NICE_CANDIDATE_TYPE_HOST);
    cand->component_id = g_ascii_strtoll (cid_str, NULL, 10);
    cand->priority = g_ascii_strtoll (prio_str, NULL, 10);
    strncpy (cand->foundation, foundation, NICE_CANDIDATE_MAX_FOUNDATION);

    ret = nice_address_set_from_string (&cand->addr, addr);
    g_assert (ret);
    nice_address_set_port (&cand->addr, g_ascii_strtoll (port_str, NULL, 10));

    g_free (addr);
    g_free (foundation);
    g_free (cid_str);
    g_free (prio_str);
    g_free (port_str);

    candidates = g_slist_append (NULL, cand);
    ret = nice_agent_set_remote_candidates (mediaSession->agent, mediaSession->stream_id,
        cand->component_id, candidates);
    g_assert (ret);
    g_slist_free (candidates);
    nice_candidate_free (cand);

    g_match_info_next (match_info, NULL);
  }

  g_match_info_free (match_info);
  g_regex_unref (regex);

  return TRUE;
}

static MesiaSession*
init_media_session (SoupServer *server, SoupMessage *msg, gint64 id)
{
  MesiaSession *mediaSession;
  GThread * lt;

  mediaSession = g_slice_new0 (MesiaSession); /* TODO: free */
  mediaSession->id = id;

  mediaSession->context = g_main_context_new ();
  mediaSession->loop = g_main_loop_new (mediaSession->context, TRUE); /* TODO: g_main_loop_unref */
  lt = g_thread_new ("ctx", loop_thread, mediaSession->loop);
  g_thread_unref (lt);

  mediaSession->server = g_object_ref (server);
  mediaSession->msg = g_object_ref (msg);

  mediaSession->agent = nice_agent_new (mediaSession->context, NICE_COMPATIBILITY_RFC5245);
  g_object_set (mediaSession->agent, "upnp", FALSE, NULL);
  g_object_set(G_OBJECT (mediaSession->agent),
               "stun-server", "77.72.174.167",
               "stun-server-port", 3478,
               NULL);

  mediaSession->stream_id = nice_agent_add_stream (mediaSession->agent, 2);
  nice_agent_attach_recv (mediaSession->agent, mediaSession->stream_id, 1, mediaSession->context,
                         kms_nice_agent_recv, NULL);
  nice_agent_attach_recv (mediaSession->agent, mediaSession->stream_id, 2, mediaSession->context,
                         kms_nice_agent_recv, NULL);
  g_signal_connect (mediaSession->agent, "candidate-gathering-done",
    G_CALLBACK (gathering_done), mediaSession);

  create_pipeline (mediaSession);

  nice_agent_gather_candidates (mediaSession->agent, mediaSession->stream_id);

  return mediaSession;
}

static void
server_callback (SoupServer *server, SoupMessage *msg, const char *path,
                 GHashTable *query, SoupClientContext *client,
                 gpointer user_data)
{
  gboolean ret;
  gchar *contents;
  gsize length;
  const char *cookie_str;
  SoupCookie *cookie = NULL;
  gint64 id, *id_ptr;
  char *header;
  MesiaSession *mediaSession = NULL;

  GST_DEBUG ("Request: %s", path);

  if (msg->method != SOUP_METHOD_GET) {
    soup_message_set_status (msg, SOUP_STATUS_NOT_IMPLEMENTED);
    GST_DEBUG ("Not implemented");
    return;
  }

  if (g_strcmp0 (path, "/") != 0) {
    soup_message_set_status (msg, SOUP_STATUS_NOT_FOUND);
    GST_DEBUG ("Not found");
    return;
  }

  cookie_str = soup_message_headers_get_list (msg->request_headers, "Cookie");
  if (cookie_str != NULL) {
    gchar **tokens, **token;

    tokens = g_strsplit (cookie_str, ";", 0);
    for (token = tokens; *token != NULL; token++) {
      cookie = soup_cookie_parse (*token, NULL);

      if (cookie != NULL) {
        if (g_strcmp0 (cookie->name, "id") == 0) {
          id = g_ascii_strtoll (cookie->value, NULL, 0);
          if (id != G_GINT64_CONSTANT (0)) {
            GST_DEBUG ("Found id: %"G_GINT64_FORMAT, id);
            mediaSession = g_hash_table_lookup (cookies, &id);
            break;
          }
        }
        soup_cookie_free (cookie);
        cookie = NULL;
      }
    }
    g_strfreev (tokens);
  }

  if (cookie == NULL) {
    gchar *id_str;
    const gchar *host;

    id = g_rand_double_range (_rand, (double) G_MININT64, (double) G_MAXINT64);
    id_str = g_strdup_printf ("%" G_GINT64_FORMAT, id);
    host = soup_message_headers_get_one(msg->request_headers, "Host");
    if (host == NULL) {
      host = "localhost";
    }

    cookie = soup_cookie_new ("id", id_str, host, path, -1);
    g_free (id_str);
  }

  if (query != NULL) {
    gchar * sdp = g_hash_table_lookup(query, "sdp");
    if (sdp != NULL && mediaSession != NULL) {
      if (configure_media_session (mediaSession, sdp)) {
        soup_message_set_status (msg, SOUP_STATUS_OK);
      } else {
        soup_message_set_status (msg, SOUP_STATUS_NOT_ACCEPTABLE);
      }
      soup_message_set_response (msg, MIME_TYPE, SOUP_MEMORY_STATIC, "", 0);
      return;
    }
  }

  g_hash_table_remove (cookies, &id);

  header = soup_cookie_to_cookie_header (cookie);
  if (header != NULL) {
    soup_message_headers_append (msg->response_headers, "Set-Cookie", header);
    g_free(header);
  } else {
    GST_WARNING ("Null cookie");
  }
  soup_cookie_free (cookie);

  mediaSession = init_media_session (server, msg, id);
  id_ptr = g_malloc (sizeof(gint64));
  *id_ptr = id;
  g_hash_table_insert (cookies, id_ptr, mediaSession);

  ret = g_file_get_contents (HTML_FILE, &contents, &length, NULL);
  if (!ret) {
    soup_message_set_status (msg, SOUP_STATUS_INTERNAL_SERVER_ERROR);
    GST_ERROR ("Error loading %s file", HTML_FILE);
    return;
  }

  soup_message_set_response (msg, MIME_TYPE, SOUP_MEMORY_STATIC, "", 0);
  soup_message_body_append (msg->response_body, SOUP_MEMORY_TAKE, contents, length);
  soup_server_pause_message (server, msg);
}

static void
destroy_media_session (gpointer data)
{
  GST_WARNING ("TODO: implement");
}

int
main (int argc, char ** argv)
{
  SoupServer *server;

  gst_init (&argc, &argv);
  GST_DEBUG_CATEGORY_INIT (GST_CAT_DEFAULT, DEBUG_NAME, 0, DEBUG_NAME);

  generate_certkey_pem_file (CERT_KEY_PEM_FILE);
  cookies = g_hash_table_new_full(g_int64_hash, g_int64_equal, g_free, destroy_media_session);
  _rand = g_rand_new ();

  GST_INFO ("Start Kurento WebRTC HTTP server");
  server = soup_server_new (SOUP_SERVER_PORT, PORT,
                            NULL);
  soup_server_add_handler (server, "/", server_callback, NULL, NULL);
  soup_server_run (server);

  g_hash_table_destroy (cookies);
  g_rand_free (_rand);

  return 0;
}
