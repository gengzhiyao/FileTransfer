//
// Created by geng on 2024/7/16.
//

#ifndef TRANSFILECLIENT_H
#define TRANSFILECLIENT_H

#include <QWidget>
#include "QTcpSocket"
#include "QFile"

#define PORT 8000

QT_BEGIN_NAMESPACE
namespace Ui
{
class TransFileClient;
}
QT_END_NAMESPACE

class TransFileClient: public QWidget
{
    Q_OBJECT

public:
    explicit TransFileClient(QWidget *parent = nullptr);
    ~TransFileClient() override;

public slots:
    void HandleTextChanged(const QString& text);

    void ConnectBtnClicked();

	void OpenBtnClicked();

	void SendBtnClicked();

	void ChangeStatus();

    void TransferFile();

	void UpdateProgressBar(qint64 numBytes);

signals:
	void TransferSuccess();
private:
    Ui::TransFileClient *ui;
    QTcpSocket *qTcpClient;
    int m_FileLength;
    QStringList m_FileNames;
    qint64 m_TotalBytes;
	qint64  m_BytesToWrite;
    qint64 m_BytesHaveWriten;
    QByteArray m_Buffer;
	QFile *m_LocalFile;

	qint64  payLoadSize;

	int m_fileIndex;
};


#endif //TRANSFILECLIENT_H
