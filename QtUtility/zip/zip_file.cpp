// Copyright (c) 2016-2018 Haiketang. All rights reversed.
// zip_file.cpp
//

#include "zip_file.h"
#include <QFileInfo>
#include <QDir>
#include "libqtbase/zip/zip.h"
#include "libqtbase/zip/unzip.h"

namespace onlyhi {

class ZipCompress {
 public:
  virtual bool Compress(const QString& directory_path,
                        const QString& compress_dir,
                        const QString& zip_name,
                        HZIP& hzip) {
    QDir dir(directory_path);
    bool result = false;

    ::ZipAddFolder(hzip, compress_dir.toStdWString().c_str());

    for (auto it : dir.entryInfoList()) {
      if (it.isFile()) {
        QString filename = compress_dir + "/" + it.fileName();
        ::ZipAdd(hzip, filename.toStdWString().c_str(),
                 it.absoluteFilePath().toStdWString().c_str());
        result = true;
      } else {
        if (it.fileName() == "." || it.fileName() == "..")
          continue;
        QString sub_dir = it.baseName();
        result = this->Compress(it.absoluteFilePath(), compress_dir + "/" + sub_dir,
                                zip_name, hzip);
      }
    }
    return result;
  }
};

bool ZipFile::CompressFiles(const std::wstring& zip_filename,
                            const std::wstring& password,
                            std::vector<std::wstring>& file_list,
                            const std::wstring& prefix_path) {
  if (zip_filename.empty())
    return false;

  HZIP hz = ::CreateZip(zip_filename.c_str(), NULL);
  if (nullptr == hz)
    return false;

  for (auto it = file_list.begin(); it != file_list.end(); it++) {
    QFileInfo file_info(QString::fromStdWString(*it));
    ::ZipAdd(hz, (prefix_path + file_info.fileName().toStdWString()).c_str(), it->c_str());
  }

  CloseZip(hz);
  hz = nullptr;
  return true;
}

bool ZipFile::CompressFolders(const std::wstring& zip_filename,
                              const std::wstring& password,
                              std::vector<std::wstring>& folder_list) {
  if (zip_filename.empty())
    return false;

  HZIP hz = ::CreateZip(zip_filename.c_str(), NULL);
  if (NULL == hz)
    return false;

  for (auto it = folder_list.begin(); it != folder_list.end(); it++) {
    ::ZipAddFolder(hz, it->c_str());
  }

  CloseZip(hz);
  hz = NULL;
  return true;
}

bool ZipFile::Compress(const std::wstring& zip_name,
                       const std::vector<std::wstring>& file_name,
                       const std::vector<std::wstring>& file_path) {
  if (zip_name.empty())
    return false;

  HZIP hz = ::CreateZip(zip_name.c_str(), NULL);
  if (NULL == hz)
    return false;

  for (int i = 0; i < file_name.size(); i++)
    ::ZipAdd(hz, file_name[i].c_str(), file_path[i].c_str());

  CloseZip(hz);
  hz = NULL;

  return true;
}

bool ZipFile::Compress(const std::wstring& zip_name,
                       const std::wstring& floder_name,
                       const std::wstring& file_name,
                       const std::wstring& file_path) {
  if (zip_name.empty())
    return false;

  HZIP hz = ::CreateZip(zip_name.c_str(), NULL);
  if (NULL == hz)
    return false;

  //for (int i = 0; i < file_name.size(); i++)
  ZipAddFolder(hz, floder_name.c_str());
  ::ZipAdd(hz, file_name.c_str(), file_path.c_str());

  CloseZip(hz);
  hz = NULL;

  return true;
}

bool ZipFile::Compress(const std::wstring& zip_name,
                       std::vector<std::wstring>& compress_file_list,
                       std::vector<std::wstring>& file_path_list) {
  if (zip_name.empty())
    return false;

  HZIP hz = ::CreateZip(zip_name.c_str(), NULL);
  if (NULL == hz)
    return false;

  for (std::vector<std::wstring>::size_type ix = 0; ix < file_path_list.size(); ix++)
    ::ZipAdd(hz, compress_file_list[ix].c_str(), file_path_list[ix].c_str());

  CloseZip(hz);
  hz = NULL;
  return true;
}

bool ZipFile::Compress(const QString& dir, const QString& zip_name) {
  HZIP hz = ::CreateZip(zip_name.toStdWString().c_str(), nullptr);
  if (NULL == hz)
    return false;

  ZipCompress zip;
  QDir compress_dir(dir);
  bool result = zip.Compress(dir, compress_dir.dirName(), zip_name, hz);

  CloseZip(hz);
  hz = NULL;
  return result;
}

//
// Member: WinZip::Uncompress, public
//
// Synopsis: 解压缩 Zip 文件
//
// Arguments: [lpszZipFileName] -- 需要解压缩的 Zip 文件名路径
//		[lpszDestination] -- 解压缩的目的目录
//

bool ZipFile::Uncompress(const std::wstring& zip_file_name,
                         const std::wstring& destination) {
  if (zip_file_name.empty() || destination.empty())
    return false;

  HZIP hz = OpenZip(zip_file_name.c_str(), 0);
  SetUnzipBaseDir(hz, destination.c_str());

  ZIPENTRY ze;
  GetZipItem(hz, -1, &ze);
  int numitems = ze.index;

  for (int zi = 0; zi < numitems; zi++) {
    GetZipItem(hz, zi, &ze);
    UnzipItem(hz, zi, ze.name);
  }

  CloseZip(hz);
  return true;
}

}	 // namespace onlyhi
