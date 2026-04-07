// GeoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MobiRobot.h"
#include "GeoDlg.h"
#include "afxdialogex.h"


// CGeoDlg 对话框

IMPLEMENT_DYNAMIC(CGeoDlg, CDialogEx)

CGeoDlg::CGeoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGeoDlg::IDD, pParent)
	, m_iXlen(0)
	, m_iYlen(0)
	, m_iWheelRadius(0)
	, m_iWheelWidth(0)
	, m_iWheelDistTail(0)
{

}

CGeoDlg::~CGeoDlg()
{
}

void CGeoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_XLEN, m_iXlen);
	DDX_Text(pDX, IDC_YLEN, m_iYlen);
	DDX_Text(pDX, IDC_EDIT_WHEEL_RADIUS, m_iWheelRadius);
	DDX_Text(pDX, IDC_EDIT_WHEEL_WIDTH, m_iWheelWidth);
	DDX_Text(pDX, IDC_EDIT_WHEEL_DIST_TAIL, m_iWheelDistTail);
}


BEGIN_MESSAGE_MAP(CGeoDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGeoDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CGeoDlg 消息处理程序


BOOL CGeoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//初始化小车结构参数
	m_iXlen = 100;
	m_iYlen = 50;
	m_iWheelRadius = 20;
	m_iWheelWidth = 10;
	m_iWheelDistTail = 25;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CGeoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
