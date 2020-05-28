#pragma once

#include <eosio/eosio.hpp>

struct [[eosio::table]] pizzauser {
  eosio::name username = ""_n;
  uint64_t coupons = 0;
  uint64_t pizzasbought = 0;

  uint64_t primary_key() const { return username.value; }
};

typedef eosio::multi_index<"user"_n, pizzauser> usertable_t;
