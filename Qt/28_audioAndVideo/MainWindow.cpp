#include "MainWindow.h"
#include"LyricParse.h"
#include<qboxlayout.h>
#include<qaudiooutput.h>
#include<qdiriterator.h>

MainWindow::MainWindow(QWidget* parent)
	:QWidget(parent)
{
	init();
}

void MainWindow::resizeEvent(QResizeEvent* rev)
{
	m_playListWidget->setFixedWidth(280);
	m_playListWidget->setFixedHeight(height() - 50 - 55);
	m_playListWidget->move(width() - m_playListWidget->width(),56);
}

void MainWindow::onPlayListWidgetClicked()
{
	setCurPlayIdx(m_playListWidget->currentRow());
}

void MainWindow::init()
{
	auto vlayout = new QVBoxLayout(this);

	vlayout->addWidget(CreateTopWidget());
	vlayout->addWidget(CreateCentralWidget());
	vlayout->addWidget(CreateBottomWidget());

	auto audioOut = new QAudioOutput(this);
	m_playListWidget = CreateMusicListWidget(this);
	m_volumeSlider = new QSlider(this);
	m_volumeSlider->move(612, 375);
	m_volumeSlider->setFixedSize(30, 100);
	m_volumeSlider->hide();
	m_volumeSlider->setRange(0, 100);
	m_volumeSlider->setValue(audioOut->volume() * 100);

	m_player = new QMediaPlayer(this);
	
	m_player->setAudioOutput(audioOut);

	loadPlayList();
	for (const QUrl& url : m_playList)
	{
		m_playListWidget->addItem(new QListWidgetItem(url.fileName()));
	}

	connect(m_bottom_playListBtn, &QPushButton::clicked, [=]()
		{
			if (m_playListWidget->isHidden())
			{
				m_playListWidget->setHidden(false);
			}
			else
			{
				m_playListWidget->setHidden(true);
			}
		});
	connect(m_bottom_volumeBtn, &QPushButton::clicked, [=]()
		{
			if (m_volumeSlider->isHidden())
			{
				m_volumeSlider->setHidden(false);
			}
			else
			{
				m_volumeSlider->setHidden(true);
			}
		});
	connect(m_playListWidget, &QListWidget::doubleClicked, this,&MainWindow::onPlayListWidgetClicked);
	connect(m_bottom_prevBtn, &QPushButton::clicked, [=]()
		{
			if (m_playIdx - 1 < 0)
			{
				setCurPlayIdx(m_playList.count() - 1);
			}
			else
			{
				setCurPlayIdx(m_playIdx - 1);
			}
		});
	connect(m_bottom_playBtn, &QPushButton::clicked, [=]()
		{
			if (m_player->isPlaying())
			{
				m_player->pause();
				m_bottom_playBtn->setText("⊙");
			}
			else
			{
				if (m_playIdx == -1)
				{
					setCurPlayIdx(0);
				}
				m_player->play();
				m_bottom_playBtn->setText("||");
			}
		});
	connect(m_bottom_nextBtn, &QPushButton::clicked, [=]()
		{
			if (m_playIdx + 1 >= m_playList.count())
			{
				setCurPlayIdx(0);
			}
			else
			{
				setCurPlayIdx(m_playIdx + 1);
			}
		});
	connect(this, &MainWindow::curPlayIdxChanged, [=](int idx)
		{
			m_playListWidget->setCurrentRow(m_playIdx);
			auto lyric = LyricParse::instance()->getLyric(QFileInfo(m_playList.at(m_playIdx).fileName()).baseName());

			m_central_lyric_widget->clear();
			for (const auto& lp : lyric)
			{
				auto item = new QListWidgetItem(lp.second);
				item->setData(Qt::UserRole,LyricParse::timeStrToInter(lp.first));
				m_central_lyric_widget->addItem(item);
			}
			
		});
	connect(m_player, &QMediaPlayer::durationChanged, [=](quint64 duration)
		{
			m_bottom_progressSlider->setRange(0, duration);
			quint64 second = duration / 1000;
			quint64 minite = second / 60;
			m_bottom_allTimeLab->setText(QString("%1:%2").arg(minite, 2, 10, QChar('0')).arg(second - minite * 60, 2, 10, QChar('0')));
		});
	connect(m_player, &QMediaPlayer::positionChanged, [=](quint64 position)
		{
			quint64 second = position / 1000;
			quint64 minite = second / 60;
			m_bottom_curTimeLab->setText(QString("%1:%2").arg(minite, 2, 10, QChar('0')).arg(second - minite * 60, 2, 10, QChar('0')));
			m_bottom_progressSlider->setValue(position);
		});
	connect(m_bottom_progressSlider, &QSlider::sliderMoved, [=](int pos)
		{
			m_player->setPosition(pos);
		});
	connect(m_player, &QMediaPlayer::mediaStatusChanged, [=](auto status)
		{
			if (status == QMediaPlayer::MediaStatus::EndOfMedia)
			{
				m_player->pause();
				m_bottom_playBtn->setText("⊙");
			}
		});
	connect(m_volumeSlider, &QSlider::valueChanged, [=](int value)
		{
			audioOut->setVolume(value / 100.0f);
		});

}

