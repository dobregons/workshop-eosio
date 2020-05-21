#include <eosio/eosio.hpp>

using eosio::name;
using eosio::contract;

class [[eosio::contract]] hello : public contract {
  public:
    using contract::contract;

    [[eosio::action]]
    void hi(name user) {
      eosio::print("This is my first contract ", user);
    }
};
