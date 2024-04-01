
// MyMFCView.cpp : CMyMFCView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MyMFC.h"
#endif

#include "MyMFCDoc.h"
#include "MyMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyMFCView

IMPLEMENT_DYNCREATE(CMyMFCView, CView)

BEGIN_MESSAGE_MAP(CMyMFCView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMyMFCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_Menu, &CMyMFCView::OnMenu)
END_MESSAGE_MAP()

// CMyMFCView ����/����

CMyMFCView::CMyMFCView()
{
	// TODO: �ڴ˴���ӹ������
	m_red=m_green=m_blue=0;
	x=600;y=300;
	m_bTrack=false;
}

CMyMFCView::~CMyMFCView()
{
}

BOOL CMyMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMyMFCView ����

void CMyMFCView::OnDraw(CDC* pDC)
{
	CMyMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	
	pDC->SetTextColor(RGB(m_red,m_green,m_blue));
	pDC->TextOut(x,y,_T("Hell World"));
	
	//pDC->LineTo(x,y);
	
	
	pDC->SelectStockObject(ANSI_FIXED_FONT);
	pDC->TextOut(10,0,_T("������һ��Բ"));
	//pDC->TextOut(10,0,"������һ��Բ");
	pDC->MoveTo(10,16);
	pDC->LineTo(115,16);
	pDC->SelectStockObject(GRAY_BRUSH);
	pDC->Ellipse(10,20,210,220);
	
}


// CMyMFCView ��ӡ


void CMyMFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMyMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMyMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMyMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CMyMFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//ClientToScreen(&point);
	//OnContextMenu(this, point);

	//����Ԥ�ȱ༭�õĲ˵�
	CMenu menu;		//�˵�
	CMenu *pSubMenu;//�Ҽ��˵�

	menu.LoadMenu(IDR_MYMENU);
	pSubMenu=menu.GetSubMenu(0);
	ClientToScreen(&point);
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);
}

void CMyMFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMyMFCView ���

#ifdef _DEBUG
void CMyMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CMyMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyMFCDoc* CMyMFCView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyMFCDoc)));
	return (CMyMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyMFCView ��Ϣ�������


void CMyMFCView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_red=rand()%255;
	m_green=rand()%255;
	m_blue=rand()%255;
	InvalidateRect(false);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMyMFCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	/*
	x=point.x;
	y=point.y;
	InvalidateRect(false);
	*/
	m_bTrack=true;
	m_ptStart=point;
	m_ptEnd=point;
	SetCapture();

	CView::OnLButtonDown(nFlags, point);
}


void CMyMFCView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDC *pDC=GetDC();
	if(m_bTrack)
	{
		pDC->SetROP2(R2_NOT);
		pDC->MoveTo(m_ptStart);
		pDC->LineTo(m_ptEnd);
		//pDC->Rectangle(m_ptStart.x,m_ptStart.y,m_ptEnd.x,m_ptEnd.y);
		pDC->SetROP2(R2_COPYPEN);
		pDC->MoveTo(m_ptStart);
		pDC->LineTo(point);
		//pDC->Rectangle(m_ptStart.x,m_ptStart.y,m_ptEnd.x,m_ptEnd.y);
		m_ptEnd=point;
		
	}
	ReleaseCapture();
	m_bTrack=false;

	CView::OnLButtonUp(nFlags, point);
}


void CMyMFCView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDC *pDC=GetDC();
	if(m_bTrack)
	{
		
		pDC->SetROP2(R2_NOT);
		pDC->MoveTo(m_ptStart);
		pDC->LineTo(m_ptEnd);
		//pDC->Rectangle(m_ptStart.x,m_ptStart.y,m_ptEnd.x,m_ptEnd.y);
		pDC->SetROP2( R2_COPYPEN);
		pDC->MoveTo(m_ptStart);
		pDC->LineTo(point);
		//pDC->Rectangle(m_ptStart.x,m_ptStart.y,m_ptEnd.x,m_ptEnd.y);
		m_ptEnd=point;
		
	}
	CView::OnMouseMove(nFlags, point);
}




void CMyMFCView::OnMenu()
{
	MessageBox(_T("TestMenu"));
	// TODO: �ڴ���������������
}
