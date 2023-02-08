
@echo off

"%systemroot%\system32\openfiles.exe" > NUL 2>&1
if %errorlevel% neq 0 (
	echo Please start with administrator privileges.
	pause
	exit /B 0
)

pushd %~dp0..\..\
set Aquapath=%CD%
popd

setx /M PATH "%PATH%; %Aquapath%\bin\x64"

exit /b 0