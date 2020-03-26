// Copyright (c) 2016, ENTROPY GAME GLOBAL LIMITED. All rights reserved.
// file: http_tunnel.cpp

#include "http_tunnel.h"
#include "utility.h"
#include <windows.h>
#include <winhttp.h>
#pragma comment(lib, "Winhttp.lib")
#define USE_WINHTTP

#ifdef USE_WINHTTP
HRESULT request(const std::wstring& url,
            const std::string& request_method,
            const std::vector<std::string> request_header,
            const std::string& request_body,
            unsigned int timeout_second,
            std::vector<std::string>& response_header,
            std::string& response,
            int* response_code) {
    DWORD dwSize = 0;
    DWORD dwDownloaded = 0;
    HINTERNET hSession = NULL, hConnect = NULL, hRequest = NULL;
    HRESULT hrResult = S_FALSE;
    do {
        // open session
        hSession = WinHttpOpen(L"Statics",
                    WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                    WINHTTP_NO_PROXY_NAME,
                    WINHTTP_NO_PROXY_BYPASS,
                    0);
        if (!hSession) {
            hrResult = GetLastError();
            break;
        }

        // set timeout
        ::WinHttpSetTimeouts(hSession,
            timeout_second,
            timeout_second,
            timeout_second,
            timeout_second);

        wchar_t szHostName[MAX_PATH] = L"";
        wchar_t szURLPath[MAX_PATH * 5] = L"";
        URL_COMPONENTS urlComp;
        memset(&urlComp, 0, sizeof(urlComp));
        urlComp.dwStructSize = sizeof(urlComp);
        urlComp.lpszHostName = szHostName;
        urlComp.dwHostNameLength = MAX_PATH;
        urlComp.lpszUrlPath = szURLPath;
        urlComp.dwUrlPathLength = MAX_PATH * 5;
        urlComp.dwSchemeLength = 1;  // None zero

        // split url
        if (!::WinHttpCrackUrl(url.c_str(), static_cast<DWORD>(url.size()), 0, &urlComp)) {
            hrResult = GetLastError();
            break;
        }

        DWORD dwOpenRequestFlag =
            (urlComp.nScheme == INTERNET_SCHEME_HTTPS) ? WINHTTP_FLAG_SECURE : 0;

        INTERNET_PORT port = 1080;

        // connect to HTTP server
        hConnect = WinHttpConnect(hSession, szHostName, port, 0);
        if (!hConnect) {
            hrResult = GetLastError();
            break;
        }

        // Create an HTTP request
        hRequest = WinHttpOpenRequest(hConnect,
                    common_cz::cp_encode(request_method).c_str(),
                    urlComp.lpszUrlPath,
                    NULL,
                    WINHTTP_NO_REFERER,
                    WINHTTP_DEFAULT_ACCEPT_TYPES,
                    dwOpenRequestFlag);
        if (!hRequest) {
            hrResult = GetLastError();
            break;
        }
#if 0
		std::vector<std::string>::const_iterator iter = request_header.begin();
		for (; iter != request_header.end(); ++iter) {
			std::wstring header = common_cz::cp_encode(*iter) + L"\r\n";
			if (iter + 1 != request_header.end()) {
				header += L"\r\n";
			}
			hrResult = WinHttpAddRequestHeaders(hRequest,
				header.c_str(),
				(ULONG)-1L,
				WINHTTP_ADDREQ_FLAG_ADD);

			if (!hrResult) {
				hrResult = GetLastError();
				break;
			}
		}
#endif
		

		if (!hrResult) {
			break;
		}

        // If HTTPS, then client is very susceptable to invalid certificates
        // Easiest to accept anything for now
        if (urlComp.nScheme == INTERNET_SCHEME_HTTPS) {
            DWORD options = SECURITY_FLAG_IGNORE_CERT_CN_INVALID |
                            SECURITY_FLAG_IGNORE_CERT_DATE_INVALID |
                            SECURITY_FLAG_IGNORE_UNKNOWN_CA;
            ::WinHttpSetOption(hRequest,
                WINHTTP_OPTION_SECURITY_FLAGS,
                (LPVOID)&options,
                sizeof(DWORD));
        }

        // Send request
        if (!WinHttpSendRequest(hRequest,
                WINHTTP_NO_ADDITIONAL_HEADERS,
                0,
                WINHTTP_NO_REQUEST_DATA,
                0,
                static_cast<DWORD>(request_body.size()),
                0)) {
            hrResult = GetLastError();
            break;
        }

        // post data
		DWORD body_size = static_cast<DWORD>(request_body.size());
        if (!request_body.empty()) {
            DWORD dwWritten = 0;
            if (!::WinHttpWriteData(hRequest,
                    request_body.c_str(),
                    body_size,
                    &dwWritten)) {
                hrResult = GetLastError();
                break;
            }

            if (!WinHttpReceiveResponse(hRequest, NULL)) {
                hrResult = GetLastError();
                break;
            }

            // get responed code
            DWORD dwStatusCode = 0;
            dwSize = sizeof(dwStatusCode);
            ::WinHttpQueryHeaders(hRequest,
                WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
                WINHTTP_HEADER_NAME_BY_INDEX,
                &dwStatusCode,
                &dwSize,
                WINHTTP_NO_HEADER_INDEX);
            *response_code = dwStatusCode;

            // get responed header
            dwSize = 0;
            ::WinHttpQueryHeaders(hRequest,
                WINHTTP_QUERY_RAW_HEADERS_CRLF,
                WINHTTP_HEADER_NAME_BY_INDEX,
                WINHTTP_NO_OUTPUT_BUFFER,
                &dwSize,
                WINHTTP_NO_HEADER_INDEX);
            if (::GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
                WCHAR* header_buff = new WCHAR[dwSize / sizeof(WCHAR)];
                if (::WinHttpQueryHeaders(hRequest,
                        WINHTTP_QUERY_RAW_HEADERS_CRLF,
                        WINHTTP_HEADER_NAME_BY_INDEX,
                        header_buff,
                        &dwSize,
                        WINHTTP_NO_HEADER_INDEX)) {
                    std::string rsp = common_cz::cp_encode(static_cast<WCHAR*>(header_buff));
                    size_t last_pos = 0;
                    do {
                        size_t pos = rsp.find("\r\n", last_pos);
                        if (pos == std::string::npos) {
                            break;
                        }

                        response_header.push_back(rsp.substr(last_pos, pos));
                        last_pos = pos + 2;  // skip \r\n
                    } while (last_pos != std::string::npos);
                }

                delete[] header_buff;
            }
        }

        // get responed data until there is nothing left.
        do {
            // Check for available data.
            dwSize = 0;
            if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
                printf("Error %u in WinHttpQueryDataAvailable.\n", GetLastError());

            // Allocate space for the buffer.
            char* buff = new char[dwSize + 1];
            ZeroMemory(buff, dwSize + 1);
            if (!WinHttpReadData(hRequest, (LPVOID)buff, dwSize, &dwDownloaded))
                break;

            // append buffer.
            response.append(buff);
            delete[] buff;
        } while (dwSize > 0);
        hrResult = GetLastError();
    } while (0, 0);

    // Report any errors.
	if (FAILED(hrResult))
		printf("Error %d has occurred.\n", GetLastError());

    // Close any open handles.
    if (hRequest)
        WinHttpCloseHandle(hRequest);
    if (hConnect)
        WinHttpCloseHandle(hConnect);
    if (hSession)
        WinHttpCloseHandle(hSession);

    return hrResult;
}
#endif

