﻿#pragma once

#include "Buffer.hpp"

namespace acid
{
	class ACID_EXPORT VertexBuffer :
		public Buffer
	{
	private:
		uint32_t m_vertexCount;
	public:
		VertexBuffer(const uint64_t &elementSize, const size_t &vertexCount, const void *newData);

		uint32_t GetVertexCount() const { return m_vertexCount; }
	};
}
