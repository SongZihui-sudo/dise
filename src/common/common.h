#ifndef COMMON_H
#define COMMON_H

#include <thread>

/*
    获取线程 id
*/
std::thread::id GetThreadId();

/*
    获取时间
*/
std::uint64_t getTime();

int get_length( long x );

#endif