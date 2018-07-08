// UpdatingForm.h
#ifndef _UPDATINGFORM_H
#define _UPDATINGFORM_H
#include <afxwin.h>
#include "resource.h"
typedef signed long int Long;
class AddressBook;
class UpdatingForm : public CDialog {
public : 
	enum { IDD = IDD_UPDATINGFORM };
public :
	UpdatingForm(CWnd *parent = NULL);
	virtual BOOL OnInitDialog();
public :
	AddressBook *addressBook;
public:
	void Load();
	void Save();
	void Insert(Long Index);
	void Delete(Long index);
	void Update(Long Index);
	CString GetCode();
protected :
	afx_msg void OnRecordButtonClicked();
	afx_msg void OnFindButtonClicked();
	afx_msg void OnCorrectButtonClicked();
	afx_msg void OnEraseButtonClicked();
	afx_msg void OnArrangeButtonClicked();
	afx_msg void OnListViewItemButtonClicked(NMHDR *pNotifyStruct,	LRESULT *result);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};

#endif // _UPDATINGFORM_H
  