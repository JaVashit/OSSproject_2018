#include "stdafx.h"
#include "GUI.h"
#include "GUIDlg.h"
#include "afxdialogex.h"
#include "opencv2\highgui.hpp"
#include "CvvImage.h"	//화면출력에 필요

using namespace cv;
using namespace std;

void PrintAscii_img(CGUIDlg* pDlg, IplImage* ascii_img, Mat dst_img, string file_name) {
	
	CWnd* pWnd = pDlg->GetDlgItem(IDC_PIC);
	pWnd->SetWindowPos(pDlg->GetParent(), 10, 10, 266, 266, NULL);	//윈도우 크기와 위치 설정(시작x, 시작y, 가로, 세로)
	CClientDC dc(pWnd);
	CRect rect;
	pWnd->GetClientRect(&rect);

	CvvImage vImg;
	vImg.CopyOf(ascii_img, 1);	//이미지를 받아서 (옵션값 0=흑백, 1=컬러)
	vImg.DrawToHDC(dc.m_hDC, &rect);	//출력
	imwrite(file_name, dst_img); // 이미지 저장
}