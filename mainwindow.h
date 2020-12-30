#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ZGLog.h>
#include <QWidget>
#include <QHBoxLayout>
#include <QMap>
#include "ZegoLiveRoom/LiveRoom-Publisher.h"
#include "ZegoLiveRoom/LiveRoom.h"
#include "ZegoLiveRoom/LiveRoomCallback-Publisher.h"
#include "ZegoLiveRoom/LiveRoomCallBack.h"
#include "ZegoLiveRoom/audio_in_output.h"
#include "ZegoLiveRoom/LiveRoomCallback.h"
#include "ZegoLiveRoom/LiveRoomCallback-Player.h"
#include "ZegoLiveRoom/zego-api-audio-device.h"
#include "ZegoLiveRoom/zego-api-audio-aux.h"
using namespace ZEGO;
using namespace ZEGO::LIVEROOM;
using namespace AVE;
using namespace AUDIOAUX;

class IPushlishRoomCallback : public LIVEROOM::ILivePublisherCallback,
                              public LIVEROOM::IRoomCallback,
                              public AV::IZegoDeviceStateCallback {

public:

};


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow,
                   public ILogToView,
                   public IRoomCallback,
                   public ILivePublisherCallback,
                   public ILivePlayerCallback
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void PrintToView(const char* log_str);
signals:
    void signal_add_remotestream(QString streamId);
    void signal_del_remotestream(QString streamId);
    void signal_enterroom(QString streamId);
public slots:
    void add_remotestream(QString streamId);
    void del_remotestream(QString streamId);
    void on_pushButtonMic_clicked();
    void on_pushButtonCamera_clicked();
    void on_pushButtonRoom_clicked();
    void on_pushButtonConnMic_clicked();
    void on_pushButtonLeave_clicked();
    void on_pushButtonPull_clicked();
    void currentIndexChangedRole(int index);
    void checkedAGC(int);
    void checkedANS(int);
    void checkedAEC(int);
   
    void checkedMicDump(int);
    void checkedSpeakerDump(int);
    void StartPushlishToServer(QString);
public:
    void EnterRoom();
    void LeaveRoom();
public:

    static void PrepCallback(const AudioFrame& inFrame,AudioFrame& outFrame);
    static void PostpCallback(const char* streamId, const AudioFrame& inFrame, AudioFrame& outFrame);

    // IRoom Callback
    void OnInitSDK(int nError)override;
    void OnLoginRoom(int errorCode, 
        const char* pszRoomID,
        const ZegoStreamInfo* pStreamInfo, 
        unsigned int streamCount) override;
    void OnLogoutRoom(int errorCode, const char* pszRoomID) override;
    void OnKickOut(int reason, const char* pszRoomID, const char* pszCustomReason = "") override;
    void OnDisconnect(int errorCode, const char* pszRoomID) override;
    void OnReconnect(int errorCode, const char* pszRoomID) override;
    void OnTempBroken(int errorCode, const char* pszRoomID) override;
    void OnStreamUpdated(ZegoStreamUpdateType type, 
        ZegoStreamInfo* pStreamInfo,
        unsigned int streamCount, 
        const char* pszRoomID) override;
    void OnStreamExtraInfoUpdated(ZegoStreamInfo* pStreamInfo,
        unsigned int streamCount,
        const char* pszRoomID)override;
    void OnCustomCommand(int errorCode,
        int requestSeq, 
        const char* pszRoomID)override;
    void OnRecvCustomCommand(const char* pszUserId, 
        const char* pszUserName,
        const char* pszContent, 
        const char* pszRoomID) override;



    // IPublish-Callback
    void OnPublishStateUpdate(int stateCode, 
        const char* pszStreamID, 
        const ZegoPublishingStreamInfo& oStreamInfo) override;
    void OnJoinLiveRequest(int seq, 
        const char* pszFromUserId,
        const char* pszFromUserName,
        const char* pszRoomID)override;
    void OnInviteJoinLiveResponse(int result,
        const char* pszFromUserId,
        const char* pszFromUserName,
        int seq) override;
    void OnEndJoinLive(int result,
        int seq, 
        const char* pszRoomID) override;
    void OnPublishQulityUpdate(const char* pszStreamID,
        int quality,
        double videoFPS,
        double videoKBS) override;
    void OnPublishQualityUpdate(const char* pszStreamID, 
        ZegoPublishQuality publishQuality) override;

    void OnCaptureVideoSizeChanged(int nWidth, int nHeight) override;

    void OnCaptureVideoSizeChanged(AV::PublishChannelIndex index, int nWidth, int nHegith)override;
    void OnPreviewSnapshot(void* pImage) override;
    void OnPreviewSnapshot(AV::PublishChannelIndex index, void* pImage) override;
    void OnRelayCDNStateUpdate(const char* streamID, 
        AV::ZegoStreamRelayCDNInfo* statesInfo, 
        unsigned int statesInfoCount) override;
    void OnUpdatePublishTargetState(int errorCode,
        const char* streamID,
        int seq) override;
    void OnCaptureVideoFirstFrame() override;
    void OnCaptureVideoFirstFrame(AV::PublishChannelIndex idx) override;
    void OnCaptureAudioFirstFrame() override;


    // ILivePlayerCallback
    void OnPlayStateUpdate(int stateCode, const char* pszStreamID) override;
    void OnPlayQualityUpdate(const char* pszStreamID,
        int quality, 
        double videoFPS, 
        double videoKBS) override;
    void OnPlayQualityUpdate(const char* pszStreamID, 
        ZegoPlayQuality playQuality) override;
    void OnJoinLiveResponse(int result, 
        const char* pszFromUserId,
        const char* pszFromUserName, 
        int seq) override;
    void OnRecvEndJoinLiveCommand(const char* pszFromUserId,
        const char* pszFromUserName,
        const char* pszRoomID)override;
    void OnInviteJoinLiveRequest(int seq, 
        const char* pszFromUserId, 
        const char* pszFromUserName, 
        const char* pszRoomID)override;
    void OnVideoSizeChanged(const char* pStreamID,
        int nWidth, 
        int nHeight) override;
    void OnRemoteCameraStatusUpdate(const char* pStreamID, 
        int nStatus, 
        int nReason) override;

    void OnRemoteMicStatusUpdate(const char* pStreamID, 
        int nStatus, 
        int nReason) override;
    void OnRecvRemoteAudioFirstFrame(const char* pStreamID) override;
    void OnRecvRemoteVideoFirstFrame(const char* pStreamID) override;
    void OnRenderRemoteVideoFirstFrame(const char* pStreamID) override;
    void OnSnapshot(void* pImage, const char* pszStreamID) override;
private:
    Ui::MainWindow *ui;
    bool bMic = true;
    bool bCamera = true;
    bool bANS = false;
    bool bAEC = false;
    bool bAGC = false;
    bool bEnterRoom = false;
    QString bps = 64000;
    QString roomId;
    QHBoxLayout* layout = nullptr;
    QMap<QString, QWidget*> remoteStreams;
    QString exePath;
    FILE* fileMic = nullptr;
    FILE* fileSpeaker = nullptr;
    QString curRemoteStreamId;
    bool bFirstInit = true;
};

#endif // MAINWINDOW_H
