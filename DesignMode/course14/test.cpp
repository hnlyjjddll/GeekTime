//
// Created by djangojiang on 2020/7/18.
//

#include "Auth.h"
#include "ApiRequest.h"
#include <iostream>

using namespace std;

int main(void) {
    UrlApiRequestBody oUrlRequestBody("www","appid","token",1595062800000);
    int32_t iRet = Auth().AuthRequest(UrlApiRequest(oUrlRequestBody));
    cout<<iRet<<endl;
    return 0;
}