#ifndef SERVER
#define SERVER
#include "header.h"
#define LOGIN 0
#define SEND 1
#define SENDALL 2
#define RECV 3
#define KICK 4
#define KICKALL 5
#define CHANGESTAT 6
#define LOGOUT 7
#define REGISTER 8
#define LOGINOK 9
#define LOGINFALSE 10
#define START 11
#define STOP 12
class mujserver:public QTcpServer
{
	Q_OBJECT
		public:
	mujserver ();
	void stop ();
	void start (int port);
	void KickAll();
	void kick (QString prezdivka);
	void send (QString prezdivka);
	void SendAll ();
		private:
	int port;
	struct packet;
	QMap <QString ,QTcpSocket*>* clients;
	QByteArray  data;
	QHostAddress addressForListen;
	QTcpSocket *docasnysocket;
	void SetPort ();
	void PacketFromData (packet & p,QByteArray *data);
	QByteArray DataFromPacket (packet p);
	void CheckLogin ();
	void registruj ();
	void getError (QString chyba);
	void getError (int error);
	public slots:
		void AcceptConnection ();
		void StartRead ();
		void tiskniStav (QAbstractSocket::SocketState);
};

#endif SERVER