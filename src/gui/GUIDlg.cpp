
// GUIDlg.cpp: 구현 파일
//


#include "stdafx.h"
#include "GUI.h"
#include "GUIDlg.h"
#include "afxdialogex.h"
#include "opencv2\highgui.hpp"
#include "CvvImage.h"	//화면출력에 필요

#include "pixelation.h";
#include "print.h";

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
	ON_BN_CLICKED(IDC_BUTTON2, &CGUIDlg::OnBnClickedButton2)
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
	CGUIDlg* pDlg = (CGUIDlg*)AfxGetApp()->GetMainWnd(); //a global function to access the main window

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

		Pixelation_img(input_img, ascii_img2, ascii_img3);

		// 화면 출력		
		if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck() == TRUE) {	//IDC_RADIO1 의 check 값이 true 일 때,
			// 화면 출력 : 흑백
			PrintAscii_img(pDlg, ascii_img2, dst_img, "grayscale_image.jpg");
		}
		else if (((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck() == TRUE) {
			// 화면 출력 : 컬러
			PrintAscii_img(pDlg, ascii_img3, dst_img2, "color_image.jpg");
		}
	}
}

void CGUIDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CGUIDlg* pDlg = (CGUIDlg*)AfxGetApp()->GetMainWnd(); //a global function to access the main window

	char szFilter[] = " All Files(*.*)|*.*|";
	
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, (CString)szFilter, NULL);
		
	if (IDOK == dlg.DoModal()) {
		// 이미지 경로 획득
		CString img_path = dlg.GetPathName();
		CStringA img_path_A(img_path);
		LPCSTR img_path_temp = img_path_A;
		String name = img_path_A;
		
		VideoCapture video(name);
		
		Mat frame;
		Mat dst;
		Mat dst2;
	
		//로드한 동영상에서 캡쳐되는 이미지 크기를 가져옴   
		Size size = Size((int)video.get(CAP_PROP_FRAME_WIDTH), (int)video.get(CAP_PROP_FRAME_HEIGHT));
		video.set(CAP_PROP_FPS, 30.0);
	
		//파일로 동영상을 저장하기 위한 준비  
		VideoWriter outputVideo;
		outputVideo.open("ouput.mp4", VideoWriter::fourcc('D', 'I', 'V', 'X'), 30, size, true);
		
		int pixel = 0;
		char arr[17] = { '#','%','&','$','@','0','=','+','?','|','/','~','-','^','.','`',' ' };
	
		//dst와 dst2 를 초기화하기 위해 동영상의 한 프레임을 가져옴
		video >> frame;
		dst = Mat::zeros(frame.size(), frame.type());
		IplImage* IplImage_img = new IplImage(dst);					//cvPutText를 하기 위해 포맷을 변환 해줌
		dst2 = Mat::zeros(frame.size(), frame.type());
		IplImage* IplImage_img2 = new IplImage(dst2);				//cvPutText를 하기 위해 포맷을 변환 해줌
	
		while (1) {
			//로드한 동영상으로부터 한 프레임을 읽어옴  
			video >> frame;

			Pixelation_vid(frame, pixel, arr, IplImage_img, IplImage_img2);
			
			//로드한 동영상에서 캡처되는 속도를 가져옴
			int fps = video.get(CAP_PROP_FPS);
			int wait = int(1.0 / fps * 1000);
	
			//동영상이 끝나거나, ESC키 누르면 종료
			if (frame.data == NULL || waitKey(wait) == 27) break;
	
			//동영상 파일에 한프레임을 저장함.  			
			if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck() == TRUE) {
				// 화면 출력 : 흑백
				//dst에 출력 비디오의 한 프레임을 저장함
				PrintAscii_vid(outputVideo, dst, pDlg, IplImage_img);
			}
			else if (((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck() == TRUE) {
				// 화면 출력 : 컬러
				//dst2에 출력 비디오의 한 프레임을 저장함
				PrintAscii_vid(outputVideo, dst2, pDlg, IplImage_img2);
			}
		
			//쓰여진 dst와 dst2를 지움
			dst = Mat::zeros(frame.size(), frame.type());
			dst2 = Mat::zeros(frame.size(), frame.type());
		}
	}
}