#ifndef NDB_DATABASE_HPP
#define NDB_DATABASE_HPP

#include <ndb/database.hpp>
#include <ndb/model.hpp>
#include <ndb/table.hpp>
#include <ndb/field.hpp>
#include <ndb/entity.hpp>
#include <ndb/expression.hpp>


#define ndb_field(TABLE, FIELD, TYPE, SIZE) \
struct FIELD##_  : ndb::field<TABLE, TYPE, ndb::size<SIZE>> { }; static constexpr const FIELD##_ FIELD {};

#define ndb_field_op \
template<class R> \
constexpr const auto operator=(const R& rhs) const \
{ \
    using L = std::decay_t<decltype(*this)>; \
    constexpr auto lhs = ndb::expression<L, ndb::expr_type_code::field, void> {}; \
    auto expr_value = ndb::expression<R, ndb::expr_type_code::value, void> { rhs }; \
    return ndb::expression<decltype(lhs), ndb::expr_type_code::op_assign, decltype(expr_value), ndb::expr_clause_code::set> { lhs, std::move(expr_value) }; \
}

namespace fields
{
    template<class Table>
    struct id : public ndb::field<Table, int, ndb::size<sizeof(int)>> { ndb_field_op };
}

namespace tables
{
    struct user
    {
        struct name_ : ndb::field<user, std::string, ndb::size<255>> {} name;

        using Detail_ = ndb::table_detail<
        ndb::entity<name_>
        >;
    };

    template<class Model>
    struct movie : ndb::table<Model>
    {
        using id_ = fields::id<movie>; static constexpr id_ id {};
        static constexpr struct name_ : ndb::field<movie, std::string, ndb::size<255>> { ndb_field_op } name {};
        static constexpr struct image_ : ndb::field<movie, std::string, ndb::size<255>> { ndb_field_op } image {};
        static constexpr struct user_ : ndb::field<movie, tables::user> {} user {};

        using Detail_ = ndb::table_detail
        <
        ndb::entity<id_, name_, image_>
        >;
    };

    template<class Model>
    struct music : ndb::table<Model>
    {
        using id_ = fields::id<music>; static constexpr id_ id {};
        static constexpr struct name_ : ndb::field<music, std::string, ndb::size<255>> { ndb_field_op } name {};
        static constexpr struct image_ : ndb::field<music, std::string, ndb::size<255>> { ndb_field_op } image {};
        //static constexpr struct user_ : ndb::field<movie, tables::user> {} user {};

        using Detail_ = ndb::table_detail
        <
        ndb::entity<id_, name_, image_>
        >;
    };
}

namespace models
{
    struct library
    {
        using movie_ = tables::movie<library>; static constexpr movie_ movie {};
        using music_ = tables::music<library>; static constexpr music_ music {};

        //static constexpr struct movie_ : ndb::table<library, tables::movie> {} movie {};
        //static constexpr struct sound_ : ndb::table<library, tables::movie> {} sound {};

        using Detail_ = ndb::model_detail
        <
        ndb::entity<movie_, music_>
        >;
    };
}

namespace databases
{
    struct project
    {
        static constexpr struct alpha_ : ndb::database<project, models::library, ndb::mongo>{} alpha {};
        static constexpr struct zeta_ : ndb::database<project, models::library, ndb::sqlite>{} zeta {};

        using Detail_ = ndb::database_detail<ndb::entity<alpha_, zeta_>>;
    };
} // databases

namespace dbs
{
    using alpha = databases::project::alpha_;
    using zeta = databases::project::zeta_;
}



/*
using Movie = entity<id, name, image>;

struct movie : db::entity<models::library::movie>
{
    int id_;
    std::string name_;

    ndb_serialize(id_ & name_)

    movie(int id) : entity(id) {}
};
*/

#endif //NDB_DATABASE_HPP
