#include <tictactoe.hpp>

using namespace eosio;

class tictactoe : eosio::contract {
    public:
    using contract::contract;

    struct [[eosio::table]] games {
        uint64_t game_id = 0;
        name game_host;
        name game_challenger;

        auto primary_key() const {return game_id;};
    };
    typedef multi_index<name( "gamestate"), games> games_state_table;

    

    [[eosio::action]] void welcome(name host, name challenger) {
        check( has_auth(host), "You don't have the right authorization to call this action.");
        print("Welcome, challengers ", host, " and ", challenger, "!");
   }

    [[eosio::action]] void create(const name &challenger, name &host) {
      require_auth(host);
      check(host != challenger, "You can't play this game against yourself.");
        games_state_table _gamestable(get_self(), get_self().value);

        _gamestable.emplace( host, [&](auto& new_game_row) {
          new_game_row.game_host = host;
          new_game_row.game_challenger = challenger;
        });
   
    }

    [[eosio::action]] void close(const name &challenger, const name &host) {
      require_auth(host);
      check(host != challenger, "You can't play this game against yourself.");


    }

    private:
};

