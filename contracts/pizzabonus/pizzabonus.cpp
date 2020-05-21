#include <eosio/eosio.hpp>
#include "./pizzabonus.h"

pizzabonus::pizzabonus(name self_contract, name first_receiver, eosio::datastream<const char*> ds) 
: contract(self_contract, first_receiver, ds), ut(self_contract, self_contract.value) {
  // TODO: Research passing custom parameters to the contract constructor
  coupon_threshold = 5;
  eosio::print("self_contract " , self_contract);
  eosio::print("first_receiver ", first_receiver);
  // self_contract pizzabonus = owner of the action
  // first_receiver pizzabonus ???
}

void pizzabonus::buypizza(name user) {
  // Valid if the user exist in the chain
  eosio::require_auth(user);
  auto iterator = ut.find(user.value);
  if (iterator == ut.end()) { // new user
    eosio::print("register new user ", user);
    ut.emplace(user, [&](auto& row) {
      row.username = user;
      row.pzsbought = 1;
    });
  } else {
    eosio::print("user already exist and bought a pizza ", user);
    ut.modify(iterator, user, [&](auto& row) {
      row.pzsbought++;
      if(row.pzsbought == coupon_threshold) {
        row.coupons++;
        row.pzsbought = 0;
      }
      eosio::print("Counter ", row.pzsbought);
    });
  }
}

uint16_t pizzabonus::getcoupons(name user) {
  //
  return 0;
}

void pizzabonus::redeemcoupon(name user) {
  //
}

void pizzabonus::chngthrhld(name user, uint16_t newvalue) { 
  //
}
