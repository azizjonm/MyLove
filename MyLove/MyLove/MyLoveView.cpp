
// MyLoveView.cpp : CMyLoveView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MyLove.h"
#endif

#include "MyLoveDoc.h"
#include "MyLoveView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyLoveView

IMPLEMENT_DYNCREATE(CMyLoveView, CView)

BEGIN_MESSAGE_MAP(CMyLoveView, CView)
END_MESSAGE_MAP()

// CMyLoveView ����/����

CMyLoveView::CMyLoveView()
{
	// TODO:  �ڴ˴���ӹ������

}

CMyLoveView::~CMyLoveView()
{
}

BOOL CMyLoveView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMyLoveView ����

void CMyLoveView::OnDraw(CDC* /*pDC*/)
{
	CMyLoveDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMyLoveView ���

#ifdef _DEBUG
void CMyLoveView::AssertValid() const
{
	CView::AssertValid();
}

void CMyLoveView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyLoveDoc* CMyLoveView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyLoveDoc)));
	return (CMyLoveDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyLoveView ��Ϣ�������
