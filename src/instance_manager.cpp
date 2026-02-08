#include "bstk/instance_manager.hpp"
#include "bstk/config.hpp"

namespace bstk {

	InstanceManager::InstanceManager(Config& config) : config_(&config) {
		reload();
	}

	void InstanceManager::reload() {
		instances_.clear();
		auto names = config_->get_instance_names();
		for (const auto& name : names) {
			instances_.emplace_back(*config_, name);
		}
	}

	Instance* InstanceManager::get(std::string_view name) {
		for (auto& inst : instances_) {
			if (inst.name() == name) return &inst;
		}
		return nullptr;
	}

	const Instance* InstanceManager::get(std::string_view name) const {
		for (const auto& inst : instances_) {
			if (inst.name() == name) return &inst;
		}
		return nullptr;
	}

	Instance* InstanceManager::find(std::function<bool(const Instance&)> pred) {
		for (auto& inst : instances_) {
			if (pred(inst)) return &inst;
		}
		return nullptr;
	}

	std::vector<Instance*> InstanceManager::find_all(std::function<bool(const Instance&)> pred) {
		std::vector<Instance*> result;
		for (auto& inst : instances_) {
			if (pred(inst)) result.push_back(&inst);
		}
		return result;
	}

	Instance& InstanceManager::create(std::string name) {
		if (has(name)) {
			throw std::runtime_error("Instance already exists: " + name);
		}
		instances_.emplace_back(*config_, std::move(name));
		return instances_.back();
	}

	bool InstanceManager::remove(std::string_view name) {
		auto it = std::find_if(instances_.begin(), instances_.end(),
			[name](const Instance& i) { return i.name() == name; });

		if (it != instances_.end()) {
			// Remove all keys from config
			auto keys = config_->get_keys_with_prefix("bst.instance." + std::string(name) + ".");
			for (const auto& key : keys) {
				config_->remove(key);
			}
			instances_.erase(it);
			return true;
		}
		return false;
	}

	bool InstanceManager::has(std::string_view name) const {
		return get(name) != nullptr;
	}

	void InstanceManager::save_all() {
		for (auto& inst : instances_) {
			inst.save_to_config();
		}
	}

	void InstanceManager::apply_to_all(std::function<void(Instance&)> func) {
		for (auto& inst : instances_) {
			func(inst);
		}
	}

	std::vector<std::reference_wrapper<Instance>> InstanceManager::with_root_access() {
		std::vector<std::reference_wrapper<Instance>> result;
		for (auto& inst : instances_) {
			if (inst.props().enable_root_access) {
				result.push_back(std::ref(inst));
			}
		}
		return result;
	}

	std::vector<std::reference_wrapper<Instance>> InstanceManager::with_high_fps() {
		std::vector<std::reference_wrapper<Instance>> result;
		for (auto& inst : instances_) {
			if (inst.props().enable_high_fps) {
				result.push_back(std::ref(inst));
			}
		}
		return result;
	}

	std::vector<std::reference_wrapper<Instance>> InstanceManager::matching_resolution(int width, int height) {
		std::vector<std::reference_wrapper<Instance>> result;
		for (auto& inst : instances_) {
			if (inst.props().fb_width == width && inst.props().fb_height == height) {
				result.push_back(std::ref(inst));
			}
		}
		return result;
	}

} // namespace bstk