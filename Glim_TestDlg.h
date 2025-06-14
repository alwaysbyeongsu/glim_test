
// Glim_TestDlg.h: 헤더 파일
//
#pragma once
#include <vector>
#define WM_USER_UPDATE_RANDOM_POS (WM_USER + 100)
using namespace std;

// CGlimTestDlg 대화 상자
class CGlimTestDlg : public CDialogEx
{
private:
	CImage m_image;
// 생성입니다.
public:
	CGlimTestDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIM_TEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	LRESULT ReDraw(WPARAM wParam, LPARAM lParam);
	void Reset();
	void DragReset();
	void DrawCircle(unsigned char* fm, int x, int y, float radius, int color);
	void DrawCircleCenter(unsigned char* fm, int x, int y, float radius, int color);
	bool InCircle(int i, int j, int centerX, int centerY, float radius);
	CircleInfo CalculateCircle(vector<POINT> points);
	void DrawCircleOutline(unsigned char* fm, int width, int height, int pitch, float x, float y, float radius, int thickness, int color);
	POINT GetRandomPos();
	static UINT RandomMoveThreadProc(LPVOID param);
	void ClearBuffer();
	int GetRandomInt(int start, int end);
public:
	int m_iNowPosX;
	int m_iNowPosY;
	CString m_strPosX;
	CString m_strPosY;
	afx_msg void OnBnClickedCancel();
	int m_iWidth = 1920;
	int m_iHeight = 1080;
	int m_iBpp = 8;
	unsigned char* m_fm;
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	bool bCheckStart = false;
	vector<POINT> m_vPoints; // 3개의 점 위치보관
	vector<int> m_vSize;
	vector<int> m_vColor;
	RECT m_rect; // 클릭범위
	bool m_bDragging = false; // 드래그 중 확인 여부
	int m_iDragIndex = -1; // -1 이면 선택된 점 없음
	POINT m_ptDragStart; // 드래그 시작 마우스 좌표
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	int m_iCirlceThickness = 0;
	afx_msg void OnBnClickedButtonRandom();
	CWinThread* m_pRandomThread;
	bool m_bThreadCheck = false;

	int m_iColor;
	double m_dThickness;
	double m_dCircleThickness;
	int m_iCircleColor;

public:
	int m_ipointX;
	int m_ipointY;
};
