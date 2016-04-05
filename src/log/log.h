// Copyright 2016 Intel Corporation
// License
// Author : xinxin.shu@intel.com

#ifndef PROJECT_LOG_H_
#define PROJECT_LOG_H_

#include <sys/time.h>
#include <string>
#include <stdio.h>


enum LogLevel : unsigned char {
  DEBUG_LEVEL = 0,
  INFO_LEVEL,
  WARN_LEVEL,
  ERROR_LEVEL,
  FATAL_LEVEL,
};

class Logger {
 public:
  Logger(const string& path, const loglevel = LogLevel::INFO_LEVLE)
    : path(path),
      log_level(log_level) {
    logstream.open(path.c_str());
  }
  virtual ~Logger() {
    logstream.close();
  }
  void get_threadid(const uint64_t thread_id);
  void logv(const LogLevel log_level, const char* format, va_list ap);
  void logv(const char* format, va_list ap);
 private:
  std::string path;
  enum LogLevel log_level
  std::ofstream logstream;

}

#endif // PROJECT_LOG_H_
