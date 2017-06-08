#include "stdafx.h"
#include "cGraph.h"


cGraph::cGraph(int nodeCount)
{
	for (int i = 0; i < nodeCount; i++)
	{
		m_nodes.push_back(new GraphNode(i));
	}

	for (int i = 0; i < nodeCount; i++)
	{
		m_edges.push_back(list<GraphEdge*>());
	}
}

cGraph::~cGraph()
{
	for (int i = 0; i < m_nodes.size(); i++) { delete m_nodes[i]; }
	m_nodes.clear();

	for (int i = 0; i < m_edges.size(); i++)
	{
		for (EdgeListIter it = m_edges[i].begin(); it != m_edges[i].end(); it++)
		{
			delete *it;
		}
		m_edges[i].clear();
	}
	m_edges.clear();
}

int cGraph::NodeCount() { return m_nodes.size(); }

bool cGraph::IsValid(int nodeIndex)
{
	return nodeIndex >= 0 && nodeIndex < NodeCount();
}

GraphNode* cGraph::GetNode(int index)
{
	if (IsValid(index)) return m_nodes[index];
	return NULL;
}

GraphEdge* cGraph::GetEdge(int from, int to)
{
	EdgeList list = GetEdgeList(from);
	for (EdgeListIter it = list.begin(); it != list.end(); it++)
	{
		if ((*it)->To() == to) { return *it; }
	}
	return NULL;
}

void cGraph::AddEdge(int from, int to, float cost)
{
	/*if (IsValid(from) && IsValid(to))
	{*/
	m_edges[from].push_back(new GraphEdge(from, to, cost));
	//}
}

void cGraph::RemoveEdge(int from, int to)
{
	EdgeList list = GetEdgeList(from);
	for (EdgeListIter it = list.begin(); it != list.end(); it++)
	{
		if ((*it)->To() == to) { it = list.erase(it); break; }
	}
}