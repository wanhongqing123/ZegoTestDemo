//
// ZGUIOperator.h
//
// Copyright 2018�� Zego. All rights reserved.
// 

#ifndef ZGUIOperator_h__
#define ZGUIOperator_h__

#include <functional>

/************************************************************************

// ��UI�̷߳�װ

// ��Dialog���ʵ���Զ�����ϢUI_CALLBACK_MSG�Ĵ�����

afx_msg LRESULT OnUICallbackMsg(WPARAM wParam, LPARAM lParam)
{
    PostUIData * pdata = (PostUIData *)wParam;
    if (pdata != nullptr && pdata->cb_in_ui_fun)
    {
        pdata->cb_in_ui_fun();
    }
    return 0;
}


// ����Ҫ���̵߳ĵط�
// ����һ����װ�ṹ�壬�ӹ����̵߳�UI�߳�Ͷ������
typedef struct UIDataStruct
{
    // �Զ���Ҫ���ݵ�������
} UIDataStruct;

UIDataStruct ui_data;
// ���̺߳����У���������������ui_data

PostUIData * pdata = CreateUIData();
// ����UI�߳��ϵĻص�����
pdata->cb_in_ui_fun = [ui_data, pdata, this]()->void
{
    // ������д����UI�Ĵ���

    // �ͷ���Դ
    DestroyUIData(pdata);
};

// Ͷ����Ϣ��UI�̣߳���UI�̻߳ص�ִ��lampda���ʽ
// ��Dialog���ͨ��PostMsgDataToUI��Ͷ�ݣ��ڷ�dialog��������õ����ھ��ͨ��GlobalPostMsgDataToUIͶ��

PostMsgDataToUI(pdata);


************************************************************************/

#define UI_CALLBACK_MSG  WM_USER + 888

typedef struct PostUIData
{
    std::function<void()>  cb_in_ui_fun;

}PostUIData;

#define CreateUIData() new PostUIData()

#define DestroyUIData(ptr)\
if(ptr != nullptr)\
{\
    PostUIData *pd = (PostUIData *)ptr;\
    delete ptr;\
}\


#define PostMsgDataToUI(p)\
if (!PostMessage(UI_CALLBACK_MSG, (WPARAM)pdata, 0))\
{\
    DestroyUIData(p);\
}\

#define GlobalPostMsgDataToUI(hwnd, p)\
if (!::PostMessage(hwnd, UI_CALLBACK_MSG, (WPARAM)pdata, 0))\
{\
    DestroyUIData(p);\
}\


#endif // ZGUIOperator_h__


