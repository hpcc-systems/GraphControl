#pragma once

#include "Platform.h"
#include "GraphDB.h"
#include "GraphvizLayout.h"
#include "GraphRender.h"
#include "GraphHotItem.h"

class HPCCSystemsGraphViewControlAPI;
class CDotViewCommon
{
public:
	HPCCSystemsGraphViewControlAPI * m_api;
	ln::IGraphBufferPtr m_buffer;
	ln::IGraphPtr m_g;
	ln::IGraphRenderPtr m_gr;
	//ln::IGraphRenderPtr m_gro;
	ln::IGraphHotItemPtr m_hotItem;
	ln::IGraphSelectionBagPtr m_selection;

	enum MOUSEDOWN
	{
		MOUSEDOWN_UNKNOWN = 0,
		MOUSEDOWN_NORMAL,
		MOUSEDOWN_DBLCLK,
		MOUSEDOWN_OVERVIEW,
		MOUSEDOWN_OVERVIEW_WIN,
		MOUSEDOWN_LAST

	} m_mouseDown;
	int m_mouseDownPosX;
	int m_mouseDownPosY;
	int m_scrollDownPosX;
	int m_scrollDownPosY;

	std::string m_dot;
	std::string m_svg;

	virtual void Invalidate() = 0;
	virtual int GetScrollOffsetX() = 0;
	virtual int GetScrollOffsetY() = 0;
	virtual void SetScrollOffset(int x, int y) = 0;
	virtual void SetScrollSize(int w, int h, bool redraw) = 0;
	virtual bool GetClientRectangle(ln::RectD & rect) = 0;
	virtual void UpdateWindow() = 0;
	virtual void InvalidateSelection() = 0;
	virtual void operator()(const std::string & dot, const std::string & svg) = 0;

	//  --- IAPICallback ---
	void Clear();
	void LoadTestData();
	void LoadXML(const std::string & verticesXML, const std::string & edgesXML);
	void LoadXML2(const std::string & xml);
	void LoadXGMML(const std::string & xgmml);
	void MergeXGMML(const std::string & xgmml);
	const std::string GetSVG();
	const char * GetLocalisedXGMML(int item, std::string & xgmml);
	double SetScale(double scale);
	double GetScale();
	virtual void CenterOnGraphItem(ln::IGraphItem * item = NULL);
	virtual void CenterOnItem(int item, bool sizeToFit, bool widthOnly);
	void StartLayout(const std::string & layout);
	void SetMessage(const std::string & msg);
	int Find(const std::string & text, bool includeProperties, std::vector<int> & results);
	bool HasItems();
	int GetSelection(std::vector<int> & results);
	int GetSelection(std::vector<std::string> & results);
	bool SetSelected(const std::vector<int> & items, bool clearPrevious);
	bool SetSelected(const std::vector<std::string> & items, bool clearPrevious);
	const ln::IClusterSet & GetClusters();
	int GetProperties(int item, ln::StringStringMap & results);
	unsigned int GetItem(const std::string &externalID);
	const char * GetGlobalID(int item);
	int GetVertices(std::vector<int> & results);
	//  --- IAPICallback ---

	void CenterOn(const ln::PointD & worldPoint);
	void MoveTo(const ln::PointD & worldPoint, int x, int y);
	ln::PointD GetCenterAsWorldPoint();
	void CalcScrollbars(bool redraw = false);
};

