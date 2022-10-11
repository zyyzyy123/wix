@echo off

goto Main
:BatCd
if %Result%H == 1H (
cd /D "%~dp1"
)
if %Result%H == 2H (
cd /D "%~f1"
)
goto :eof

:CmdDo
if %1H == H (
%Open% %HelpDoc% 1 :r
set BatEnd=1
goto :eof
)

if %1 == --help (
%Open% %HelpDoc% 1 :r
set BatEnd=1
goto :eof
)

if %1 == \\\ (
%Open% "%~f0" 1 :n+
set BatEnd=1
goto :eof
)

if %1 == \\\h (
%Open% %HelpDoc% 1 :n
set BatEnd=1
goto :eof
)

set temp=%~1
set head=%temp:~0,1%
set tail=%temp:~-1%
if %head%H == *H (
echo 文件名不合法 或者 是一个目录 或者 请在管理员模式下执行
set BatEnd=1
goto :eof
)


if %Result%H == 0H (
echo 文件名不合法 或者 是一个目录 或者 请在管理员模式下执行
set BatEnd=1
goto :eof
)

if %arg2%H == :cH (
call :BatCd %1
set BatEnd=0
goto :eof
)

set BatEnd=0

goto :eof


:Main
set Dir_Simple=%~d0%~p0\C_space\bin\Dir_Simple.exe
set Open=%~d0%~p0\C_space\bin\Open.exe
set New=%~d0%~p0\C_space\bin\New.exe
set HelpDoc=%~d0%~p0\help\%~n0.txt
set arg=%1
set arg1=%arg:\=/%
set arg2=%2
set arg3=%~3
call :CmdDo %1 %2 %3
if %BatEnd%H == 1H (
goto :eof
)

%Dir_Simple% %arg1%
set x1=%errorlevel%

if %arg2%H == :rH (
%Open% %arg1% %x1%  %arg2%  %arg3%
set Result=%x1%
goto :ElseDo
)

%Open% %arg1% %x1%  %arg2%  %arg3%

if %x1% == 0 (
goto :ReOpen
)

set Result=%x1%
goto :ElseDo

:ReOpen
%New% %arg1% %x1%
%Dir_Simple% %arg1%
set x2=%errorlevel%
%Open% %arg1% %x2%  %arg2%  %arg3%
set Result=%x2%
goto :ElseDo

:ElseDo
call :CmdDo %1 %2 %3
set BatEnd=
set x1=
set x2=
set Result=
set temp=
set head=
set Dir_Simple=
set Open=
set New=
set helpDoc=
set arg1=
set arg2=
set arg3=