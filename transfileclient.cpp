//
// Created by geng on 2024/7/16.
//
// You may need to build the project (run Qt uic code generator) to get "ui_TransFileClient.h" resolved

#include "transfileclient.h"
#include "ui_TransFileClient.h"
#include "QHostAddress"
#include "QFileDialog"

TransFileClient::TransFileClient(QWidget* parent)
	:
	QWidget(parent), ui(new Ui::TransFileClient)
{
	ui->setupUi(this);
	this->setWindowTitle("发送多个文件");

	//初始化相关变量
	m_TotalBytes=0;
	m_BytesHaveWriten=0;
	m_BytesToWrite=0;
	m_FileLength=0;
	m_LocalFile= nullptr;
	payLoadSize=64*1024;
	m_fileIndex=0;
	ui->Address->setText("127.0.0.1");ui->Port->setText("8000");

	ui->SendButton->setEnabled(false);
	ui->ProgressBar->reset();
	qTcpClient = new QTcpSocket(this);
	connect(ui->Address, &QLineEdit::textChanged, this, &TransFileClient::HandleTextChanged);
	connect(ui->ConnectButton,&QPushButton::clicked, this,&TransFileClient::ConnectBtnClicked);
	connect(ui->SendButton, &QPushButton::clicked, this, &TransFileClient::TransferFile);
	connect(ui->OpenButton, &QPushButton::clicked, this, &TransFileClient::OpenBtnClicked);
	connect(qTcpClient, &QTcpSocket::connected, this, &TransFileClient::ChangeStatus);
	connect(qTcpClient,&QTcpSocket::bytesWritten, this,&TransFileClient::UpdateProgressBar);
	//connect(this,&TransFileClient::TransferSuccess, this,&TransFileClient::TransferFile);
}

TransFileClient::~TransFileClient()
{
	delete ui;
}

/**
 * 根据用户输入的文本更改按钮的状态
 * @param text 输入框中的文本
 */
void TransFileClient::HandleTextChanged(const QString& text)
{
	if (!text.isEmpty())
	{
		ui->SendButton->setEnabled(true);
	}
	else
	{
		ui->SendButton->setEnabled(false);
	}

}

void TransFileClient::ConnectBtnClicked()
{
	qTcpClient->connectToHost(QHostAddress(ui->Address->text()), ui->Port->text().toInt());
}

void TransFileClient::ChangeStatus()
{
	ui->StatusLabel->setText(tr("连接至%1成功").arg(ui->Address->text()));
}

void TransFileClient::SendBtnClicked()
{

}

void TransFileClient::TransferFile()
{
	m_LocalFile=new QFile(m_FileNames[m_fileIndex]);
	if (!m_LocalFile->open(QIODevice::ReadOnly))
	{
		qDebug()<<"open file error";
		return;
	}

	m_TotalBytes=m_LocalFile->size();

	QDataStream out(&m_Buffer,QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_6_7);

	QString fileNameWithoutPath=m_FileNames[m_fileIndex].right(m_FileNames[m_fileIndex].size()-m_FileNames[m_fileIndex].lastIndexOf('/')-1);
	out<<qint64(0)<<qint64(0)<<fileNameWithoutPath;
	qDebug()<<fileNameWithoutPath;
	//qDebug()<<m_fileIndex;

	m_TotalBytes+=m_Buffer.size();
	out.device()->seek(0);

	out<<m_TotalBytes<<qint64(m_Buffer.size()- sizeof(qint64)*2);
	m_BytesToWrite=m_TotalBytes-qTcpClient->write(m_Buffer);
	m_Buffer.resize(0);

	//if (m_fileIndex==m_FileLength-1) qTcpClient->close();

}

void TransFileClient::OpenBtnClicked()
{
	m_FileNames = QFileDialog::getOpenFileNames(this);
	if (!m_FileNames.isEmpty())
	{
		m_FileLength = m_FileNames.size();
		ui->StatusLabel->setText("打开所选内容成功");
		//qDebug() << tr("所选文件中最后一个文件名为%1").arg(m_FileNames[m_FileLength - 1]);
		//qDebug()<<m_FileNames[m_FileLength-1].right(m_FileNames[m_FileLength-1].size()-m_FileNames[m_FileLength-1].lastIndexOf('/')-1);
	}
}

/**
 * 执行当前文件继续发送的逻辑，同时更新进度
 * @param numBytes
 */
void TransFileClient::UpdateProgressBar(qint64 numBytes)
{
	m_BytesHaveWriten+=(int)numBytes;
	//Q_UNUSED(numBytes)
	if (m_BytesToWrite>0)
	{
		m_Buffer=m_LocalFile->read(qMin(m_BytesToWrite,payLoadSize));
		m_BytesToWrite-=(int)qTcpClient->write(m_Buffer);
		m_Buffer.resize(0);
	}
	else
	{
		m_LocalFile->close();
	}
	if (m_BytesHaveWriten==m_TotalBytes)
	{
		qTcpClient->flush();
		m_LocalFile->close();
		m_BytesToWrite=0;
		m_BytesHaveWriten=0;
		m_TotalBytes=0;
		delete m_LocalFile;
		m_LocalFile= nullptr;
		disconnect(qTcpClient,&QTcpSocket::bytesWritten, this,&TransFileClient::TransferFile);
		qTcpClient->close();
		if (m_fileIndex<=m_FileLength-1)
		{
			emit TransferSuccess();
			m_fileIndex++;
		}
	}
}



/*
void TransFileClient::TransferFile()
{
	for (int i = 0; i < m_FileLength; i++)
	{
		m_LocalFile=new QFile(m_FileNames[i]);
		if (!m_LocalFile->open(QIODevice::ReadOnly))
		{
			qDebug()<<"open file error";
			return;
		}

		//这里存储所选文件的总大小
		m_TotalBytes=m_LocalFile->size();
		QDataStream out(&m_Buffer,QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_6_7);

		QString fileNameWithoutPath=m_FileNames[i].right(m_FileNames[i].size()-m_FileNames[m_FileLength-1].lastIndexOf('/')-1);

		out<<qint64(0)<<qint64(0)<<fileNameWithoutPath;

		//将文件总大小，文件名大小和文件名称存到总字节中
		m_TotalBytes+=m_Buffer.size();

		out.device()->seek(0);
		/*     * qint64(0)  |  qint64(0)  |  fileNameWithoutPath   |
		 *  |               |             |                        |
		 *  |———————————————————————————————————————————————————————
		    |以上是out中的内容，总共占据了m_Buffer.size()大小，减去前面两个qint64的大小就是 fileNameWithoutPath占据的空间
		     为什么不用fileNameWithoutPath.size()这样的函数获取大小呢？ 因为是字符串，只能获取length，不能获取size
		     这个有点像栈区，接受的时候先接受fileNameWithoutPath* /
		out<<m_TotalBytes<<qint64(m_Buffer.size()- sizeof(qint64)*2);
		m_BytesToWrite=m_TotalBytes-qTcpClient->write(m_Buffer);
		m_Buffer.resize(0);
	}
	//m_LocalFile->close();
	//qTcpClient->close();
}
*/