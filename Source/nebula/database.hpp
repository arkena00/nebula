#ifndef NDB_DATABASE_HPP
#define NDB_DATABASE_HPP

#include <ndb/initializer.hpp>
#include <ndb/engine/sqlite/sqlite.hpp>
#include <ndb/engine.hpp>

#include <ndb/database.hpp>
#include <ndb/model.hpp>
#include <ndb/table.hpp>
#include <ndb/field.hpp>
#include <ndb/entity.hpp>

#include <ndb/preprocessor.hpp>
#include <ndb/expression.hpp>

#include <ndb/query.hpp>

namespace tables
{
	// id | name | rarity | stability | mass
	template<class Model>
	struct atom : ndb::table<Model>
	{
		ndb_field(atom, id, int, sizeof(int));
		ndb_field(atom, name, std::string, 255);
		ndb_field(atom, rarity, int, sizeof(int));
		ndb_field(atom, stability, int, sizeof(int));
		ndb_field(atom, mass, int, sizeof(int));

		using Detail_ = ndb::table_detail
			<
			ndb::entity<id_, name_, rarity_, stability_, mass_>
			>;
	};

	// id | domain_id | name | build_time | volume | mps | eps
    template<class Model>
    struct object : ndb::table<Model>
    {
		ndb_field(object, id, int, sizeof(int));
		ndb_field(object, name, std::string, 255);
		ndb_field(object, domain_id, int, sizeof(int));
		ndb_field(object, build_time, int, sizeof(int));
		ndb_field(object, volume, int, sizeof(int));
		ndb_field(object, description, std::string, 500);
			
        using Detail_ = ndb::table_detail
        <
        ndb::entity<id_, name_, domain_id_, build_time_, volume_, description_>
        >;
    };
}

namespace models
{
    struct library
    {
		using atom_ = tables::atom<library>; static constexpr atom_ atom{};
        using object_ = tables::object<library>; static constexpr object_ object{};

        using Detail_ = ndb::model_detail
        <
			ndb::entity<atom_, object_>
        >;
    };
}

namespace databases
{
    struct project
    {
        static constexpr struct library_ : ndb::database<project, models::library, ndb::sqlite>{} nebula {};

        using Detail_ = ndb::database_detail<ndb::entity<library_>>;
    };
} // databases

namespace dbs
{
    using library = databases::project::library_;
}

static constexpr const models::library library;

#endif // NDB_DATABASE_HPP
