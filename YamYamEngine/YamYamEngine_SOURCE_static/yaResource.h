#pragma once
#include "yaEntity.h"

namespace ya
{
	class Resource : public Entity
	{
	public:
		Resource();
		virtual ~Resource();

		virtual HRESULT Load(const std::filesystem::path& path) = 0;

		const std::wstring& GetKey() { return mKey; }
		const std::filesystem::path& GetPath() { return mPath; }

		void SetKey(const std::wstring& key) { mKey = key; }
		void SetPath(const std::filesystem::path& path) { mPath = path; }

	private:
		std::wstring mKey;
		std::filesystem::path mPath;
	};
}
