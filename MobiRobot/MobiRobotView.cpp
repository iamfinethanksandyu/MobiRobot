
// MobiRobotView.cpp : CMobiRobotView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MobiRobot.h"
#endif

#include "MobiRobotDoc.h"
#include "MobiRobotView.h"
#include "GeoDlg.h"
#include "MotionDlg.h"
#define PI 3.1415926
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMobiRobotView

IMPLEMENT_DYNCREATE(CMobiRobotView, CView)

BEGIN_MESSAGE_MAP(CMobiRobotView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMobiRobotView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_SET_MOTION, &CMobiRobotView::OnSetMotion)
END_MESSAGE_MAP()

// CMobiRobotView ����/����

CMobiRobotView::CMobiRobotView()
{
	// TODO: �ڴ˴����ӹ������	
}

CMobiRobotView::~CMobiRobotView()
{
}

BOOL CMobiRobotView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMobiRobotView ��ӡ
void CMobiRobotView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMobiRobotView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMobiRobotView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ���Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMobiRobotView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ���Ӵ�ӡ����е���������
}

void CMobiRobotView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMobiRobotView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMobiRobotView ���

#ifdef _DEBUG
void CMobiRobotView::AssertValid() const
{
	CView::AssertValid();
}

void CMobiRobotView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMobiRobotDoc* CMobiRobotView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMobiRobotDoc)));
	return (CMobiRobotDoc*)m_pDocument;
}
#endif //_DEBUG

// CMobiRobotView ��Ϣ��������
void CMobiRobotView::OnInitialUpdate()//��ͼ���ݺ���ʾ�����ʼ����
{
	CView::OnInitialUpdate();
	//��ʼ��������λ�ˣ�����������ϵ���������ϵ��ʼһ�£�
	m_pose.x = m_pose.y = m_pose.a = 0;
	//ʹ�öԻ����ȡС���ṹ����
	CGeoDlg dlg;
	dlg.DoModal();	
	m_L = (float)(dlg.m_iYlen  + dlg.m_iWheelWidth) / 2;//�ڲ��־�+�ֿ�֮�룬�������ĵ�������ԭ�����
	m_r = (float)dlg.m_iWheelRadius;
	//��С���ṹ������ʼ���������ߣ��������������ϵ�£�
	//�����ĵ�
	m_car0[0][0].x = m_car0[0][3].x = -(float)dlg.m_iWheelDistTail;//��β������
	m_car0[0][1].x = m_car0[0][2].x = (float)dlg.m_iXlen - dlg.m_iWheelDistTail;//��ͷ������
	m_car0[0][0].y = m_car0[0][1].y = -(float)dlg.m_iYlen / 2 ;//����������
	m_car0[0][2].y = m_car0[0][3].y =  (float)dlg.m_iYlen / 2;//����������
	m_car0[0][4] = m_car0[0][0];//���߷������
	//�����ĵ�
	m_car0[1][0].x = m_car0[1][3].x = -m_r;//���ֺ�Ե������
	m_car0[1][1].x = m_car0[1][2].x = m_r;//����ǰԵ������
	m_car0[1][0].y = m_car0[1][1].y = -(float)dlg.m_iYlen / 2 - dlg.m_iWheelWidth;//�������������
	m_car0[1][2].y = m_car0[1][3].y = -(float)dlg.m_iYlen / 2;//�����Ҳ�������
	m_car0[1][4] = m_car0[1][0];//���߷������
	//�����ĵ�
	m_car0[2][0].x = m_car0[2][3].x = -(float)dlg.m_iWheelRadius;//���ֺ�Ե������
	m_car0[2][1].x = m_car0[2][2].x = (float)dlg.m_iWheelRadius;//����ǰԵ������
	m_car0[2][2].y = m_car0[2][3].y = (float)dlg.m_iYlen / 2;//�������������
	m_car0[2][0].y = m_car0[2][1].y = (float)dlg.m_iYlen / 2 + dlg.m_iWheelWidth;//�����Ҳ�������
	m_car0[2][4] = m_car0[2][0];//���߷������
	//��С�����ж���ת��Ϊ��������
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 5; j++)
			m_car[i][j] = RelToAbs(m_pose, m_car0[i][j]);	
	//ʹ��ͼʧЧ�Ӷ�����OnDraw�ػ�С���ĳ�ʼ״̬
	InvalidateRect(NULL, TRUE);
	//�������˶�������ʼ��
	m_fArcRadius = 100;
	m_fConSpeed = 0.1;//����ת��(w1 + w2)/2������һ��ʱ�䵥λת0.1����	
}

