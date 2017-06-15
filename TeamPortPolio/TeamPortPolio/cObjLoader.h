#pragma once

class cMtlTex;
class cConstruct;

class cObjLoader
{
public:
	cObjLoader();
	~cObjLoader();

private:
	map<string, cMtlTex* > m_mapMtlTex;

public:
	void LoadMtlLib(char* szFolder, char* szFile);
	LPD3DXMESH LoadMesh(OUT vector<cMtlTex*> &vecMtlTex, IN char* szFolder, IN char* szFile);
	LPD3DXMESH LoadMesh(OUT vector<cMtlTex*> &vecMtlTex, IN char* szFolder, IN char* szFile, bool newone);
	LPD3DXMESH LoadMesh_Map(OUT vector<cMtlTex*> &vecMtlTex, OUT vector<ST_PNT_VERTEX> &vecVertex, OUT vector<DWORD>& vecIndex,
						OUT int& cellPerRow, OUT float& cellSpace, 
						OUT vector<cConstruct*>& vecConstruct,
						IN char* szFolder, IN char* szFile, bool doOptimizeInplace = true);

};