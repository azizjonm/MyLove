
// MyLoveView.cpp : CMyLoveView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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

// CMyLoveView 构造/析构

CMyLoveView::CMyLoveView()
{
	// TODO:  在此处添加构造代码

}

CMyLoveView::~CMyLoveView()
{
}

BOOL CMyLoveView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMyLoveView 绘制

void CMyLoveView::OnDraw(CDC* /*pDC*/)
{
	CMyLoveDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CMyLoveView 诊断

#ifdef _DEBUG
void CMyLoveView::AssertValid() const
{
	CView::AssertValid();
}

void CMyLoveView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyLoveDoc* CMyLoveView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyLoveDoc)));
	return (CMyLoveDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyLoveView 消息处理程序
