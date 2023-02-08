
@echo off


"%systemroot%\system32\openfiles.exe" > NUL 2>&1
if %errorlevel% neq 0 (
	echo Please start with administrator privileges.
	pause
	exit /B 0
)

echo Remove any and all Aqua from the registry.
echo Please delete the PATH environment variable manually.
pause

"%systemroot%\system32\reg.exe" delete "HKEY_CLASSES_ROOT\Aqua.Script" /f
"%systemroot%\system32\reg.exe" delete "HKEY_CLASSES_ROOT\.aqua" /f
"%systemroot%\system32\reg.exe" delete "HKEY_CLASSES_ROOT\Aqua.Script\DefaultIcon" /f
"%systemroot%\system32\reg.exe" delete "HKEY_CLASSES_ROOT\Aqua.Script\shell\open\command" /f
