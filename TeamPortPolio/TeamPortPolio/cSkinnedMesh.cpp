#include "stdafx.h"
#include "cSkinnedMesh.h"
#include "cAllocateHierarchy.h"
#include "IEntity.h"	
#include "ISteeringEntity.h"

cSkinnedMesh::cSkinnedMesh()
	: m_pRoot(NULL)
	, m_pAnimController(NULL)
	, m_fBlendTime(0.35f)
	, m_fPassedBlendTime(0.0f)
	, m_isAnimBlend(false)
{
	m_pIEntity = NULL;
	m_currentIndex = FG_READYATTACK;

}

cSkinnedMesh::cSkinnedMesh(const cSkinnedMesh & pResource)
	: m_pRoot(NULL)
	, m_pAnimController(NULL)
	, m_fBlendTime(0.35f)
	, m_fPassedBlendTime(0.0f)
	, m_isAnimBlend(false)
{
	m_pRoot = new ST_BONE;
	/*D3DXFRAME temp = *pResource.m_pRoot;
	m_pRoot = &temp;*/
	//m_pRoot = pResource.m_pRoot;
	CopyFrame(m_pRoot, pResource.m_pRoot);
	pResource.m_pAnimController->CloneAnimationController(pResource.m_pAnimController->GetMaxNumAnimationOutputs(), pResource.m_pAnimController->GetMaxNumAnimationSets(), pResource.m_pAnimController->GetMaxNumTracks(), pResource.m_pAnimController->GetMaxNumEvents(), &m_pAnimController);
	
	m_pIEntity = NULL;
	m_currentIndex = FG_READYATTACK;

	SetupBoneMatrixPtrs(m_pRoot);
	m_fPassedTime = 0.0f;
	m_pAnimController->GetAnimationSet(3, &m_currentAnim);
}


cSkinnedMesh::~cSkinnedMesh()
{
	cAllocateHierarchy ah;
	D3DXFrameDestroy(m_pRoot, &ah);
	SAFE_RELEASE(m_pAnimController);
}

void cSkinnedMesh::Setup(char* szFolder, char* szFile)
{
	std::string sFullPath(szFolder);
	sFullPath = sFullPath + std::string("/") + std::string(szFile);

	cAllocateHierarchy ah;
	ah.SetFolder(szFolder);
	//	m_pAnimController->CloneAnimationController()
	D3DXLoadMeshHierarchyFromX(sFullPath.c_str(),
		D3DXMESH_MANAGED,
		D3DDevice,
		&ah,
		NULL,
		&m_pRoot,
		&m_pAnimController);

	SetupBoneMatrixPtrs(m_pRoot);
	m_fPassedTime = 0.0f;
	//if (pLeg)pLeg->SetParent(m_pRoot);
	m_pAnimController->GetAnimationSet(m_currentIndex, &m_currentAnim);
}

void cSkinnedMesh::Update()
{
	m_fPassedTime += TIME->GetElapsedTime();

	if (m_isAnimBlend)
	{
		m_fPassedBlendTime += TIME->GetElapsedTime();
		if (m_fPassedBlendTime >= m_fBlendTime)
		{
			m_isAnimBlend = false;
			m_pAnimController->SetTrackWeight(0, 1.0f);
			m_pAnimController->SetTrackEnable(1, false);
			//

		}
		else
		{
			float fWeight = m_fPassedBlendTime / m_fBlendTime;
			m_pAnimController->SetTrackWeight(0, fWeight);
			m_pAnimController->SetTrackWeight(1, 1.0f - fWeight);
		}
	}


	//cout << 1000.0f - (m_pIEntity->Speed()*100.0f )<< endl;
	//TIME->ElapsedUpdate();
	m_pAnimController->AdvanceTime(TIME->GetElapsedTime(), NULL);



	Update(m_pRoot, NULL);

	UpdateSkinnedMesh(m_pRoot);
}

