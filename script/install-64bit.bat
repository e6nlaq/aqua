
@echo off

"%systemroot%\system32\openfiles.exe" > NUL 2>&1
if %errorlevel% neq 0 (
	echo Please start with administrator privileges.
	pause
	exit /B 0
)

pushd %~dp0..\
set Aquapath=%CD%
popd

call path/64.bat
@REM del /q "%Aquapath%\install\path.bat"
pause

"%systemroot%\system32\reg.exe" add "HKEY_CLASSES_ROOT\.aqua" /d Aqua.Script /f
"%systemroot%\system32\reg.exe" add "HKEY_CLASSES_ROOT\Aqua.Script" /d "Aqua Script File" /f
"%systemroot%\system32\reg.exe" add "HKEY_CLASSES_ROOT\Aqua.Script\DefaultIcon" /d "%Aquapath%\image\aqua.ico" /f
"%systemroot%\system32\reg.exe" add "HKEY_CLASSES_ROOT\Aqua.Script\shell\open\command" /d "%Aquapath%\bin\x64\aqua.exe ""%%1""" /f
