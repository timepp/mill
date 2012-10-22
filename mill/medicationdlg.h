#pragma once
#include "resource.h"

#include "medicalrecorddlg.h"
#include "suggestiondlg.h"
#include "peoplemgr.h"

class CMedicationDlg
	: public CDialogImpl<CMedicationDlg>
	, public CDialogResize<CMedicationDlg>
{
public:
	enum {IDD = IDD_MEDICATION};

	BEGIN_MSG_MAP(CMedicationDlg)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_CLOSE(OnClose)
		
		COMMAND_HANDLER(IDC_NAME, EN_CHANGE, OnEnChangeName)
		NOTIFY_HANDLER(IDC_BIRTHDAY, DTN_DATETIMECHANGE, OnDtnDatetimechangeBirthday)
		COMMAND_HANDLER(IDC_AGE, EN_CHANGE, OnEnChangeAge)

		CHAIN_MSG_MAP(CDialogResize<CMedicationDlg>)
		COMMAND_HANDLER(IDOK, BN_CLICKED, OnBnClickedOk)
	END_MSG_MAP()

	BEGIN_DLGRESIZE_MAP(CMedicationDlg)
		DLGRESIZE_CONTROL(IDC_IDNUMBER, DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_ADDRESS, DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_COMMENT, DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDOK, DLSZ_MOVE_X|DLSZ_MOVE_Y)
		DLGRESIZE_CONTROL(IDC_PRINT, DLSZ_MOVE_X|DLSZ_MOVE_Y)
		DLGRESIZE_CONTROL(IDC_STATIC_SPLITTER, DLSZ_SIZE_X|DLSZ_MOVE_Y)
		DLGRESIZE_CONTROL(ID_MEDICAL_RECORD, DLSZ_SIZE_X|DLSZ_SIZE_Y)
		DLGRESIZE_CONTROL(IDC_STATIC_GROUP1, DLSZ_SIZE_X)
	END_DLGRESIZE_MAP()

private:
	CMedicalRecordDlg m_dlg;
	CSuggestionDlg m_peopleSuggestDlg;
	CSuggestionEdit m_nameEdit;

private:
	void LoadPeople(const People* p);
	void SavePeople(People* p);

private:
	LRESULT OnInitDialog(HWND hwnd, LPARAM param);
	void OnClose();
	virtual void OnFinalMessage(HWND hwnd);
public:
	LRESULT OnEnChangeName(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnDtnDatetimechangeBirthday(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
	LRESULT OnEnChangeAge(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedOk(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
