
// MyLoveView.h : CMyLoveView 类的接口
//

#pragma once


class CMyLoveView : public CView
{
protected: // 仅从序列化创建
	CMyLoveView();
	DECLARE_DYNCREATE(CMyLoveView)

// 特性
public:
	CMyLoveDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CMyLoveView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MyLoveView.cpp 中的调试版本
inline CMyLoveDoc* CMyLoveView::GetDocument() const
   { return reinterpret_cast<CMyLoveDoc*>(m_pDocument); }
#endif