void cSkinnedMesh::Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
{
	if (pFrame == NULL)
		pFrame = m_pRoot;

	ST_BONE* pBone = (ST_BONE*)pFrame;
	pBone->CombinedTransformationMatrix = pBone->TransformationMatrix;
	/*cout << pBone->TransformationMatrix._11 << " "<<pBone->TransformationMatrix._12 << " "<<pBone->TransformationMatrix._13 << " "<<pBone->TransformationMatrix._14 << endl;
	cout << pBone->TransformationMatrix._21 << " " << pBone->TransformationMatrix._22 << " " << pBone->TransformationMatrix._23 << " " << pBone->TransformationMatrix._24 << endl;
	cout << pBone->TransformationMatrix._31 << " " << pBone->TransformationMatrix._32 << " " << pBone->TransformationMatrix._33 << " " << pBone->TransformationMatrix._34 << endl;
	cout << pBone->TransformationMatrix._41 << " " << pBone->TransformationMatrix._42 << " " << pBone->TransformationMatrix._43 << " " << pBone->TransformationMatrix._44 << endl;
*/


	if (m_pIEntity)
	{
		D3DXMATRIXA16 matS, matR, matT;
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		D3DXMatrixIdentity(&matT);
		D3DXMatrixScaling(&matS, 0.5f, 0.5f, 0.5f);
		D3DXMatrixRotationY(&matR, MATH->GetRotY(m_pIEntity->Forward()));
		D3DXMatrixTranslation(&matT, m_pIEntity->Pos().x, m_pIEntity->Pos().y, m_pIEntity->Pos().z);
		m_matWorld = matS*matR* matT;

	}
	if (pParent)
	{
		pBone->CombinedTransformationMatrix *=
			((ST_BONE*)pParent)->CombinedTransformationMatrix;
	}
	if (pFrame->pFrameFirstChild)
	{
		Update(pFrame->pFrameFirstChild, pFrame);
	}

	if (pFrame->pFrameSibling)
	{
		Update(pFrame->pFrameSibling, pParent);
	}
}

void cSkinnedMesh::Render(LPD3DXFRAME pFrame)
{
	if (pFrame == NULL)
		pFrame = m_pRoot;

	ST_BONE* pBone = (ST_BONE*)pFrame;



	D3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;

		if (pBoneMesh->MeshData.pMesh)
		{
			m_matWorld *= pBone->CombinedTransformationMatrix;
			
			D3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
			for (size_t i = 0; i < pBoneMesh->vecMtl.size(); ++i)
			{
				D3DDevice->SetTexture(0, pBoneMesh->vecTexture[i]);
				D3DDevice->SetMaterial(&pBoneMesh->vecMtl[i]);
				pBoneMesh->MeshData.pMesh->DrawSubset(i);
			}
		}
	}

	if (pFrame->pFrameFirstChild)
	{
		Render(pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		Render(pFrame->pFrameSibling);
	}
}

void cSkinnedMesh::SetupBoneMatrixPtrs(LPD3DXFRAME pFrame)
{
	if (pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh =
			(ST_BONE_MESH*)pFrame->pMeshContainer;
		if (pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				ST_BONE* pBone =
					(ST_BONE*)D3DXFrameFind(m_pRoot, pSkinInfo->GetBoneName(i));
				//cout << "Bone : " << pSkinInfo->GetBoneName(i) << endl;
				
				pBoneMesh->ppBoneMatrixPtrs[i] =
					&(pBone->CombinedTransformationMatrix);
			/*	cout << pBone->CombinedTransformationMatrix._11 << " " << pBone->CombinedTransformationMatrix._12 << " " << pBone->CombinedTransformationMatrix._13 << " " << pBone->CombinedTransformationMatrix._14 << endl;
				cout << pBone->CombinedTransformationMatrix._21 << " " << pBone->CombinedTransformationMatrix._22 << " " << pBone->CombinedTransformationMatrix._23 << " " << pBone->CombinedTransformationMatrix._24 << endl;
				cout << pBone->CombinedTransformationMatrix._31 << " " << pBone->CombinedTransformationMatrix._32 << " " << pBone->CombinedTransformationMatrix._33 << " " << pBone->CombinedTransformationMatrix._34 << endl;
				cout << pBone->CombinedTransformationMatrix._41 << " " << pBone->CombinedTransformationMatrix._42 << " " << pBone->CombinedTransformationMatrix._43 << " " << pBone->CombinedTransformationMatrix._44 << endl;
*/
			}
		}
	}//
	 //cout << "sibling : " << pSkinInfo->GetBoneName(i) << endl;

	if (pFrame->pFrameFirstChild)
	{
		//cout << "child : " << pFrame->pFrameFirstChild->Name() << endl;
		SetupBoneMatrixPtrs(pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		SetupBoneMatrixPtrs(pFrame->pFrameSibling);
	}
}

void cSkinnedMesh::UpdateSkinnedMesh(LPD3DXFRAME pFrame)
{
	if (pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh =
			(ST_BONE_MESH*)pFrame->pMeshContainer;
		if (pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				//cout << pSkinInfo->GetBoneName(i)<<endl;
				pBoneMesh->pCurrentBoneMatrices[i] =
					pBoneMesh->pBoneOffsetMatrices[i] * *(pBoneMesh->ppBoneMatrixPtrs[i]);	
			}
		}

		BYTE* src = NULL;
		BYTE* dest = NULL;

		pBoneMesh->pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&src);
		pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (void**)&dest);

		pBoneMesh->pSkinInfo->UpdateSkinnedMesh(
			pBoneMesh->pCurrentBoneMatrices, NULL, src, dest);

		pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
		pBoneMesh->pOrigMesh->UnlockVertexBuffer();
	}

	if (pFrame->pFrameFirstChild)
	{
		UpdateSkinnedMesh(pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		UpdateSkinnedMesh(pFrame->pFrameSibling);
	}
}