QWidget* MainWindow::CreateTopWidget()
{
	auto w = new QLabel("音乐播放器");
	w->setContentsMargins(0, 0, 0, 0);
	w->setMargin(0);
	w->setAlignment(Qt::AlignCenter);
	//设置字体
	auto font = w->font();
	font.setPixelSize(18);
	w->setFont(font);
	return w;
}

QWidget* MainWindow::CreateCentralWidget()
{
	auto w = new QWidget();
	m_central_pixLab = new QLabel();
	m_central_lyric_widget = new QListWidget();

	auto hlayout = new QHBoxLayout(w);
	hlayout->addWidget(m_central_pixLab); 
	hlayout->addWidget(m_central_lyric_widget);

	m_central_pixLab->setPixmap(QPixmap(":/Resource/images/record.png"));

	return w;
}

QWidget* MainWindow::CreateBottomWidget()
{
	auto w = new QWidget();
	w->setContentsMargins(0, 0, 0, 0);

	m_bottom_prevBtn = new QPushButton("<");//上一曲
	m_bottom_nextBtn = new QPushButton(">");//下一曲
	m_bottom_playBtn = new QPushButton("⊙");//播放/暂停
	m_bottom_curTimeLab = new QLabel("00:00");//当前播放时间
	m_bottom_allTimeLab = new QLabel("00:00");//歌曲总时长
	m_bottom_progressSlider = new QSlider(Qt::Horizontal);//播放进度条
	m_bottom_volumeBtn = new QPushButton("+");//音量
	m_bottom_playListBtn = new QPushButton("=");//播放列表

	m_bottom_prevBtn->setFixedWidth(50);
	m_bottom_nextBtn->setFixedWidth(50);
	m_bottom_playBtn->setFixedWidth(50);
	m_bottom_volumeBtn->setFixedWidth(50);
	m_bottom_playListBtn->setFixedWidth(50);

	auto hlayout = new QHBoxLayout(w);
	hlayout->addWidget(m_bottom_prevBtn);
	hlayout->addWidget(m_bottom_playBtn);
	hlayout->addWidget(m_bottom_nextBtn);
	hlayout->addWidget(m_bottom_curTimeLab);
	hlayout->addWidget(m_bottom_progressSlider);
	hlayout->addWidget(m_bottom_allTimeLab);
	hlayout->addWidget(m_bottom_volumeBtn);
	hlayout->addWidget(m_bottom_playListBtn);
	hlayout->setContentsMargins(0, 0, 0, 0);

	return w;
}

QListWidget* MainWindow::CreateMusicListWidget(QWidget* parent)
{
	auto lw = new QListWidget(parent);
	
	
	lw->setHidden(true);
	return lw;
}

void MainWindow::loadPlayList()
{
	QDirIterator iter("C:\\Users\\HUAWEI\\Documents\\GitHub\\C_Hub\\Qt\\28_audioAndVideo\\Resource\\music",{"*.mp3","*.ogg","*.mp4","*.wav","*.lrc"});
	while (iter.hasNext())
	{
		auto info = iter.nextFileInfo();
		if (info.suffix() == "lrc")
		{
			LyricParse::instance()->addLyric(info.baseName(), info.absoluteFilePath());
		}
		else
		{
			m_playList.append(QUrl::fromLocalFile(info.absoluteFilePath()));
		}
		
	}
}

void MainWindow::setCurPlayIdx(int idx)
{
	if (m_playList.isEmpty())
	{
		qWarning() << "m_playList is empty";
		return;
	}
	if (idx < 0 || idx >= m_playList.count())
	{
		qWarning() << "idx out of range";
		return;
	}
	if (m_playIdx != idx)
	{
		m_playIdx = idx;
		emit curPlayIdxChanged(m_playIdx);
	}
	m_player->setSource(m_playList.at(m_playIdx));
	m_player->play();
	m_bottom_playBtn->setText("||");
	

	
}
