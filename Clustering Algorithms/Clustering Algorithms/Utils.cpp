#include "Utils.h"



Utils::Utils()
{



	
	





	



}


Utils::~Utils()
{
}


string Utils::colorTable(int colorIndex)
{
	string tabela[25] =
	{ "#000000", // 1-Black
		"#FF0000", // 2-Red
		"#00FF00", // 3-Lime
		"#0000FF", // 4-Blue
		"#FFFF00", // 5-Yellow
		"#00FFFF", // 6-Cyan
		"#FF00FF", // 7-Fuchsia
		"#C0C0C0", // 8-Silver
		"#808080", // 9-Gray
		"#800000", //10-Maroon
		"#808000", //11-Olive
		"#008000", //12-Green
		"#800080", //13-Purple
		"#008080", //14-Teal
		"#000080", //15-Navy
		"#DC143C", //16-crimson
		"#CD5C5C", //17-indian red
		"#FF4500", //18-orange red
		"#FF8C00", //19-dark orange
		"#DAA520", //20-golden rod
		"#2F4F4F", //21-dark slate gray
		"#8B4513", //22-saddle brown
		"#BC8F8F", //23-rosy brown
		"#B0C4DE", //24-light steel blue
		"#BDB76B", //25-dark khaki
	};
	return tabela[colorIndex % 25];
}


void Utils::showSolution(ShortSolution *solution)
{

	ofstream a;
	string pythonFile = "teste.py";
	a.open(pythonFile);
	int size = 14;
	string corAtual;
	string corPreenchimento;
	/*
	Node* node;

	a << "import matplotlib.pyplot as plt\n\n";

	if (solution != nullptr)
	{
		CRoute *cr = solution->first;

		for (; cr != nullptr; cr = cr->next)
		{
			//plotando arestas intraCluster
			for (RNode *ns = cr->first; ns->next != nullptr; ns = ns->next)
			{
				a << "plt.plot([" << ns->node->xNode << "," << ns->next->node->xNode
					<< "], [" << ns->node->yNode << "," << ns->next->node->yNode << "], color="
					<< "'#000000'" << R"(, linestyle='-', marker=',')"
					<< ", markerfacecolor=" << "'#000000'"
					<< ", markersize=" << size << ")\n";
			}
			//plotando arestas interCluster
			if (cr->next != nullptr)
			{
				a << "plt.plot([" << cr->last->node->xNode << "," << cr->next->first->node->xNode
					<< "], [" << cr->last->node->yNode << "," << cr->next->first->node->yNode << "], color="
					<< "'#000000'" << R"(, linestyle='-', marker=',')"
					<< ", markerfacecolor=" << "'#000000'"
					<< ", markersize=" << size << ")\n";
			}
		}
		//fechando ciclo entre os clusters
		a << "plt.plot([" << solution->last->last->node->xNode << "," << solution->first->first->node->xNode
			<< "], [" << solution->last->last->node->yNode << "," << solution->first->first->node->yNode << "], color="
			<< "'#000000'" << R"(, linestyle='-', marker=',')"
			<< ", markerfacecolor=" << "'#000000'"
			<< ", markersize=" << size << ")\n";
	}

	for (int i = 0; i < graph.order; ++i) {
		node = &graph.nodeList[i];
		corAtual = "\'" + colorTable(node->cluster->id - 1) + "\'";
		a << "plt.plot([" << node->xNode << "], [" << node->yNode << "], color="
			<< corAtual << ", linestyle=\'--\', marker='o'"
			", markerfacecolor=" << corAtual
			<< ", markersize=" << size << ")\n";
	}
	for (int i = 0; i < graph.order; ++i) {
		node = &graph.nodeList[i];
		a << "plt.text(" << node->xNode << ", " << node->yNode << ",\'" << node->tabu->id << "\'"
			" , horizontalalignment='center',verticalalignment='center', color =" << "\'#FFFFFF\'" << ")\n";
	}
	a << "plt.show()\n";
	a.close();
	string command = "python " + pythonFile;
	system(command.c_str());

	*/

}