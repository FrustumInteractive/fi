Frustum Interactive Development Environment
-------------------------------------------

Windows
-------
To develope under windows, the latest version of Git is required with git bash enabled (preferred).
The windows command line can be used as well, although there is a risk of less makefile support.

There are external packages required for building such as GCC/CLang.
The MinGW/GCC package for windows is minGW.tar.gz which should be extracted in the extern/minGW folder.
This is where the startdev.sh script points to in order to build.
When git bash is installed, running startdev.sh sets the environment for the required build tools.
If windows cmd line is used instead then startdev.bat should be called first to set environment.


Mac OS
------
Xcode and commandline developer tools should be first installed.
Once complete, the projects in projects/ folder can be built by calling 'make'.


Linux
-----
latest GCC should be installed.
In ubuntu 'sudo apt-get install build-essential' should work.
other deps:
  sudo apt install libx11-dev
  sudo apt install mesa-common-dev

Hardware accellerated graphics drivers with at least OpenGL 3.2 support are required
development libraries for those drivers are also needed. 


General
-------
To checkout projects:
  'cd projects' [you should be in /DEV/fi/projects/ for example.]
  'git clone git@github.com:FrustumInteractive/<project_name>.git'

its important to keep the same reponame for your repo since the build system will look for it in
the directory structure.

When inside the project directory you can use some shell script tools:
 - './cleanall' -> cleans all projects and their test folders
 - './statusall' -> does a git status on all projects to see if there are commits/changes pending
 - './updateall' -> does a git pull on all projects to make sure they're up to date.


Projects
--------
example repos when in projects folder:
  git@github.com:FrustumInteractive/fiApp.git (x-platform applications)
  git@github.com:FrustumInteractive/fiMath.git (matrices/vectors)


The above repos are for some of the static libs that comprise the FI codebase.
Inside each checked out directory, there is typically a 'test' folder. Calling 'make' inside
the test folder should build an executible which tests the funtionality of that library.
Any subsequent library creation should follow this scheme.


Makefiles
--------- 
inside templates/ folder there are makefile templates.
To build a new application, templates/Makefile_application can be copied to the new project's folder
  `ex: cp ../../templates/makefile_application Makefile`
This new makefile can then be edited to add general source files, platform specific source, library dependencies,
and triggering library dependencies to be built ('DEPENDENCIES').
