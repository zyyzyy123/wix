#===============================================================================��ʼ��
param (                        													#�����в�����
	[String]$arg1,
	[String]$arg2,
	[String]$arg3
)
$MY=$MyInvocation.Mycommand.Definition 											#���ű�·��
$DP=Split-Path -Parent $MyInvocation.Mycommand.Definition						#���ű������ļ���
$NAME=[System.IO.Path]::GetFileNameWithoutExtension($MY)
$Dir_Simple=$DP+"\C_space\bin\Dir_Simple.exe"
$Open=$DP+"\C_space\bin\Open.exe"
$New=$DP+"\C_space\bin\New.exe"
$arg1=$arg1.Replace("\","/")
#===============================================================================ps
if($arg1.contains("*") -eq 1){
Write-Host "·�������Ϸ� ���� ���ڹ���Աģʽ��ִ��"
return 
}

if( ($arg1.CompareTo("") -eq 0) -or ($arg1.CompareTo("--help") -eq 0)){
& $Open ($DP+"\help\"+$NAME+".txt"+" 1 :r").Split()
return 
}
elseif($arg1.CompareTo("///") -eq 0){
& $Open ($MY+" 1 :n+").Split()
return
}
elseif($arg1.CompareTo("///h")  -eq 0){
& $Open ($DP+"\help\"+$NAME+".txt"+" 1 :n").Split()
return
}
#===============================================================================main
& $Dir_Simple ("`""+$arg1+"`"").Split()
$x1=$LASTEXITCODE

#���ƻ���ɾ�����нӿ�
if($arg2.CompareTo(":r") -eq 0){
	if($x1 -eq 2){
	dir $arg1
	}
	elseif($x1 -eq 1){
	& $Open ("`""+$arg1+"`""+" "+$x1+" "+$arg2+" "+$arg3).Split()
	}
	elseif($x1 -eq 0){
	Write-Host "��·��������"
	}
	return
}



if($x1 -eq 0){
& $New ("`""+$arg1+"`""+" "+$x1).Split()
& $Dir_Simple ("`""+$arg1+"`"").Split()
$x1=$LASTEXITCODE
}




if($x1 -eq 0){
Write-Host "·�������Ϸ� ���� ���ڹ���Աģʽ��ִ��"
return 
}

& $Open ("`""+$arg1+"`""+" "+$x1+" "+$arg2+" "+$arg3).Split()

#===============================================================================ps

#���ƻ����������нӿ�
if($arg2.CompareTo(":c") -eq 0){
 if($x1 -eq 2){
 cd $arg1
 }
 elseif($x1 -eq 1){
 cd $arg1+"/.."
 }
}
#===============================================================================swicthд��
#switch -case ($arg0){
#	"" {$PZYY="0";}																
#	"--help" {$PZYY="0"}														
#	"\\\" {$PZYY="h";notepad $MY}												
#	default {
#	}
#}
