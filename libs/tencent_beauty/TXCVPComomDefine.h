#pragma once
/*
* ��ͷ�ļ����ڶ��� sdk ���õ�һЩ�ṹ�� 
*/
#include <string.h>

#ifdef TXCVPCOMBINE
#define DLLIMEXPORT __declspec(dllexport)
#else
#define DLLIMEXPORT
#endif // TXCVPCOMBINE

#define VIDEOPROCESS_NO_OUTPUT		-1
#define VIDEOPROCESS_FORMAT_TEXTURE2D  0
#define VIDEOPROCESS_FORMAT_I420  1
#define VIDEOPROCESS_FORMAT_NV12  2
#define VIDEOPROCESS_FORMAT_NV21  3
#define VIDEOPROCESS_FORMAT_RGB   4
#define VIDEOPROCESS_FORMAT_YUY2  5
#define VIDEOPROCESS_FORMAT_RGBA  6
#define VIDEOPROCESS_FORMAT_BGR	  7
#define VIDEOPROCESS_FORMAT_XRGB  8
#define VIDEOPROCESS_FORMAT_BGRA  9

typedef struct CropRect
{
	CropRect() {
		xOffset = -1;
		yOffset = -1;
		cropWidth = -1;
		cropHeight = -1;

		originWidth = -1;
		originHeight = -1;
	}
	int xOffset;
	int yOffset;
	int cropWidth;
	int cropHeight;

	int originWidth;
	int originHeight;
}CropRect;

typedef struct TXCCombineFrame {
	TXCCombineFrame() {
		texture = -1;
		data = nullptr;
		format = VIDEOPROCESS_FORMAT_I420;
		width = 0;
		height = 0;
		rotation = 0;
		memset(&crop, 0, sizeof(crop));
		memset(&posision, 0, sizeof(posision));
	}
	int texture;
	unsigned char* data;
	int format;
	int width;
	int height;
	int rotation;
	CropRect crop;
	CropRect posision;
}TXCCombineFrame;

class DLLIMEXPORT CTXIVideoPreprocessorListener
{
public:
	/**
	* �ⲿ�˾�����ص�
	* @param texture   ���������ID
	* @param width     �����������
	* @param height    ���������߶�
	*/
	virtual int willAddWatermark(int texture, int width, int height) {
		return 0;
	}
	/**
	* ������һ֡ͼ��
	* @param texture   �����������ID
	* @param width     ������������
	* @param height    ����������߶�
	* @param timestamp ������ʱ���������ʱ�䣩
	*/
	virtual void didProcessFrame(int texture, int width, int height, unsigned long long timestamp) {

	}

	/**
	* ������һ֡ͼ��
	* @param data      ������֡����
	* @param width     ������֡���ݿ��
	* @param height    ������֡���ݸ߶�
	* @param format    ������֡���ݸ�ʽ����TXEFrameFormat�ж���
	* @param timestamp ������ʱ���������ʱ�䣩
	*/
	virtual void didProcessFrame(unsigned char* data, int width, int height, int format, unsigned long long timestamp) {

	};
};

class CTXINotifyListener {
public:
	/**
	* SurfaceTexture����
	* @param event �¼�id
	* @param param �¼�����
	*/
	virtual void onNotifyEvent(int event, void* param) {
	
	}
};

// ���Ŵ����¼�
typedef enum tagPlayEventType
{
	EVENT_ERROR_PLAY = 0,			// ����ʧ�ܣ�1���ļ�������  2����Ƶ��������
	EVENT_MEDIA_STOP = 1,          // ���ֶ�����ֹͣ�¼�; 1,�ļ�������  2����Ƶ����
	EVENT_ERROR_STREAM_FORMAT = 2,		// ��֧������ʽ		1����֧������Ƶ��ʽ����
	EVENT_ERROR_AUDIO_DEVICE = 3,		// ��Ƶ�豸��ʧ��	1����Ҫ������Ƶ��ʱ��������ʧ��
	EVENT_ERROR_MEDIE_INFO = 4,	// ��ȡ��Ƶ��Ϣ����			1����֧����Ƶ��ʽ

	// SDK �ڲ�����
	EVENT_ERROR_OPENGL_INIT = 100,	// Opengl ��ʼ��ʧ��
}EventPlayType;

typedef enum TxeFillModeTag
{
	TXE_FILL_MODE_SCALE_TO_FILL = 0,	// �����ѹ����䣬ȫ��ʾ�����Կ�����Ƶ�������棩
	TXE_FILL_MODE_SCALL_ASPECT_FILL = 1,	// ����Ƶ�̱�������Ӧ���
}TxeFillModeTag;

typedef struct TXCGreenScreenParam {
	TXCGreenScreenParam() {
		bAudioTrack = false;		// Ĭ�Ϻ�����Ƶ��
		iAudioVolume = 100;			// �������Ƶ�죬Ĭ������Ϊ 80
		renderMode = TXE_FILL_MODE_SCALE_TO_FILL;	// Ĭ��ȫ��ʾ����Ļ�������ܻ���Σ�
	}
	bool bAudioTrack;	// 1�������Ƶˮӡ 2��Ĭ��Ϊfalse����������Ƶ�죻3������Ƶ�ļ�ˮӡ����ǰ��Ч
	int  iAudioVolume;	// ˮӡ��Ƶ������С��0~100��

	TxeFillModeTag renderMode;		// ˮӡ��Ƶ���ģʽ
}TXCGreenScreenParam;