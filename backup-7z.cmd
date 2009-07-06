@echo off
setlocal
set line=%DATE%
:parse_date
for /F "delims=/ tokens=1,*" %%a in ("%line%") do (
   set line=%%b
   set now=%%a.%now%
)
if "%line%" neq "" goto parse_date
set now=%now:~0,10%
set now=%now%-%TIME:~0,8%
set now=%now::=.%
for %%I in (.) do set CWD=%%~nI
7z a -mx9 -r -x!*.rar -x!*.7z %CWD%-%now%.7z
endlocal
