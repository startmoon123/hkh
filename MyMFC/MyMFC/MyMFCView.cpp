
// MyMFCView.cpp : CMyMFCView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
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

// CMyMFCView 构造/析构

CMyMFCView::CMyMFCView()
{
	// TODO: 在此处添加构造代码
	m_red=m_green=m_blue=0;
	x=600;y=300;
	m_bTrack=false;
}

CMyMFCView::~CMyMFCView()
{
}

BOOL CMyMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMyMFCView 绘制

void CMyMFCView::OnDraw(CDC* pDC)
{
	CMyMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	
	pDC->SetTextColor(RGB(m_red,m_green,m_blue));
	pDC->TextOut(x,y,_T("Hell World"));
	
	//pDC->LineTo(x,y);
	
	
	pDC->SelectStockObject(ANSI_FIXED_FONT);
	pDC->TextOut(10,0,_T("下面是一个圆"));
	//pDC->TextOut(10,0,"下面是一个圆");
	pDC->MoveTo(10,16);
	pDC->LineTo(115,16);
	pDC->SelectStockObject(GRAY_BRUSH);
	pDC->Ellipse(10,20,210,220);
	
}


// CMyMFCView 打印


void CMyMFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMyMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMyMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMyMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMyMFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//ClientToScreen(&point);
	//OnContextMenu(this, point);

	//加载预先编辑好的菜单
	CMenu menu;		//菜单
	CMenu *pSubMenu;//右键菜单

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


// CMyMFCView 诊断

#ifdef _DEBUG
void CMyMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CMyMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyMFCDoc* CMyMFCView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyMFCDoc)));
	return (CMyMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyMFCView 消息处理程序


void CMyMFCView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_red=rand()%255;
	m_green=rand()%255;
	m_blue=rand()%255;
	InvalidateRect(false);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMyMFCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加命令处理程序代码
}