void cSkinnedMesh::SetAnimationIndex(int nIndex)
{

	int num = m_pAnimController->GetNumAnimationSets();				// 애니메이션 정보를 가지고 옴

	if (nIndex > num) nIndex = nIndex % num;

	LPD3DXANIMATIONSET pAnimSet = NULL;
	m_pAnimController->GetAnimationSet(nIndex, &pAnimSet);			// 해당 인덱스의 애니메이션을 가지고 옴
	m_pAnimController->SetTrackAnimationSet(0, pAnimSet);			// 0을 꼭 넣어두기(Track)
	//m_pAnimController->GetCurrentTrackEvent(,D3DXEVENT_);

	//m_pAnimController->

	SAFE_RELEASE(pAnimSet);
}

void cSkinnedMesh::SetAnimationIndexBlend(int nIndex)
{
	m_isAnimBlend = true;
	m_fPassedBlendTime = 0.0f;
	int num = m_pAnimController->GetNumAnimationSets();
	if (nIndex > num)nIndex = nIndex%num;

	LPD3DXANIMATIONSET pPrevAnimSet = NULL;
	LPD3DXANIMATIONSET pNextAnimSet = NULL;

	D3DXTRACK_DESC stTrackDesc;

	m_pAnimController->GetTrackDesc(0, &stTrackDesc);
	m_pAnimController->GetTrackAnimationSet(0, &pPrevAnimSet);
	m_pAnimController->SetTrackAnimationSet(1, pPrevAnimSet);
	m_pAnimController->SetTrackDesc(1, &stTrackDesc);

	m_pAnimController->GetAnimationSet(nIndex, &pNextAnimSet);
	m_pAnimController->SetTrackAnimationSet(0, pNextAnimSet);
	m_pAnimController->SetTrackPosition(0, 0.0f);


	m_pAnimController->SetTrackWeight(0, 0.0f);
	m_pAnimController->SetTrackWeight(1, 1.0f);

	SAFE_RELEASE(pPrevAnimSet);
	SAFE_RELEASE(pNextAnimSet);

	m_fPassedTime = 0.0f;
	m_currentIndex = nIndex;
	m_pAnimController->GetAnimationSet(m_currentIndex, &m_currentAnim);
}



