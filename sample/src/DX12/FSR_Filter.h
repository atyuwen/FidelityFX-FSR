// FidelityFX Super Resolution Sample
//
// Copyright (c) 2021 Advanced Micro Devices, Inc. All rights reserved.
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once
#include "PostProc/PostProcCS.h"

using namespace CAULDRON_DX12;

struct State;

class FSR_Filter
{
public:
	void OnCreate(Device* pDevice, ResourceViewHeaps* pResourceViewHeaps, bool slowFallback = false);
	void OnCreateWindowSizeDependentResources(Device* pDevice, ID3D12Resource* input, ID3D12Resource* output, int displayWidth, int displayHeight, State* pState, bool hdr);
	void OnDestroyWindowSizeDependentResources();
	void OnDestroy();
	void Upscale(ID3D12GraphicsCommandList* pCommandList, int displayWidth, int displayHeight, State *pState, DynamicBufferRing* pConstantBufferRing, bool hdr);

private:
	PostProcCS                      m_easu;
	PostProcCS                      m_easuL;
	bool                            m_easuLInitialized = false;
	PostProcCS                      m_rcas;
	PostProcCS                      m_bilinear;
	CBV_SRV_UAV                     m_outputTextureUav;
	CBV_SRV_UAV                     m_inputTextureSrv;
	Texture							m_intermediary;
	CBV_SRV_UAV                     m_intermediaryUav;
	CBV_SRV_UAV                     m_intermediarySrv;
};
