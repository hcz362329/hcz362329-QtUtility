// Copyright (c) 2016-2018 Haiketang. All rights reversed.
// zip_file.h
//

#ifndef _ZIP_FILE_H_
#define _ZIP_FILE_H_
#pragma once
#include <vector>
#include "libqtbase/libqtbase_global.h"

namespace onlyhi {

// Class: ZipFile
// Purpose: For Zip file compression and decompression
//
class LIBQTBASE_EXPORT ZipFile {
 public:
  virtual bool CompressFiles(const std::wstring& zip_filename,
                             const std::wstring& password,
                             std::vector<std::wstring>& file_list,
                             const std::wstring& prefix_path);

  virtual bool CompressFolders(const std::wstring& zip_filename,
                               const std::wstring& password,
                               std::vector<std::wstring>& folder_list);

  bool Compress(const std::wstring& zip_name,
                const std::vector<std::wstring>& file_name,
                const std::vector<std::wstring>& file_path);

  static bool Compress(const std::wstring& zip_name,
                       const std::wstring& floder_name,
                       const std::wstring& file_name,
                       const std::wstring& file_path);

  bool Compress(const std::wstring& zip_name,
                std::vector<std::wstring>& compress_file_list,
                std::vector<std::wstring>& file_path_list);

  bool Compress(const QString& dir, const QString& zip_name);

  bool Uncompress(const std::wstring& zip_file_name, const std::wstring& destination);
};

}   // namespace onlyhi

#endif	// _ZIP_FILE_H_
