/*
 * Log.cpp
 *
 *  Created on: Nov 27, 2023
 *      Author: Che Nam Hoang
 */
#include "Log.h"

extern UART_HandleTypeDef huart2;
Logger::LogPriority Logger::priority = Logger::LogPriority::LOG_PRIORITY_DEBUG;
char Logger::mBuffer[LOG_BUFFER_SIZE] = {0};
UART_HandleTypeDef *Logger::mHuart = &huart2;
