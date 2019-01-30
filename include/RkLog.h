/**
 * File name: RkLog.h
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor (http://quamplex.com/redkite)
 *
 * This file is part of Redkite.
 *
 * GeonKick is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef RK_LOGGING_H
#define RK_LOGGING_H

#include <iostream>

#ifdef RK_LOG_DEBUG_LEVEL
#define RK_LOG_DEBUG(smg) std::cout << "[DEBUG]" << __PRETTY_FUNCITON__ << ": " << msg;
#define RK_LOG_INFO_LEVEL
#ifdef // RK_LOG_DEBUG_LEVEL

#ifdef RK_LOG_INFO_LEVEL
#define RK_LOG_INFO(smg) std::cout << "[INFO]" << __PRETTY_FUNCITON__ << ": " << msg;
#define RK_LOG_WARN_LEVEL
#ifdef // RK_LOG_INFO_LEVEL

#ifdef RK_LOG_WARN_LEVEL
#define RK_LOG_WARN(smg) std::cout << "[WARN]" << __PRETTY_FUNCITON__ << ": " << msg;
#define RK_LOG_ERROR_LEVEL
#endif // RK_LOG_WARN_LEVEL

#ifdef RK_LOG_ERROR_LEVEL
#define RK_LOG_ERROR(smg) std::cout << "[ERROR]" << __PRETTY_FUNCITON__ << ": " << msg;
#endif // RK_LOG_ERROR_LEVEL

#endif // RK_LOGGING_H
