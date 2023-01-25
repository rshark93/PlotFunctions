#include "main.h"

#include <cmath>
#include <iomanip>

using namespace matplot;

calculate_function::calculate_function() {
	std::cout << "calculate function constructor" << std::endl;
}

calculate_function::~calculate_function() {
	std::cout << "\ncalculate_function destructor" << std::endl;
}

void calculate_function::init_plot_setting(const double x_start, const double x_end, const double y_min,
	const double y_max, const int max_points)
{
	x_start_value_ = x_start;
	x_end_value_ = x_end;

	y_min_value_ = y_min;
	y_max_value_ = y_max;

	graph_max_points_ = max_points;
}

void calculate_function::calculate(const std::string& graph_name, double(* math_func)(double))
{
	const auto step = (abs(x_start_value_) + abs(x_end_value_)) / graph_max_points_;

	std::vector<point2d> function_result;

	for (auto x = x_start_value_; x < x_end_value_; x += step) {
		auto y = math_func(x);

		if(y < y_min_value_) y = y_min_value_;
		if (y > y_max_value_) y = y_max_value_;

		function_result.push_back(point2d{ x, y });
	}

	result_points_.insert(std::pair(graph_name, function_result ));
}

void calculate_function::print_result(const std::string& graph_name)
{
	if (!result_points_.count(graph_name)) {
		std::cout << "Graph name Key not valid!";
		return;
	}

	std::cout << "\n" << std::setw(20) << "PLOT: " << graph_name << std::endl;

	std::cout << std::setw(5) << " " << "  ";
	std::cout << std::setw(10) << "X:";
	std::cout << std::setw(20) << "Y:" << std::endl;

	const auto pts = result_points_[graph_name];

	for (auto i = 0; i < pts.size() - 1; ++i) {
		std::cout << std::setw(5) << i + 1 << ". ";
		std::cout << std::setw(10) << pts[i].x;
		std::cout << std::setw(20) << pts[i].y << std::endl;
	}
}

int calculate_function::plot_graphic(const std::string& graph_name, const std::array<float, 3>& graph_color,
                                     const float dot_size) {
	std::vector<double> x_values;
	std::vector<double> y_values;

	for (const auto & [x, y] : result_points_[graph_name]) {
		x_values.push_back(x);
		y_values.push_back(y);
	}

	plot(x_values, y_values, "--gs")->line_width(2)
	                                .marker_size(dot_size)
	                                .color(graph_color)
	                                .marker_color(GRAY)
	                                .marker_face_color(BLACK);

	hold(on);
	show();
	return 0;
}

// 10^tg(x)
double math_fun_0(const double x) {
	return pow(10, tan(x));
}

// 10^sin(x)
double math_fun_1(const double x) {
	return pow(10, sin(x));
}

int main(const int argc, char* argv[]) {
	constexpr auto total_points = 21;
	constexpr auto x_start = 0.;
	constexpr auto x_end = 6.;

	constexpr auto min_y = -50.f;
	constexpr auto max_y = 50.f;

	constexpr auto first_fun_name = "10^tg(x)";
	constexpr auto second_fun_name = "10^sin(x)";

	const auto calculate_obj = std::make_unique<calculate_function>();

	calculate_obj->init_plot_setting(x_start, x_end, min_y, max_y, total_points);

	calculate_obj->calculate(first_fun_name, math_fun_0);
	calculate_obj->calculate(second_fun_name, math_fun_1);

	calculate_obj->print_result(first_fun_name);
	calculate_obj->print_result(second_fun_name);

	constexpr auto dot_size = 5.f;

	if(!calculate_obj->plot_graphic(second_fun_name, RED, dot_size))
		return EXIT_FAILURE;
	
	if (!calculate_obj->plot_graphic(first_fun_name, GREEN, dot_size))
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}