
// MyLoveView.h : CMyLoveView ��Ľӿ�
//

#pragma once


class CMyLoveView : public CView
{
protected: // �������л�����
	CMyLoveView();
	DECLARE_DYNCREATE(CMyLoveView)

// ����
public:
	CMyLoveDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CMyLoveView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MyLoveView.cpp �еĵ��԰汾
inline CMyLoveDoc* CMyLoveView::GetDocument() const
   { return reinterpret_cast<CMyLoveDoc*>(m_pDocument); }
#endif

