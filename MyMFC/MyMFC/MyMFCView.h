
// MyMFCView.h : CMyMFCView ��Ľӿ�
//

#pragma once


class CMyMFCView : public CView
{
protected: // �������л�����
	CMyMFCView();
	DECLARE_DYNCREATE(CMyMFCView)

// ����
public:
	CMyMFCDoc* GetDocument() const;
	int m_red,m_green,m_blue;
	int x,y;
// ����
public:
	
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
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
// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // MyMFCView.cpp �еĵ��԰汾
inline CMyMFCDoc* CMyMFCView::GetDocument() const
   { return reinterpret_cast<CMyMFCDoc*>(m_pDocument); }
#endif

