#if !defined(PLANNERS_SEARCH_BASE_HPP_)
#define PLANNERS_SEARCH_BASE_HPP_

#include "../formalism/action.hpp"
#include "search_result.hpp"

#include <map>
#include <string>
#include <variant>
#include <vector>

namespace planners
{
    class SearchBase
    {
      private:
        std::vector<std::function<void()>> event_handlers_;

      protected:
        volatile bool should_abort;

        SearchBase();

        /// @brief Notify all registered handlers
        void notify_handlers() const;

      public:
        virtual ~SearchBase() = default;

        /// @brief Register an event handler
        /// @param handler Event handler
        void register_handler(const std::function<void()>& handler);

        void abort();

        /// @brief Get statistics from the last planning step
        /// @return A dictionary with statistics
        virtual std::map<std::string, std::variant<int32_t, double>> get_statistics() const = 0;

        /// @brief Find a plan for the associated problem
        /// @param out_plan The plan, if one was found
        /// @return The result of the planning step
        virtual SearchResult plan(formalism::ActionList& out_plan) = 0;
    };

}  // namespace planners

#endif  // PLANNERS_SEARCH_BASE_HPP_