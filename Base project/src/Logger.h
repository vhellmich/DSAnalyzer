#ifndef SIMPLE_LOGGER_H
#define SIMPLE_LOGGER_H


#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <memory>

/// <summary>
/// Basic logger class using spdlog.
/// </summary>
class Logger {
public:
    /// <summary>
	/// Must be called before using the logger.
    /// </summary>
    static void Init();
    static std::shared_ptr<spdlog::logger>& Get();

private:
    static std::shared_ptr<spdlog::logger> s_Logger;
};

#endif // SIMPLE_LOGGER_H