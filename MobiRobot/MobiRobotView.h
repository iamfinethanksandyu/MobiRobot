
// MobiRobotView.h : CMobiRobotView 类的接口
//

#pragma once
#include <vector>
using namespace std;

struct Point2f//浮点坐标结构
{
	float x, y;
};

struct POSE//机器人位姿结构
{
	float x, y, a;//机器人人坐标系原点的绝对坐标和机器人坐标系的姿态（方向角）	
};

struct CAR_TRACK_RECORD//小车轨迹记录结构（只用于记录小车原点的轨迹）
{	
	int iCurType;//运动类型，0原地旋转，1直线运动，2圆弧运动
	BOOL bLeft;//是否左转，仅对运动类型0和2有用
	float fArcCenter;//圆弧运动圆心，对于直线运动和原地旋转无用
	float fArcRadius;//圆弧运动半径
	float fArcAngle[2];//圆弧的起始角度和终止角度，对于直线运动和原地旋转无用
	Point2f fptLine[2];//直线的起点和终点
};

class CMobiRobotView : public CView
{
protected: // 仅从序列化创建
	CMobiRobotView();
	DECLARE_DYNCREATE(CMobiRobotView)

// 特性
public:
	CMobiRobotDoc* GetDocument() const;
	//机器人结构参数
	float m_L;//左右轮距之半
	float m_r;//车轮半径
	Point2f m_car0[3][5], m_car[3][5];//小车坐标系下的和绝对坐标系下的小车车体、左右轮的三个折线点数组
	//输入的机器人运动要求
	float m_fArcRadius;//要求的圆弧运动半径，若为0则是原地旋转，若>9999则为直线运动
	float m_fConSpeed;//要求的共模速度，对于直线和圆弧运动均有效，原地旋转此项为0
	//计算出的机器人运动要求
	Point2f m_fptArcCenter;//圆弧运动圆心
	float m_fDifSpeed;//计算得到的差模速度，对于直线运动为0，对于原地旋转则只有差模速度而无共摸速度	
	//机器人运动状态
	POSE m_pose;//机器人坐标系当前位姿
	//机器人运动历史
	//vector<CAR_TRACK_RECORD> m_track;//小车原点的轨迹记录向量（向量即可以动态增长或减小的数组）
	vector<Point2f> m_track;
	
// 操作
public:
	//相对坐标转绝对坐标
	//输入参数：pose—相对坐标系位姿，ptRel—要转换的相对坐标
	//返回值：转换结果的绝对坐标
	Point2f RelToAbs(POSE& pose, Point2f ptRel);

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMobiRobotView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnInitialUpdate();
	afx_msg void OnSetMotion();
};

#ifndef _DEBUG  // MobiRobotView.cpp 中的调试版本
inline CMobiRobotDoc* CMobiRobotView::GetDocument() const
   { return reinterpret_cast<CMobiRobotDoc*>(m_pDocument); }
#endif

