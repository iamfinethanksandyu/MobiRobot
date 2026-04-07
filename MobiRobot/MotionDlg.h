#pragma once

// CMotionDlg 对话框
class CMotionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMotionDlg)

public:
	CMotionDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMotionDlg();

// 对话框数据
	enum { IDD = IDD_MOTION_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_fRadius;
	float m_fConSpeed;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
