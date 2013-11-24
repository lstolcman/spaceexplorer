@echo off
set buildpath=%cd%
set current=%cd%

FOR /R .\src %%G IN (*.hpp *.cpp) DO call:UNCRUSTFILE "%%G"
goto:eof

:UNCRUSTFILE
set pathstr="%~1"
if not %pathstr:3rd=%==%pathstr% goto:eof
uncrustify --no-backup -c "%buildpath%\uncrustify.cfg" "%~1"
cd %buildpath%
goto:eof
