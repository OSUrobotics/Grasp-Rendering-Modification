#Grasp-Rendering-Modification

##Programs to know:
* OpenGL
  * OpenGL is a low level API that is used to interact with the GPU to render 3D applications. OpenGL only handles actual rendering, and provides no API for user input, audio or windowing.
* Qt
  * Qt is a window manager that can be used to display 3D rendered programs. It is useful for developing standalone code outside the OpenRAVE program. The ExaminerViewer window used by OpenRAVE to display the simulation is implemented in Qt.
* Open Inventor
  * Open Inventor is a high level, retained mode toolkit that was designed to speed up the programming process for 3D applications. This program uses groups of objects arranged into a scene graph that is traversed when rendering happens. Originally an open-source program, it became closed-source in 2012 when it was bought by FEI company, which keeps documentation for versions 8.6+. An example Open Inventor Scene Graph is shown below.
   
  
![alt text](http://i.imgur.com/DjcyUOH.gif "Example Open Inventor Scene Graph")

* Coin/Coin3D
  * Coin3D is a open source clone of the Open Inventor API. It was developed by Kongsberg Oil & Gas Technologies from 1998 to 2011. The latest stable release, version 3.1.3, was released March 2010, and is fully compatible with the Open Inventor version 2.1 API.
* OpenRAVE
  * OpenRAVE is the grasp simulation framework that


##Important OpenRAVE files:
* qtcoinviewer.cpp
  * This file contains the code that initializes the coin3D environment. It also implements message classes that send update messages to the threading software. However these do not actually seem to  be used(?)
* environment-core.hpp
  * This file implements the handling of the message classes created from qtcoinviewer.cpp. This file also implements Environment(), which keeps track of the simulation environment.
* openravepy_viewer.cpp
* renderToTexture.cpp
* viewer.h
* warmcoolFrag.glsl/warmcoolVert.glsl
