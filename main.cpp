#include "header.h"
#include "gui.h"
#include "mujserver.h"
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
 int main(int argv, char **args)
         {
              QApplication app(argv, args);
			  mujserver * server=new mujserver ();
			  gui * mojegui =new gui (server);

			  return app.exec();
         }