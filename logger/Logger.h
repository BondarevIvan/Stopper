#pragma once
#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE 	"\033[34m"

#define LOG_TERMINAL(...) logger::logging(std::cerr, BLUE, __VA_ARGS__)
#define LOG_EVENT(...) logger::logging(logger::get_events_stream(), GREEN, "[ EVENT.\t", logger::time_represent(), "]", __VA_ARGS__)
#define LOG_ERROR(...) logger::logging(logger::get_events_stream(), RED,   "[ ERROR.\t", logger::time_represent(), "]", __VA_ARGS__)

namespace logger {
	std::string root_folder();
	template<class Arg>
	void logging(std::ostream& out, const Arg& arg) {
		out << arg << std::endl;
	}
	template<class Arg, class... Args>
	void logging(std::ostream& out, const Arg& arg, Args... args) {
		out << arg << ' ';
		logging(out, args...);
	}

	std::string time_represent();
	std::ostream& get_events_stream();
}