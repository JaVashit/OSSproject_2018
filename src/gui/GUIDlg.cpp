
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

	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);	//Default로 RAIO1 버튼 체크

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

		// Mat로 읽어오기
		Mat input_img = imread(img_path_temp, CV_LOAD_IMAGE_COLOR);
		// 원본 이미지를 변환하여 출력할 이미지 선언 & 초기화  dst_img : 컬러 , dst_img2 : 흑백
		Mat dst_img = Mat::zeros(input_img.size(), input_img.type());
		Mat dst_img2 = Mat::zeros(input_img.size(), input_img.type());

		// Mat to IplImage
		IplImage* ascii_img2 = new IplImage(dst_img);
		IplImage* ascii_img3 = new IplImage(dst_img2);

		//원본의 색을 저장하여 폰트의 색 결정
		Scalar color = 0;

		//각 픽셀이 폰트를 정할 때 사용하는 수치를 저장하기 위한 변수
		int insert_sum = 0;

		//출력에 사용될 단어
		char arr[17] = { '#','%','&','$','@','0','=','+','?','|','/','~','-','^','.','`',' ' };

		for (int i = 0; i <input_img.size().height; i += 1) {
			for (int j = 0; j < input_img.size().width; j += 1) {

				int color = 0;
				CvScalar ascii_color = 0;

				color += (input_img.at<Vec3b>(i, j)[0] + input_img.at<Vec3b>(i, j)[1]
					+ input_img.at<Vec3b>(i, j)[2]) / 3;
				ascii_color = input_img.at<Vec3b>(i, j);

				int pixel = (color / (2 * 2)); // Divide the calculated RGB mean value by the width of the square of size 2

				CvFont font;
				cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.6f, 0.6f, 0, 1, 8);
				char szText[2];

				if (pixel >= 0 && pixel <= 15) sprintf_s(szText, "%c", arr[0]);
				else if (pixel > 15 && pixel <= 30) sprintf_s(szText, "%c", arr[1]);
				else if (pixel > 30 && pixel <= 45) sprintf_s(szText, "%c", arr[2]);
				else if (pixel > 45 && pixel <= 60) sprintf_s(szText, "%c", arr[3]);
				else if (pixel > 60 && pixel <= 75) sprintf_s(szText, "%c", arr[4]);
				else if (pixel > 75 && pixel <= 90) sprintf_s(szText, "%c", arr[5]);
				else if (pixel > 90 && pixel <= 105) sprintf_s(szText, "%c", arr[6]);
				else if (pixel > 105 && pixel <= 120) sprintf_s(szText, "%c", arr[7]);
				else if (pixel > 120 && pixel <= 135) sprintf_s(szText, "%c", arr[8]);
				else if (pixel > 135 && pixel <= 150) sprintf_s(szText, "%c", arr[9]);
				else if (pixel > 150 && pixel <= 165) sprintf_s(szText, "%c", arr[10]);
				else if (pixel > 165 && pixel <= 180) sprintf_s(szText, "%c", arr[11]);
				else if (pixel > 180 && pixel <= 195) sprintf_s(szText, "%c", arr[12]);
				else if (pixel > 195 && pixel <= 210) sprintf_s(szText, "%c", arr[13]);
				else if (pixel > 210 && pixel <= 225) sprintf_s(szText, "%c", arr[14]);
				else if (pixel > 225 && pixel <= 240) sprintf_s(szText, "%c", arr[15]);
				else if (pixel > 240 && pixel <= 255) sprintf_s(szText, "%c", arr[16]);


				if (j % 10 == 0 && i % 5 == 0)
					cvPutText(ascii_img2, szText, cvPoint(j, i), &font, cvScalar(255, 255, 255));
				if (j % 14 == 0 && i % 18 == 0)
					cvPutText(ascii_img3, szText, cvPoint(j, i), &font, ascii_color);

			}

		}

		// 화면 출력		
		if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck() == TRUE) {	//IDC_RADIO1 의 check 값이 true 일 때,
																		// 화면 출력 : 흑백
			CWnd* pWnd = GetDlgItem(IDC_PIC);	//윈도우 생성
			pWnd->SetWindowPos(GetParent(), 10, 10, 266, 266, NULL);	//윈도우 크기와 위치 설정(시작x, 시작y, 가로, 세로)
			CClientDC dc(pWnd);
			CRect rect;
			pWnd->GetClientRect(&rect);

			CvvImage vImg;
			vImg.CopyOf(ascii_img2, 1);	//이미지를 받아서 (옵션값 0=흑백, 1=컬러)
			vImg.DrawToHDC(dc.m_hDC, &rect);	//출력
			imwrite("grayscale_image.jpg", dst_img); // 이미지 저장
		}
		else if (((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck() == TRUE) {
			// 화면 출력 : 컬러
			CWnd* pWnd = GetDlgItem(IDC_PIC);
			pWnd->SetWindowPos(GetParent(), 10, 10, 266, 266, NULL);
			CClientDC dc(pWnd);
			CRect rect;
			pWnd->GetClientRect(&rect);

			CvvImage vImg;
			vImg.CopyOf(ascii_img3, 1);
			vImg.DrawToHDC(dc.m_hDC, &rect);
			imwrite("color_image.jpg", dst_img2); // 이미지 저장
		}
	}
}
