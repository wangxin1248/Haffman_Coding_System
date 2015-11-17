
// 哈夫曼编译码系统Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "哈夫曼编译码系统.h"
#include "哈夫曼编译码系统Dlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <malloc.h>
#include <stdio.h>
#include<fstream>
#include<stdlib.h>
#include<math.h>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
struct HaffNode
{
	int weight;
	int parent;
	int lchild;
	int rchild;
};
struct HaffCode
{
	int *bit;
	int start;
	int weight;
	char data;
};
typedef struct
{
	int weight;                  
	int parent, lchild, rchild;    
}HTNode, *HuffmanTree;
typedef char **HuffmanCode;



/*全局变量*/
HuffmanTree HT;//代表哈夫曼树
HuffmanCode HC;//代表哈夫曼编码
HaffNode *ht;//哈夫曼节点指针
HaffCode *hc;//哈夫曼编码指针
int *w, *b, i, j, n;//w权值,n大小
char *a;//存放字符
int flag = 0;//标识
int numb = 0;//计数
SYSTEMTIME st;
CString strDate, strTime;
CString getTime() {
	GetLocalTime(&st);
	strTime.Format("%2d:%2d:%2d-->", st.wHour, st.wMinute, st.wSecond);
	return strTime;
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C哈夫曼编译码系统Dlg 对话框



C哈夫曼编译码系统Dlg::C哈夫曼编译码系统Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
	, m_num(0)
	, m_element(_T(""))
	, m_weight(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C哈夫曼编译码系统Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_record);
	DDX_Text(pDX, IDC_EDIT2, m_num);
	DDX_Text(pDX, IDC_EDIT3, m_element);
	DDX_Text(pDX, IDC_EDIT4, m_weight);
}

