/***********
* -*- coding: utf-8 -*-
*@Author: 蒋磊
*@email: 2872509481@qq.com
*
************/
#include<iostream>
#include <limits.h>
#include<vector>
#include<iomanip>
#include<Windows.h>
#define MAX 100
#define INFINITY INT_MAX
//INFINITY : 没有路径

//Map: 存储数据
class Map {
public:
	std::vector<std::vector<int>  > graph;
	std::vector<std::string> place;

	//修改图的内容
	Map() {
		//存储地点
		place = { "天府广场","宽窄巷子","古大慈圣寺","文殊院",
				  "人民公园","东郊记忆","东湖公园","成华区雕塑公园",
   				  "成都武侯祠博物馆","四川雕塑艺术院","圣花乡","锦城湖" };
		//通过二维数据储存矩阵
		std::vector<int> row_1 = { INFINITY, 1300, 2800, 2300, 1500, INFINITY, 7600, INFINITY, 2900, 3300, INFINITY, INFINITY, };
		std::vector<int> row_2 = { 1300, INFINITY, INFINITY, INFINITY, 1600, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, };
		std::vector<int> row_3 = { 2800, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, 5700, 3200, INFINITY, INFINITY, INFINITY, INFINITY, };
		std::vector<int> row_4 = { 2300, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, };
		std::vector<int> row_5 = { 1500, 1600, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, 3800, INFINITY, INFINITY, INFINITY, };
		std::vector<int> row_6 = { INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, 3200, INFINITY, INFINITY, INFINITY, INFINITY, };
		std::vector<int> row_7 = { 7600, INFINITY, 5700, INFINITY, INFINITY, INFINITY, INFINITY, 5600, 8100, 5300, 10000, 13000, };
		std::vector<int> row_8 = { INFINITY, INFINITY, 3200, INFINITY, INFINITY, 3200, 5600, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, };
		std::vector<int> row_9 = { 2900, INFINITY, INFINITY, INFINITY, 3800, INFINITY, 8100, INFINITY, INFINITY, 1800, INFINITY, INFINITY, };
		std::vector<int> row_10 = { 3300, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, 5300, INFINITY, 1800, INFINITY, INFINITY, 9000, };
		std::vector<int> row_11 = { INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, 10000, INFINITY, INFINITY, INFINITY, INFINITY, 12000, };
		std::vector<int> row_12 = { INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,13000,INFINITY,INFINITY,9000,12000,INFINITY };
		graph.push_back(row_1);
		graph.push_back(row_2);
		graph.push_back(row_3);
		graph.push_back(row_4);
		graph.push_back(row_5);
		graph.push_back(row_6);
		graph.push_back(row_7);
		graph.push_back(row_8);
		graph.push_back(row_9);
		graph.push_back(row_10);
		graph.push_back(row_11);
		graph.push_back(row_12);

	}
};

class Graph : public Map {


public:
	std::vector<std::vector<int>  > distance;
	std::vector<std::vector<int>  > path;

	Graph() {
		Map();

		//深复制
		distance = graph;
		path = graph;

		//初始化 path
		for (auto row = path.begin(); row < path.end(); row++)
			for (auto col = (*row).begin(); col < (*row).end(); col++)
				*col = -1;

	}

	// get函数
	std::vector<std::vector<int>  > GetGraph()const {
		return graph;
	}
	std::vector<std::vector<int>  > GetDistance()const {
		return distance;
	}
	std::vector<std::vector<int>  > GetPath()const {
		return path;
	}

	//Floyd 算法，遍历最短路径
	void Floyd() {

		for (size_t each_node = 0; each_node < distance.size(); each_node++) {  //遍历，此处为便于索引没有用迭代器
			for (size_t row = 0; row < distance.size(); row++) {
				for (size_t col = 0; col < distance.size(); col++) {
					if (distance[row][each_node] != INFINITY &&  //节点判断，只有不为∞的节点才能通过
						distance[each_node][col] != INFINITY &&
						distance[row][col] >
						distance[row][each_node] +
						distance[each_node][col]) {

						distance[row][col] =
							distance[row][each_node] +
							distance[each_node][col];
						path[row][col] = each_node;
					}
				}
			}
		}
	}

