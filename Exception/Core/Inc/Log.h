/*
 * Library name: Log.h
 *     Version : 1.0.0
 *   Created on: Nov 27, 2023
 *       Author: Che Nam Hoang
 * 	Description: This library contains functions for printing device operating logs at 5 levels
 *               [DEBUG][INFO][WARN][ERROR][FATAL]
 */

#ifndef LOG_H_
#define LOG_H_

#include "main.h"
#include <cstdint>
#include <cstring>
#include <cstdio>

#define LOG_ENABLE true // true for enable log action, false to disable it.
/**
 * @brief  Marco function for Logger
 *
 */
#if LOG_ENABLE

#define LOGD_STM32(message, ...) Logger::Debug(message, ##__VA_ARGS__)
#define LOGI_STM32(message, ...) Logger::Infor(message, ##__VA_ARGS__)
#define LOGW_STM32(message, ...) Logger::Warn(message, ##__VA_ARGS__)
#define LOGE_STM32(message, ...) Logger::Error(message, ##__VA_ARGS__)
#define LOGF_STM32(message, ...) Logger::Fatal(message, ##__VA_ARGS__)
#else
#define LOGD_STM32(message, ...)
#define LOGI_STM32(message, ...)
#define LOGW_STM32(message, ...)
#define LOGE_STM32(message, ...)
#define LOGF_STM32(message, ...)
#endif

#define LOGX_HDR_C "[%s:%d][%s]:"
#define LOGX_ARGS_C __FILE_NAME__, __LINE__, __FUNCTION__

#define LOGD(lmess, args...) LOGD_STM32(LOGX_HDR_C lmess, LOGX_ARGS_C, ##args)
#define LOGI(lmess, args...) LOGI_STM32(LOGX_HDR_C lmess, LOGX_ARGS_C, ##args)
#define LOGW(lmess, args...) LOGW_STM32(LOGX_HDR_C lmess, LOGX_ARGS_C, ##args)
#define LOGE(lmess, args...) LOGE_STM32(LOGX_HDR_C lmess, LOGX_ARGS_C, ##args)
#define LOGF(lmess, args...) LOGF_STM32(LOGX_HDR_C lmess, LOGX_ARGS_C, ##args)

class Logger
{
public:
	enum class LogPriority
	{
	    LOG_PRIORITY_DEBUG,
	    LOG_PRIORITY_INFO,
	    LOG_PRIORITY_WARN,
	    LOG_PRIORITY_ERROR,
	    LOG_PRIORITY_FATAL
	};

	static void setPriority(LogPriority new_priority)
	{
		priority = new_priority;
	}

	template<typename ... Args>
	static void Debug(const char *message, Args ... args)
	{
		if (priority <= LogPriority::LOG_PRIORITY_DEBUG)
		{
			print("[DEBUG]\t");
			snprintf(mBuffer, LOG_BUFFER_SIZE, message, args...);
			print(mBuffer);
			print("\n");
		}
	}

	template<typename ... Args>
	static void Infor(const char *message, Args ... args)
	{
		if (priority <= LogPriority::LOG_PRIORITY_INFO)
		{
			print("[INFO]\t");
			snprintf(mBuffer, LOG_BUFFER_SIZE, message, args...);
			print(mBuffer);
			print("\n");
		}
	}

	template<typename ... Args>
	static void Warn(const char *message, Args ... args)
	{
		if (priority <= LogPriority::LOG_PRIORITY_WARN)
		{
			print("[WARN]\t");
			snprintf(mBuffer, LOG_BUFFER_SIZE, message, args...);
			print(mBuffer);
			print("\n");
		}
	}

	template<typename ... Args>
	static void Error(const char *message, Args ... args)
	{
		if (priority <= LogPriority::LOG_PRIORITY_ERROR)
		{
			print("[ERROR]\t");
			snprintf(mBuffer, LOG_BUFFER_SIZE, message, args...);
			print(mBuffer);
			print("\n");
		}
	}

	template<typename ... Args>
	static void Fatal(const char *message, Args ... args)
	{
		if (priority <= LogPriority::LOG_PRIORITY_FATAL)
		{
			print("[FATAL]\t");
			snprintf(mBuffer, LOG_BUFFER_SIZE, message, args...);
			print(mBuffer);
			print("\n");
		}
	}

private:
    static const uint16_t LOG_BUFFER_SIZE = 1024U;
    static LogPriority priority;
    static UART_HandleTypeDef *mHuart;
    static char mBuffer[LOG_BUFFER_SIZE];
    static void print(const char *pMessage)
    {
        HAL_UART_Transmit(mHuart, (uint8_t*) const_cast<char*>(pMessage),
                strlen(pMessage), 1000);
    }
};

#endif /* LOG_H_ */
