#include "gui.h"
#include "mujserver.h"
gui::gui (mujserver * server)
{
	this->server=server;
	init ();
	setlayout ();
	Connect ();
	show ();
}
void gui::start ()
{
	server->start (port);
}
void gui::stop ()
{
	server->stop ();
}
void gui::kick ()
{
	
}
void gui::KickAll ()
{
	server->KickAll ();
}
void gui::send ()
{
	QString text=zpravaEdit->text ();
	server->send (text);
}
void gui::SendAll ()
{

}
void gui::nastav ()
{
	QString portS=portEdit->text ();
	port=portS.toInt ();
	startServer->setEnabled (true);
	stopServer->setEnabled (true);
	sendMsg->setEnabled (true);
	kickClient->setEnabled (true);
	kickAllClients->setEnabled (true);
}
void gui::init ()
{
	
	 popisekPort=new QLabel ("port");
	popisekZprava=new QLabel ("zprava");
	kickClient=new QPushButton ("vykopnout klienta");
	kickAllClients=new QPushButton ("vykopnout vsechny klienty");
	sendMsg=new QPushButton ("posli zpravu");
	startServer=new QPushButton ("nastartovat");
	stopServer=new QPushButton ("stop");
	nastavit=new QPushButton ("nastavit");
	layout=new QHBoxLayout ();
	 layout2=new QHBoxLayout ();
	 Vlayout=new QVBoxLayout ();
	listClients=new QComboBox ();
	portEdit=new QLineEdit ();
	zpravaEdit=new QLineEdit ();
	 widget=new QWidget (this);
	widget2=new QWidget (this);
	startServer->setEnabled (false);
	stopServer->setEnabled (false);
	sendMsg->setEnabled (false);
	kickClient->setEnabled (false);
	kickAllClients->setEnabled (false);
}
void gui::setlayout ()
{
	layout->addWidget (kickClient);
	layout->addWidget (kickAllClients);
	layout->addWidget (nastavit);
	layout->addWidget (startServer);
	layout->addWidget (stopServer);
	layout->addWidget (listClients);
	layout2->addWidget (popisekPort);
	layout2->addWidget (portEdit);
	layout2->addWidget (popisekZprava);
	layout2->addWidget (zpravaEdit);
	layout->addWidget (sendMsg);
	widget->setLayout (layout);
	widget2->setLayout (layout2);
	Vlayout->addWidget (widget);
	Vlayout->addWidget (widget2);
	this->setLayout (Vlayout);
}
void gui::Connect ()
{
	connect (startServer,SIGNAL (clicked ()),this,SLOT (start()));
	connect (stopServer,SIGNAL (clicked ()),this,SLOT (stop()));
	connect (kickClient,SIGNAL (clicked ()),this,SLOT (kick()));
	connect (kickAllClients,SIGNAL (clicked ()),this,SLOT (KickAll()));
	connect (sendMsg,SIGNAL (clicked ()),this,SLOT (send()));
	connect (nastavit,SIGNAL (clicked()),this,SLOT (nastav()));
}

