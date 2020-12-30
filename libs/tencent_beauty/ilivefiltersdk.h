// ilivefiltersdk.h

#pragma once

#ifdef TXCVPCOMBINE
#define DLLIMEXPORT __declspec(dllexport)
#else
#define DLLIMEXPORT
#endif // TXCVPCOMBINE

class CGLDrawThread;

#ifndef VIDEOPROCESS_NO_OUTPUT
#define VIDEOPROCESS_NO_OUTPUT		-1
#endif
#ifndef VIDEOPROCESS_FORMAT_TEXTURE2D
#define VIDEOPROCESS_FORMAT_TEXTURE2D  0
#endif
#ifndef VIDEOPROCESS_FORMAT_I420
#define VIDEOPROCESS_FORMAT_I420  1
#endif
#ifndef VIDEOPROCESS_FORMAT_NV12
#define VIDEOPROCESS_FORMAT_NV12  2
#endif
#ifndef VIDEOPROCESS_FORMAT_NV21
#define VIDEOPROCESS_FORMAT_NV21  3
#endif
#ifndef VIDEOPROCESS_FORMAT_RGB
#define VIDEOPROCESS_FORMAT_RGB   4
#endif
#ifndef VIDEOPROCESS_FORMAT_YUY2
#define VIDEOPROCESS_FORMAT_YUY2  5
#endif
#ifndef VIDEOPROCESS_FORMAT_RGBA
#define VIDEOPROCESS_FORMAT_RGBA  6
#endif
#ifndef VIDEOPROCESS_FORMAT_BGR
#define VIDEOPROCESS_FORMAT_BGR	  7
#endif
#ifndef VIDEOPROCESS_FORMAT_XRGB
#define VIDEOPROCESS_FORMAT_XRGB  8
#endif
#ifndef VIDEOPROCESS_FORMAT_BGRA
#define VIDEOPROCESS_FORMAT_BGRA  9
#endif
class CTXCVPLock;
class CTXINotifyListener;
class CTXMVideoPreprocessor;
struct TXCGreenScreenParam;

class DLLIMEXPORT TILFilter{
public:
	/**
	* ���캯��; Ĭ��Ϊ��GL������ֻ֧��ԭʼ���ݴ���
	*/
	TILFilter();
	/**
	* ���캯��
	* @param bGLContext��false: ��GL ������ֻ֧��ԭʼ���ݴ���   true: ��GL������sdk֧���������봦��
	*/
	TILFilter(bool bGLContext);
	~TILFilter();
public:
	/**
	* ������ͬʱҲ֧�ֶ�ʵ����
	*/
	static TILFilter* getInstance();
	
public:
	/**
	* �����˾����ͣ���δʵ�֣�
	*/
	int setFilter(int filter);

	/**
	* Ԥ��������
	* @param data������/��� ����
	* @param len�����ݳ���
	* @param width�����ݿ��
	* @param height�����ݸ߶�
	* @param type�������ʽ(I420����Ϊ��VIDEOPROCESS_FORMAT_I420)
	*/
	int processData(unsigned char* data, int len, int width, int height, int type);

	/**
	* Ԥ��������
	* @param textureId����������/��� ����
	* @param len�����ݳ���
	* @param width�����ݿ��
	* @param height�����ݸ߶�
	* @param type�������ʽ��VIDEOPROCESS_FORMAT_TEXTURE2D��
	* @return: ����ֵΪ sdk���������� id
	*/
	int processData(int textureId, int len, int width, int height, int type);

	/**
	* �¼�֪ͨ�ص�
	* @param   notify���ص���ָ��
	*/
	void setNotify(CTXINotifyListener* notify);

	/**
	* �������ճ̶�
	* @param blur�� ���ճ̶ȣ�0~9����������Ϊ5
	*/
	void setBeauty(int blur);

	/**
	* �������׳̶�
	* @param white�� ���׳̶ȣ�0~9����������Ϊ3
	*/
	void setWhite(int white);
	/**
	* ����������
	* @param sharpness�� ���ճ̶ȣ�0~9����������Ϊ2
	*/
	void setSharpness(int sharpness);
	/**
	* ���շ��
	* @param style�� 0���⻬  1����Ȼ  2������
	*/
	void setBeautyStyle(int style);
	/**
	* ����ˮӡ
	* @param filePath ˮӡ�ļ�·����֧�� BMP, GIF, JPEG, PNG, TIFF, Exif, WMF, and EMF ��ʽ������� NULL�������ȥ��ˮӡ
	* @param xOffset  ���Ͻ�x��ƫ��
	* @param yOffset  ���Ͻ�y��ƫ��
	* @param fWidthRatio ˮӡռ x�� �ı���
	*/
	void setWaterMark(const char* filePath, float xOffset, float yOffset, float fWidthRatio);
	
	/**
	* ������Ļ����
	* @param filePath ��Ļ�����ļ�·��(""����ȡ����Ļ)��֧�� BMP, GIF, JPEG, PNG, TIFF, Exif, WMF, and EMF ��ʽ/mp4��ʽ
	* @param pathLen  ·���ĳ���
	* @param isLoop  �Ƿ�ѭ��������Ƶ�ļ�������ʱ��֧����Ƶ��ʽ��Ԥ����
	*/
	void setGreenScreenFile(const char* filePath, int pathLen, bool isLoop);

	/**
	* ������Ļ�����������������Ҫ�ı���Ļ�����ԣ����Բ����ã�
	* @param   param.bAudioTrack : �Ƿ������Ƶ�죨true�� ����   false�������أ�
	*		   param.iAudioVolume : ������Ļ��Ƶ������ǰ���Ǽ�������Ƶ�죬����Ч�� ��Χ��0~100��0�������� 100���������
	*		   param.renderMode :	��Ļ��Ƶ���ģʽ ��TXE_FILL_MODE_SCALE_TO_FILL��չʾ������Ƶ�������Ǳ���  TXE_FILL_MODE_SCALL_ASPECT_FILL������Ӧ���������Ļ��
	*/	
	void setGreenScreenParam(TXCGreenScreenParam* param);

	/**
	* ��ȡ sdk �Ƿ�֧��Ԥ������֧�� Opengl 2.0 �����Կ���
	*/
	bool getSDKSupport();
	/**
	* ����sdk��Դ
	*/
	void destroyFilter();

private:
	int m_width;
	int m_height;
	int m_beautyLevel;
	int m_whiteLevel;
	int m_shapnessLevel;
	int m_BeautyStyle;

	// ˮӡ���
	std::string m_WaterMarkPath;
	float m_xOffset;
	float m_yOffset;
	float m_fWidthRatio;

	// ��Ļ���
	std::string m_GreenScreenPath;
	bool m_bGreenLoop;

	CTXCVPLock* m_lockFilter;
	CGLDrawThread* m_glDrawThread;
	TXCGreenScreenParam* m_TxcGreenParam;
	CTXINotifyListener* mNotifyListen;
	// dua �ϱ����Ʊ���
	bool m_bReportDua;
	bool m_bSetBautyDua;
	bool m_bSetWhiteDua;
	bool m_bSetSharpDua;

	bool m_bSetGreenScreenDua;

	bool m_bFirstFrame;
	int m_iRealFps;
	long m_startTime;

	bool m_bSDKSupport;

	bool m_bIfGLContext;

	CTXMVideoPreprocessor* mTxcVideoProcessor;
};