# https client
 c++ https client without openssl (using wininet)

# example
``` C++
#include <iostream>

#include "httpclient.h"
#include "httpheader.h"

int main() {
  Http::SslClient http_client(L"httpbin.org");
  http_client.SetMethod(Http::Method::POST);
  http_client.SetPath(L"/post");
  http_client.SetUserAgent(
      L"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.152 Safari/537.36");
  http_client.SetAccept(Http::Accept::Default);
  http_client.SetReferer(L"https://google.com/");
  http_client.AddBodyData(Http::ContentType::FormEncoded,
                          "test1=data1&test2=data2",
                          strlen("test1=data1&test2=data2"));

  int data_size = 0;
  char *result = http_client.SendRequest(data_size);
  std::cout << "Data size: " << data_size << std::endl;
  std::cout << result << std::endl;
  delete[]result;
  return 0;
}
```