LPD3DXFRAME cSkinnedMesh::CopyFrame(LPD3DXFRAME pFrame, const LPD3DXFRAME& pCopyedFrame)
{
	
	//ST_BONE_MESH* test=(ST_BONE_MESH*)pFrame;
	pFrame->Name = pCopyedFrame->Name;
	pFrame->pMeshContainer = NULL;
	if (pCopyedFrame->pMeshContainer)
	{
		//pFrame->pMeshContainer = new ST_BONE_MESH;
		ST_BONE_MESH* pMeshContainer = new ST_BONE_MESH;
		//pMeshContainer = (ST_BONE_MESH*)pCopyedFrame->pMeshContainer;
		//pFrame->pMeshContainer = pMeshContainer;


		pMeshContainer->MeshData = ((ST_BONE_MESH*)pCopyedFrame->pMeshContainer)->MeshData;
		/*((ST_BONE_MESH*)pCopyedFrame->pMeshContainer)->MeshData.pMesh->CloneMeshFVF(((ST_BONE_MESH*)pCopyedFrame->pMeshContainer)->MeshData.pMesh->GetOptions(), ST_PNT_VERTEX::FVF, D3DDevice, &pMeshContainer->MeshData.pMesh);
		((ST_BONE_MESH*)pCopyedFrame->pMeshContainer)->MeshData.pPatchMesh->CloneMesh(((ST_BONE_MESH*)pCopyedFrame->pMeshContainer)->MeshData.pPatchMesh->GetOptions(), NULL, &pMeshContainer->MeshData.pPatchMesh);
		((ST_BONE_MESH*)pCopyedFrame->pMeshContainer)->MeshData.pPMesh->ClonePMeshFVF(((ST_BONE_MESH*)pCopyedFrame->pMeshContainer)->MeshData.pPMesh->GetOptions(), ST_PNT_VERTEX::FVF, D3DDevice, &pMeshContainer->MeshData.pPMesh);
		pMeshContainer->MeshData.Type = ((ST_BONE_MESH*)pCopyedFrame->pMeshContainer)->MeshData.Type;*/
		
		//((ST_BONE_MESH*)pCopyedFrame->pMeshContainer)->MeshData.Type->ClonePMeshFVF(((ST_BONE_MESH*)pCopyedFrame->pMeshContainer)->MeshData.pPMesh->GetOptions(), ST_PNT_VERTEX::FVF, D3DDevice, &pMeshContainer->MeshData.pPMesh);
		pMeshContainer->Name = ((ST_BONE_MESH*)pCopyedFrame->pMeshContainer)->Name;
		pMeshContainer->NumMaterials = ((ST_BONE_MESH*)pCopyedFrame->pMeshContainer)->NumMaterials;
		pMeshContainer->pAdjacency = new DWORD;
		pMeshContainer->pAdjacency = ((ST_BONE_MESH*)pCopyedFrame->pMeshContainer)->pAdjacency;
		pMeshContainer->pBoneOffsetMatrices = new D3DXMATRIX;
		pMeshContainer->pBoneOffsetMatrices = ((ST_BONE_MESH*)pCopyedFrame->pMeshContainer)->pBoneOffsetMatrices;
		pMeshContainer->pCurrentBoneMatrices = new D3DXMATRIX;
		pMeshContainer->pCurrentBoneMatrices = ((ST_BONE_MESH*)pCopyedFrame->pMeshContainer)->pCurrentBoneMatrices;
		pMeshContainer->pEffects = new D3DXEFFECTINSTANCE;
		pMeshContainer->pEffects = ((ST_BONE_MESH*)pCopyedFrame->pMeshContainer)->pEffects;
		pMeshContainer->pMaterials = new D3DXMATERIAL;
		pMeshContainer->pMaterials = ((ST_BONE_MESH*)pCopyedFrame->pMeshContainer)->pMaterials;
		pMeshContainer->pNextMeshContainer = new ST_BONE_MESH;
		pMeshContainer->pNextMeshContainer = (ST_BONE_MESH*)pCopyedFrame->pMeshContainer->pNextMeshContainer;

		((ST_BONE_MESH*)pCopyedFrame->pMeshContainer)->pOrigMesh->CloneMeshFVF(((ST_BONE_MESH*)pCopyedFrame->pMeshContainer)->pOrigMesh->GetOptions(), ST_PNT_VERTEX::FVF, D3DDevice, &pMeshContainer->pOrigMesh);
	
		pMeshContainer->vecMtl = ((ST_BONE_MESH*)pCopyedFrame->pMeshContainer)->vecMtl;
		pMeshContainer->vecTexture = ((ST_BONE_MESH*)pCopyedFrame->pMeshContainer)->vecTexture;
		
		((ST_BONE_MESH*)pCopyedFrame->pMeshContainer)->pSkinInfo->Clone(&pMeshContainer->pSkinInfo);
		pMeshContainer->ppBoneMatrixPtrs = new D3DXMATRIX*[pMeshContainer->pSkinInfo->GetNumBones()];//((ST_BONE_MESH*)pCopyedFrame->pMeshContainer)->ppBoneMatrixPtrs;

		pFrame->pMeshContainer = pMeshContainer;
		//pFrame->pMeshContainer->pSkinInfo = pCopyedFrame->pMeshContainer->pSkinInfo;

		//((ST_BONE_MESH*)(((ST_BONE*)pFrame)->pMeshContainer))= ((ST_BONE*)pCopyedFrame)->pMeshContainer;
	}
	//D3DXMatrixIdentity(&pFrame->TransformationMatrix);

	pFrame->TransformationMatrix = ((ST_BONE*)pCopyedFrame)->TransformationMatrix;
	pFrame->pFrameFirstChild = NULL;
	pFrame->pFrameSibling = NULL;
	if (pCopyedFrame->pFrameFirstChild != NULL)pFrame->pFrameFirstChild = new ST_BONE;
	if (pCopyedFrame->pFrameSibling != NULL)   pFrame->pFrameSibling = new ST_BONE;
	
	if (pCopyedFrame->pFrameFirstChild != NULL)
	{
		//cout << "child : " << pFrame->pFrameFirstChild->Name() << endl;
		CopyFrame(pFrame->pFrameFirstChild, pCopyedFrame->pFrameFirstChild);
	}

	if (pCopyedFrame->pFrameSibling != NULL)
	{
		CopyFrame(pFrame->pFrameSibling, pCopyedFrame->pFrameSibling);
	}
	return pFrame;
}