BEGIN_MESSAGE_MAP(C哈夫曼编译码系统Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON4, &C哈夫曼编译码系统Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &C哈夫曼编译码系统Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &C哈夫曼编译码系统Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &C哈夫曼编译码系统Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON1, &C哈夫曼编译码系统Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &C哈夫曼编译码系统Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// C哈夫曼编译码系统Dlg 消息处理程序

BOOL C哈夫曼编译码系统Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // 在最后一行添加新的内容

	str.Format(_T("初始化系统... ...\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // 在最后一行添加新的内容

	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // 在最后一行添加新的内容

	str.Format(_T("下面初始化赫夫曼链表,请在右边输入字符元素大小,并点击保存\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // 在最后一行添加新的内容

	/*设置其他按钮为不可用*/
	GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON7)->EnableWindow(false);
	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C哈夫曼编译码系统Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮,则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序
//  这将由框架自动完成。

void C哈夫曼编译码系统Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C哈夫曼编译码系统Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



/*取最小*/
int minx(HuffmanTree t, int i)
{
	int j, flag;
	int k = 1000; // 取k为不可能小于的值
	for (j = 1;j <= i;j++)
		if (t[j].weight<k&&t[j].parent == 0)
			k = t[j].weight, flag = j;
	t[flag].parent = 1;
	return flag;     //返回最小值位置
}
void select(HuffmanTree t, int i, int &s1, int &s2)
{
	int j;
	s1 = minx(t, i);//调用minx函数
	s2 = minx(t, i);
	if (s1>s2)// s1为最小的两个值中序号小的那个
	{
		j = s1;
		s1 = s2;
		s2 = j;
	}
}


/*画二叉树*/
void paint(CDC *pDC, int parent, int x, int y, int c, int d)//c表示该节点的层次,d表示该节点与其父的左右关系
{
	double pi = 3.14;//用于计算分支度数
	int ix, iy, ix0, iy0;
	float hd1, hd2;
	/*确定hd1 hd2值*/
	if (c % 2 == 0 && d != 4)
	{	
		hd1 = pi / 6;
		hd2 = pi / 3; 
	}
	else 
	{ 
		hd1 = pi / 3;
		hd2 = pi / 6; 
	}
	/*调用三角函数确定偏移量*/
	ix0 = 50 * cos(hd1);
	iy0 = 50 * sin(hd1);
	/*左递归调用*/
	if (ht[parent].lchild != -1)
	{
		paint(pDC, ht[parent].lchild, x - ix0, y + iy0, c + 1, -1);
	}
	
	pDC->Ellipse(x - 10, y - 10, x + 8, y + 8);//画一个矩形内接圆

	char str[5];
	_itoa(ht[parent].weight, str, 10);//将整形转换为字符串 int--->char*
	pDC->TextOut(x - 4, y - 8, str);//显示权值到指定位置
	/*d不为0情况*/
	if (d != 0)
	{
		ix = x - 8 * cos(hd2)*d;
		iy = y - 8 * sin(hd2);
		pDC->MoveTo(ix, iy);
		ix = x - 36 * cos(hd2)*d;
		iy = y - 36 * sin(hd2);
		pDC->LineTo(ix, iy);
	}
	/*右递归调用*/
	if (ht[parent].rchild != -1)
		paint(pDC, ht[parent].rchild, x + ix0, y + iy0, c + 1, 1);
}
/*画图调用函数*/
void paint(CDC *pDC)
{
	paint(pDC, 2 * n - 2, 175, 10, 0, 0);
}


/*将输入的哈夫曼树编码为哈夫曼编码格式*/
void Haffman(int w[], int n, HaffNode ht[], HaffCode hc[], char a[])
{
	int i, j, m1, m2, x1, x2;//M1,M2表示最小和次小,x1 x2表示左右孩子


	/*初始化树 添加树权值信息*/
	for (i = 0;i<2 * n - 1;i++)
	{
		if (i<n)//输入树的权值
			ht[i].weight = w[i];
		else//无效节点处理
		ht[i].weight = 0;
		ht[i].parent = 0;
		ht[i].lchild = -1;
		ht[i].rchild = -1;
	}


	/*初始化树 添加树字符信息*/
	for (i = 0;i<n;i++)
		hc[i].data = a[i];


	/*利用输入的元素建立哈夫曼树*/

	/*求出最小权值位置*/
	for (i = 0;i<n - 1;i++)
	{
		m1 = m2 = 1000;//m1 m2取无限大值 保存权值
		x1 = x2 = 0;//保存位置


		/*求出节点中最小节点和次小节点 分别将其权值存入m1和m2 位置存入x1和x2*/
		for (j = 0;j<n + i;j++)
		{
			if (ht[j].weight<m1&&ht[j].parent == 0)
			{
				m2 = m1;
				x2 = x1;
				m1 = ht[j].weight;
				x1 = j;
			}
			else
				if (ht[j].weight<m2&&ht[j].parent == 0)
				{
					m2 = ht[j].weight;
					x2 = j;
				}
		}

		/*将x1和x2作为新节点的左右子节点,新节点的权值为左右子节点之和*/
		ht[x1].parent = n + i;
		ht[x2].parent = n + i;
		ht[n + i].weight = ht[x1].weight + ht[x2].weight;
		ht[n + i].lchild = x1;
		ht[n + i].rchild = x2;

	}



	/*哈夫曼树生成哈夫曼编码*/

	HaffCode cd;
	cd.bit = new int[n];
	int child, parent;
	/*对所有节点进行编码*/
	for (i = 0;i<n;i++)
	{
		/*初始化哈夫曼编码结构体数据*/
		cd.start = n - 1;
		cd.weight = ht[i].weight;
		child = i;
		parent = ht[child].parent;


		/*将所有的叶子节点左节点设置成0,右节点设置成1*/
		while (parent != 0)
		{
			if (ht[parent].lchild == child)
				cd.bit[cd.start] = 0;
			else
				cd.bit[cd.start] = 1;
			cd.start--;
			child = parent;
			parent = ht[child].parent;
		}


		hc[i].bit = new int[n];
		/*保存编码信息*/
		for (j = cd.start + 1;j<n;j++)
			hc[i].bit[j] = cd.bit[j];
		//迭代
		hc[i].start = cd.start;
		hc[i].weight = cd.weight;
	}
}


/*BUTTON1: 保存字符集个数*/
void C哈夫曼编译码系统Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	/*准备工作*/
	delete[]w;
	delete[]ht;
	delete[]hc;
	UpdateData(TRUE);

	/*n为输入字符大小,根据字符大小为其他变量分配空间*/
	n = m_num;
	w= new int[n];
	ht = new HaffNode[2 * n - 1];
	hc = new HaffCode[n];

	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // 在最后一行添加新的内容

	str.Format(_T("请输入字符与对应权值,并点击输入完成\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // 在最后一行添加新的内容

	GetDlgItem(IDC_BUTTON1)->EnableWindow(false);//使保存字符大小按钮失效
	GetDlgItem(IDC_BUTTON2)->EnableWindow(true);//打开保存字符和权值按钮
}


/*BUTTON2: 保存字符及其对应权值*/
void C哈夫曼编译码系统Dlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here

	/*a保存输入的字符*/
	UpdateData(TRUE);
	int m = 0;
	m = strlen(m_element);
	a = new char[m + 1];
	strcpy(a, m_element);

	/*w保存字符对应的权值*/
	/*先将输入的权值存放在q中,权值的长度为m*/
	UpdateData(TRUE);
	m = strlen(m_weight);
	char *q = new char[m + 1];
	strcpy(q, m_weight);

	/*按照空格将权值分开存入w中*/
	q[m] = ' ';
	q[m + 1] = ' ';

	for (int i = 0, j = 0;i<m;i++, j++)
	{
		int s = 0;
		while (q[i] != ' ')
		{
			s = 10 * s + q[i] - '0';
			i++;
		}
		w[j] = s;
	}

	Haffman(w, n, ht, hc, a);//将输入的树编码

	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // 在最后一行添加新的内容

	str.Format(_T("输入完成,请点击新建树开始启动系统\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // 在最后一行添加新的内容

	GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
	/*将新建树按钮显示为可以用*/
	GetDlgItem(IDC_BUTTON4)->EnableWindow(true);
}


/*BUTTON4: 新建树*/
void C哈夫曼编译码系统Dlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	/*设置其他按钮为可用*/
	GetDlgItem(IDC_BUTTON5)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON7)->EnableWindow(true);

	flag = 1;

	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // 在最后一行添加新的内容

	str.Format(_T("正在创建哈夫曼树... ...\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // 在最后一行添加新的内容

	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // 在最后一行添加新的内容

	str.Format(_T("创建成功!请保存文件\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // 在最后一行添加新的内容

	/*创建初始化值*/
	int m, i, s1, s2, start;
	int c, f;
	HuffmanTree p;
	char *cd;

	/*条件判断*/
	if (n <= 1)
		return;

	m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1)*sizeof(HTNode)); // 定义hfm树,malloc() 函数用来动态地分配内存空间

	/*初始化树各值*/
	for (p = HT + 1, i = 1;i <= n;++i, ++p, ++w)
	{
		p->weight = *w;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}
	for (;i <= m;++i, ++p)
		p->parent = 0;

	/*建赫夫曼树*/
	for (i = n + 1;i <= m;++i)
	{
		select(HT, i - 1, s1, s2);//选择出最小值最小序号为s1
		HT[s1].parent = HT[s2].parent = i;//s1s2定义一个共同的父节点
		HT[i].lchild = s1;//i左节点设置为s1
		HT[i].rchild = s2;//i右节点设置为s2
		HT[i].weight = HT[s1].weight + HT[s2].weight;//设置新权值
	}

	HC = (HuffmanCode)malloc((n + 1)*sizeof(char*));//定义hfm编码
	cd = (char*)malloc(n*sizeof(char));
	cd[n - 1] = '\0';

	/*求赫夫曼编码*/
	for (i = 1;i <= n;i++)
	{
		start = n - 1;
		for (c = i, f = HT[i].parent;f != 0;c = f, f = HT[f].parent)
			// 从叶子到根逆向求编码
			if (HT[f].lchild == c)
				cd[--start] = '0';//左支为0
			else
				cd[--start] = '1';//右支为1
		HC[i] = (char*)malloc((n - start)*sizeof(char));

		strcpy(HC[i], &cd[start]);//将赫夫曼编码存入HC中
	}

	free(cd);//释放定义的空间cd

	TCHAR szFilter1[] = _T("txt files(*.txt)|*.txt|all files(*.*)|*.*||");
	// 构造保存文件对话框   
	CFileDialog fileDlg1(FALSE, _T("txt"), _T("hfmTree"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter1, this);
	CString strFilePath1;

	// 显示保存文件对话框   
	if (IDOK == fileDlg1.DoModal())
	{
		// 如果点击了文件对话框上的“保存”按钮则将选择的文件路径显示到编辑框里   
		strFilePath1 = fileDlg1.GetPathName();
	}

	/*保存hfmTree.txt*/
	ofstream fop(strFilePath1);
	fop << "data code" << endl;

	for (int i = 0;i<n;i++)
	{
		fop << a[i] << "    ";
		for (int j = hc[i].start + 1;j<n;j++)
			fop << hc[i].bit[j];
		fop << endl;
		flush(cout);
	}

	ifstream fip(strFilePath1);
	fip.close();


	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // 在最后一行添加新的内容

	str.Format(_T("打印树\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // 在最后一行添加新的内容


	UpdateData(TRUE);
	CWnd *pWnd = GetDlgItem(IDC_PRINTTREE);//获得控件句柄
	CDC *pDC = pWnd->GetDC();//CDC实例化一个对象的指针,pWnd被赋值为GetDC
	CBrush NewBrush(RGB(0, 255, 0));//创建绿色画刷
	CBrush*pOldBrush = pDC->SelectObject(&NewBrush);//pDC指向画刷对象
	paint(pDC);//画二叉树
	UpdateData(FALSE);


	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // 在最后一行添加新的内容

	str.Format(_T("打印结束!\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // 在最后一行添加新的内容
}


/*BUTTON5:编码*/
void C哈夫曼编译码系统Dlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // 在最后一行添加新的内容

	str.Format(_T("请选择所要编码文件!\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // 在最后一行添加新的内容

	TCHAR szFilter2[] = _T("txt files(*.txt)|*.txt|all files(*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg2(TRUE, _T("txt"), _T("tobetran"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter2, this);
	CString strFilePath2;

	// 显示打开文件对话框   
	if (IDOK == fileDlg2.DoModal())
	{
		// 如果点击了文件对话框上的“确定”按钮则将选择的文件路径显示到编辑框里   
		strFilePath2 = fileDlg2.GetPathName();
	}

	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // 在最后一行添加新的内容

	str.Format(_T("请选择编码文件编码保存位置!\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // 在最后一行添加新的内容
	TCHAR szFilter3[] = _T("txt files(*.txt)|*.txt|all files(*.*)|*.*||");
	// 构造保存文件对话框   
	CFileDialog fileDlg3(FALSE, _T("txt"), _T("CodeFile"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter3, this);
	CString strFilePath3;

	// 显示保存文件对话框   
	if (IDOK == fileDlg3.DoModal())
	{
		// 如果点击了文件对话框上的“保存”按钮则将选择的文件路径显示到编辑框里   
		strFilePath3 = fileDlg3.GetPathName();
	}

	/*打开文件*/
	FILE *tobetran, *codefile;
	tobetran = fopen(strFilePath2, "rb");
	codefile = fopen(strFilePath3, "wb");

	char *tran;//存放tobetran里的字符
	i = 99;//标识位
	tran = (char*)malloc(100 * sizeof(char)); //为tran分配100个字节

	while (i == 99)
	{
		if (fgets(tran, 100, tobetran) == NULL)//tobetran文件为空,退出
		{
			break;
		}
		
		//二重循环,逐行逐个编码
		for (i = 0;*(tran + i) != '\0';i++)
		{
			for (j = 0;j <= n;j++)
			{
				if (*(a + j - 1) == *(tran + i))//找到要编码的字符与建立的赫夫曼树编码相对应的字符进行编码
				{
					fputs(HC[j], codefile);//保存字符的编码
					if (j>n)//无法找到相对应字符,退出
					{
						break;
					}
				}
			}
		}
	}

	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // 在最后一行添加新的内容

	str.Format(_T("编码工作完成!\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // 在最后一行添加新的内容

	fclose(tobetran);//关闭文件
	fclose(codefile);
	free(tran);
}


/*BUTTON6:译码*/
void C哈夫曼编译码系统Dlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // 在最后一行添加新的内容

	str.Format(_T("请选择译码文件\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // 在最后一行添加新的内容
	TCHAR szFilter2[] = _T("txt files(*.txt)|*.txt|all files(*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg2(TRUE, _T("txt"), _T("CodeFile"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter2, this);
	CString strFilePath2;

	// 显示打开文件对话框   
	if (IDOK == fileDlg2.DoModal())
	{
		// 如果点击了文件对话框上的“确定”按钮则将选择的文件路径显示到编辑框里   
		strFilePath2 = fileDlg2.GetPathName();
	}

	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // 在最后一行添加新的内容

	str.Format(_T("请选择译码文件保存位置\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // 在最后一行添加新的内容

	// 构造保存文件对话框   
	TCHAR szFilter3[] = _T("txt files(*.txt)|*.txt|all files(*.*)|*.*||");
	CFileDialog fileDlg3(FALSE, _T("txt"), _T("Textfile"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter3, this);
	CString strFilePath3;

	// 显示保存文件对话框   
	if (IDOK == fileDlg3.DoModal())
	{
		// 如果点击了文件对话框上的“保存”按钮则将选择的文件路径显示到编辑框里   
		strFilePath3 = fileDlg3.GetPathName();
	}

	//打开文件
	FILE *codef, *txtfile;
	txtfile = fopen(strFilePath3, "w");
	codef = fopen(strFilePath2, "r");

	char *tbdc, *outext, i2;
	int io = 0, i, m;
	unsigned long length = 10000;

	tbdc = (char*)malloc(length*sizeof(char)); //分配空间
	fgets(tbdc, length, codef);//从文件结构体指针stream中读取数据,每次读取一行。
	outext = (char*)malloc(length*sizeof(char)); //分配空间
	m = 2 * n - 1;
	//译码过程,从根出发  按字符‘0’或‘1’确定找左孩子或右孩子,直至叶子结点
	for (i = 0;*(tbdc + i) != '\0';i++)  //进入循环开始译码
	{
		i2 = *(tbdc + i);
		if (HT[m].lchild == 0)//找到叶子结点
		{
			*(outext + io) = *(a + m - 1);//将对应字符存入outext
			io++;
			m = 2 * n - 1;
			i--;
		}
		else if (i2 == '0') m = HT[m].lchild;//左支迭代
		else if (i2 == '1') m = HT[m].rchild;//右支迭代
	}

	*(outext + io) = '\0';//结束符
	fputs(outext, txtfile);//保存译码字符

	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // 在最后一行添加新的内容

	str.Format(_T("译码结果:\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // 在最后一行添加新的内容

	/*打印译码结果*/
	str = outext;
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // 在最后一行添加新的内容
	str.Format(_T("\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // 在最后一行添加新的内容
	
	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // 在最后一行添加新的内容

	str.Format(_T("译码完成!\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // 在最后一行添加新的内容
	/*释放空间*/
	free(tbdc);
	free(outext);
	fclose(txtfile);
	fclose(codef);
}


/*BUTTON7:打印编码*/
void C哈夫曼编译码系统Dlg::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // 在最后一行添加新的内容

	str.Format(_T("请选择所要打印编码文件!\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // 在最后一行添加新的内容

	TCHAR szFilter4[] = _T("txt files(*.txt)|*.txt|all files(*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg4(TRUE, _T("txt"), _T("CodeFile"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter4, this);
	CString strFilePath4;

	// 显示打开文件对话框   
	if (IDOK == fileDlg4.DoModal())
	{
		// 如果点击了文件对话框上的“确定”按钮则将选择的文件路径显示到编辑框里   
		strFilePath4 = fileDlg4.GetPathName();
	}

	strTime = getTime();
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(strTime);  // 在最后一行添加新的内容

	str.Format(_T("请选择打印编码文件保存位置\r\n"));
	lastLine = m_record.LineIndex(m_record.GetLineCount());
	m_record.SetSel(lastLine - 1, lastLine - 1, 0);
	m_record.ReplaceSel(str);  // 在最后一行添加新的内容

							   // 构造保存文件对话框   
	TCHAR szFilter5[] = _T("txt files(*.txt)|*.txt|all files(*.*)|*.*||");
	CFileDialog fileDlg5(FALSE, _T("txt"), _T("CodePrin"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter5, this);
	CString strFilePath5;

	// 显示保存文件对话框   
	if (IDOK == fileDlg5.DoModal())
	{
		// 如果点击了文件对话框上的“保存”按钮则将选择的文件路径显示到编辑框里   
		strFilePath5 = fileDlg5.GetPathName();
	}
	//打开文件
	FILE * CodePrin, *CodeFile;
	CodePrin = fopen(strFilePath5, "w");
	CodeFile = fopen(strFilePath4, "r");

	char *work3;
	work3 = (char*)malloc(51 * sizeof(char));//动态分配内存

	/*每行50个打印编码*/
	do
	{
		if (fgets(work3, 51, CodeFile) == NULL)//文件为空退出
		{
			break;
		}
		fputs(work3, CodePrin);//将work3存入codeprint
		/*打印50个代码*/
		str = work3;
		lastLine = m_record.LineIndex(m_record.GetLineCount());
		m_record.SetSel(lastLine - 1, lastLine - 1, 0);
		m_record.ReplaceSel(str);  // 在最后一行添加新的内容

	} while (strlen(work3) == 50);

	/*释放空间*/
	free(work3);
	fclose(CodePrin);
	fclose(CodeFile);
}