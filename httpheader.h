//
// Created by Godbuntu on 2021-02-16.
//

#ifndef HTTPS_NETWORK_HTTPHEADER_H_
#define HTTPS_NETWORK_HTTPHEADER_H_

namespace Request {
namespace Method {
const wchar_t *GET = L"GET";
const wchar_t *POST = L"POST";
}

namespace Accept {
const wchar_t *Default[] = {
    L"text/html",
    L"application/xhtml+xml",
    L"application/xml;q=0.9",
    L"image/avif",
    L"image/webp",
    L"aimage/apng",
    L"*/*;q=0.8",
    L"application/signed-exchange;v=b3;q=0.9",
    nullptr,
};
}

namespace ContentType {
const wchar_t *FormEncoded = L"application/x-www-form-urlencoded";
const wchar_t *Json = L"application/json";
}
}

#endif //HTTPS_NETWORK_HTTPHEADER_H_
