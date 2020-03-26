#ifndef FileDialog_h
#define FileDialog_h
#include <QFileDialog>
#include <QFile>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QWidget>
class FileSaveAS : public QWidget
{
	Q_OBJECT
public:
	explicit FileSaveAS(QWidget* parent=0);
	~FileSaveAS();

	void SetWebUrl(const QVariantList& arguments);
	void StartDownLoad();
	bool RemoveFile(QFile *file);
	bool FileAccessible(QFile *file);
public slots:
	void OnReadyRead();
	void OnFinished();
	void onError(QNetworkReply::NetworkError error);
private:
	QString m_strWebUrl;
	QString m_strFileName;
	QString m_strExtendName;
	QFile* m_pFile;
	QString m_strError;
	QNetworkAccessManager *m_pNetworkManager;
	QNetworkReply* m_pNetworkReply;
};

#endif