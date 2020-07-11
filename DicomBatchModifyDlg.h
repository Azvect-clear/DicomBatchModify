
// DicomBatchModifyDlg.h: 头文件
//

#pragma once
#include <dcmtk\config\osconfig.h>
#include <dcmtk\dcmdata\dctk.h>
#include <dcmtk/dcmdata/libi2d/i2dbmps.h>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <afxcontrolbars.h>

#include<vector>
#include <string>

using namespace std;

// CDicomBatchModifyDlg 对话框
class CDicomBatchModifyDlg : public CDialogEx
{
// 构造
public:
	CDicomBatchModifyDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DICOMBATCHMODIFY_DIALOG };
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
	std::vector<std::string> dcmFilePath;
	std::vector<std::string> dcmDirPath;
	std::vector<std::string> dcmNewPath;
	std::vector<std::string> dcmDir;

	DcmFileFormat dfile;
	OFCondition result;

	CListCtrl m_list;
	int index;

	CStatic m_static1;
	CEdit m_patientID;
	CEdit m_patientName;
	CEdit m_patientSex;
	CEdit m_patientAge;
	CEdit m_studyUID;
	CEdit m_studyDate;
	CEdit m_hospitalName;
	CEdit m_studyDesc;

	void getInformation(string path);
	bool saveFile(string path);
	bool clearAll();
	bool setFileCount();

	afx_msg void OnBnClickedButtonFile();
	afx_msg void OnBnClickedButtonFolder();
	afx_msg void OnBnClickedButtonMod();
	afx_msg void OnBnClickedButtonClear();
};
