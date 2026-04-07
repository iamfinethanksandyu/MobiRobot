#pragma once


// CGeoDlg 对话框

class CGeoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGeoDlg)

public:
	CGeoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGeoDlg();

// 对话框数据
	enum { IDD = IDD_GEO_PARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_iXlen;
	int m_iYlen;
	int m_iWheelRadius;
	int m_iWheelWidth;
	int m_iWheelDistTail;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