namespace common_cz {
const size_t kHeaderBufferSize = 512;
const char kHeaderEnding[] = "\r\n";

struct ReadStream {
    const std::string* buffer;
    size_t read_bytes;
};

size_t write_callback(char* data, size_t size, size_t nmemb, std::string* writer_data) {
    if (writer_data == NULL)
        return 0;
    int len = static_cast<int>(size * nmemb);
    writer_data->append(data, len);
    return len;
}

size_t read_callback(char* buffer, size_t size, size_t nitems, void* instream) {
    if (instream && buffer) {
        ReadStream* rs = reinterpret_cast<ReadStream*>(instream);
        if (rs) {
            size_t total_bytes = rs->buffer->length();
            if (total_bytes > rs->read_bytes) {
                size_t remain_size = total_bytes - rs->read_bytes;
                size_t copy_size = min(size * nitems, remain_size);
                memcpy(buffer, rs->buffer->data() + rs->read_bytes, copy_size);
                rs->read_bytes += copy_size;
                return copy_size;
            }
        }
    }
    return 0;
}

size_t rsp_header_callback(void* ptr, size_t size, size_t nmemb, void* stream) {
    size_t s = size * nmemb;
    if (s > sizeof(kHeaderEnding) - 1) {
        s -= sizeof(kHeaderEnding) - 1;
        char buffer[kHeaderBufferSize] = {0};
        memcpy(buffer, ptr, min(s, sizeof(buffer) - 1));
        // printf("RSP Header: %s, %u\n", buffer, size * nmemb);
        if (stream) {
            std::vector<std::string>* headers = reinterpret_cast<std::vector<std::string>*>(stream);
            if (headers) {
                headers->push_back(buffer);
            }
        }
    }
    return size * nmemb;
}

struct HttpTunnel::Impl {
    Impl()
        : proto_(SERVICE_PROTOCOL_DEFAULT),
          domain_(""),
          path_(SERVICE_PATH_DEFAULT),
          method_(SERVICE_METHOD_GET),
          port_(SERVICE_PORT_DEFAULT) {}
    ~Impl() {}

