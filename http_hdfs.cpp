// http_hdfs.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <tchar.h>
#include <atlconv.h>
#include "libwebhdfs.h"



//���̻ص�����
void WebHdfs_OnProcedure(LPCTSTR lpDesc)
{
	USES_CONVERSION;
		printf("01���̻ص�����\r\n");
	printf(T2A((LPTSTR)lpDesc));
	printf("\r\n");
}

//�ϴ��ص�����
void WebHdfs_OnUpload(LPCTSTR lpFileID, double nTotalSize, double nLoadSize)
{
	USES_CONVERSION;
	printf("02�ϴ��ص�����\r\n");
	double fschedule = nLoadSize/(double)nTotalSize;
	printf("�ϴ�[%s]-����[%d]\n", T2A((LPTSTR)lpFileID),  (int)(fschedule*100));
}

//���ػص�����
void WebHdfs_OnDownload(LPCTSTR lpFileID, double nTotalSize, double nLoadSize)
{
	USES_CONVERSION;
	printf("03���ػص�����\r\n");
	double fschedule = nLoadSize/nTotalSize;
	printf("����[%s]-����[%d]\n", T2A((LPTSTR)lpFileID), (int)(fschedule*100));
}

int _tmain(int argc, _TCHAR* argv[])
{
	//���ó���ǰĿ¼
	TCHAR lpszFilePath [_MAX_PATH] = {0};
	TCHAR path_buffer[_MAX_PATH] = {0};
	if (GetModuleFileName (NULL, lpszFilePath, _MAX_PATH) > 0) {
		TCHAR drive[_MAX_DRIVE];   
		TCHAR dir[_MAX_DIR];
		_tsplitpath_s (lpszFilePath, drive, _MAX_DRIVE, dir, _MAX_DIR, NULL, 0, NULL, 0);
		_tmakepath_s (path_buffer, _MAX_PATH, drive, dir, NULL, NULL);
		SetCurrentDirectory(path_buffer);
	}

	int iErrcode = 0;
	LPCTSTR lpErrInfo = NULL;

	//����WEBHDFS����
	WebHdfs_Client hdfs = Create_WebHdfsClient(TEXT("10.81.1.4"), 14000, TEXT("root"), TEXT(""));
	if (!hdfs)
	{
		iErrcode = WebHdfsClient_GetLastError(hdfs);
		lpErrInfo = WebHdfsClient_GetLastErrorDesc(hdfs);
		return -1;
	}
	BOOL bResult = FALSE;
	WebHdfsClient_OnProcedure(hdfs, WebHdfs_OnProcedure);
	WebHdfsClient_OnUpload(hdfs, WebHdfs_OnUpload);
	WebHdfsClient_OnDownload(hdfs, WebHdfs_OnDownload);

	//TEXT("C:\\others\\11.zip")
	//TEXT("D:\\VS2008SP1CHSX1512981.iso");

	//�ϴ��ļ�
	TCHAR FileID[MAX_PATH] = {0};
	bResult = WebHdfsClient_UploadFile(hdfs, TEXT("D:\\tesqt.txt"), FileID, MAX_PATH);
	if (!bResult)
	{
		iErrcode = WebHdfsClient_GetLastError(hdfs);
		lpErrInfo = WebHdfsClient_GetLastErrorDesc(hdfs);
	}

	////�����ļ�
	//bResult = WebHdfsClient_DownLoadFile(hdfs, FileID, TEXT("D:\\HadoopHttp.zip"));
	//if (!bResult)
	//{
	//	iErrcode = WebHdfsClient_GetLastError(hdfs);
	//	lpErrInfo = WebHdfsClient_GetLastErrorDesc(hdfs);
	//}

	Destroy_WebHdfsClient(hdfs);

	system("pause");
	return 0;
}

