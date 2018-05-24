
// GUIDlg.cpp: 구현 파일
//


#include "stdafx.h"
#include "GUI.h"
#include "GUIDlg.h"
#include "afxdialogex.h"
#include "opencv2\highgui.hpp"
#include "CvvImage.h"	//화면출력에 필요

using namespace cv;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGUIDlg 대화 상자



CGUIDlg::CGUIDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GUI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CGUIDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CGUIDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CGUIDlg 메시지 처리기

BOOL CGUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGUIDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void CGUIDlg::OnBnClickedButton1()
{
	char szFilter[] = " All Files(*.*)|*.*|";

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, (CString)szFilter, NULL);
	
	if (IDOK == dlg.DoModal()) {

		// 이미지 경로 획득
		CString img_path = dlg.GetPathName();
		CStringA img_path_A(img_path);
		LPCSTR img_path_temp = img_path_A;

		// IplImage로 읽어오기
		IplImage* input_img = cvLoadImage(img_path_A);
		
		// Picture Control에 이미지 출력
		if (input_img) {
			CWnd* pWnd = GetDlgItem(IDC_PIC);
			pWnd->SetWindowPos(GetParent(), 10, 10, 266, 266, NULL);
			CClientDC dc(pWnd);
			CRect rect;
			pWnd->GetClientRect(&rect);

			CvvImage vImg;
			vImg.CopyOf(input_img, 1);
			vImg.DrawToHDC(dc.m_hDC, &rect);

		}
		
		// 원본 이미지를 변환하여 출력할 이미지 선언 & 초기화  dst_img : 컬러 , dst_img2 : 흑백
		IplImage* dst_img = cvCreateImage(cvSize(input_img->width, input_img->height), input_img->depth, input_img->nChannels);
		IplImage* dst_img2 = cvCreateImage(cvSize(input_img->width, input_img->height), IPL_DEPTH_8U, 1);

		//원본의 색을 저장하여 폰트의 색 결정
		Scalar color = 0;

		//각 픽셀이 폰트를 정할 때 사용하는 수치를 저장하기 위한 변수
		int insert_sum = 0;

		//출력에 사용될 단어
		char arr[10] = { '@','$','0' ,'=' ,'+' ,'|' ,'-' ,'^' ,'.' ,' ' };

		for (int y = 0; y < input_img->height; y = y + 2) {
			for (int x = 0; x < input_img->width; x = x + 2) {

				color = cvGet2D(input_img, y, x);

				for (int c = 0; c < 3; c++) {
					insert_sum = insert_sum + color.val[c];

				}

				insert_sum = (insert_sum / 3);

				//		fontFace(int) - 폰트 타입
				//		hscale(float) - 너비 지정
				//		vscale(float) - 높이 지정
				//		shear(float) - 폰트 기울기
				//		thickness(int) - 폰트 선 두께
				//		lineType(int) - 폰트 선 타입

				CvFont font;
				cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.5f, 0.5f, 0, 1, 8);
				char szText[10];

				if (insert_sum >= 0 && insert_sum <= 25) {
					sprintf_s(szText, "%c", arr[0]);
				}
				else if (insert_sum > 25 && insert_sum <= 50) {
					sprintf_s(szText, "%c", arr[1]);
				}
				else if (insert_sum > 50 && insert_sum <= 75) {
					sprintf_s(szText, "%c", arr[2]);
				}
				else if (insert_sum > 75 && insert_sum <= 100) {
					sprintf_s(szText, "%c", arr[3]);
				}
				else if (insert_sum > 100 && insert_sum <= 125) {
					sprintf_s(szText, "%c", arr[4]);
				}
				else if (insert_sum > 125 && insert_sum <= 150) {
					sprintf_s(szText, "%c", arr[5]);
				}
				else if (insert_sum > 150 && insert_sum <= 175) {
					sprintf_s(szText, "%c", arr[6]);
				}
				else if (insert_sum > 175 && insert_sum <= 200) {
					sprintf_s(szText, "%c", arr[7]);
				}
				else if (insert_sum > 200 && insert_sum <= 225) {
					sprintf_s(szText, "%c", arr[8]);
				}
				else if (insert_sum > 225 && insert_sum <= 255) {
					sprintf_s(szText, "%c", arr[9]);
				}

				cvPutText(dst_img, szText, cvPoint(x, y), &font, cvScalar(color.val[0], color.val[1], color.val[2]));
				cvPutText(dst_img2, szText, cvPoint(x, y), &font, cvScalar(color.val[0], color.val[1], color.val[2]));
				insert_sum = 0;
			}
		}

		// 화면 출력
		//opencv 출력
		//cvShowImage("dst", dst_img);
		//cvShowImage("dst2", dst_img2);
	}
}