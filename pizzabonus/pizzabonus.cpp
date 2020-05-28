#include <eosio/eosio.hpp>
#include "./pizzabonus.h"

#define DEFAULT_THRESHOLD 5;

pizzabonus::pizzabonus(name self_contract, name first_receiver, eosio::datastream<const char*> ds) 
: 
contract(self_contract, first_receiver, ds),
ut(self_contract, self_contract.value),
config(self_contract, self_contract.value) {
  eosio::print("self_contract " , self_contract);
  eosio::print("first_receiver ", first_receiver);
  // self_contract pizzabonus = owner of the action
  // first_receiver pizzabonus ???
}

void pizzabonus::init() {
  config.get_or_create(_self, configtype{});
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
      if(row.pzsbought >= config.get().threshold) {
        row.coupons++;
        row.pzsbought = 0;
      }
      eosio::print("Counter ", row.pzsbought);
    });
  }
}

uint16_t pizzabonus::getcoupons(name user) {
  eosio::require_auth(user);
  auto iterator = ut.find(user.value);
  if (iterator == ut.end()) { // user doesn't exists
    eosio::print("getcoupons user not registered", user);
    return 0;
  } else {
    eosio::print("getcoupons ", user, " ", iterator->coupons);
    return iterator->coupons;
  }
}

void pizzabonus::redeemcoupon(name user) {
  eosio::require_auth(user);
  auto iterator = ut.find(user.value);
  if (iterator == ut.end()) { // new user
    eosio::print("redeemcoupon user not registered ", user);
  } else {
      if (iterator->coupons > 0) {
        ut.modify(iterator, user, [&](auto& row) {
          row.coupons--;
          eosio::print("redeemcoupon redeemed ", user, " new coupon count ", row.coupons);
        });
      } else {
        eosio::print("redeemcoupon no available coupons for ", user);        
      }
  }
}

void pizzabonus::chngthrhld(name user, uint16_t newvalue) { 
  eosio::require_auth(user);
  configtype config_state = config.get();
  config_state.threshold = newvalue;
  config.set(config_state, _self);
  eosio::print("new coupon threshold: ", config.get().threshold);
}