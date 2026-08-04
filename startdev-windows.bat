@echo off
setlocal

set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%VSWHERE%" (
    echo ERROR: Visual Studio Installer's vswhere.exe was not found.
    exit /b 1
)

for /f "usebackq tokens=*" %%I in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "VSINSTALL=%%I"
if not defined VSINSTALL (
    echo ERROR: No Visual Studio installation with the x64 C++ tools was found.
    exit /b 1
)

call "%VSINSTALL%\Common7\Tools\VsDevCmd.bat" -arch=x64
if errorlevel 1 exit /b %errorlevel%

set "GIT_BASH=%ProgramFiles%\Git\bin\bash.exe"
if not exist "%GIT_BASH%" (
    echo ERROR: Git for Windows Bash was not found at "%GIT_BASH%".
    exit /b 1
)

set "BASH_EMU=1"
set "TOOLCHAIN=llvm-msvc"

rem winget portable packages publish command aliases here. Include it explicitly
rem so a newly-installed GNU Make works even before Windows refreshes PATH.
if exist "%LOCALAPPDATA%\Microsoft\WinGet\Links\make.exe" set "PATH=%PATH%;%LOCALAPPDATA%\Microsoft\WinGet\Links"

where make.exe >nul 2>nul
if errorlevel 1 (
    echo WARNING: GNU Make is not on PATH.
    echo Install it with: winget install --id ezwinports.make --exact
    echo.
)

echo Starting Git Bash with the Visual Studio x64 and Windows SDK environment.
echo Default repository toolchain: %TOOLCHAIN%
"%GIT_BASH%" --login -i

endlocal
