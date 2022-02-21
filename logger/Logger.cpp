#include "Logger.h"

#include <fstream>
#include <iostream>

namespace logger {
	std::string root_folder() {
		return std::getenv("ROOT_FOLDER");
	}

	std::ostream& get_events_stream() {
		static std::ofstream fout(root_folder() + std::string("/logs/events.txt"));
		return fout;
	}

	std::string time_represent() {
		std::ostringstream time_represent;
		const auto now = std::chrono::system_clock::now();
		const auto now_time = std::chrono::system_clock::to_time_t(now);
		time_represent << std::ctime(&now_time);
		std::string time_represent_str = time_represent.str();
		time_represent_str.pop_back();
		return time_represent_str;
	}
}