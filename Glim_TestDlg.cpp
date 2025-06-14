
// Glim_TestDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include <vector>
#include <Windows.h>
#include "Glim_Test.h"
#include "Glim_TestDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <algorithm>
#include <random>

#ifdef _DEBUG
#define new DEBUG_NEW
#pragma comment(linker, "/entry:WinMainCRTStartup /Subsystem:console")
#endif

using namespace std;


static int g_OffSetY = 50;

#define WM_USER_UPDATE_RANDOM_POS (WM_USER + 100)

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


// CGlimTestDlg 대화 상자



CGlimTestDlg::CGlimTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIM_TEST_DIALOG, pParent)
	, m_iNowPosX(0)
	, m_iNowPosY(0)
	, m_strPosX(_T("x"))
	, m_strPosY(_T("y"))
	, m_iColor(100)
	, m_dThickness(5)
	, m_dCircleThickness(3)
	, m_iCircleColor(100)
	, m_ipointX(0)
	, m_ipointY(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGlimTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_iNowPosX);
	DDX_Text(pDX, IDC_EDIT2, m_iNowPosY);
	DDX_Text(pDX, IDC_STATIC_X, m_strPosX);
	DDX_Text(pDX, IDC_STATIC_Y, m_strPosY);
	DDX_Text(pDX, IDC_EDIT_COLOR, m_iColor);
	DDX_Text(pDX, IDC_EDIT_THICKNESS, m_dThickness);
	DDX_Text(pDX, IDC_EDIT_CIRCLE_THICKNESS, m_dCircleThickness);
	DDX_Text(pDX, IDC_EDIT_COLOR2, m_iCircleColor);
	DDX_Text(pDX, IDC_EDIT3, m_ipointX);
	DDX_Text(pDX, IDC_EDIT4, m_ipointY);
}

BEGIN_MESSAGE_MAP(CGlimTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CGlimTestDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CGlimTestDlg::OnBnClickedButtonReset)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_RANDOM, &CGlimTestDlg::OnBnClickedButtonRandom)
	ON_MESSAGE(WM_USER_UPDATE_RANDOM_POS, &CGlimTestDlg::ReDraw)
END_MESSAGE_MAP()


// CGlimTestDlg 메시지 처리기

BOOL CGlimTestDlg::OnInitDialog()
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

void CGlimTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGlimTestDlg::OnPaint()
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
HCURSOR CGlimTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGlimTestDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

LRESULT CGlimTestDlg::ReDraw(WPARAM wParam, LPARAM lParam)
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, g_OffSetY);
	return 0;
}

void CGlimTestDlg::Reset()
{
	if (m_bThreadCheck == true) return;

	if (m_image.IsNull())
	{
		m_image.Create(m_iWidth, m_iHeight, m_iBpp);
	}
	if (m_fm == nullptr)
	{
		m_fm = (unsigned char*)m_image.GetBits();
	}


	if (m_iBpp == 8)
	{
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; ++i)
		{
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_image.SetColorTable(0, 256, rgb);
	}

	ClearBuffer();
	//memset(m_fm, 255, m_iWidth * m_iHeight);

	CClientDC dc(this);
	m_image.Draw(dc, 0, g_OffSetY);

	m_rect.left = 0;
	m_rect.right = 1920;
	m_rect.top = 50;
	m_rect.bottom = 1080 + m_rect.top;
	m_vPoints.clear();
	m_vSize.clear();
	m_vColor.clear();
	m_iDragIndex = -1;
	bCheckStart = true;
}

void CGlimTestDlg::DragReset()
{
	m_iDragIndex = -1;       
	//bCheckStart = false;      

	ClearBuffer();
	m_vPoints.clear();

	CClientDC dc(this);
	m_image.Draw(dc, 0, g_OffSetY);          // 화면 다시 그리기

}