void CMobiRobotView::OnDraw(CDC* pDC)// CMobiRobotView ����
{
	CMobiRobotDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//�����������ת������ʾ����
	POINT car[3][5];//С������ʾ���꣬�ֲ�����
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 5; j++)
		{
			car[i][j].x = (long)m_car[i][j].x;
			car[i][j].y = (long)m_car[i][j].y;
		}	
	//ѡ�»���
	CPen pen(PS_SOLID, 2, RGB(255, 0, 255));//ʵ�ߡ��߿�2���ء���ɫ
	CPen* pOldPen = pDC->SelectObject(&pen);
	//����С������������
	for(int i = 0; i < 3; i++)
		pDC->Polyline(car[i], 5);	
	//��ʷ�켣����ת��ͨ����
	POINT* pts = new POINT[m_track.size()];
	for(int i = 0; i < m_track.size(); i++)
	{
		pts[i].x = (long)m_track[i].x;
		pts[i].y = (long)m_track[i].y;
	}
	
	//������ʷ�켣
	pDC->Polyline(pts, m_track.size());
	delete [] pts;
	//ѡ�ؾɻ���
	pDC->SelectObject(pOldPen);

	//显示小车当前位姿信息
	CString strPose;
	strPose.Format(_T("当前位姿：\nX = %.2f\nY = %.2f\n角度 = %.2f°"),
		m_pose.x, m_pose.y, m_pose.a * 180.0f / PI);

	//设置文本背景为透明
	pDC->SetBkMode(TRANSPARENT);
	//设置文本颜色为深蓝色
	pDC->SetTextColor(RGB(0, 0, 128));

	//在窗口右上角显示位姿信息
	CRect rect;
	GetClientRect(&rect);
	CRect textRect(rect.right - 200, 10, rect.right - 10, 100);
	pDC->DrawText(strPose, &textRect, DT_LEFT);

	//显示操作提示
	CString strHelp = _T("操作说明：\n↑ 前进  ↓ 后退\n← 左转  → 右转\nL 左圆弧  R 右圆弧\n菜单：设置运动参数");
	CRect helpRect(10, 10, 200, 150);
	pDC->SetTextColor(RGB(0, 100, 0));
	pDC->DrawText(strHelp, &helpRect, DT_LEFT);
}

