#ifdef BUILD_DLL
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
#endif
#define DEBUG_Command 0

EXPORT int check_dir(char* Target_Path);
/*
function:�鿴·��ΪĿ¼���ļ�
input:target_path(ȫ·��)
output:1(�ļ�),2(Ŀ¼),0(������)
*/
EXPORT int CreateFL(char* Target_Path);
/*
function:�����ļ�,·�����Ϸ����ļ��в�����ʱʧ��,����ɹ�
input:target_path(ȫ·��)
output:0(ʧ��),1(�ɹ�)
*/
EXPORT int CreateDoc(char* Target_Path);
/*
function:����Ŀ¼,·�����Ϸ����ļ��в�����ʱʧ��,����ɹ�
input:target_path(ȫ·��)
output:0(ʧ��),1(�ɹ�)
*/

EXPORT int CommandLine(char argv_EXC[],char argv_EXCp[],char argv_Target_Path[],int select);
/*
function:����Ŀ¼,·�����Ϸ����ļ��в�����ʱʧ��,����ɹ�
input:target_path(ȫ·��)
output:0(ʧ��),1(�ɹ�)
*/                                 
//���к���,select=cmd/porcess

EXPORT int Q_Path(char Path_in[],char Path_out[]);
/*
function:·������""
*/                                 
