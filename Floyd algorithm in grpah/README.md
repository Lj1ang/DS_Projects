# Group_04 Project_3
## Background
&emsp; &emsp; 该项目从实际问题出发，将路径问题抽象为图，并通过Floyd算法实现对最短路径的求解，输出  **a )** 最短路径的距离以**b)** 走最短路径所通过的节点

## Features
- 通过调用百度地图API，展示了用户可以选择的地点
- 维护了一个基于STL里的vector实现的Map类来存储邻接矩阵
- 通过迭代器实现遍历
- 运用Floyd算法实现路径的计算
- 通过`PrintMatrix()`来输出矩阵
- 与`DisplayPath()`来得到最短路径

## Usage
- 依据`Option` 的提示选择`1` ,`2`或者`3`
- 如果出现`WRONG INPUT!!!\nTRY AGAIN` 请重新输入