void CGlimTestDlg::DrawCircle(unsigned char* fm, int x, int y, float radius, int color)
{
	int iCenterX = x + radius;
	int iCenterY = y + radius;
	int iPitch = m_image.GetPitch();
	for (int j = y; j < y + radius * 2; ++j)
	{
		for (int i = x; i < x + radius * 2; ++i)
		{
			if (InCircle(i, j, iCenterX, iCenterY, radius))
			{
				fm[j * iPitch + i] = color;
			}
		}
	}

}

void CGlimTestDlg::DrawCircleCenter(unsigned char* fm, int x, int y, float radius, int color)
{
	int iPitch = m_image.GetPitch();

	for (int j = (int)(y - radius); j <= (int)(y + radius); ++j)
	{
		for (int i = (int)(x - radius); i <= (int)(x + radius); ++i)
		{
			if (i >= 0 && i < m_iWidth && j >= 0 && j < m_iHeight)
			{
				if (InCircle(i, j, x, y, radius))
				{
					fm[j * iPitch + i] = color;
				}
			}
		}
	}
}

bool CGlimTestDlg::InCircle(int i, int j, int centerX, int centerY, float radius)
{
	bool bRet = false;

	double dX = i - centerX;
	double dY = j - centerY;
	double dDist = dX * dX + dY * dY;

	if (dDist <= radius * radius)
	{
		bRet = true;
	}

	return bRet;
}

CircleInfo CGlimTestDlg::CalculateCircle(vector<POINT> points)
{
	CircleInfo result = { 0,0,0,false };

	float x1 = points[0].x, y1 = points[0].y;
	float x2 = points[1].x, y2 = points[1].y;
	float x3 = points[2].x, y3 = points[2].y;

	float a = x1 * (y2 - y3) - y1 * (x2 - x3) + x2 * y3 - x3 * y2;
	if (fabs(a) < 1e-6) return result; // 세점이 일직선인 경우 예외처리

	float A1 = x1 * x1 + y1 * y1;
	float B1 = x2 * x2 + y2 * y2;
	float C1 = x3 * x3 + y3 * y3;

	float D = 2.0f * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
	if (fabs(D) < 1e-6f) return result;

	float Ux = (A1 * (y2 - y3) + B1 * (y3 - y1) + C1 * (y1 - y2)) / D;
	float Uy = (A1 * (x3 - x2) + B1 * (x1 - x3) + C1 * (x2 - x1)) / D;

	float dx = x1 - Ux;
	float dy = y1 - Uy;
	float r = sqrt(dx * dx + dy * dy);

	result.fcx = Ux;
	result.fcy = Uy;
	result.fradius = r;
	result.bvalid = true;

	//DrawCircleCenter(m_fm, (int)Ux , (int)Uy , (int)r, 155);

	return result;
}

void CGlimTestDlg::DrawCircleOutline(unsigned char* fm, int width, int height, int pitch, float x, float y, float radius, int thickness, int color)
{
	int rMin = max(0, (int)(radius - thickness / 2));
	int rMax = (int)(radius + thickness / 2);

	for (int j = (int)(y - rMax); j <= (int)(y + rMax); ++j)
	{
		for (int i = (int)(x - rMax); i <= (int)(x + rMax); ++i)
		{
			if (i < 0 || i >= width || j < 0 || j >= height)
				continue;

			float dx = i - x;
			float dy = j - y;
			float dist = sqrt(dx * dx + dy * dy);

			if (dist >= rMin && dist <= rMax)
			{
				int index = j * pitch + i;
				fm[index] = (unsigned char)color;
			}
		}
	}
}

POINT CGlimTestDlg::GetRandomPos()
{
	POINT Rdpt;

	/*random_device rd;
	mt19937_64 gen(rd());
	uniform_int_distribution<> disX(m_rect.left + 20, m_rect.right - 20);
	uniform_int_distribution<> disY(m_rect.top + 20, m_rect.bottom - 20);

	Rdpt.x = disX(gen);
	Rdpt.y = disY(gen);*/
	Rdpt.x = rand() % (m_iWidth / 2);
	Rdpt.y = rand() % (m_iHeight / 2);


	return Rdpt;
}

