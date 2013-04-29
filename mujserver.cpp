#include "mujserver.h"
struct mujserver::packet
	{
	unsigned int flag;
	QByteArray data;
	QString sender;
	QString receiver;
	int options;
};
void mujserver::tiskniStav (QAbstractSocket::SocketState stat)
{
	switch (stat)
	{
	case QAbstractSocket::UnconnectedState:
		qDebug ("The socket is not connected.");
		break;
	case QAbstractSocket::HostLookupState:
		qDebug ("The socket is performing a host name lookup.");
		break;
	case QAbstractSocket::ConnectingState:
		qDebug ("The socket has started establishing a connection.");
		break;
	case QAbstractSocket::ConnectedState:
		qDebug ("A connection is established.");
		break;
	case QAbstractSocket::BoundState:
		qDebug ("The socket is bound to an address and port (for servers).");
		break;
	case QAbstractSocket::ClosingState:
		qDebug ("The socket is about to close (data may still be waiting to be written).");
		break;
	case QAbstractSocket::ListeningState:
		qDebug ("For internal use only.");
		break;
	}
}
mujserver::mujserver ()
{
	clients=new QMap <QString ,QTcpSocket*>;
	data=QByteArray ();
	addressForListen =QHostAddress ();
	qRegisterMetaType<QAbstractSocket::SocketState>("SocketState");
}
void mujserver::AcceptConnection ()
{
	docasnysocket=nextPendingConnection ();
	connect (docasnysocket,SIGNAL (readyRead ()),this,SLOT (StartRead ()));
	connect (docasnysocket,SIGNAL (stateChanged(QAbstractSocket::SocketState)),SLOT (tiskniStav (QAbstractSocket::SocketState)));
}
void mujserver::PacketFromData (packet & p,QByteArray * data)
{
	QVector <int> * poziceLomeno=new QVector <int> (10);
	int index=0;
	int pocatek=0;
	int flag=0;
	int options=0;
	QString receiver,sender ;
	QByteArray flagarray ,optionsarray ,receiverarray ,senderarray ,dataarray ;
	do
	{
	if (data->at (index)=='/')
	{
		poziceLomeno->append (index);
		index ++;
		index++;
	}
	else
	{
		index++;
	}
	}
	while (data->at (index)!='\0');
	for (int poziceVector=0;poziceVector<poziceLomeno->size ();poziceVector++)
	{
		int lomeno=poziceLomeno->at (poziceVector);
		switch (poziceVector)
		{
			case 0:
			flagarray.append (data->left (lomeno));
			p.flag=flagarray.toInt ();
			pocatek=lomeno+2;
			break;
			case 1:
			dataarray.append (data->mid (pocatek,lomeno));
			p.data.append (dataarray);
			pocatek=lomeno+2;
				break;
			case 2:
			receiver.append (data->mid (pocatek,lomeno));
			p.receiver.append (receiver);
			pocatek=lomeno+2;
			break;
			case 3:
			sender.append (data->mid (pocatek,lomeno));
			p.sender.append (sender);
			pocatek=lomeno+2;
			break;
			case 4:
				optionsarray.append (data->at (data->size ()-1));
				p.options=optionsarray.toInt ();
				break;
		}
	}
}
QByteArray mujserver::DataFromPacket (packet p)
{
	QByteArray data=QByteArray ();
	data.append (QByteArray::number (p.flag));
	data.append ("//");
	data.append (p.data);
	data.append ("//");
	data.append (p.receiver.toLatin1 ());
	data.append ("//");
	data.append (p.sender.toLatin1 ());
	data.append ("//");
	data.append (p.options);
	data.append ('\0');
	return data;
}
void mujserver::StartRead ()
{
	qDebug ("ctu data");
	QByteArray  data= QByteArray ();
	data=docasnysocket->readAll ();
	getError (docasnysocket->error ());
	packet mujpacket;
	PacketFromData (mujpacket,&data);
	clients->insert (mujpacket.receiver,docasnysocket);
	switch (mujpacket.flag)
	{
	case LOGIN:
	{
		clients->insert (mujpacket.data,docasnysocket);
		/*
	QFile soubor ("hesla.txt");
	soubor.open (QIODevice::ReadOnly);
	QTextStream stream (&soubor);
	while (!soubor.atEnd ())
	{
		QString radek=stream.readLine ();
		if (mujpacket.data==radek)
		{
			packet odeslani;
			odeslani.flag=LOGINOK;
			socket->write (DataFromPacket (odeslani));
			getError (socket->error ());
		}
		if (soubor.atEnd ())
		{
			packet odeslani;
			odeslani.flag=LOGINFALSE;
			socket->write (DataFromPacket (odeslani));
			getError (socket->error ());
		}
	}
	}
	*/
	break;
	case SEND:
	
	break;
	case SENDALL:
	break;
	case RECV:
	break;
	case KICK:
	break;
	case KICKALL:
	break;
	case CHANGESTAT:
	break;
	case LOGOUT:
	break;
	case REGISTER:
		{
	QFile soubor ("hesla.txt");
	soubor.open (QIODevice::Append);
	QTextStream stream (&soubor);
	stream >> mujpacket.data;
	soubor.close ();
	break;
		}
	}
}
}
void mujserver::start (int port)
{
	listen (QHostAddress::LocalHost,port);
	getError (errorString ());
	connect (this,SIGNAL (newConnection ()),this,SLOT (AcceptConnection()));
}
void mujserver::stop ()
{
	close ();
}
void mujserver::kick (QString prezdivka)
{
}
void mujserver::KickAll ()
{
}
void mujserver::send (QString prezdivka)
{

}
void mujserver::SendAll ()
{
}
void mujserver::getError (QString chyba)
{
QMessageBox * boxik=new QMessageBox ();
boxik->setText (chyba);
boxik->exec ();
}
void mujserver::getError (int error)
{
	QMessageBox * chybka=new QMessageBox ();
	switch (error)
	{
	case QAbstractSocket::ConnectionRefusedError:
		chybka->setText ("odmitnuti spojeni nebo vyprseni casu");
		break;
	case QAbstractSocket::RemoteHostClosedError:
		chybka->setText ("server ukoncil pripojeni");
	break;
	case QAbstractSocket::HostNotFoundError:
		chybka->setText ("nelze se pripojit na adresu");
		break;
	case QAbstractSocket::SocketAccessError:
		chybka->setText ("operace se socketem selhala protoze nemate opravneni");
		break;
	case QAbstractSocket::SocketResourceError:
		chybka->setText ("prekroceni zdroju systemu (prilis mnoho socketu)");
		break;
	case QAbstractSocket::SocketTimeoutError:
		chybka->setText ("vyprsel cas pro provedeni operace socketu");
		break;
	case QAbstractSocket::DatagramTooLargeError:
		chybka->setText ("datagram je vetsi nez limit systemu");
		break;
	case QAbstractSocket::NetworkError:
		chybka->setText ("problem se siti");
		break;
	case QAbstractSocket::AddressInUseError:
		chybka->setText ("funkce bind adresa uz je pouzita");
		break;
	case QAbstractSocket::SocketAddressNotAvailableError:
		chybka->setText ("The address specified to QAbstractSocket::bind() does not belong to the host.");
		break;
	case QAbstractSocket::UnsupportedSocketOperationError:
		chybka->setText ("nepodporovana operace se sockety na systemu napr.IPv6");
		break;
	case QAbstractSocket::ProxyAuthenticationRequiredError:
		chybka->setText ("socket vyuziva proxy a proxy potrebuje autentifikaci");
		break;
	case QAbstractSocket::SslHandshakeFailedError:
		chybka->setText ("SSL handshake selhal");
		break;
	case QAbstractSocket::OperationError:
		chybka->setText ("chyba pri provadeni operace");
		break;
	case QAbstractSocket::TemporaryError:
		chybka->setText ("A temporary error occurred(e.g., operation would block and socket is non-blocking).");
		break;
	case QAbstractSocket::UnknownSocketError:
		chybka->setText ("neznama chyba se socketem");
		break;
	}
	chybka->exec ();
}