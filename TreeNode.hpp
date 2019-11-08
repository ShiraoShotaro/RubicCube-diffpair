#ifndef LBVR_TREENODE_HPP
#define LBVR_TREENODE_HPP

#include <list>
#include <vector>
#include <memory>
#include <tuple>
#include <functional>

namespace lbvr {

struct TreeNode {
public:
	enum Color {
		R = 0, G, B, Y, W, N, CMax
	};
	
	TreeNode() : color(-1) {}
	TreeNode(int _color, const std::vector<const TreeNode *> & _route, const std::list<std::tuple<int, int>> & _edges, const std::list<std::tuple<int, int, int>> & _corners)
		: color(_color), route(_route), edges(_edges), corners(_corners) {}

	int color;

	std::list<std::unique_ptr<TreeNode>> children;
	std::vector<const TreeNode *> route;

	std::list<std::tuple<int, int>> edges;
	std::list<std::tuple<int, int, int>> corners;

	bool generateChildren(const int external_exclude1 = -1, const int external_exclude2 = -1);
	bool choiseChildrenFromEdges(const int external_exclude = -1);
	bool choiseChildrenFromCorners(const int external_exclude = -1);

	static void generate(TreeNode & node, const std::function<void(TreeNode&)> & next, int exclude1 = -1, int exclude2 = -1);
	static void chooseEdge(TreeNode & node, const std::function<void(TreeNode&)> & next, int exclude = -1);
	static void chooseCorner(TreeNode & node, const std::function<void(TreeNode&)> & next, int exclude = -1);

	std::string toString() const;
};

}

#endif