    void SetProtocol(const std::string& proto) { proto_ = proto; }

    void SetDomain(const std::string& domain) { domain_ = domain; }

    void SetTunnelPort(const unsigned short port) { port_ = port; }

    void SetPath(const std::string& path) { path_ = path; }

    void SetMethod(const std::string& method) { method_ = method; }

    void SetHeaders(const std::vector<std::string>& headers) {
        headers_.clear();
        headers_.assign(headers.begin(), headers.end());
    }

    void GetUrl(std::string* url) {
        if (url) {
            char buf[512] = {0};
            if (port_ != SERVICE_PORT_DEFAULT) {
#if defined(_MSC_VER)
                _snprintf_s(buf,
                    _countof(buf),
                    _TRUNCATE,
                    "%s://%s:%u%s",
                    proto_.c_str(),
                    domain_.c_str(),
                    port_,
                    path_.c_str());
#else
                snprintf(buf,
                    sizeof(buf),
                    "%s://%s:%u%s",
                    proto_.c_str(),
                    domain_.c_str(),
                    port_,
                    path_.c_str());
#endif
            } else {
#if defined(_MSC_VER)
                _snprintf_s(buf,
                    _countof(buf),
                    _TRUNCATE,
                    "%s://%s%s",
                    proto_.c_str(),
                    domain_.c_str(),
                    path_.c_str());
#else
                snprintf(buf,
                    sizeof(buf),
                    "%s://%s%s",
                    proto_.c_str(),
                    domain_.c_str(),
                    path_.c_str());
#endif
            }
            buf[sizeof(buf) - 1] = '\0';
            *url = buf;
        }
    }

    void GetErrorMessage(std::string* error_message) const {
        if (error_message) {
            *error_message = error_;
        }
    }

    bool Request(const std::string& request_body,
            std::string* response,
            unsigned int timeout_second,
            int* response_code) {
        std::string url;
        GetUrl(&url);
        if (proto_ == SERVICE_PROTOCOL_HTTP) {
            return _RequestHttp(url, request_body, response, timeout_second, response_code);
        } else if (proto_ == SERVICE_PROTOCOL_HTTPS) {
            return _RequestHttp(url, request_body, response, timeout_second, response_code);
        } else {
            return _RequestHttp(url, request_body, response, timeout_second, response_code);
        }
    }

    bool Request(const std::string url,
            const std::string& request_body,
            std::string* response,
            unsigned int timeout_second,
            int* response_code) {
        return _RequestHttp(url, request_body, response, timeout_second, response_code);
    }

