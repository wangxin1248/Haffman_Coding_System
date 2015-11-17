
// 哈夫曼编译码系统Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// C哈夫曼编译码系统Dlg 对话框
class C哈夫曼编译码系统Dlg : public CDialogEx
{
// 构造
public:
	C哈夫曼编译码系统Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_record;
	afx_msg void OnBnClickedButton4();
	CString str;
	int lastLine;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	int m_num;
	CString m_element;
	CString m_weight;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
