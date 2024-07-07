/**
 * @file timer.h
 * @date 2024-07-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <chrono>
#include <thread>

class Timer {
    private:
        bool running;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime, m_endTime;
        std::chrono::duration<double> m_elapsedTime;
    public:
        Timer() : running(false), m_elapsedTime(std::chrono::high_resolution_clock::duration::zero()) {}

        // 开始或恢复计时
        void start() {
            running = true;
            m_startTime = std::chrono::high_resolution_clock::now();
        }
        // 暂停计时
        void stop() {
            if (running) {
                m_endTime = std::chrono::high_resolution_clock::now();
                m_elapsedTime += m_endTime - m_startTime;
                running = false;
            }
        }
        // 返回已经计时的时间
        double elapsed() {
            if (running) {
                return std::chrono::duration<double>((std::chrono::high_resolution_clock::now() - m_startTime) + m_elapsedTime).count();
            }
            else {
                return m_elapsedTime.count();
            }
        }
        // 重置计时器
        void reset() {
            running = false;
            m_elapsedTime = std::chrono::high_resolution_clock::duration::zero();
        }
        // 休眠s秒
        void sleep(int s) {
            std::this_thread::sleep_for(std::chrono::seconds(s));
        }
};

#endif