#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ZGManager.h"
#include "ZGHelper.h"
#include "ZGConfigHelper.h"

#include <QMessageBox>
#include <QCheckBox>
#include <QComboBox>
//#define APPID 4094740804
//#define TOKEN "0x5c,0x96,0x31,0x45,0xbf,0x41,0xcb,0x86,0xf7,0x17,0x7e,0x97,0xb4,0x13,0x94,0x8a,0x79,0x1c,0x46,0xc5,0x90,0x04,0x4a,0x35,0xa8,0xc8,0x62,0x8b,0xe6,0x2c,0x08,0x67"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bool ret = ZGManagerInstance()->InitSdk();
    if (ret) {
        printf("Init Success\n");
    }
    else {
        printf("Init Failed\n");
    }

    ui->comboBoxRole->clear();
    ui->comboBoxRole->addItem(QString::fromLocal8Bit("主播"),0);
    ui->comboBoxRole->addItem(QString::fromLocal8Bit("观众"),1);


    std::vector<AudioDeviceInfo> vec = ZGConfigHelperInstance()->GetMicDevicesList();
    ui->comboBoxMic->clear();
    for (auto iter : vec) {
        ui->comboBoxMic->addItem(QString::fromLocal8Bit(iter.device_name.c_str()),QString(iter.device_id.c_str()));
    }

    std::vector< AudioDeviceInfo> vec2 = ZGConfigHelperInstance()->GetSpeakerDevicesList();
    for (auto iter : vec2) {
        ui->comboBoxSpeaker->addItem(QString::fromLocal8Bit(iter.device_name.c_str()), QString(iter.device_id.c_str()));
    }

    connect(ui->checkBoxAEC, SIGNAL(stateChanged(int)), this, SLOT(checkedAEC(int)));
    connect(ui->checkBoxANS, SIGNAL(stateChanged(int)), this, SLOT(checkedANS(int)));
    connect(ui->checkBoxAGC,SIGNAL(stateChanged(int)),this,SLOT(checkedAGC(int)));

    connect(this, SIGNAL(signal_add_remotestream(QString)), this, SLOT(add_remotestream(QString)), Qt::ConnectionType::QueuedConnection);
    connect(this, SIGNAL(signal_del_remotestream(QString)),this,SLOT(del_remotestream(QString)),Qt::ConnectionType::QueuedConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void  MainWindow::PrintToView(const char* log_str) {
    if (!log_str) {
        ui->label_2->setText(QString::fromStdString(log_str));
    }
}


void MainWindow::on_pushButtonMic_clicked() {
    if (bMic) {
        
    }
}
void MainWindow::on_pushButtonCamera_clicked() {

}
void MainWindow::on_pushButtonANS_clicked() {

}
void MainWindow::on_pushButtonAEC_clicked() {

}
void MainWindow::on_pushButtonAGC_clicked() {

}

// JoinLive 直播连麦
// VideoComm  视频通话

void MainWindow::on_pushButtonRoom_clicked() {
    std::string roomid = ui->lineEditRoomId->text().toStdString();
    std::string device_uuid_ = ZGHelperInstance()->GetDeviceUUID();

    LIVEROOM::SetUseTestEnv(true);
    LIVEROOM::SetUser(device_uuid_.c_str(), device_uuid_.c_str());
    // 设置推流回调
    LIVEROOM::SetLivePublisherCallback(this);
    // 设置拉流回调
    LIVEROOM::SetLivePlayerCallback(this);
    // 设置房间回调
    LIVEROOM::SetRoomCallback(this);
    // 登录房间
    ZGConfigHelperInstance()->SetPublishResolution(640, 480);
    LIVEROOM::SetPreviewView((void*)ui->widgetCamera->winId());
    LIVEROOM::StartPreview();
    
    if (ui->comboBoxRole->currentData().toInt() == 0) {
        LIVEROOM::LoginRoom(roomid.c_str(), ZEGO::LIVEROOM::Anchor, device_uuid_.c_str());
    }
    else
    {
        LIVEROOM::LoginRoom(roomid.c_str(), ZEGO::LIVEROOM::Audience, device_uuid_.c_str());
    }
    LIVEROOM::SetRoomConfig(false ,true);
    layout = new QHBoxLayout(ui->widgetRemote);
    ui->widgetRemote->setLayout(layout);
    int bpx = ui->lineEditAudiobps->text().toInt();
    LIVEROOM::SetAudioBitrate(bpx);
    AUDIOAUX::MuteAux(true);
}


void MainWindow::on_pushButtonConnMic_clicked() {

}


void MainWindow::currentIndexChangedRole(int index) {
}
void MainWindow::checkedAGC(int state) {
     auto st = ui->checkBoxAGC->checkState();
     if (st == Qt::Checked) {
         LIVEROOM::EnableAGC(true);
     }
     else {
         LIVEROOM::EnableAGC(false);
     }
}
void MainWindow::checkedANS(int state) {
    auto st = ui->checkBoxANS->checkState();
    if (st == Qt::Checked) {
        LIVEROOM::EnableNoiseSuppress(true);
    }
    else {
        LIVEROOM::EnableNoiseSuppress(false);
    }
}
void MainWindow::checkedAEC(int state) {
    auto st = ui->checkBoxAEC->checkState();
    if (st == Qt::Checked) {
        LIVEROOM::EnableAEC(true);
    }
    else {
        LIVEROOM::EnableAEC(false);
    }
}

void MainWindow::on_pushButtonLeave_clicked() {
    LIVEROOM::StopPublishing();
    LIVEROOM::LogoutRoom();
}

void MainWindow::oPrepCallback(const AudioFrame& inFrame, AudioFrame& outFrame) {

    printf("onPreCallback");
}

// IRoom Callback  EnableMic SetAudioBitrate
void MainWindow::OnInitSDK(int nError) {
    printf("OnInitSDK error %d\n",nError);
}

void MainWindow::OnLoginRoom(int errorCode,
    const char* pszRoomID,
    const ZegoStreamInfo* pStreamInfo,
    unsigned int streamCount) {
    if (errorCode == 0) {
        printf("Login RoomId %s Success\n", pszRoomID);

        if (ui->comboBoxRole->currentData().toInt() == 0) {
            string stream_id = ZGHelper::Instance()->GetRandomUUID().c_str();
            AV::ZegoPublishFlag publish_flag = AV::ZEGO_JOIN_PUBLISH;// 连麦方式
            LIVEROOM::StartPublishing("", stream_id.c_str(), publish_flag, "");
        }
    }
    else {
        printf("Login RoomId %s failed \n", pszRoomID);
    }
}

void MainWindow::OnLogoutRoom(int errorCode, const char* pszRoomID) {
    printf("OnLogoutRoom error %d,RoomId %s\n",errorCode,pszRoomID);
}

void MainWindow::OnKickOut(int reason,
    const char* pszRoomID,
    const char* pszCustomReason) {
    printf("reason %d,RoomId %s\n",reason, pszRoomID);
};

void MainWindow::OnDisconnect(int errorCode, const char* pszRoomID) {
    printf("OnDisconnect errorCode %d RoomId %s\n",errorCode,pszRoomID);
};

void MainWindow::OnReconnect(int errorCode, const char* pszRoomID) {
    printf("OnReconnect %d,RoomId %d\n",errorCode,pszRoomID);
};

void MainWindow::OnTempBroken(int errorCode, const char* pszRoomID) {
    printf("OnTempBroken \n");
};

void MainWindow::add_remotestream(QString streamId) {
    QWidget* it2 = remoteStreams.value(streamId);
    std::string str = streamId.toStdString();
    if (it2) {
        LIVEROOM::StartPlayingStream(str.c_str(), (void*)it2->winId());
    }
    else {
        QWidget* it = new QWidget();
        //it->resize( ,ui->widgetRemote->height()-10);
        it->setMinimumWidth(ui->widget->width() / (remoteStreams.size() + 1));
        it->setMinimumHeight(ui->widgetRemote->height() - 10);
        it->setGeometry(remoteStreams.size() * it->width(),10,it->width(),it->height());
        layout->addWidget(it);
        remoteStreams.insert(streamId, it);
        LIVEROOM::StartPlayingStream(str.c_str(), (void*)it->winId());
    }
}
void MainWindow::del_remotestream(QString streamId) {
    QWidget* it = remoteStreams.value(streamId);
    if (it)
        delete it;
    remoteStreams.remove(streamId);
}

void MainWindow::OnStreamUpdated(ZegoStreamUpdateType type,
    ZegoStreamInfo* pStreamInfo,
    unsigned int streamCount,
    const char* pszRoomID) {
    printf("OnStreamUpdated streamCount %d RoomId %s\n",streamCount,pszRoomID);
    if (type == ZegoStreamUpdateType::StreamDeleted) {
        emit signal_del_remotestream(QString(pStreamInfo->szStreamId));
        
    }
    if (type == ZegoStreamUpdateType::StreamAdded) {
        emit signal_add_remotestream(QString(pStreamInfo->szStreamId));
    }
};


void MainWindow::OnStreamExtraInfoUpdated(ZegoStreamInfo* pStreamInfo,
    unsigned int streamCount,
    const char* pszRoomID) {
    printf("OnStreamExtraInfoUpdated\n");
};

void MainWindow::OnCustomCommand(int errorCode,
    int requestSeq,
    const char* pszRoomID) {
    printf("OnCustomCommand\n");
};

void MainWindow::OnRecvCustomCommand(const char* pszUserId,
    const char* pszUserName,
    const char* pszContent,
    const char* pszRoomID) {
    printf("OnRecvCustomCommand\n");
};


// IPublish-Callback
void MainWindow::OnPublishStateUpdate(int stateCode,
    const char* pszStreamID,
    const ZegoPublishingStreamInfo& oStreamInfo) {
   // printf("OnPublishStateUpdate stateCode %d,pszStreamID %s\n",stateCode,pszStreamID);
};

void MainWindow::OnJoinLiveRequest(int seq,
    const char* pszFromUserId,
    const char* pszFromUserName,
    const char* pszRoomID) {
    printf("OnJoinLiveRequest seq %d  pszFromUserId %s,pszFromUserName %s,pszRoomID %s\n",
        seq, pszFromUserId, pszFromUserName, pszRoomID);
};

void MainWindow::OnInviteJoinLiveResponse(int result,
    const char* pszFromUserId,
    const char* pszFromUserName,
    int seq) {
    printf("OnInviteJoinLiveResponse %d,UserId %s,UserName %s\n",
        result, pszFromUserId, pszFromUserName);
};

void MainWindow::OnEndJoinLive(int result,
    int seq,
    const char* pszRoomID) {
    printf("OnEndJoinLive\n");
};

void MainWindow::OnPublishQulityUpdate(const char* pszStreamID,
    int quality,
    double videoFPS,
    double videoKBS) {
   /// printf("OnPublishQulityUpdate\n");
};
void MainWindow::OnPublishQualityUpdate(const char* pszStreamID,
    ZegoPublishQuality publishQuality) {
    printf("OnPublishQualityUpdate\n");
};

void MainWindow::OnCaptureVideoSizeChanged(int nWidth, int nHeight) {
    printf("OnCaptureVideoSizeChanged\n");
};

void MainWindow::OnCaptureVideoSizeChanged(AV::PublishChannelIndex index,
    int nWidth,
    int nHegith) {
    printf("OnCaptureVideoSizeChanged\n");
};

void MainWindow::OnPreviewSnapshot(void* pImage) {
    printf("OnPreviewSnapshot\n");
};

void MainWindow::OnPreviewSnapshot(AV::PublishChannelIndex index, void* pImage) {
    printf("OnPreviewSnapshot\n");
};

void MainWindow::OnRelayCDNStateUpdate(const char* streamID,
    AV::ZegoStreamRelayCDNInfo* statesInfo,
    unsigned int statesInfoCount) {
    printf("OnRelayCDNStateUpdate\n");
};

void MainWindow::OnUpdatePublishTargetState(int errorCode,
    const char* streamID,
    int seq) {
    printf("OnUpdatePublishTargetState\n");
};

void MainWindow::OnCaptureVideoFirstFrame() {
    printf("OnCaptureVideoFirstFrame\n");
};

void MainWindow::OnCaptureVideoFirstFrame(AV::PublishChannelIndex idx) {
    printf("OnCaptureVideoFirstFrame\n");
};

void MainWindow::OnCaptureAudioFirstFrame() {
    printf("OnCaptureAudioFirstFrame\n");
};

void MainWindow::OnPlayStateUpdate(int stateCode, const char* pszStreamID) {
     
}

void MainWindow::OnPlayQualityUpdate(const char* pszStreamID,
    int quality,
    double videoFPS,
    double videoKBS) {

};

void MainWindow::OnPlayQualityUpdate(const char* pszStreamID,
    ZegoPlayQuality playQuality) {
};

void MainWindow::OnJoinLiveResponse(int result,
    const char* pszFromUserId,
    const char* pszFromUserName,
    int seq) {
    printf("OnJoinLiveResponse\n");
};

void MainWindow::OnRecvEndJoinLiveCommand(const char* pszFromUserId,
    const char* pszFromUserName,
    const char* pszRoomID) {
    printf("OnRecvEndJoinLiveCommand\n");
};

void MainWindow::OnInviteJoinLiveRequest(int seq,
    const char* pszFromUserId,
    const char* pszFromUserName,
    const char* pszRoomID) {
    printf("OnInviteJoinLiveRequest\n");
};

void MainWindow::OnVideoSizeChanged(const char* pStreamID,
    int nWidth,
    int nHeight) {
    printf("OnVideoSizeChanged\n");
};

void MainWindow::OnRemoteCameraStatusUpdate(const char* pStreamID,
    int nStatus,
    int nReason) {
    printf("OnRemoteCameraStatusUpdate\n");
};

void MainWindow::OnRemoteMicStatusUpdate(const char* pStreamID,
    int nStatus,
    int nReason) {
    printf("OnRemoteMicStatusUpdate\n");
};

void MainWindow::OnRecvRemoteAudioFirstFrame(const char* pStreamID) {
    printf("OnRecvRemoteAudioFirstFrame\n");
};

void MainWindow::OnRecvRemoteVideoFirstFrame(const char* pStreamID) {
    printf("OnRecvRemoteVideoFirstFrame\n");
};

void MainWindow::OnRenderRemoteVideoFirstFrame(const char* pStreamID) {
    printf("OnRenderRemoteVideoFirstFrame\n");
};

void MainWindow::OnSnapshot(void* pImage, const char* pszStreamID) {
    printf("OnSnapshot\n");
};