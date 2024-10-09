#include"MainWindow.h"
#include<QApplication>
#include<QWidget>
#include<qsoundeffect.h>
#include<qmediaplayer.h>
#include<qaudiooutput.h>
#include<qvideowidget.h>

//去掉黑窗口
//#pragma comment(linker,"/subSystem:windows /entry:mainCRTStartup")

class Test : public QObject
{
public:
	Test()
	{
		//soundEffect_play();
		//media_play();
		//media_play_video();

	}
	void soundEffect_play()
	{
		if (!m_sound)
		{
			m_sound = new QSoundEffect(this);
			m_sound->setSource(QUrl::fromLocalFile("C:\\Users\\HUAWEI\\Videos\\Qt\\28 音视频播放\\assets\\sound\\video_call.wav"));

		}
		m_sound->play();
	}

	void media_play()
	{
		if (!m_player)
		{
			m_player = new QMediaPlayer(this);
			//创建音频输出
			auto audioOut = new QAudioOutput(m_player);//指定this也行
			//设置播放器
			m_player->setAudioOutput(audioOut);
			
		}
		//设置媒体源
		m_player->setSource(QUrl::fromLocalFile("C:\\Users\\HUAWEI\\Videos\\Qt\\28 音视频播放\\assets\\sound\\video_call.wav"));
		//播放
		m_player->play();
		m_player->setLoops(10);
	}

	void media_play_video()
	{
		if (!m_player)
		{
			m_player = new QMediaPlayer(this);
			//创建音频输出
			auto audioOut = new QAudioOutput(m_player);//指定this也行
			//设置播放器
			m_player->setAudioOutput(audioOut);
			//创建视频输出
			auto videoOut = new QVideoWidget;
			videoOut->show();
			m_player->setVideoOutput(videoOut);

			
		}
		//设置媒体源
		m_player->setSource(QUrl::fromLocalFile("C:\\Users\\HUAWEI\\Videos\\Qt\\28 音视频播放\\assets\\video\\MMD.mp4"));
		//播放
		m_player->play();
		m_player->setLoops(10);
	}
private:
	QSoundEffect* m_sound{};
	QMediaPlayer* m_player{};
};

int main(int argc, char* argv[]) {

	QApplication a(argc, argv);

	MainWindow w;
	w.show();
	//Test test;

	return a.exec();
}

#include "main.moc"