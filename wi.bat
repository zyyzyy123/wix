@echo off
rem wiģ��vi
rem PZYYΪ1��������,0����,2·������,3�������ĵ�
rem �ӳٱ��������ر�
goto MAIN
rem /////////////////////////////////////////////////////////////////////////////////////////������
rem===================================================�� New(target_path)
:New
type nul> "%~f1" 2>nul
goto :eof
rem===================================================New	END
rem===================================================�� Open(target_path��EXC��EXCp)
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



rem======================================���Ի�
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
rem======================================����

start  /max %2 %~3  "%~f1" 2>nul 1>nul
goto :eof
rem===================================================Open	END




rem====================================================�� Doc(target_path��EXC��EXCp)
rem====================================================Doc	END




rem===================================================SX(d Ŀ¼��- �ļ���N ����) Dir_check_simple(target_path)   
:Dir_check_simple
set SX=%~a1N
set SX=%SX:~0,1%
goto :eof
rem===================================================Dir_check_simple	END








rem /////////////////////////////////////////////////////////////////////////////////////////������
:MAIN
rem==================================��ʼ��
set MY=%~f0
set DP=%~d0%~p0
set PZYY=1
rem MYΪ����λ��
rem DPΪ����·��

rem==================================����
if %1H == H (
set PZYY=0
goto CHECK
)

if %1 == --help (
set PZYY=0
goto CHECK
)
rem==================================�򿪴˽ű�
if %1 == \\\ (	
set PZYY=3
start /B /max notepad %MY% 2>nul 1>nul
goto CHECK
)
rem==================================�򿪰����ĵ�
if %1 == \\\h (
set PZYY=3
start /B /max notepad %DP%help\%~n0.txt 2>nul 1>nul
goto CHECK
)
rem==================================���ļ�
call :Dir_check_simple  %1 SX  
if %SX% == - (
call :Open %1 %2 %3
)

if %SX% == d (
rem call :Doc %1 %2 %3	//ȥ����Ŀ¼ģ��
set PZYY=2
)

if %SX% == N (
goto :step2
)

goto CHECK
rem==================================�����ļ�
:step2
call :New %1
call :Dir_check_simple  %1 SX
if %SX% == - (
call :Open %1 %2 %3
)else (
set PZYY=2
)

goto CHECK








rem /////////////////////////////////////////////////////////////////////////////////////////////������
:CHECK
if %PZYY%==0 (
type %DP%help\%~n0.txt
)
if %PZYY%==2 (
echo �ļ������Ϸ� ���� ��һ��Ŀ¼ ���� ���ڹ���Աģʽ��ִ��
)
if %PZYY%==1 (
echo ��·��"%~f1"
)








rem //////////////////////////////////////////////////////////////////////////////////////////////�������
set PZYY=
set MY=
set DP=
