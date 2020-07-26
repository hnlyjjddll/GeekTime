//
// Created by jdl on 2020/7/26.
//

#include "display.h"
#include "storage.h"

int main(void){
    RedisStorage oRedisStorage;
    WebCfg cfg;
    WebDisplay oDisplay(cfg);

    oDisplay.Dispay(oRedisStorage, HtmlDisplayFormat());
    return 0;
}