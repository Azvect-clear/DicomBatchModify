
// DicomBatchModifyDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "DicomBatchModify.h"
#include "DicomBatchModifyDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CDicomBatchModifyDlg 对话框



CDicomBatchModifyDlg::CDicomBatchModifyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DICOMBATCHMODIFY_DIALOG, pParent)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CDicomBatchModifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_STATIC1, m_static1);
	DDX_Control(pDX, IDC_EDIT_PatientID, m_patientID);
	DDX_Control(pDX, IDC_EDIT_NAME, m_patientName);
	DDX_Control(pDX, IDC_EDIT_SEX, m_patientSex);
	DDX_Control(pDX, IDC_EDIT_AGE, m_patientAge);
	DDX_Control(pDX, IDC_EDIT_StudyID, m_studyUID);
	DDX_Control(pDX, IDC_EDIT_DATE, m_studyDate);
	DDX_Control(pDX, IDC_EDIT_HOSIPTAL, m_hospitalName);
	DDX_Control(pDX, IDC_EDIT_DESP, m_studyDesc);
}

BEGIN_MESSAGE_MAP(CDicomBatchModifyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FILE, &CDicomBatchModifyDlg::OnBnClickedButtonFile)
	ON_BN_CLICKED(IDC_BUTTON_FOLDER, &CDicomBatchModifyDlg::OnBnClickedButtonFolder)
	ON_BN_CLICKED(IDC_BUTTON_MOD, &CDicomBatchModifyDlg::OnBnClickedButtonMod)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CDicomBatchModifyDlg::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// CDicomBatchModifyDlg 消息处理程序

BOOL CDicomBatchModifyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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
	// 列表行索引
	index = 0;
	// 列表控件初始化
	m_list.ModifyStyle(NULL, LVS_REPORT, 0);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	while (m_list.DeleteColumn(0));
	m_list.InsertColumn(0, _T(" 文 件 路 径"), LVCFMT_LEFT, 1000, 0);

	CFont m_Font;
	m_Font.CreatePointFont(300, _T("楷体"), NULL);
	m_static1.SetFont(&m_Font, true);
	//m_static1.SetWindowText("100");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDicomBatchModifyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDicomBatchModifyDlg::OnPaint()
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
HCURSOR CDicomBatchModifyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDicomBatchModifyDlg::getInformation(string path)
{
	OFString value;
	result = dfile.loadFile(path.c_str());
	if (!result.good())
	{
		return;
	}
	DcmDataset *data = dfile.getDataset();

	// 标签字段查找并更新
	// 病人ID
	data->findAndGetOFStringArray(DCM_PatientID, value);
	m_patientID.SetWindowText(value.c_str());
	// 病人姓名
	data->findAndGetOFStringArray(DCM_PatientName, value);
	m_patientName.SetWindowText(value.c_str());
	// 病人性别
	data->findAndGetOFStringArray(DCM_PatientSex, value);
	m_patientSex.SetWindowText(value.c_str());
	// 病人年龄
	data->findAndGetOFStringArray(DCM_PatientAge, value);
	m_patientAge.SetWindowText(value.c_str());
	// 检查UID
	data->findAndGetOFStringArray(DCM_StudyInstanceUID, value);
	m_studyUID.SetWindowText(value.c_str());
	// 检查日期
	data->findAndGetOFStringArray(DCM_StudyDate, value);
	m_studyDate.SetWindowText(value.c_str());
	// 医院名称
	data->findAndGetOFStringArray(DCM_InstitutionName, value);
	m_hospitalName.SetWindowText(value.c_str());
	// 检查描述
	data->findAndGetOFStringArray(DCM_StudyDescription, value);
	m_studyDesc.SetWindowText(value.c_str());

}


// 选择文件
void CDicomBatchModifyDlg::OnBnClickedButtonFile()
{
	if (dcmFilePath.size() > 0)
	{
		dcmFilePath.clear();
	}

	CFileDialog fpDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT,
		_T("DICOM文件(*.dcm; *.dic) | *.dcm; *.dic || "), NULL); //
	DWORD MAXFILE = 40000;//初始化空间大小，若超过初始化空间，程序fd.DoModal()会自己返回IDCANCEL值  
	fpDlg.m_ofn.nMaxFile = MAXFILE;
	TCHAR * pc = new TCHAR[MAXFILE];//定义为T类型，可避免转换  
	USES_CONVERSION;
	fpDlg.m_ofn.lpstrFile = pc;
	fpDlg.m_ofn.lpstrFile[0] = NULL;//对文件选择对话框初始化

	std::string strImgPath;
	if (IDOK == fpDlg.DoModal())
	{
		POSITION pos = fpDlg.GetStartPosition();
		while (pos)
		{
			CString imgPath = fpDlg.GetNextPathName(pos);
			strImgPath = (CStringA)imgPath;
			dcmFilePath.emplace_back(strImgPath);
			m_list.InsertItem(index++, strImgPath.c_str());
		}
	}
	getInformation(strImgPath);
	pc = NULL;
	delete[] pc;
	setFileCount();
}


