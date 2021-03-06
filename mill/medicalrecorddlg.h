#pragma once

#include "resource.h"

class CMedicalRecordDlg 
	: public CDialogImpl<CMedicalRecordDlg>
	, public CDialogResize<CMedicalRecordDlg>
{
public:
	enum {IDD = IDD_MEDICAL_RECORD};

	BEGIN_MSG_MAP(CMedicalRecordDlg)
		MSG_WM_INITDIALOG(OnInitDialog)
		CHAIN_MSG_MAP(CDialogResize<CMedicalRecordDlg>)
	END_MSG_MAP()

	BEGIN_DLGRESIZE_MAP(CMedicalRecordDlg)
		DLGRESIZE_CONTROL(IDC_PRESCRIPTION, DLSZ_SIZE_Y)
		DLGRESIZE_CONTROL(IDC_DIAGNOSE, DLSZ_SIZE_X|DLSZ_SIZE_Y)
		DLGRESIZE_CONTROL(IDC_DESCRIPTION, DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_PSNOTE, DLSZ_SIZE_X | DLSZ_MOVE_Y)
		DLGRESIZE_CONTROL(IDC_STATIC_PSNOTE, DLSZ_MOVE_Y)
	END_DLGRESIZE_MAP()

private:
	LRESULT OnInitDialog(HWND hwnd, LPARAM param);
};
