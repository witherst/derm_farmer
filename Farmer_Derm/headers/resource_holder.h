#ifndef RESOURCE_HOLDER_H
#define RESOURCE_HOLDER_H

namespace fd {

#include <assert.h>
#include <string>

	template <typename Resource, typename Identifier>
	class ResourceHolder {
	public:
		template<typename Parameter>
		void Load(Identifier id, const std::string& filename, const Parameter& second_parameter);
		void Load(Identifier id, const std::string& filename);
		Resource& Get(Identifier id);
		const Resource& Get(Identifier id) const;

	private:
		std::map<Identifier, std::unique_ptr<Resource>> resource_map_;

	};

#include "resource_holder.inl"

} // namespace fd
#endif

