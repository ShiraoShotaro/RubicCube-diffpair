#include <iostream>
#include <string>
#include "TreeNode.hpp"

#include <functional>
using namespace lbvr;

// TEMP
int way_count = 0;

namespace {

void layer2(TreeNode&);
void layer3(TreeNode&);
void layer4(TreeNode&);
void layer5(TreeNode&);
void layer6(TreeNode&);
void layer7(TreeNode&);
void layer8(TreeNode&);
void layer9(TreeNode&);
void layer10(TreeNode&);
void layer11(TreeNode&);
void layer12(TreeNode&);
void layer13(TreeNode&);
void layer14(TreeNode&);

void goal(TreeNode&);

void layer1(TreeNode & root) {
	// 1層目
	root.generate(root, layer2, root.color);
}

void layer2(TreeNode & node) {
	// 2層目
	node.chooseEdge(node, layer3, TreeNode::N);
}

void layer3(TreeNode & node) {
	// 3層目
	node.generate(node, layer4, node.route.at(0)->color);
}

void layer4(TreeNode & node) {
	// 4層目
	node.chooseEdge(node, layer5, TreeNode::W);
}

void layer5(TreeNode & node) {
	// 5層目
	node.generate(node, layer6, node.route.at(1)->color, node.route.at(3)->color);
}

void layer6(TreeNode & node) {
	// 6層目 : ここも何も考えずに普通に作る
	node.generate(node, layer7, node.color, node.route.at(2)->color);
}

void layer7(TreeNode & node) {
	// 7層目 : ここでコーナーのマッチング
	node.chooseCorner(node, layer8, node.route.at(4)->color);
}

void layer8(TreeNode & node) {
	// 8層目
	node.generate(node, layer9, node.route.at(0)->color);
}

void layer9(TreeNode & node) {
	// 9層目
	node.chooseEdge(node, layer10, TreeNode::R);
}

void layer10(TreeNode & node) {
	// 10層目
	node.generate(node, layer11, node.route.at(3)->color, node.route.at(8)->color);
}

void layer11(TreeNode & node) {
	// 11層目
	node.generate(node, layer12, node.color, node.route.at(4)->color);
}

void layer12(TreeNode & node) {
	// 12層目
	node.chooseCorner(node, layer13, node.route.at(10)->color);
}

void layer13(TreeNode & node) {
	// 13層目
	node.generate(node, layer14, node.route.at(0)->color);
}

void layer14(TreeNode & node) {
	// 14層目
	node.chooseEdge(node, goal);
}

void goal(TreeNode & node) {
	// global variable
	way_count++;
	std::cout << ".";
}

}

int main(void) {

	// ルートノードの作成
	TreeNode root;
	root.color = TreeNode::G;

	root.edges = {
		{TreeNode::G, TreeNode::R},
		{TreeNode::G, TreeNode::W},
		{TreeNode::G, TreeNode::N},
		{TreeNode::G, TreeNode::Y},
		{TreeNode::Y, TreeNode::B},
		{TreeNode::Y, TreeNode::N},
		{TreeNode::R, TreeNode::B},
		{TreeNode::R, TreeNode::W},
		{TreeNode::W, TreeNode::B},
		{TreeNode::W, TreeNode::N},
		{TreeNode::R, TreeNode::Y},
		{TreeNode::B, TreeNode::N},
	};

	root.corners = {
		{TreeNode::G, TreeNode::R, TreeNode::Y},
		{TreeNode::G, TreeNode::Y, TreeNode::N},
		{TreeNode::G, TreeNode::N, TreeNode::W},
		{TreeNode::G, TreeNode::W, TreeNode::R},
		{TreeNode::B, TreeNode::Y, TreeNode::N},
		{TreeNode::B, TreeNode::N, TreeNode::W},
		{TreeNode::B, TreeNode::W, TreeNode::R},
		{TreeNode::B, TreeNode::R, TreeNode::Y},
	};

	layer1(root);

	std::cerr << "Finished. Way_num = " << way_count << std::endl;

	while(1);

	return 0;
}

