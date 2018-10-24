#pragma once

#include <vector>
#include <stack>
#include <list>
#include <map>

#define SIZE 3

extern const int result[SIZE][SIZE];

typedef unsigned int u32;

class graph {
	//std::vector<std::vector<std::vector<int>>> visited_matrices;
	std::map<std::vector<std::vector<int>>, int> visited_matrices;

enum move_type {
	m_up			,
	m_down			,
	m_left			,
	m_right			,
	m_jump_up		,
	m_jump_down		,
	m_jump_left		,
	m_jump_right	,

	m_no_type		= -1
};

private:
	bool								check_if_final_step		(const std::vector<std::vector<int>> &cur, const std::vector<std::vector<int>> &result);

	std::vector<std::vector<int>>		create_child			(const std::vector<std::vector<int>> &parent, const int i, const int j, const int step_i, const int step_j);

	const std::vector<std::vector<int>> move_up					(const std::vector<std::vector<int>> &parent, const int i, const int j);
	const std::vector<std::vector<int>> move_down				(const std::vector<std::vector<int>> &parent, const int i, const int j);
	const std::vector<std::vector<int>> jump_up					(const std::vector<std::vector<int>> &parent, const int i, const int j);
	const std::vector<std::vector<int>> jump_down				(const std::vector<std::vector<int>> &parent, const int i, const int j);
	const std::vector<std::vector<int>> move_left				(const std::vector<std::vector<int>> &parent, const int i, const int j);
	const std::vector<std::vector<int>> move_right				(const std::vector<std::vector<int>> &parent, const int i, const int j);
	const std::vector<std::vector<int>> jump_right				(const std::vector<std::vector<int>> &parent, const int i, const int j);
	const std::vector<std::vector<int>> jump_left				(const std::vector<std::vector<int>> &parent, const int i, const int j);

	bool								check_if_visited		(const std::vector<std::vector<int>> &child);

	bool								if_exist_and_not_visited(const std::vector<std::vector<int>> &new_child, std::stack <std::vector<std::vector<int>>> &v_stack);
	bool								if_exist_and_not_visited(const std::vector<std::vector<int>> &new_child, std::list <std::vector<std::vector<int>>> &v_list);
	bool								do_step					(const std::vector<std::vector<int>> &data, const int i, const int j, std::stack <std::vector<std::vector<int>>> &v_stack);
	move_type							do_step					(const std::vector<std::vector<int>> &data, const int i, const int j, std::list <std::vector<std::vector<int>>> &v_list);

	void								print_all_steps			(std::stack <std::vector<std::vector<int>>> &st);
	void								print_all_steps			(const std::string &filename, std::list <std::vector<std::vector<int>>> &st);
	void								print_all_steps			(const std::string &filename, std::map<std::vector<std::vector<int>>, std::vector<std::vector<int>>> came_from, const std::vector<std::vector<int>> &goal, const std::vector<std::vector<int>> &start);

	void								print_matrix			(const std::vector<std::vector<int>> &matrix);
	void								print_matrix_to_file	(const std::string &file_name, std::vector<std::vector<int>> &matrix, const u32 stack_size);

	int									calculate_manhattan_cost(const std::vector<std::vector<int>> &matrix);
private:
	struct								board;
	struct								less_then_by_priority;
public:
	graph								() {}
	~graph								() {}

	void								depth_first_traversal	(const std::vector<std::vector<int>> &started_data, const std::vector<std::vector<int>> &result);
	void								breadth_first_traversal	(const std::vector<std::vector<int>> &started_data, const std::vector<std::vector<int>> &result);
	void								A_star_search			(const std::vector<std::vector<int>> &started_data, const std::vector<std::vector<int>> &result);
};
