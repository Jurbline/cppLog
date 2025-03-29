#include "../../include/SearchEngineServer/CalculateTask.h"
#include "../../include/ProtocolParser.h"
#include "../../include/LRUCache/LRUCache.h"
#include "../../include/LRUCache/CacheManager.h"
#include "../../include/SearchEngineServer/SearchEngineServer.h"
#include "../../include/Reactor/TcpConnection.h"
#include "../../include/Reactor/InetAddress.h"
#include "../../include/MyLog.h"
#include <iostream>

namespace SearchEngine
{

extern thread_local const char *tname;
//用于多线程环境中为不同线程存储独立的状态或标识符（如线程名）


void wordSearcher();
void pageSearcher();
void nextPageSearcher();
void process();

}
