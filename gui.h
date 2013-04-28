#ifndef GUI
#define GUI
#include "header.h"
#include "mujserver.h"
class gui:public QWidget
{
	Q_OBJECT
private:
	int port;
	QString textZpravy,adresa;
	QWidget *widget,*widget2;
	QComboBox * listClients;
	QPushButton * kickClient,*kickAllClients,*sendMsg,*startServer,*stopServer,*nastavit;
	QHBoxLayout * layout,*layout2;
	QVBoxLayout * Vlayout;
	QTextBrowser * stavovyText;
	QLineEdit *portEdit,*zpravaEdit;
	mujserver * server;
	QLabel *popisekPort,*popisekZprava;
	void init ();
	void setlayout ();
	void Connect ();
public:
	gui (mujserver * server);
	private slots:
	void stop ();
	void start ();
	void KickAll();
	void kick ();
	void send ();
	void SendAll ();
	void nastav ();
};
#endif GUI