    bool _RequestHttp(const std::string& url,
            const std::string& request_body,
            std::string* response,
            unsigned int timeout_second,
            int* response_code) {
#ifdef USE_WINHTTP
        return S_OK == request(common_cz::cp_encode(url),
                           method_,
                           headers_,
                           request_body,
                           timeout_second,
                           rsp_headers_,
                           *response,
                           response_code);

#else
        bool result = false;
        size_t rsp_code = 0;
        CURL* curl = curl_easy_init();
        if (curl) {
            ReadStream rs;
            rs.buffer = &request_body;
            rs.read_bytes = 0;
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            if (headers_.size() > 0) {
                curl_slist* plist = NULL;
                for (std::vector<std::string>::iterator iter = headers_.begin();
                     iter != headers_.end();
                     ++iter) {
                    plist = curl_slist_append(plist, iter->c_str());
                }
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, plist);
            }
            curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, request_body.length());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request_body.data());
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
            curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
            curl_easy_setopt(curl, CURLOPT_READDATA, &rs);
            curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, timeout_second);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout_second);
            curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, rsp_header_callback);
            curl_easy_setopt(curl, CURLOPT_HEADERDATA, &rsp_headers_);

            CURLcode res = curl_easy_perform(curl);
            result = (res == CURLE_OK);
            if (response_code) {
                if (curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &rsp_code) == CURLE_OK) {
                    *response_code = static_cast<int>(rsp_code);
                }
            }
            if (!result) {
                const char* error_text = curl_easy_strerror(res);
                if (error_text)
                    error_ = error_text;
            }
            curl_easy_cleanup(curl);
        }
        return result;
#endif
    }

    //     bool _RequestSsl(const std::string& /*request_body*/,
    //             std::string* /*response*/,
    //             int* /*response_code*/) {
    //         // TODO(ramkingxie): implement later
    //     }

    // 比较key不区分大小写
    bool GetResponseHeader(const std::string& key, std::string* value) {
        bool found = false;
        std::string name;
        std::vector<std::string>::iterator iter = rsp_headers_.begin();
        while (iter != rsp_headers_.end()) {
            std::string header = *iter;
            std::string::size_type pos = header.find_first_of(':');
            if (pos != std::string::npos) {
                name = header.substr(0, pos);
                if (_stricmp(name.c_str(), key.c_str()) == 0) {
                    found = true;
                    if (value) {
                        value->clear();
                        if (header.size() > pos + 1) {
                            std::string v = header.substr(pos + 1, header.size() - pos - 1);
                            if (v[0] == ' ')
                                *value = v.substr(1);
                            else
                                *value = v;
                        }
                    }
                    break;
                }
            }
            ++iter;
        }
        return found;
    }

    std::string proto_;
    std::string domain_;
    unsigned short port_;  // NOLINT
    std::string path_;
    std::string method_;
    std::string error_;
    std::vector<std::string> headers_;
    std::vector<std::string> rsp_headers_;
};

HttpTunnel::HttpTunnel() : impl_(new Impl()) {}

HttpTunnel::~HttpTunnel() {
    if (impl_) {
        delete impl_;
        impl_ = NULL;
    }
}

void HttpTunnel::SetProtocol(const std::string& proto) {
    if (impl_)
        impl_->SetProtocol(proto);
}

void HttpTunnel::SetDomain(const std::string& domain) {
    if (impl_)
        impl_->SetDomain(domain);
}

void HttpTunnel::SetTunnelPort(const unsigned short port) {
    if (impl_)
        return impl_->SetTunnelPort(port);
}

void HttpTunnel::SetPath(const std::string& path) {
    if (impl_)
        impl_->SetPath(path);
}

void HttpTunnel::SetMethod(const std::string& method) {
    if (impl_)
        impl_->SetMethod(method);
}

void HttpTunnel::SetHeaders(const std::vector<std::string>& headers) {
    if (impl_)
        impl_->SetHeaders(headers);
}

bool HttpTunnel::Request(const std::string& request_body,
                    std::string* response,
                    unsigned int timeout_second,
                    int* response_code) {
    if (impl_)
        return impl_->Request(request_body, response, timeout_second, response_code);
    return false;
}

bool HttpTunnel::Request(const std::string& url,
                    const std::string& request_body,
                    std::string* response,
                    unsigned int timeout_second,
                    int* response_code) {
    if (impl_)
        return impl_->Request(url, request_body, response, timeout_second, response_code);
    return false;
}

void HttpTunnel::GetErrorMessage(std::string* error_message) const {
    if (impl_)
        return impl_->GetErrorMessage(error_message);
}

bool HttpTunnel::GetResponseHeader(const std::string& key, std::string* value) {
    if (impl_)
        return impl_->GetResponseHeader(key, value);
    return false;
}
}  // namespace common_cz
