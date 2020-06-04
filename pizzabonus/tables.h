  
#pragma once

#include <eosio/eosio.hpp>
#include <eosio/singleton.hpp>

// table to store user information
struct [[eosio::table]] pizzauser {
  eosio::name username = ""_n;
  uint16_t pzsbought = 0;
  uint16_t coupons = 0;

  uint64_t primary_key() const { return username.value; }
};

struct [[eosio::table]] configtype {
  uint16_t threshold = 5;
};

typedef eosio::multi_index<"pizzauser"_n, pizzauser> usertable_t;
typedef eosio::singleton<"pizzaconfig"_n, configtype> config_t;