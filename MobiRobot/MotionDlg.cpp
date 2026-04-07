// MotionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MobiRobot.h"
#include "MotionDlg.h"
#include "afxdialogex.h"


// CMotionDlg 对话框

IMPLEMENT_DYNAMIC(CMotionDlg, CDialogEx)

CMotionDlg::CMotionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMotionDlg::IDD, pParent)
	, m_fRadius(0)
	, m_fConSpeed(0)
{

}

CMotionDlg::~CMotionDlg()
{
}

void CMotionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ARC_RADIUS, m_fRadius);
	DDX_Text(pDX, IDC_EDIT_CON_SPEED, m_fConSpeed);
}


BEGIN_MESSAGE_MAP(CMotionDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMotionDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMotionDlg 消息处理程序


BOOL CMotionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化	
	UpdateData(FALSE);//将以上两个后台数据更新到显示界面上	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CMotionDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//从显示界面更新后台数据
	CDialogEx::OnOK();
}
