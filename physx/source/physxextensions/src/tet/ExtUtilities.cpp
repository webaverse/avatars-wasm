// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of NVIDIA CORPORATION nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Copyright (c) 2008-2022 NVIDIA Corporation. All rights reserved.

#include "foundation/PxAssert.h"
#include "ExtUtilities.h"
#include "GuAABBTreeBuildStats.h"
#include "foundation/PxFPU.h"

namespace physx
{
namespace Ext
{
	using namespace Gu;
	
	void buildTree(const PxU32* triangles, const PxU32 numTriangles, const Vec3* points, PxArray<Gu::BVHNode>& tree, PxF32 enlargement)
	{
		//Computes a bounding box for every triangle in triangles
		AABBTreeBounds boxes;
		boxes.init(numTriangles);
		for (PxU32 i = 0; i < numTriangles; ++i)
		{
			const PxU32* tri = &triangles[3 * i];
			PxBounds3 box = PxBounds3::empty();
			box.include(points[tri[0]].toFloat());
			box.include(points[tri[1]].toFloat());
			box.include(points[tri[2]].toFloat());
			box.fattenFast(enlargement);
			boxes.getBounds()[i] = box;
		}

		Gu::buildAABBTree(numTriangles, boxes, tree);
	}
}
}
