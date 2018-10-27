#pragma once


// CDlgCameraSet 对话框

class CDlgCameraSet : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCameraSet)

public:
	CDlgCameraSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCameraSet();


	BOOL	m_bMirrorX;
	BOOL	m_bMirrorY;
	double	m_dX;
	double	m_dY;
	double	m_dH;
	double	m_dW;
	int m_nExpo;
	CSliderCtrl m_sliderExpo;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CAMERASET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult);

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
