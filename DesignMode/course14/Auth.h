//
// Created by djangojiang on 2020/7/18.
//

#ifndef STUDY_AUTH_H
#define STUDY_AUTH_H

#include "ApiRequest.h"
#include <cstdint>

class Auth{
public:
    int32_t AuthRequest(const AbstractApiRequest& oApiRequest);
};

#endif //STUDY_AUTH_H