	// 通过迭代器遍历所有地点
	void PrintPlaces() {
		int cnt = 1;  //输出标号控制
		for (auto iter = place.begin(); iter < place.end(); iter++, cnt++)
			std::cout << cnt << "." << *iter << std::endl;
	}
	//打印矩阵函数。传入矩阵变量名
	void PrintMatrix(std::vector<std::vector<int>  > matrix) const {  //const修饰，不会改变矩阵内容
		char col_num = 'a';  //由于地点名太长，此处输出矩阵时用字母代替地点，a映射为place[0]，以此类推
		std::cout << "     \t";
		for (auto col = (*matrix.begin()).begin();  //迭代器遍历
			col < (*matrix.begin()).end(); col++, col_num++) {
			std::cout << std::setiosflags(std::ios::left)  //格式化输出
				      << std::setw(8) << col_num;
		}
		puts("\n\n");  //格式化输出
		col_num = 'a';
		for (auto row = matrix.begin(); row < matrix.end(); row++, col_num++) {
			std::cout << std::setiosflags(std::ios::left)  //格式化输出
				<< std::setw(8) << col_num;
			for (auto col = (*row).begin(); col < (*row).end(); col++) {
				if (*col == INFINITY) {
					std::cout << "∞      ";
					continue;
				}
				if (*col == -1) {
					std::cout << "N/A     ";
					continue;
				}
				std::cout << std::setiosflags(std::ios::left)  //格式化输出
					<< std::setw(8) << *col;
			}
			puts("\n\n");
		}
	}
	//递归分治，输出路径
	 void GetPath(size_t row ,size_t col) {
		size_t each_node = path[row][col];
		
		if (each_node != -1) {
			GetPath(row, each_node);
			std::cout << place[each_node] << "->";
			GetPath(each_node, col);
		}
		
	}
	 //输出路径
	void DisplayPath(int row , int col) {
		std::cout << "From " << place[row] << " to " << place[col]<<" : ";  //输出起点
		std::cout << place[row] << "->";
		Graph::GetPath(row, col);  //递归调用
		std::cout << place[col] << std::endl;  //输出终点
		std::cout<< " \nThe distance is "<< distance[row][col]<<" m" << std::endl;  //输出距离
		puts("");
	}

};
int main(){
	system("start map.html");  //打开地图
	Graph* my_graph = new Graph();
	my_graph->Floyd();//调用Floyd算法计算最短路径
	//用户交互部分
	my_graph->PrintPlaces();
	int option = 0;
	//主程序循环
	while (true) {

		//用户选择信息
		std::cout << "Options:" << std::endl;
		std::cout << "  1.display the whole infomation of matrix and paths" << std::endl;
		std::cout << "  2.find the shortest path from point_A to point_B" << std::endl;
		std::cout << "  3.quit" << std::endl;
		std::cout << "Pleae input your option:";
		std::cin >> option;

		//判断选择并执行
		if (option == 1) {
			std::cout << "Graph=" << std::endl;
			my_graph->PrintMatrix(my_graph->GetGraph()); //打印图的矩阵
			std::cout << "Distance=" << std::endl;
			my_graph->PrintMatrix(my_graph->GetDistance());  //打印距离矩阵
			std::cout << "Path=" << std::endl;
			my_graph->PrintMatrix(my_graph->GetPath());  //打印路径矩阵
		}

		else if (option == 2) {
			int row = 0; int col = 0;
			std::cout << "From: " << std::endl;  //格式化输出
			std::cin >> row;
			std::cout << "To: " << std::endl;
			std::cin >> col;
			row--; col--;
			if (0 <= row && row <= 11 && 0 <= col && col <= 11 && row != col) //输入合法性判断
				my_graph->DisplayPath(row, col);
			else {
				std::cout << "WRONG INPUT!!!\nTRY AGAIN" << std::endl;
				continue;
			}
		}

		else if (option == 3)  //退出程序
			return 0;

		else {
			std::cout << "WRONG INPUT!!!\nTRY AGAIN" << std::endl;
			continue;
		}
	}
	return 0;
}