@echo off
rem wi模拟vi
rem PZYY为1正常启用,0帮助,2路径错误,3打开内置文档
rem 延迟变量开启关闭
goto MAIN
rem /////////////////////////////////////////////////////////////////////////////////////////函数区
rem===================================================无 New(target_path)
:New
type nul> "%~f1" 2>nul
goto :eof
rem===================================================New	END
rem===================================================无 Open(target_path，EXC，EXCp)
:Open
if %2H == H (
start  "" "%~f1"
goto :eof
)
if %2 == :0 (
goto :eof
)
if %2 == :r (
type  "%~f1"
set PZYY=r
goto :eof
)



rem======================================个性化
if %2 == code (
%2  %~3  "%~f1" 2>nul 1>nul
goto :eof
)

if %2 == vim (
%2  %~3  "%~f1" 2>nul
goto :eof
)

if %2 == :v (
vim  %~3  "%~f1" 2>nul
goto :eof
)

if %2 == :n (
start /max notepad %~3  "%~f1" 2>nul 1>nul
goto :eof
)

if %2 == :n+ (
start /max notepad++ %~3  "%~f1" 2>nul 1>nul
goto :eof
)
rem======================================其他

start  /max %2 %~3  "%~f1" 2>nul 1>nul
goto :eof
rem===================================================Open	END




rem====================================================无 Doc(target_path，EXC，EXCp)
rem====================================================Doc	END




rem===================================================SX(d 目录，- 文件，N 错误) Dir_check_simple(target_path)   
:Dir_check_simple
set SX=%~a1N
set SX=%SX:~0,1%
goto :eof
rem===================================================Dir_check_simple	END








rem /////////////////////////////////////////////////////////////////////////////////////////主函数
:MAIN
rem==================================初始化
set MY=%~f0
set DP=%~d0%~p0
set PZYY=1
rem MY为程序位置
rem DP为程序路径

rem==================================帮助
if %1H == H (
set PZYY=0
goto CHECK
)

if %1 == --help (
set PZYY=0
goto CHECK
)
rem==================================打开此脚本
if %1 == \\\ (	
set PZYY=3
start /B /max notepad %MY% 2>nul 1>nul
goto CHECK
)
rem==================================打开帮助文档
if %1 == \\\h (
set PZYY=3
start /B /max notepad %DP%help\%~n0.txt 2>nul 1>nul
goto CHECK
)
rem==================================打开文件
call :Dir_check_simple  %1 SX  
if %SX% == - (
call :Open %1 %2 %3
)

if %SX% == d (
rem call :Doc %1 %2 %3	//去掉了目录模块
set PZYY=2
)

if %SX% == N (
goto :step2
)

goto CHECK
rem==================================创建文件
:step2
call :New %1
call :Dir_check_simple  %1 SX
if %SX% == - (
call :Open %1 %2 %3
)else (
set PZYY=2
)

goto CHECK








rem /////////////////////////////////////////////////////////////////////////////////////////////检查错误
:CHECK
if %PZYY%==0 (
type %DP%help\%~n0.txt
)
if %PZYY%==2 (
echo 文件名不合法 或者 是一个目录 或者 请在管理员模式下执行
)
if %PZYY%==1 (
echo 打开路径"%~f1"
)








rem //////////////////////////////////////////////////////////////////////////////////////////////清理变量
set PZYY=
set MY=
set DP=
