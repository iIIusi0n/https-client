//
// Created by Godbuntu on 2021-02-15.
//

#ifndef HTTPS_NETWORK_HTTPCLIENT_H_
#define HTTPS_NETWORK_HTTPCLIENT_H_

#ifndef _UNICODE
#define _UNICODE
#endif
#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <wininet.h>

namespace Http {
class Client {
 public:
  explicit Client(const wchar_t *hostname, int port = INTERNET_DEFAULT_HTTP_PORT);
  ~Client();

  void SetMethod(const wchar_t *method);
  void SetPath(const wchar_t *path);
  void SetUserAgent(const wchar_t *user_agent);
  void SetReferer(const wchar_t *referer);
  void SetAccept(LPCWSTR *accept);
  void AddCustomHeader(const wchar_t *name, const wchar_t *value);
  void AddBodyData(const wchar_t *content_type, const char *content,
                   size_t content_length);
  virtual void BuildRequest();
  virtual char *SendRequest(int &data_size);

 private:
  void AddRequestHeader(const wchar_t *header);

  HINTERNET internet_session_;

 protected:
  HINTERNET http_request_ = nullptr;
  HINTERNET internet_connection_;
  wchar_t *method_ = nullptr;
  wchar_t *path_ = nullptr;
  wchar_t *referer_ = nullptr;
  LPCWSTR *accept_ = nullptr;
  char *content_ = nullptr;
  size_t content_length_ = 0;
};

class SslClient : public Client {
 public:
  explicit SslClient(const wchar_t *hostname,
                     int port = INTERNET_DEFAULT_HTTPS_PORT)
      : Client(hostname, port) {}
  void BuildRequest() override;
  char *SendRequest(int &data_size) override;
};
}

#endif //HTTPS_NETWORK_HTTPCLIENT_H_
