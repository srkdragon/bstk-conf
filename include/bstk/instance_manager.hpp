#ifndef BSTK_INSTANCE_MANAGER_HPP
#define BSTK_INSTANCE_MANAGER_HPP

#include "instance.hpp"
#include <vector>
#include <iterator>
#include <functional>

namespace bstk {

	class InstanceManager {
	public:
		using Iterator = std::vector<Instance>::iterator;
		using ConstIterator = std::vector<Instance>::const_iterator;

		explicit InstanceManager(Config& config);

		// Load all instances from config
		void reload();

		// Instance access
		[[nodiscard]] size_t count() const noexcept { return instances_.size(); }
		[[nodiscard]] bool empty() const noexcept { return instances_.empty(); }

		// Get by index
		[[nodiscard]] Instance& operator[](size_t index) { return instances_[index]; }
		[[nodiscard]] const Instance& operator[](size_t index) const { return instances_[index]; }

		// Get by name
		[[nodiscard]] Instance* get(std::string_view name);
		[[nodiscard]] const Instance* get(std::string_view name) const;

		// Find by predicate
		[[nodiscard]] Instance* find(std::function<bool(const Instance&)> pred);
		[[nodiscard]] std::vector<Instance*> find_all(std::function<bool(const Instance&)> pred);

		// Create new instance
		Instance& create(std::string name);

		// Remove instance
		bool remove(std::string_view name);
		bool remove(const Instance& instance) { return remove(instance.name()); }

		// Check existence
		[[nodiscard]] bool has(std::string_view name) const;

		// Iteration
		[[nodiscard]] Iterator begin() { return instances_.begin(); }
		[[nodiscard]] Iterator end() { return instances_.end(); }
		[[nodiscard]] ConstIterator begin() const { return instances_.begin(); }
		[[nodiscard]] ConstIterator end() const { return instances_.end(); }

		// Bulk operations
		void save_all();  // Save all instances to config
		void apply_to_all(std::function<void(Instance&)> func);

		// Filter views
		[[nodiscard]] std::vector<std::reference_wrapper<Instance>> with_root_access();
		[[nodiscard]] std::vector<std::reference_wrapper<Instance>> with_high_fps();
		[[nodiscard]] std::vector<std::reference_wrapper<Instance>> matching_resolution(int width, int height);

		// Config access
		[[nodiscard]] Config& config() noexcept { return *config_; }
		[[nodiscard]] const Config& config() const noexcept { return *config_; }

	private:
		Config* config_;
		std::vector<Instance> instances_;
	};

	// Range-based for loop helper
	inline InstanceManager::Iterator begin(InstanceManager& mgr) { return mgr.begin(); }
	inline InstanceManager::Iterator end(InstanceManager& mgr) { return mgr.end(); }
	inline InstanceManager::ConstIterator begin(const InstanceManager& mgr) { return mgr.begin(); }
	inline InstanceManager::ConstIterator end(const InstanceManager& mgr) { return mgr.end(); }

} // namespace bstk

#endif // BSTK_INSTANCE_MANAGER_HPP