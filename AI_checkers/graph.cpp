#include "stdafx.h"
#include "graph.h"

#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>

	bool graph::check_if_final_step(const std::vector<std::vector<int>> &cur, const std::vector<std::vector<int>> &result) {
		for (u32 i = 0; i < SIZE; ++i) {
			for (u32 j = 0; j < SIZE; ++j) {
				if (cur[i][j] != result[i][j])
					return false;
			}
		}
	
		return true;
	}

	std::vector<std::vector<int>> graph::create_child(const std::vector<std::vector<int>> &parent, const int i, const int j, const int step_i, const int step_j) {
		std::vector<std::vector<int>> new_ch = std::vector<std::vector<int>>(SIZE, std::vector<int>(SIZE));

		for(u32 i = 0; i < SIZE; ++i) {
			for (u32 j = 0; j < SIZE; ++j) {
				new_ch[i][j] = parent[i][j];
			}
		}

		std::swap(new_ch[i][j], new_ch[i+step_i][j+step_j]);
		return new_ch;
	}

	const std::vector<std::vector<int>> graph::move_up(const std::vector<std::vector<int>> &parent, const int i, const int j) {
		return (j-1 >= 0 && parent[i][j-1] == 0) ? create_child(parent, i, j, 0, -1) : std::vector<std::vector<int>>();
	}

	const std::vector<std::vector<int>> graph::move_down(const std::vector<std::vector<int>> &parent, const int i, const int j) {
		return (j+1 < SIZE && parent[i][j+1] == 0) ? create_child(parent, i, j, 0, 1) : std::vector<std::vector<int>>();
	}

	const std::vector<std::vector<int>> graph::jump_up(const std::vector<std::vector<int>> &parent, const int i, const int j) {
		return (j-2 >= 0 && parent[i][j-2] == 0) ? create_child(parent, i, j, 0, -2) : std::vector<std::vector<int>>();
	}

	const std::vector<std::vector<int>> graph::jump_down(const std::vector<std::vector<int>> &parent, const int i, const int j) {
		return (j+2 < SIZE && parent[i][j+2] == 0) ? create_child(parent, i, j, 0, 2) : std::vector<std::vector<int>> ();
	}

	const std::vector<std::vector<int>> graph::move_left(const std::vector<std::vector<int>> &parent, const int i, const int j) {
		return (i-1 >= 0 && parent[i-1][j] == 0) ? create_child(parent, i, j, -1, 0) : std::vector<std::vector<int>> ();
	}

	const std::vector<std::vector<int>> graph::move_right(const std::vector<std::vector<int>> &parent, const int i, const int j) {
		return (i+1 < SIZE && parent[i+1][j] == 0) ? create_child(parent, i, j, 1, 0) :  std::vector<std::vector<int>> ();
	}

	const std::vector<std::vector<int>> graph::jump_right(const std::vector<std::vector<int>> &parent, const int i, const int j) {
		return (i+2 < SIZE && parent[i+2][j] == 0) ? create_child(parent, i, j, 2, 0) : std::vector<std::vector<int>> ();
	}

	const std::vector<std::vector<int>> graph::jump_left(const std::vector<std::vector<int>> &parent, const int i, const int j) {
		return (i-2 >= 0 && parent[i-2][j] == 0) ? create_child(parent, i, j, -2, 0) : std::vector<std::vector<int>> ();
	}

	bool graph::check_if_visited(const std::vector<std::vector<int>> &child) {
		return visited_matrices.count(child);
	}

	bool graph::if_exist_and_not_visited(const std::vector<std::vector<int>> &new_child, std::stack <std::vector<std::vector<int>>> &v_stack) {
		if (!new_child.empty() && !check_if_visited(new_child)) {
			v_stack.push(new_child);
			return true;
		}

		return false;
	}

	bool graph::if_exist_and_not_visited(const std::vector<std::vector<int>> &new_child, std::list <std::vector<std::vector<int>>> &v_list) {
		if (!new_child.empty() && !check_if_visited(new_child)) {
			v_list.push_back(new_child);
			return true;
		}

		return false;
	}

	bool graph::do_step(const std::vector<std::vector<int>> &data, const int i, const int j, std::stack <std::vector<std::vector<int>>> &v_stack) {
		return (if_exist_and_not_visited(move_up(data, i, j), v_stack) ||
				if_exist_and_not_visited(move_down(data, i, j), v_stack) ||
				if_exist_and_not_visited(move_left(data, i, j), v_stack) ||
				if_exist_and_not_visited(move_right(data, i, j), v_stack) ||
				if_exist_and_not_visited(jump_up(data, i, j), v_stack) ||
				if_exist_and_not_visited(jump_down(data, i, j), v_stack) ||
				if_exist_and_not_visited(jump_left(data, i, j), v_stack) ||
				if_exist_and_not_visited(jump_right(data, i, j), v_stack));
	}

	graph::move_type graph::do_step(const std::vector<std::vector<int>> &data, const int i, const int j, std::list <std::vector<std::vector<int>>> &v_list) {
		if (if_exist_and_not_visited(move_up(data, i, j), v_list))
			return graph::move_type::m_up;
		if (if_exist_and_not_visited(move_down(data, i, j), v_list))
			return graph::move_type::m_down;
		if (if_exist_and_not_visited(move_left(data, i, j), v_list))
			return graph::move_type::m_left;
		if (if_exist_and_not_visited(move_right(data, i, j), v_list))
			return graph::move_type::m_right;
		if (if_exist_and_not_visited(jump_up(data, i, j), v_list))
			return graph::move_type::m_jump_up;
		if (if_exist_and_not_visited(jump_down(data, i, j), v_list))
			return graph::move_type::m_jump_down;
		if (if_exist_and_not_visited(jump_left(data, i, j), v_list))
			return graph::move_type::m_jump_left;
		if (if_exist_and_not_visited(jump_right(data, i, j), v_list))
			return graph::move_type::m_jump_right;

		return graph::move_type::m_no_type;
	}

	void graph::print_all_steps(std::stack <std::vector<std::vector<int>>> &st) {
		u32 step_counter = 0;
		u32 st_size = st.size();

		while(!st.empty()) {
			print_matrix_to_file("depths_first_output.txt", st.top(), st_size - step_counter++); 
			st.pop();
		}
	}

	void graph::print_all_steps(const std::string &filename, std::map<std::vector<std::vector<int>>, std::vector<std::vector<int>>> came_from, const std::vector<std::vector<int>> &goal, const std::vector<std::vector<int>> &start) {
		std::vector<std::vector<int>> current = goal;

		std::list<std::vector<std::vector<int>>> path;

		while (!check_if_final_step(current, start)) {
			std::map<std::vector<std::vector<int>>, std::vector<std::vector<int>>>::iterator it = came_from.find(current);
			current = it->second;
			path.push_back(current);
		}

		path.push_front(goal);

		path.reverse();

		print_all_steps(filename, path);
	}

	void graph::print_all_steps(const std::string &filename, std::list <std::vector<std::vector<int>>> &st) {
		u32 step_counter = 0;

		while(!st.empty()) {
			print_matrix_to_file(filename, st.front(), step_counter++); 
			st.pop_front();
		}
	}

	void graph::depth_first_traversal(const std::vector<std::vector<int>> &started_data, const std::vector<std::vector<int>> &result) {
		std::cout << "Depth First Traversal" << std::endl;

		visited_matrices.clear();

		std::stack <std::vector<std::vector<int>>> visited;
		visited.push(started_data);

		while(!visited.empty()) {
			std::vector<std::vector<int>> data = visited.top();

			if(!check_if_visited(data))
				visited_matrices.insert(std::pair<std::vector<std::vector<int>>, int>(data, 0));

			bool added_to_stack = false;

			for (u32 i = 0; i < SIZE; ++i) {
				for (u32 j = 0; j < SIZE; ++j) {
					if (data[i][j] == -1 || !do_step(data, i, j, visited))
						continue;

					added_to_stack = true;
				}

				if (added_to_stack)		break;
			}
	
			if (added_to_stack && check_if_final_step(visited.top(), result)) {
				print_all_steps(visited); break;
			} else if (!added_to_stack) {
				visited.pop();
			}
		}

		std::cout << std::endl;
	}

	void graph::breadth_first_traversal(const std::vector<std::vector<int>> &started_data, const std::vector<std::vector<int>> &result) {
		std::cout << "Breadth First Traversal" << std::endl;
		
		visited_matrices.clear();

		std::list<std::vector<std::vector<int>>> visited_list;
		visited_list.push_back(started_data);

		std::map<std::vector<std::vector<int>>, std::vector<std::vector<int>>> came_from;
		came_from[started_data] = started_data;

		while(!visited_list.empty()) {
			std::vector<std::vector<int>> data = visited_list.front();
			visited_list.pop_front();

			if(check_if_visited(data))
				continue;

			visited_matrices.insert(std::pair<std::vector<std::vector<int>>, int>(data, 0));

			for (u32 i = 0; i < SIZE; ++i) {
				for (u32 j = 0; j < SIZE; ++j) {
					if (data[i][j] == -1 || do_step(data, i, j, visited_list) == m_no_type)
						continue;

					came_from.insert(std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>>(visited_list.back(), data));

					if (check_if_final_step(visited_list.back(), result)) {
						print_all_steps("breaths_first_output.txt", came_from, result, started_data);
						return;
					}
				}
			}
		}
	}

	struct graph::board {
		std::vector<std::vector<int>> value;
		int priority;

		board(const std::vector<std::vector<int>> &v, const int pr): priority(pr), value(v) {}
	};

	struct graph::less_then_by_priority {
		bool operator()(const board& lhs, const board& rhs) const {
			return lhs.priority > rhs.priority;
		}
	};

	int graph::calculate_manhattan_cost(const std::vector<std::vector<int>> &matrix) {
		int manhattan_distance_sum = 0;
		for (u32 x = 0; x < SIZE; ++x) {
			for (u32 y = 0; y < SIZE; ++y) {
				int value = matrix[x][y]; // tiles array contains board elements
				if (value == 0 || value == -1) 
					continue;

                int dx = x - ((value - 1) / SIZE + ((value - 2) / SIZE)); // x-distance to expected coordinate
                int dy = y - ((value - 1) % SIZE + ((value - 2) % SIZE) ); // y-distance to expected coordinate
                manhattan_distance_sum += abs(dx) + abs(dy); 
			}
		}

		return manhattan_distance_sum;  // Manhattan distance on a square grid
	}

	void graph::A_star_search(const std::vector<std::vector<int>> &started_data, const std::vector<std::vector<int>> &result) {
		std::cout << "A* Search" << std::endl;
		
		visited_matrices.clear();

		board brd(started_data, 0);

		std::priority_queue<board, std::vector<board>, less_then_by_priority> visited;
		visited.push(brd);

		std::map<std::vector<std::vector<int>>, std::vector<std::vector<int>>> came_from;
		came_from.insert(std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>>(started_data, std::vector<std::vector<int>>()));

		std::map<std::vector<std::vector<int>>, int> cost_so_far; // cost_so_far
		cost_so_far.insert(std::pair<std::vector<std::vector<int>>, int>(started_data, 0));

		came_from[started_data] = started_data;
		cost_so_far[started_data] = 0;

		while(!visited.empty()) {
			board data = visited.top();
			visited.pop();
		
			if (check_if_final_step(data.value, result)) {
				print_all_steps("a_star_search_output.txt", came_from, result, started_data);
				return;
			}
		
			if(check_if_visited(data.value))
				continue;
		
			visited_matrices.insert(std::pair<std::vector<std::vector<int>>, int>(data.value, 0));

			std::list<std::vector<std::vector<int>>> visited_list;
			
			int manhattan_cost = calculate_manhattan_cost(data.value);

			for (u32 i = 0; i < SIZE; ++i) {
				for (u32 j = 0; j < SIZE; ++j) {
					if (data.value[i][j] == -1) continue;

					move_type m_t = do_step(data.value, i, j, visited_list);

					if (m_t == m_no_type) continue;

					std::map<std::vector<std::vector<int>>, int>::iterator it = cost_so_far.find(data.value);
					std::map<std::vector<std::vector<int>>, int>::iterator it_next = cost_so_far.find(visited_list.back());

					int new_cost = it->second + 1;

					if (it_next == cost_so_far.end() || new_cost < it->second) {
						if (it_next == cost_so_far.end()) {
							cost_so_far.insert(std::pair<std::vector<std::vector<int>>, int>(visited_list.back(), new_cost)); // second parameter - (value) - distance from start
						} else {
							cost_so_far[visited_list.back()] = new_cost;
						}

						int priority = new_cost + manhattan_cost;
					
						board new_b(visited_list.back(), priority);
						visited.push(new_b);

						came_from.insert(std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>>(new_b.value, data.value));
					}
				}
			}
		}
	}

	void graph::print_matrix_to_file(const std::string &file_name, std::vector<std::vector<int>> &matrix, const u32 step_counter) {
		std::ofstream fout(file_name, std::ios_base::app);

		fout << step_counter << std::endl;

		for(u32 i = 0; i < SIZE; ++i) {
			fout << i << "\t";
			for (u32 j = 0; j < SIZE; ++j)
				fout << matrix[i][j] << " ";

			fout << std::endl;
		}

		fout << std::endl;
		
		fout.close();
	}

	void graph::print_matrix (const std::vector<std::vector<int>> &matrix) {
		for(u32 i = 0; i < SIZE; ++i) {
			std::cout << i << "\t";
			for (u32 j = 0; j < SIZE; ++j)
				std::cout << matrix[i][j] << " ";

			std::cout << std::endl;
		}

		std::cout << std::endl;
	}