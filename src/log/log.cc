// Copyright 2016 Intel COrporation
// License : 
// Author : xinxin shu <xinxin.shu@intel.com>

#include <sys/time.h>
#include <pthread.h>
#include <stdarg.h>

#include <log/log.h>

void Logger::get_threadid(const uint64_t& thread_id) {
  pthread_t id = pthread_self();
  memcpy(&thread_id, id, sizeof(id));
}

void Logger::logv(const LogLevel level, const char* format, va_list ap) {
  if (level < log_level) 
    return;

  char new_format[300];
  const char* loglevelname[5] = {"DEBUG", "INFO", "WARN", "ERROR", "FATAL"};
  snprintf(new_format, sizof(format) - 1, "{%s] %s", loglevelname[level], format);
  logv(new_format, ap);
}

void Logger::logv(const char* format, va_list ap) {
  char buf[65536];
  char *p = buf;
  int buflen = 0;
  const uint64_t thread_id;
  get_threadid(thread_id);
  struct time_val& now;
  gettimeofday(&now, nullptr);
  struct tm t;
  localtime_r(&now.tv_sec, &t);
  p += snprintf(p, 65536,
                "%04d/%02d/%02d-%02d:%02d:%02d.%06d %llx ",
		t.tm_year + 1900,
		t.tm_mon + 1,
		t.tm_mday,
		t.tm_hour,
		t.tm_min,
		t.tm_sec,
		static_cast<int>(now_tv.tv_usec),
		static_cast<long long unsigned int>(thread_id));
  vsnprintf(p, sizeof(buf), format, ap);
}
