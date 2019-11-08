#include "TreeNode.hpp"
#include <iostream>
#include <string>
bool lbvr::TreeNode::generateChildren(const int external_exclude1, const int external_exclude2) {
	this->route.push_back(this);
	for (int i = 0; i < TreeNode::CMax; i++) {
		if (i == external_exclude1 || i == external_exclude2) continue;
		this->children.emplace_back(
			std::make_unique<TreeNode>(
				i,
				this->route,
				this->edges,
				this->corners));
	}
	return !this->children.empty();
}

bool lbvr::TreeNode::choiseChildrenFromEdges(const int external_exclude) {
	this->route.push_back(this);
	for (auto p = this->edges.begin(); p != this->edges.end(); p++) {
		if (this->color == std::get<0>(*p) && external_exclude != std::get<1>(*p)) {
			int cc = std::get<1>(*p);
			auto tmp = std::make_unique<TreeNode>(
				cc,
				this->route,
				this->edges,
				this->corners
				);
			tmp->edges.remove(*p);
			this->children.emplace_back(std::move(tmp));
		}
		else if (this->color == std::get<1>(*p) && external_exclude != std::get<0>(*p)) {
			int cc = std::get<0>(*p);
			auto tmp = std::make_unique<TreeNode>(
				cc,
				this->route,
				this->edges,
				this->corners
				);
			tmp->edges.remove(*p);
			this->children.emplace_back(std::move(tmp));
		}
	}
	return !this->children.empty();
}

bool lbvr::TreeNode::choiseChildrenFromCorners(const int external_exclude) {
	auto iter = this->route.rbegin();
	int cc1 = (*iter)->color;
	this->route.push_back(this);

	for (auto p = this->corners.begin(); p != this->corners.end(); p++) {
		int cc2 = -1;
		if (this->color == std::get<0>(*p) && cc1 == std::get<1>(*p) && external_exclude != std::get<2>(*p)) {
			cc2 = std::get<2>(*p);
		}
		else if(this->color == std::get<0>(*p) && cc1 == std::get<2>(*p) && external_exclude != std::get<1>(*p)) {
			cc2 = std::get<1>(*p);
		}
		else if(this->color == std::get<1>(*p) && cc1 == std::get<2>(*p) && external_exclude != std::get<0>(*p)) {
			cc2 = std::get<0>(*p);
		}
		else if(this->color == std::get<1>(*p) && cc1 == std::get<0>(*p) && external_exclude != std::get<2>(*p)) {
			cc2 = std::get<2>(*p);
		}
		else if(this->color == std::get<2>(*p) && cc1 == std::get<0>(*p) && external_exclude != std::get<1>(*p)) {
			cc2 = std::get<1>(*p);
		}
		else if(this->color == std::get<2>(*p) && cc1 == std::get<1>(*p) && external_exclude != std::get<0>(*p)) {
			cc2 = std::get<0>(*p);
		}

		if(cc2 != -1) {
			auto tmp = std::make_unique<TreeNode>(
				cc2,
				this->route,
				this->edges,
				this->corners
				);
			tmp->corners.remove(*p);
			this->children.emplace_back(std::move(tmp));
		}
	}
	return !this->children.empty();
}


std::string lbvr::TreeNode::toString() const {
	auto color2str = [](int color) -> std::string {
		switch (color) {
		case TreeNode::R: return "R";
		case TreeNode::G: return "G";
		case TreeNode::B: return "B";
		case TreeNode::Y: return "Y";
		case TreeNode::W: return "W";
		case TreeNode::N: return "N";
		}
		return "X";
	};
	
	std::string ret = "Layer " + std::to_string(this->route.size()) + " [" + color2str(this->color) + "] -> (";
	for (const auto & p : this->children) {

		ret += color2str(p->color) + ", ";
	}
	ret += " )";
	return ret;
}


void lbvr::TreeNode::generate(TreeNode & node, const std::function<void(TreeNode&)>& next, int exclude1, int exclude2) {
	if (!node.generateChildren(exclude1, exclude2)) {
#ifdef _DEBUG
		std::cerr << node.toString() << " Failed." << std::endl;
#endif
		return;
	}
#ifdef _DEBUG
	std::cerr << node.toString() << std::endl;
#endif

	for (const auto & child : node.children) next(*child);
}

void lbvr::TreeNode::chooseEdge(TreeNode & node, const std::function<void(TreeNode&)> & next, int exclude) {
	if (!node.choiseChildrenFromEdges(exclude)) {
#ifdef _DEBUG
		std::cerr << node.toString() << " Failed." << std::endl;
#endif
		return;
	}
#ifdef _DEBUG
	std::cerr << node.toString() << std::endl;
#endif

	for (const auto & child : node.children) next(*child);
}

void lbvr::TreeNode::chooseCorner(TreeNode & node, const std::function<void(TreeNode&)>& next, int exclude) {
	if (!node.choiseChildrenFromCorners(exclude)) {
#ifdef _DEBUG
		std::cerr << node.toString() << " Failed." << std::endl;
#endif
		return;
	}
#ifdef _DEBUG
	std::cerr << node.toString() << std::endl;
#endif

	for (const auto & child : node.children) next(*child);
}