// 选择文件夹
void CDicomBatchModifyDlg::OnBnClickedButtonFolder()
{
	vector<string> directoryPath;
	TCHAR	szFolderPath[MAX_PATH] = { 0 };
	CString	strFolderPath = TEXT("");

	BROWSEINFO sInfo;
	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
	sInfo.pidlRoot = 0;
	sInfo.lpszTitle = _T("请选择目录");
	sInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_DONTGOBELOWDOMAIN;
	sInfo.lpfn = NULL;

	// 显示文件夹选择对话框  
	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);
	if (lpidlBrowse != NULL)
	{
		// 取得文件夹名  
		if (::SHGetPathFromIDList(lpidlBrowse, szFolderPath))
		{
			strFolderPath = szFolderPath;
		}
	}
	if (strFolderPath == "")
		return;
	if (lpidlBrowse != NULL)
	{
		::CoTaskMemFree(lpidlBrowse);
	}
	CString strWildcard(strFolderPath);
	strWildcard += _T("\\*.*");
	CFileFind finder;
	BOOL bWorking = finder.FindFile(strWildcard);
	int i;
	CString fontName, lastType, filepath, filename, filesize;//存储切割结果
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		filename = finder.GetFileName();
		//假设文件夹里面全是图片，获取图片文件长度
		if (filename != _T(".") && filename != _T(".."))
		{
			filepath = finder.GetFilePath();
			dcmFilePath.emplace_back(filepath);
			m_list.InsertItem(index++, filepath);
		}
	}
	string lastFilePath = filepath;
	getInformation(lastFilePath);
	finder.Close();
	setFileCount();
}

// 保存文件
bool CDicomBatchModifyDlg::saveFile(string path)
{
	int pointIndex = path.rfind(".");
	string prefix = path.substr(0, pointIndex) + "M";
	string suffix = ".dcm";
	string newPath = prefix + suffix;
	OFCondition status = dfile.saveFile(newPath.c_str(), EXS_Unknown, EET_ExplicitLength, EGL_recalcGL, EPD_noChange, 0, 0, EWM_dontUpdateMeta);
	CFile::Remove(path.c_str());
	CFile::Rename(newPath.c_str(), path.c_str());
	if (!status.good())
	{
		MessageBox(TEXT("修改失败！ 请重试！"), TEXT("错误"), MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}


// 重置
bool CDicomBatchModifyDlg::clearAll()
{
	dcmFilePath.clear();
	m_list.DeleteAllItems();
	m_patientID.SetWindowText("");
	m_patientName.SetWindowText("");
	m_patientSex.SetWindowText("");
	m_patientAge.SetWindowText("");
	m_studyUID.SetWindowText("");
	m_studyDate.SetWindowText("");
	m_hospitalName.SetWindowText("");
	m_studyDesc.SetWindowText("");
	index = 0;
	setFileCount();
	return true;
}

// 批量修改
void CDicomBatchModifyDlg::OnBnClickedButtonMod()
{
	if (dcmFilePath.size() == 0)
	{
		MessageBox(TEXT("请选择文件重试！"), TEXT("提示"), MB_OK | MB_ICONWARNING);
		return;
	}

	CString newPatientID;
	CString newPatientName;
	CString newPatientSex;
	CString newPatientAge;
	CString newStudyUID;
	CString newStudyDate;
	CString newHosiptalName;
	CString newStudyDesc;
	m_patientID.GetWindowText(newPatientID);
	m_patientName.GetWindowText(newPatientName);
	m_patientSex.GetWindowText(newPatientSex);
	m_patientAge.GetWindowText(newPatientAge);
	m_studyUID.GetWindowText(newStudyUID);
	m_studyDate.GetWindowText(newStudyDate);
	m_hospitalName.GetWindowText(newHosiptalName);
	m_studyDesc.GetWindowText(newStudyDesc);
	
	for (int i = 0; i < dcmFilePath.size(); ++i)
	{
		string filePath = dcmFilePath.at(i);
		result = dfile.loadFile(filePath.c_str());
		DcmDataset *data = dfile.getDataset();

		// 病人ID
		delete data->remove(DCM_PatientID);
		data->putAndInsertString(DCM_PatientID, newPatientID);
		
		// 病人姓名
		delete data->remove(DCM_PatientName);
		data->putAndInsertString(DCM_PatientName, newPatientName);
		
		// 病人性别
		delete data->remove(DCM_PatientSex);
		data->putAndInsertString(DCM_PatientSex, newPatientSex);

		// 病人年龄
		delete data->remove(DCM_PatientAge);
		data->putAndInsertString(DCM_PatientAge, newPatientAge);

		// 检查UID
		delete data->remove(DCM_StudyInstanceUID);
		data->putAndInsertString(DCM_StudyInstanceUID, newStudyUID);

		// 检查日期
		delete data->remove(DCM_StudyDate);
		data->putAndInsertString(DCM_StudyDate, newStudyDate);
		delete data->remove(DCM_SeriesDate);
		data->putAndInsertString(DCM_SeriesDate, newStudyDate);
		delete data->remove(DCM_AcquisitionDate);
		data->putAndInsertString(DCM_AcquisitionDate, newStudyDate);
		delete data->remove(DCM_ContentDate);
		data->putAndInsertString(DCM_ContentDate, newStudyDate);

		// 医院名称
		delete data->remove(DCM_InstitutionName);
		data->putAndInsertString(DCM_InstitutionName, newHosiptalName);

		// 检查描述
		delete data->remove(DCM_StudyDescription);
		data->putAndInsertString(DCM_StudyDescription, newStudyDesc);

		saveFile(filePath);
	}

	clearAll();

	AfxMessageBox(_T("修改成功！"));
}

// 清空
void CDicomBatchModifyDlg::OnBnClickedButtonClear()
{
	clearAll();
}

bool CDicomBatchModifyDlg::setFileCount()
{
	CString fileCount;
	fileCount.Format(_T("%d"), index);
	GetDlgItem(IDC_STATIC_FILECNT)->SetWindowText(fileCount);
	return true;
}