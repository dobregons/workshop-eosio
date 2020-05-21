#pragma once

#include <eosio/eosio.hpp>

struct [[eosio::table]] coupon {
  uint16_t value;
  bool active = false;
};

// EOSIO_REFLECT(Coupon, value, active);

struct [[eosio::table]] user {
  eosio::name username = ""_n;
  coupon cpn = coupon{};

  // eosio::name primary_key() const { return username; }
  uint64_t primary_key() const { return username.value; }
};

// EOSIO_REFLECT(User, username, cpm);

typedef eosio::multi_index<"user"_n, user> usertable_t;
