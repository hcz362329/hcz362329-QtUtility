#include "FileDialog.h"
#include <QDebug>
#include<QMessageBox>
FileSaveAS::FileSaveAS(QWidget* parent)
	:QWidget(parent)
	, m_pFile(nullptr)
{
	//setWindowTitle(QString::fromWCharArray(L"保存下载文件"));
	//setFileMode(QFileDialog::DirectoryOnly);
	//connect(this,&QFileDialog::fileSelected,[=](const QString &file_name){

	//	qDebug()<<"file_name:"<<file_name;
	//	m_strExtendName = file_name + "/"+ m_strFileName;
	//	qDebug()<<"strExtendName:"<<m_strExtendName;
	//	StartDownLoad();
	//});
	////QListView{background-color:white;}QListView::item {background: white;}QListView::item:alternate {background: gray;}QListView::item:hover {background: gray;}
	//setStyleSheet("QListView {background-color:rgb(255,255,255);border:solid 0px rgba(0,0,0,0);}\
	//			  QListView::item {background: rgba(0,0,0,0);}\
	//			  QListView::item:alternate {background: rgba(0,0,0,50%);}\
	//			  QListView::item:hover {background: rgb(229,243,255);}\
	//			  QLineEdit{background-color:white;}\
	//			  QComboBox{background-color:white;}");
}

FileSaveAS::~FileSaveAS()
{

}

void FileSaveAS::SetWebUrl(const QVariantList& arguments)
{
	if (arguments.size()>1)
	{
		m_strWebUrl = qvariant_cast<QString>(arguments[0]);

		QFileInfo info = QFileInfo(m_strWebUrl);
		QString strSuffix = info.suffix();

		m_strFileName = qvariant_cast<QString>(arguments[1]);
		QString strFilter = m_strFileName+QString(".")+strSuffix;
		QString strExt = QString("Images (*.%1)").arg(strSuffix);
		QString strFile1 = QFileDialog::getSaveFileName(NULL,QString::fromWCharArray(L"选择文件保存的路径"),strFilter,strExt);
		if (!strFile1.isEmpty())
		{
			m_strExtendName = strFile1 ;
			QFileInfo info1 = QFileInfo(m_strExtendName);
			QString strFileName = info1.fileName();
			QString strSuffix2 = info1.suffix();
			if ( !strFileName.isEmpty() && !strSuffix2.isEmpty() )
			{
				m_strFileName = strFileName;
			}
			StartDownLoad();
		}
	}
}

void FileSaveAS::StartDownLoad()
{
	//如果文件存在，关闭文件并移除
	if(QFile::exists(m_strExtendName))
	{
		QFile file(m_strExtendName);
		if (!RemoveFile(&file))
		{
			return ;
		}
	}

	//创建并打开文件
	m_pFile = new QFile(m_strExtendName);
	if (!m_pFile->open(QIODevice::WriteOnly))
	{
		m_strError = QStringLiteral("Error: QFile::open(%1) - %2").arg(m_strExtendName).arg(m_pFile->errorString());
		if (nullptr != m_pFile)
		{
			delete m_pFile;
			m_pFile = nullptr;
		}
		return ;
	}
#if 0


	if (!m_strWebUrl.isEmpty())
	{
		QNetworkRequest request(m_strWebUrl);
		QSslConfiguration config = request.sslConfiguration();
		config.setPeerVerifyMode(QSslSocket::VerifyNone);
		config.setProtocol(QSsl::TlsV1SslV3);
		request.setSslConfiguration(config);
		m_pNetworkManager = new QNetworkAccessManager;
		m_pNetworkReply = m_pNetworkManager->get(request);
		connect(m_pNetworkReply, SIGNAL(readyRead()), this, SLOT(OnReadyRead()));
		connect(m_pNetworkReply, SIGNAL(finished()), this, SLOT(OnFinished()));
		connect(m_pNetworkReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
	}
#endif
}

void FileSaveAS::OnReadyRead()
{
	if (m_pNetworkReply->error() == QNetworkReply::NoError)
	{
		if (FileAccessible(m_pFile) && m_pFile->isOpen() && m_pNetworkReply->isOpen())
		{
			const QByteArray& bytesRev = m_pNetworkReply->readAll();
			if (-1 == m_pFile->write(bytesRev))
			{
				qDebug() << m_pFile->errorString();
			}
		}
	}
}

void FileSaveAS::OnFinished()
{
	int statusCode = m_pNetworkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	bool bSuccess = (m_pNetworkReply->error() == QNetworkReply::NoError && statusCode == 200);

	if (!bSuccess)
	{
		
	}
	
	if (m_pFile && m_pFile->exists() )
	{
		m_pFile->close();
	}
	if (m_pNetworkReply->isOpen())
	{
		const QByteArray& bytes = m_pNetworkReply->readAll();
		if (!bytes.isEmpty())
		{
			m_strError.append(QString::fromUtf8(bytes));
		}
	}
	m_pNetworkReply->deleteLater();
	m_pNetworkManager->deleteLater();
	if (bSuccess)
	{
		QString strContent = QString::fromWCharArray(L"文件下载成功：") + m_strFileName;
		QMessageBox::information(NULL,"Load",strContent);
	}
}

void FileSaveAS::onError(QNetworkReply::NetworkError error)
{

}

bool FileSaveAS::RemoveFile(QFile *pFile)
{
	if (pFile && pFile->exists() )
	{
		pFile->close();
		return pFile->remove();
	}
	return true;
}

bool FileSaveAS::FileAccessible(QFile *file)
{
	if ( file!= nullptr && file->exists())
	{
		return true;
	}
	return false;
}