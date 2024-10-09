#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include<qwidget.h>
#include<qlabel.h>
#include<qpushbutton.h>
#include<qslider.h>
#include<qlistwidget.h>
#include<qmediaplayer.h>

class MainWindow :public QWidget
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);
	void resizeEvent(QResizeEvent* rev) override;

public:
	void onPlayListWidgetClicked();
signals:
	void curPlayIdxChanged(int idx);
private:
	void init();
	//顶部
	QWidget* CreateTopWidget();
	//中间
	QLabel* m_central_pixLab{};//左边图片
	QListWidget* m_central_lyric_widget{};//右边歌词
	QWidget* CreateCentralWidget();
	//底部
	QPushButton* m_bottom_prevBtn{};//上一曲
	QPushButton* m_bottom_nextBtn{};//下一曲
	QPushButton* m_bottom_playBtn{};//播放/暂停
	QLabel* m_bottom_curTimeLab{};//当前播放时间
	QLabel* m_bottom_allTimeLab{};//歌曲总时长
	QSlider* m_bottom_progressSlider{};//播放进度条
	QPushButton* m_bottom_volumeBtn{};//音量
	QPushButton* m_bottom_playListBtn{};//播放列表

	QWidget* CreateBottomWidget();

	//歌曲列表
	QListWidget* m_playListWidget{};
	QListWidget* CreateMusicListWidget(QWidget* parent=nullptr);

	//音量调节Slider
	QSlider* m_volumeSlider{};

	//音乐播放器
	QMediaPlayer* m_player{};

	QList<QUrl> m_playList;
	int m_playIdx{ -1 };

	void loadPlayList();
	void setCurPlayIdx(int idx);
};


#endif // !MAINWINDOW_H_