void CMobiRobotView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//float da;//��nRepCnt��ʱ�䵥λ�߹���Բ����
	//�����������ϵλ�ˣ�����һ��nRepCnt����һ��ʱ�䵥λ
	POSE prePose = m_pose;//����ǰ�ȼ�¼��һ�ε�λ��
	switch(nChar)
	{
	case VK_UP://�ص�ǰ��������ƽ�ƣ�ǰ����
		m_pose.x += nRepCnt * m_fConSpeed * m_r * cos(m_pose.a);
		m_pose.y += nRepCnt * m_fConSpeed * m_r * sin(m_pose.a);
		break;
	case VK_DOWN://�е�ǰ������ƽ�ƣ����ˣ�
		m_pose.x -= nRepCnt * m_fConSpeed * m_r * cos(m_pose.a);
		m_pose.y -= nRepCnt * m_fConSpeed * m_r * sin(m_pose.a);
		break;
	case VK_LEFT://ԭ���������Ի���������ϵԭ��Ϊ���ģ�
		m_pose.a -= nRepCnt * m_fConSpeed * m_r / m_L;//(float)PI / 180;//������Ļ����ϵY�����£���X�ᵽY�����������������������������������Ľ������ͽ��ٶ�Ϊ��
		break;
	case VK_RIGHT://ԭ���������Ի���������ϵԭ��Ϊ���ģ�
		m_pose.a += nRepCnt * m_fConSpeed * m_r / m_L;//(float)PI / 180;//������Ļ����ϵY�����£���X�ᵽY�����������������������������������Ľ������ͽ��ٶ�Ϊ��
		break;
	case 'L'://��ʱ����Բ��
	case 'l':
		//���ϵ�λ�����Բ��
		m_fptArcCenter.x = m_pose.x + m_fArcRadius * cos(m_pose.a - PI / 2);
		m_fptArcCenter.y = m_pose.y + m_fArcRadius * sin(m_pose.a - PI / 2);
		//���µ�ǰ��̬
		//m_fDifSpeed = 2 * m_L * m_fConSpeed / m_fArcRadius;//�����ģת��w2-w1
		//da = nRepCnt * m_r * m_fDifSpeed / (2 * m_L);//������nRepCnt��ʱ�䵥λ�߹���Բ����
		m_pose.a -= nRepCnt * m_r * m_fConSpeed / m_fArcRadius;//������nRepCnt��ʱ�䵥λ�߹���Բ����
		//��Բ�ķ���ǰλ��
		m_pose.x = m_fptArcCenter.x - m_fArcRadius * cos(m_pose.a - PI / 2);
		m_pose.y = m_fptArcCenter.y - m_fArcRadius * sin(m_pose.a - PI / 2);		
		break;
	case 'R'://˳ʱ����Բ��
	case 'r':
		//���ϵ�λ�����Բ��
		m_fptArcCenter.x = m_pose.x + m_fArcRadius * cos(m_pose.a + PI / 2);
		m_fptArcCenter.y = m_pose.y + m_fArcRadius * sin(m_pose.a + PI / 2);
		//���µ�ǰ��̬
		m_pose.a += nRepCnt * m_r * m_fConSpeed / m_fArcRadius;//������nRepCnt��ʱ�䵥λ�߹���Բ����
		//��Բ�ķ���ǰλ��
		m_pose.x = m_fptArcCenter.x - m_fArcRadius * cos(m_pose.a + PI / 2);
		m_pose.y = m_fptArcCenter.y - m_fArcRadius * sin(m_pose.a + PI / 2);		
		break;
	}
	//�������ֱ�ߣ�ֱ�����˵��������ת��������
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 5; j++)
			m_car[i][j] = RelToAbs(m_pose, m_car0[i][j]);	
	//�����ĵ���ʷ�켣
	Point2f fpt;
	fpt.x = m_pose.x;
	fpt.y = m_pose.y;
	m_track.push_back(fpt);
	//ʹ��ͼʧЧ�Ӷ�����OnDraw�ػ�
	InvalidateRect(NULL, TRUE);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//BOOL Arc( LPCRECT lpRect, POINT ptStart, POINT ptEnd );

//�������ת��������
//���������pose���������ϵλ�ˣ�ptRel��Ҫת�����������
//����ֵ��ת������ľ�������
Point2f CMobiRobotView::RelToAbs(POSE& pose, Point2f ptRel)
{
	Point2f ptAbs;
	ptAbs.x = ptRel.x * cos(pose.a) - ptRel.y * sin(pose.a) + pose.x;
	ptAbs.y = ptRel.x * sin(pose.a) + ptRel.y * cos(pose.a) + pose.y;
	return ptAbs;
}

//ʹ���˶����öԻ������û������˶�����
void CMobiRobotView::OnSetMotion()
{
	// TODO: �ڴ�����������������
	//��ʼ���Ի������
	CMotionDlg dlg;
	dlg.m_fConSpeed = m_fConSpeed;
	dlg.m_fRadius = m_fArcRadius;
	//��ʾ�Ի��򲢸����˶���������ȡ���Ի����򲻸���
	if(dlg.DoModal() == IDOK)//��ʾ�˶����öԻ������޸��˶������������ȷ����ť�رյģ�����±���ͼ����˶�����
	{
		m_fConSpeed = dlg.m_fConSpeed;
		m_fArcRadius = dlg.m_fRadius;
	}
}
