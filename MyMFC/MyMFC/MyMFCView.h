
// MyMFCView.h : CMyMFCView 类的接口
//

#pragma once


class CMyMFCView : public CView
{
protected: // 仅从序列化创建
	CMyMFCView();
	DECLARE_DYNCREATE(CMyMFCView)

// 特性
public:
	CMyMFCDoc* GetDocument() const;
	int m_red,m_green,m_blue;
	int x,y;
// 操作
public:
	
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMyMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CPoint m_ptStart;
	CPoint m_ptEnd;
	bool m_bTrack;
// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMenu();
};

#ifndef _DEBUG  // MyMFCView.cpp 中的调试版本
inline CMyMFCDoc* CMyMFCView::GetDocument() const
   { return reinterpret_cast<CMyMFCDoc*>(m_pDocument); }
#endif

