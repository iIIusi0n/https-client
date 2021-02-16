//
// Created by Godbuntu on 2021-02-15.
//

#include "httpclient.h"

namespace Http {
Client::Client(const wchar_t *hostname, int port) {
  internet_session_ = InternetOpen(
      nullptr,
      INTERNET_OPEN_TYPE_DIRECT,
      nullptr,
      nullptr,
      0);
  internet_connection_ = InternetConnect(
      internet_session_,
      hostname,
      port,
      L"",
      L"",
      INTERNET_SERVICE_HTTP,
      0,
      0);
}

Client::~Client() {
  InternetCloseHandle(http_request_);
  InternetCloseHandle(internet_connection_);
  InternetCloseHandle(internet_session_);
}

void Client::SetMethod(const wchar_t *method) {
  method_ = new wchar_t[wcslen(method) + 1];
  wcscpy(method_, method);
}

void Client::SetPath(const wchar_t *path) {
  path_ = new wchar_t[wcslen(path) + 1];
  wcscpy(path_, path);
}

void Client::SetUserAgent(const wchar_t *user_agent) {
  user_agent_ = new wchar_t[wcslen(user_agent) + 1];
  wcscpy(user_agent_, user_agent);
}

void Client::SetReferer(const wchar_t *referer) {
  referer_ = new wchar_t[wcslen(referer) + 1];
  wcscpy(referer_, referer);
}

void Client::SetAccept(LPCWSTR *accept) {
  accept_ = accept;
}

void Client::AddRequestHeader(const wchar_t *header) {
  HttpAddRequestHeaders(
      http_request_,
      header,
      -1,
      HTTP_ADDREQ_FLAG_ADD);
}

void Client::AddCustomHeader(const wchar_t *name, const wchar_t *value) {
  auto *header = new wchar_t[wcslen(name) + wcslen(value) + 5];
  wcscpy(header, name);
  wcscat(header, L": ");
  wcscat(header, value);
  wcscat(header, L"\r\n");
  AddRequestHeader(header);
}

void Client::AddBodyData(const wchar_t *content_type, const char *content,
                            size_t content_length) {
  AddCustomHeader(L"Content-Type", content_type);
  content_length_ = content_length;
  content_ = new char[content_length];
  memcpy(content_, content, content_length);
}

char *Client::SendRequest(int &data_size) {
  http_request_ = HttpOpenRequest(
      internet_connection_,
      method_,
      path_,
      L"HTTP/1.1",
      referer_,
      accept_,
      0,
      0);
  HttpSendRequest(http_request_, nullptr, 0, (LPVOID) content_, content_length_);

  int buffer_size = 128;
  data_size = 0;
  char *buffer = new char[buffer_size];
  char *data, *data_backup;
  while (true) {
    int read_size;
    bool read;
    read = InternetReadFile(
        http_request_,
        buffer,
        buffer_size,
        reinterpret_cast<LPDWORD>(&read_size));

    if (read_size == 0) {
      break;
    }
    if (!read) {
      exit(0);
    } else {
      data_backup = new char[data_size];
      memcpy(data_backup, data, data_size);
      data = new char[data_size + read_size];
      memcpy(data, data_backup, data_size);
      memcpy(data + data_size, buffer, read_size);
      data_size += read_size;
    }
  }
  delete[]buffer;
  delete[]data_backup;
  return data;
}

char *SslClient::SendRequest(int &data_size) {
  http_request_ = HttpOpenRequest(
      internet_connection_,
      method_,
      path_,
      L"HTTP/1.1",
      referer_,
      accept_,
      (u_int)INTERNET_FLAG_SECURE |
          (u_int)INTERNET_FLAG_IGNORE_CERT_CN_INVALID |
          (u_int)INTERNET_FLAG_IGNORE_CERT_DATE_INVALID,
      0);
  HttpSendRequest(http_request_, nullptr, 0, (LPVOID) content_, content_length_);

  int buffer_size = 128;
  data_size = 0;
  char *buffer = new char[buffer_size];
  char *data, *data_backup;
  while (true) {
    int read_size;
    bool read;
    read = InternetReadFile(
        http_request_,
        buffer,
        buffer_size,
        reinterpret_cast<LPDWORD>(&read_size));

    if (read_size == 0) {
      break;
    }
    if (!read) {
      exit(0);
    } else {
      data_backup = new char[data_size];
      memcpy(data_backup, data, data_size);
      data = new char[data_size + read_size];
      memcpy(data, data_backup, data_size);
      memcpy(data + data_size, buffer, read_size);
      data_size += read_size;
    }
  }
  delete[]buffer;
  delete[]data_backup;
  return data;
}
}