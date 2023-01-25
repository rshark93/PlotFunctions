#pragma once

#include <map>
#include <vector>

#include <matplot/matplot.h>

#define RED { 1., .0, .0 }
#define GREEN { 0., 1., .0 }
#define BLUE { 0., .0, 1. }
#define BLACK { 0., 0., 0. }
#define GRAY { .5, .5, .5 }
#define WHITE { 1., 1., 1. }

struct point2d {
	double x;
	double y;
};

class calculate_function {

public:
	void init_plot_setting(double x_start, double x_end, double y_min, double y_max, int max_points);
	void calculate(const std::string& graph_name, double(*math_func)(double));
	void print_result(const std::string& graph_name);
	int plot_graphic(const std::string& graph_name, const std::array<float,3> &graph_color, float dot_size);

	calculate_function();
	~calculate_function();
private:
	double x_start_value_ = 0.;
	double x_end_value_ = 10.;
	double y_min_value_ = -1000.;
	double y_max_value_ = 1000.;

	int graph_max_points_ = 21;

	std::map<std::string, std::vector<point2d>> result_points_;
};