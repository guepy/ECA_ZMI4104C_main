@ECHO off

:: ===========================================
:: soleil_env.bat :
:: script de declaration des
:: variables d'environements utiles pour le
:: developpement de TANGO, a configurer
:: ===========================================
:: les variables suivantes sont dependantes
:: de la configuration de la plateforme :
:: modifier les variables "xxx_ROOT"
:: et supprimer "::" (commentaires)
::
:: RQ : il peut etre pratique de copier ce
:: fichier dans %SOLEIL_ROOT%\tango\bin qui est
:: ecrit en dur dans la variable path
:: ===========================================
::
:: ======== DEVICE SERVERS PATHS

SET PSDK=C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2
CALL "C:\Program Files\Microsoft Visual Studio 8\VC\bin\vcvars32.bat"


:: ======== PYTHON PATHS
SET PYTHON_ROOT=c:\Python25
SET PATH=%PYTHON_ROOT%;%PATH%
SET PYTHONPATH=%SOLEIL_ROOT%\bindings\python\python25;%PYTHONPATH%

goto end

:: :ERROR_NO_VCDIR
:: echo ERROR: "C:\Program Files\Microsoft Visual Studio 8" does not exist
:: goto end

:: :ERROR_NO_SDKDIR
:: echo ERROR: "C:\Program Files\Microsoft SDKs\Windows\v6.0" does not exist
:: goto end

:end

