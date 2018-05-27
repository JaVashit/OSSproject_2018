#include "stdafx.h"
#include "GUI.h"
#include "GUIDlg.h"
#include "afxdialogex.h"
#include "opencv2\highgui.hpp"
#include "CvvImage.h"	//ȭ����¿� �ʿ�

using namespace cv;
using namespace std;

void PrintAscii_img(CGUIDlg* pDlg, IplImage* ascii_img, Mat dst_img, string file_name) {
	
	CWnd* pWnd = pDlg->GetDlgItem(IDC_PIC);
	pWnd->SetWindowPos(pDlg->GetParent(), 10, 10, 266, 266, NULL);	//������ ũ��� ��ġ ����(����x, ����y, ����, ����)
	CClientDC dc(pWnd);
	CRect rect;
	pWnd->GetClientRect(&rect);

	CvvImage vImg;
	vImg.CopyOf(ascii_img, 1);	//�̹����� �޾Ƽ� (�ɼǰ� 0=���, 1=�÷�)
	vImg.DrawToHDC(dc.m_hDC, &rect);	//���
	imwrite(file_name, dst_img); // �̹��� ����
}

void PrintAscii_vid(VideoWriter outputVideo, Mat dst, CGUIDlg* pDlg, IplImage* IplImage_img) {
	outputVideo << dst;
	CWnd* pWnd = pDlg->GetDlgItem(IDC_PIC);
	pWnd->SetWindowPos(pDlg->GetParent(), 10, 10, 266, 266, NULL);
	CClientDC dc(pWnd);
	CRect rect;
	pWnd->GetClientRect(&rect);

	CvvImage vImg;
	vImg.CopyOf(IplImage_img, 1);
	vImg.DrawToHDC(dc.m_hDC, &rect);
}