LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS     := -DPOCO_ANDROID -DPOCO_NO_FPENVIRONMENT -DPOCO_NO_WSTRING -DPOCO_NO_SHAREDMEMORY

LOCAL_MODULE := poconet_static

LOCAL_MODULE_FILENAME := libpoconet

LOCAL_SRC_FILES := \
src/AbstractHTTPRequestHandler.cpp \
src/DatagramSocket.cpp \
src/DatagramSocketImpl.cpp \
src/DialogSocket.cpp \
src/DNS.cpp \
src/FilePartSource.cpp \
src/FTPClientSession.cpp \
src/FTPStreamFactory.cpp \
src/HostEntry.cpp \
src/HTMLForm.cpp \
src/HTTPAuthenticationParams.cpp \
src/HTTPBasicCredentials.cpp \
src/HTTPBufferAllocator.cpp \
src/HTTPChunkedStream.cpp \
src/HTTPClientSession.cpp \
src/HTTPCookie.cpp \
src/HTTPCredentials.cpp \
src/HTTPDigestCredentials.cpp \
src/HTTPFixedLengthStream.cpp \
src/HTTPHeaderStream.cpp \
src/HTTPIOStream.cpp \
src/HTTPMessage.cpp \
src/HTTPRequest.cpp \
src/HTTPRequestHandler.cpp \
src/HTTPRequestHandlerFactory.cpp \
src/HTTPResponse.cpp \
src/HTTPServer.cpp \
src/HTTPServerConnection.cpp \
src/HTTPServerConnectionFactory.cpp \
src/HTTPServerParams.cpp \
src/HTTPServerRequest.cpp \
src/HTTPServerRequestImpl.cpp \
src/HTTPServerResponse.cpp \
src/HTTPServerResponseImpl.cpp \
src/HTTPServerSession.cpp \
src/HTTPSession.cpp \
src/HTTPSessionFactory.cpp \
src/HTTPSessionInstantiator.cpp \
src/HTTPStream.cpp \
src/HTTPStreamFactory.cpp \
src/ICMPClient.cpp \
src/ICMPEventArgs.cpp \
src/ICMPPacket.cpp \
src/ICMPPacketImpl.cpp \
src/ICMPSocket.cpp \
src/ICMPSocketImpl.cpp \
src/ICMPv4PacketImpl.cpp \
src/IPAddress.cpp \
src/IPAddressImpl.cpp \
src/MailMessage.cpp \
src/MailRecipient.cpp \
src/MailStream.cpp \
src/MediaType.cpp \
src/MessageHeader.cpp \
src/MulticastSocket.cpp \
src/MultipartReader.cpp \
src/MultipartWriter.cpp \
src/NameValueCollection.cpp \
src/Net.cpp \
src/NetException.cpp \
src/NetworkInterface.cpp \
src/NullPartHandler.cpp \
src/PartHandler.cpp \
src/PartSource.cpp \
src/PartStore.cpp \
src/POP3ClientSession.cpp \
src/QuotedPrintableDecoder.cpp \
src/QuotedPrintableEncoder.cpp \
src/RawSocket.cpp \
src/RawSocketImpl.cpp \
src/RemoteSyslogChannel.cpp \
src/RemoteSyslogListener.cpp \
src/ServerSocket.cpp \
src/ServerSocketImpl.cpp \
src/SMTPChannel.cpp \
src/SMTPClientSession.cpp \
src/Socket.cpp \
src/SocketAddress.cpp \
src/SocketAddressImpl.cpp \
src/SocketImpl.cpp \
src/SocketNotification.cpp \
src/SocketNotifier.cpp \
src/SocketReactor.cpp \
src/SocketStream.cpp \
src/StreamSocket.cpp \
src/StreamSocketImpl.cpp \
src/StringPartSource.cpp \
src/TCPServer.cpp \
src/TCPServerConnection.cpp \
src/TCPServerConnectionFactory.cpp \
src/TCPServerDispatcher.cpp \
src/TCPServerParams.cpp \
src/WebSocket.cpp \
src/WebSocketImpl.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/../Foundation/include

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/../Foundation/include

LOCAL_EXPORT_LDLIBS := -llog

include $(BUILD_STATIC_LIBRARY)