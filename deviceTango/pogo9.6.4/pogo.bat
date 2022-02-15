@ECHO OFF

GOTO SCRIPT_BEGIN
REM **********************************************************************
REM *
REM * Revision: start-pogo.bat
REM * Author:   N.leclercq
REM * Date:     04/25/2003
REM * Purpose:  Launch Pogo
REM *
REM **********************************************************************
:SCRIPT_BEGIN

set TANGO_ROOT=%~dp0\..\..

start javaw -cp Pogo-9.6.4.jar org.tango.pogo.pogo_gui.Pogo %*

:SCRIPT_END