UINT CGlimTestDlg::RandomMoveThreadProc(LPVOID param)
{
	CGlimTestDlg* pDlg = reinterpret_cast<CGlimTestDlg*>(param);
	const int repeatCount = 10;
	const int delayMs = 500;

	for (int i = 0; i < repeatCount; ++i)
	{
		if (!pDlg->m_hWnd) break;

		
		for (int j = 0; j < 3; ++j)
		{
			pDlg->m_vPoints[j] = pDlg->GetRandomPos();
			pDlg->m_vSize[j] = pDlg->GetRandomInt(5 ,30);
			pDlg->m_vColor[j] = pDlg->GetRandomInt(0, 250);
		}
		pDlg->m_iCircleColor = pDlg->GetRandomInt(0, 250);

		if (pDlg->m_vPoints.size() == 3)
		{
			CircleInfo Info = pDlg->CalculateCircle(pDlg->m_vPoints);

			pDlg->ClearBuffer();

			//for (auto& iter : pDlg->m_vPoints)
			//{
			//	pDlg->DrawCircleCenter(pDlg->m_fm, iter.x, iter.y, pDlg->m_dThickness, 100);
			//}

			for (int k = 0; k < pDlg->m_vPoints.size(); ++k)
			{
				pDlg->DrawCircleCenter(pDlg->m_fm, pDlg->m_vPoints[k].x, pDlg->m_vPoints[k].y,
					pDlg->m_vSize[k], pDlg->m_vColor[k]);
			}

			pDlg->DrawCircleOutline(pDlg->m_fm, pDlg->m_image.GetWidth(), pDlg->m_image.GetHeight(), pDlg->m_image.GetPitch(), Info.fcx, Info.fcy, Info.fradius, pDlg->m_dCircleThickness, pDlg->m_iCircleColor);

		}
		::PostMessage(pDlg->m_hWnd, WM_USER_UPDATE_RANDOM_POS, 0, 0);

		Sleep(delayMs);
	}
	pDlg->m_bThreadCheck = false;

	return 0;
}

void CGlimTestDlg::ClearBuffer()
{
	for (int j = 0; j < m_iHeight; ++j)
	{
		for (int i = 0; i < m_iWidth; ++i)
		{
			m_fm[j * m_image.GetPitch() + i] = 255;
		}
	}  // 화면 버퍼 클리어
}

int CGlimTestDlg::GetRandomInt(int start, int end)
{
	
	return (rand() % (end - start + 1)) + start;
}

void CGlimTestDlg::OnBnClickedButtonReset()
{
	Reset();
}


void CGlimTestDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (!m_fm)
	{
		return;
	}

	if (PtInRect(&m_rect, point)) // 사각형 박스 안 체크
	{
		UpdateData(true);
		POINT clickpt = point;
		clickpt.y -= g_OffSetY; // offset조정
		int radius = static_cast<int>(m_dThickness); // 클릭감지범위

		for (int i = 0; i < m_vPoints.size(); ++i) // 3개의 점중 클릭된 점 체크
		{
			POINT pt = m_vPoints[i];
			int dx = pt.x - clickpt.x;
			int dy = pt.y - clickpt.y;
			if ((dx * dx + dy * dy) <= radius * radius)
			{
				m_ipointX = m_vPoints[i].x;
				m_ipointY = m_vPoints[i].y;
				break;
			}
			else
			{
				m_ipointX = 0;
				m_ipointY = 0;
			}
		}
		UpdateData(false);
	}


	if (bCheckStart) // 초기화 or 시작 후 체크
	{
		//float radius = 5.f;

		UpdateData(true);
		CDialogEx::OnMouseMove(nFlags, point);
		m_iNowPosX = point.x/* - m_dThickness*/;
		m_iNowPosY = point.y - g_OffSetY/* - m_dThickness*/;

		if (m_iNowPosX < 0 || m_iNowPosY < 0)
		{
			return;
		}

		UpdateData(false);
	}

	if (m_bDragging && m_iDragIndex != -1 && m_iDragIndex < m_vPoints.size()) // 드래그 상태인지 체크
	{
		POINT crrpt = point;
		crrpt.y -= g_OffSetY; // 오프셋 조정

		// 시작점부터 현재 움직이는 위치계산
		int dx = crrpt.x - m_ptDragStart.x;
		int dy = crrpt.y - m_ptDragStart.y;

		m_vPoints[m_iDragIndex].x += dx;
		m_vPoints[m_iDragIndex].y += dy;

		m_ptDragStart = crrpt;


		ClearBuffer();

		if (m_vPoints.size() == 3) // 3번째 점이 찍혔을 때 
		{
			CircleInfo Info = CalculateCircle(m_vPoints);
			DrawCircleOutline(m_fm, m_image.GetWidth(), m_image.GetHeight(), m_image.GetPitch(), Info.fcx, Info.fcy, Info.fradius, m_dCircleThickness, m_iColor);
		}

		//for (auto iter : m_vPoints)
		//{
		//	DrawCircleCenter(m_fm, iter.x, iter.y, m_dThickness, m_iColor);
		//}
		for (int i = 0; i < m_vPoints.size(); ++i)
		{
			DrawCircleCenter(m_fm, m_vPoints[i].x, m_vPoints[i].y,
				m_vSize[i], m_vColor[i]);
		}

		CClientDC dc(this);
		m_image.Draw(dc, 0, g_OffSetY);
	}
}


void CGlimTestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (point.x < 0 || point.y < 50 ||
		point.x >= 1920 || point.y >= g_OffSetY + 1080)
	{
		return;
	}
	if (PtInRect(&m_rect, point)) // 사각형 박스 안 체크
	{
		POINT clickpt = point;
		clickpt.y -= g_OffSetY; // offset조정

		int radius = static_cast<int>(m_dThickness); // 클릭감지범위
		m_iDragIndex = -1;
		for (int i = 0; i < m_vPoints.size(); ++i) // 3개의 점중 클릭된 점 체크
		{
			POINT pt = m_vPoints[i];
			int iDragX = pt.x - clickpt.x;
			int iDragY = pt.y - clickpt.y;
			if ((iDragX * iDragX + iDragY * iDragY) <= radius * radius)
			{
				m_iDragIndex = i;
				break;
			}
		}

		if (m_iDragIndex != -1) // 점이 클릭 됬을 때
		{
			m_bDragging = true;
			m_ptDragStart = clickpt;
			SetCapture();
		}
		else if (m_vPoints.size() < 3) // 점이 3개가 안될 때 
		{
			float radius = m_dThickness;
			//int x = point.x - (int)radius;
			//int y = (point.y - g_OffSetY) - (int)radius;
			POINT pt;
			
			pt.x = point.x;
			pt.y = (point.y - g_OffSetY);

			DrawCircleCenter(m_fm, pt.x, pt.y, radius, m_iColor);

			m_vPoints.push_back(pt);
			m_vSize.push_back(m_dThickness);
			m_vColor.push_back(m_iColor);

			if (m_vPoints.size() == 3) // 3번째 점이 찍혔을 때 
			{
				CircleInfo Info = CalculateCircle(m_vPoints);
				DrawCircleOutline(m_fm, m_image.GetWidth(), m_image.GetHeight(),m_image.GetPitch(), Info.fcx, Info.fcy, Info.fradius, m_dCircleThickness, m_iColor);
			}

			CClientDC dc(this);
			m_image.Draw(dc, 0, g_OffSetY);
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CGlimTestDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_bDragging)
	{
		m_bDragging = false;
		m_iDragIndex = -1;
		ReleaseCapture();
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CGlimTestDlg::OnBnClickedButtonRandom()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_bThreadCheck == true || m_vPoints.size() != 3) return;

	m_bThreadCheck = true;
	m_pRandomThread = AfxBeginThread(RandomMoveThreadProc, this);

}
