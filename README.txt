Frustum Interactive Development Environment
-------------------------------------------

Windows
-------

The supported native Windows setup uses Git Bash as the shell, GNU Make as the
build driver, and Visual Studio LLVM plus the Windows SDK as the C/C++ toolchain.

Prerequisites:
 - Windows 10 or 11
 - Git for Windows, including Git Bash
 - Visual Studio 2022 or Build Tools 2022 with these components:
   - Desktop development with C++ / MSVC x64 tools
   - C++ Clang tools for Windows
   - A Windows 10 or Windows 11 SDK
 - GNU Make 4.x

Install GNU Make from a normal Command Prompt or PowerShell window:

  winget install --id ezwinports.make --exact

Close any old terminal after installing it. From the fi repository root, run:

  startdev-windows.bat

This locates Visual Studio, initializes its x64 compiler and SDK environment,
selects TOOLCHAIN=llvm-msvc, and opens Git Bash. Verify the environment with:

  make --version
  clang++ --version

Projects can then be built in the usual way, for example:

  cd projects/fiApp/test
  make deepclean
  make

The shared templates also retain the old MinGW route. In an environment that
already provides MinGW-w64 GCC, select it with TOOLCHAIN=mingw.

Windows API compatibility is controlled centrally by WINDOWS_MIN_VERSION. The
default is 0x0601 (the Windows 7 API surface). A project can raise it when using
newer APIs, for example:

  make WINDOWS_MIN_VERSION=0x0A00

This controls declarations exposed by the Windows SDK; it does not by itself
guarantee that the selected compiler runtime supports an obsolete Windows release.

For Vulkan applications, also install the LunarG Vulkan SDK and open a fresh
development shell so VULKAN_SDK is available. Select the backend with:

  make EXTRACXXFLAGS=-DFI_GFX_VULKAN

The shared application and static-library templates propagate the SDK's Windows
Include directory to dependency builds. Applications must link Vulkan with
-L$(VULKAN_SDK)/Lib -lvulkan-1; the fiGfx scene test does this automatically.


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

For Vulkan development and the shader tools used by fiApp/fiGfx on Ubuntu:

  sudo apt update
  sudo apt install libvulkan-dev vulkan-tools glslang-tools xxd

The Vulkan loader also needs a driver for the installed GPU. For Intel and AMD
GPUs, install Ubuntu's Mesa Vulkan driver:

  sudo apt install mesa-vulkan-drivers

For NVIDIA GPUs, install Ubuntu's recommended proprietary NVIDIA driver. Confirm
that Vulkan can see the GPU with:

  vulkaninfo --summary

Ubuntu packages use the standard system include and library paths; VULKAN_SDK
does not need to be set. For example, run the fiGfx scene test with:

  cd projects/fiGfx/test/scene
  ./build_run.sh vulkan


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
