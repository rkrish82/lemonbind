for %%I in (.) do set CWD=%%~nI
winrar a -v -r -s -ag-YYYY.MM.DD-HH.MM.SS -x*.rar -x*.7z %CWD%
