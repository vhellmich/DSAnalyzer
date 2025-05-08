#include "Logger.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> Logger::s_Logger;

void Logger::Init() {
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/events.log", true);
    auto console_sink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();

    file_sink->set_level(spdlog::level::trace); 
    console_sink->set_level(spdlog::level::warn); 

    // Set format (optional)
    file_sink->set_pattern("[%H:%M:%S] [%^%l%$] [thread %t] [%s:%# %!] %v");
    console_sink->set_pattern("[%H:%M:%S] [%^%l%$] [thread %t] [%s:%# %!] %v");

    s_Logger = std::make_shared<spdlog::logger>("Logger", spdlog::sinks_init_list{ file_sink, console_sink });

    spdlog::register_logger(s_Logger);
    spdlog::set_level(spdlog::level::trace);
}

std::shared_ptr<spdlog::logger>& Logger::Get() {
    return s_Logger;
}